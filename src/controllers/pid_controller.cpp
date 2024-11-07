#include "pid_controller.h"
#include "utility/Logger.h"

template <typename T>
PID<T>::PID(float kP, float kI, float kD): kP_(kP), kI_(kI), kD_(kD)
{
}

template <typename T>
bool PID<T>::setGains(float kP, float kI, float kD)
{
    if (kP >= 0.f && kI >= 0.f && kD >= 0.f)
    {
        kP_ = kP;
        kI_ = kI;
        kD_ = kD;

        LOG_DEBUG("PID - PID gains succesfully set to %2f(kP), %2f(kI), %2f(kD)", kP, kI, kD);
        return true;
    }

    LOG_DEBUG("PID - setGains unsuccesful: Invalid PID gains %2f(kP), %2f(kI), %2f(kD)", kP, kI, kD);
    return false;
}

template <typename T>
float PID<T>::compute(T input, T setPoint)
{
    T result;
    return T;
}