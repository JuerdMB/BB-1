#include "tasks/mcs_task.h"
#include "MotorControlSystem/BalanceController.h"
#include "utility/Logger.h"

void mcs_task(void *pvParameters)
{
    Logger::debug("mcs_task - Setting up mcs_task.");

    BalanceController BalanceController;

    if (BalanceController.init() == true)
        while (true)
        {

            if (BalanceController.updateOrientationData())
            {

                Logger::debug("mcs_task - BalanceController got new orientation data!");
            }

            else
            {
                //     // Handle the case where no data was received
                Logger::warn("mcs_task - No new orientation data received upon update.");
            }

            // // Always update motor speeds. Even when no IMU data is available, new heading might be available.
            // BalanceController.updateMotorSpeeds();
            // BalanceController.setMotorSpeeds();

            // Delay task with configured duration
            vTaskDelay(MCS_TASK_DELAY / portTICK_PERIOD_MS);
        }
}