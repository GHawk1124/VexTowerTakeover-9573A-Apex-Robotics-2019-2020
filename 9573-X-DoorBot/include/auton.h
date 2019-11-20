#ifndef AUTON
#define AUTON
#include "robotConfig.h"

void driveInches(double inches);

void strafeInches(double inches);

void pointTurn(double rots);

void closeClaw();

void openClaw();

void liftTo(double degrees);

#endif