#ifndef USER_CONFIG
#define USER_CONFIG

/* Driver */

// Sets the Stopping Type for Auton and Drive
// Hold: Motor holds at end position, Brake: Hardstop forces motor at end
// position, Coast: Motor stops due to friction
#define MOTOR_STOPPING_AUTON BRAKE // HOLD : BRAKE : COAST
#define MOTOR_STOPPING_DRIVE COAST // HOLD : BRAKE : COAST

/* Robot */

// Define for each Robot
#define WHEEL_DIAMETER 4 // FLOAT
#define WHEEL_CIRCUM WHEEL_DIAMETER * PI
#define PI 3.14159265358
#define BOT_WIDTH 13.0 // FLOAT

#endif

#ifndef CONSTANTS
#define CONSTANTS
/* Ports */

// Define for each Robot
#define RF_P vex::PORT1
#define LF_P vex::PORT2
#define RB_P vex::PORT3
#define LB_P vex::PORT4
#define LEFT_LIFT_P vex::PORT5
#define RIGHT_LIFT_P vex::PORT6
#define CLAW_LEFT_P vex::PORT7
#define CLAW_RIGHT_P vex::PORT8

// Consts
#define LIFT_SPEED 75
#define CLAW_SPEED 100
#define MAX_SPEED 100
#define MIN_SPEED_AUTON 5
#define HALF_SPEED 50
#define OFF 0

// Button Maps
#define RAISE_LIFT ButtonR1.pressing
#define LOWER_LIFT ButtonR2.pressing
#define OPEN_CLAW ButtonL1.pressing

#endif
