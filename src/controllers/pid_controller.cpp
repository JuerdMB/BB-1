#include "pid_controller.h"
#include "utility/Logger.h"

template <typename T>
PID<T>::PID(float kP, float kI, float kD): kP_(kP), kI_(kI), kD_(kD), constrained_(false)
{
}

template <typename T>
PID<T>::PID(float kP, float kI, float kD, T constrain_min, T constrain_max)
{
    PID(kP, kI, kD);
    setConstraints(constrain_min, constrain_max);
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

    // If PID constraints are set, constrain result to min-max
    if(constrained_ && (result < constrained_min_ || result > constrained_max_)){
        T result_old = result;
        result = constrain(result, constrained_min_, constrained_max_);
        LOG_DEBUG("PID output values out of bounds: %d, constraining to %d", result, result_old);
    }

    return result;
}

template <typename T>
bool PID<T>::setConstraints(T min, T max){

    // Bounds checking
    if(min >= max) {
        LOG_WARN("Invalid PID constrain values");
        return false;
    }

    constrained_ = true;
    constrained_min_ = min;
    constrained_max_ = max;
    return true;
}