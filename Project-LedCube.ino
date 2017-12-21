#include "Shifter.h"
#include "LedCubePattern.h"

#define SERPIN 2
#define SCLKPIN 3
#define LCLKPIN 4

uint8_t newPattern[4][4] = {{HIGH, LOW, HIGH, LOW},  //GROUP 0
                            {LOW, HIGH, LOW, HIGH},  //GROUP 0
                            {HIGH, LOW, HIGH, LOW},  //GROUP 1
                            {LOW, HIGH, LOW, HIGH}}; //GROUP 1


Shifter *shifter = newShifter(SERPIN, SCLKPIN, LCLKPIN, 16);
LedCube *cube = newLedCube(4, 4, 4, shifter);

void setup()
{
  setLedCubeLayer(cube, 0, (uint8_t *)newPattern);
}

void loop()
{
  
}

