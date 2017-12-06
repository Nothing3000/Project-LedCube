#ifndef LEDPATTERN_H
#define LEDPATTERN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Arduino.h"
#include "Shifter.h"


typedef struct {
  uint8_t cols;
  uint8_t rows;
  uint8_t *rowPins;
  uint8_t **pattern;
  Shifter *shifter;
} LedPattern;

LedPattern *newLedPattern(uint8_t cols, uint8_t rows, uint8_t *rowPins, Shifter *shifter);
void setLedPattern(LedPattern *leds, uint8_t *newPattern);
void updateLeds(LedPattern *leds);

#ifdef __cplusplus
}
#endif
#endif //LEDPATTERN_H
