#pragma once

template <typename T>
class PID
{
public:
    PID(float kP, float kI, float kD);
    bool setGains(float kP, float kI, float kD);
    float compute(T input, T setPoint);

private:
    float kP_;
    float kI_;
    float kD_;
};
