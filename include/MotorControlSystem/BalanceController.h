#pragma once

#include "MotorDriver.h"
#include "PID.h"
#include "data_types.h"

class BalanceController
{
public:
    BalanceController();
    bool init();
    OrientationData getOrientationData();
    void updateMotorSpeeds();

private:
    MotorDriver motor_driver_;
    PID pid_balance_;
    PID pid_heading_;
    PID pid_speed_;
};
