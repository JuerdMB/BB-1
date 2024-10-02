#pragma once

/*
 *  This is the Inertial reference System of the robot.
 *  It provides access to filtered data from the sensors.
 *  It takes care of all error checking and filtering, which it abstracts away.
 */

#include "Logger/Logger.h"
#include "definitions.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>

class IMU
{
public:
    IMU();
    ~IMU();
    void begin();
    const orientation3D getOrientation();

private:
    Adafruit_ICM20948 icm;
    unsigned long last_icm_update;
    orientation3D orientation;
    orientation3D orientation_prev;

    void init();
    void setDataReadyCallback();

    void readRawData()
    void imuTask(void *pvParameters);
    void computeOrientation(const sensors_vec_t *acc, const sensors_vec_t *gyr, const sensors_vec_t *mag, uint32_t dT);
};