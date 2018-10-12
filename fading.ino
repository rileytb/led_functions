#include <Adafruit_NeoPixel.h>

#define PIN 0
#define NUMPIXELS 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int waitTime = 2;
int curLit = 0;
int maxLight = 255;
int minLight = 100;

uint32_t red = strip.Color(255, 0, 0);
uint32_t green = strip.Color(0, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);

void setup() {
  strip.begin();
  strip.show();
}

void loop() {
  fadeInAll(blue);
  delay(150);
  fadeInAll(green);
  delay(150);
}

void fadeIn(uint8_t index, uint8_t red, uint8_t green, uint8_t blue) {
  for (uint8_t b = minLight; b < maxLight; b++) {
    strip.setPixelColor(index, red * b / 255, green * b / 255, blue * b / 255);
    strip.show();
    delay(2);
  };
}

void fadeOut(uint8_t index, uint8_t red, uint8_t green, uint8_t blue) {
  for (uint8_t b = maxLight; b > minLight; b--) {
    strip.setPixelColor(index, red * b / 255, green * b / 255, blue * b / 255);
    strip.show();
    delay(2);
  };
}

void fadeInAll(uint32_t color) {
  for (uint8_t b = minLight; b < maxLight; b++) {
    for (uint8_t p = 0; p < NUMPIXELS; p++) {
      strip.setPixelColor(p, color * b / 255);
    };
    strip.show();
    delay(70);
  };
}

