// /* MOTOR CONTROL FOR ROLLER COASTER */

// #include "MqttClient.h"
// #include <Ticker.h>

// #define PWMA         D1
// #define DA           D3
// #define PWMB         D2
// #define DB           D4

// void handler(String topic, JsonObject& message);

// MqttClient client(handler);
// Ticker topStartTicker;
// Ticker bottomStopTicker;
// Ticker topStopTicker;

// void startBottom() {
//     for (int i=600; i<PWMRANGE; i=i+20) {
//         analogWrite(PWMA, i);
//         delay(50);
//     }
//     analogWrite(PWMA, PWMRANGE);
// }

// void startTop() {
//     topStartTicker.detach();

//     for (int i=600; i<PWMRANGE; i=i+20) {
//         analogWrite(PWMB, i);
//         delay(50);
//     }
//     analogWrite(PWMB, PWMRANGE);
// }

// void stopBottom() {
//     bottomStopTicker.detach();

//     for (int i=PWMRANGE; i>600; i=i-20) {
//         analogWrite(PWMA, i);
//         delay(50);
//     }
//     analogWrite(PWMA, 0);
// }

// void stopTop() {
//     topStopTicker.detach();

//     for (int i=PWMRANGE; i>600; i=i-20) {
//         analogWrite(PWMB, i);
//         delay(50);
//     }
//     analogWrite(PWMB, 0);
// }

// void run(unsigned short pause = 0) {
//     StaticJsonBuffer<200> jsonBuffer;
//     JsonObject& startEvent = jsonBuffer.createObject();
//     startEvent["duration"] = 20;
//     client.publish("event/roller/started", startEvent);

//     startBottom();
//     topStartTicker.attach(4, startTop);
//     bottomStopTicker.attach(9, stopBottom);
//     topStopTicker.attach(10, stopTop);

//     JsonObject& stopEvent = jsonBuffer.createObject();
//     stopEvent["pause"] = pause;
//     client.publish("event/roller/stopped", stopEvent);
// }


// void handler(String topic, JsonObject& message) {
//     if (topic == "command/roller/run") {
//         unsigned short pause = message["pause"];

//         run(pause);
//     }
// }

// void setup() {
//     Serial.begin(115200);
//     Serial.println("Setup roller coaster motor controller");

//     pinMode(PWMA, OUTPUT);
//     pinMode(DA, OUTPUT);
//     pinMode(PWMB, OUTPUT);
//     pinMode(DB, OUTPUT);

//     analogWrite(PWMA, 0);
//     analogWrite(PWMB, 0);

//     client.begin();
//     client.subscribe("command/roller/#");
// }

// void loop() {
//     client.loop();
// }
