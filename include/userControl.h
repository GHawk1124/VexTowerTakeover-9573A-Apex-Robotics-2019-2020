#ifndef USER_CONTROL
#define USER_CONTROL

#include "robotConfig.h"

namespace Threads {
  class t_Lift : public vex::thread {
  public:
    static t_Lift *mSelf;

    static t_Lift &tc_Lift() {
      if(mSelf == nullptr) {
        mSelf = new t_Lift();
      }
      return *mSelf;;
    }

    static void entry();
  public:

  bool m_once;

  double m_enc_LIFT_AVG;

  void run();

  private:
    t_Lift();
  };

  class t_Intake : public vex::thread {
  public:
    static t_Intake *mSelf;

    static t_Intake &tc_Intake() {
      if(mSelf == nullptr) {
        mSelf = new t_Intake();
      }
      return *mSelf;
    }

    static void entry();
  public:

  void run();

  private:
    t_Intake();
  };

  class t_Drive : public vex::thread {
  public:
    static t_Drive *mSelf;

    static t_Drive &tc_Drive() {
      if(mSelf == nullptr) {
        mSelf = new t_Drive();
      }
      return *mSelf;
    }

    static void entry();
  public:

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

  private:
    t_Drive();
  };
}

#endif