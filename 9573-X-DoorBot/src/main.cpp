#include "auton.h"
#include "robotConfig.h"
#include "userControl.h"

static volatile double rfr;
static volatile double rbr;
static volatile double lfr;
static volatile double lbr;

void driveInchesGAR(double inches, int speed, int timeToSleep,
                 vex::brakeType brakeType) {
  driveTrain.setStopping(brakeType);
  if (inches > 0) {
    driveTrain.driveFor(FWD, inches, vex::distanceUnits::in, speed, vPCT, true);
  } else {
    driveTrain.driveFor(BWD, std::abs(inches), vex::distanceUnits::in, speed,
                        vPCT, true);
  }
  vex::this_thread::sleep_for(timeToSleep);
}

void newDriveInchesGar(double inches, int speed, int timeToSleep,
                 vex::brakeType brakeType) {
	// Setup
	{
	vex::thread rfM (RF.rotation);
	vex::thread rbM (RB.rotation);
	vex::thread lfM (LF.rotation);
	vex::thread lbM (RF.rotation);
	}


}

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
#ifdef LEFT_TURN
  driveInchesGAR(35, 20, 500, BRAKE);
  driveInchesGAR(-22.5, 40, 200, BRAKE);
  Intake.spin(FWD, 10, vPCT);
  driveTrain.turnFor(LEFT, 116, DEG);
  Intake.stop();
  vex::this_thread::sleep_for(200);
  driveInchesGAR(13, 20, 200, BRAKE);
  Intakef(BWD, 1250);
  Liftf(FWD, 1000);
  driveInchesGAR(-12, 20, 500, BRAKE);
  Liftf(BWD, 1000);
#endif
#ifdef RIGHT_TURN
  driveInchesGAR(40, 20, 500, BRAKE);
  driveInchesGAR(-27.5, 40, 200, BRAKE);
  Intake.spin(FWD, 10, vPCT);
  driveTrain.turnFor(RIGHT, 119, DEG);
  Intake.stop();
  vex::this_thread::sleep_for(200);
  driveInchesGAR(11, 20, 200, BRAKE);
  Intakef(BWD, 1250);
  Liftf(FWD, 1000);
  driveInchesGAR(-12, 20, 500, BRAKE);
  Liftf(BWD, 1000);
#endif
#ifdef SIMPLE
  driveInchesGAR(12, 30, 300, BRAKE);
  vex::this_thread::sleep_for(300);
  driveInchesGAR(-10, 30, 300, BRAKE);
#endif
}

void usercontrol() {
  pre_auton();
  autonomous();
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
