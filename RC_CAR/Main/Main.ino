#include "UltrasonicSensor.h"
#include <WiFi.h>
#include <Servo.h>
#include "WebApp.h"

WebApp web;
UltrasonicSensor distanceSensor;
Servo servo;  // Steering
Servo esc;      // Motor

void setup() {
  //Allow for serial read- 115200 baud
  Serial.begin(115200);

  //Assign pins
  servo.attach(28);
  esc.attach(15);
  
  //Connect WiFi
  web.connectToWifi();
  
  // Initialize to neutral
  servo.writeMicroseconds(1500);
  esc.writeMicroseconds(1500);
  delay(2000);

}

void loop() {
  //Listen and send commands through the web app
  web.sendServoCommand(servo, esc);
  distanceSensor.getDistance();
}
