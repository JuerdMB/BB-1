#include <Wire.h>
#include <Adafruit_ICM20948.h>
#include "config.h"
#include "imu.h"
#include "tasks/imu_reader_task.h"
#include "utility/Logger.h"
#include "utility/shared_data.h"

IMU::IMU() : icm_(Adafruit_ICM20948()), currentOrientation_(Orientation()), lastOrientationUpdate_(0)
{
    latestIMUData_.accelerometer.x = 0.;
    latestIMUData_.accelerometer.y = 0.;
    latestIMUData_.accelerometer.z = 0.;
    latestIMUData_.gyroscope.x = 0.;
    latestIMUData_.gyroscope.y = 0.;
    latestIMUData_.gyroscope.z = 0.;
    latestIMUData_.magnetometer.x = 0.;
    latestIMUData_.magnetometer.y = 0.;
    latestIMUData_.magnetometer.z = 0.;
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

    // Set up interrupt on IMU_INT_PIN
    pinMode(ICM_INTERRUPT, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ICM_INTERRUPT), imuInterruptHandler, RISING);
    Logger::info("IMU - IMU interrupt set up on pin %d", ICM_INTERRUPT);

    return true;
}

void IMU::retrieveRawData()
{
    // Temporary store reading values
    sensors_event_t accel_event, gyro_event, temp_event, mag_event;
    sensors_event_t *accel = &accel_event;
    sensors_event_t *gyro = &gyro_event;
    sensors_event_t *temp = &temp_event;
    sensors_event_t *mag = &mag_event;

    // Update central accel, gyro, temperature and magnetometer values
    if (!icm_.getEvent(accel, gyro, temp, mag))
    {
        Logger::warn("retrieving data from ICM unsuccesful with [accel], [gyro], [temp], [mag]");
        return;
    }

    // Update central accel, gyro, temperature and magnetometer values
    latestIMUData_.accelerometer.x = accel->acceleration.x;
    latestIMUData_.accelerometer.y = accel->acceleration.y;
    latestIMUData_.accelerometer.z = accel->acceleration.z;
    latestIMUData_.gyroscope.x = gyro->gyro.x;
    latestIMUData_.gyroscope.y = gyro->gyro.y;
    latestIMUData_.gyroscope.z = gyro->gyro.z;
    latestIMUData_.magnetometer.x = mag->magnetic.x;
    latestIMUData_.magnetometer.y = mag->magnetic.y;
    latestIMUData_.magnetometer.z = mag->magnetic.z;
    Logger::debug("Got new accelerometer, gyro and magnetometer values: [ %0.2f , %0.2f, %0.2f ] , [ %0.2f , %0.2f , %0.2f ] , [ %0.2f , %0.2f , %0.2f ]", 
                                    latestIMUData_.accelerometer.x, latestIMUData_.accelerometer.y, latestIMUData_.accelerometer.z,
                                    latestIMUData_.gyroscope.x, latestIMUData_.gyroscope.y, latestIMUData_.gyroscope.z,
                                    latestIMUData_.magnetometer.x, latestIMUData_.magnetometer.y, latestIMUData_.magnetometer.z);

}

void IMU::updateFilteredOrientation()
{
    // // Calculate time interval since last measurement
    uint32_t now = micros();
    uint32_t deltaTime = now - lastOrientationUpdate_;
    lastOrientationUpdate_ = now;

    // Compute pitch in radians from accelerometers x and z
    double pitch_accelerometers = atan2(latestIMUData_.accelerometer.x, latestIMUData_.accelerometer.z);

    // Compute yaw rate from gyro_y, assuming gyro rate from sensor is in rad/s
    float pitch_rate = latestIMUData_.gyroscope.y * deltaTime * 1000000;

    // Combine with complementary filter.
    float pitch_filtered = (previousOrientation_.pitch + pitch_rate) * COMPLEMENTARY_FILTER_PITCH_ALPHA + pitch_accelerometers * (1.f - COMPLEMENTARY_FILTER_PITCH_ALPHA);

    // Update previous orientation
    previousOrientation_ = currentOrientation_;

    // Update orientation
    currentOrientation_.pitch = pitch_filtered;
}

void IMU::publishFilteredOrientation()
{
    // Publish to FreeRTOS queue
    SharedData::sendOrientationData(currentOrientation_);

    // Publish over ROS2
    // rosNode.publishOrientation(orientation);
}
