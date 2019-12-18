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
  Lift.resetRotation();
  double ll, rl;
  while (true) {
    ll = LEFT_LIFT.rotation(DEG);
    rl = RIGHT_LIFT.rotation(DEG);
    LEFT_LIFT.spin(FWD,
                   LIFT_SPEED * Controller.RAISE_LIFT() -
                       LIFT_SPEED * Controller.LOWER_LIFT() + rl - ll,
                   vPCT);
    RIGHT_LIFT.spin(FWD,
                   LIFT_SPEED * Controller.RAISE_LIFT() -
                       LIFT_SPEED * Controller.LOWER_LIFT() + ll - rl,
                   vPCT);
    //    Lift.spin(FWD, LIFT_SPEED * (Controller.RAISE_LIFT() -
    //    Controller.LOWER_LIFT()), vPCT);
    vex::this_thread::sleep_for(10);
  }
}

void Threads::t_Claw::run() {
  // Claw.resetRotation();
  while (true) {
    // Claw.rotateTo((Controller.OPEN_CLAW() ? -160 : -400), DEG, false);
    Claw.spin(FWD,
              CLAW_SPEED *
                  ((Controller.OPEN_CLAW() && Claw.rotation(DEG) <= -60) -
                   !Controller.OPEN_CLAW()),
              vPCT);
    vex::this_thread::sleep_for(10);
  }
}

void Threads::t_Drive::run() {
  int X1 = 0, X2 = 0, Y1 = 0, deadzone = 15;
  while (true) {
    Y1 = abs(Controller.LEFT_JOY_VERT()) > deadzone
             ? -Controller.LEFT_JOY_VERT()
             : 0;
    X1 = abs(Controller.LEFT_JOY_HORIZ()) > deadzone
             ? Controller.LEFT_JOY_HORIZ()
             : 0;
    X2 = abs(Controller.RIGHT_JOY_HORIZ()) > deadzone
             ? Controller.RIGHT_JOY_HORIZ()
             : 0;
    LF.spin(FWD, Y1 - X2 - X1, vPCT);
    LB.spin(FWD, Y1 - X2 + X1, vPCT);
    RF.spin(FWD, Y1 + X2 + X1, vPCT);
    RB.spin(FWD, Y1 + X2 - X1, vPCT);
  }
}