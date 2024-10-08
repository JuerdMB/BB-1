#include "MotorControlSystem/BalanceController.h"
#include "MotorControlSystem/MotorDriver.h"
#include "utility/Logger.h"

BalanceController::BalanceController() : motor_driver_(MotorDriver()), pid_balance_(PID()), pid_heading_(PID()), pid_speed_(PID())
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

OrientationData BalanceController::getOrientationData()
{
    OrientationData orientationData;
    return orientationData;
}

void BalanceController::updateMotorSpeeds()
{
}