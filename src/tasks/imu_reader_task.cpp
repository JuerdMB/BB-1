#include "config.h"
#include "utility/Logger.h"
#include "tasks/imu_reader_task.h"
#include "hardware/imu.h"

void IRAM_ATTR imuInterruptHandler() {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Notify the imu reading task that new data if available
    vTaskNotifyGiveFromISR(imuReadingTaskHandle, &xHigherPriorityTaskWoken);

    // Perform a context switch to imu reader task if no higher priority task is ready
    if (xHigherPriorityTaskWoken == pdTRUE) {
        portYIELD_FROM_ISR();
    }
}

TaskHandle_t imuReadingTaskHandle = nullptr;

void imuReaderTask(void *parameters)
{
    LOG_DEBUG("Setting up imuReaderTask.");

    // Assign the current task to the task handler
    imuReadingTaskHandle = xTaskGetCurrentTaskHandle();

    // Create and init IMU Object, this also sets up the IMU interrupt handler if IMU_USE_INTERRUPT is set
    IMU imu;

    if(imu.init() != IMU_INIT_SUCCEEDED){
        // IMU init failed, restart ESP and try again
        LOG_ERROR("IMU init failed, restarting ESP32.");
        ESP.restart();
    }

    while (true)
    {
        // Wait for notification from ISR
        #ifdef IMU_USE_INTERRUPT
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        #endif

        // Temporary container for raw IMU data
        RawIMUdata rawIMUdata;

        IMU_READ_ERROR imu_read_result = imu.retrieveRawData(rawIMUdata);

        // Obtain new data from sensor
        if(imu_read_result != IMU_READ_SUCCESS){
            LOG_WARN("IMU data read error: %d", (int)imu_read_result);
            break;
        }

        LOG_DEBUG("Got new accelerometer, gyro and magnetometer values: [ %0.2f , %0.2f, %0.2f ] , [ %0.2f , %0.2f , %0.2f ] , [ %0.2f , %0.2f , %0.2f ]",
                  rawIMUdata.accelerometer.x, rawIMUdata.accelerometer.y, rawIMUdata.accelerometer.z,
                  rawIMUdata.gyroscope.x, rawIMUdata.gyroscope.y, rawIMUdata.gyroscope.z,
                  rawIMUdata.magnetometer.x, rawIMUdata.magnetometer.y, rawIMUdata.magnetometer.z);

        Orientation currentOrientation;

        // Calculate new orientation based on raw IMU data
        imu.updateFilteredOrientation(rawIMUdata, currentOrientation);

        // Send to freeRTOS queue and publish over ROS
        imu.publishFilteredOrientation(currentOrientation);

        vTaskDelay(100);
    }
}

