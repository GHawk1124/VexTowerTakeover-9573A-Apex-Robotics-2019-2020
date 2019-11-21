#include "auton.h"
#include "robotConfig.h"
#include "userControl.h"
#include <cmath>

#define STACK_4

void driveInchesGAR(double inches, int speed, int timeToSleep,
                 vex::brakeType brakeType) {
  driveTrain.setStopping(brakeType);
  dtdriveTrain.driveFor(BWD, inches, vex::distanceUnits::in, speed, vPCT, true);
  vex::this_thread::sleep_for(timeToSleep);
}

void pre_auton() {
  dtdriveTrain.setStopping(BRAKE);
  Lift.setMaxTorque(100, PCT);
  Lift.setStopping(MOTOR_STOPPING_AUTON);
  Claw.setMaxTorque(100, PCT);
  Claw.setStopping(COAST);
}

void pre_drive() {
  RF.setStopping(MOTOR_STOPPING_DRIVE);
  LF.setStopping(MOTOR_STOPPING_DRIVE);
  RB.setStopping(MOTOR_STOPPING_DRIVE);
  LB.setStopping(MOTOR_STOPPING_DRIVE);
  Lift.setMaxTorque(100, PCT);
  Lift.setStopping(HOLD);
  Claw.setMaxTorque(100, PCT);
  Claw.setStopping(COAST);
}

void autonomous() {
#ifdef STACK_4
  Claw.spinFor(.1, SEC, -50, vPCT);
  driveInchesGAR(27.25, 60, 500, BRAKE);
  Claw.spinFor(.7, SEC, -50, vPCT);
  Claw.spin(BWD, 100, vPCT);
  Lift.spinFor(.1, SEC, 50, vPCT);
  Lift.stop(HOLD);
  driveInchesGAR(-27.25, 60, 500, BRAKE);
  vex::this_thread::sleep_for(2000000);
#endif
#ifdef SIMPLE
  driveInchesGAR(12, 30, 300, BRAKE);
  vex::this_thread::sleep_for(300);
  driveInchesGAR(-10, 30, 300, BRAKE);
#endif
}

void usercontrol() {
  pre_auton();
  autonomous();
  pre_drive();

  Threads::t_Drive::tc_Drive();
  Threads::t_Claw::tc_Claw();
  Threads::t_Lift::tc_Lift();

  while (true) {
    vex::this_thread::sleep_for(10);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    vex::task::sleep(100);
  }
  return 0;
}
