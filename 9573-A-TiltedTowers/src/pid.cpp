#include "pid.h"
#include <cmath>

pid_controller::pid_controller(float _pidTarget,
                               vex::motor_group *_motorGroup) {
  m_pidTarget = _pidTarget;
  m_motorGroup = _motorGroup;
}

void init() {
  
}

void pid_controller::entry() { pid_run(m_pidTarget, m_motorGroup, 1); }
void pid_controller::entry2() { pid_run(m_pidTarget, m_motorGroup, 2); }
void pid_controller::entry3() { pid_run(m_pidTarget, m_motorGroup, 3); }

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

    float tpidDrive =
        (Kp * pidErrors[3]) + (Ki * pidIntegral) + (Kd * pidDerivative);

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

    if (_pidDrive == 1) {
      motorGroup->spin(FWD, pidDriveAvg, vPCT);
    }
  }
  if (_pidDrive == 1) {
    motorGroup->stop();
  }
  pidErrors[0] = 0;
  pidLastError = 0;
  pidIntegral = 0;
  pidDerivative = 0;
}