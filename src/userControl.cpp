#include "userControl.h"
#include <cmath>

Threads::t_Lift *Threads::t_Lift::mSelf = nullptr;
Threads::t_Intake *Threads::t_Intake::mSelf = nullptr;
Threads::t_Drive *Threads::t_Drive::mSelf = nullptr;

Threads::t_Lift::t_Lift() : vex::thread(&Threads::t_Lift::entry) {}

Threads::t_Intake::t_Intake() : vex::thread(&Threads::t_Intake::entry) {}

Threads::t_Drive::t_Drive() : vex::thread(&Threads::t_Drive::entry) {}

void Threads::t_Lift::entry() {
  Threads::t_Lift::mSelf->run();
}

void Threads::t_Intake::entry() {
  Threads::t_Intake::mSelf->run();
}

void Threads::t_Drive::entry() {
  Threads::t_Drive::mSelf->run();
}

void Threads::t_Lift::run() {
  m_once = false;
  while (true) {
    if(Controller.ButtonL1.pressing()) {
      Lift.spin(FWD, LIFT_SPEED, PCT);
      m_once = false;
    } else if(Controller.ButtonL2.pressing()) {
      Lift.spin(BWD, MAX_SPEED / 10, PCT);
      m_once = false;
    } else {
      if (!m_once) {
        m_enc_LIFT_AVG = (LIFT_1.rotation(DEG) + LIFT_2.rotation(DEG)) / 2;
        m_once = true;
      }
      if (std::abs(((LIFT_1.rotation(DEG) + LIFT_2.rotation(DEG)) / 2)) < m_enc_LIFT_AVG) {
        Lift.spin(FWD, LIFT_SPEED / 50, PCT);
      } else if (std::abs(((LIFT_1.rotation(DEG) + LIFT_2.rotation(DEG)) / 2)) > m_enc_LIFT_AVG) {
        Lift.spin(BWD, LIFT_SPEED / 50, PCT);
      } else {
        Lift.stop();
      }
    }
    vex::this_thread::sleep_for(10);
  }
}

void Threads::t_Intake::run() {
  while (true) {
    if(Controller.ButtonR1.pressing()) {
      Intake.spin(FWD, INTAKE_SPEED, PCT);
    } else if(Controller.ButtonR2.pressing()) {
      Intake.spin(BWD, INTAKE_SPEED, PCT);
    } else {
      Intake.stop();
    }
    vex::this_thread::sleep_for(10);
  }
}

void Threads::t_Drive::Tank() {
  RF.spin(FWD, Controller.RIGHT_JOY_VERT(), vPCT);
  LF.spin(FWD, Controller.LEFT_JOY_VERT(), vPCT);
  RB.spin(FWD, Controller.RIGHT_JOY_VERT(), vPCT);
  LB.spin(FWD, Controller.LEFT_JOY_VERT(), vPCT);
}

void Threads::t_Drive::SS_Arcade() {
  LF.spin(FWD, (Controller.LEFT_JOY_VERT() + Controller.LEFT_JOY_HORIZ()), vPCT); 
  RF.spin(FWD, (Controller.LEFT_JOY_VERT() - Controller.LEFT_JOY_HORIZ()), vPCT);
  LB.spin(FWD, (Controller.LEFT_JOY_VERT() + Controller.LEFT_JOY_HORIZ()), vPCT); 
  RB.spin(FWD, (Controller.LEFT_JOY_VERT() - Controller.LEFT_JOY_HORIZ()), vPCT);
}

void Threads::t_Drive::TS_Arcade() {
  LF.spin(FWD, (Controller.LEFT_JOY_VERT() + Controller.RIGHT_JOY_HORIZ()), vPCT); 
  RF.spin(FWD, (Controller.LEFT_JOY_VERT() - Controller.RIGHT_JOY_HORIZ()), vPCT);
  LB.spin(FWD, (Controller.LEFT_JOY_VERT() + Controller.RIGHT_JOY_HORIZ()), vPCT); 
  RB.spin(FWD, (Controller.LEFT_JOY_VERT() - Controller.RIGHT_JOY_HORIZ()), vPCT);
}

void Threads::t_Drive::run() {
  Threads::t_Drive::Tank();

  Threads::t_Drive::SS_Arcade();

  Threads::t_Drive::TS_Arcade();
}