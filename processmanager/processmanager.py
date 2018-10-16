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

def julemandned():
    client.publish("sallingaarhus/julemandned",{})

def runSkorsten():
    duration = 20
    client.publish("sallingaarhus/julemandop", {})
    client.publish("command/status/on", {"duration":duration, "number":0})
    threading.Timer(17.0, julemandned)

def runFerris():
    duration = 20
    client.publish("command/ferris/run", {"duration": duration})
    client.publish("command/status/on", {"duration": duration, "number":1})

def runRocking():
    duration = 10
    client.publish("sallingaarhus/gyngestolgyng", {})
    client.publish("command/status/on", {"duration": duration, "number":2})

def runRoller():
    duration = 20
    client.publish("command/roller/run", {})
    client.publish("command/status/on", {"duration": duration, "number":3})

def runTrainA():
    duration = 20
    client.publish("command/train/run", {"duration": duration, "train":"A"})
    client.publish("command/status/on", {"duration": duration, "number":4})

def runFriends():
    duration = 20
    client.publish("command/friends/run", {"duration": duration})
    client.publish("command/status/on", {"duration": duration, "number":5})

def runTrainB():
    duration = 20
    client.publish("command/train/run", {"duration": duration, "train":"B"})
    client.publish("command/status/on", {"duration": duration, "number":6})

timerToActivateIfNoActivity = threading.Timer(20.0, runFerris)

def activate(activity):
    global timerToActivateIfNoActivity
    if (timerToActivateIfNoActivity.is_alive()):
        timerToActivateIfNoActivity.cancel()
    timerToActivateIfNoActivity = threading.Timer(900.0, activate, (random.randint(0,6)))
    timerToActivateIfNoActivity.start()

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

timerToActivateIfNoActivity = threading.Timer(900.0, activate, (random.randint(0,6)))
timerToActivateIfNoActivity.start()

def handler(topic, message):
    if (topic == "event/facedetected"):
        activity = random.randint(0,6)
        activate(activity)
    elif (topic == "command/activate"):
        activate(message["number"])
    # elif (topic == "command/activate/0"):
    #     activate(0)
    # elif (topic == "command/activate/1"):
    #     activate(1)
    # elif (topic == "command/activate/2"):
    #     activate(2)
    # elif (topic == "command/activate/3"):
    #     activate(3)
    # elif (topic == "command/activate/4"):
    #     activate(4)
    # elif (topic == "command/activate/5"):
    #     activate(5)
    # elif (topic == "command/activate/6"):
    #     activate(6)


def subscriptions():
    client.subscribe("event/facedetected")
    client.subscribe("command/activate")

client = MqttClient(handler, subscriptions)
client.loop_forever()
