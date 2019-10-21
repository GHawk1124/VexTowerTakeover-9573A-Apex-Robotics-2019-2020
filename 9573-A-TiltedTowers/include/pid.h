#include "robotConfig.h"

#define PID_SENSOR_SCALE 1
#define PID_INTEGRAL_LIMIT 50
#define PID_DRIVE_MAX MAX_SPEED_AUTON
#define PID_DRIVE_MIN 0

class pid_controller {
public:
  //static pid_controller* mself;

public:
  const float Kp = 1.0;
  const float Ki = 0;
  const float Kd = 0;

  float pidSensorCurrentValue;
  float pidError;
  float pidLastError;
  float pidIntegral;
  float pidDerivative;
  float pidDrive;

  float m_pidTarget;
  vex::motor_group *m_motorGroup;

  void entry();

  pid_controller(float _pidTarget, vex::motor_group *_motorGroup);
private:
  void pid_run(float pidTarget, vex::motor_group *motor);
};