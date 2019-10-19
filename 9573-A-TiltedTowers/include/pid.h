#include "robotConfig.h"

#define PID_SENSOR_SCALE 1
#define PID_INTEGRAL_LIMIT 50
#define PID_DRIVE_MAX MAX_SPEED_AUTON
#define PID_DRIVE_MIN 0

class pid_controller : vex::thread {
public:
  //static pid_controller* mself;

  //static void entry();
public:
  const float Kp = 1.0;
  const float Ki = 1.0;
  const float Kd = 1.0;

  float pidSensorCurrentValue;
  float pidError;
  float pidLastError;
  float pidIntegral;
  float pidDerivative;
  float pidDrive;

  int pid_run(float pidTarget, vex::motor_group *motor);

  pid_controller(float _pidTarget, vex::motor_group *_motorGroup);
  ~pid_controller();
};