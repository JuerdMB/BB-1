#pragma once

#if defined(ARDUINO)
#include <Wire.h>
#include <Adafruit_ICM20948.h>
#include "utility/shared_data.h"
#endif

// #define IMU_USE_INTERRUPT

enum IMU_ERROR_CODE {
    IMU_INIT_SUCCEEDED,
    IMU_INIT_FAILED,
}; 

class IMU
{
public:
    IMU();
    int init();
    void retrieveRawData();
    void updateFilteredOrientation();
    void publishFilteredOrientation();

private:
    Adafruit_ICM20948 icm_;
    RawIMUdata latestIMUData_;
    Orientation currentOrientation_;
    Orientation previousOrientation_;
    uint32_t lastOrientationUpdate_;
};

