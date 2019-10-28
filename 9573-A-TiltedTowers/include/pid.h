#ifndef PID
#define PID

#include "robotConfig.h"

// Defines basic constants
#define PID_SENSOR_SCALE 3
#define PID_INTEGRAL_LIMIT 50
#define PID_DRIVE_MAX MAX_SPEED_AUTON
#define PID_DRIVE_MIN 10

/*
 * @brief Instantiates a pid_controller with set parameters and destroys it when
 *  finished.
 */
void newPID(double _rots, float _Kp, float _Ki, float _Kd);

/*
 * @brief Controller for a pid loop.
 */
class pid_controller {
public:
  /*
   * @brief Used to init the PID.
   */
  void init();

  /*
   * @brief Sets each member function equal to the constructed values. Allows
   *  the creation of different types of PID loops for each of the applications
   *  of the bot.
   */
  pid_controller(float _pidTarget, float _Kp, float _Ki, float _Kd);

protected:
  /*
   * @brief Defines the PID Encoder Value Target.
   */
  const float pidTarget;

  /*
   * @brief Defines the Motor Group to act on.
   */
  // vex::motor_group *drivetrain;

  /*
   * @brief Defines the PID tuning constants (defined in constructor)
   */
  const float Kp;
  const float Ki;
  const float Kd;

  /*
   * @brief Defines the four sensor values used for the P, I, and D (Proportion,
   *  Integral, and Derivative)
   */
  float pidError;
  float pidLastError;
  float pidIntegral;
  float pidDerivative;

  /*
   * @brief Defines the motor speeds used for threads 1, 2 and 3 respectively
   */
  float pidDrive;

private:
  /*
   * @brief Starts the PID loop that eases into the correct encoder values
   *  driving the correct number of rotations
   */
  void run(float pidTarget);
};

#endif