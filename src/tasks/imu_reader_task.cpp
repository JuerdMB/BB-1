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
    Logger::debug("imuReaderTask - Setting up imuReaderTask.");

    // Assign the current task to the task handler
    imuReadingTaskHandle = xTaskGetCurrentTaskHandle();

    // Create and init IMU Object, this also sets up the IMU interrupt handler if IMU_USE_INTERRUPT is set
    IMU imu;
    if(imu.init() == IMU_INIT_FAILED){
        // IMU init failed, restart ESP and try again
        ESP.restart();
    }

    while (true)
    {
        // Wait for notification from ISR
        #ifdef IMU_USE_INTERRUPT
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        #endif

        // Obtain new data from sensor
        imu.retrieveRawData();
        imu.updateFilteredOrientation();
        imu.publishFilteredOrientation();

        // Delay task with configured duration
        vTaskDelay(100);
    }
}

