// /* Light control for Office cave */

// // #include "MqttClient.h"
// #include <WS2812FX.h>

// #define PIN           D3
// #define NUMPIXELS     300

// WS2812FX pixels = WS2812FX(NUMPIXELS, PIN, NEO_RGB+NEO_KHZ800);

// void setup() {
//   Serial.begin(115200);

//   pixels.init();

//   pixels.setBrightness(40);

//   //setSegment(uint8_t n, uint16_t start, uint16_t stop, uint8_t mode, const uint32_t colors[], uint16_t speed, bool reverse)
//   pixels.setSegment(0, 0, 10, FX_MODE_BLINK, (const uint32_t[]) {0x00FF00, RED}, 1000, false);
//   pixels.setSegment(1, 11, 30, FX_MODE_MERRY_CHRISTMAS, (const uint32_t[]) {BLUE, ORANGE, WHITE}, 10000, false);

//   pixels.start();
// }

// void loop() {
//   pixels.service();
// }
