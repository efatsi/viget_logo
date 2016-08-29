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
    blueDelay = (rand() % 1000);// + 5000;
  }
}

void runBlueCircle() {
  for (int i = 5; i >= 1; i--) {
    strip.setPixelColor(0, 2 * i, 2 * i, map(i, 0, 5, 255, 100));
    strip.setPixelColor(PIXEL_COUNT - 1, 5 + i, 5 + i, map(i, 0, 5, 220, 100));
    strip.setPixelColor(PIXEL_COUNT - 2, 5 + i, 5 + i, map(i, 0, 5, 220, 100));
    strip.show();
    delay(100);
  }

  for (int i = 0; i < PIXEL_COUNT * 2; i++) {
    for (int j = 0; j < PIXEL_COUNT; j++) {
      if (i == j) {
        strip.setPixelColor(j, 0, 0, 255);
      } else if ((PIXEL_COUNT + i - j) % PIXEL_COUNT == 1) {
        strip.setPixelColor(j, 5, 5, 220);
      } else if ((PIXEL_COUNT + i - j) % PIXEL_COUNT == 2) {
          strip.setPixelColor(j, 5, 5, 220);
      } else {
        strip.setPixelColor(j, 10, 10, 100);
      }
    }
    strip.show();
    delay(100);
  }

  for (int i = 1; i <= 5; i++) {
    strip.setPixelColor(PIXEL_COUNT - 1, 2 * i, 2 * i, map(i, 0, 5, 255, 100));
    strip.setPixelColor(PIXEL_COUNT - 2, 5 + i, 5 + i, map(i, 0, 5, 220, 100));
    strip.setPixelColor(PIXEL_COUNT - 3, 5 + i, 5 + i, map(i, 0, 5, 220, 100));
    strip.show();
    delay(100);
  }
}
