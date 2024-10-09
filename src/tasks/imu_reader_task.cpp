#include "config.h"
#include "utility/Logger.h"
#include "tasks/imu_reader_task.h"
#include "hardware/imu.h"

void IRAM_ATTR imuInterruptHandler() {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(imuReadingTaskHandle, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken == pdTRUE) {
        portYIELD_FROM_ISR();
    }
}

TaskHandle_t imuReadingTaskHandle = nullptr;

void imuReaderTask(void *parameters)
{
    Logger::debug("imuReaderTask - Setting up imuReaderTask.");

    // Assign the current task to the task handler
    imuReadingTaskHandle = xTaskGetCurrentTaskHandle();

    // Create and init IMU Object, this also sets up the IMU interrupt handler
    IMU imu;
    imu.init();

    while (true)
    {
        // Wait for notification from ISR
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        Logger::debug("imuReaderTask - Got new IMU data.");

        // Obtain new data from sensor
        imu.retrieveRawData();
        imu.updateFilteredOrientation();
        imu.publishFilteredOrientation();

        // Delay task with configured duration
        vTaskDelay(1000);
    }
}

