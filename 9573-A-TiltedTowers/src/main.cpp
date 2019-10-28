#include "auton.h"
#include "robotConfig.h"
#include "userControl.h"

#define AUTON_TESTING

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
  driveTrain._wheel_circumference = 4;
  driveInches(35, 20, BRAKE);
  vex::this_thread::sleep_for(500);
  driveInches(-22.5, 40, BRAKE);
  vex::this_thread::sleep_for(200);
  Intake.spin(FWD, 10, vPCT);
  driveTrain.turnFor(vex::turnType::left, 116, DEG);
  Intake.stop();
  vex::this_thread::sleep_for(200);
  driveInches(13, 20, BRAKE, false);
  vex::this_thread::sleep_for(200);
  Intake.spin(BWD, 50, vPCT);
  vex::this_thread::sleep_for(1250);
  Intake.stop();
  vex::this_thread::sleep_for(500);
  Liftf(FWD);
  vex::this_thread::sleep_for(500);
  driveInches(-12, 20, BRAKE, false);
  vex::this_thread::sleep_for(500);
  Liftf(BWD);
#endif
#ifdef RIGHT_TURN
  driveInches(40, 20, BRAKE);
  vex::this_thread::sleep_for(500);
  driveInches(-27.5, 40, BRAKE);
  vex::this_thread::sleep_for(200);
  Intake.spin(FWD, 10, vPCT);
  driveTrain.turnFor(vex::turnType::right, 119, DEG);
  Intake.stop();
  vex::this_thread::sleep_for(200);
  driveInches(11, 20, BRAKE, false);
  vex::this_thread::sleep_for(200);
  Intake.spin(BWD, 50, vPCT);
  vex::this_thread::sleep_for(1250);
  Intake.stop();
  vex::this_thread::sleep_for(500);
  Liftf(FWD);
  vex::this_thread::sleep_for(500);
  driveInches(-12, 20, BRAKE, false);
  vex::this_thread::sleep_for(500);
  Liftf(BWD);
#endif
#ifdef SIMPLE
  driveInches(12, 30, BRAKE, false);
  vex::this_thread::sleep_for(300);
  driveInches(-10, 30, BRAKE, false);
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
#ifdef AUTON_TESTING
  newPID(3, 1, 0, 0);
#endif
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    vex::task::sleep(100);
  }
}