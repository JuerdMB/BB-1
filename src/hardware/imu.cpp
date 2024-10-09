#include <Wire.h>
#include <Adafruit_ICM20948.h>
#include "config.h"
#include "imu.h"
#include "tasks/imu_reader_task.h"
#include "utility/Logger.h"

IMU::IMU() : icm_(Adafruit_ICM20948()), last_imu_update_(0)
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
            Logger::info("IMU - ICM20948 Found!");
            break;
        }

        Logger::warn("IMU - Failed to find ICM20948 chip, attempt %d/%d", retry_count + 1, ICM_INIT_MAX_RETRIES);
        retry_count++;

        // Wait 1 second
        vTaskDelay(ICM_INIT_FAILED_DELAY_MS / portTICK_PERIOD_MS);
    }

    // Check final status
    if (!inited)
    {
        // Handle error case after all retries
        Logger::error("IMU - IMU initialization failed after %d attempts", ICM_INIT_MAX_RETRIES);

        // Return error code
        return false;
    }

    // Initialize accelerometer settings
    icm_.setAccelRange(ICM20948_ACCEL_RANGE_16_G);
    Logger::info("IMU - Accelerometer range set to: %d", icm_.getAccelRange());
    return true;

    // Set up interrupt on IMU_INT_PIN
    pinMode(ICM_INTERRUPT, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ICM_INTERRUPT), imuInterruptHandler, RISING);
    Logger::info("IMU - IMU interrupt set up on pin %d", ICM_INTERRUPT);
}

void IMU::retrieveRawData()
{
    // Update central accel, gyro, temperature and magnetometer values
    // imu.getEvent(&this->accel, &this->gyro, &this->temperature, &this->mag);
}

void IMU::updateFilteredOrientation()
{
    // // Calculate time interval since last measurement
    // uint32_t now = micros();
    // uint32_t dT = now - last_imu_update_;
    // last_imu_update_ = now;

    // // Compute pitch in radians from accelerometers x and z
    // double pitch_accelerometers = atan2(accel.acceleration.x, accel.acceleration.z);

    // // Compute yaw rate from gyro_y.
    // float pitch_change = gyro.gyro.y * dT;

    // // Combine with complementary filter.
    // float pitch_filtered = (pitch_filtered_prev + pitch_change) * COMPLEMENTARY_FILTER_ALPHA_PITCH + pitch_accelerometers * (1. - COMPLEMENTARY_FILTER_ALPHA_PITCH);

    // // Store current orientation for orientation rate in next cycle
    // pitch_filtered_prev = pitch_filtered;

    // // Update orientation
    // orientation_.p = pitch_filtered;
}

void IMU::publishFilteredOrientation()
{
        // Publis to 
    // SharedData::setOrientation(orientation_);

    // Publish to ROS
    // orientation3D orientation = getOrientation();

    // Publish over ROS2
    // rosNode.publishOrientation(orientation);
}

