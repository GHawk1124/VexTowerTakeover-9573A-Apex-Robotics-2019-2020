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
  Lift.setStopping(HOLD);
  int ll, rl;
  while (true) {
    ll = LEFT_LIFT.rotation(DEG);
    rl = RIGHT_LIFT.rotation(DEG);
    LEFT_LIFT.spin(BWD,
                   (LIFT_SPEED * Controller.RAISE_LIFT() -
                    LIFT_SPEED / 3 * Controller.LOWER_LIFT()) +
                       (rl > ll ? 4 : 0),
                   vPCT);
    RIGHT_LIFT.spin(BWD,
                    (LIFT_SPEED * Controller.RAISE_LIFT() -
                     LIFT_SPEED / 3 * Controller.LOWER_LIFT()) +
                        (ll > rl ? 4 : 0),
                    vPCT);
    vex::this_thread::sleep_for(10);
  }
}

void Threads::t_Claw::run() {
  Claw.setStopping(COAST);
  while (true) {
    Claw.spin(FWD, CLAW_SPEED * Controller.OPEN_CLAW(), vPCT);
    vex::this_thread::sleep_for(10);
  }
}

void Threads::t_Drive::Tank() {
  while (true) {
    driveTrainLeft.spin(FWD, Controller.RIGHT_JOY_VERT(), vPCT);
    driveTrainRight.spin(FWD, Controller.LEFT_JOY_VERT(), vPCT);
  }
}

void Threads::t_Drive::SS_Arcade() {
  while (true) {
    driveTrainLeft.spin(
        FWD, (Controller.LEFT_JOY_VERT() + Controller.LEFT_JOY_HORIZ()), vPCT);
    driveTrainRight.spin(
        FWD, (Controller.LEFT_JOY_VERT() - Controller.LEFT_JOY_HORIZ()), vPCT);
  }
}

void Threads::t_Drive::TS_Arcade() {
  while (true) {
    driveTrainLeft.spin(
        FWD, (Controller.LEFT_JOY_VERT() + Controller.RIGHT_JOY_HORIZ()), vPCT);
    driveTrainRight.spin(
        FWD, (Controller.LEFT_JOY_VERT() - Controller.RIGHT_JOY_HORIZ()), vPCT);
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