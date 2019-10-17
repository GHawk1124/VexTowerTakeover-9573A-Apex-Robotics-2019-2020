#include "auton.h"

// TODO:
//    Rotate approaches target (Don't use MAX_SPEED)
//    Use threading to increase sensor accuracy

void driveInches(double inches, vex::brakeType brakeType) {
  double rots = inches / (WHEEL_CIRCUM);
  driveTrain.setStopping(brakeType);
  driveTrain.rotateTo(rots, ROT, MAX_SPEED, vPCT);
}

void pointTurn(double degrees, vex::brakeType brakeType) {
  double rots = degrees;
  driveTrain.setStopping(brakeType);
  if (degrees > 0) {
    RF.rotateTo(rots, ROT, -MAX_SPEED, vPCT);
    LF.rotateTo(rots, ROT, MAX_SPEED, vPCT);
  } else {
    RF.rotateTo(rots, ROT, MAX_SPEED, vPCT);
    LF.rotateTo(rots, ROT, -MAX_SPEED, vPCT);
  }
}

void fSwingTurn(double degrees, vex::brakeType brakeType) {
  double rots = (2 * BOT_WIDTH * PI * (degrees / 360) / WHEEL_CIRCUM);
  if (degrees > 0) {
    LF.setStopping(brakeType);
    LF.rotateTo(rots, ROT, MAX_SPEED, vPCT);
  } else {
    RF.setStopping(brakeType);
    RF.rotateTo(rots, ROT, MAX_SPEED, vPCT);
  }
}

void bSwingTurn(double degrees, vex::brakeType brakeType) {
  double rots = (2 * BOT_WIDTH * PI * (degrees / 360) / WHEEL_CIRCUM);
  if (degrees > 0) {
    RF.setStopping(brakeType);
    RF.rotateTo(rots, ROT, -MAX_SPEED, vPCT);
  } else {
    LF.setStopping(brakeType);
    LF.rotateTo(rots, ROT, -MAX_SPEED, vPCT);
  }
}