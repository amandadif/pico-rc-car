#include <Arduino.h>
#include "StepMotor.h"

// Connect the port of the stepper motor driver
int outPorts[] = {13, 12, 11, 10};

StepMotor:: StepMotor() {
// set pins to output
  for (int i = 0; i < 4; i++) {
    pinMode(outPorts[i], OUTPUT);
  }
}
//Suggestion: the motor turns precisely when the ms range is between 3 and 20
void StepMotor :: moveSteps(bool dir, int steps, byte ms) {
  for (unsigned long i = 0; i < steps; i++) {
    moveOneStep(dir); // Rotate a step
    delay(constrain(ms,3,20)); // Control the speed
  }
}

void StepMotor :: moveOneStep(bool dir) {
  // Define a variable, use four low bit to indicate the state of port
  static byte out = 0x01;
  // Decide the shift direction according to the rotation direction
  if (dir) { // ring shift left
    out != 0x08 ? out = out << 1 : out = 0x01;
  }
  else { // ring shift right
    out != 0x01 ? out = out >> 1 : out = 0x08;
  }
  // Output singal to each port
  for (int i = 0; i < 4; i++) {
    digitalWrite(outPorts[i], (out & (0x01 << i)) ? HIGH : LOW);
  }
}