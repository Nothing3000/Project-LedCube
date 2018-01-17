#include "Shifter.h"
#include "LedCubePattern.h"
#include "Animations.h"

#define SERPIN 2
#define SCLKPIN 3
#define LCLKPIN 4


uint8_t transitionPattern[4][4] = {{HIGH, LOW, LOW, LOW},  //GROUP 0
                                   {HIGH, LOW, LOW, LOW},  //GROUP 0
                                   {HIGH, LOW, LOW, LOW},  //GROUP 1
                                   {HIGH, LOW, LOW, LOW}}; //GROUP 1


Shifter *shifter = newShifter(SERPIN, SCLKPIN, LCLKPIN, 16);
LedCube *cube = newLedCube(4, 4, 4, shifter);

void setup()
{
  setupCubeInterrupt(cube);
}

void loop()
{
  allOff(cube);
  edgeTrail(cube);
  edgeTrail(cube);
  allOff(cube);
  backFrontPlane(cube);
  backFrontPlane(cube);
  setAllLedCubeLayer(cube, &transitionPattern[0][0]);
  delay(500);
  leftRightPlane(cube);
  leftRightPlane(cube);
  allOff(cube);
  setLedCubeLayer(cube, 1, &highPattern[0][0]);
  delay(500);
  verticalPlane(cube);
  verticalPlane(cube);
  allOff(cube);
  letItSnow(cube);
  allOff(cube);
  bottomFill(cube);
  bottomEmpty(cube);
  topFill(cube);
  topEmpty(cube);
  delay(5000);
}



