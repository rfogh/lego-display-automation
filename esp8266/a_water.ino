// /* Light control for Water */

// #include <WS2812FX.h>
// #include <Ticker.h>

// #define PIN           D6
// #define NUMPIXELS     6

// WS2812FX pixels = WS2812FX(NUMPIXELS, PIN, NEO_GRB+NEO_KHZ800);

// void setup() {
//   Serial.begin(115200);

//   pixels.init();
//   pixels.setBrightness(100);
//   pixels.setSpeed(500);
//   pixels.setColor(WHITE);
//   pixels.setMode(FX_MODE_FIRE_FLICKER);
//   pixels.start();
// }

// void loop() {
//   pixels.service();
// }
