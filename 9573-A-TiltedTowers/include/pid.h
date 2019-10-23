#ifndef PID
#define PID

#include "robotConfig.h"

// Defines basic constants
#define PID_SENSOR_SCALE 1
#define PID_INTEGRAL_LIMIT 50
#define PID_DRIVE_MAX MAX_SPEED_AUTON
#define PID_DRIVE_MIN 0

/*
 * @brief Controller for a pid loop.
 */
class pid_controller {
public:
  /*
   * @brief Define a static pointer to its own class. This is used to call the
   *  class function from the static init function.
   */
  static pid_controller *mself;

  /*
   * @brief Defines the PID tuning constants (defined in constructor)
   */
  static float Kp;
  static float Ki;
  static float Kd;

  /*
   * @brief Used to init the three PID threads
   */
  static void init();
  static void init2();
  static void init3();

  /*
   * @brief Target sensor value for the PID loop (defined in constructor)
   */
  static float pidTarget;

  /*
   * @brief Define a static pointer to a motor group. This Motor Group will be
   *  controlled by the PID loop
   */
  static vex::motor_group *motorGroup;

public:
  /*
   * @brief Defines the four sensor values used for the P, I, and D (Proportion,
   *  Integral, and Derivative)
   */
  float pidSensorCurrentValue;
  float pidLastError;
  float pid2LastError;
  float pid3LastError;
  float pidIntegral;
  float pidDerivative;

  /*
   * @brief Defines the array that stores all of the past and current Error
   *  Values
   */
  float pidErrors[4];

  /*
   * @brief Defines the motor speeds used for threads 1, 2 and 3 respectively
   */
  float pidDrive;
  float pidDrive2;
  float pidDrive3;

  /*
   * @brief Sets each member function equal to the constructed values. Allows
   *  the creation of different types of PID loops for each of the applications
   *  of the bot.
   */
  pid_controller(float _pidTarget, vex::motor_group *_motorGroup, float _Kp,
                 float _Ki, float _Kd);

private:
  /*
   * @brief Starts the PID loop that eases into the correct encoder values
   *  driving the correct number of rotations
   */
  void pid_run(float pidTarget, vex::motor_group *motor, uint8_t _pidDrive);
};

#endif