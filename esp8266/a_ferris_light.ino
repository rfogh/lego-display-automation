// /* Light control for Ferris wheel */

// #include "MqttClient.h"
// #include <WS2812FX.h>

// #define PIN           D6
// #define NUMSTRIP      12
// #define NUMPIXELS     8

// WS2812FX pixels = WS2812FX(NUMSTRIP*NUMPIXELS, PIN, NEO_GRB+NEO_KHZ800);
// MqttClient *client;
  
// void handler(char* topic, JsonObject& message) {
//   if (strcmp(topic, "command/ferris/setmode") == 0) {
//     pixels.resetSegments();

//     unsigned int colors[3];
//     message["colors"].as<JsonArray>().copyTo(colors);

//     unsigned short mode = message["mode"];
//     unsigned short speed = message["speed"];
//     unsigned short direction = message["direction"];

//     if (message["circle"]) {
//       for (int i=0; i<NUMSTRIP; i++) {
//         pixels.setSegment(i, i*NUMPIXELS, (i+1)*NUMPIXELS-1, mode, colors, speed, i%2==direction);
//       }
//     }
//     else {
//       pixels.setSegment(0, 0, NUMSTRIP*NUMPIXELS-1, mode, colors, speed, direction==1);
//     }

//     client->publish("event/ferris/modeset");
//   }
//   else if (strcmp(topic, "command/ferris/setbrightness") == 0) {
//     pixels.setBrightness(message["brightness"]);

//     client->publish("event/ferris/brightnessset");
//   }
// }

// void setup() {
//   Serial.begin(115200);

//   pixels.init();
//   pixels.setBrightness(40);
//   pixels.setSpeed(1000);
//   pixels.setColor(GREEN);
//   pixels.setMode(FX_MODE_STATIC);
//   pixels.start();

//   client = new MqttClient(handler);
//   client->subscribe("command/ferris/#");
// }

// void loop() {
//   pixels.service();
//   client->loop();
// }
