// /* MOTOR AND LIGHT CONTROL FOR FRIENDS CAVE */

// #include "MqttClient.h"
// #include <Ticker.h>

// #define PWMA         D1
// #define DA           D3
// #define PWMB         D2
// #define DB           D4
// #define CAVE_LIGHT   D8
// #define CAVE_BLOW    D5

// void handler(String topic, JsonObject& message);

// MqttClient client(handler);
// Ticker ticker;

// void start(unsigned short duration = 0) {
//     digitalWrite(DA, 1);
//     analogWrite(PWMA, PWMRANGE);
//     delay(duration);
//     digitalWrite(DA, 0);
// }

// void stop() {
//     analogWrite(PWMA, 0);
// }

// void handler(String topic, JsonObject& message) {
//     if (topic == "command/friends/run") {
//         unsigned short duration = message["duration"];

//         ticker.once(duration+duration, stop);
//         start(duration);
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

//     client.begin();
//     client.subscribe("command/friends/#");
// }

// void loop() {
//     client.loop();
// }
