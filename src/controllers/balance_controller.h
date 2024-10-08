#pragma once

#include "hardware/motor_driver.h"
#include "controllers/pid_controller.h"
#include "utility/utils.h"

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
