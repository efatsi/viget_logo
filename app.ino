#include "neopixel/neopixel.h" // use for Build IDE
#include "math.h"

#define PIXEL_PIN D2
#define PIXEL_COUNT 28
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

  strip.setBrightness(255);
  strip.show();
}

void loop() {
  if ((millis() - blueTimer) > blueDelay) {
    runBlueCircle();
    blueTimer = millis();
    blueDelay = (rand() % 1000);// + 5000;
  }
}

int lowRg = 0;
int lowB = 120;

int highHeadRg = 30;
int highHeadB  = 255;
int highTailRg = 30;
int highTailB  = 255;

int fadeCount = 8;

void runBlueCircle() {
  for (int i = 0; i < PIXEL_COUNT * 2; i++) {
    for (int j = 0; j < PIXEL_COUNT; j++) {
      if ((i - j) % PIXEL_COUNT == 0) {
        strip.setPixelColor(j, leadColor(i));
      } else if ((PIXEL_COUNT + i - j) % PIXEL_COUNT == 1) {
        strip.setPixelColor(j, tailColor(i));
      } else if ((PIXEL_COUNT + i - j) % PIXEL_COUNT == 2) {
          strip.setPixelColor(j, tailColor(i));
      } else if ((PIXEL_COUNT + i - j) % PIXEL_COUNT == 3) {
          strip.setPixelColor(j, tailColor(i));
      } else {
        strip.setPixelColor(j, lowRg + 15, lowRg, lowB);
      }
    }
    strip.show();
    delay(stepDelay(i));
  }
}

int stepDelay(int i) {
  // return 35 + pow((0.16 * i) - 4, 2);
  return 30 + pow((0.19 * i) - 5, 2);
}

uint32_t leadColor(int i) {
  int rg, b;

  if (i <= fadeCount) {
    rg = max(0,   map(i + 1, 0, fadeCount, lowRg, highHeadRg));
    b  = min(255, map(i + 1, 0, fadeCount, lowB, highHeadB));
  } else if (i >= (PIXEL_COUNT * 2) - fadeCount) {
    rg = max(0,   map(i + 1, (PIXEL_COUNT * 2) - fadeCount, (PIXEL_COUNT * 2), highHeadRg, lowRg));
    b  = min(255, map(i + 1, (PIXEL_COUNT * 2) - fadeCount, (PIXEL_COUNT * 2), highHeadB, lowB));
  } else {
    rg = highHeadRg;
    b  = highHeadB;
  }
  return strip.Color(rg, rg, b);
}

uint32_t tailColor(int i) {
  int rg, b;

  if (i <= fadeCount) {
    rg = max(0,   map(i + 1, 0, fadeCount, lowRg, highTailRg));
    b  = min(255, map(i + 1, 0, fadeCount, lowB, highTailB));
  } else if (i >= (PIXEL_COUNT * 2) - fadeCount) {
    rg = max(0,   map(i + 1, (PIXEL_COUNT * 2) - fadeCount, (PIXEL_COUNT * 2), highTailRg, lowRg));
    b  = min(255, map(i + 1, (PIXEL_COUNT * 2) - fadeCount, (PIXEL_COUNT * 2), highTailB, lowB));
  } else {
    rg = highTailRg;
    b  = highTailB;
  }
  return strip.Color(rg, rg, b);
}
