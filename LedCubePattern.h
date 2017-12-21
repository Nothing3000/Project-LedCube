#ifndef LEDPATTERN_H
#define LEDPATTERN_H

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

LedCubeLayer newLedCubeLayer(uint8_t rows, uint8_t cols);
void setLedCubeLayer(LedCube *cube, uint8_t layer, uint8_t *newPattern);
void updateLeds(LedCubeLayer *leds);

#ifdef __cplusplus
}
#endif
#endif //LEDPATTERN_H
