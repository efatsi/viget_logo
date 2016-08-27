#include "neopixel/neopixel.h" // use for Build IDE

#define PIXEL_PIN D2
#define PIXEL_COUNT 23
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(200, PIXEL_PIN, PIXEL_TYPE);

long blueTimer = 0;
long blueDelay = 0;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  for (int i = 0; i < PIXEL_COUNT; i++) {
    strip.setPixelColor(i, 0, 0, 120);
  }

  strip.show();
}

void loop() {
  if ((millis() - blueTimer) > blueDelay) {
    runBlueCircle();
    blueTimer = millis();
    blueDelay = (rand() % 15000) + 5000;
  }
}

void runBlueCircle() {
  for (int i = 0; i < PIXEL_COUNT; i++) {
    for (int j = 0; j < PIXEL_COUNT; j++) {
      if (i == j) {
        strip.setPixelColor(j, 0, 0, 120);
      } else if ((PIXEL_COUNT + i - j) % PIXEL_COUNT == 1) {
        strip.setPixelColor(j, 10, 10, 120);
      } else if ((PIXEL_COUNT + i - j) % PIXEL_COUNT == 2) {
          strip.setPixelColor(j, 10, 10, 120);
      } else {
        strip.setPixelColor(j, 20, 20, 120);
      }
    }
    strip.show();
    delay(70);
  }
}
