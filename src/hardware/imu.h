#pragma once

#if defined(ARDUINO)
#include <Wire.h>
#include <Adafruit_ICM20948.h>
#include "utility/shared_data.h"
#endif

// #define IMU_USE_INTERRUPT

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
    int init();
    int retrieveRawData(RawIMUdata &dataContainer);
    void updateFilteredOrientation(RawIMUdata &rawIMUdata);
    void publishFilteredOrientation();

private:
    Adafruit_ICM20948 icm_;
    Orientation currentOrientation_;
    Orientation previousOrientation_;
    uint32_t lastOrientationUpdate_;
};

