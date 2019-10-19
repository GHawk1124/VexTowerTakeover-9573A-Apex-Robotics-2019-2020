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

class t_Intake : public vex::thread {
public:
  static t_Intake *mSelf;

  static t_Intake &tc_Intake() {
    if (mSelf == nullptr) {
      mSelf = new t_Intake();
    }
    return *mSelf;
  }

  static void entry();

private:
  void run();

  t_Intake();
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
  void Tank();

  void SS_Arcade();

  void TS_Arcade();

  void run();

  t_Drive();
};

} // namespace Threads

#endif