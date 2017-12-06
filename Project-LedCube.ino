#include "Shifter.h"
#include "LedPattern.h"


//Voorbeeld pinnummers
#define SERPIN 4
#define SCLKPIN 5
#define LCLKPIN 6
#define ROWPIN1 2
#define ROWPIN2 3


uint8_t colPins[] = {ROWPIN1, ROWPIN2};
uint8_t pattern[2][8] = {{LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH},
                         {HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW}};
                         
Shifter *shifter = newShifter(SERPIN, SCLKPIN, LCLKPIN, 8);
LedPattern *leds = newLedPattern(2, 8, colPins, shifter);

void setup() 
{
  setLedPattern(leds, &pattern[0][0]);
}

void loop()
{
  updateLeds(leds);
}

