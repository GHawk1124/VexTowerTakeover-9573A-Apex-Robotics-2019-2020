#include "pid.h"
#include <cmath>

pid_controller::pid_controller(float _pidTarget,
                               vex::motor_group *_motorGroup) {}

int pid_controller::pid_run(float pidTarget, vex::motor_group *motorGroup) {
  pidLastError = 0;
  pidIntegral = 0;
  motorGroup->resetRotation();

  while (pidError != 0) {
    pidSensorCurrentValue = motorGroup->rotation(ROT) * PID_SENSOR_SCALE;
    pidError = pidSensorCurrentValue - pidTarget;

    if (std::abs(pidError) < PID_INTEGRAL_LIMIT) {
      pidIntegral += pidError;
    } else {
      pidIntegral = 0;
    }

    pidDerivative = pidError - pidLastError;
    pidLastError = pidError;
    pidDrive = (Kp * pidError) + (Ki * pidIntegral) + (Kd * pidDerivative);

    if (pidDrive > PID_DRIVE_MAX) {
      pidDrive = PID_DRIVE_MAX;
    } else if (pidDrive < PID_DRIVE_MIN) {
      pidDrive = PID_DRIVE_MIN;
    }

    motorGroup->spin(FWD, pidDrive, vPCT);
  }
  pidError = 0;
  pidLastError = 0;
  pidIntegral = 0;
  pidDerivative = 0;
  return 0;
}