#include "Animations.h"

static void snowGen(LedCube *cube);

void bottomFill(LedCube *cube)
{
  uint8_t pattern[4][4];
  for(int8_t layer = 1; layer < 5; layer++)
  {
    for(int8_t row = 0; row < 4; row++)
    {
      for(int8_t col = 0; col <4; col++)
      {
        pattern[row][col] = LOW;
      }
    }
      
    for(int8_t row = 0; row < 4; row++)
    {
      for(int8_t col = 0; col <4; col++)
      {
        pattern[row][col] = HIGH;
        setLedCubeLayer(cube, layer, &pattern[0][0]);
        delay(100);
      }
    }
  }
}

void bottomEmpty(LedCube *cube)
{
  uint8_t pattern[4][4];
  for(int8_t layer = 1; layer < 5; layer++)
  {
    for(int8_t row = 0; row < 4; row++)
    {
      for(int8_t col = 0; col <4; col++)
      {
        pattern[row][col] = HIGH;
      }
    }
      
    for(int8_t row = 0; row < 4; row++)
    {
      for(int8_t col = 0; col <4; col++)
      {
        pattern[row][col] = LOW;
        setLedCubeLayer(cube, layer, &pattern[0][0]);
        delay(100);
      }
    }
  }
}

void topFill(LedCube *cube)
{
  uint8_t pattern[4][4];
  for(int8_t layer = 4; layer > 0; layer--)
  {
    for(int8_t row = 3; row >= 0; row--)
    {
      for(int8_t col = 3; col >= 0; col--)
      {
        pattern[row][col] = LOW;
      }
    }
      
    for(int8_t row = 3; row >= 0; row--)
    {
      for(int8_t col = 3; col >= 0; col--)
      {
        pattern[row][col] = HIGH;
        setLedCubeLayer(cube, layer, &pattern[0][0]);
        delay(100);
      }
    }
  }
}

void topEmpty(LedCube *cube)
{
  uint8_t pattern[4][4];
  for(int8_t layer = 4; layer > 0; layer--)
  {
    for(int8_t row = 3; row >= 0; row--)
    {
      for(int8_t col = 3; col >= 0; col--)
      {
        pattern[row][col] = HIGH;
      }
    }
      
    for(int8_t row = 3; row >= 0; row--)
    {
      for(int8_t col = 3; col >= 0; col--)
      {
        pattern[row][col] = LOW;
        setLedCubeLayer(cube, layer, &pattern[0][0]);
        delay(100);
      }
    }
  }
}

void allOn(LedCube *cube)
{
  setAllLedCubeLayer(cube, &highPattern[0][0]);
}

void allOff(LedCube *cube)
{
  setAllLedCubeLayer(cube, &lowPattern[0][0]);
}

static void snowGen(LedCube *cube)
{
  uint8_t pattern[4][4];
  for(int8_t row = 0; row < 4; row++)
  {
    for(int8_t col = 0; col < 4; col++)
    {
      if(rand() > RAND_MAX/2)
      {
        pattern[row][col] = HIGH;
      }
      else
      {
        pattern[row][col] = LOW;
      }
    }
  }
  copyLedCubeLayer(cube, 1, 2);
  copyLedCubeLayer(cube, 2, 3);
  copyLedCubeLayer(cube, 3, 4);
  setLedCubeLayer(cube, 4, &pattern[0][0]);
}

void letItSnow(LedCube *cube)
{
  for(int8_t i = 0; i < 9; i++)
  {
    snowGen(cube);
    delay(500);
  }
}

void edgeTrail(LedCube *cube)
{
  uint8_t pattern[4][4] = {{HIGH, HIGH, HIGH, HIGH},
                           {LOW, LOW, LOW, LOW},
                           {LOW, LOW, LOW, LOW},
                           {LOW, LOW, LOW, LOW}};

  setAllLedCubeLayer(cube, &pattern[0][0]);
  for(int8_t i = 1; i < 4; i++)
  {
    pattern[0][4-i] = LOW;
    pattern[i][0] = HIGH;
    setAllLedCubeLayer(cube, &pattern[0][0]);
    delay(250);
  }

  for(int8_t i = 0; i < 3; i++)
  {
    pattern[i][0] = LOW;
    pattern[3][1+i] = HIGH;
    setAllLedCubeLayer(cube, &pattern[0][0]);
    delay(250);
  }

  for(int8_t i = 0; i < 3; i++)
  {
    pattern[3][i] = LOW;
    pattern[2-i][3] = HIGH;
    setAllLedCubeLayer(cube, &pattern[0][0]);
    delay(250);
  }

  for(int8_t i = 0; i < 3; i++)
  {
    pattern[3-i][3] = LOW;
    pattern[0][2-i] = HIGH;
    setAllLedCubeLayer(cube, &pattern[0][0]);
    delay(250);
  }
}
void leftRightPlane(LedCube *cube)
{
  uint8_t pattern[4][4] = {{LOW, LOW, LOW, LOW},
                           {LOW, LOW, LOW, LOW},
                           {LOW, LOW, LOW, LOW},
                           {LOW, LOW, LOW, LOW}};

  for(int8_t i = 1; i < 4; i++)
  {
    pattern[0][i] = HIGH;
    pattern[1][i] = HIGH;
    pattern[2][i] = HIGH;
    pattern[3][i] = HIGH;
    setAllLedCubeLayer(cube, &pattern[0][0]);
    pattern[0][i] = LOW;
    pattern[1][i] = LOW;
    pattern[2][i] = LOW;
    pattern[3][i] = LOW;
    delay(500);
  }

  for(int8_t i = 1; i < 4; i++)
  {
    pattern[0][3-i] = HIGH;
    pattern[1][3-i] = HIGH;
    pattern[2][3-i] = HIGH;
    pattern[3][3-i] = HIGH;
    setAllLedCubeLayer(cube, &pattern[0][0]);
    pattern[0][3-i] = LOW;
    pattern[1][3-i] = LOW;
    pattern[2][3-i] = LOW;
    pattern[3][3-i] = LOW;
    delay(500);
  }
}

void backFrontPlane(LedCube *cube)
{
  uint8_t pattern[4][4] = {{LOW, LOW, LOW, LOW},
                           {LOW, LOW, LOW, LOW},
                           {LOW, LOW, LOW, LOW},
                           {LOW, LOW, LOW, LOW}};

  for(int8_t i = 1; i < 4; i++)
  {
    pattern[i][0] = HIGH;
    pattern[i][1] = HIGH;
    pattern[i][2] = HIGH;
    pattern[i][3] = HIGH;
    setAllLedCubeLayer(cube, &pattern[0][0]);
    pattern[i][0] = LOW;
    pattern[i][1] = LOW;
    pattern[i][2] = LOW;
    pattern[i][3] = LOW;
    delay(500);
  }

  for(int8_t i = 1; i < 4; i++)
  {
    pattern[3-i][0] = HIGH;
    pattern[3-i][1] = HIGH;
    pattern[3-i][2] = HIGH;
    pattern[3-i][3] = HIGH;
    setAllLedCubeLayer(cube, &pattern[0][0]);
    pattern[3-i][0] = LOW;
    pattern[3-i][1] = LOW;
    pattern[3-i][2] = LOW;
    pattern[3-i][3] = LOW;
    delay(500);
  }
}

void verticalPlane(LedCube *cube)
{
  setLedCubeLayer(cube, 1, &highPattern[0][0]);
  for(int8_t layer = 2; layer < 5; layer++)
  {
    copyLedCubeLayer(cube, layer, layer-1);
    setLedCubeLayer(cube, layer-1, &lowPattern[0][0]);
    delay(500);
  }
  for(int8_t layer = 3; layer > 0; layer--)
  {
    copyLedCubeLayer(cube, layer, layer+1);
    setLedCubeLayer(cube, layer+1, &lowPattern[0][0]);
    delay(500);
  }
}

