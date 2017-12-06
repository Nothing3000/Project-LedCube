#include "Shifter.h"

/*
 * This function creates a new shifter structure,
 * this structure contains all the information related to
 * the shiftregister.
 */
Shifter *newShifter(uint8_t ser, uint8_t sclk, uint8_t lclk, uint8_t shifterSize)
{
  pinMode(ser, OUTPUT);
  pinMode(sclk, OUTPUT);
  pinMode(lclk, OUTPUT);

  digitalWrite(ser, LOW);
  digitalWrite(sclk, LOW);
  digitalWrite(lclk, LOW);
  
  Shifter *shifter;
  shifter = (Shifter *)malloc(sizeof(Shifter));

  shifter -> serPin = ser;
  shifter -> sclkPin = sclk;
  shifter -> lclkPin = lclk;
  shifter -> pattern = NULL;
  shifter -> patternSize = shifterSize;

  return shifter;
}

/*
 * Loads a new pattern into the Shifter struct.
 */
void setShifterPattern(Shifter *shifter, uint8_t *newPattern)
{
  shifter -> pattern = newPattern;
  updateShifter(shifter);
}

/*
 * Transmits the data contained in the shifter struct to the actual shiftregister.
 */
void updateShifter(Shifter *shifter)
{
  uint8_t shifterSerPin = shifter -> serPin;
  uint8_t shifterSclkPin = shifter -> sclkPin;
  uint8_t shifterLclkPin = shifter -> lclkPin;
  uint8_t *shifterPattern = shifter -> pattern;
  uint8_t shifterPatternSize = shifter -> patternSize;
  
  for(int8_t i = shifterPatternSize-1; i >= 0; i--)
  {
    digitalWrite(shifterSerPin, shifterPattern[i]);
    digitalWrite(shifterSclkPin, HIGH);
    digitalWrite(shifterSclkPin, LOW);
  }

  digitalWrite(shifterLclkPin, HIGH);
  digitalWrite(shifterLclkPin, LOW);
}

