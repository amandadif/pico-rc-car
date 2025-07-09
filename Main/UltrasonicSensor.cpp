#include <Arduino.h>
#include "UltrasonicSensor.h"
#include "PathStatusLED.h"

PathStatusLED LEDindicator;
UltrasonicSensor::UltrasonicSensor()
  : sonar(trigPin, echoPin, maxDistance) // initialize NewPing object
{
  // Nothing else needed here — NewPing handles pinMode internally
}

bool UltrasonicSensor::getPathClearStatus() {
  bool pathClearStatus;
  float distance = sonar.ping_cm(); // returns distance in cm, non-blocking

  if (distance == 0) {
    pathClearStatus = false;
    return pathClearStatus;
  }
  else if(distance <= 30) {
    Serial.println("STOP");
    pathClearStatus = false;
    LEDindicator.activateStatusLED(pathClearStatus);
    return pathClearStatus;
  }
  else {
    pathClearStatus = true;
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  LEDindicator.activateStatusLED(pathClearStatus);
  return pathClearStatus;
}


