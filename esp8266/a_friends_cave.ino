// /* MOTOR AND LIGHT CONTROL FOR FRIENDS CAVE */

// #include "MqttClient.h"
// #include <WS2812FX.h>
// #include <Ticker.h>

// #define PWMA         D1
// #define DA           D3
// #define PWMB         D2
// #define DB           D4
// #define CAVE_LIGHT   D8
// #define CAVE_BLOW    D5

// MqttClient *client = NULL;
// Ticker ticker;
// WS2812FX pixels = WS2812FX(1, CAVE_BLOW, NEO_GRB+NEO_KHZ800);

// void start(unsigned short direction, unsigned short duration = 0) {
//     StaticJsonBuffer<200> jsonBuffer;
//     JsonObject& event = jsonBuffer.createObject();
//     event["duration"] = duration;
//     client->publish("event/friends/started", event);

//     analogWrite(PWMA, PWMRANGE);
//     digitalWrite(DA, HIGH);
//     delay(duration/2);
//     digitalWrite(DA, LOW);
// }

// void stop(unsigned short pause = 0) {
//     ticker.detach();
//     analogWrite(PWMA, 0);

//     StaticJsonBuffer<200> jsonBuffer;
//     JsonObject& event = jsonBuffer.createObject();
//     event["pause"] = pause;
//     client->publish("event/friends/stopped", event);
// }

// void handler(String topic, JsonObject& message) {
//     if (topic == "command/friends/run") {
//         unsigned short direction = message["direction"];
//         unsigned short duration = message["duration"];
//         unsigned short pause = message["pause"];

//         ticker.attach(duration, stop, pause);

//         start(direction, duration);
//     }
// }

// void setup() {
//     Serial.begin(115200);

//     pinMode(PWMA, OUTPUT);
//     pinMode(DA, OUTPUT);
//     pinMode(PWMB, OUTPUT);
//     pinMode(DB, OUTPUT);
//     pinMode(CAVE_LIGHT, OUTPUT);
//     pinMode(CAVE_BLOW, OUTPUT);

//     analogWrite(PWMA, 0);
//     analogWrite(PWMB, 0);

//     digitalWrite(CAVE_LIGHT, HIGH);

//     pixels.init();
//     pixels.setBrightness(100);
//     pixels.setSpeed(1000);
//     pixels.setColor(WHITE);
//     pixels.setMode(FX_MODE_BLINK);
//     pixels.start();

//     client = new MqttClient(handler);
//     client->subscribe("command/friends/#");
// }

// void loop() {
//     pixels.service();
//     client->loop();
// }
