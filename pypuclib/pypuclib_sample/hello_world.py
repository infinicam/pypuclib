import cv2 # need to import extra module "pip install opencv-python"
import pypuclib
from pypuclib import CameraFactory, Camera, XferData, Decoder
from pypuclib import Resolution, PUCException, PUC_DATA_MODE

print(pypuclib.__doc__)

# To connect the camera first detected
cam = CameraFactory().create()

# To decode image, get decoder obj from camera
decoder = cam.decoder()

# Set filepath to save image
savePath = "hello_world.bmp"

# Function : Save single image as BMP 
def saveBMP(img):
    cv2.imwrite(savePath, img)
    print("saved a BMP image")

# Explanation
print("press Esc to quit this application ")
print("press 's' to save a BMP image")


while True:
    # Grab the single image data
    xferData = cam.grab()

    # Decode the data can be used as image
    array = decoder.decode(xferData)

    # Show the image
    cv2.imshow("INFINICAM", array)

    key = cv2.waitKey(1)
    if key & 0xFF == ord('s'): # s : save image
        saveBMP(array)
    elif key & 0xFF == 27: # Esc : quit application
        break


# Close live image window
cv2.destroyAllWindows()





