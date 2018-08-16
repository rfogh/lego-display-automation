// /* MOTOR CONTROL FOR FERRIS WHEEL */

// #include "MqttClient.h"
// #include <Ticker.h>

// #define PWMA         D1
// #define DA           D3
// #define PWMB         D2
// #define DB           D4

// MqttClient *client = NULL;
// Ticker ticker;

// void start(unsigned short direction, unsigned short duration = 0) {
//     if (direction == 0) {
//         analogWrite(DA, LOW);
//     } else {
//         analogWrite(DA, HIGH);
//     }

//     StaticJsonBuffer<200> jsonBuffer;
//     JsonObject& event = jsonBuffer.createObject();
//     event["duration"] = duration;
//     client->publish("event/ferris/started", event);

//     for (int i=600; i<PWMRANGE; i=i+20) {
//         analogWrite(PWMA, i);
//         delay(50);
//     }
//     analogWrite(PWMA, PWMRANGE);
// }

// void stop(unsigned short pause = 0) {
//     ticker.detach();
//     for (int i=PWMRANGE; i>600; i=i-20) {
//         analogWrite(PWMA, i);
//         delay(50);
//     }
//     analogWrite(PWMA, 0);

//     StaticJsonBuffer<200> jsonBuffer;
//     JsonObject& event = jsonBuffer.createObject();
//     event["pause"] = pause;
//     client->publish("event/ferris/stopped", event);
// }

// void handler(char* topic, JsonObject& message) {
//     if (strcmp(topic, "command/ferris/run") == 0) {
//         unsigned short direction = message["direction"];
//         unsigned short duration = message["duration"];
//         unsigned short pause = message["pause"];

//         ticker.attach(duration, stop, pause);

//         start(direction, duration);
//     }
//     if (strcmp(topic, "command/ferris/start") == 0) {
//         unsigned short direction = message["direction"];
//         start(direction);
//     }
//     if (strcmp(topic, "command/ferris/stop") == 0) {
//         stop();
//     }
// }

// void setup() {
//     Serial.begin(115200);

//     pinMode(PWMA, OUTPUT);
//     pinMode(DA, OUTPUT);
//     pinMode(PWMB, OUTPUT);
//     pinMode(DB, OUTPUT);

//     analogWrite(PWMA, 0);
//     analogWrite(PWMB, 0);

//     client = new MqttClient(handler);
//     client->subscribe("command/ferris/#");
// }

// void loop() {
//     client->loop();
// }
