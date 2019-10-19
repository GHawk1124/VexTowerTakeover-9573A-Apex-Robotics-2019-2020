#include "userControl.h"
#include <cmath>

Threads::t_Lift *Threads::t_Lift::mSelf = nullptr;
Threads::t_Claw *Threads::t_Claw::mSelf = nullptr;
Threads::t_Drive *Threads::t_Drive::mSelf = nullptr;

Threads::t_Lift::t_Lift() : vex::thread(&Threads::t_Lift::entry) {}

Threads::t_Claw::t_Claw() : vex::thread(&Threads::t_Claw::entry) {}

Threads::t_Drive::t_Drive() : vex::thread(&Threads::t_Drive::entry) {}

void Threads::t_Lift::entry() { Threads::t_Lift::mSelf->run(); }

void Threads::t_Claw::entry() { Threads::t_Claw::mSelf->run(); }

void Threads::t_Drive::entry() { Threads::t_Drive::mSelf->run(); }

void Threads::t_Lift::run() {
  while (true) {
    if (Controller.ButtonL1.pressing()) {
      Lift.setStopping(MOTOR_STOPPING_DRIVE);
      Lift.spin(BWD, LIFT_SPEED, vPCT);
    } else if (Controller.ButtonL2.pressing()) {
      Lift.setStopping(MOTOR_STOPPING_DRIVE);
      Lift.spin(FWD, LIFT_SPEED / 10, vPCT);
    } else {
      Lift.stop(HOLD);
    }
    vex::this_thread::sleep_for(10);
  }
}

void Threads::t_Claw::run() {
  while (true) {
    if (Controller.ButtonR1.pressing()) {
      Claw.setStopping(COAST);
      Claw.spin(FWD, CLAW_SPEED, vPCT);
    } else if (Controller.ButtonR2.pressing()) {
      Claw.setStopping(COAST);
      Claw.spin(BWD, CLAW_SPEED, vPCT);
    } else {
      Claw.stop(HOLD);
    }
    vex::this_thread::sleep_for(10);
  }
}

void Threads::t_Drive::Tank() {
  while (true) {
    RF.spin(FWD, Controller.RIGHT_JOY_VERT(), vPCT);
    LF.spin(FWD, Controller.LEFT_JOY_VERT(), vPCT);
  }
}

void Threads::t_Drive::SS_Arcade() {
  while (true) {
    LF.spin(FWD, (Controller.LEFT_JOY_VERT() + Controller.LEFT_JOY_HORIZ()),
            vPCT);
    RF.spin(FWD, (Controller.LEFT_JOY_VERT() - Controller.LEFT_JOY_HORIZ()),
            vPCT);
  }
}

void Threads::t_Drive::TS_Arcade() {
  while (true) {
    LF.spin(FWD, (Controller.LEFT_JOY_VERT() + Controller.RIGHT_JOY_HORIZ()),
            vPCT);
    RF.spin(FWD, (Controller.LEFT_JOY_VERT() - Controller.RIGHT_JOY_HORIZ()),
            vPCT);
  }
}

void Threads::t_Drive::run() {
if (DRIVE_TYPE == 1)
  Threads::t_Drive::Tank();

if (DRIVE_TYPE == 3)
  Threads::t_Drive::SS_Arcade();

if (DRIVE_TYPE == 2)
  Threads::t_Drive::TS_Arcade();
}