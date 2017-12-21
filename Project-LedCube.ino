#include "Shifter.h"
#include "LedCubePattern.h"

#define SERPIN 2
#define SCLKPIN 3
#define LCLKPIN 4

uint8_t newPatternLayer1[4][4] = {{HIGH, LOW, HIGH, LOW},  //GROUP 1
                                  {LOW, HIGH, LOW, HIGH},  //GROUP 1
                                  {HIGH, LOW, HIGH, LOW},  //GROUP 2
                                  {LOW, HIGH, LOW, HIGH}}; //GROUP 2


Shifter *shifter = newShifter(SERPIN, SCLKPIN, LCLKPIN, 16);
LedCube *cube = newLedCube(4, 4, 4, shifter);

void setup()
{
  setLedCubeLayer(cube, 0, (uint8_t *)newPatternLayer1);
}

void loop()
{
  
}

