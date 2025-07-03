#include <Arduino.h>
#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor()
  : sonar(trigPin, echoPin, maxDistance) // initialize NewPing object
{
  // Nothing else needed here — NewPing handles pinMode internally
}

float UltrasonicSensor::getDistance() {
  float distance = sonar.ping_cm(); // returns distance in cm, non-blocking

  if (distance == 0) {
    Serial.println("No echo");
    return -1; // or return 0 if you prefer
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}


