#ifndef SHIFTER_H
#define SHIFTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Arduino.h"


typedef struct {
  uint8_t serPin;
  uint8_t sclkPin;
  uint8_t lclkPin;
  uint8_t *pattern;
  uint8_t patternSize;
} Shifter;

Shifter *newShifter(uint8_t ser, uint8_t sclk, uint8_t lclk, uint8_t shifterSize);
void setShifterPattern(Shifter *shifter, uint8_t *newPattern);
void updateShifter(Shifter *shifter);

#ifdef __cplusplus
}
#endif
#endif //SHIFTER_H
