#include "balance_controller.h"
#include "hardware/motor_driver.h"
#include "utility/Logger.h"
#include "utility/shared_data.h"
#include "config.h"

BalanceController::BalanceController() : motor_driver_(MotorDriver()), pid_balance_(PID()), pid_heading_(PID()), 
                                            pid_speed_(PID()), pitch_setpoint_(0.f)
{
}

bool BalanceController::init()
{

    bool motorDriverInit = motor_driver_.init();
    if (motorDriverInit != true) // TODO -
    {
        Logger::debug("BalanceController - Something wrong in MotorDriver initialization.");
        return false;
    }

    if (!pid_balance_.setGains(0.f, 0.f, 0.f))
        return false;
    if (!pid_heading_.setGains(0.f, 0.f, 0.f))
        return false;
    if (!pid_speed_.setGains(0.f, 0.f, 0.f))
        return false;

    Logger::debug("BalanceController - BalanceController succesfully inited.");
    return true;
}

bool BalanceController::retrieveOrientationFromIMU(Orientation &orientationData)
{
    // Attempt to read from queue
    bool success = SharedData::receiveOrientationData(&orientationData);

    return success;
}

void BalanceController::updateMotorSpeeds(Orientation &orientationData, int &motorLeftSpeed, int &motorRightSpeed)
{
    float pitchSpeedComponent = pid_balance_.compute(orientationData.pitch, pitch_setpoint_);

    // Temporarily simply assign pitch correction to motor speed components
    motorLeftSpeed = pitchSpeedComponent;
    motorRightSpeed = pitchSpeedComponent;
}

void BalanceController::setMotorSpeeds(int motorLeftSpeed, int motorRightSpeed){

    motor_driver_.setMotorSpeeds(motorLeftSpeed, motorRightSpeed);

}