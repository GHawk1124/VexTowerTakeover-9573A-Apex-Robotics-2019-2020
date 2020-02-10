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
  int side = 1;
  int team = 1;
  if (side == 1) {
    strafeInches(team *6.5);
    strafeInches(team * -6.5);
    driveInches(8);
    closeClaw();
    liftTo(90);
    driveInches(3);
    vex::wait(.1, vex::seconds);
    openClaw();
    liftTo(-15);
    driveInches(2.75);
    vex::wait(.1, vex::seconds);
    closeClaw();
    vex::wait(.1, vex::seconds);
    liftTo(140);
    pointTurn(team * 90);
    strafeInches(team * 15.25);
    pointTurn(team * 35);
    driveInches(2.5);
    liftTo(90);
    openClaw();
    driveInches(-5);
  } else {
    strafeInches(team * -5);
    driveInches(3);
    closeClaw();
    liftTo(110);
    strafeInches(team * 16.);
    openClaw();
    liftTo(-10);
    driveInches(1);
    closeClaw();
    liftTo(130);
    pointTurn(team * -90);
    strafeInches(team * -4.5);
    driveInches(33);
    openClaw();
    driveInches(-11);
  }
}

void usercontrol() {
  pre_drive();

  Threads::t_Drive::tc_Drive();
  //Threads::t_Claw::tc_Claw();
  //Threads::t_Lift::tc_Lift();
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