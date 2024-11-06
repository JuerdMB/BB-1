#include "motion_controller.h"
#include "hardware/motor_driver.h"
#include "utility/Logger.h"
#include "utility/shared_data.h"
#include "config.h"

MotionController::MotionController() : motor_driver_(MotorDriver()), pid_balance_(PID()), pid_heading_(PID()), 
                                            pid_speed_(PID())
{
}

bool MotionController::init()
{

    bool motorDriverInit = motor_driver_.init();
    if (motorDriverInit != true) // TODO -
    {
        LOG_DEBUG("MotionController - Something wrong in MotorDriver initialization.");
        return false;
    }

    if (!pid_balance_.setGains(0.f, 0.f, 0.f))
        return false;
    if (!pid_heading_.setGains(0.f, 0.f, 0.f))
        return false;
    if (!pid_speed_.setGains(0.f, 0.f, 0.f))
        return false;

    LOG_DEBUG("MotionController - MotionController succesfully inited.");
    return true;
}

bool MotionController::retrieveOrientationFromIMU(Orientation &orientationData)
{
    // Attempt to read from queue
    bool success = SharedData::receiveOrientationData(&orientationData);

    return success;
}

void MotionController::setMotorSpeeds(int motorLeftSpeed, int motorRightSpeed){

    motor_driver_.setMotorSpeeds(motorLeftSpeed, motorRightSpeed);

}