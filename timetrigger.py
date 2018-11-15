#!/usr/bin/python3

#MQTT
import paho.mqtt.client as mqtt
import time

client = mqtt.Client()
client.connect("192.168.1.2")

client.loop_start()

while (True):
    client.publish("event/facedetected", 0)

    hour = time.localtime().tm_hour
    if (hour in range(8,22)):
        time.sleep(60)
    else
        time.sleep(900)

        
client.loop_stop()