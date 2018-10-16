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

    unsigned int colors[3] = {getRandomColor(), getRandomColor(), getRandomColor()};
    bool circle = random(2) == 1;
    unsigned short mode = random(56);
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
