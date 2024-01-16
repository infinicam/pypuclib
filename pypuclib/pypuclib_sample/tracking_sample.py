import cv2 # need to import extra module "pip install opencv-python"
import numpy as np

import time, math, multiprocessing
from multiprocessing import Process, Manager, Array, Value
from multiprocessing import shared_memory

import pypuclib
from pypuclib import CameraFactory, Camera, XferData, Resolution, Decoder

def trim(array, roi):
    return array[roi[1]:roi[1] + roi[3], roi[0]:roi[0] + roi[2]]

def renewROI(roi, pt, reso):
    tl = [int(roi[2] / 4),
          int(roi[3] / 4)]
    offset = [(pt[0] - tl[0]) // 8 * 8,
              (pt[1] - tl[1]) // 8 * 8]

    if roi[0] + offset[0] > 0 and roi[0] + offset[0] + roi[2] < reso.width:
        roi[0] += offset[0]

    if roi[1] + offset[1] > 0 and roi[1] + offset[1] + roi[3] < reso.height:
        roi[1] += offset[1]

class Measure():
    def __init__(self, master = None):
        self.count = 0
        self.stTime = self.edTime = time.time()
        self.elapsed_time = 1

    def measureTime(self):
        self.count += 1
        if self.count % 1000 == 0:
            self.edTime = time.time()
            self.elapsed_time = self.edTime - self.stTime
            self.stTime = self.edTime
        return self.elapsed_time

    def measureFPS(self):
        return 1000 / self.measureTime()

class Application():
    def __init__(self, master = None):

        # prepare camera
        self.cam = CameraFactory().create()
        self.reso = self.cam.resolution()
        self.dec = self.cam.decoder()
        self.dec.setNumDecodeThread(4)
        data = self.cam.grab()
        frame = self.dec.decode(data)

        # create shared memory for image
        self.shm = shared_memory.SharedMemory(create=True, size=data.dataSize(), name="raw_image")
        self.shared_arr = np.ndarray(shape=self.shm.size, dtype="uint8", buffer=self.shm.buf)

        # template
        while True:
            # tempROI is tuple : (x, y, width, height)
            tempROI = cv2.selectROI("select", frame, False)

            # ROI's width and height is not 0
            if tempROI[2] != 0 and tempROI[3] != 0:
                break

        cv2.destroyWindow("select")
        self.tempROI = list(tempROI)
        self.template = trim(frame, self.tempROI)

        # decoding roi(twice of template)
        self.roi = list()
        self.roi.append(int(self.tempROI[0] - self.tempROI[2] / 2) // 8 * 8)
        self.roi.append(int(self.tempROI[1] - self.tempROI[3] / 2) // 8 * 8)
        self.roi.append(int(self.tempROI[2] * 2))
        self.roi.append(int(self.tempROI[3] * 2))

        # Shared values
        self.trackPt = Array('i', 2)
        self.fps = Value("f", 0)

        self.oldSeq = 0
        self.measure = Measure()

    def cppcallback(self, xferdata):
        seq = xferdata.sequenceNo()
        if self.oldSeq != seq :
            # calculate matching pt
            frame = self.dec.decode(xferdata, self.roi[0], self.roi[1], self.roi[2], self.roi[3])
            match = cv2.matchTemplate(frame, self.template, cv2.TM_CCORR_NORMED)
            min_value, max_value, min_pt, max_pt = cv2.minMaxLoc(match)

            # move decoding roi
            renewROI(self.roi, max_pt, self.reso)

            # share data
            self.trackPt[0] = self.roi[0] + max_pt[0]
            self.trackPt[1] = self.roi[1] + max_pt[1]
            np.copyto(self.shared_arr, xferdata.data())
            self.fps.value = self.measure.measureFPS()

            self.oldSeq = seq

    def processing(self):
        self.cam.beginXfer(self.cppcallback)
        p = Process(target=window, args=[self.dec.quantization(), self.tempROI[2:4], self.trackPt, self.fps])
        p.start()
        p.join()
        self.cam.close()

def window(q, tempsize, pos, fps):
    dec = Decoder(q)
    while True:
        shm = shared_memory.SharedMemory(name="raw_image")
        arr = np.ndarray(shape=shm.size, dtype="uint8", buffer=shm.buf)
        img = dec.decode(arr, Resolution(1246, 1008))
        col = cv2.cvtColor(img, cv2.COLOR_GRAY2RGB)
        cv2.putText(col, "fps="+str(fps.value), (30, 30), cv2.FONT_HERSHEY_PLAIN, 2, (255, 255, 255), 1)
        cv2.rectangle(col, (pos[0], pos[1]),(pos[0] + tempsize[0], pos[1] + tempsize[1]), (0, 255, 0), 2)
        cv2.imshow("INFINICAM", col)
        key = cv2.waitKey(33)
        if key == 27:
            break
    cv2.destroyAllWindows()

def main():
    app = Application()
    app.processing()

if __name__ == '__main__':
    main()