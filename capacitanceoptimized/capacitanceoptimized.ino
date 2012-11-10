#include "pins_arduino.h" // Arduino pre-1.0 needs this
#include "pitches.h"
#include "math.h"
const int numsensors = 5;
const int threshold = 9;
int sensorpins[] = {
  4, 5, 6, 7, 8};
const int speakerPin = 12;

void setup()
{
  Serial.begin(9600);
}

void loop(){
  int answers[] = {0, 0, 0, 0, 0};
  int bools[] = {0, 0, 0, 0, 0};
  for (int i = 0; i < numsensors; i++) {
    answers[i] = readCapacitivePin(sensorpins[i]);
    if (answers[i] > threshold) {
      bools[i] = 1; 
    }
    Serial.print(answers[i]);
    Serial.print(", ");
    }
  Serial.println();
  playmusic(bools);
  delay(5);
}

void playmusic(int* bools) {
  int notecode = 0;
  for (int i = 0; i < numsensors; i++) {
    notecode += bools[i]*pow(2, i);
  }
  switch(notecode)
  {
    case 0:
    case 1:
      tone(speakerPin, NOTE_C4);
    case 2:
      tone(speakerPin, NOTE_D4);
    case 3:
      tone(speakerPin, NOTE_E4);
  }
}


uint8_t readCapacitivePin(int pinToMeasure) {
  // Variables used to translate from Arduino to AVR pin naming
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  // Here we translate the input pin number from
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  //  and which bit of those registers we care about.
  byte bitmask;
  port = portOutputRegister(digitalPinToPort(pinToMeasure));
  ddr = portModeRegister(digitalPinToPort(pinToMeasure));
  bitmask = digitalPinToBitMask(pinToMeasure);
  pin = portInputRegister(digitalPinToPort(pinToMeasure));
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  // Make the pin an input with the internal pull-up on
  *ddr &= ~(bitmask);
  *port |= bitmask;

  // Now see how long the pin to get pulled up. This manual unrolling of the loop
  // decreases the number of hardware cycles between each read of the pin,
  // thus increasing sensitivity.
  uint8_t cycles = 17;
  if (*pin & bitmask) { 
    cycles =  0;
  }
  else if (*pin & bitmask) { 
    cycles =  1;
  }
  else if (*pin & bitmask) { 
    cycles =  2;
  }
  else if (*pin & bitmask) { 
    cycles =  3;
  }
  else if (*pin & bitmask) { 
    cycles =  4;
  }
  else if (*pin & bitmask) { 
    cycles =  5;
  }
  else if (*pin & bitmask) { 
    cycles =  6;
  }
  else if (*pin & bitmask) { 
    cycles =  7;
  }
  else if (*pin & bitmask) { 
    cycles =  8;
  }
  else if (*pin & bitmask) { 
    cycles =  9;
  }
  else if (*pin & bitmask) { 
    cycles = 10;
  }
  else if (*pin & bitmask) { 
    cycles = 11;
  }
  else if (*pin & bitmask) { 
    cycles = 12;
  }
  else if (*pin & bitmask) { 
    cycles = 13;
  }
  else if (*pin & bitmask) { 
    cycles = 14;
  }
  else if (*pin & bitmask) { 
    cycles = 15;
  }
  else if (*pin & bitmask) { 
    cycles = 16;
  }

  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to 
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  *port &= ~(bitmask);
  *ddr  |= bitmask;

  return cycles;
}

