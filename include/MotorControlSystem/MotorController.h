#pragma once

#include "MotorDriver.h"
#include "PID.h"

class MotorController
{
public:
    MotorController();
    bool init();
    bool updateOrientationData();
    void updateMotorSpeeds();
    void setMotorSpeeds();

private:
    MotorDriver motor_driver_;
    PID pid_balance_;
    PID pid_heading_;
    PID pid_speed_;
};
