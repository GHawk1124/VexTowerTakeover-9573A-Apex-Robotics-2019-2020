#include "robotConfig.h"

vex::brain Brain;

vex::motor RF = vex::motor(RF_P, MID_RATIO, true);
vex::motor LF = vex::motor(LF_P, MID_RATIO, false);
vex::motor RB = vex::motor(RB_P, MID_RATIO, true);
vex::motor LB = vex::motor(LB_P, MID_RATIO, false);
vex::motor_group rightDT = vex::motor_group(RF, RB);
vex::motor_group leftDT = vex::motor_group(LF, LB);
vex::motor_group driveTrain = vex::motor_group(RF, LF);

vex::motor LIFT = vex::motor(LIFT_P, MID_RATIO, true);
vex::motor_group Lift = vex::motor_group(LIFT);

vex::motor INTAKE_1 = vex::motor(INTAKE_1_P, MID_RATIO, true);
vex::motor INTAKE_2 = vex::motor(INTAKE_2_P, MID_RATIO, false);
vex::motor_group Intake = vex::motor_group(INTAKE_1, INTAKE_2);

vex::controller Controller;
vex::competition Competition;