#!/usr/bin/python3

import paho.mqtt.client as mqtt
import json
import time
import random

class MqttClient:
    
    host = "192.168.1.2"

    def __init__(self, handler, subscriptions):
        self.client = mqtt.Client()
        self.client.connect(self.host)
        self.client.on_message = self.__on_message
        self.client.on_connect = self.__on_connect
        self.handler = handler
        self.on_connect = subscriptions
                
    def __on_message(self, client, userdata, message):
        topic = message.topic
        payload = {}
        if (message.payload):
            payload = json.loads(str(message.payload.decode("utf-8")))
        self.handler(topic, payload)
        
    def __on_connect(self, client, userdata, flags, rc):
        self.on_connect()
                
    def publish(self, topic, message={}):
        jsonMessage = json.dumps(message)
        print("Publish to "+ topic +": "+ jsonMessage)
        self.client.publish(topic, jsonMessage)
        
    def subscribe(self, topic):
        self.client.subscribe(topic)
        
    def loop_forever(self):
        self.client.loop_forever()

def getRandomColor():
    color = 0
    while color == 0:
        color = random.randint(0,1)*0xFF0000 + random.randint(0,1)*0xFF00 + random.randint(0,1)*0xFF
    return color

# Ferris light:
#   command/ferris/setmode {"colors": [array of 3 colors], "mode", "speed", "direction": [0,1,2]}
#   command/ferris/setbrightness {"brightness": [0-255]}

# Ferris motor:
#   command/ferris/run {"duration", "pause"}

# Rollercoaster:
#   command/roller/run {}

# Friends cave
#   command/friends/run {"duration", "pause"}

# Train A/B
#   command/train/run {"direction": [0,1], "duration", "pause", "train": [A,B]"}

# Julemand op/ned
#   sallingaarhus/julemandop
#   sallingaarhus/julemandned

# Gyngestol
#   sallingaarhus/gyngestolgyng

# Status light
#   command/status/on {"duration", "number": [0-6]}
#   command/status/off {"number": [0-6]}
#   command/ferris/setbrightness {"brightness": [0-255]}

def changeFerris():
    circle = random.randint(0,1) == 1
    mode = random.randint(0,55)
    colors = [getRandomColor(), getRandomColor(), getRandomColor()]
    speed = 1000 if circle else 7000
    direction = random.randint(0,2)
    client.publish("command/ferris/setmode", {"circle":circle,"mode":mode,"colors":colors,"speed":speed,"direction":direction})

def runSkorsten():
    duration = 15
    client.publish("sallingaarhus/julemandop", {})
    client.publish("command/status/on", {"number":0})
    time.sleep(duration-2)
    client.publish("sallingaarhus/julemandned", {})
    time.sleep(2)
    client.publish("command/status/off", {"number":0})

def runFerris():
    duration = 10
    client.publish("command/ferris/run", {"duration": duration})
    client.publish("command/status/on", {"duration": duration, "number":1})

def runRocking():
    duration = 10
    client.publish("sallingaarhus/gyngestolgyng", {})
    client.publish("command/status/on", {"duration": duration, "number":2})

def runRoller():
    duration = 10
    client.publish("command/roller/run", {})
    client.publish("command/status/on", {"duration": duration, "number":3})

def runTrainA():
    duration = 10
    client.publish("command/train/run", {"duration": duration, "train":"A"})
    client.publish("command/status/on", {"duration": duration, "number":4})

def runFriends():
    duration = 10
    client.publish("command/friends/run", {"duration": duration, "pause":1})
    client.publish("command/status/on", {"duration": duration, "number":5})

def runTrainB():
    duration = 10
    client.publish("command/train/run", {"duration": duration, "train":"B"})
    client.publish("command/status/on", {"duration": duration, "number":6})

def changeLight():
    changeFerris()
    threading.Timer(20, changeLight).start()

def handler(topic, message):
    if (topic == "event/facedetected"):
        activity = random.randint(0,6)
        if (activity == 0):
            runSkorsten()
        elif (activity == 1):
            runFerris()
        elif (activity == 2):
            runRocking()
        elif (activity == 3):
            runRoller()
        elif (activity == 4):
            runTrainA()
        elif (activity == 5):
            runFriends()
        elif (activity == 6):
            runTrainB()


def subscriptions():
    client.subscribe("event/facedetected")

client = MqttClient(handler, subscriptions)

changeLight()

client.loop_forever()
