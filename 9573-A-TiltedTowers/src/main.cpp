#include "auton.h"
#include "robotConfig.h"
#include "userControl.h"

#define SIMPLE

void pre_auton() {
  driveTrain.setStopping(MOTOR_STOPPING_AUTON);
  Lift.setMaxTorque(110, PCT);
  Lift.setStopping(MOTOR_STOPPING_AUTON);
  Lift.resetRotation();
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
#ifdef STACK_UNPROTECTED_BLUE
  driveInches(25, 20, true, 500, BRAKE);
  driveInches(10, 20, true, 500, BRAKE);
  driveInches(10, 20, true, 500, BRAKE);
  driveInches(-32.5, 40, true, 200, BRAKE);
  Intake.spin(FWD, MAX_SPEED, vPCT);
  driveTrain.turnFor(LEFT, 93, DEG);
  Intake.stop();
  driveInches(9, 20, 200, false, BRAKE);
  Intakef(BWD, 625);
  Liftf(1000, true);
  driveInches(1, 100, 0, false, COAST);
  driveInches(-12, 20, false, 500, BRAKE);
  Liftf(250, true);
#endif
#ifdef STACK_PROTECTED_BLUE
// TODO
#endif
#ifdef STACK_UNPROTECTED_RED
  driveInches(25, 20, true, 500, BRAKE);
  driveInches(10, 20, true, 500, BRAKE);
  driveInches(10, 20, true, 500, BRAKE);
  driveInches(-32.5, 40, true, 200, BRAKE);
  Intake.spin(FWD, MAX_SPEED, vPCT);
  driveTrain.turnFor(RIGHT, 93, DEG);
  Intake.stop();
  driveInches(9, 20, 200, false, BRAKE);
  Intakef(BWD, 625);
  Liftf(1000, true);
  driveInches(1, 100, 0, false, COAST);
  driveInches(-12, 20, false, 500, BRAKE);
  Liftf(250, true);
#endif
#ifdef STACK_PROTECTED_RED
// TODO
#endif
#ifdef SIMPLE
  driveInches(12, 30, 300, false, BRAKE);
  vex::this_thread::sleep_for(300);
  driveInches(-10, 30, 300, false, BRAKE);
#endif
vex::this_thread::sleep_for(2000);
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