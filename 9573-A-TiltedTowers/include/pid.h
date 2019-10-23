#include "robotConfig.h"

#define PID_SENSOR_SCALE 1
#define PID_INTEGRAL_LIMIT 50
#define PID_DRIVE_MAX MAX_SPEED_AUTON
#define PID_DRIVE_MIN 0

class pid_controller {
public:
  static pid_controller *mself;

  static float Kp;
  static float Ki;
  static float Kd;

  static void init();

  static void init2();

  static void init3();

  static float pidTarget;

  static vex::motor_group *motorGroup;

public:
  float pidSensorCurrentValue;
  float pidLastError;
  float pid2LastError;
  float pid3LastError;
  float pidIntegral;
  float pidDerivative;

  float pidErrors[4];

  float m_pidTarget;
  vex::motor_group *m_motorGroup;

  float pidDrive;
  float pidDrive2;
  float pidDrive3;

  pid_controller(float _pidTarget, vex::motor_group *_motorGroup, float _Kp,
                 float _Ki, float _Kd);

private:
  void pid_run(float pidTarget, vex::motor_group *motor, uint8_t _pidDrive);
};