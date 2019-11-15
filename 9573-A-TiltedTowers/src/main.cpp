#include "auton.h"
#include "robotConfig.h"
#include "userControl.h"

#define LEFT_TURN

void pre_auton() {
  driveTrain.setStopping(MOTOR_STOPPING_AUTON);
  Lift.setMaxTorque(100, PCT);
  Lift.setStopping(MOTOR_STOPPING_AUTON);
  Intake.setMaxTorque(100, PCT);
  Intake.setStopping(MOTOR_STOPPING_AUTON);
}

void pre_drive() {
  driveTrain.setStopping(MOTOR_STOPPING_DRIVE);
  Lift.setMaxTorque(100, PCT);
  Lift.setStopping(MOTOR_STOPPING_DRIVE);
  Intake.setMaxTorque(100, PCT);
  Intake.setStopping(MOTOR_STOPPING_DRIVE);
}

void autonomous() {
#ifdef LEFT_TURN
  driveInches(35, 20, true, 500, BRAKE);
  driveInches(-22.5, 40, true, 200, BRAKE);
  Intake.spin(FWD, 10, vPCT);
  driveTrain.turnFor(LEFT, 116, DEG);
  Intake.stop();
  vex::this_thread::sleep_for(200);
  driveInches(13, 20, 200, false, BRAKE);
  Intakef(BWD, 1250);
  Liftf(FWD, 1000);
  driveInches(-12, 20, 500, false, BRAKE);
  Liftf(BWD, 1000);
#endif
#ifdef RIGHT_TURN
  driveInches(40, 20, true, 500, BRAKE);
  driveInches(-27.5, 40, true, 200, BRAKE);
  Intake.spin(FWD, 10, vPCT);
  driveTrain.turnFor(RIGHT, 119, DEG);
  Intake.stop();
  vex::this_thread::sleep_for(200);
  driveInches(11, 20, 200, false, BRAKE);
  Intakef(BWD, 1250);
  Liftf(FWD, 1000);
  driveInches(-12, 20, 500, false, BRAKE);
  Liftf(BWD, 1000);
#endif
#ifdef SIMPLE
  driveInches(12, 30, 300, false, BRAKE);
  vex::this_thread::sleep_for(300);
  driveInches(-10, 30, 300, false, BRAKE);
#endif
}

void usercontrol() {
  pre_drive();

  Threads::t_Drive::tc_Drive();
  Threads::t_Intake::tc_Intake();
  Threads::t_Lift::tc_Lift();

  while (true) {
    if (Controller.RESET()) {
      Threads::t_Drive::mSelf = nullptr;
      Threads::t_Intake::mSelf = nullptr;
      Threads::t_Lift::mSelf = nullptr;
      vex::this_thread::sleep_for(3000);
      Threads::t_Drive::tc_Drive();
      Threads::t_Intake::tc_Intake();
      Threads::t_Lift::tc_Lift();
    }
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