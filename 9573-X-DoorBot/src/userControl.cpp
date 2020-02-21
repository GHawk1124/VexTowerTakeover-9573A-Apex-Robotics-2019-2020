
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
  while (true) {
    LEFT_LIFT.spin(FWD,
                   LIFT_SPEED * Controller.RAISE_LIFT() -
                       LIFT_SPEED * Controller.LOWER_LIFT(),
                   vPCT);
    RIGHT_LIFT.spin(FWD,
                    LIFT_SPEED * Controller.RAISE_LIFT() -
                        LIFT_SPEED * Controller.LOWER_LIFT(),
                    vPCT);
    vex::this_thread::sleep_for(10);
  }
}

void Threads::t_Claw::run() {
  bool close = false;
  while (true) {
    close = Controller.CLOSE_CLAW();
    ClawLeft.rotateTo(close * -540, DEG, 100, vPCT, false);
    ClawRight.rotateTo(close * -540, DEG, 100, vPCT, false);
    vex::this_thread::sleep_for(10);
  }
}

void Threads::t_Drive::run() {
  double magnitude, angle, x, y, turn;
  while (true) {
    x = Controller.LEFT_JOY_HORIZ();
    y = Controller.LEFT_JOY_VERT();
    turn = Controller.RIGHT_JOY_HORIZ();
    magnitude = sqrt((x * x) + (y * y));
    angle = atan2(y, x);
    RF.spin(FWD, sin(angle - PI / 4) * magnitude - turn, vPCT);
    LB.spin(FWD, sin(angle - PI / 4) * magnitude + turn, vPCT);
    LF.spin(FWD, sin(angle + PI / 4) * magnitude + turn, vPCT);
    RB.spin(FWD, sin(angle + PI / 4) * magnitude - turn, vPCT);
    vex::this_thread::sleep_for(10);
  }
}