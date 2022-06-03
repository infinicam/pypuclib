import cv2
import pypuclib
from pypuclib import CameraFactory, XferData, Decoder
import numpy as np
# import datetime
import time

# Load yolo
def load_yolo():
    net = cv2.dnn.readNet("yolov3-tiny.weights", "yolov3-tiny.cfg")
    try:
        if hasattr("cv2", "cuda") and cv2.cuda.getCudaEnableDeviceCount() >= 1:
            net.setPreferableBackend(cv2.dnn.DNN_BACKEND_CUDA)
            net.setPreferableTarget(cv2.dnn.DNN_TARGET_CUDA_FP16)
    except:
        print("Cuda was not detected")
    classes = []
    with open("coco.names", "r") as f:
        classes = [line.strip() for line in f.readlines()] 
    
    output_layers = [layer_name for layer_name in net.getUnconnectedOutLayersNames()]
    return net, classes, output_layers

def detect_objects(img, net, outputLayers):         
    blob = cv2.dnn.blobFromImage(img, scalefactor=0.00392, size=(160, 160), mean=(0, 0, 0), swapRB=True, crop=False)
    net.setInput(blob)
    outputs = net.forward(outputLayers)
    return blob, outputs

def get_box_dimensions(outputs, height, width):
    boxes = []
    confs = []
    class_ids = []
    for output in outputs:
        for detect in output:
            scores = detect[5:]
            class_id = np.argmax(scores)
            conf = scores[class_id]
            if conf > 0.3:
                w = int(detect[2] * width)
                h = int(detect[3] * height)
                x = int(int(detect[0] * width) - w/2)
                y = int(int(detect[1] * height) - h / 2)
                boxes.append([x, y, w, h])
                confs.append(float(conf))
                class_ids.append(class_id)
    return boxes, confs, class_ids
            
def draw_labels(boxes, confs, class_ids, classes, img): 
    indexes = cv2.dnn.NMSBoxes(boxes, confs, 0.5, 0.4)
    for i in range(len(boxes)):
        if i in indexes:
            x, y, w, h = boxes[i]
            label = str(classes[class_ids[i]])
            cv2.rectangle(img, (x,y), (x+w, y+h), (255,0,255), 2)
            cv2.putText(img, label, (x, y - 5), cv2.FONT_HERSHEY_PLAIN, 1, (255,0,255), 1)
    cv2.imshow("Image", img)

if __name__ == '__main__':

    model, classes, output_layers = load_yolo()
    cam = CameraFactory().create()
    decoder = cam.decoder()
    prevTime = time.time()
    numFrames = 0
    totalTime = 0.0
    warmup = 30
    while True:
        xferData = cam.grab()
        frameMono = decoder.decode(xferData)
        height, width = frameMono.shape
        frame = cv2.merge((frameMono, frameMono, frameMono))
        CurrTime = time.time()
        prevTime = time.time()
        blob, outputs = detect_objects(frame, model, output_layers)
        CurrTime = time.time()
        if numFrames >= warmup:
            totalTime += CurrTime - prevTime
        numFrames += 1
        if numFrames >= warmup and totalTime>0:
            t = (numFrames-warmup) / totalTime
        else:
            t = 0.0
        boxes, confs, class_ids = get_box_dimensions(outputs, height, width)
        draw_labels(boxes, confs, class_ids, classes, frame)
        key = cv2.waitKey(1)
        
        print(t, flush=True)
        
        if key == 27: # Hit escape to quit
            break


    cv2.destroyAllWindows()
