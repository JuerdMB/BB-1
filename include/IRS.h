#pragma once

/*
 *  This is the Inertial reference System of the robot.
 *  It provides access to filtered data from the sensors.
 *  It takes care of all error checking and filtering, which it abstracts away.
 */

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include "Logger.h"
#include "dataTypes.h"

// ICM SPI ports
#define ICM_CS 5
#define ICM_SCK 18
#define ICM_MISO 19
#define ICM_MOSI 23

#define COMPLEMENTARY_FILTER_ALPHA_PITCH .05

extern Logger &logger;

class IRS
{
public:
    IRS();
    ~IRS();

    void initialize();

    bool update();

    bool runChecks();

    const orientation3* getOrientation();

private:
    /* ICM-20948 sensor */
    Adafruit_ICM20948 icm;
    uint32_t last_icm_update;

    /* Robot pose data */
    orientation3 orientation;
    orientation3 orientation_prev;
    vec3 position;

    void computeOrientation(const sensors_vec_t *acc, const sensors_vec_t *gyr, const sensors_vec_t *mag, uint32_t dT);

    /* Helper functions*/
    void printSensorDataString(sensors_event_t *a, sensors_event_t *g, sensors_event_t *t, sensors_event_t *m);
};

void IRS_Task(void *pvParameters);
