#ifndef AUTON
#define AUTON

#include "robotConfig.h"

void driveInches(double inches);

void strafeInches(double inches);

void pointTurn(double degrees);

void closeClaw();

void openClaw();

void liftTo(double degrees);

#endif