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
bool listeningForTouchInput = false;

void listenForInput() {
    ticker.detach();

    pixels.setColor(BLUE);
    pixels.setMode(FX_MODE_STATIC);

    listeningForTouchInput = true;
}

void handler(char* topic, JsonObject& message) {
    if (strcmp(topic, "event/ferris/started") == 0) {
        ticker.detach();

        unsigned short duration = message["duration"];
        pixels.setColor(GREEN);
        pixels.setMode(FX_MODE_COLOR_WIPE_INV);
        pixels.setSpeed(duration*2000);
    }
    else if (strcmp(topic, "event/ferris/stopped") == 0) {
        unsigned short pause = message["pause"];
        pixels.setColor(BLUE);
        pixels.setMode(FX_MODE_COLOR_WIPE);
        pixels.setSpeed(pause*2000);

        ticker.attach(pause, listenForInput);
    }
    else if (strcmp(topic, "command/touch/setbrightness") == 0) {
        pixels.setBrightness(message["brightness"]);
        
        client->publish("event/touch/brightnessset");
    }
}

void setup() {
    Serial.begin(115200);

    pinMode(TOUCHPIN, INPUT);

    pixels.init();
    pixels.setBrightness(10);
    pixels.setSpeed(1200);
    listenForInput();
    pixels.start();

    client = new MqttClient("ferris_touch", handler);
    client->subscribe("event/ferris/#");
    client->subscribe("command/touch/#");
}

void readTouch() {
    if (!listeningForTouchInput) {
        return;
    }

    int touched = digitalRead(TOUCHPIN);
    if(touched == HIGH) {
        listeningForTouchInput = false;
        pixels.setColor(GREEN);
        pixels.setMode(FX_MODE_STATIC);
        ticker.attach(WAIT_FOR_START_MESSAGE_TIMEOUT, listenForInput);
        client->publish("event/ferris/activated");
    }
}

void loop() {
    readTouch();

    pixels.service();
    client->loop();
}
