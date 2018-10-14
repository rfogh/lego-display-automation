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

def handler(topic, message):
    if (topic == "event/ferris/activated"):
        client.publish("command/ferris/run", {"direction":0, "duration":10, "pause":5})
    elif (topic == "event/facedetected"):
        circle = random.randint(0,1) == 1
        mode = random.randint(0,55)
        colors = [getRandomColor(), getRandomColor(), getRandomColor()]
        speed = 1000 if circle else 7000
        direction = random.randint(0,2)
        client.publish("command/ferris/setmode", {"circle":circle,"mode":mode,"colors":colors,"speed":speed,"direction":direction})

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

def runFerris() {
    duration = 10
    client.publish("command/ferris/run", {"duration": duration})
    client.publish("command/status/on", {"duration": duration})
}

def subscriptions():
    client.subscribe("event/facedetected")
    client.subscribe("event/ferris/activated")

client = MqttClient(handler, subscriptions)

runFerris()

##client.publish("command/ferris/setmode", {"circle":True,"mode":44,"colors":[255],"speed":1000,"direction":0})
##client.publish("command/ferris/start", {"direction":0})
##time.sleep(5)
##client.publish("command/ferris/stop")
##time.sleep(2)
##client.publish("command/ferris/setmode", {"circle":True,"mode":44,"colors":[65280],"speed":1000,"direction":1})
##client.publish("command/ferris/start", {"direction":1})
##time.sleep(5)
##client.publish("command/ferris/stop")
##client.publish("command/ferris/setmode", {"circle":False,"mode":44,"colors":[255],"speed":10000,"direction":0})

client.loop_forever()
