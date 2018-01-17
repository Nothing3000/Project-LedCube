#ifndef LEDCUBEPATTERN_H
#define LEDCUBEPATTERN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Arduino.h"
#include "Shifter.h"

typedef struct {
  uint8_t **pattern;
} LedCubeLayer;

typedef struct {
  uint8_t layerSize;
  LedCubeLayer *layers;
  uint8_t layerCols;
  uint8_t layerRows;
  Shifter *shifter;
} LedCube;

LedCube *newLedCube(uint8_t rows, uint8_t cols, uint8_t layerSize, Shifter *shifter);
void setupCubeInterrupt(LedCube *cube);

void setLedCubeLayer(LedCube *cube, uint8_t layer, const uint8_t *newPattern);
void setAllLedCubeLayer(LedCube *cube, const uint8_t *newPattern);
void copyLedCubeLayer(LedCube *cube, uint8_t dest, uint8_t source);


#ifdef __cplusplus
}
#endif
#endif //LEDCUBEPATTERN_H
