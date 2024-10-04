#include "tasks/mcs_task.h"
#include "MotorControlSystem/MotorController.h"
#include "utility/Logger.h"

void mcs_task(void *pvParameters)
{
    MotorController motorController;

    motorController.init();

    while (true)
    {

        if (!motorController.updateOrientationData())
        {
            // Handle the case where no data was received
            Logger::warn("mcs_task - No new orientation data received upon update.");
        }

        // Always update motor speeds. Even when no IMU data is available, new heading might be available.
        motorController.updateMotorSpeeds();
        motorController.setMotorSpeeds();

        // Delay task with configured duration
        vTaskDelay(MCS_TASK_DELAY / portTICK_PERIOD_MS);
    }
}