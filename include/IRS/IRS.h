#pragma once

#include <Arduino.h>
#include "IMU.h"

class IRS
{
public:
    IRS();
    bool init();    // TODO - Create error type for error checking
    void readRawData();
    void updateFilteredOrientation();
    void publishFilteredOrientation();
    bool isDataReady();

private:
    IMU imu_;
};