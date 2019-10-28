
#include "auton.h"
#include "robotConfig.h"
#include "userControl.h"

void pre_auton() {
  DriveTrain.setMaxTorque(100, PCT);
  DriveTrain.setStopping(MOTOR_STOPPING_AUTON);
  Lift.setMaxTorque(100, PCT);
  Lift.setStopping(MOTOR_STOPPING_AUTON);
  Claw.setMaxTorque(100, PCT);
  Claw.setStopping(COAST);
}

void pre_drive() {
  DriveTrain.setMaxTorque(100, PCT);
  DriveTrain.setStopping(MOTOR_STOPPING_DRIVE);
  Lift.setMaxTorque(100, PCT);
  Lift.setStopping(HOLD);
  Claw.setMaxTorque(100, PCT);
  Claw.setStopping(COAST);
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
    /*if (Controller.RESET()) {
      Lift.stop(COAST);
      Threads::t_Drive::mSelf = nullptr;
      Threads::t_Claw::mSelf = nullptr;
      Threads::t_Lift::mSelf = nullptr;
      vex::this_thread::sleep_for(3000);
      Threads::t_Drive::tc_Drive();
      Threads::t_Claw::tc_Claw();
      Threads::t_Lift::tc_Lift();
    }*/
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