#pragma once

/*  This is the Inertial reference System of the robot.
 *   It provides access to filtered data from the sensors.
 *   It takes care of all error checking and filtering, which it abstracts away.
 *
 *   The class acts as a ROS node with namespace "IRS"
 */

#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SimpleKalmanFilter.h>
#include <Logger.h>

#define NAMESPACE "IRS"

// ICM SPI ports
#define ICM_CS 5
#define ICM_SCK 18
#define ICM_MISO 19
#define ICM_MOSI 23

#define COMPLEMENTARY_FILTER_ALPHA_PITCH .05

extern Logger& logger;

class IRS
{
public:
    IRS();
    ~IRS();

    void initialize();
    bool update();
    bool runChecks();

private:
    /* ICM-20948 sensor object and ports, to be defined upon startup */
    Adafruit_ICM20948 icm;
    void printSensorDataString(sensors_event_t *a, sensors_event_t *g, sensors_event_t *t, sensors_event_t *m);

    // Temporary pitch as double, and function to calculate it
    double computePitchComplementaryFilter(float accx, float accz, float gyrY, uint32_t dT);
    double pitch;
    double pitch_previous;

    uint32_t last_icm_update;

    // Variables to store robot pose information
    // Pose
    // void storePoseToHistory(pose);
};

void IRS_Task(void *pvParameters);

