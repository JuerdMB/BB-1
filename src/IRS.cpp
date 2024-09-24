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

    // Calculate time interval since last measurement
    uint32_t now = micros();
    uint32_t dT = now - last_icm_update;
    last_icm_update = now;

    // Debug printing for serial plotter
    printSensorDataString(&accel, &gyro, &temp, &mag);

    // Compute orientation vector
    // This is where the kalman filter would come in, or I could use a simpler complementary filter
    computeOrientation(&accel.acceleration, &gyro.gyro, &mag.magnetic, dT);

    // If all is succesful, return true
    return true;
}

void IRS::computeOrientation(const sensors_vec_t *acc, const sensors_vec_t *gyr, const sensors_vec_t *mag, uint32_t dT)
{
    orientation3 orientation_change;

    // Compute pitch in radians from accelerometers x and z
    double pitch_accelerometers = atan2(acc->x, acc->z);

    // Compute yaw rate from gyro_y.
    float pitch_change = gyr->y * dT;

    // Combine with complementary filter.
    orientation.p = (orientation_prev.p + pitch_change) * COMPLEMENTARY_FILTER_ALPHA_PITCH + pitch_accelerometers * (1. - COMPLEMENTARY_FILTER_ALPHA_PITCH);

    // Store current orientation for orientation rate in next cycle
    orientation_prev = orientation;
}

const orientation3 *IRS::getOrientation()
{
    return &orientation;
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