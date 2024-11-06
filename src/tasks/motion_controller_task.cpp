#include "tasks/motion_controller_task.h"
#include "controllers/motion_controller.h"
#include "utility/Logger.h"
#include "utility/utils.h"
#include "config.h"

void motionControllerTask(void *pvParameters)
{
    LOG_DEBUG("MotionControllerTask - Setting up MotionControllerTask.");

    MotionController MotionController;

    if (MotionController.init() == true)
    {
        while (true)
        {
            // Wait for new IMU sensor data in queue
            // ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            // TODO: obtain this from higher level controller through ROS. If no command for x amount of time, stand still.
            float desired_speed = 0;
            float desired_relative_heading = 0;

            // Attemp to obtain orientationData from queue and wait for new notification if unsuccesful.
            Orientation currentOrientation;

            if (!MotionController.retrieveOrientationFromIMU(currentOrientation))
            {
                LOG_WARN("MotionControllerTask - No new orientation data received upon update.");
                continue;
            }
            LOG_DEBUG("Balance controller got orientation data from queue of size %d", sizeof(currentOrientation));

            // TODO: determine current speed
            float current_linear_speed = 0;

            // Compute desired pitch angle based on current and desired linear speed
            float desired_pitch_angle = MotionController.pid_speed_.compute(current_linear_speed, desired_speed);

            // Compute the base motor speed based on desired pitch angle and 
            float balance_correction = MotionController.pid_balance_.compute(currentOrientation.pitch, desired_pitch_angle);

            // Compute the differential component based on desired relative heading and current heading
            float heading_correction = MotionController.pid_heading_.compute(currentOrientation.yaw, desired_relative_heading);

            // Temporary values for motorSpeeds
            float motorLeftSpeed = balance_correction - heading_correction;
            float motorRightSpeed = balance_correction + heading_correction;

            // Send motor speeds to motors
            MotionController.setMotorSpeeds(motorLeftSpeed, motorRightSpeed);

            LOG_DEBUG("Balance controller set motor speeds  to %d, %d.", motorLeftSpeed, motorRightSpeed);
        }
    }

    else
    {
        LOG_WARN("Balance Controller failed to initialize with error code X");
        vTaskDelete(NULL);
    }
}