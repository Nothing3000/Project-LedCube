#include "Shifter.h"

//Voorbeeld pinnummers
#define SERPIN 4
#define SCLKPIN 5
#define LCLKPIN 6

uint8_t pattern[8] = {LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH};
                         
Shifter *shifter = newShifter(SERPIN, SCLKPIN, LCLKPIN, 8);

void setup() 
{
  setShifterPattern(shifter, pattern);
}

void loop()
{
  
}

