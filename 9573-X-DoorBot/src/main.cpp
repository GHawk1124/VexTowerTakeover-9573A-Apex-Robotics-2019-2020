#include "robotConfig.h"
#include "userControl.h"
#include "auton.h"

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
  strafeInches(24);
  /*pointTurn(180);
  driveInches(24);*/
}

void usercontrol() {
  pre_drive();

  autonomous();
  
  Threads::t_Drive::tc_Drive();
  //Threads::t_Claw::tc_Claw();
  //Threads::t_Lift::tc_Lift();

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
  return 0;
}