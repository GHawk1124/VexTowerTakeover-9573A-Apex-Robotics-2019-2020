#ifndef USER_CONTROL
#define USER_CONTROL

#include "robotConfig.h"

namespace Threads {

class t_Lift : public vex::thread {
public:
  static t_Lift *mSelf;

  static t_Lift &tc_Lift() {
    if (mSelf == nullptr) {
      mSelf = new t_Lift();
    }
    return *mSelf;
    ;
  }

  static void entry();

private:
  void run();

  t_Lift();
};

class t_Claw : public vex::thread {
public:
  static t_Claw *mSelf;

  static t_Claw &tc_Claw() {
    if (mSelf == nullptr) {
      mSelf = new t_Claw();
    }
    return *mSelf;
  }

  static void entry();

private:
  void run();

  t_Claw();
};

class t_Drive : public vex::thread {
public:
  static t_Drive *mSelf;

  static t_Drive &tc_Drive() {
    if (mSelf == nullptr) {
      mSelf = new t_Drive();
    }
    return *mSelf;
  }

  static void entry();

private:
#if DRIVE_TYPE == TANK
  void Tank();
#endif

#if DRIVE_TYPE == SS_ARCADE
  void SS_Arcade();
#endif

#if DRIVE_TYPE == TS_Arcade
  void TS_Arcade();
#endif

  void run();

  t_Drive();
};

} // namespace Threads

#endif