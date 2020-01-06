#include "testPID.h"
#include <cmath>

// Defines basic constants
#define WHEEL_DIAMETER 4
#define PID_SENSOR_SCALE 5
#define PID_INTEGRAL_LIMIT 50
#define PID_DRIVE_MAX 50
#define PID_DRIVE_MIN 10
#define THRESHOLD 20

static const double PI = std::atan(1.0)*4;

static volatile float rot1 = 0.0f;
static volatile float rot2 = 0.0f;
static volatile float rot3 = 0.0f;

static bool stop = false;
static bool close = false;
static float pidDrive = 0.0f;

void Measure_1() {
  while (!stop) {
    rot1 = RF.rotation(ROT);
    RF.spin(FWD, pidDrive, vPCT);
    if (close) {
      RF.setStopping(COAST)
    }
    vex::this_thread::sleep_for(1);
  }
  RF.stop(BREAK);
}

void Measure_2() {
  while (!stop) {
    rot2 = RB.rotation(ROT);
    RB.spin(FWD, pidDrive, vPCT);
    if (close) {
      RB.setStopping(COAST)
    }
    vex::this_thread::sleep_for(1);
  }
  RB.stop(BREAK);
}

void Measure_3() {
  while (!stop) {
    rot3 = LF.rotation(ROT);
    LF.spin(FWD, pidDrive, vPCT);
    if (close) {
      LF.setStopping(COAST)
    }
    vex::this_thread::sleep_for(1);
  }
  LF.stop(BREAK);
}

pid_controller::pid_controller(float _pidTarget, float _Kp, float _Ki,
                               float _Kd)
    : pidTarget(_pidTarget), Kp(_Kp), Ki(_Ki), Kd(_Kd) {
}

void pid_controller::init() {
  run(pidTarget);
}

void pid_controller::run(float pidTarget) {
  vex::thread pid1(&Measure_1);
  vex::thread pid2(&Measure_2);
  vex::thread pid3(&Measure_3);

  float encVal = ((LB.rotation(ROT) + rot1 + rot2 + rot3) / 4);

  do {
    encVal = ((LB.rotation(ROT) + rot1 + rot2 + rot3) / 4);

    deltaD = encVal
    pidDrive = (-PID_DRIVE_MAX * std::cos(((2*PI*pidError)/deltaD)+encVal)) + (PID_DRIVE_MAX + PID_DRIVE_MIN)

    if (pidDrive > PID_DRIVE_MAX) {
      pidDrive = PID_DRIVE_MAX;
    }

    if (pidDrive < THRESHOLD) {
      LB.setStopping(COAST)
      close = true;
    }

    LB.spin(FWD, pidDrive, vPCT);
  } while (pidDrive >= PID_DRIVE_MIN);

  stop = true;
  LB.stop(BREAK);
  pid1.interrupt();
  pid2.interrupt();
  pid3.interrupt();
}