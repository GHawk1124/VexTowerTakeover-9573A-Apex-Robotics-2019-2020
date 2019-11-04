#include "auton.h"
#include "robotConfig.h"
#include "userConfig.h"
#include <cmath>

static const double WHEEL_CIRCUM = WHEEL_DIAMETER * PI;
static double leftRots = 0, rightRots = 0, leftXRots = 0, rightXRots = 0;

void spinLeft() {
  while (std::abs(leftRots - driveTrainLeft.rotation(ROT)) >= 0.01) {
    driveTrainLeft.spin(FWD, MAX_SPEED_AUTON * (leftRots - driveTrainLeft.rotation(ROT)), vPCT);
  }
}

  newPID(rots, &DriveTrain, 1, 0, 0);
void spinRight() {
  while (std::abs(rightRots - driveTrainRight.rotation(ROT)) >= 0.01) {
    driveTrainRight.spin(FWD, MAX_SPEED_AUTON * (rightRots - driveTrainRight.rotation(ROT)), vPCT);
}

void spinXLeft() {
  while (std::abs(leftXRots - driveTrainXLeft.rotation(ROT)) >= 0.01) {
    driveTrainXLeft.spin(FWD, MAX_SPEED_AUTON * (leftXRots - driveTrainXLeft.rotation(ROT)), vPCT);
  }
}


void spinXRight() {
  while (std::abs(rightXRots - driveTrainXRight.rotation(ROT)) >= 0.01) {
    driveTrainXRight.spin(FWD, MAX_SPEED_AUTON * (rightXRots - driveTrainXRight.rotation(ROT)), vPCT);
  }
}

void startDriveTrain() {
  driveTrain.resetRotation();
  vex::thread left (spinLeft);
  vex::thread right (spinRight);
  left.join();
  right.join();
}

void startDriveXTrain() {
  driveTrain.resetRotation();
  vex::thread left (spinXLeft);
  vex::thread right (spinXRight);
  left.join();
  right.join();
}

void driveInches(double inches) {
  leftRots = rightRots = -inches / WHEEL_CIRCUM;
  startDriveTrain();
}

void strafeInches(double inches) {
  leftXRots = 2 * inches / WHEEL_CIRCUM;
  rightXRots = -leftXRots;
  startDriveXTrain());
}

void pointTurn(double degrees) {
  double rots = (2 * BOT_WIDTH * PI * (degrees / 360) / WHEEL_CIRCUM);
  leftRots = rots;
  rightRots = -rots;
  startDriveTrain();
}