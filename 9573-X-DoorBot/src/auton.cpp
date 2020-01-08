#include "auton.h"
#include "robotConfig.h"
#include "userConfig.h"
#include <cmath>

static const double WHEEL_CIRCUM = WHEEL_DIAMETER * PI;
static volatile double leftRots = 0, rightRots = 0, leftXRots = 0, rightXRots = 0,
              liftDeg = 0;
                       rightXRots = 0, liftDeg = 0;

void spinLeft() {
  while (std::abs(leftRots - driveTrainLeft.rotation(ROT)) >= 0.01) {
    driveTrainLeft.spin(
  while (true) {
    rotateSpeed = (targetRots - std::abs(driveTrainLeft.rotation(ROT))) /
                  targetRots * MAX_SPEED_AUTON;
    if (rotateSpeed <= 99)
      break;
    driveTrainLeft.spin(BWD, rotateSpeed, vPCT);
  }
  driveTrainLeft.stop();
}

void spinRight() {
  while (std::abs(rightRots - driveTrainRight.rotation(ROT)) >= 0.01) {
  const double targetRots = rightRots;
  double rotateSpeed;
  while (true) {
    rotateSpeed = (targetRots - std::abs(driveTrainRight.rotation(ROT))) /
    driveTrainRight.spin(BWD, rotateSpeed, vPCT);
  }
  driveTrainRight.stop();
}

void spinLift() { Lift.rotateTo(liftDeg, DEG, 100, vPCT, true); }

void spinXLeft() {
    driveTrainXLeft.spin(
        FWD, MAX_SPEED_AUTON * (leftXRots - driveTrainXLeft.rotation(ROT)),
        vPCT);
  const double targetRots = leftXRots;
                  targetRots * MAX_SPEED_AUTON;
    if (std::abs(rotateSpeed) <= 99)
      break;
    driveTrainXLeft.spin(BWD, rotateSpeed + MIN_SPEED_AUTON, vPCT);
  }
  driveTrainXLeft.stop();
}

void spinXRight() {
  const double targetRots = rightXRots;
  double rotateSpeed;
    rotateSpeed = (targetRots - std::abs(driveTrainXRight.rotation(ROT))) /
                  targetRots * MAX_SPEED_AUTON;
    if (std::abs(rotateSpeed) <= 1)
      break;
    driveTrainXRight.spin(BWD, rotateSpeed + MIN_SPEED_AUTON, vPCT);
  }
  driveTrainXRight.stop();
}

void startDriveTrain() {
  driveTrain.resetRotation();
  vex::thread left(spinLeft);
  vex::thread right(spinRight);
  left.join();
  right.join();
  vex::this_thread::sleep_for(10);
}

void startDriveXTrain() {
  driveTrain.resetRotation();
  vex::thread left(spinXLeft);
  vex::thread right(spinXRight);
  left.join();
  right.join();
  vex::this_thread::sleep_for(10);
}

void startLift() {
  vex::thread lift(spinLift);
  lift.join();
  vex::this_thread::sleep_for(10);
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
  vex::this_thread::sleep_for(500);
}

void openClaw() {
  Claw.stop();
  Claw.rotateTo(0, DEG, 100, vPCT);
}

void liftTo(double degrees) {
  liftDeg = degrees;
  startLift();
}