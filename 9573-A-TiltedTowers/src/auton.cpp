#include "auton.h"

void driveInches(double inches, vex::brakeType brakeType) {
  double rots = inches / (WHEEL_CIRCUM);
  pid_controller pid = pid_controller(rots, &driveTrain);
  driveTrain.setStopping(brakeType);
  while (pid.pidDrive != 0) {
    driveTrain.spin(FWD, pid.pidDrive, vPCT);
  }
}

void pointTurn(double degrees, vex::brakeType brakeType) {
  double rots = (BOT_WIDTH * PI * (degrees / 360) / WHEEL_CIRCUM);
  driveTrain.setStopping(brakeType);
  if (degrees > 0) {
    RF.rotateFor(rots, ROT, -MAX_SPEED, vPCT);
    LF.rotateTo(rots, ROT, MAX_SPEED, vPCT);
  } else {
    RF.rotateFor(rots, ROT, MAX_SPEED, vPCT);
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