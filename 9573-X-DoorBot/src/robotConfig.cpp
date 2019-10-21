#include "robotConfig.h"

vex::brain Brain;

vex::motor RF = vex::motor(RF_P, MID_RATIO, true);
vex::motor LF = vex::motor(LF_P, MID_RATIO, false);
vex::motor RB = vex::motor(RB_P, MID_RATIO, true);
vex::motor LB = vex::motor(LB_P, MID_RATIO, false);
vex::motor_group driveTrainLeft = vex::motor_group(LF, LB);
vex::motor_group driveTrainRight = vex::motor_group(RF, RB);
vex::motor_group driveTrain = vex::motor_group(RF, LF, RB, LB);

vex::motor LEFT_LIFT = vex::motor(LEFT_LIFT_P, TORQUE_RATIO, false);
vex::motor RIGHT_LIFT = vex::motor(RIGHT_LIFT_P, TORQUE_RATIO, true);
vex::motor_group Lift = vex::motor_group(LEFT_LIFT, RIGHT_LIFT);

vex::motor Claw = vex::motor(CLAW_P, MID_RATIO, true);

vex::controller Controller;
vex::competition Competition;