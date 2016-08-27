#include "neopixel/neopixel.h" // use for Build IDE

#define PIXEL_PIN D2
#define PIXEL_COUNT 23
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(200, PIXEL_PIN, PIXEL_TYPE);

long blueStart    = 0;
long blueStop     = 0;
long blueDelay    = 0;
long blueLoopTime = 1000;
bool blueOn       = false;

void setup() {

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  for (int i = 0; i < PIXEL_COUNT; i++) {
    strip.setPixelColor(i, 0, 0, 120);
  }

  strip.show();
  delay(1000);
}

void loop() {
  determineState();
  display();
}

void determineState() {
  if (!blueOn) {
    if ((millis() - blueStop) > blueDelay) {
      blueStart = millis();
      blueOn    = true;
    }
  }
}

void display() {
  if (blueOn) {
    if ((millis() - blueStart) < blueLoopTime) {
      float percentage = (1.0 * (millis() - blueStart)) / blueLoopTime;
      // kind of jumpy
      // int step = (PIXEL_COUNT * (millis() - blueStart)) / blueLoopTime;
      int step = PIXEL_COUNT * percentage;
      displayBlue(step);
    } else {
      blueOn    = false;
      blueStop  = millis();
      blueDelay = (rand() % 4000) + 1000;
    }
  }
}

void displayBlue(int step) {
  for (int j = 0; j < PIXEL_COUNT; j++) {
    if (step == j) {
      strip.setPixelColor(j, 0, 0, 0);
      // strip.setPixelColor(j, 0, 0, 120);
    } else if ((PIXEL_COUNT + step - j) % PIXEL_COUNT == 1) {
      strip.setPixelColor(j, 0, 0, 0);
      // strip.setPixelColor(j, 7, 7, 120);
    } else if ((PIXEL_COUNT + step - j) % PIXEL_COUNT == 2) {
      strip.setPixelColor(j, 0, 0, 0);
      // strip.setPixelColor(j, 7, 7, 120);
    } else {
      strip.setPixelColor(j, 20, 20, 120);
    }
    strip.show();
  }
}
