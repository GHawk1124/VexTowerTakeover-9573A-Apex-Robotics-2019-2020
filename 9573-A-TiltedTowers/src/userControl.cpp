#include "userControl.h"
#include <cmath>

Threads::t_Lift *Threads::t_Lift::mSelf = nullptr;
Threads::t_Intake *Threads::t_Intake::mSelf = nullptr;
Threads::t_Drive *Threads::t_Drive::mSelf = nullptr;

Threads::t_Lift::t_Lift() : vex::thread(&Threads::t_Lift::entry) {}

Threads::t_Intake::t_Intake() : vex::thread(&Threads::t_Intake::entry) {}

Threads::t_Drive::t_Drive() : vex::thread(&Threads::t_Drive::entry) {}

void Threads::t_Lift::entry() { Threads::t_Lift::mSelf->run(); }

void Threads::t_Intake::entry() { Threads::t_Intake::mSelf->run(); }

void Threads::t_Drive::entry() { Threads::t_Drive::mSelf->run(); }

void Threads::t_Lift::run() {
  while (true) {
    if (Controller.ButtonL1.pressing()) {
      Lift.setStopping(MOTOR_STOPPING_DRIVE);
      Lift.spin(FWD, 75, vPCT);
    } else if (Controller.ButtonL2.pressing()) {
      Lift.setStopping(MOTOR_STOPPING_DRIVE);
      Lift.spin(BWD, HALF_SPEED, vPCT);
    } else {
      Lift.stop();
    }
    vex::this_thread::sleep_for(10);
  }
}

void Threads::t_Intake::run() {
  while (true) {
    if (Controller.ButtonR1.pressing()) {
      Intake.setStopping(COAST);
      Intake.spin(FWD, INTAKE_SPEED, vPCT);
    } else if (Controller.ButtonR2.pressing()) {
      Intake.setStopping(COAST);
      Intake.spin(BWD, INTAKE_SPEED, vPCT);
    } else {
      Intake.stop(HOLD);
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
#if DRIVE_TYPE == 1
  Threads::t_Drive::Tank();
#endif

#if DRIVE_TYPE == 2
  Threads::t_Drive::SS_Arcade();
#endif

#if DRIVE_TYPE == 3
  Threads::t_Drive::TS_Arcade();
#endif
}