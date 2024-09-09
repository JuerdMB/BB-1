#include "IRS.h"

IRS::IRS()
{
    // Empty constructor
}

IRS::~IRS()
{
    // Empty descructor
}

void IRS::initialize()
{
    Wire.begin();
    Wire.setClock(100000); // Standard I2C speed (can lower to 100kHz if needed)

    bool initialized = false;

    while (!initialized)
    {

        if (icm.begin_SPI(ICM_CS, ICM_SCK, ICM_MISO, ICM_MOSI))
        {
            initialized = true;
        }

        else
        {
            logger.log(LOG_LEVEL_ERROR, "Failed to find ICM20948 chip, trying again");
            delay(500);
        }
    }

    logger.log(LOG_LEVEL_DEBUG, "ICM initialized");

    icm.setAccelRange(ICM20948_ACCEL_RANGE_16_G);

    switch (icm.getAccelRange())
    {
    case ICM20948_ACCEL_RANGE_2_G:
        logger.log(LOG_LEVEL_INFO, "+-2G");
        break;
    case ICM20948_ACCEL_RANGE_4_G:
        logger.log(LOG_LEVEL_INFO, "+-4G");
        break;
    case ICM20948_ACCEL_RANGE_8_G:
        logger.log(LOG_LEVEL_INFO, "+-8G");
        break;
    case ICM20948_ACCEL_RANGE_16_G:
        logger.log(LOG_LEVEL_INFO, "+-16G");
        break;
    }
}

bool IRS::update()
{
    //  /* Get a new normalized sensor event */
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t mag;
    sensors_event_t temp;
    icm.getEvent(&accel, &gyro, &temp, &mag);


    // Debug printing for serial plotter
    printSensorDataString(&accel, &gyro, &temp, &mag);

    // Do calculations to compute Transformation and Rotation vectors, and Quaternion from rawAccData, rawGyrData, rawMagData
    // This is where the kalman filter would come in, or I could use a simpler complementary filter
    pitch = computePitchComplementaryFilter(accel.acceleration.x, accel.acceleration.z);

    // If all is succesful, return true
    return true;
}

double IRS::computePitchComplementaryFilter(float accx, float accz)
{
    double pitch = 0.0;
    return pitch;
}

bool IRS::runChecks()
{
    // TODO: Fill rotation through convenient functions
    // pose.orientation.setRPY(/*Roll*/ 0, /*Pitch*/ 0, /*Yaw*/ 0); // Insert current pitch into quaternion

    // Save to history so we can do checks before overwritten
    // storePoseToHistory(pose);

    // Do calculations on pose history
    // runPoseChecks();

    return true;
}

void IRS_Task(void *pvParameters)
{
    IRS *irs = static_cast<IRS *>(pvParameters); // Cast pvParameters to IRS pointer
    irs->initialize();

    while (true)
    {
        if (irs->update())
        {

            if (!irs->runChecks())
            {
                // If something really bad happened, fix it here
            }
        }

        // irs->nodeHandle_->spinOnce();

        // Delay for appropriate sampling rate
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

    // Debug printing for serial plotter
void IRS::printSensorDataString(sensors_event_t *a, sensors_event_t *g, sensors_event_t *t, sensors_event_t *m)
{
    // Print accelerometer data
    Serial.print("\t\taccX: ");
    Serial.print(a->acceleration.x, 6); // Print with 6 decimal places
    Serial.print("\t\taccY: ");
    Serial.print(a->acceleration.y, 6);
    Serial.print("\t\taccZ: ");
    Serial.print(a->acceleration.z, 6);

    // Print gyroscope data
    Serial.print("\t\tgyrX:");
    Serial.print(g->gyro.x, 6);
    Serial.print("\t\tgyrY:");
    Serial.print(g->gyro.y, 6);
    Serial.print("\t\tgyrZ:");
    Serial.print(g->gyro.z, 6);

    // Print magnetometer data
    Serial.print("\t\tmagX:");
    Serial.print(m->magnetic.x, 6);
    Serial.print("\t\tmagY:");
    Serial.print(m->magnetic.y, 6);
    Serial.print("\t\tmagZ:");
    Serial.println(m->magnetic.z, 6);
}