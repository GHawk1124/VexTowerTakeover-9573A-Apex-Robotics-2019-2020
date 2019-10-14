#ifndef AUTON
#define AUTON

#include "robotConfig.h"

void driveInches(double inches, vex::brakeType brakeType=MOTOR_STOPPING_AUTON);

void turn(int degrees);

#endif