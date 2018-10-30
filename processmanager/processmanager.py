#!/usr/bin/python3

import paho.mqtt.client as mqtt
import json
import time
import random
import threading

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

# Ferris light:
#   command/ferris/setmode {"colors": [array of 3 colors], "mode", "speed", "direction": [0,1,2]}
#   command/ferris/setbrightness {"brightness": [0-255]}

# Ferris motor:
#   command/ferris/run {"duration", "pause"}

# Rollercoaster:
#   command/roller/run {}

# Friends cave
#   command/friends/run {"duration"}

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

def runSkorsten():
    duration = 12
    client.publish("command/status/on", {"duration":duration, "number":0})
    time.sleep(1)
    client.publish("sallingaarhus/julemandop", {})
    client.publish("sallingaarhus/julemandned", {})
    return duration

def runFerris():
    duration = 20
    client.publish("command/status/on", {"duration": duration, "number":1})
    time.sleep(1)
    client.publish("command/ferris/run", {"duration": duration})
    return duration

def runRocking():
    duration = 30
    client.publish("command/status/on", {"duration": duration, "number":2})
    time.sleep(1)
    client.publish("sallingaarhus/gyngestolgyng", {})
    return duration

def runRoller():
    duration = 13
    client.publish("command/status/on", {"duration": duration, "number":3})
    time.sleep(1)
    client.publish("command/roller/run", {})
    return duration

def runTrainA():
    duration = 20
    client.publish("command/status/on", {"duration": duration, "number":4})
    time.sleep(1)
    client.publish("command/train/run", {"duration": duration, "train":"A"})
    return duration

def runFriends():
    duration = 20
    # client.publish("command/status/on", {"duration": duration, "number":5})
    time.sleep(1)
    # client.publish("command/friends/run", {"duration": duration})
    return 0

def runTrainB():
    duration = 20
    client.publish("command/status/on", {"duration": duration, "number":6})
    time.sleep(1)
    client.publish("command/train/run", {"duration": duration, "train":"B"})
    return duration

nextRunningTime = time.time()


def activate(activity):
    global nextRunningTime
    if (time.time() < nextRunningTime):
        return

    duration = 0
    if (activity == 0):
        duration = runSkorsten()
    elif (activity == 1):
        duration = runFerris()
    elif (activity == 2):
        duration = runRocking()
    elif (activity == 3):
        duration = runRoller()
    elif (activity == 4):
        duration = runTrainA()
    elif (activity == 5):
        duration = runFriends()
    elif (activity == 6):
        duration = runTrainB()

    nextRunningTime = time.time() + duration

def handler(topic, message):
    if (topic == "event/facedetected"):
        activity = random.randint(0,6)
        activate(activity)
    elif (topic == "command/activate"):
        activate(message["number"])


def subscriptions():
    client.subscribe("event/facedetected")
    client.subscribe("command/activate")

client = MqttClient(handler, subscriptions)
client.loop_forever()
