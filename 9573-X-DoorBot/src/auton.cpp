#include "auton.h"
#include "robotConfig.h"
#include "userConfig.h"
#include <cmath>

/*static const double WHEEL_CIRCUM = WHEEL_DIAMETER * PI;
static const int MAX_SPEED_AUTON = 100 - MIN_SPEED_AUTON;
static volatile double leftRots = 0, rightRots = 0, leftXRots = 0,
                       rightXRots = 0, liftDeg = 0;

void spinLeft() {
  driveTrainLeft.resetRotation();
  double targetRots = leftRots;
  double rotateSpeed;
  while (true) {
    rotateSpeed = (targetRots - std::abs(driveTrainLeft.rotation(ROT))) /
                      targetRots * MAX_SPEED_AUTON +
                  MIN_SPEED_AUTON;
    if (std::abs(targetRots - driveTrainLeft.rotation(ROT)) <= 0.09) {
      break;
    }
    driveTrainLeft.spin(targetRots > 0 ? FWD : BWD, rotateSpeed, vPCT);
  }
  driveTrainLeft.stop();
  driveTrainLeft.resetRotation();
  delete &targetRots;
}

void spinRight() {
  driveTrainRight.resetRotation();
  double targetRots = rightRots;
  double rotateSpeed;
  while (true) {
    rotateSpeed = (targetRots - std::abs(driveTrainRight.rotation(ROT))) /
                      targetRots * MAX_SPEED_AUTON +
                  MIN_SPEED_AUTON;
    if (std::abs(targetRots - driveTrainRight.rotation(ROT)) <= 0.09) {
      break;
    }
    driveTrainRight.spin(targetRots > 0 ? FWD : BWD, rotateSpeed, vPCT);
  }
  driveTrainRight.stop();
  driveTrainRight.resetRotation();
  delete &targetRots;
}

void spinLift() { Lift.rotateTo(liftDeg, DEG, 100, vPCT, true); }

void spinXLeft() {
  driveTrainXLeft.resetRotation();
  double targetRots = leftXRots;
  double rotateSpeed;
  while (true) {
    rotateSpeed = (targetRots - std::abs(driveTrainXLeft.rotation(ROT))) /
                      targetRots * MAX_SPEED_AUTON +
                  MIN_SPEED_AUTON;
    if (std::abs(targetRots - driveTrainXLeft.rotation(ROT)) <= 0.09) {
      break;
    }
    driveTrainXLeft.spin(targetRots > 0 ? FWD : BWD, rotateSpeed, vPCT);
  }
  driveTrainXLeft.stop();
  driveTrainXLeft.resetRotation();
  delete &targetRots;
}

void spinXRight() {
  driveTrainXRight.resetRotation();
  double targetRots = rightXRots;
  double rotateSpeed;
  while (true) {
    rotateSpeed = (targetRots - std::abs(driveTrainXRight.rotation(ROT))) /
                      targetRots * MAX_SPEED_AUTON +
                  MIN_SPEED_AUTON;
    if (std::abs(targetRots - driveTrainXRight.rotation(ROT)) <= 0.09) {
      break;
    }
    driveTrainXRight.spin(targetRots > 0 ? FWD : BWD, rotateSpeed, vPCT);
  }
  driveTrainXRight.stop();
  driveTrainXRight.resetRotation();
  delete &targetRots;
}

void startDriveTrain() {
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
  double rots = (BOT_WIDTH * PI * (degrees / 360) / WHEEL_CIRCUM) * 1.5;
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
Don't use me.
*/

void driveTo(double xInches, double yInches) {
  double rots = sqrt((xInches * xInches) + (yInches * yInches)) / WHEEL_CIRCUM;
  double angle = atan2(yInches, xInches);
  RF.spin(FWD, sin(angle - PI / 4) * 100, vPCT);
  LB.spin(FWD, sin(angle - PI / 4) * 100, vPCT);
  LF.spin(FWD, sin(angle + PI / 4) * 100, vPCT);
  RB.spin(FWD, sin(angle + PI / 4) * 100, vPCT);
  while (fabs(((RF.rotation(ROT) + LF.rotation(ROT) + RB.rotation(ROT) +
                LB.rotation(ROT)) /
               4) -
              rots) <= 0.01) {
  }
  driveTrain.stop(MOTOR_STOPPING_AUTON);
}