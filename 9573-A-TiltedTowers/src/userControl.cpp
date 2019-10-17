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
  m_once = false;
  while (true) {
    if (Controller.ButtonL1.pressing()) {
      Lift.setStopping(MOTOR_STOPPING_DRIVE);
      Lift.spin(BWD, LIFT_SPEED, vPCT);
    } else if (Controller.ButtonL2.pressing()) {
      Lift.setStopping(MOTOR_STOPPING_DRIVE);
      Lift.spin(FWD, LIFT_SPEED / 10, vPCT);
    } else {
      Lift.stop(HOLD);
      /*
      if (!m_once) {
        m_enc_LIFT_AVG = (LIFT_1.rotation(DEG) + LIFT_2.rotation(DEG)) / 2;
        m_once = true;
      }
      if (std::abs(((LIFT_1.rotation(DEG) + LIFT_2.rotation(DEG)) / 2)) <
      m_enc_LIFT_AVG) { Lift.spin(FWD, LIFT_SPEED / 50, PCT); } else if
      (std::abs(((LIFT_1.rotation(DEG) + LIFT_2.rotation(DEG)) / 2)) >
      m_enc_LIFT_AVG) { Lift.spin(BWD, LIFT_SPEED / 50, PCT); } else {
        Lift.stop();
      }*/
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
    // RB.spin(FWD, Controller.RIGHT_JOY_VERT(), vPCT);
    // LB.spin(FWD, Controller.LEFT_JOY_VERT(), vPCT);
  }
}

void Threads::t_Drive::SS_Arcade() {
  while (true) {
    LF.spin(FWD, (Controller.LEFT_JOY_VERT() + Controller.LEFT_JOY_HORIZ()),
            vPCT);
    RF.spin(FWD, (Controller.LEFT_JOY_VERT() - Controller.LEFT_JOY_HORIZ()),
            vPCT);
    // LB.spin(FWD, (Controller.LEFT_JOY_VERT() + Controller.LEFT_JOY_HORIZ()),
    // vPCT); RB.spin(FWD, (Controller.LEFT_JOY_VERT() -
    // Controller.LEFT_JOY_HORIZ()), vPCT);
  }
}

void Threads::t_Drive::TS_Arcade() {
  while (true) {
    LF.spin(FWD, (Controller.LEFT_JOY_VERT() + Controller.RIGHT_JOY_HORIZ()),
            vPCT);
    RF.spin(FWD, (Controller.LEFT_JOY_VERT() - Controller.RIGHT_JOY_HORIZ()),
            vPCT);
    // LB.spin(FWD, (Controller.LEFT_JOY_VERT() + Controller.RIGHT_JOY_HORIZ()),
    // vPCT); RB.spin(FWD, (Controller.LEFT_JOY_VERT() -
    // Controller.RIGHT_JOY_HORIZ()), vPCT);
  }
}

void Threads::t_Drive::run() {
#if DRIVE_TYPE == TANK
  Threads::t_Drive::Tank();
#endif

#if DRIVE_TYPE == SS_ARCADE
  Threads::t_Drive::SS_Arcade();
#endif

#if DRIVE_TYPE == TS_ARCADE
  Threads::t_Drive::TS_Arcade();
#endif
}