#include "config.h"
#include "tasks/irs_task.h"
#include "IRS/IRS.h"
#include "utility/Logger.h"

void irs_task(void *parameters)
{
    Logger::debug("irs_task - Setting up irs_task.");

    IRS irs;

    bool irs_inited = irs.init();

    if (irs_inited)

        while (true)
        {
            // TODO: wait for dataReady with FreeRTOS
            Logger::debug("irs_task - Got new IMU data.");

            //     irs.readRawData();
            //     irs.updateFilteredOrientation();
            //     irs.publishFilteredOrientation();

            // Delay task with configured duration
            vTaskDelay(IMU_TASK_DELAY / portTICK_PERIOD_MS);
        }
}