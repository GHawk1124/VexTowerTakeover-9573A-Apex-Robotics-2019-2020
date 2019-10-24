#include "auton.h"

const float WHEEL_CIRCUM = WHEEL_DIAMETER * PI;


void driveInches(double inches, vex::brakeType brakeType) {
  double rots = inches / (WHEEL_CIRCUM);
  DriveTrain.setStopping(brakeType);
  newPID(rots, &DriveTrain, 1, 0, 0);
}

void pointTurn(double degrees, vex::brakeType brakeType) {
  double rots = (BOT_WIDTH * PI * (degrees / 360) / WHEEL_CIRCUM);
  DriveTrain.setStopping(brakeType);
  if (degrees > 0) {
    DriveTrainRight.rotateTo(rots, ROT, -MAX_SPEED, vPCT, false);
    DriveTrainLeft.rotateTo(rots, ROT, MAX_SPEED, vPCT);
  } else {
    DriveTrainRight.rotateTo(rots, ROT, MAX_SPEED, vPCT, false);
    DriveTrainLeft.rotateTo(rots, ROT, -MAX_SPEED, vPCT);
  }
}

void fSwingTurn(double degrees, vex::brakeType brakeType) {
  double rots = (2 * BOT_WIDTH * PI * (degrees / 360) / WHEEL_CIRCUM);
  if (degrees > 0) {
    DriveTrainLeft.setStopping(brakeType);
    DriveTrainLeft.rotateTo(rots, ROT, MAX_SPEED, vPCT);
  } else {
    DriveTrainRight.setStopping(brakeType);
    DriveTrainRight.rotateTo(rots, ROT, MAX_SPEED, vPCT);
  }
}

void bSwingTurn(double degrees, vex::brakeType brakeType) {
  double rots = (2 * BOT_WIDTH * PI * (degrees / 360) / WHEEL_CIRCUM);
  if (degrees > 0) {
    DriveTrainRight.setStopping(brakeType);
    DriveTrainRight.rotateTo(rots, ROT, -MAX_SPEED, vPCT);
  } else {
    DriveTrainLeft.setStopping(brakeType);
    DriveTrainLeft.rotateTo(rots, ROT, -MAX_SPEED, vPCT);
  }
}