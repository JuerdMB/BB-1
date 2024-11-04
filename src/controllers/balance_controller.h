#pragma once

#include "hardware/motor_driver.h"
#include "controllers/pid_controller.h"
#include "utility/utils.h"

class BalanceController
{
public:
    BalanceController();
    bool init();
    bool retrieveOrientationFromIMU(Orientation &orientationData);
    void updateMotorSpeeds(Orientation &orientationData, int &motorLeftSpeed, int &motorRightSpeed);
    void setMotorSpeeds(int motorLeftSpeed, int motorRightSpeed);

private:
    MotorDriver motor_driver_;
    PID pid_balance_;
    PID pid_heading_;
    PID pid_speed_;
    float pitch_setpoint_;
};
