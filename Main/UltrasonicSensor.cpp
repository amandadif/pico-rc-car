#include <Arduino.h>
#include "UltrasonicSensor.h"
#include "PathStatusLED.h"

PathStatusLED LEDindicator;
float lastDistance;
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

  if(distance != lastDistance){
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  lastDistance = distance;
  LEDindicator.activateStatusLED(pathClearStatus);
  return pathClearStatus;
}


