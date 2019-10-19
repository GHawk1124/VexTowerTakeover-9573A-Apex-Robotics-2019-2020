#include "robotConfig.h"

vex::brain Brain;

vex::motor RF = vex::motor(RF_P, MID_RATIO, true);
vex::motor LF = vex::motor(LF_P, MID_RATIO, false);
vex::motor RB = vex::motor(RB_P, MID_RATIO, true);
vex::motor LB = vex::motor(LB_P, MID_RATIO, false);
vex::motor_group driveTrain = vex::motor_group(RF, LF, RB, LB);

vex::motor LIFT_1 = vex::motor(LIFT_1_P, TORQUE_RATIO, false);
vex::motor LIFT_2 = vex::motor(LIFT_2_P, TORQUE_RATIO, true);
vex::motor_group Lift = vex::motor_group(LIFT_1, LIFT_2);

vex::motor Claw = vex::motor(CLAW_P, MID_RATIO, true);

vex::controller Controller;
vex::competition Competition;