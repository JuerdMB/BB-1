#pragma once

#include <Wire.h>
#include <Adafruit_ICM20948.h>
#include "utility/shared_data.h"
#include "config.h"


enum IMU_INIT_ERROR {
    IMU_INIT_SUCCEEDED,
    IMU_INIT_FAILED,
}; 

enum IMU_READ_ERROR {
    IMU_READ_SUCCESS,
    IMU_READ_FAILED
};

class IMU
{
public:
    IMU();
    IMU_INIT_ERROR init();
    IMU_READ_ERROR retrieveRawData(RawIMUdata &dataContainer);
    void updateFilteredOrientation(RawIMUdata &rawIMUdata, Orientation &currentOrientation);
    void publishFilteredOrientation(Orientation &currentOrientation);

private:
    Adafruit_ICM20948 icm_;
    Orientation previousOrientation_;
    uint32_t lastOrientationUpdate_;
};

