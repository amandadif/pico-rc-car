#include "DriveControl.h"
#include "UltrasonicSensor.h"

UltrasonicSensor ultraSonicSensor;

DriveControl::DriveControl(Servo& escMotor, Servo& steerServo) 
  : esc(escMotor), servo(steerServo) {}

void DriveControl::handleDriveCommand(int val, bool pathClear) {
  if (val >= 1000 && val <= 2000) {
    lastESCVal = val;
    lastPathClear = pathClear;
    if (val < 1500) {
      esc.writeMicroseconds(1500);
      delay(300);
      esc.writeMicroseconds(val);
      delay(300);
      esc.writeMicroseconds(val);
      Serial.println("REVERSE: " + String(val));
    } else {
      if(pathClear == true) {
        esc.writeMicroseconds(val);
        Serial.println("FORWARD: " + String(val));
      }
      else {
        esc.writeMicroseconds(1500);
        Serial.println("BLOCKED: " + String(1500));
      }
    }
  }
}

void DriveControl::handleSteeringCommand(int val) {
  if (val >= 1000 && val <= 2000) {
    servo.writeMicroseconds(val);
    Serial.println("STEERING: " + String(val));
  }
}

void DriveControl::emergencyOverride(bool currentPathClear) {
  // Only override if path became blocked while moving forward
  if (!currentPathClear && lastESCVal > 1500) {
    esc.writeMicroseconds(1500);
    Serial.println("⛔ Emergency STOP: path blocked while going forward.");
    lastESCVal = 1500; // reset so it doesn't keep stopping
  }
}
