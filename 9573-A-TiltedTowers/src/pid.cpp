#include "pid.h"
#include <cmath>

static volatile float rot1 = 0.0f;
static volatile float rot2 = 0.0f;
static volatile float rot3 = 0.0f;

void Measure_1() {
  while (true) {
    rot1 = driveTrain.rotation(ROT) * PID_SENSOR_SCALE;
    vex::this_thread::sleep_for(1);
  }
}

void Measure_2() {
  while (true) {
    rot2 = driveTrain.rotation(ROT) * PID_SENSOR_SCALE;
    vex::this_thread::sleep_for(1);
  }
}

void Measure_3() {
  while (true) {
    rot3 = driveTrain.rotation(ROT) * PID_SENSOR_SCALE;
    vex::this_thread::sleep_for(1);
  }
}

void newPID(double _rots, vex::motor_group *_motorGroup, float _Kp, float _Ki,
            float _Kd) {
  vex::thread pid1(&Measure_1);
  vex::thread pid2(&Measure_2);
  vex::thread pid3(&Measure_3);
  pid_controller pid(_rots, _motorGroup, _Kp, _Ki, _Kd);
  pid.init();
  pid1.interrupt();
  pid2.interrupt();
  pid3.interrupt();
}

pid_controller::pid_controller(float _pidTarget, vex::motor_group *_motorGroup,
                               float _Kp, float _Ki, float _Kd)
    : pidTarget(_pidTarget), motorGroup(_motorGroup), Kp(_Kp), Ki(_Ki),
      Kd(_Kd) {}

void pid_controller::init() { run(pidTarget, motorGroup); }

void pid_controller::run(float pidTarget, vex::motor_group *motorGroup) {
  motorGroup->resetRotation();
  pidLastError = motorGroup->rotation(ROT);
  pidIntegral = 0;

  do {
    pidError =
        pidTarget - ((motorGroup->rotation(ROT) + rot1 + rot2 + rot3) / 4) *
                        PID_SENSOR_SCALE;

    if (pidError < PID_INTEGRAL_LIMIT) {
      pidIntegral += pidError;
    } else {
      pidIntegral = 0;
    }

    pidDerivative = pidError - pidLastError;

    pidLastError = pidError;

    pidDrive = (pid_controller::Kp * pidError) +
               (pid_controller::Ki * pidIntegral) +
               (pid_controller::Kd * pidDerivative);

    if (pidDrive > PID_DRIVE_MAX) {
      pidDrive = PID_DRIVE_MAX;
    } else if (pidDrive < PID_DRIVE_MIN) {
      pidDrive = PID_DRIVE_MIN;
    }

    motorGroup->spin(FWD, pidDrive, vPCT);
  } while (pidError != 0);

  motorGroup->stop();
}