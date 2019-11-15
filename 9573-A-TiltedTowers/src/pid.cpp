#include "pid.h"
#include <cmath>

static volatile float rot1 = 0.0f;
static volatile float rot2 = 0.0f;
static volatile float rot3 = 0.0f;

static vex::motor_group mgdriveTrain(RF, LF);

void Measure_1() {
  while (true) {
    rot1 = mgdriveTrain.rotation(ROT) * PID_SENSOR_SCALE;
    vex::this_thread::sleep_for(1);
  }
}

void Measure_2() {
  while (true) {
    rot2 = mgdriveTrain.rotation(ROT) * PID_SENSOR_SCALE;
    vex::this_thread::sleep_for(1);
  }
}

void Measure_3() {
  while (true) {
    rot3 = mgdriveTrain.rotation(ROT) * PID_SENSOR_SCALE;
    vex::this_thread::sleep_for(1);
  }
}

void newPID(double _rots, float _Kp, float _Ki, float _Kd) {
  Brain.Screen.print("PID Starting");
  vex::thread pid1(&Measure_1);
  vex::thread pid2(&Measure_2);
  vex::thread pid3(&Measure_3);
  pid_controller pid(_rots, _Kp, _Ki, _Kd);
  pid.init();
  pid1.interrupt();
  pid2.interrupt();
  pid3.interrupt();
}

pid_controller::pid_controller(float _pidTarget, float _Kp, float _Ki,
                               float _Kd)
    : pidTarget(_pidTarget), Kp(_Kp), Ki(_Ki), Kd(_Kd) {
  Brain.Screen.setCursor(5, 1);
  Brain.Screen.print("PID Control Created");
}

void pid_controller::init() {
  run(pidTarget);
  Brain.Screen.setCursor(6, 1);
  Brain.Screen.print(pidTarget);
}

void pid_controller::run(float pidTarget) {
  Brain.Screen.setCursor(7, 1);
  Brain.Screen.print("RUNNING PID");
  mgdriveTrain.resetRotation();
  pidLastError = mgdriveTrain.rotation(ROT);
  pidIntegral = 0;

  do {
    pidError =
        pidTarget - ((mgdriveTrain.rotation(ROT) + rot1 + rot2 + rot3) / 4);
    Brain.Screen.setCursor(8, 1);
    Brain.Screen.print(pidError);
    if (pidError < PID_INTEGRAL_LIMIT) {
      pidIntegral += pidError;
    } else {
      pidIntegral = 0;
    }

    pidDerivative = pidError - pidLastError;

    pidLastError = pidError;

    pidDrive = (Kp * pidError) + (Ki * pidIntegral) + (Kd * pidDerivative);
    Brain.Screen.setCursor(9, 1);
    Brain.Screen.print(pidDrive);

    if (pidDrive > PID_DRIVE_MAX) {
      pidDrive = PID_DRIVE_MAX;
    } else if (pidDrive < PID_DRIVE_MIN) {
      pidDrive = PID_DRIVE_MIN;
    }
    Brain.Screen.setCursor(10, 1);
    Brain.Screen.print(pidDrive * PID_SENSOR_SCALE);
    if (pidDrive > 0) {
      mgdriveTrain.spin(FWD, pidDrive * PID_SENSOR_SCALE, vPCT);
    } else {
      mgdriveTrain.spin(BWD, pidDrive * PID_SENSOR_SCALE, vPCT);
    }
  } while (pidError <= -0.1f || pidError >= 0.1f);

  mgdriveTrain.stop();
}