#include "LedPattern.h"

LedPattern *newLedPattern(uint8_t rows, uint8_t cols, uint8_t *rowPins, Shifter *shifter)
{
  LedPattern *leds;
  leds = (LedPattern *)malloc(sizeof(LedPattern));

  for(int8_t i = 0; i < cols; i++)
  {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }

  leds -> cols = cols;
  leds -> rows = rows;
  leds -> rowPins = rowPins;
  leds -> shifter = shifter;
  leds -> pattern = (uint8_t **)calloc(rows, sizeof(uint8_t));

  for(int8_t i = 0; i < cols; i++)
  {
    leds -> pattern[i] = (uint8_t *)calloc(cols, sizeof(uint8_t));
  }

  return leds;
}

void setLedPattern(LedPattern *leds, uint8_t *newPattern)
{
  uint8_t cols = leds -> cols;
  uint8_t rows = leds -> rows;
  uint8_t **pattern = leds -> pattern;

  for(int8_t row = 0; row < rows; row++)
  {
    for(int8_t col = 0; col < cols; col++)
    {
      pattern[row][col] = ((uint8_t **)newPattern)[row][col];
    }
  }
}

void updateLeds(LedPattern *leds)
{
  uint8_t cols = leds -> cols;
  uint8_t rows = leds -> rows;
  uint8_t **pattern = leds -> pattern;
  uint8_t *rowPins = leds -> rowPins;
  Shifter *shifter = leds -> shifter;

  for(int8_t row = 0; row < rows; row++)
  {
    setShifterPattern(shifter, pattern[row]);
    digitalWrite(rowPins[row], LOW);
    digitalWrite(rowPins[row], HIGH);
  }
  
  
}

