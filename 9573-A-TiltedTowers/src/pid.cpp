#include "pid.h"
#include <cmath>

pid_controller *pid_controller::mself = nullptr;

float pid_controller::pidTarget = 0.0;
vex::motor_group *pid_controller::motorGroup = nullptr;

float pid_controller::Kp = 0;
float pid_controller::Ki = 0;
float pid_controller::Kd = 0;

pid_controller::pid_controller(float _pidTarget, vex::motor_group *_motorGroup,
                               float _Kp, float _Ki, float _Kd) {
  pid_controller::Kp = _Kp;
  pid_controller::Ki = _Ki;
  pid_controller::Kd = _Kd;
}

void pid_controller::init() {
  pid_controller::mself->pid_run(pid_controller::pidTarget,
                                 pid_controller::motorGroup, 1);
}

void pid_controller::init2() {
  pid_controller::mself->pid_run(pid_controller::pidTarget,
                                 pid_controller::motorGroup, 2);
}

void pid_controller::init3() {
  pid_controller::mself->pid_run(pid_controller::pidTarget,
                                 pid_controller::motorGroup, 3);
}

void pid_controller::pid_run(float pidTarget, vex::motor_group *motorGroup,
                             uint8_t _pidDrive) {
  pidErrors[0] = 0;
  pidLastError = 0;
  pid2LastError = 0;
  pid3LastError = 0;
  pidIntegral = 0;
  motorGroup->resetRotation();

  while (pidErrors[0] != 0) {
    pidSensorCurrentValue = motorGroup->rotation(ROT) * PID_SENSOR_SCALE;
    pidErrors[0] = pidSensorCurrentValue - pidTarget;
    if (std::abs(pidErrors[0]) < PID_INTEGRAL_LIMIT) {
      pidIntegral += pidErrors[0];
    } else {
      pidIntegral = 0;
    }

    pidErrors[1] = pidLastError;
    pidErrors[2] = pid2LastError;
    pidErrors[3] = pid3LastError;
    pid3LastError = pid2LastError;
    pid2LastError = pidLastError;
    pidLastError = pidErrors[0];

    pidDerivative =
        pidErrors[0] - (pidErrors[1] + pidErrors[2] + pidErrors[3]) / 3;

    float tpidDrive = (pid_controller::Kp * pidErrors[3]) +
                      (pid_controller::Ki * pidIntegral) +
                      (pid_controller::Kd * pidDerivative);

    if (tpidDrive > PID_DRIVE_MAX) {
      tpidDrive = PID_DRIVE_MAX;
    } else if (tpidDrive < PID_DRIVE_MIN) {
      tpidDrive = PID_DRIVE_MIN;
    }

    if (_pidDrive == 1) {
      pidDrive = tpidDrive;
    } else if (_pidDrive == 2) {
      pidDrive2 = tpidDrive;
    } else {
      pidDrive3 = tpidDrive;
    }

    float pidDriveAvg = (pidDrive + pidDrive2 + pidDrive3) / 3;

    if (_pidDrive == 3) {
      motorGroup->spin(FWD, pidDriveAvg, vPCT);
    }
  }
  motorGroup->stop();
  pidErrors[0] = 0;
  pidLastError = 0;
  pidIntegral = 0;
  pidDerivative = 0;
}