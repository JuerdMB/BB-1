#include "config.h"
#include "utility/Logger.h"
#include "tasks/imu_reader_task.h"
#include "hardware/imu.h"

void imuReaderTask(void *parameters)
{
    Logger::debug("imuReadingTask - Setting up imuReadingTask.");

    IMU imu;

    while (true)
    {
        // TODO: wait for dataReady with FreeRTOS
        Logger::debug("imuReadingTask - Got new IMU data.");

        // Obtain new data from sensor
        imu.retrieveRawData();
        imu.updateFilteredOrientation();
        imu.publishFilteredOrientation();

        // Delay task with configured duration
        vTaskDelay(1000);
    }
}