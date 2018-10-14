// #include <WS2812FX.h>
// #include <Ticker.h>

// #define PWMA         D1
// #define DA           D3
// #define PWMB         D2
// #define DB           D4

// #define PIN           D5
// #define NUMPIXELS     4

// WS2812FX pixels = WS2812FX(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
// Ticker changeTicker;

// Ticker AStartTicker;
// Ticker AReverseTicker;
// Ticker AStopTicker;
// Ticker BStartTicker;
// Ticker BStopTicker;

// void stopA() {
//     Serial.println("StopA");
//     for (int i=PWMRANGE; i>600; i=i-20) {
//         analogWrite(PWMA, i);
//         delay(50);
//     }
//     analogWrite(PWMA, 0);
// }

// void reverseA() {
//     Serial.println("ReverseA");
//     digitalWrite(DA, HIGH);
//     for (int i=600; i<PWMRANGE; i=i+20) {
//         analogWrite(PWMA, i);
//         delay(50);
//     }
//     analogWrite(PWMA, PWMRANGE);
//     AStopTicker.once(10, stopA);
// }

// void startA() {
//     Serial.println("StartA");
//     digitalWrite(DA, LOW);
//     for (int i=600; i<PWMRANGE; i=i+20) {
//         analogWrite(PWMA, i);
//         delay(50);
//     }
//     analogWrite(PWMA, PWMRANGE);
//     AReverseTicker.once(10, reverseA);
// }

// void stopB() {
//     Serial.println("StopB");
//     for (int i=PWMRANGE; i>600; i=i-20) {
//         analogWrite(PWMB, i);
//         delay(50);
//     }
//     analogWrite(PWMB, 0);
// }

// void startB() {
//     Serial.println("StartB");
//     for (int i=600; i<PWMRANGE; i=i+20) {
//         analogWrite(PWMB, i);
//         delay(50);
//     }
//     analogWrite(PWMB, PWMRANGE);
//     BStopTicker.once(5, stopB);
// }

// void setup() {
//   Serial.begin(115200);
//   Serial.println("Starting");

//   AStartTicker.attach(23, startA);
// //   AStartTicker.attach(83, startA);
//   BStartTicker.attach(27, startB);

//   pinMode(PWMA, OUTPUT);
//   pinMode(DA, OUTPUT);
//   pinMode(PWMB, OUTPUT);
//   pinMode(DB, OUTPUT);

//   pixels.init();
//   pixels.setBrightness(255);

//   pixels.setMode(FX_MODE_STATIC);
//   pixels.setColor(RED);
//   pixels.setSpeed(10000);

// //   pixels.setSegment(0, 6, 6, FX_MODE_STATIC, (const uint32_t[]) {0xFFFF99, YELLOW, WHITE}, 10000, false);
// //   pixels.setSegment(1, 14, 14, FX_MODE_STATIC, (const uint32_t[]) {GREEN, WHITE, YELLOW}, 3000, false);
// //   pixels.setSegment(2, 0, 5, FX_MODE_STATIC, BLACK, 3000, false);
// //   pixels.setSegment(3, 7, 13, FX_MODE_STATIC, BLACK, 3000, false);

//   pixels.start();
// }

// void loop() {
//   pixels.service();
// }
