// /* MOTOR CONTROL FOR FERRIS WHEEL */

// #include "MqttClient.h"
// #include <Ticker.h>

// #define PWMA         D1
// #define DA           D3
// #define PWMB         D2
// #define DB           D4

// void handler(String topic, JsonObject& message);

// MqttClient client(handler);
// Ticker ticker;

// void start(unsigned short direction, unsigned short duration = 0) {
//     if (direction == 0) {
//         digitalWrite(DA, LOW);
//     } else {
//         digitalWrite(DA, HIGH);
//     }

//     // StaticJsonBuffer<200> jsonBuffer;
//     // JsonObject& event = jsonBuffer.createObject();
//     // event["duration"] = duration;
//     // client.publish("event/ferris/started", event);

//     for (int i=600; i<PWMRANGE; i=i+20) {
//         analogWrite(PWMA, i);
//         delay(50);
//     }
//     analogWrite(PWMA, PWMRANGE);
// }

// void stop(unsigned short pause = 0) {
//     for (int i=PWMRANGE; i>600; i=i-20) {
//         analogWrite(PWMA, i);
//         delay(50);
//     }
//     analogWrite(PWMA, 0);

//     // StaticJsonBuffer<200> jsonBuffer;
//     // JsonObject& event = jsonBuffer.createObject();
//     // event["pause"] = pause;
//     // client->publish("event/ferris/stopped", event);
// }

// void handler(String topic, JsonObject& message) {
//     if (topic == "command/ferris/run") {
//         unsigned short direction = message["direction"];
//         unsigned short duration = message["duration"];
//         unsigned short pause = message["pause"];

//         ticker.once(duration, stop, pause);

//         start(direction, duration);
//     }
//     else if (topic == "command/ferris/start") {
//         unsigned short direction = message["direction"];
//         start(direction);
//     }
//     else if (topic == "command/ferris/stop") {
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

//     client.begin();
//     client.subscribe("command/ferris/#");
// }

// void loop() {
//     client.loop();
// }
