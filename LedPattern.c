#include "LedPattern.h"

LedPattern *ledsInterrupt;

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
  leds -> pattern = (uint8_t **)calloc(rows, sizeof(uint8_t *));

  for(int8_t i = 0; i < rows; i++)
  {
    leds -> pattern[i] = (uint8_t *)calloc(cols, sizeof(uint8_t));
  }

  return leds;
}

void setupLedInterrupt(LedPattern *leds)
{
  // initialize timer1 
  noInterrupts();           // disable all interrupts
  ledsInterrupt = leds;
  
  TCCR1A = 0;
  TCCR1B = 0;

  // Set timer1_counter to the correct value for our interrupt interval 
  
  TCNT1 = TIMER1VALUE;   // preload timer 65536-16MHz/256/100Hz
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
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
      pattern[row][col] = newPattern[row*cols+col];
    }
  }
}

void updateLeds(LedPattern *leds)
{
  uint8_t rows = leds -> rows;
  uint8_t **pattern = leds -> pattern;
  uint8_t *rowPins = leds -> rowPins;
  Shifter *shifter = leds -> shifter;

  static uint8_t row;
 
  digitalWrite(rowPins[row], HIGH);

  if(row < rows-1)
    row++;
  else
    row = 0;
  
  setShifterPattern(shifter, pattern[row]);
  digitalWrite(rowPins[row], LOW);


}

ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
  updateLeds(ledsInterrupt);
  TCNT1 = TIMER1VALUE;   // preload timer
}

