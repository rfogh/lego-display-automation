#include "MqttClient.h"

#include <Adafruit_NeoPixel.h>


#define PIN           6
#define NUMSTRIP      12
#define NUMPIXELS     8

#define N             0x00000000  //Black
#define W             0x00FFFFFF  //White
#define Y             0x00FFFF00  //Yellow
#define P             0x00FF00FF  //Purple
#define T             0x0000FFFF  //Turquoise
#define R             0x00FF0000  //Red
#define G             0x0000FF00  //Green
#define B             0x000000FF  //Blue
#define O             0x00FFA500  //Orange
#define V             0x008A2BE2  //Violet
#define I             0x004B0082  //Indigo

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMSTRIP*NUMPIXELS, PIN, NEO_RGB+NEO_KHZ800);

MqttClient client = MqttClient("ferris_light");

unsigned int small_circle[NUMSTRIP][NUMPIXELS] = {
  {Y,N,N,N,N,N,N,N},
  {N,Y,N,N,N,N,N,N},
  {N,N,Y,N,N,N,N,N},
  {N,N,N,Y,N,N,N,N},
  {N,N,N,N,Y,N,N,N},
  {N,N,N,N,N,Y,N,N},
  {N,N,N,N,N,N,Y,N},
  {N,N,N,N,N,Y,N,N},
  {N,N,N,N,Y,N,N,N},
  {N,N,N,Y,N,N,N,N},
  {N,N,Y,N,N,N,N,N},
  {N,Y,N,N,N,N,N,N}
};

unsigned int large_circle[NUMSTRIP][NUMPIXELS] = {
  {N,Y,N,N,N,N,N,N},
  {N,N,Y,N,N,N,N,N},
  {N,N,N,Y,N,N,N,N},
  {N,N,N,N,Y,N,N,N},
  {N,N,N,N,N,Y,N,N},
  {N,N,N,N,N,N,Y,N},
  {N,N,N,N,N,N,N,Y},
  {N,N,N,N,N,N,Y,N},
  {N,N,N,N,N,Y,N,N},
  {N,N,N,N,Y,N,N,N},
  {N,N,N,Y,N,N,N,N},
  {N,N,Y,N,N,N,N,N}
};
  
void setup() {
  pixels.begin();

  client.initialize(handler);
  client.subscribe("command/ferris");
}

void handler(char* topic, JsonObject message) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  // char *id = message["id"];
}

void loop() {
  client.loop();

  draw(small_circle);
  delay(200);
  draw(large_circle);
  delay(200);
}

void draw(unsigned int colors[NUMSTRIP][NUMPIXELS]) {
  for (int i=0; i<NUMSTRIP; i++) {
    bool isEven = (i % 2) == 0;
    for(int j=0; j<NUMPIXELS; j++) {
      unsigned int pixelIndex;
      if (isEven) {
        pixelIndex = i*NUMPIXELS+j;
      }
      else {
        pixelIndex = i*NUMPIXELS+((NUMPIXELS-1)-j);
      }
      pixels.setPixelColor(pixelIndex, colors[i][j]);
    }
  }
  pixels.show();
}

