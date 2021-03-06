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

public:
  void Tank();

  void SS_Arcade();

  void TS_Arcade();

  void run();

private:
  t_Drive();
};

} // namespace Threads

#endif