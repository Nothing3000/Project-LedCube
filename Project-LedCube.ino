#include "Shifter.h"
#include "LedCubePattern.h"

#define SERPIN 2
#define SCLKPIN 3
#define LCLKPIN 4

uint8_t shiftPattern[16] = {HIGH, LOW, HIGH, LOW, 
                            LOW, HIGH, LOW, HIGH,
                            HIGH, HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH};
                          /*4.1   4.0   3.1  3.0   2.1   2.0   1.1   1.0*/ 

uint8_t newPattern[4][4] = {{HIGH, LOW, HIGH, LOW},  //GROUP 0
                            {LOW, HIGH, LOW, HIGH},  //GROUP 0
                            {HIGH, LOW, HIGH, LOW},  //GROUP 1
                            {LOW, HIGH, LOW, HIGH}}; //GROUP 1

uint8_t pattern2[4][4] = {{LOW, LOW, LOW, LOW},  //GROUP 0
                          {LOW, LOW, LOW, LOW},  //GROUP 0
                          {LOW, LOW, LOW, LOW},  //GROUP 1
                          {LOW, LOW, LOW, LOW}}; //GROUP 1


Shifter *shifter = newShifter(SERPIN, SCLKPIN, LCLKPIN, 16);
LedCube *cube = newLedCube(4, 4, 4, shifter);

void setup()
{
  setLedCubeLayer(cube, 4, &pattern2[0][0]);
  setLedCubeLayer(cube, 3, &pattern2[0][0]);
  setLedCubeLayer(cube, 2, &pattern2[0][0]);
  setLedCubeLayer(cube, 1, &pattern2[0][0]);
  setupCubeInterrupt(cube);
  //setShifterPattern(shifter, shiftPattern);
}

void loop()
{
  bottomFill();
  bottomEmpty();
  delay(2000);
  topFill();
  topEmpty();
}

void bottomFill()
{
  for(int8_t layer = 1; layer < 5; layer++)
  {
    for(int8_t row = 0; row < 4; row++)
    {
      for(int8_t col = 0; col <4; col++)
      {
        pattern2[row][col] = LOW;
      }
    }
      
    for(int8_t row = 0; row < 4; row++)
    {
      for(int8_t col = 0; col <4; col++)
      {
        pattern2[row][col] = HIGH;
        setLedCubeLayer(cube, layer, &pattern2[0][0]);
        delay(100);
      }
    }
  }
}

void bottomEmpty()
{
  for(int8_t layer = 1; layer < 5; layer++)
  {
    for(int8_t row = 0; row < 4; row++)
    {
      for(int8_t col = 0; col <4; col++)
      {
        pattern2[row][col] = HIGH;
      }
    }
      
    for(int8_t row = 0; row < 4; row++)
    {
      for(int8_t col = 0; col <4; col++)
      {
        pattern2[row][col] = LOW;
        setLedCubeLayer(cube, layer, &pattern2[0][0]);
        delay(100);
      }
    }
  }
}

void topFill()
{
  for(int8_t layer = 4; layer > 0; layer--)
  {
    for(int8_t row = 3; row >= 0; row--)
    {
      for(int8_t col = 3; col >= 0; col--)
      {
        pattern2[row][col] = LOW;
      }
    }
      
    for(int8_t row = 3; row >= 0; row--)
    {
      for(int8_t col = 3; col >= 0; col--)
      {
        pattern2[row][col] = HIGH;
        setLedCubeLayer(cube, layer, &pattern2[0][0]);
        delay(100);
      }
    }
  }
}

void topEmpty()
{
  for(int8_t layer = 4; layer > 0; layer--)
  {
    for(int8_t row = 3; row >= 0; row--)
    {
      for(int8_t col = 3; col >= 0; col--)
      {
        pattern2[row][col] = HIGH;
      }
    }
      
    for(int8_t row = 3; row >= 0; row--)
    {
      for(int8_t col = 3; col >= 0; col--)
      {
        pattern2[row][col] = LOW;
        setLedCubeLayer(cube, layer, &pattern2[0][0]);
        delay(100);
      }
    }
  }
}

