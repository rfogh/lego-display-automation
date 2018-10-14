// /* Light control for Office cave */

// #include <WS2812FX.h>
// #include <Ticker.h>

// #define PIN           D2
// #define NUMPIXELS     16

// WS2812FX pixels = WS2812FX(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
// Ticker changeTicker;

// void change() {
//   pixels.resetSegments();
//   int duration = 10;

//   switch(random(6)) {
//     case 0:
//       // setSegment(uint8_t n, uint16_t start, uint16_t stop, uint8_t mode, const uint32_t colors[], uint16_t speed, bool reverse)
//       // Ticket counter
//       pixels.setSegment(0, 0, 3, FX_MODE_STATIC, (const uint32_t[]) {0xFFFF66, WHITE, YELLOW}, 2000, false);
//       //WC
//       pixels.setSegment(1, 4, 4, FX_MODE_BLINK, (const uint32_t[]) {0xFFFFCC, 0xFFFF33}, 50, false);
//       //Office
//       pixels.setSegment(2, 6, 6, FX_MODE_STATIC, (const uint32_t[]) {0xFFFF99, YELLOW, WHITE}, 10000, false);
//       pixels.setSegment(6, 14, 14, FX_MODE_STATIC, (const uint32_t[]) {0xFFFF66, WHITE, YELLOW}, 3000, false);
//       //Dining room
//       pixels.setSegment(3, 7, 7, FX_MODE_STATIC, (const uint32_t[]) {YELLOW, ORANGE, WHITE}, 1000, false);
//       pixels.setSegment(5, 13, 13, FX_MODE_STATIC, (const uint32_t[]) {0xFFCCCC, YELLOW, WHITE}, 2000, false);
//       //Waiting hall
//       pixels.setSegment(4, 8, 12, FX_MODE_STATIC, (const uint32_t[]) {0xFFFF99, YELLOW, WHITE}, 1000, false);
//       duration = 30;
//       break;
//     case 1:
//       pixels.setSegment(0, 0, 14, FX_MODE_RAINBOW_CYCLE, WHITE, 200, false);
//       break;
//     case 2:
//       pixels.setSegment(0, 0, 14, FX_MODE_COMET, RED, 2000, false);
//       duration = 4;
//       break;
//     case 3:
//       pixels.setSegment(0, 0, 14, FX_MODE_TWINKLE, 0xFFFF99, 2000, false);
//       break;
//     case 4:
//       //Office
//       pixels.setSegment(0, 6, 6, FX_MODE_STATIC, (const uint32_t[]) {0xFFFF99, YELLOW, WHITE}, 10000, false);
//       pixels.setSegment(1, 14, 14, FX_MODE_STATIC, (const uint32_t[]) {GREEN, WHITE, YELLOW}, 3000, false);
//       pixels.setSegment(2, 0, 5, FX_MODE_STATIC, BLACK, 3000, false);
//       pixels.setSegment(3, 7, 13, FX_MODE_STATIC, BLACK, 3000, false);
//       break;
//     case 5:
//       pixels.setSegment(0, 0, 14, FX_MODE_SPARKLE, CYAN, 2000, false);
//       duration = 4;
//       break;
//   }

//   changeTicker.once(duration, change);
// }

// void setup() {
//   Serial.begin(115200);

//   randomSeed(analogRead(0));

//   pixels.init();
//   pixels.setBrightness(255);
//   change();
//   pixels.start();
// }

// void loop() {
//   pixels.service();
// }
