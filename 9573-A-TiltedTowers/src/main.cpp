#include "auton.h"
#include "robotConfig.h"
#include "userControl.h"


void pre_auton() {
  driveTrain.setMaxTorque(100, PCT);
  driveTrain.setStopping(MOTOR_STOPPING_AUTON);
  Lift.setMaxTorque(100, PCT);
  Lift.setStopping(MOTOR_STOPPING_AUTON);
  Intake.setMaxTorque(100, PCT);
  Intake.setStopping(MOTOR_STOPPING_AUTON);
}

void pre_drive() {
  driveTrain.setMaxTorque(100, PCT);
  driveTrain.setStopping(MOTOR_STOPPING_DRIVE);
  Lift.setMaxTorque(100, PCT);
  Lift.setStopping(MOTOR_STOPPING_DRIVE);
  Intake.setMaxTorque(100, PCT);
  Intake.setStopping(MOTOR_STOPPING_DRIVE);
}

// TODO:
void autonomous() {
  /*driveInches(12, BRAKE);
  vex::this_thread::sleep_for(1000);
  pointTurn(90);
  vex::this_thread::sleep_for(1000);
  fSwingTurn(90, BRAKE);*/
}

void usercontrol() {
  pre_drive();

  Threads::t_Drive::tc_Drive();
  Threads::t_Intake::tc_Intake();
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