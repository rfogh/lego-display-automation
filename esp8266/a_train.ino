// /* MOTOR CONTROL FOR TRAIN */

// #include "MqttClient.h"

// #define PWMA         D1
// #define DA           D3
// #define PWMB         D2
// #define DB           D4

// #define SENSOR       D7

// MqttClient *client = NULL;
// unsigned short speed = 0;
// unsigned short sensorCount = 0;

// void setup() {
//   Serial.begin(115200);
  
//   pinMode(PWMA, OUTPUT);
//   pinMode(DA, OUTPUT);
//   pinMode(PWMB, OUTPUT);
//   pinMode(DB, OUTPUT);

//   pinMode(SENSOR, INPUT);

//   client = new MqttClient("train");
//   client->initialize(handler);
//   client->subscribe("command/train/#");
// }

// void loop() {
//   client->loop();

//   int sensorReading = digitalRead(SENSOR);
//   if (sensorReading == LOW) {
//     sensorCount++;

//     if(sensorCount == 1) {
//       Serial.println("Slowing down...");
//       slowDown();
//     }
//     if (sensorCount == 2) {
//       stop();
//       Serial.println("Stopped");
//     }
//     delay(1000);
//   }
// }

// void handler(char* topic, JsonObject& message) {
//   if (strcmp(topic, "command/train/start") == 0) {
//     unsigned short direction = message["direction"];
//     unsigned short speed = message["speed"];

//     if (speed < 500) {
//       speed = 500;
//     }
//     if (speed > PWMRANGE) {
//       speed = PWMRANGE;
//     }

//     if (direction == 0) {
//       analogWrite(DA, LOW);
//     }
//     else {
//       analogWrite(DA, HIGH);
//     }

//     for (int i=400; i<speed; i=i+20) {
//       analogWrite(PWMA, i);
//       delay(50);
//     }
//     analogWrite(PWMA, speed);

//     sensorCount = 0;
//   }
//   if (strcmp(topic, "command/train/stop") == 0) {
//     slowDown();
//     stop();
//   }
// }

// void slowDown() {
//     for (int i=speed; i>100; i=i-20) {
//       analogWrite(PWMA, i);
//       delay(50);
//     }
// }

// void stop() {
//     analogWrite(PWMA, 0);
// }
