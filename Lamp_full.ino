#include <Adafruit_NeoPixel.h>

#define PIN 0
#define NUMPIXELS 12

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int waitTime = 25;
int curLit = 0;
int maxLight = 255;
int minLight = 25;

uint32_t white = strip.Color(255, 255, 255);
uint32_t red = strip.Color(255, 0, 0);
uint32_t green = strip.Color(0, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t pink = strip.Color(255, 20, 175);
uint32_t none = strip.Color(0, 0, 0);
uint32_t yellow = strip.Color(142, 111, 0);
uint32_t purple = strip.Color(228, 157, 232);

//Didn't work
//struct RetVal {
//  uint8_t red;
//  uint8_t green;
//  uint8_t blue;
//};
//
//RetVal separateColors(uint32_t color);
//
//RetVal separateColors(uint32_t color) {
//  uint8_t r = ((uint8_t)color >> 16),
//    g = ((uint8_t)color >>  8),
//    b = (uint8_t)color;
//
//  return { r, g, b };
//}

// Returns the Red component of a 32-bit color
uint8_t Red(uint32_t color)
{
    return (color >> 16) & 0xFF;
}

// Returns the Green component of a 32-bit color
uint8_t Green(uint32_t color)
{
    return (color >> 8) & 0xFF;
}

// Returns the Blue component of a 32-bit color
uint8_t Blue(uint32_t color)
{
    return color & 0xFF;
}

//END UTILS
//**********************//

void setup() {
  strip.begin();
  strip.show();
}

void loop() {

  colorFade(green); // fade into red
  colorFade(blue); // and then into white
  colorFade(red); // fade into red
  colorFade(white); // and then into white
  colorFade(yellow); // fade into red
  colorFade(green); // and then into white
  delay(5000);

  //  flashRandom(70, 8);
  //    fadeInAll(255, 0, 0);
  //  delay(8000);

  // for(uint16_t i = 0; i < 50; i++) {
  //    fadeInAll(142, 111, 0);
  //    delay(50);
  //    fadeOutAll(142, 111, 0);
  // }

  //  for(uint16_t i = 0; i < 50; i++) {
  //    chase(0, 0, 255, white);
  //  }
}

void chase(uint32_t red, uint32_t green, uint32_t blue, uint32_t baseColor) {
    for(uint16_t i=0; i<strip.numPixels() + 3; i++) {
      strip.setPixelColor(i, red, green, blue); // Draw new pixel
      strip.setPixelColor(i-1, red/2, green/2, blue/8); // Draw new pixel
      strip.setPixelColor(i-2, red/4, green/4, blue/16); // Draw new pixel
      strip.setPixelColor(i-3, baseColor); // Erase pixel a few steps bac
      strip.show();
      delay(500);
  }
}

void colorFade(uint32_t changeToColor) {
  for(uint16_t i = 0; i < strip.numPixels(); i++) {
      uint8_t curr_r, curr_g, curr_b;
      uint32_t curr_col = strip.getPixelColor(i); // get the current colour
      curr_b = curr_col & 0xFF; curr_g = (curr_col >> 8) & 0xFF; curr_r = (curr_col >> 16) & 0xFF;  // separate into RGB components
      
      uint8_t set_r, set_g, set_b;
      set_b = changeToColor & 0xFF; set_g = (changeToColor >> 8) & 0xFF; set_r = (changeToColor >> 16) & 0xFF;  // separate into RGB components
    
      while ((curr_r != set_r) || (curr_g != set_g) || (curr_b != set_b)){  // while the curr color is not yet the target color
        if (curr_r < set_r) curr_r++; else if (curr_r > set_r) curr_r--;  // increment or decrement the old color values
        if (curr_g < set_g) curr_g++; else if (curr_g > set_g) curr_g--;
        if (curr_b < set_b) curr_b++; else if (curr_b > set_b) curr_b--;
        setAll(strip.Color(curr_r, curr_g, curr_b));
        strip.show();
        delay(10);  // add a delay if its too fast
      }
      delay(1000);
  }
}

void fadeIn(uint8_t index, uint32_t red, uint32_t green, uint32_t blue) {
  for (uint8_t b = minLight; b < maxLight; b++) {
    strip.setPixelColor(index, red * b / 255, green * b / 255, blue * b / 255);
    strip.show();
    delay(10);
  };
}

void fadeOut(uint8_t index, uint32_t red, uint32_t green, uint32_t blue) {
  for (uint8_t b = maxLight; b > minLight; b--) {
    strip.setPixelColor(index, red * b / 255, green * b / 255, blue * b / 255);
    strip.show();
    delay(10);
  };
}

void fadeInAll(uint32_t red, uint32_t green, uint32_t blue) {
  for (uint8_t b = minLight; b < maxLight; b++) {
    for (uint8_t p = 0; p < NUMPIXELS; p++) {
      strip.setPixelColor(p, red * b / 255, green * b / 255, blue * b / 255);
    };
    strip.show();
    delay(10);
  };
}

void fadeOutAll(uint32_t red, uint32_t green, uint32_t blue) {
  for (uint8_t b = maxLight; b > minLight; b--) {
    for (uint8_t p = 0; p < NUMPIXELS; p++) {
      strip.setPixelColor(p, red * b / 255, green * b / 255, blue * b / 255);
    };
    strip.show();
    delay(10);
  };
}

void flashRandom(int wait, uint8_t howmany) {

  for(uint16_t i=0; i<howmany; i++) {
    // get a random pixel from the list
    int j = random(strip.numPixels());

    // now we will 'fade' it in 5 steps
    for (int x=0; x < 5; x++) {
      int r = red * (x+1); r /= 5;
      int g = green * (x+1); g /= 5;
      int b = blue * (x+1); b /= 5;

      strip.setPixelColor(j, strip.Color(r, g, b));
      strip.show();
      delay(wait);
    }
    // & fade out in 5 steps
    for (int x=5; x >= 0; x--) {
      int r = red * x; r /= 5;
      int g = green * x; g /= 5;
      int b = blue * x; b /= 5;

      strip.setPixelColor(j, strip.Color(r, g, b));
      strip.show();
      delay(wait);
    }
  }
  // LEDs will be off when done (they are faded to 0)
}

void setAll(uint32_t color) {
  for (uint8_t p = 0; p < NUMPIXELS; p++) {
    strip.setPixelColor(p, color);
  };
  strip.show();
}
