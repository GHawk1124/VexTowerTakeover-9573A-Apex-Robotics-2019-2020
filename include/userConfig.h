#ifndef USER_CONFIG
#define USER_CONFIG

/* Driver */

// Single Stick Arcade: Left Stick Controls Bot
// Two Stick Arcade: Left Stick Controls Forward/Backward, Right Stick Controls Left/Right
// Tank: Left Stick Controls Forward/Backward Left Side of Bot, Right Stick Controls Forward/Backward Right Side of Bot
#define DRIVE_TYPE TANK // SS_ARCADE : TS_Arcade : TANK

// Sets the Stopping Type for Auton and Drive
// Hold: Motor holds at end position, Brake: Hardstop forces motor at end position, Coast: Motor stops due to friction
#define MOTOR_STOPPING_AUTON COAST // HOLD : BRAKE : COAST
#define MOTOR_STOPPING_DRIVE COAST // HOLD : BRAKE : COAST


/* Robot */

// Define for each Robot
#define WHEEL_DIAMETER 4.00 // FLOAT
#define PI 3.14159265
#define WHEEL_CIRCUM WHEEL_DIAMETER*PI // FLOAT
#define BOT_WIDTH 12.00 // FLOAT

/* Ports */

// Define for each Robot
#define RF_P vex::PORT1
#define LF_P vex::PORT10
//#define RB_P vex::PORT11
//#define LB_P vex::PORT20
#define LIFT_1_P vex::PORT2
#define LIFT_2_P vex::PORT9
#define INTAKE_1_P vex::PORT11
#define INTAKE_2_P vex::PORT20

#endif