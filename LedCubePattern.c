#include "LedCubePattern.h"

LedCube *newLedCube(uint8_t rows, uint8_t cols, uint8_t layerSize, Shifter *shifter)
{
  LedCube *cube;
  cube = (LedCube *)malloc(sizeof(LedCube));

  cube -> layerRows = rows;
  cube -> layerCols = cols;
  cube -> layerSize = layerSize;
  cube -> shifter = shifter;
  cube -> layers = (LedCubeLayer *)malloc(layerSize * sizeof(LedCubeLayer));

  for(int8_t i = 0; i < layerSize; i++)
  {
    cube -> layers[i] = newLedCubeLayer(rows, cols);
  }

  return cube;
}

void updateCube(LedCube *cube)
{
  static uint8_t currentLayer = 0;
  static uint8_t currentGroup = 0;

  updateLayer(cube, currentLayer, currentGroup);

  if(currentLayer == 3 && currentGroup == 1)
    currentLayer = 0;
  else if(currentLayer < 4 && currentGroup == 1)
    currentLayer++;

  currentGroup ^= 1;
}


LedCubeLayer newLedCubeLayer(uint8_t rows, uint8_t cols)
{
  LedCubeLayer leds;
  
  leds.pattern = (uint8_t **)malloc(rows * sizeof(uint8_t*));

  for(int8_t i = 0; i < cols; i++)
  {
    leds.pattern[i] = (uint8_t *)calloc(cols, sizeof(uint8_t));
  }

  return leds;
}

void setLedCubeLayer(LedCube *cube, uint8_t layer, uint8_t *newPattern)
{
  uint8_t cols = cube -> layerCols;
  uint8_t rows = cube -> layerRows;
  uint8_t **pattern = cube -> layers[layer].pattern;

  for(int8_t row = 0; row < rows; row++)
  {
    for(int8_t col = 0; col < cols; col++)
    {
      pattern[row][col] = newPattern[row*cols+col];
    }
  }
}

void updateLayer(LedCube *cube, uint8_t layer, uint8_t group)
{
  uint8_t patternBuffer[16];
  
  uint8_t **pattern = cube -> layers[layer].pattern;
  Shifter *shifter = cube -> shifter;

  for(int8_t i = 0; i < 8; i++)
  {
    if(group == 0)
      patternBuffer[i] = ((uint8_t *)pattern)[i];
    if(group == 1)
      patternBuffer[i] = ((uint8_t *)pattern)[i+8];
  }

  for(int8_t i = 8; i < 16; i++)
  {
    patternBuffer[i] = HIGH; 
  }

  patternBuffer[layer*2+8 + group] = LOW;
 
  setShifterPattern(shifter, patternBuffer);
}

