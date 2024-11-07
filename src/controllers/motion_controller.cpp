#include "motion_controller.h"
#include "hardware/motor_driver.h"
#include "utility/Logger.h"
#include "utility/shared_data.h"
#include "config.h"

MotionController::MotionController() : motor_driver_(MotorDriver())
{
}

MotionControllerError MotionController::init()
{
    bool motorDriverInit = motor_driver_.init();
    if (motorDriverInit != true) // TODO -
    {
        LOG_DEBUG("MotionController - Something wrong in MotorDriver initialization.");
        return MOTION_CONTROLLER_SETUP_FAILED;
    }

    LOG_DEBUG("MotionController - MotionController succesfully inited.");
    return MOTION_CONTROLLER_SETUP_SUCCESS;
}

bool MotionController::retrieveOrientationFromIMU(Orientation &orientationData)
{
    // Attempt to read from queue
    bool success = SharedData::receiveOrientationData(&orientationData);

    return success;
}

void MotionController::setMotorSpeeds(int motorLeftSpeed, int motorRightSpeed)
{

    motor_driver_.setMotorSpeeds(motorLeftSpeed, motorRightSpeed);
}