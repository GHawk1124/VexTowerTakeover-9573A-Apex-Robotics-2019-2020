#ifndef AUTON
#define AUTON

#include "pid.h"
#include "robotConfig.h"


/*
 * @brief Drives a specific number of inches that stops with a specific stopping
 *  type.
 * @param inches Sets the number of inches for the DriveTrain to move.
 * @param brakeType Sets the brakeType for when the function completes.
 */
void driveInches(double inches,
                 vex::brakeType brakeType = MOTOR_STOPPING_AUTON);

/*
 * @brief Turns the bot a specific number of degrees while staying in place.
 *  (Rotates around Center of Robot)
 * @param degrees Sets the number of degrees for the DriveTrain to turn.
 * @param brakeType Sets the brakeType for when the function completes.
 */
void pointTurn(double degrees, vex::brakeType brakeType = MOTOR_STOPPING_AUTON);

/*
 * @brief Turns the bot a specific number of degrees while staying in place.
 *  (Rotates around top left or top right wheel)
 * @param degrees Sets the number of degrees for the DriveTrain to rotate.
 * @param brakeType Sets the brakeType for when the function completes.
 */
void fSwingTurn(double degrees,
                vex::brakeType brakeType = MOTOR_STOPPING_AUTON);

/*
 * @brief Turns the bot a specific number of degrees while staying in place.
 *  (Rotates around bottom left or bottom right wheel)
 * @param degrees Sets the number of degrees for the DriveTrain to rotate.
 * @param brakeType Sets the brakeType for when the function completes.
 */
void bSwingTurn(double degrees,
                vex::brakeType brakeType = MOTOR_STOPPING_AUTON);

#endif