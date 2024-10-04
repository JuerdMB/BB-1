#pragma once

#include <Arduino.h>
#include "IMU.h"

class IRS
{
public:
    IRS();
    void init();
    void readRawData();
    void updateFilteredOrientation();
    void publishFilteredOrientation();
    bool isDataReady();

private:
    IMU imu_;
};