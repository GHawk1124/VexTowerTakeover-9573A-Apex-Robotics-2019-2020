#include "auton.h"
#include "robotConfig.h"
#include "userControl.h"

void pre_auton() {
  Claw.resetRotation();
  Lift.resetRotation();
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
  Claw.resetRotation();
  // Side as one is left, anything else as right, team as 1 is blue, -1 is red
  int side = 0;
  int team = 1;
  if (side == 1) {
    strafeInches(team * 5.5);
    strafeInches(team * -5);
    driveInches(13.5);
    closeClaw();
    liftTo(100);
    driveInches(4.7);
    openClaw();
    liftTo(-10);
    driveInches(0.5);
    closeClaw();
    liftTo(120);
    pointTurn(team * 90);
    strafeInches(team * 13);
    driveInches(15);
    openClaw();
    driveInches(-11);
  } else {
    strafeInches(team * -5);
    strafeInches(team * 15.5);
    driveInches(1);
    closeClaw();
    liftTo(110);
    driveInches(-2);
    strafeInches(team * - 15.5);
    openClaw();
    liftTo(-10);
    closeClaw();
  }
}

void usercontrol() {
  // autonomous();
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