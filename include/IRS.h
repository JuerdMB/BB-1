#pragma once

#include <Arduino.h>
#include "IMU.h"

class IRS
{
public:
    IRS();
    bool init();    // TODO - Create error type for error checking

private:
    IMU imu_;
};