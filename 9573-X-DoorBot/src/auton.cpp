#include "auton.h"

void driveInches(double inches, vex::brakeType brakeType) {
  double rots = inches / (WHEEL_CIRCUM);
  driveTrain.setStopping(brakeType);
  driveTrain.rotateTo(rots, ROT, MAX_SPEED, vPCT);
}

void pointTurn(double degrees, vex::brakeType brakeType) {
  double rots = degrees;
  driveTrain.setStopping(brakeType);
  driveTrain.rotateTo(rots, ROT, MAX_SPEED, vPCT);
}

void swingTurn(double degrees, vex::brakeType brakeType) {
  double rots = ((BOT_WIDTH*PI) / (degrees / 360)) / WHEEL_CIRCUM;
  driveTrain.setStopping(brakeType);
  driveTrain.rotateTo(rots, ROT, MAX_SPEED, vPCT);
}