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

            if (irs.isDataReady())
            {
                Logger::debug("irs_task - Got new IMU data.");
                //     irs.readRawData();
                //     irs.updateFilteredOrientation();
                //     irs.publishFilteredOrientation();
            }
            else
            {
                //     // Handle the case whe/re IMU is not ready
                Logger::warn("irs_task - No IMU data available.");
            }

            // Delay task with configured duration
            vTaskDelay(IMU_TASK_DELAY / portTICK_PERIOD_MS);
        }
}