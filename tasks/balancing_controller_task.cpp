#include "tasks/mcs_task.h"
#include "MotorControlSystem/BalanceController.h"
#include "utility/Logger.h"
#include "data_types.h"

void mcs_task(void *pvParameters)
{
    Logger::debug("mcs_task - Setting up mcs_task.");

    BalanceController BalanceController;

    if (BalanceController.init() == true)
        while (true)
        {
            // TODO: wait for dataReady with FreeRTOS

            Logger::debug("mcs_task - BalanceController got new orientation data!");

            OrientationData OrientationData = BalanceController.getOrientationData();

            // Error checking
            // if(X){
            //     // Handle the case where there is corrupt data or st
            //     Logger::warn("mcs_task - No new orientation data received upon update.");
            // }

            // // Always update motor speeds. Even when no IMU data is available, new heading might be available.
            // BalanceController.updateMotorSpeeds();
            // BalanceController.setMotorSpeeds();

            // Delay task with configured duration
            vTaskDelay(MCS_TASK_DELAY / portTICK_PERIOD_MS);
        }
}