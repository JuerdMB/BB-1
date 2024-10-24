#include "tasks/balancing_controller_task.h"
#include "controllers/balance_controller.h"
#include "utility/Logger.h"
#include "utility/utils.h"

void balancingControllerTask(void *pvParameters)
{
    Logger::debug("balancingControllerTask - Setting up balancingControllerTask.");

    BalanceController BalanceController;

    if (BalanceController.init() == true)
        while (true)
        {
            // TODO: wait for dataReady with FreeRTOS

            Logger::debug("balancingControllerTask - BalanceController got new orientation data!");

            Orientation OrientationData = BalanceController.retrieveOrientationFromIMU();

            // Error checking
            // if(X){
            //     // Handle the case where there is corrupt data or st
            //     Logger::warn("balancingControllerTask - No new orientation data received upon update.");
            // }

            // // Always update motor speeds. Even when no IMU data is available, new heading might be available.
            // BalanceController.updateMotorSpeeds();
            // BalanceController.setMotorSpeeds();

            // Delay task with configured duration
            vTaskDelay(1000);
        }
}