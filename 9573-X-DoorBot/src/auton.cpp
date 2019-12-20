#include "auton.h"
#include "robotConfig.h"
#include "userConfig.h"
#include <cmath>

static const double WHEEL_CIRCUM = WHEEL_DIAMETER * PI;
static volatile double leftRots = 0, rightRots = 0, leftXRots = 0, rightXRots = 0,
              liftDeg = 0;

void spinLeft() {
  while (std::abs(leftRots - driveTrainLeft.rotation(ROT)) >= 0.01) {
    driveTrainLeft.spin(
        FWD, MAX_SPEED_AUTON * (leftRots - driveTrainLeft.rotation(ROT)), vPCT);
  }
  driveTrainLeft.stop();
}

void spinRight() {
  while (std::abs(rightRots - driveTrainRight.rotation(ROT)) >= 0.01) {
    driveTrainRight.spin(
        FWD, MAX_SPEED_AUTON * (rightRots - driveTrainRight.rotation(ROT)),
        vPCT);
  }
  driveTrainRight.stop();
}

void spinLift() { Lift.rotateTo(liftDeg, DEG, 100, vPCT, true); }

void spinXLeft() {
  while (std::abs(leftXRots - driveTrainXLeft.rotation(ROT)) >= 0.01) {
    driveTrainXLeft.spin(
        FWD, MAX_SPEED_AUTON * (leftXRots - driveTrainXLeft.rotation(ROT)),
        vPCT);
  }
  driveTrainXLeft.stop();
}

void spinXRight() {
  while (std::abs(rightXRots - driveTrainXRight.rotation(ROT)) >= 0.01) {
    driveTrainXRight.spin(
        FWD, MAX_SPEED_AUTON * (rightXRots - driveTrainXRight.rotation(ROT)),
        vPCT);
  }
  driveTrainXRight.stop();
}

void startDriveTrain() {
  driveTrain.resetRotation();
  vex::thread left(spinLeft);
  vex::thread right(spinRight);
  right.join();
}

void startDriveXTrain() {
  driveTrain.resetRotation();
  vex::thread left(spinXLeft);
  vex::thread right(spinXRight);
  right.join();
}

void startLift() {
  vex::thread lift(spinLift);
  lift.join();
}

void driveInches(double inches) {
  leftRots = rightRots = -inches / WHEEL_CIRCUM;
  startDriveTrain();
}

void strafeInches(double inches) {
  leftXRots = 2 * inches / WHEEL_CIRCUM;
  rightXRots = -leftXRots;
  startDriveXTrain();
}

void pointTurn(double degrees) {
  double rots = 2 * BOT_WIDTH * PI * (degrees / 360) / WHEEL_CIRCUM;
  leftRots = rots;
  rightRots = -rots;
  startDriveTrain();
}

void closeClaw() {
  Claw.spin(BWD, 100, vPCT);
  vex::this_thread::sleep_for(1000);
}

void openClaw() {
  Claw.stop();
  Claw.rotateTo(0, DEG, 100, vPCT);
}

void liftTo(double degrees) {
  liftDeg = degrees;
  startLift();
  vex::this_thread::sleep_for(100);
}