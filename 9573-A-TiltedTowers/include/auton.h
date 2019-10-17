#ifndef AUTON
#define AUTON

#include "robotConfig.h"

void driveInches(double inches,
                 vex::brakeType brakeType = MOTOR_STOPPING_AUTON);

void pointTurn(double degrees, vex::brakeType brakeType = MOTOR_STOPPING_AUTON);

void fSwingTurn(double degrees,
                vex::brakeType brakeType = MOTOR_STOPPING_AUTON);

void bSwingTurn(double degrees,
                vex::brakeType brakeType = MOTOR_STOPPING_AUTON);

#endif