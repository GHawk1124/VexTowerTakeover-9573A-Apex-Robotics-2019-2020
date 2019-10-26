#include "auton.h"

const float WHEEL_CIRCUM = WHEEL_DIAMETER * PI;

void driveInches(double inches, int speed, vex::brakeType brakeType) {
  driveTrain.resetRotation();
  double rots = inches / (WHEEL_CIRCUM);
  //driveTrain.setStopping(brakeType);
  Intake.spin(FWD, MAX_SPEED, vPCT);
  driveTrain.rotateTo(rots, ROT, speed, vPCT, true);
  Intake.stop();
}

void pointTurn(double degrees, vex::brakeType brakeType) {
  double rots = (BOT_WIDTH * PI * (degrees / 360) / WHEEL_CIRCUM);
  driveTrain.setStopping(brakeType);
  if (degrees > 0) {
    rightDT.rotateTo(rots, ROT, -MAX_SPEED, vPCT, false);
    leftDT.rotateTo(rots, ROT, MAX_SPEED, vPCT, true);
  } else {
    rightDT.rotateTo(rots, ROT, MAX_SPEED, vPCT, false);
    leftDT.rotateTo(rots, ROT, -MAX_SPEED, vPCT, true);
  }
}

void fSwingTurn(double degrees, vex::brakeType brakeType) {
  double rots = (2 * BOT_WIDTH * PI * (degrees / 360) / WHEEL_CIRCUM);
  if (degrees > 0) {
    leftDT.setStopping(brakeType);
    leftDT.rotateTo(rots, ROT, MAX_SPEED, vPCT, true);
  } else {
    rightDT.setStopping(brakeType);
    rightDT.rotateTo(rots, ROT, MAX_SPEED, vPCT, true);
  }
}

void bSwingTurn(double degrees, vex::brakeType brakeType) {
  double rots = (2 * BOT_WIDTH * PI * (degrees / 360) / WHEEL_CIRCUM);
  if (degrees > 0) {
    rightDT.setStopping(brakeType);
    rightDT.rotateTo(rots, ROT, -MAX_SPEED, vPCT, true);
  } else {
    leftDT.setStopping(brakeType);
    leftDT.rotateTo(rots, ROT, -MAX_SPEED, vPCT, true);
  }
}