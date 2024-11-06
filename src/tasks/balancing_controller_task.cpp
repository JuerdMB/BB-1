#include "tasks/balancing_controller_task.h"
#include "controllers/balance_controller.h"
#include "utility/Logger.h"
#include "utility/utils.h"

void balancingControllerTask(void *pvParameters)
{
    LOG_DEBUG("balancingControllerTask - Setting up balancingControllerTask.");

    BalanceController BalanceController;

    if (BalanceController.init() == true)
    {
        while (true)
        {
            // TODO: wait for dataReady with FreeRTOS
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            LOG_DEBUG("balancingControllerTask - BalanceController got new orientation data!");

            Orientation orientationData;
            if (!BalanceController.retrieveOrientationFromIMU(orientationData))
            {
                LOG_WARN("balancingControllerTask - No new orientation data received upon update.");
                continue;
            }

            // Temporary values for motorSpeeds
            int motorLeftSpeed = 0;
            int motorRightSpeed = 0;

            // Always update motor speeds. Even when no IMU data is available, new heading might be available.
            BalanceController.updateMotorSpeeds(orientationData, motorLeftSpeed, motorRightSpeed);

            // Send motor speeds to motors
            BalanceController.setMotorSpeeds(motorLeftSpeed, motorRightSpeed);
        }
    }

    else
    {
        LOG_WARN("Balance Controller failed to initialize with error code X");
        vTaskDelete(NULL);
    }
}