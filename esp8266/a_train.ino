// /* MOTOR CONTROL FOR TRAINS */

// #include "MqttClient.h"
// #include <Ticker.h>

// #define PWMA         D1
// #define DA           D3
// #define PWMB         D2
// #define DB           D4

// #define MAX_POWER_A  750
// #define MAX_POWER_B  800

// void handler(String topic, JsonObject& message);

// MqttClient client(handler);
// Ticker aTicker;
// Ticker bTicker;

// void startA(unsigned short direction, unsigned short duration = 0) {
//     if (direction == 0) {
//         digitalWrite(DA, LOW);
//     } else {
//         digitalWrite(DA, HIGH);
//     }

//     StaticJsonBuffer<200> jsonBuffer;
//     JsonObject& event = jsonBuffer.createObject();
//     event["duration"] = duration;
//     event["train"] = "A";
//     client.publish("event/train/started", event);

//     for (int i=600; i<MAX_POWER_A; i=i+20) {
//         analogWrite(PWMA, i);
//         delay(50);
//     }
//     analogWrite(PWMA, MAX_POWER_A);
// }

// void startB(unsigned short direction, unsigned short duration = 0) {
//     if (direction == 0) {
//         digitalWrite(DB, LOW);
//     } else {
//         digitalWrite(DB, HIGH);
//     }

//     StaticJsonBuffer<200> jsonBuffer;
//     JsonObject& event = jsonBuffer.createObject();
//     event["duration"] = duration;
//     event["train"] = "B";
//     client.publish("event/train/started", event);

//     for (int i=600; i<MAX_POWER_B; i=i+20) {
//         analogWrite(PWMB, i);
//         delay(50);
//     }
//     analogWrite(PWMB, MAX_POWER_B);
// }

// void stopA(unsigned short pause = 0) {
//     for (int i=MAX_POWER_A; i>600; i=i-20) {
//         analogWrite(PWMA, i);
//         delay(50);
//     }
//     analogWrite(PWMA, 0);

//     StaticJsonBuffer<200> jsonBuffer;
//     JsonObject& event = jsonBuffer.createObject();
//     event["pause"] = pause;
//     event["train"] = "A";
//     client.publish("event/train/stopped", event);
// }

// void stopB(unsigned short pause = 0) {
//     for (int i=MAX_POWER_B; i>600; i=i-20) {
//         analogWrite(PWMB, i);
//         delay(50);
//     }
//     analogWrite(PWMB, 0);

//     StaticJsonBuffer<200> jsonBuffer;
//     JsonObject& event = jsonBuffer.createObject();
//     event["pause"] = pause;
//     event["train"] = "B";
//     client.publish("event/train/stopped", event);
// }

// void handler(String topic, JsonObject& message) {
//     if (topic == "command/train/run") {
//         unsigned short direction = message["direction"];
//         unsigned short duration = message["duration"];
//         unsigned short pause = message["pause"];
//         String train = message["train"];

//         if (train == "A") {
//             aTicker.once(duration, stopA, pause);
//             startA(direction, duration);
//         }

//         if (train == "B") {
//             bTicker.once(duration, stopB, pause);
//             startB(direction, duration);
//         }
//     }
//     else if (topic == "command/train/start") {
//         unsigned short direction = message["direction"];
//         String train = message["train"];

//         if (train == "A") {
//             startA(direction);
//         }

//         if (train == "B") {
//             startB(direction);
//         }
//     }
//     else if (topic == "command/train/stop") {
//         String train = message["train"];

//         if (train == "A") {
//             stopA();
//         }

//         if (train == "B") {
//             stopB();
//         }
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
//     client.subscribe("command/train/#");
// }

// void loop() {
//     client.loop();
// }
