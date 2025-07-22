#ifndef DRIVECONTROL_H
#define DRIVECONTROL_H

#include <Servo.h>
class DriveControl {
  Servo& esc;
  Servo& servo;

public:
  DriveControl(Servo& escMotor, Servo& steerServo);
  void handleDriveCommand(int val, bool pathClear);
  void handleSteeringCommand(int val);
  int lastESCVal = 1500;  // Neutral
  bool lastPathClear = true;
  void emergencyOverride(bool currentPathClear);
};

#endif


