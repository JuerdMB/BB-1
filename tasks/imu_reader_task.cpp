#include "config.h"
#include "utility/Logger.h"
#include "tasks/imu_reader_task.h"
#include "IRS/IRS.h"

void imu_reader_task(void *parameters)
{
    Logger::debug("imu_reader_task - Setting up imu_reader_task.");

    IRS irs;

    bool irs_inited = irs.init();

    if (irs_inited)

        while (true)
        {
            // TODO: wait for dataReady with FreeRTOS
            Logger::debug("imu_reader_task - Got new IMU data.");

            //     irs.readRawData();
            //     irs.updateFilteredOrientation();
            //     irs.publishFilteredOrientation();

            // Delay task with configured duration
            vTaskDelay(IMU_TASK_DELAY / portTICK_PERIOD_MS);
        }
}