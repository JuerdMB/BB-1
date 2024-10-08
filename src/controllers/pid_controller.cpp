#include "pid_controller.h"
#include "utility/Logger.h"

PID::PID(): kP_(0.f), kI_(0.f), kD_(0.f)
{
}

bool PID::setGains(float kP, float kI, float kD)
{
    if (kP >= 0.f && kI >= 0.f && kD >= 0.f)
    {
        kP_ = kP;
        kI_ = kI;
        kD_ = kD;

        Logger::debug("PID - PID gains succesfully set to %2f(kP), %2f(kI), %2f(kD)", kP, kI, kD);
        return true;
    }

    Logger::debug("PID - setGains unsuccesful: Invalid PID gains %2f(kP), %2f(kI), %2f(kD)", kP, kI, kD);
    return false;
}

float PID::compute(float input, float setPoint)
{
    return 0.f;
}