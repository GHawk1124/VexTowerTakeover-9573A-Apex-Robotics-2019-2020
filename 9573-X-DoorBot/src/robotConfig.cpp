#include "robotConfig.h"

vex::brain Brain;

vex::motor RF = vex::motor(RF_P, MID_RATIO, true);
vex::motor LF = vex::motor(LF_P, MID_RATIO, false);
vex::motor_group driveTrain = vex::motor_group(RF, LF);

vex::motor LIFT_1 = vex::motor(LIFT_1_P, TORQUE_RATIO, false);
vex::motor LIFT_2 = vex::motor(LIFT_2_P, TORQUE_RATIO, true);
vex::motor_group Lift = vex::motor_group(LIFT_1, LIFT_2);

vex::motor CLAW_1 = vex::motor(CLAW_1_P, MID_RATIO, true);
vex::motor CLAW_2 = vex::motor(CLAW_2_P, MID_RATIO, false);
vex::motor_group Claw = vex::motor_group(CLAW_1, CLAW_2);

vex::controller Controller;
vex::competition Competition;