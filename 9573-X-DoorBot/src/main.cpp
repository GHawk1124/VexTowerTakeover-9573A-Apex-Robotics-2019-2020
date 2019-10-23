
#include "auton.h"
#include "robotConfig.h"
#include "userControl.h"

void pre_auton() {
  driveTrain.setMaxTorque(100, PCT);
  driveTrain.setStopping(MOTOR_STOPPING_AUTON);
  Lift.setMaxTorque(100, PCT);
  Lift.setStopping(MOTOR_STOPPING_AUTON);
  Claw.setMaxTorque(100, PCT);
  Claw.setStopping(MOTOR_STOPPING_AUTON);
}

void pre_drive() {
  driveTrain.setMaxTorque(100, PCT);
  driveTrain.setStopping(MOTOR_STOPPING_DRIVE);
  Lift.setMaxTorque(100, PCT);
  Lift.setStopping(MOTOR_STOPPING_DRIVE);
  Claw.setMaxTorque(100, PCT);
  Claw.setStopping(MOTOR_STOPPING_DRIVE);
}

void autonomous() {
  driveInches(12, COAST);
  vex::this_thread::sleep_for(1000);
  pointTurn(90);
  vex::this_thread::sleep_for(1000);
}

void usercontrol() {
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
}