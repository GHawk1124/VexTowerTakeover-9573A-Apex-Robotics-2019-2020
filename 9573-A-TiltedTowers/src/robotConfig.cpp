#include "robotConfig.h"

vex::brain Brain;

vex::motor RF (RF_P, MID_RATIO, true);
vex::motor LF (LF_P, MID_RATIO, false);
vex::motor RB (RB_P, MID_RATIO, true);
vex::motor LB (LB_P, MID_RATIO, false);
vex::motor_group rightDT (RF, RB);
vex::motor_group leftDT (LF, LB);
vex::motor_group driveTrain (RF, LF, RB, LB);

vex::motor LIFT (LIFT_P, TORQUE_RATIO, true);
vex::motor_group Lift (LIFT);

vex::motor INTAKE_1 (INTAKE_1_P, TORQUE_RATIO, true);
vex::motor INTAKE_2 (INTAKE_2_P, TORQUE_RATIO, false);
vex::motor_group Intake (INTAKE_1, INTAKE_2);

vex::controller Controller;
vex::competition Competition;