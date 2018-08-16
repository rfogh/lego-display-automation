/* Touch control for activation on window */

#include "MqttClient.h"
#include <WS2812FX.h>
#include <Ticker.h>

#define TOUCHPIN                        D5
#define PIXELPIN                        D3
#define NUMPIXELRING                    12
#define WAIT_FOR_START_MESSAGE_TIMEOUT  5

WS2812FX pixels = WS2812FX(NUMPIXELRING, PIXELPIN, NEO_GRB+NEO_KHZ800);
MqttClient *client;
Ticker ticker;
bool listeningForTouch = false;

void listenForTouch() {
    ticker.detach();

    pixels.setColor(BLUE);
    pixels.setMode(FX_MODE_STATIC);

    client->publish("event/touch/activated");

    listeningForTouch = true;
}

void handler(String topic, JsonObject& message) {
    if (topic == "command/touch/run") {
        ticker.detach();

        unsigned short duration = message["duration"];
        if (duration > 0) {
            pixels.setColor(GREEN);
            pixels.setMode(FX_MODE_COLOR_WIPE_INV);
            pixels.setSpeed(duration*2000);
        } else {
            pixels.setColor(GREEN);
            pixels.setMode(FX_MODE_COMET);
            pixels.setSpeed(3000);
        }

        client->publish("event/touch/runstarted");
    }
    else if (topic == "command/touch/pause") {
        unsigned short duration = message["duration"];

        if (duration > 0) {
            pixels.setColor(BLUE);
            pixels.setMode(FX_MODE_COLOR_WIPE);
            pixels.setSpeed(duration*2000);
            ticker.attach(duration, listenForTouch);
    
            client->publish("event/touch/paused");
        }
        else {
            listenForTouch();
        }
    }
    else if (topic == "command/touch/setbrightness") {
        pixels.setBrightness(message["brightness"]);
        client->publish("event/touch/brightnessset");
    }
}

void readTouch() {
    if (!listeningForTouch) {
        return;
    }

    int touched = digitalRead(TOUCHPIN);
    if(touched == HIGH) {
        listeningForTouch = false;
        pixels.setColor(GREEN);
        pixels.setMode(FX_MODE_STATIC);
        ticker.attach(WAIT_FOR_START_MESSAGE_TIMEOUT, listenForTouch);

        StaticJsonBuffer<40> jsonBuffer;
        JsonObject& event = jsonBuffer.createObject();
        event["clientid"] = client->getClientId();

        client->publish("event/touch/touched", event);
    }
}

void setup() {
    Serial.begin(115200);

    pinMode(TOUCHPIN, INPUT);

    pixels.init();
    pixels.setBrightness(10);
    pixels.setSpeed(1200);
    listenForTouch();
    pixels.start();

    client = new MqttClient(handler);
    client->subscribe("command/touch/#");
}

void loop() {
    readTouch();

    pixels.service();
    client->loop();
}
