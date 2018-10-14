// /* Status control */

// #include "MqttClient.h"
// #include <WS2812FX.h>
// #include <Ticker.h>

// #define PIXELPIN                        D2
// #define NUMPIXELRING                    12
// #define NUMRINGS                        7
// #define WAIT_FOR_START_MESSAGE_TIMEOUT  5

// void handler(String topic, JsonObject& message);

// WS2812FX pixels(NUMPIXELRING*NUMRINGS, PIXELPIN, NEO_GRB+NEO_KHZ800);
// MqttClient client(handler);
// Ticker stopTicker;

// void stop(unsigned short numRing) {
//     pixels.setSegment(numRing, numRing*NUMPIXELRING, (numRing+1)*NUMPIXELRING-1, FX_MODE_STATIC, BLACK, 3000, false);
// }

// void setup() {
//     Serial.begin(115200);

//     pixels.init();
//     pixels.setBrightness(10);
//     for (unsigned short numRing = 0; numRing < NUMRINGS; numRing++) {
//         pixels.setSegment(numRing, numRing*NUMPIXELRING, (numRing+1)*NUMPIXELRING-1, FX_MODE_STATIC, BLACK, 1000, false);
//     }
//     pixels.start();

//     client.begin();
//     client.subscribe("command/status/#");
// }

// void loop() {
//     pixels.service();
//     client.loop();
// }

// void handler(String topic, JsonObject& message) {
//     if (topic == "command/status/on") {
//         unsigned short duration = message["duration"];
//         unsigned short numRing = message["number"];
//         if (duration > 0) {
//             pixels.setSegment(numRing, numRing*NUMPIXELRING, (numRing+1)*NUMPIXELRING-1, FX_MODE_COLOR_WIPE_INV, GREEN, duration*2000, false);
//             stopTicker.once(duration, stop, numRing);
//         } else {
//             pixels.setSegment(numRing, numRing*NUMPIXELRING, (numRing+1)*NUMPIXELRING-1, FX_MODE_COMET, GREEN, 1500, false);
//         }

//         client.publish("event/status/started");
//     }
//     else if (topic == "command/status/off") {
//         unsigned short numRing = message["number"];
//         stop(numRing);
//         client.publish("event/status/stopped");
//     }
//     else if (topic == "command/status/setbrightness") {
//         pixels.setBrightness(message["brightness"]);
//         client.publish("event/status/brightnessset");
//     }
// }
