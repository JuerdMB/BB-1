#include <Wire.h>
#include <Adafruit_ICM20948.h>
#include "config.h"
#include "imu.h"
#include "tasks/imu_reader_task.h"
#include "utility/Logger.h"
#include "utility/shared_data.h"

IMU::IMU() : icm_(Adafruit_ICM20948()), previousOrientation_(Orientation()), lastOrientationUpdate_(0)
{
}

IMU_INIT_ERROR IMU::init()
{
    uint8_t retry_count = 0;
    bool inited = false;

    // Retry initialization until success or max retries exceeded
    while (retry_count < ICM_INIT_MAX_RETRIES && !inited)
    {
        // Attempt to init sensor
        inited = icm_.begin_SPI(ICM_CS, ICM_SCK, ICM_MISO, ICM_MOSI);

        if (inited)
        {
            LOG_INFO("IMU - ICM20948 Found after %d attempts!", retry_count+1);
            break;
        }

        LOG_WARN("IMU - Failed to find ICM20948 chip, attempt %d/%d", retry_count + 1, ICM_INIT_MAX_RETRIES);
        retry_count++;

        vTaskDelay(ICM_INIT_FAILED_DELAY_MS / portTICK_PERIOD_MS);
    }

    // Check final status
    if (!inited)
    {
        LOG_ERROR("IMU - IMU initialization failed after %d attempts", ICM_INIT_MAX_RETRIES);
        return IMU_INIT_FAILED;
    }

    // Initialize accelerometer settings
    icm_.setAccelRange(ICM20948_ACCEL_RANGE_16_G);
    LOG_INFO("IMU - Accelerometer range set to: %d", icm_.getAccelRange());

    // If IMU_USE_INTERRUPT is defined, assign ISR to signal imu reader task upon new data availability
    #ifdef IMU_USE_INTERRUPT
        // Set up interrupt on IMU_INT_PIN
        pinMode(ICM_INTERRUPT, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(ICM_INTERRUPT), imuInterruptHandler, RISING);
        LOG_INFO("IMU - IMU interrupt set up on pin %d", ICM_INTERRUPT);
    #endif

    return IMU_INIT_SUCCEEDED;
}

IMU_READ_ERROR IMU::retrieveRawData(RawIMUdata &dataContainer)
{
    // Update central accel, gyro, temperature and magnetometer values
    sensors_event_t accel_event, gyro_event, temp_event, mag_event;
    if (!icm_.getEvent(&accel_event, &gyro_event, &temp_event, &mag_event))
    {
        LOG_WARN("unsuccesful read from ICM unsuccesful with [accel], [gyro], [temp], [mag]");
        return IMU_READ_FAILED;
    }

    // Store accel, gyro, temperature and magnetometer values
    dataContainer.accelerometer.x = accel_event.acceleration.x;
    dataContainer.accelerometer.y = accel_event.acceleration.y;
    dataContainer.accelerometer.z = accel_event.acceleration.z;
    dataContainer.gyroscope.x = gyro_event.gyro.x;
    dataContainer.gyroscope.y = gyro_event.gyro.y;
    dataContainer.gyroscope.z = gyro_event.gyro.z;
    dataContainer.magnetometer.x = mag_event.magnetic.x;
    dataContainer.magnetometer.y = mag_event.magnetic.y;
    dataContainer.magnetometer.z = mag_event.magnetic.z;

    return IMU_READ_SUCCESS;
}

void IMU::updateFilteredOrientation(RawIMUdata &rawIMUdata, Orientation &currentOrientation)
{
    // // Calculate time interval since last measurement
    uint32_t now = micros();
    uint32_t deltaTime = now - lastOrientationUpdate_;
    lastOrientationUpdate_ = now;

    // Compute pitch in radians from accelerometers x and z
    double pitch_accelerometers = atan2(rawIMUdata.accelerometer.x, rawIMUdata.accelerometer.z);

    // Compute yaw rate from gyro_y, assuming gyro rate from sensor is in rad/s
    float pitch_rate = rawIMUdata.gyroscope.y * deltaTime * 1000000;

    // Combine with complementary filter.
    float pitch_filtered = (previousOrientation_.pitch + pitch_rate) * COMPLEMENTARY_FILTER_PITCH_ALPHA + pitch_accelerometers * (1.f - COMPLEMENTARY_FILTER_PITCH_ALPHA);

    // Update orientation
    currentOrientation.pitch = pitch_filtered;

    // Store current orientation for next calculation
    previousOrientation_ = currentOrientation;
}

void IMU::publishFilteredOrientation(Orientation &currentOrientation)
{
    // Publish to FreeRTOS queue
    SharedData::sendOrientationData(currentOrientation);

    // Publish over ROS2
    // rosNode.publishOrientation(orientation);
}
