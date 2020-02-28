#include "auton.h"
#include "robotConfig.h"
#include "userConfig.h"
#include <cmath>

void driveInches(double inches) {
  driveTrain.resetRotation();
  double rots = inches / WHEEL_CIRCUM / 10;
  double speed;
  while ((fabs(rots) - (fabs(RF.rotation(ROT)) + fabs(LB.rotation(ROT))) / 2) >=
         0.01) {
    speed =
        (rots - (fabs(RF.rotation(ROT)) + fabs(LB.rotation(ROT))) / 2) * 90 +
        10;
    RF.spin(FWD, speed / sqrt(2), vPCT);
    LB.spin(FWD, speed / sqrt(2), vPCT);
    LF.spin(FWD, speed / sqrt(2), vPCT);
    RB.spin(FWD, speed / sqrt(2), vPCT);
  }
  driveTrain.stop(MOTOR_STOPPING_AUTON);
  vex::this_thread::sleep_for(5);
}

void strafeInches(double inches) {
  driveTrain.resetRotation();
  double rots = inches / WHEEL_CIRCUM / 7.917;
  double speed;
  while ((fabs(rots) - (fabs(RF.rotation(ROT)) + fabs(LB.rotation(ROT))) / 2) >=
         0.01) {
    speed =
        (rots - (fabs(RF.rotation(ROT)) + fabs(LB.rotation(ROT))) / 2) * 90 +
        10;
    RF.spin(FWD, -sqrt(3) / 2 * speed, vPCT);
    LB.spin(FWD, -sqrt(3) / 2 * speed, vPCT);
    LF.spin(FWD, sqrt(3) / 2 * speed, vPCT);
    RB.spin(FWD, sqrt(3) / 2 * speed, vPCT);
    vex::this_thread::sleep_for(5);
  }
  driveTrain.stop(MOTOR_STOPPING_AUTON);
}

void pointTurn(double degrees) {
  driveTrain.resetRotation();
  double rots = (BOT_WIDTH * PI * (degrees / 360)) / WHEEL_CIRCUM / 5;
  double leftSpeed, rightSpeed;
  while ((fabs(rots) - (fabs(RF.rotation(ROT)) + fabs(RB.rotation(ROT))) / 2) >=
         0.01) {
    leftSpeed =
        (rots - (fabs(RF.rotation(ROT)) + fabs(RB.rotation(ROT))) / 2) *
            90 +
        10;
    rightSpeed = -leftSpeed;
    RF.spin(FWD, rightSpeed, vPCT);
    LB.spin(FWD, leftSpeed, vPCT);
    LF.spin(FWD, leftSpeed, vPCT);
    RB.spin(FWD, rightSpeed, vPCT);
    vex::this_thread::sleep_for(5);
  }
  driveTrain.stop(MOTOR_STOPPING_AUTON);
}

void closeClaw() {
  ClawLeft.rotateTo(-540, DEG, 100, vPCT, false);
  ClawRight.rotateTo(-540, DEG, 100, vPCT, false);
  vex::this_thread::sleep_for(1000);
}

void openClaw() {
  ClawLeft.rotateTo(-360, DEG, 100, vPCT, false);
  ClawRight.rotateTo(-360, DEG, 100, vPCT, true);
}

void liftTo(double degrees) { Lift.rotateTo(degrees, DEG, 100, vPCT, true); }