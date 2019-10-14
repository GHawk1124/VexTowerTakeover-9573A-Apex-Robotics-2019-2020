#include "auton.h"

void driveInches(double inches, vex::brakeType breakType) {
  double rots = inches / (WHEEL_CIRCUM);
  driveTrain.setStopping(breakType);
  driveTrain.rotateTo(rots, ROT, MAX_SPEED, vPCT);
}