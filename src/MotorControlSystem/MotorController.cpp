#include "MotorControlSystem/MotorController.h"
#include "MotorControlSystem/MotorDriver.h"
#include "utility/Logger.h"

MotorController::MotorController() : motor_driver_(MotorDriver()), pid_balance_(PID()), pid_heading_(PID()), pid_speed_(PID())
{
}

bool MotorController::init()
{

    bool motorDriverInit = motor_driver_.init();
    if (motorDriverInit != true) // TODO -
    {
        Logger::debug("MotorController - Something wrong in MotorDriver initialization.");
        return false;
    }

    if (!pid_balance_.setGains(0.f, 0.f, 0.f))
        return false;
    if (!pid_heading_.setGains(0.f, 0.f, 0.f))
        return false;
    if (!pid_speed_.setGains(0.f, 0.f, 0.f))
        return false;

    Logger::debug("MotorController - MotorController succesfully inited.");
    return true;
}

bool MotorController::updateOrientationData()
{
    // Tester implementation randomizes true value
    bool isTrue = (bool)random(2);
    return isTrue;
}

void MotorController::updateMotorSpeeds()
{
}

void MotorController::setMotorSpeeds()
{
}