#ifndef USER_CONFIG
#define USER_CONFIG

/* Driver */

// Single Stick Arcade: Left Stick Controls Bot
// Two Stick Arcade: Left Stick Controls Forward/Backward, Right Stick Controls
// Left/Right Tank: Left Stick Controls Forward/Backward Left Side of Bot, Right
// Stick Controls Forward/Backward Right Side of Bot
#define DRIVE_TYPE 1 // 3 SS_ARCADE : 2 TS_Arcade : 1 TANK

// Sets the Stopping Type for Auton and Drive
// Hold: Motor holds at end position, Brake: Hardstop forces motor at end
// position, Coast: Motor stops due to friction
#define MOTOR_STOPPING_AUTON COAST // HOLD : BRAKE : COAST
#define MOTOR_STOPPING_DRIVE COAST // HOLD : BRAKE : COAST

/* Robot */

// Define for each Robot
#define WHEEL_DIAMETER 4.00 // FLOAT
#define PI 3.14159265
#define BOT_WIDTH 12.00                 // FLOAT

/* Ports */

// Define for each Robot
#define RF_P vex::PORT1
#define LF_P vex::PORT10
#define LIFT_P vex::PORT12
#define INTAKE_1_P vex::PORT11
#define INTAKE_2_P vex::PORT20

#endif