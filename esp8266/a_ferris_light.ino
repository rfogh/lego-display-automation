/* Light control for Ferris wheel */

#include <WS2812FX.h>
#include <Ticker.h>

#define PIN           D6
#define NUMSTRIP      12
#define NUMPIXELS     8

WS2812FX pixels = WS2812FX(NUMSTRIP*NUMPIXELS, PIN, NEO_GRB+NEO_KHZ800);
Ticker ticker;

unsigned int getRandomColor() {
    unsigned int color = 0;
    while (color == 0 || color == 0xFFFFFF) {
        color = random(2)*0xFF0000 + random(2)*0x00FF00 + random(2)*0x0000FF;
    }
    return color;
}

void changeLight() {
    pixels.resetSegments();

    unsigned short modes[9] = {
      // FX_MODE_BICOLOR_CHASE,
      // FX_MODE_BLINK_RAINBOW,
      // FX_MODE_CHASE_BLACKOUT,
      // FX_MODE_CHASE_BLACKOUT_RAINBOW,
      // FX_MODE_CHASE_COLOR,
      // FX_MODE_CHASE_FLASH,
      // FX_MODE_CHASE_FLASH_RANDOM,
      FX_MODE_CHASE_RAINBOW,
      // FX_MODE_CHASE_RANDOM,
      // FX_MODE_CIRCUS_COMBUSTUS,
      // FX_MODE_COLOR_SWEEP_RANDOM,
      // FX_MODE_COLOR_WIPE,
      // FX_MODE_COLOR_WIPE_RANDOM,
      FX_MODE_COMET,
      // FX_MODE_DUAL_SCAN,
      FX_MODE_FIREWORKS,
      FX_MODE_FIREWORKS_RANDOM,
      FX_MODE_FLASH_SPARKLE,
      // FX_MODE_HALLOWEEN,
      // FX_MODE_LARSON_SCANNER,
      // FX_MODE_MERRY_CHRISTMAS,
      // FX_MODE_MULTI_DYNAMIC,
      // FX_MODE_MULTI_STROBE,
      // FX_MODE_RAINBOW,
      FX_MODE_RAINBOW_CYCLE,
      // FX_MODE_RANDOM_COLOR,
      // FX_MODE_RUNNING_COLOR,
      // FX_MODE_RUNNING_LIGHTS,
      // FX_MODE_RUNNING_RANDOM,
      // FX_MODE_RUNNING_RED_BLUE,
      // FX_MODE_SCAN,
      FX_MODE_SPARKLE,
      // FX_MODE_STROBE,
      // FX_MODE_STROBE_RAINBOW,
      // FX_MODE_THEATER_CHASE,
      // FX_MODE_THEATER_CHASE_RAINBOW,
      // FX_MODE_TRICOLOR_CHASE,
      FX_MODE_TWINKLE,
      // FX_MODE_TWINKLE_FADE,
      // FX_MODE_TWINKLE_FADE_RANDOM,
      FX_MODE_TWINKLE_RANDOM
    };

    unsigned int colors[3] = {getRandomColor(), getRandomColor(), getRandomColor()};
    bool circle = random(2) == 1;
    unsigned short mode = modes[random(9)];
    unsigned short speed = circle ? 1000 : 7000;
    unsigned short direction = random(3);

    if (circle) {
      for (int i=0; i<NUMSTRIP; i++) {
        pixels.setSegment(i, i*NUMPIXELS, (i+1)*NUMPIXELS-1, mode, colors, speed, i%2==direction); 
      }
    }
    else {
      pixels.setSegment(0, 0, NUMSTRIP*NUMPIXELS-1, mode, colors, speed, direction==1);
    }
}

void reboot() {
    ESP.reset();
}

void setup() {
  Serial.begin(115200);

  pixels.init();
  pixels.setBrightness(20);
  changeLight();
  pixels.start();

  ticker.attach(20, reboot);
}

void loop() {
  pixels.service();
}
