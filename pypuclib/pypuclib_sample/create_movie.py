import cv2 # need to import extra module "pip install opencv-python"

import threading
import pypuclib
from pypuclib import CameraFactory, Camera, XferData, Decoder

# define max decode thread
PUC_MAX_DECODE_THREAD_COUNT = 32

print(pypuclib.__doc__)


# To connect the camera first detected
cam = CameraFactory().create()


# To decode image, get decoder obj from camera
decoder = cam.decoder()


# setup save video file
path = "create_movie.avi"
width = 512
height = 512
SAVE_FRAME_COUNT = 1000
fps = 60
codec = cv2.VideoWriter_fourcc(*'MJPG') # codec type of avi file 
video = cv2.VideoWriter(path, codec, fps, (width, height), False)


# global variable
b_show = False      # UI flag
g_count = 0         # counter of save frames


# Explanation
print("press Esc to quit this application ")
print("press 's' to save a AVI file")


# at first, set multi decode thread
while(1):
    threadnum = input("input decode thread num >> ")
    if threadnum.isdecimal() & (0 < int(threadnum) <= PUC_MAX_DECODE_THREAD_COUNT):
        decoder.setNumDecodeThread(int(threadnum))
        break


# callback function in transfer
def callback(data):
    global g_count
    global b_show

    # finish save AVI file
    if g_count == SAVE_FRAME_COUNT:
        video.release()
        g_count = 0
        b_show = True
        
    if video.isOpened() == True:
        src = decoder.decode(data,0,0,512,512) # decode range (x,y,w,h) = (0,0,512,512)
        video.write(src)
        g_count += 1
     

 # begin transfer
cam.beginXfer(callback)


while True:

    if b_show == True:
        # Grab the single image data
        xferData = cam.grab()

        # Decode the data can be used as image
        img = decoder.decode(xferData)

        # get sequence number of transfer data
        seq = "sequenceNo = " + str(xferData.sequenceNo())
        cv2.putText(img, seq, (0, 50), cv2.FONT_HERSHEY_COMPLEX_SMALL, 1, (255,255,255), 2, cv2.LINE_AA)

        # Show the image
        cv2.imshow("INFINICAM", img)

    # get key what user input
    key = cv2.waitKey(1)

    if key & 0xFF == 27: # press Esc to end application 
        break

    elif key & 0xFF == ord('s'): # press 's' to save avi
        b_show = False
        if video.isOpened() == False:
            video.open(path, codec, fps, (width, height), False)


 # end transfer     
cam.endXfer()

print("end")

 # Close live image window
cv2.destroyAllWindows()
