#include "UltrasonicSensor.h"
#include <WiFi.h>
#include <Servo.h>
#include "WebApp.h"
#include "StepMotor.h"
#include "DriveControl.h"

WebApp web;
Servo servo;  // Steering
Servo esc;      // Motor
StepMotor stepMotor;
DriveControl driveController(esc, servo);
UltrasonicSensor US;

bool pathClear;
int lastPrint;

void setup() {
  //Allow for serial read- 115200 baud
  Serial.begin(115200);

  pinMode(18, INPUT);
  //Assign pins
  servo.attach(14);
  esc.attach(15);

  //Connect WiFi
  web.connectToWifi();
  
  // Initialize to neutral
  servo.writeMicroseconds(1500);
  esc.writeMicroseconds(1500);
  delay(2000);

}

void loop() {
  if(digitalRead(18) != lastPrint) {
    Serial.print(digitalRead(18));
    lastPrint = digitalRead(18);
  }
  else{}
  static unsigned long lastPing = 0;
  if (millis() - lastPing > 150) {
    pathClear = US.getPathClearStatus();
    lastPing = millis();
  }
  driveController.emergencyOverride(pathClear);
  web.serveClient(driveController, pathClear);
}
