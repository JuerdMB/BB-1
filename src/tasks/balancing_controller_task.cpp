#include "tasks/balancing_controller_task.h"
#include "controllers/balance_controller.h"
#include "utility/Logger.h"
#include "utility/utils.h"

void balancing_controller_task(void *pvParameters)
{
    Logger::debug("balancing_controller_task - Setting up balancing_controller_task.");

    BalanceController BalanceController;

    if (BalanceController.init() == true)
        while (true)
        {
            // TODO: wait for dataReady with FreeRTOS

            Logger::debug("balancing_controller_task - BalanceController got new orientation data!");

            OrientationData OrientationData = BalanceController.getOrientationData();

            // Error checking
            // if(X){
            //     // Handle the case where there is corrupt data or st
            //     Logger::warn("balancing_controller_task - No new orientation data received upon update.");
            // }

            // // Always update motor speeds. Even when no IMU data is available, new heading might be available.
            // BalanceController.updateMotorSpeeds();
            // BalanceController.setMotorSpeeds();

            // Delay task with configured duration
            vTaskDelay(1000);
        }
}