#include "robotConfig.h"

vex::brain Brain;

vex::motor RF(RF_P, MID_RATIO, true);
vex::motor LF(LF_P, MID_RATIO, false);
vex::motor RB(RB_P, MID_RATIO, true);
vex::motor LB(LB_P, MID_RATIO, false);
vex::motor_group driveTrainLeft(LF, LB);
vex::motor_group driveTrainRight(RF, RB);
vex::motor_group driveTrainXLeft(LF, RB);
vex::motor_group driveTrainXRight(RF, LB);
vex::motor_group driveTrain(LF, RF, LB, RB);

vex::motor LEFT_LIFT(LEFT_LIFT_P, TORQUE_RATIO, false);
vex::motor RIGHT_LIFT(RIGHT_LIFT_P, TORQUE_RATIO, true);
vex::motor_group Lift(LEFT_LIFT, RIGHT_LIFT);

vex::motor ClawLeft(CLAW_LEFT_P, TORQUE_RATIO, true);
vex::motor ClawRight(CLAW_RIGHT_P, TORQUE_RATIO, true);
vex::motor_group Claw(ClawLeft, ClawRight);

vex::controller Controller;
vex::competition Competition;