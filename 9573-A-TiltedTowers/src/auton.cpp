#include "auton.h"

const float WHEEL_CIRCUM = WHEEL_DIAMETER * PI;

void driveInches(double inches, vex::brakeType brakeType) {
  double rots = inches / (WHEEL_CIRCUM);
  pid_controller pid = pid_controller(rots, &driveTrain);
  driveTrain.setStopping(brakeType);
  pid.entry();
  //vex::thread pid1 = vex::thread(&pid.entry);
}

void pointTurn(double degrees, vex::brakeType brakeType) {
  double rots = (BOT_WIDTH * PI * (degrees / 360) / WHEEL_CIRCUM);
  driveTrain.setStopping(brakeType);
  if (degrees > 0) {
    rightDT.rotateFor(rots, ROT, -MAX_SPEED, vPCT);
    leftDT.rotateTo(rots, ROT, MAX_SPEED, vPCT);
  } else {
    rightDT.rotateFor(rots, ROT, MAX_SPEED, vPCT);
    leftDT.rotateTo(rots, ROT, -MAX_SPEED, vPCT);
  }
}

void fSwingTurn(double degrees, vex::brakeType brakeType) {
  double rots = (2 * BOT_WIDTH * PI * (degrees / 360) / WHEEL_CIRCUM);
  if (degrees > 0) {
    leftDT.setStopping(brakeType);
    leftDT.rotateTo(rots, ROT, MAX_SPEED, vPCT);
  } else {
    rightDT.setStopping(brakeType);
    rightDT.rotateTo(rots, ROT, MAX_SPEED, vPCT);
  }
}

void bSwingTurn(double degrees, vex::brakeType brakeType) {
  double rots = (2 * BOT_WIDTH * PI * (degrees / 360) / WHEEL_CIRCUM);
  if (degrees > 0) {
    rightDT.setStopping(brakeType);
    rightDT.rotateTo(rots, ROT, -MAX_SPEED, vPCT);
  } else {
    leftDT.setStopping(brakeType);
    leftDT.rotateTo(rots, ROT, -MAX_SPEED, vPCT);
  }
}