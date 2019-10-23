#ifndef USER_CONTROL
#define USER_CONTROL

#include "robotConfig.h"

// Includes all UserControl Threads
namespace Threads {

/*
 * @brief Creates a thread that can only be created if it doesn't already exist.
 *  All variables pertaining to the thread remain in the class
 * @inheritance Inherits from vex::thread to create the thread with a static
 *  function inside the class
 */
class t_Lift : public vex::thread {
public:
  /*
   * @brief Define a static pointer to its own class. This is used to call the
   *  class function from the static entry function for the thread.
   */
  static t_Lift *mSelf;

  /*
   * @brief Makes this class only able to be instantiated with a call to this
   *  function and if it hasn't already been created. This avoids the
   *  possibility of creating too many threads.
   * @return *t_Lift If the function is called when the object exists it will
   *  return the pointer to the memory location of the existing object.
   */
  static t_Lift &tc_Lift() {
    if (mSelf == nullptr) {
      mSelf = new t_Lift();
    }
    return *mSelf;
  }

  /*
   * @brief Static function used as a parameter for the thread. This runs the
   *  private function to make the thread useful.
   */
  static void entry();

private:
  /*
   * @brief runs the legitimate code for the thread called by the static entry
   *  function.
   */
  void run();

  /*
   * @brief Class constructor is private so this object can only be instantiated
   *  through the tc_create function. mSelf is the only place for an object of
   *  type t_Lift to exist.
   */
  t_Lift();
};

/*
 * @brief Creates a thread that can only be created if it doesn't already exist.
 *  All variables pertaining to the thread remain in the class
 * @inheritance Inherits from vex::thread to create the thread with a static
 *  function inside the class
 */
class t_Intake : public vex::thread {
public:
  /*
   * @brief Define a static pointer to its own class. This is used to call the
   *  class function from the static entry function for the thread.
   */
  static t_Intake *mSelf;

  /*
   * @brief Makes this class only able to be instantiated with a call to this
   *  function and if it hasn't already been created. This avoids the
   *  possibility of creating too many threads.
   * @return *t_Lift If the function is called when the object exists it will
   *  return the pointer to the memory location of the existing object.
   */
  static t_Intake &tc_Intake() {
    if (mSelf == nullptr) {
      mSelf = new t_Intake();
    }
    return *mSelf;
  }

  /*
   * @brief Static function used as a parameter for the thread. This runs the
   *  private function to make the thread useful.
   */
  static void entry();

private:
  /*
   * @brief runs the legitimate code for the thread called by the static entry
   *  function.
   */
  void run();

  /*
   * @brief Class constructor is private so this object can only be instantiated
   *  through the tc_create function. mSelf is the only place for an object of
   *  type t_Intake to exist.
   */
  t_Intake();
};

/*
 * @brief Creates a thread that can only be created if it doesn't already exist.
 *  All variables pertaining to the thread remain in the class
 * @inheritance Inherits from vex::thread to create the thread with a static
 *  function inside the class
 */
class t_Drive : public vex::thread {
public:
  /*
   * @brief Define a static pointer to its own class. This is used to call the
   *  class function from the static entry function for the thread.
   */
  static t_Drive *mSelf;

  /*
   * @brief Makes this class only able to be instantiated with a call to this
   *  function and if it hasn't already been created. This avoids the
   *  possibility of creating too many threads.
   * @return *t_Lift If the function is called when the object exists it will
   *  return the pointer to the memory location of the existing object.
   */
  static t_Drive &tc_Drive() {
    if (mSelf == nullptr) {
      mSelf = new t_Drive();
    }
    return *mSelf;
  }

  /*
   * @brief Static function used as a parameter for the thread. This runs the
   *  private function to make the thread useful.
   */
  static void entry();

private:
  /*
   * @brief Runs the Tank drive code on a thread.
   */
  void Tank();

  /*
   * @brief Runs the Single Stick drive code on a thread.
   */
  void SS_Arcade();

  /*
   * @brief Runs the Two Stick Arcade drive code on a thread.
   */
  void TS_Arcade();

  /*
   * @brief runs the legitimate code for the thread called by the static entry
   * function.
   */
  void run();

  /*
   * @brief Class constructor is private so this object can only be instantiated
   *  through the tc_create function. mSelf is the only place for an object of
   *  type t_Intake to exist.
   */
  t_Drive();
};

} // namespace Threads

#endif