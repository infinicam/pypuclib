import tkinter as tk
import tkinter.font as tkfont
from tkinter import ttk
from tkinter import filedialog
from PIL import Image, ImageTk # need to import extra module "pip install pillow"

import numpy as np
import os, csv, json, threading
from enum import IntEnum

import pypuclib
from pypuclib import CameraFactory, Camera, XferData, Resolution, Decoder

class FILE_TYPE(IntEnum):
    CSV = 0
    BINARY = 1

class BinaryReader():
    def __init__(self, name):
        # read json file
        self.dict = dict()
        with open(name, mode='rt', encoding='utf-8') as file:
            self.dict = json.load(file)

        self.file = open(name.replace(".json", ".npy"), "rb")

        # read file info
        d = np.load(self.file)
        self.framesize = self.file.tell()
        self.file.seek(0, os.SEEK_END)
        self.filesize = self.file.tell()
        self.framecount = int(self.filesize / self.framesize)
        self.file.seek(0)

        # prepare for decode
        self.decoder = Decoder(self.dict["quantization"])
        self.width = self.dict["width"]
        self.height = self.dict["height"]

        self.opened = True

    def read(self, frameNo, raw = False):
        self.file.seek(self.framesize * frameNo)
        array = np.load(self.file)
        if raw:
            return array
        else:
            return self.decoder.decode(array, Resolution(self.width, self.height))

    def readseqNo(self,frameNo):
        self.file.seek(self.framesize * frameNo)
        array = np.load(self.file)
        return self.decoder.extractSequenceNo(array, self.width, self.height)

class FileCreator():
    def __init__(self, name, filetype):
        if filetype == FILE_TYPE.CSV:
            self.file = open(name + ".csv", 'w')
            self.writer = csv.writer(self.file, lineterminator='\n')
            self.writer.writerow(["SequenceNo", "diff"])
        elif filetype == FILE_TYPE.BINARY:
            self.file = open(name + ".npy", 'wb')
        else:
            return

        self.oldSeq = 0
        self.opened = True
        self.filetype = filetype

    def write(self, xferData):
        if self.opened:
            if self.filetype == FILE_TYPE.CSV:
                self.write_csv(xferData.sequenceNo())
            elif self.filetype == FILE_TYPE.BINARY:
                self.write_binary(xferData.sequenceNo(),
                                  xferData.data())

    def write_csv(self, seq):
        if self.oldSeq != seq:
            self.writer.writerow(
                        [str(seq), 
                        str(seq - self.oldSeq), 
                        "*" if (seq - self.oldSeq) > 1 else ""])
            self.oldSeq = seq

    def write_binary(self, seq, nparray):
        if self.oldSeq != seq:
            np.save(self.file, nparray)
            self.oldSeq = seq

    def create_json(name, cam):
        data = dict()
        data["framerate"] = cam.framerate()
        data["shutter"] = cam.shutter()
        data["width"] = cam.resolution().width
        data["height"] = cam.resolution().height
        data["quantization"] = cam.decoder().quantization()
        with open(name+".json", mode='wt', encoding='utf-8') as file:
            json.dump(data, file, ensure_ascii=False, indent=2)

    def close(self):
        if self.opened:
            self.file.close()


class SbTextFrame(tk.Frame):
    def __init__(self,master):
        super().__init__(master)
        text = tk.Text(self,wrap='none',undo=True)
        x_sb = tk.Scrollbar(self,orient='horizontal')
        y_sb = tk.Scrollbar(self,orient='vertical')
        x_sb.config(command=text.xview)
        y_sb.config(command=text.yview)
        text.config(xscrollcommand=x_sb.set,yscrollcommand=y_sb.set)
        text.grid(column=0,row=0,sticky='nsew')
        x_sb.grid(column=0,row=1,sticky='ew')
        y_sb.grid(column=1,row=0,sticky='ns')
        self.columnconfigure(0,weight=1)
        self.rowconfigure(0,weight=1)
        self.text = text
        self.x_sb = x_sb
        self.y_sb = y_sb


def add_tab(fname):
    global tframes,fnames,notebook

    tframe=SbTextFrame(notebook)
    tframes.append(tframe)

    if os.path.isfile(fname):
        f=open(fname,'r')
        lines=f.readlines()
        f.close()
        for line in lines:
            tframe.text.insert('end',line)

    fnames.append(fname)
    title=os.path.basename(fname)

    notebook.add(tframe,text=title)



class Application(tk.Frame):
    def __init__(self, master = None):
        super().__init__(master)
        master.title("gui_sample")
        master.geometry("800x600")
        self.pack(expand=1, fill=tk.BOTH, anchor=tk.NW)

        self.cam = CameraFactory().create()
        self.fcreator = None
        self.decoder = self.cam.decoder()

        self.framerateValues = [1, 10, 50, 100, 125, 250, 500, 950, 1000, 
                                1500, 2000, 2500, 3000, 3200, 4000, 5000, 
                                8000, 10000, 20000, 25000, 30000]

        self.framerateStr = tk.IntVar()
        self.resolutionStr = tk.StringVar()
        self.shutterStr = tk.StringVar()
        self.acqutionVal = tk.IntVar()
        self.savefileVal = tk.IntVar()
        self.uistopVal = tk.BooleanVar()
        self.isRec = False
        self.locker = threading.Lock()
        self.font = tkfont.Font(self,family="Arial",size=10,weight="bold")

        self.createWidget()

        self.delay = 15
        self.updateID = 0
        self.update()

    def createWidget(self):
        #---------------------------------------------------
        # options frame
        #---------------------------------------------------
        frameWidth=300
        self.optionFrame = ttk.LabelFrame(self, 
                                          text="options", 
                                          width=frameWidth,
                                          relief=tk.RAISED)
        self.optionFrame.propagate(False)
        self.optionFrame.pack(side=tk.RIGHT, fill=tk.Y, padx=5, pady=5)

        #---------------------------------------------------
        # framerate
        #---------------------------------------------------
        self.frameratePanel = ttk.Frame(self.optionFrame,
                                        width=frameWidth,
                                        height=30,
                                        relief=tk.FLAT)
        self.frameratePanel.propagate(False)
        self.frameratePanel.pack(side=tk.TOP, fill=tk.Y, padx=5, pady=5)

        self.framerateLabel = ttk.Label(self.frameratePanel,text="Framerate[fps]", width=20)
        self.framerateLabel.pack(side=tk.LEFT, padx=5)

        self.framerateList = ttk.Combobox(self.frameratePanel, 
                                          values=self.framerateValues, 
                                          textvariable=self.framerateStr)
        self.framerateList.pack(side=tk.LEFT, padx=5)
        self.framerateList.bind("<<ComboboxSelected>>", self.updateFramerate)

        #---------------------------------------------------
        # shutter
        #---------------------------------------------------
        self.shutterPanel = ttk.Frame(self.optionFrame,
                                      width=frameWidth,
                                      height=30,
                                      relief=tk.FLAT)
        self.shutterPanel.propagate(False)
        self.shutterPanel.pack(side=tk.TOP, fill=tk.Y, padx=5, pady=5)

        self.shutterLabel = ttk.Label(self.shutterPanel,text="Shutter speed[sec]", width=20)
        self.shutterLabel.pack(side=tk.LEFT, padx=5)

        self.shutterList = ttk.Combobox(self.shutterPanel,  
                                        textvariable=self.shutterStr)
        self.shutterList.pack(side=tk.LEFT, padx=5)
        self.shutterList.bind("<<ComboboxSelected>>", self.updateShutter)

        #---------------------------------------------------
        # resolution
        #---------------------------------------------------
        self.resolutionPanel = ttk.Frame(self.optionFrame,
                                         width=frameWidth,
                                         height=30,
                                         relief=tk.FLAT)
        self.resolutionPanel.propagate(False)
        self.resolutionPanel.pack(side=tk.TOP, fill=tk.Y, padx=5, pady=5)

        self.resolutionLabel = ttk.Label(self.resolutionPanel,text="Resolution[pixel]", width=20)
        self.resolutionLabel.pack(side=tk.LEFT, padx=5)

        self.resolutionList = ttk.Combobox(self.resolutionPanel,  
                                           textvariable=self.resolutionStr)
        self.resolutionList.pack(side=tk.LEFT, padx=5)
        self.resolutionList.bind("<<ComboboxSelected>>", self.updateResolution)

        #---------------------------------------------------
        # Acquisition mode
        #---------------------------------------------------
        self.acquisitionPanel = ttk.Frame(self.optionFrame,
                                          width=frameWidth,
                                          height=30,
                                          relief=tk.FLAT)
        self.acquisitionPanel.propagate(False)
        self.acquisitionPanel.pack(side=tk.TOP, fill=tk.Y, padx=5, pady=5)

        self.acqusitionLabel = ttk.Label(self.acquisitionPanel,text="Acquisition mode", width=18)
        self.acqusitionLabel.pack(side=tk.LEFT, padx=5)

        self.acqusition1 = tk.Radiobutton(self.acquisitionPanel,
                                          text="single",
                                          value=0,
                                          variable=self.acqutionVal,
                                          command=self.updateAcquisition)
        self.acqutsiion2 = tk.Radiobutton(self.acquisitionPanel,
                                          text="continuous",
                                          value=1,
                                          variable=self.acqutionVal,
                                          command=self.updateAcquisition)
        self.acqusition1.pack(side=tk.LEFT, padx = 5)
        self.acqutsiion2.pack(side=tk.LEFT, padx = 5)

        #---------------------------------------------------
        # savefiles
        #---------------------------------------------------
        self.savefilesPanel = ttk.Frame(self.optionFrame,
                                        width=frameWidth,
                                        height=30,
                                        relief=tk.FLAT)
        self.savefilesPanel.propagate(False)
        self.savefilesPanel.pack(side=tk.TOP, fill=tk.Y, padx=5, pady=5)

        self.savefilesLabel = ttk.Label(self.savefilesPanel,text="Save file", width=18)
        self.savefilesLabel.pack(side=tk.LEFT, padx=5)

        self.savefile_csv = tk.Radiobutton(self.savefilesPanel,
                                           text="csv",
                                           value=FILE_TYPE.CSV.value,
                                           variable=self.savefileVal)
        self.savefile_bin = tk.Radiobutton(self.savefilesPanel,
                                           text="binary",
                                           value=FILE_TYPE.BINARY.value,
                                           variable=self.savefileVal,)
        self.savefile_csv.pack(side=tk.LEFT, padx = 5)
        self.savefile_bin.pack(side=tk.LEFT, padx = 5)


        #---------------------------------------------------
        # record button
        #---------------------------------------------------
        self.recPanel = ttk.Frame(self.optionFrame,
                                  width=frameWidth,
                                  height=30,
                                  relief=tk.FLAT)
        self.recPanel.propagate(False)
        self.recPanel.pack(side=tk.BOTTOM, fill=tk.Y, padx=5, pady=5)
        self.recButton = ttk.Button(self.recPanel, 
                                    text = "REC", 
                                    command=self.rec,
                                    width=15)
        self.recButton.pack(side=tk.RIGHT,anchor="center", expand=True)
        self.uistopCheck = ttk.Checkbutton(self.recPanel,
                                           text="Stop Live",
                                           variable=self.uistopVal,
                                           command=self.uistop)
        self.uistopCheck.pack(side=tk.RIGHT,anchor="center", expand=True)

        self.resetSeqButton = ttk.Button(self.recPanel,
                                         text = "Reset Seq No",
                                         command = self.resetSequenceNo,
                                         width = 30)
        self.resetSeqButton.pack(side=tk.RIGHT, anchor = "center", expand = True)


        #---------------------------------------------------
        # reset button
        #---------------------------------------------------
        self.resetPanel = ttk.Frame(self.optionFrame,
                                  width=frameWidth,
                                  height=30,
                                  relief=tk.FLAT)
        self.resetPanel.propagate(False)
        self.resetPanel.pack(side=tk.BOTTOM, fill=tk.Y, padx=5, pady=5)
        self.resetButton = ttk.Button(self.resetPanel, 
                                    text = "RESET", 
                                    command=self.resetDevice,
                                    width=15)
        self.resetButton.pack(side=tk.RIGHT,anchor="sw", expand=True)



        #---------------------------------------------------
        # canvas
        #---------------------------------------------------
        self.canvas = tk.Canvas(self, width=1296, height=1080)
        self.canvas.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True, padx=5, pady=5)

        #---------------------------------------------------
        # initialize ui
        #---------------------------------------------------
        self.framerateList.set(self.cam.framerate())
        self.updateResolutionList()
        self.updateShutterList()
        self.updateAcquisition()

    def update(self):
        data = self.cam.grab()
        self.updatecanvas(data)
        self.updateID = self.after(self.delay, self.update)

    def updatecanvas(self, data):
        cw = self.canvas.winfo_width()
        ch = self.canvas.winfo_height()
        w = data.resolution().width
        h = data.resolution().height
        scale = 1
        if cw > 1 and ch > 1:
            scale = cw/w if cw/w < ch/h else ch/h

        array = self.decoder.decode(data)
        i = Image.fromarray(array).resize((int(w*scale), int(h*scale)))
        self.img = ImageTk.PhotoImage(image=i)
        self.canvas.delete("all")
        pos = [(cw-i.width)/2,(ch-i.height)/2]
        self.canvas.create_image(pos[0], pos[1], anchor="nw", image=self.img)
        self.canvas.create_text(pos[0]+5, pos[1]+5, anchor="nw", 
                                text="SequeceNo:" + str(data.sequenceNo()),
                                font=self.font, fill="limeGreen")

    def updateFramerate(self, e):
        rate = self.framerateStr.get()
        self.cam.setFramerateShutter(rate, rate)
        self.updateResolutionList()
        self.updateShutterList()

    def updateShutter(self, e):
        resStr = self.shutterStr.get().split("1/")
        self.cam.setShutter(int(resStr[1]))

    def updateResolution(self, e):
        resStr = self.resolutionStr.get().split("x")
        self.cam.setResolution(int(resStr[0]), int(resStr[1]))

    def updateResolutionList(self):
        resMax = self.cam.resolutionMax()
        resLimit = self.cam.resolutionLimit()
        hStep = resLimit.limitH.step
        hMin = resLimit.limitH.min
        hMax = resMax.height
        wStep = resLimit.limitW.step
        wMin = resLimit.limitW.min
        wMax = resMax.width

        resW = range(wMin, wMax+1, wStep if wStep != 0 else 1)
        resH = range(hMin, hMax+1, hStep if hStep != 0 else 1)
        resValues = []
        for h in resH:
            for w in resW:
                resValues.append(str(w)+"x"+str(h))
        self.resolutionList.config(values=resValues)
        res = self.cam.resolution()
        self.resolutionList.set(str(res.width)+"x"+str(res.height))

    def updateShutterList(self):
        fps = self.cam.framerate()
        shutValues = []
        for s in self.framerateValues:
               if s >= fps:
                   shutValues.append("1/" + str(s))
        self.shutterList.config(values = shutValues)
        shutter = self.cam.shutter()
        self.shutterList.set("1/" + str(shutter))

    def updateAcquisition(self):
        acq = self.acqutionVal.get()
        if acq and not self.cam.isXferring():
            self.cam.beginXfer(self.cppCallback)
        if not acq and self.cam.isXferring():
            self.cam.endXfer()

    def cppCallback(self, xferData):
        self.locker.acquire()
        if self.isRec:
            self.fcreator.write(xferData)
        self.locker.release()

    def rec(self):
        self.locker.acquire()
        self.isRec = not self.isRec
        if self.isRec:
            self.recButton.state(["pressed"])
            self.fcreator = FileCreator("test", self.savefileVal.get())
        else:
            self.recButton.state(["!pressed"])
            self.fcreator.close()
            FileCreator.create_json("test", self.cam)
        self.locker.release()

    def uistop(self):
        if self.uistopVal.get():
            self.after_cancel(self.updateID)
        else:
            self.updateID = self.after(self.delay, self.update)

    def terminate(self):
        self.after_cancel(self.updateID)
        self.cam.close()
        if self.fcreator is not None:
            self.fcreator.close()

    def resetSequenceNo(self):
        self.cam.resetSequenceNo()

    def resetDevice(self):
        self.locker.acquire()
        self.cam.resetDevice()
        self.cam = CameraFactory().create()
        self.framerateList.set(self.cam.framerate())
        self.updateResolutionList()
        self.updateShutterList()
        self.locker.release()


class FileApplication(tk.Frame):
    def __init__(self, master = None):
        super().__init__(master)
        master.geometry("800x600")
        self.pack(expand=1, fill=tk.BOTH, anchor=tk.NW)

        self.font = tkfont.Font(self,family="Arial",size=10,weight="bold")

        self.createWidget()

    def createWidget(self):
        #---------------------------------------------------
        # options frame
        #---------------------------------------------------
        frameWidth=300
        self.optionFrame = ttk.LabelFrame(self, 
                                          text="file data", 
                                          width=frameWidth,
                                          relief=tk.RAISED)
        self.optionFrame.propagate(False)
        self.optionFrame.pack(side=tk.RIGHT, fill=tk.Y, padx=5, pady=5)

        #---------------------------------------------------
        # file open
        #---------------------------------------------------
        self.framecountPanel = ttk.Frame(self.optionFrame,
                                        width=frameWidth,
                                        height=30,
                                        relief=tk.FLAT)

        self.framecountPanel.propagate(False)
        self.framecountPanel.pack(side=tk.TOP, fill=tk.Y, padx=5, pady=5)

        self.framecount_text = tk.StringVar()
        self.framecount_text.set("file framecount = %d" % 0)
        self.fileframelabel = tk.Label(self.framecountPanel, textvariable = self.framecount_text)
        self.fileframelabel.pack(side=tk.LEFT, padx=5)

        self.filePanel = ttk.Frame(self.optionFrame,
                                  width=frameWidth,
                                  height=30,
                                  relief=tk.FLAT)

        self.filePanel.propagate(False)
        self.filePanel.pack(side=tk.BOTTOM, fill=tk.Y, padx=5, pady=5)


        self.fileButton = ttk.Button(self.filePanel, 
                                    text = "OPEN", 
                                    command=self.openfile,
                                    width=15)
        self.fileButton.pack(side=tk.RIGHT,anchor="center", expand=True)



        #---------------------------------------------------
        # canvas
        #---------------------------------------------------
        self.canvas = tk.Canvas(self, width=1296, height=1080)
        self.canvas.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True, padx=5, pady=5)



    def createimagedata(self, data, seqNo):
        cw = self.canvas.winfo_width()
        ch = self.canvas.winfo_height()
        w = self.reader.width
        h = self.reader.height
        scale = 1
        if cw > 1 and ch > 1:
            scale = cw/w if cw/w < ch/h else ch/h

        array = data
        i = Image.fromarray(array).resize((int(w*scale), int(h*scale)))
        self.img = ImageTk.PhotoImage(image=i)
        self.canvas.delete("all")
        pos = [(cw-i.width)/2,(ch-i.height)/2]
        self.canvas.create_image(pos[0], pos[1], anchor="nw", image=self.img)
        self.canvas.create_text(pos[0]+5, pos[1]+5, anchor="nw", 
                                text="SequeceNo:" + str(seqNo + self.iniFileSeqNo),
                                font=self.font, fill="limeGreen")
        
    def openfile(self):
        dir = os.path.abspath(os.path.dirname(__file__))
        type = [("データファイル","*.json")]
        fname = filedialog.askopenfilename(filetypes=type, initialdir=dir)

        self.reader = BinaryReader(fname)
        data = self.reader.read(0)
        self.iniFileSeqNo = self.reader.readseqNo(0)
        
        self.createimagedata(data, self.iniFileSeqNo)

        self.filespinboxLabel = ttk.Label(self.filePanel, text="Frame:", width=8)
        self.filespinboxLabel.pack(side=tk.LEFT, padx=5)

        self.filespinBox = ttk.Spinbox(self.filePanel,
                                       textvariable=0,
                                       from_=0,
                                       to=self.reader.framecount,
                                       command=self.updatecanvas,
                                       increment=1,
                                       )
        self.filespinBox.pack(side=tk.LEFT, padx=5)
        
        self.framecount_text.set("file framecount = %d" % self.reader.framecount)


    def updatecanvas(self):
        seqNo = int(self.filespinBox.get())
        data = self.reader.read(seqNo)
        self.createimagedata(data, seqNo)


def main():
    global root,notebook,tframes,fnames
    root = tk.Tk()

    root.title('tabbed editor')
    root.geometry('800x600')
    notebook = ttk.Notebook(root)
    notebook.pack(fill='both',expand=1)

    app = Application(master = root)
    notebook.add(app, text="cam")
    fileapp = FileApplication(master = root)
    notebook.add(fileapp, text="file")

    app.mainloop()
    app.terminate()

if __name__ == '__main__':
    main()
