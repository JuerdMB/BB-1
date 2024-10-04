#include "IMU.h"
#include "config.h"
#include "Logger.h"
#include "shared_data.h"

IMU::IMU() : orientation_(orientation3D()), last_imu_update(0), pitch_filtered_prev(0.0f), dataReady(false)
{
}

void IMU::start()
{
    // Pin the IMU task to core 1
    xTaskCreatePinnedToCore(imuTask, "IMU_Task", 4096, this, 5, NULL, 1);
}

// Static wrapper function for IMU (run) task
void IMU::imuTask(void *imuInstance)
{
    // Cast imuInstance parameter to IMU* type
    IMU *imuPtr = static_cast<IMU *>(imuInstance);
    // Call the actual run function
    imuPtr->run();
}

void IMU::init()
{
    Wire.begin();
    Wire.setClock(100000);

    bool initialized = false;
    while (!initialized)
    {
        if (imu.begin_SPI(ICM_CS, ICM_SCK, ICM_MISO, ICM_MOSI))
            initialized = true;

        else
        {
            Logger::error("Failed to find ICM20948 chip, trying again");
            delay(500);
        }
    }
    imu.setAccelRange(ICM20948_ACCEL_RANGE_16_G);

    Logger::debug("ICM initialized");

    // attachInterrupt(interrupt)
}

bool IMU::isDataReady()
{
    // if(dataReady){
    //     dataReady = false;
    //     return true;
    // }
    // return false;

    return true; // TODO: For now, simply return true, as hardware interrupt of IMU is not set yet
}

void IMU::run()
{
    this->init();

    while (true)
    {
        // Check if dataReady flag is set by IMU. If so, update and publish orientation.
        if (isDataReady())
        {
            this->readRawData();
            this->updateFilteredOrientation();
            this->publishFilteredOrientation();
        }

        // Delay task with configured duration
        vTaskDelay(IMU_TASK_DELAY);
    }
}

void IMU::readRawData()
{
    // Update central accel, gyro, temperature and magnetometer values
    imu.getEvent(&this->accel, &this->gyro, &this->temperature, &this->mag);
}

void IMU::updateFilteredOrientation()
{
    // Calculate time interval since last measurement
    uint32_t now = micros();
    uint32_t dT = now - last_imu_update;
    last_imu_update = now;

    // Compute pitch in radians from accelerometers x and z
    double pitch_accelerometers = atan2(accel.acceleration.x, accel.acceleration.z);

    // Compute yaw rate from gyro_y.
    float pitch_change = gyro.gyro.y * dT;

    // Combine with complementary filter.
    float pitch_filtered = (pitch_filtered_prev + pitch_change) * COMPLEMENTARY_FILTER_ALPHA_PITCH + pitch_accelerometers * (1. - COMPLEMENTARY_FILTER_ALPHA_PITCH);

    // Store current orientation for orientation rate in next cycle
    pitch_filtered_prev = pitch_filtered;

    // Update orientation
    orientation_.p = pitch_filtered;
}

void IMU::publishFilteredOrientation()
{
    // Publis to 
    SharedData::setOrientation(orientation_);

    // Publish to ROS
    // orientation3D orientation = getOrientation();

    // Publish over ROS2
    // rosNode.publishOrientation(orientation);
}
