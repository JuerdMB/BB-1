#pragma once

#include "hardware/motor_driver.h"
#include "controllers/pid_controller.h"
#include "utility/utils.h"

class MotionController
{
public:
    MotionController();
    bool init();
    bool retrieveOrientationFromIMU(Orientation &orientationData);
    void setMotorSpeeds(int motorLeftSpeed, int motorRightSpeed);

    PID pid_balance_;
    PID pid_heading_;
    PID pid_speed_;

private:
    MotorDriver motor_driver_;
};
