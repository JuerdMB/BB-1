#pragma once

#include "hardware/motor_driver.h"

#include "utility/utils.h"

enum MotionControllerError
{
    MOTION_CONTROLLER_SETUP_FAILED,
    MOTION_CONTROLLER_INVALID_GPIO,
    MOTION_CONTROLLER_SETUP_SUCCESS
};

class MotionController
{
public:
    MotionController();
    MotionControllerError init();
    bool retrieveOrientationFromIMU(Orientation &orientationData);
    void setMotorSpeeds(int motorLeftSpeed, int motorRightSpeed);

private:
    MotorDriver motor_driver_;
};
