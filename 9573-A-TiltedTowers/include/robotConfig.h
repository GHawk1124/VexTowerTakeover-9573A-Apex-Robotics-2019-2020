#ifndef ROBOT_CONFIG
#define ROBOT_CONFIG

#ifndef VEX
#define VEX
#include "vex.h"
#endif

#include "userConfig.h"

#ifndef RM_STANDARD_V5_DEFINITIONS
#define RM_STANDARD_V5_DEFINITIONS

// Gear Settings
#define SPEED_RATIO vex::gearSetting::ratio6_1
#define MID_RATIO vex::gearSetting::ratio18_1
#define TORQUE_RATIO vex::gearSetting::ratio36_1
// Directions
#define FWD vex::directionType::fwd
#define BWD vex::directionType::rev
// Velocity Units
#define vPCT vex::velocityUnits::pct
// Rotation Units
#define DEG vex::rotationUnits::deg
#define ROT vex::rotationUnits::rev
#define RAW vex::rotationUnits::raw
// Percent Units
#define PCT vex::percentUnits::pct
// Time Units
#define M_SEC vex::timeUnits::msec
#define SEC vex::timeUnits::sec
// Brake Types
#define BRAKE vex::brakeType::brake
#define HOLD vex::brakeType::hold
#define COAST vex::brakeType::coast
// Controller
#define RIGHT_JOY_VERT Axis2.position
#define RIGHT_JOY_HORIZ Axis1.position
#define LEFT_JOY_VERT Axis3.position
#define LEFT_JOY_HORIZ Axis4.position
// Consts
#define LIFT_SPEED 100
#define INTAKE_SPEED 100
#define MAX_SPEED 100
#define HALF_SPEED 50
#define OFF 0

#endif

// Extern so cpp module can define
extern vex::brain Brain;

extern vex::motor RF;
extern vex::motor LF;
// extern vex::motor RB;
// extern vex::motor LB;
extern vex::motor_group driveTrain;

extern vex::motor LIFT_1;
extern vex::motor LIFT_2;
extern vex::motor_group Lift;

extern vex::motor INTAKE_1;
extern vex::motor INTAKE_2;
extern vex::motor_group Intake;

extern vex::controller Controller;
extern vex::competition Competition;

#endif