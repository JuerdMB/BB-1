#pragma once

/*
 *  This is the Inertial reference System of the robot.
 *  It provides access to filtered data from the sensors.
 *  It takes care of all error checking and filtering, which it abstracts away.
 */

#include "definitions.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "Logger.h"

class IMU
{
public:
    IMU();
    void start();
    void run(); // TODO check why we got no error that this function was inaccessible in task function back when this function was still private

private:
    // Initialisation functions
    static void imuTask(void *imuInstance);
    void init();
    bool isDataReady();

    // Runtime functions
    void readRawData();
    void updateFilteredOrientation();
    void publishFilteredOrientation();

    // Objects
    Adafruit_ICM20948 imu;
    // ROSNode rosNode; // TODO implement ROS functionality
    SemaphoreHandle_t orientation_mutex_;
    orientation3D orientation_;

    volatile bool dataReady;
    unsigned long last_imu_update;
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t mag;
    sensors_event_t temperature;
    float pitch_filtered_prev;
};