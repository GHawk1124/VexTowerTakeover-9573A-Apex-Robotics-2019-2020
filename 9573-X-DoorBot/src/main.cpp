#include "auton.h"
#include "robotConfig.h"
#include "userControl.h"


void pre_auton() {
  RF.setStopping(MOTOR_STOPPING_DRIVE);
  LF.setStopping(MOTOR_STOPPING_DRIVE);
  RB.setStopping(MOTOR_STOPPING_DRIVE);
  LB.setStopping(MOTOR_STOPPING_DRIVE);
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
  driveInches(39);
  driveInches(-15);
  strafeInches(-6.5);
  pointTurn(-90);
  driveInches(7);
  closeClaw();
  driveInches(22);
  pointTurn(-90);
  driveInches(11);
  // Not exact
  //liftTo(180);
  driveInches(2);
  openClaw();
  driveInches(-12);
}

void usercontrol() {
  //autonomous();
  //pre_auton();
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