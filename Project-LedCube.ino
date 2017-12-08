#include "Shifter.h"
#include "LedPattern.h"

//Voorbeeld pinnummers
#define SERPIN 4
#define SCLKPIN 5
#define LCLKPIN 6
#define ROWPIN1 2
#define ROWPIN2 3

uint8_t rowPins[] = {ROWPIN1, ROWPIN2};

uint8_t pattern[2][8] = {{LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH},
                         {HIGH, LOW, LOW, HIGH, LOW, LOW, HIGH, LOW}};
                         
uint8_t pattern2[2][8] = {{HIGH, LOW, LOW, HIGH, LOW, LOW, HIGH, LOW},
                         {LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH}};
                         
Shifter *shifter = newShifter(SERPIN, SCLKPIN, LCLKPIN, 8);
LedPattern *leds = newLedPattern(2, 8, rowPins, shifter);

void setup() 
{
  setupLedInterrupt(leds);
}

void loop()
{
  setLedPattern(leds, (uint8_t *)pattern);
  delay(1000);
  setLedPattern(leds, (uint8_t *)pattern2);
  delay(1000);
}

