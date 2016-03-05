/*
 * 
 */
#include <FastLED.h>

#define LED_TYPE    P9813 // FastLED config
#define COLOR_ORDER RGB
#define DATA_PIN    11    // SPI pins
#define CLOCK_PIN   13
#define MAX_LEDS    25    // how many in the string
#define DULL_NDX    0     // starting led
#define DULL_LEDS   (5 * 2) // # we are using
#define ADDR_OFST   1     // starting led offset distance
#define ADDR_LEDS   (4 * 2) // # we are using
#define FPS         25    // frames / second
#define BRIGHTNESS  200   // don't crank it all the way!
#define hStep       24    // distance between HSV colors

CRGB leds[MAX_LEDS];

void setup()
{
  // put your setup code here, to run once:
  FastLED.addLeds<LED_TYPE, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, MAX_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  uint8_t i;
  for (i=0; i<MAX_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void loop()
{
  static uint8_t hue = 0;

  // put your main code here, to run repeatedly:
  uint8_t i, ndx, start;
  ndx = hue++;

  start = DULL_NDX;
  for (i=0; i<DULL_LEDS; /* */)
  {
    leds[start + i++] = CHSV(ndx, 255, 255);
    leds[start + i++] = CHSV(ndx, 255, 255);
    ndx += hStep;
  }
  start = DULL_NDX + DULL_LEDS + ADDR_OFST;
  for (i=ADDR_LEDS; i>0; /* */)
  {
    leds[start + --i] = CHSV(ndx, 255, 255);
    leds[start + --i] = CHSV(ndx, 255, 255);
    ndx += hStep;
  }
  FastLED.show();

  delay(1000 / FPS);
}

