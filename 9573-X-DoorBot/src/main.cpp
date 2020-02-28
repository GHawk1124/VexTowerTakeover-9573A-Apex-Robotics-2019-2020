#include "auton.h"
#include "robotConfig.h"
#include "userControl.h"

void pre_auton() {
  ClawLeft.resetRotation();
  ClawRight.resetRotation();
  Lift.resetRotation();
  driveTrain.setStopping(MOTOR_STOPPING_DRIVE);
  Lift.setMaxTorque(100, PCT);
  Lift.setStopping(HOLD);
  ClawLeft.setMaxTorque(100, PCT);
  ClawRight.setMaxTorque(100, PCT);
  ClawLeft.setStopping(COAST);
  ClawRight.setStopping(COAST);
}

void pre_drive() {
  driveTrain.setStopping(MOTOR_STOPPING_DRIVE);
  Lift.setMaxTorque(100, PCT);
  Lift.setStopping(HOLD);
  ClawLeft.setMaxTorque(100, PCT);
  ClawRight.setStopping(COAST);
  ClawRight.setMaxTorque(100, PCT);
  ClawLeft.setStopping(COAST);
}

void autonomous() {
  ClawLeft.resetRotation();
  ClawRight.resetRotation();
  driveTrain.resetRotation();
  bool smallGoal = true;
  // 1 is for blue team, -1 for red
  int blueTeam = -1;
  if (smallGoal) {
    strafeInches(blueTeam * -10);
    strafeInches(blueTeam * 5.5);
    driveInches(17);
    closeClaw();
    liftTo(115);
    driveInches(5);
    openClaw();
    liftTo(5); 
    driveInches(1.25);
    closeClaw();
    liftTo(135);
    driveInches(5);
    liftTo(120);
    openClaw();
    driveInches(-1);
    liftTo(10);
    driveInches(2);
    closeClaw();
    liftTo(90);
    driveInches(-18);
  } else {
    strafeInches(10 * blueTeam);
    strafeInches(-13.5 * blueTeam);
    driveInches(30);
    strafeInches(-11 * blueTeam);
    driveInches(2);
    liftTo(125);
    closeClaw();
    driveInches(-25);
    pointTurn(70 * blueTeam);
    driveInches(27);  
    strafeInches(7 * blueTeam);
    liftTo(160);
    driveInches(8);
    openClaw();
    driveInches(-10);    
  }
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
  return 0;
}