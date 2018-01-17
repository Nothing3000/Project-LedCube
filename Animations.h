#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Arduino.h"
#include "LedCubePattern.h"

const uint8_t lowPattern[4][4] = {{LOW, LOW, LOW, LOW},  //GROUP 0
                                  {LOW, LOW, LOW, LOW},  //GROUP 0
                                  {LOW, LOW, LOW, LOW},  //GROUP 1
                                  {LOW, LOW, LOW, LOW}}; //GROUP 1

const uint8_t highPattern[4][4] = {{HIGH, HIGH, HIGH, HIGH},  //GROUP 0
                                   {HIGH, HIGH, HIGH, HIGH},  //GROUP 0
                                   {HIGH, HIGH, HIGH, HIGH},  //GROUP 1
                                   {HIGH, HIGH, HIGH, HIGH}}; //GROUP 1

void bottomFill(LedCube *cube);
void bottomEmpty(LedCube *cube);
void topFill(LedCube *cube);
void topEmpty(LedCube *cube);
void allOn(LedCube *cube);
void allOff(LedCube *cube);
void letItSnow(LedCube *cube);
void edgeTrail(LedCube *cube);
void leftRightPlane(LedCube *cube);
void backFrontPlane(LedCube *cube);
void verticalPlane(LedCube *cube);

#ifdef __cplusplus
}
#endif
#endif //ANIMATIONS_H

