#pragma once

template <typename T>
class PID
{
public:
    PID(float kP, float kI, float kD);
    PID(float kP, float kI, float kD, T constrain_min, T constrain_max);
    bool setGains(float kP, float kI, float kD);
    float compute(T input, T setPoint);
    bool setConstraints(T min, T max);

private:
    bool constrained_;
    T constrained_min_;
    T constrained_max_;
    float kP_;
    float kI_;
    float kD_;
};
