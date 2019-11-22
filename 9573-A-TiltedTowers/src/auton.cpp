#include "auton.h"
#include <cmath>

const float WHEEL_CIRCUM = WHEEL_DIAMETER * PI;

void driveInches(double inches, int speed, bool intake, int timeToSleep,
                 vex::brakeType brakeType) {
  driveTrain.setStopping(brakeType);
  Intake.spin(FWD, intake * MAX_SPEED, vPCT);
  driveTrain.driveFor(FWD, inches, vex::distanceUnits::in, speed, vPCT, true);
  Intake.stop();
  vex::this_thread::sleep_for(timeToSleep);
}

void newDriveInches(double inches, bool intake, int timeToSleep,
                    vex::brakeType brakeType) {
  double rots = inches / WHEEL_CIRCUM;
  newPID(rots, 1, 0, 0);
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
  double rots = (2 * BOT_WIDTH * PI * (std::abs(degrees) / 360) / WHEEL_CIRCUM);
  if (degrees > 0) {
    leftDT.setStopping(brakeType);
    rightDT.setStopping(HOLD);
    leftDT.rotateTo(rots, ROT, MAX_SPEED, vPCT, true);
    rightDT.setStopping(brakeType);
  } else {
    rightDT.setStopping(brakeType);
    leftDT.setStopping(HOLD);
    rightDT.rotateTo(rots, ROT, MAX_SPEED, vPCT, true);
    leftDT.setStopping(brakeType);
  }
}

void bSwingTurn(double degrees, vex::brakeType brakeType) {
  double rots = (2 * BOT_WIDTH * PI * (std::abs(degrees) / 360) / WHEEL_CIRCUM);
  if (degrees > 0) {
    rightDT.setStopping(brakeType);
    leftDT.setStopping(HOLD);
    rightDT.rotateTo(rots, ROT, -MAX_SPEED, vPCT, true);
    rightDT.setStopping(brakeType);
  } else {
    leftDT.setStopping(brakeType);
    rightDT.setStopping(HOLD);
    leftDT.rotateTo(rots, ROT, -MAX_SPEED, vPCT, true);
    rightDT.setStopping(brakeType);
  }
}

void Liftf(vex::directionType dir, float ltime) {
  Lift.spin(dir, LIFT_SPEED, vPCT);
  vex::this_thread::sleep_for(ltime);
  Lift.stop();
}

void Intakef(vex::directionType dir, float ltime) {
  Intake.spin(dir, INTAKE_SPEED, vPCT);
  vex::this_thread::sleep_for(ltime);
  Intake.stop();
}