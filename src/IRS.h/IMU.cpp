#include <Wire.h>
#include <Adafruit_ICM20948.h>
#include "IRS/IMU.h"
#include "config.h"
#include "utility/Logger.h"

IMU::IMU() : icm_(Adafruit_ICM20948()), data_ready_(false)
{
}

bool IMU::init()
{

    uint8_t retry_count = 0;
    bool inited = false;

    // Retry initialization until success or max retries exceeded
    while (retry_count < ICM_INIT_MAX_RETRIES && !inited)
    {
        inited = icm_.begin_SPI(ICM_CS, ICM_SCK, ICM_MISO, ICM_MOSI);

        if (inited)
        {
            Logger::debug("IMU - ICM20948 Found!");
            break;
        }

        Logger::debug("Failed to find ICM20948 chip, attempt %d/%d", retry_count + 1, ICM_INIT_MAX_RETRIES);
        retry_count++;

        // Wait 1 second
        vTaskDelay(ICM_INIT_FAILED_DELAY_MS / portTICK_PERIOD_MS);
    }

    // Check final status
    if (!inited)
    {
        // Handle error case after all retries
        Logger::error("IMU initialization failed after %d attempts", ICM_INIT_MAX_RETRIES);

        // Return error code
        return false;
    }

    // Initialize accelerometer settings
    icm_.setAccelRange(ICM20948_ACCEL_RANGE_16_G);
    Logger::debug("Accelerometer range set to: %d", icm_.getAccelRange());
    return true;
}

bool IMU::isDataReady()
{
    // Tester implementation randomizes true value
    bool isTrue = (bool)random(2);
    return isTrue;
}

void IMU::setDataReadyCallback(void (*callback)())
{
}