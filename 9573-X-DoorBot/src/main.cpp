#include "auton.h"
#include "robotConfig.h"
#include "userControl.h"

void pre_auton() {
  driveTrain.setStopping(MOTOR_STOPPING_DRIVE);
  Lift.setMaxTorque(100, PCT);
  Lift.setStopping(HOLD);
  Claw.setMaxTorque(100, PCT);
  Claw.setStopping(COAST);
}

void pre_drive() {
  driveTrain.setStopping(MOTOR_STOPPING_DRIVE);
  Lift.setMaxTorque(100, PCT);
  Lift.setStopping(HOLD);
  Claw.setMaxTorque(100, PCT);
  Claw.setStopping(COAST);
}

void autonomous() {
  // Side as one is left, anything else as right, team as 1 is blue, -1 is red
  int side = 1;
  int team = -1;
  if (side == 1) {
    strafeInches(team * 5.5);
    strafeInches(team * -5.5);
    driveInches(14.5);
    closeClaw();
    liftTo(110);
    pointTurn(team * 90);
    strafeInches(team * 10.8);
    driveInches(11.5);
    openClaw();
    driveInches(-11);
  } else {
    strafeInches(-5.5);
    strafeInches(17.5);
    driveInches(3.5);
    closeClaw();
    liftTo(110);
    driveInches(-6);
    strafeInches(-17.5);
  }
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