#include "auton.h"

const float WHEEL_CIRCUM = WHEEL_DIAMETER * PI;

void newPID(double _rots, float __Kp, float __Ki, float __Kd) {
  pid_controller::mself = new pid_controller(
      pid_controller::pidTarget, pid_controller::motorGroup, __Kp, __Ki, __Kd);
  pid_controller::pidTarget = _rots;
  pid_controller::motorGroup = &driveTrain;
  vex::thread pid1 = vex::thread(&pid_controller::init);
  vex::thread pid2 = vex::thread(&pid_controller::init2);
  vex::thread pid3 = vex::thread(&pid_controller::init3);
  pid3.join();
  delete pid_controller::mself;
}

void driveInches(double inches, vex::brakeType brakeType) {
  double rots = inches / (WHEEL_CIRCUM);
  driveTrain.setStopping(brakeType);
  newPID(rots, 1, 0, 0);
}

void pointTurn(double degrees, vex::brakeType brakeType) {
  double rots = (BOT_WIDTH * PI * (degrees / 360) / WHEEL_CIRCUM);
  driveTrain.setStopping(brakeType);
  if (degrees > 0) {
    rightDT.rotateTo(rots, ROT, -MAX_SPEED, vPCT, false);
    leftDT.rotateTo(rots, ROT, MAX_SPEED, vPCT);
  } else {
    rightDT.rotateTo(rots, ROT, MAX_SPEED, vPCT, false);
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