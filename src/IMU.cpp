#include "IMU.h"
#include "config.h"
#include "Logger/Logger.h"

IMU::IMU()
{
}

IMU::~IMU()
{
}

void IMU::start()
{
    Wire.begin();
    Wire.setClock(100000);

    bool initialized = false;
    while (!initialized)
    {

        if (icm.begin_SPI(ICM_CS, ICM_SCK, ICM_MISO, ICM_MOSI))
        {
            initialized = true;
        }

        else
        {
            logError("Failed to find ICM20948 chip, trying again");
            delay(500);
        }
    }
    icm.setAccelRange(ICM20948_ACCEL_RANGE_16_G);

    logDebug("ICM initialized");

    xTaskCreatePinnedToCore(IMU_Task, "IMU_Task", 10000, (void *)this, 1, NULL, 1); // Core 1: IMU Task
}

bool IMU::update()
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

    // Compute orientation vector
    // This is where the kalman filter would come in, or I could use a simpler complementary filter
    computeOrientation(&accel.acceleration, &gyro.gyro, &mag.magnetic, dT);

    return true;
}

void IMU::computeOrientation(const sensors_vec_t *acc, const sensors_vec_t *gyr, const sensors_vec_t *mag, uint32_t dT)
{
    orientation3D orientation_change;

    // Compute pitch in radians from accelerometers x and z
    double pitch_accelerometers = atan2(acc->x, acc->z);

    // Compute yaw rate from gyro_y.
    float pitch_change = gyr->y * dT;

    // Combine with complementary filter.
    orientation.p = (orientation_prev.p + pitch_change) * COMPLEMENTARY_FILTER_ALPHA_PITCH + pitch_accelerometers * (1. - COMPLEMENTARY_FILTER_ALPHA_PITCH);

    // Store current orientation for orientation rate in next cycle
    orientation_prev = orientation;
}

const orientation3D *IMU::getOrientation()
{
    // TODO make this thread-safe
    return &orientation;
}

void IMU_Task(void *pvParameters)
{
    while (true)
    {
        // if new imu data available: updateFilteredOrientation();
        // if success: publish

        // Delay for appropriate sampling rate
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}