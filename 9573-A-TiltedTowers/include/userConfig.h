#ifndef USER_CONFIG
#define USER_CONFIG

/* Driver */

// Single Stick Arcade: Left Stick Controls Bot
// Two Stick Arcade: Left Stick Controls Forward/Backward, Right Stick Controls
// Left/Right Tank: Left Stick Controls Forward/Backward Left Side of Bot, Right
// Stick Controls Forward/Backward Right Side of Bot
#define DRIVE_TYPE 3 // 2 SS_ARCADE : 3 TS_Arcade : 1 TANK

/* Consts */
#define LIFT_SPEED 65
#define INTAKE_SPEED 85
#define MAX_SPEED 75
#define MAX_SPEED_AUTON 100
#define HALF_SPEED 50
#define OFF 0
#define DRIVE_TRAIN_SPEED_RATIO 1

// Sets the Stopping Type for Auton and Drive
// Hold: Motor holds at end position, Brake: Hardstop forces motor at end
// position, Coast: Motor stops due to friction
#define MOTOR_STOPPING_AUTON COAST // HOLD : BRAKE : COAST
#define MOTOR_STOPPING_DRIVE COAST // HOLD : BRAKE : COAST

/* Robot */

// Define for each Robot
#define WHEEL_DIAMETER 2.50 // FLOAT
#define PI 3.14159265
#define BOT_WIDTH 14.50                 // FLOAT

/* Ports */

// Define for each Robot
#define RF_P vex::PORT19
#define LF_P vex::PORT12
#define RB_P vex::PORT20
#define LB_P vex::PORT11
#define LIFT_P vex::PORT9
#define INTAKE_1_P vex::PORT10
#define INTAKE_2_P vex::PORT2

#endif