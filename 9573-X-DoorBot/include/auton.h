#ifndef AUTON
#define AUTON

#include "robotConfig.h"

void driveTo(double xInches, double yInches);

void pointTurn(double degrees);

void closeClaw();

void openClaw();

void liftTo(double degrees);

#endif