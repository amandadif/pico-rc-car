#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include <NewPing.h>

class UltrasonicSensor {
  private:
    static const uint8_t trigPin = 17;
    static const uint8_t echoPin = 16;
    static const unsigned int maxDistance = 400; // in cm
    NewPing sonar;
    float lastDistance;

  public:
    UltrasonicSensor();      // Constructor
    bool getPathClearStatus();     // Return distance in cm
};

#endif
