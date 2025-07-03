#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include <NewPing.h>

class UltrasonicSensor {
  private:
    static const uint8_t trigPin = 19;
    static const uint8_t echoPin = 18;
    static const unsigned int maxDistance = 400; // in cm
    NewPing sonar;

  public:
    UltrasonicSensor();      // Constructor
    float getDistance();     // Return distance in cm
};

#endif
