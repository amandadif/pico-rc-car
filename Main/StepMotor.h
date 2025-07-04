#include <Arduino.h>
#ifndef STEPMOTOR_H
#define STEPMOTOR_H


class StepMotor {
  private:
    int outports[4];
    void moveOneStep(bool dir);

  public:
    StepMotor();      // Constructor
    void moveSteps(bool dir, int steps, byte ms) ;
};

#endif