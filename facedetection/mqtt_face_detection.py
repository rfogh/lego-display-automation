#!/usr/bin/python3

#MQTT
import paho.mqtt.client as mqtt
#OpenCV
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
import sys
import imutils
import os

# Create the haar cascade
cascPath = os.path.join(os.path.dirname(os.path.realpath(__file__)), "haarcascade_frontalface_default.xml")
faceCascade = cv2.CascadeClassifier(cascPath)

# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (320, 240)
camera.framerate = 4
rawCapture = PiRGBArray(camera, size=(320, 240))

client = mqtt.Client()
client.connect("192.168.1.2")

client.loop_start()

# capture frames from the camera
for frame in camera.capture_continuous(rawCapture, format="bgr"):
	# grab the raw NumPy array representing the image, then initialize the timestamp
	# and occupied/unoccupied text
    image = frame.array
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    
    # Detect faces in the image
    faces = faceCascade.detectMultiScale(
    gray,
    scaleFactor=1.1,
    minNeighbors=5,
    minSize=(20, 20),
    flags = cv2.CASCADE_SCALE_IMAGE
    )
    
    for (x, y, w, h) in faces:
        cv2.rectangle(image, (x, y), (x+w, y+h), (0, 255, 0), 2)
    
    if len(faces) > 0:
        client.publish("event/facedetected", len(faces))
        time.sleep(5)
    
    # clear the stream in preparation for the next frame
    rawCapture.truncate(0)
    
    time.sleep(1)
        
client.loop_stop()