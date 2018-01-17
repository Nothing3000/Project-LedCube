#include "LedCubePattern.h"

static LedCube **cubeInterrupts = NULL;
static uint8_t cubes = 0;
static uint16_t timervalue;

static void updateCube(LedCube *cube);
static LedCubeLayer newLedCubeLayer(uint8_t rows, uint8_t cols);
static void updateLayer(LedCube *cube, uint8_t layer, uint8_t group);

/*
 * Updates the next layer of currently active LED Cubes.
 */
ISR(TIMER1_OVF_vect)
{
  for(int8_t i = 0; i < cubes; i++)
  {
    updateCube(cubeInterrupts[i]);
    TCNT1 = timervalue;   // Reset timer
  }
}

/*
 * Assigns input values to a knew ledcube struct.
 */
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

/*
 * Sets the interrupt and timing values for a ledcube.
 */
void setupCubeInterrupt(LedCube *cube)
{
  noInterrupts();           // disable all interrupts
  cubes++;
  cubeInterrupts = (LedCube **)realloc(cubeInterrupts, cubes*sizeof(LedCube *));
  cubeInterrupts[cubes-1] = cube;
  timervalue = 65536-(2000000/(400*cubes)); //timervalue = 65536-((16E6/8)/(200*cubes))
  
  
  TCCR1A = 0;
  TCCR1B = 0;
  
  TCNT1 = timervalue;       // preload the timervalue
  TCCR1B |= (1 << CS11);    // 8 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
}

/*
 * Used by the ISR function, turns on the next group of LEDS according to the currently stored pattern.
 */
static void updateCube(LedCube *cube)
{
  static uint8_t currentLayer = 1;
  static uint8_t currentGroup = 0;

  updateLayer(cube, currentLayer, currentGroup);

  if(currentLayer == 4 && currentGroup == 1)
    currentLayer = 1;
  else if(currentLayer < 5 && currentGroup == 1)
    currentLayer++;

  currentGroup ^= 1;
}

/*
 * Used by the newLedCube function to reserve memory space for the individual layers.
 */
static LedCubeLayer newLedCubeLayer(uint8_t rows, uint8_t cols)
{
  LedCubeLayer leds;
  
  leds.pattern = (uint8_t **)malloc(rows * sizeof(uint8_t*));

  for(int8_t i = 0; i < cols; i++)
  {
    leds.pattern[i] = (uint8_t *)calloc(cols, sizeof(uint8_t));
  }

  return leds;
}

/*
 * Copies the data from newPattern to the internal storage for the selected layer.
 */
void setLedCubeLayer(LedCube *cube, uint8_t layer, const uint8_t *newPattern)
{
  uint8_t cols = cube -> layerCols;
  uint8_t rows = cube -> layerRows;
  uint8_t **pattern = cube -> layers[layer-1].pattern;

  for(int8_t row = 0; row < rows; row++)
  {
    for(int8_t col = 0; col < cols; col++)
    {
      pattern[row][col] = newPattern[row*cols+col];
    }
  }
}

/*
 * Copies the data from newPattern to the internal storage for all the layers.
 */

void setAllLedCubeLayer(LedCube *cube, const uint8_t *newPattern)
{
  for(int8_t layer = 4; layer > 0; layer--)
  {
    setLedCubeLayer(cube, layer, newPattern);
  }
}

/*
 * Copies the data currently in the source layer to the destenation layer.
 */
void copyLedCubeLayer(LedCube *cube, uint8_t dest, uint8_t source)
{
  uint8_t cols = cube -> layerCols;
  uint8_t rows = cube -> layerRows;
  uint8_t **destPattern = cube -> layers[dest-1].pattern;
  uint8_t **sourcePattern = cube -> layers[source-1].pattern;

  for(int8_t row = 0; row < rows; row++)
  {
    for(int8_t col = 0; col < cols; col++)
    {
      destPattern[row][col] = sourcePattern[row][col];
    }
  }
}

/*
 * Used by the updateCube function, this function updates the individual groups of a layer.
 */
static void updateLayer(LedCube *cube, uint8_t layer, uint8_t group)
{
  uint8_t patternBuffer[16];
  
  uint8_t **pattern = cube -> layers[layer-1].pattern;
  Shifter *shifter = cube -> shifter;

  for(int8_t i = 0; i < 4; i++)
  {
    if(group == 0)
      patternBuffer[i] = pattern[0][i];
    if(group == 1)
      patternBuffer[i] = pattern[2][i];
  }
  
  for(int8_t i = 0; i < 4; i++)
  {
    if(group == 0)
      patternBuffer[i+4] = pattern[1][i];
    if(group == 1)
      patternBuffer[i+4] = pattern[3][i];
  }

  for(int8_t i = 8; i < 16; i++)
  {
    patternBuffer[i] = HIGH; 
  }

  patternBuffer[17-2*layer - group] = LOW;
 
  setShifterPattern(shifter, patternBuffer);
}

