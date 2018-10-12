#include <Adafruit_NeoPixel.h>

#define PIN 0
#define NUMPIXELS 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int index = 0;

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  chase(index);
  index +=1;
  if (index > NUMPIXELS) {
    index = 0;
  }
  delay(80);
}

void chase(int index) {
    for(int i=0; i < NUMPIXELS; i++) {
    if ((i + index) % 2 == 0) {
      strip.setPixelColor(i, strip.Color(255, 0, 0));
    } else {
      strip.setPixelColor(i, strip.Color(0, 0, 255));
    }
    strip.show();
//    delay(80);
  }
}

