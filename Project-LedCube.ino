#include "Shifter.h"

//Voorbeeld pinnummers
#define SERPIN 2
#define SCLKPIN 4
#define LCLKPIN 3

uint8_t pattern[8] = {LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH};
                         
Shifter *shifter = newShifter(SERPIN, SCLKPIN, LCLKPIN, 8);

void setup() 
{
  setShifterPattern(shifter, pattern);
}

void loop()
{
  for(int8_t i = 0; i < 8; i++)
  {
    pattern[i] = HIGH;
    updateShifter(shifter);
    pattern[i] = LOW;
    delay(100);
  }
  for(int8_t i = 7; i >= 0; i--)
  {
    pattern[i] = HIGH;
    updateShifter(shifter);
    pattern[i] = LOW;
    delay(100);
  }
}

