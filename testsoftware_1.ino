#include "Shifter.h"


//Voorbeeld pinnummers
#define SERPIN 2
#define SCLKPIN 3
#define LCLKPIN 4



uint8_t pattern[] = {LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH};
Shifter *leds = newShifter(SERPIN, SCLKPIN, LCLKPIN, 8);

void setup() 
{
  setShifterPattern(leds, pattern);
  updateShifter(leds);
}

void loop()
{
  
}

