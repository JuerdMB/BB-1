#include "tasks/motion_controller_task.h"
#include "controllers/motion_controller.h"
#include "controllers/pid_controller.h"
#include "utility/Logger.h"
#include "utility/utils.h"
#include "config.h"

void motionControllerTask(void *pvParameters)
{
    LOG_DEBUG("MotionControllerTask - Setting up MotionControllerTask.");

    // Setup PIDs
    PID pid_balance(1.0f, 0.0f, 1.0f);
    PID pid_heading(1.0f, 0.0f, 1.0f);
    PID pid_speed(1.0f, 0.0f, 1.0f);

    // Setup and initialize Motion Controller
    MotionController motionController;
    
    MotionControllerError success = MOTION_CONTROLLER_SETUP_FAILED;
    uint8_t attempts = 0;
    while (success != MOTION_CONTROLLER_SETUP_SUCCESS)
    {
        attempts++;
        MotionControllerError success = motionController.init();
        if (success != MOTION_CONTROLLER_SETUP_SUCCESS)
        {
            if (attempts >= 5)
            {
                LOG_ERROR("Balance Controller failed after %d attempts, deleting task.", attempts);
                vTaskDelete(NULL);
            }
            LOG_ERROR("Balance Controller failed to initialize with error code %d", success);
        }
    }

    while (true)
    {
        // Wait for new IMU sensor data in queue
        // ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // TODO: obtain this from higher level controller through ROS. If no command for x amount of time, stand still.
        float desired_speed = 0;
        float desired_relative_heading = 0;

        // Attemp to obtain orientationData from queue and wait for new notification if unsuccesful.
        Orientation currentOrientation;

        if (!motionController.retrieveOrientationFromIMU(currentOrientation))
        {
            LOG_WARN("MotionControllerTask - No new orientation data received upon update.");
            continue;
        }
        LOG_DEBUG("Balance controller got orientation data from queue of size %d", sizeof(currentOrientation));

        // TODO: determine current speed
        float current_linear_speed = 0;

        // Compute desired pitch angle based on current and desired linear speed
        float desired_pitch_angle = pid_speed.compute(current_linear_speed, desired_speed);

        // Compute the base motor speed based on desired pitch angle and
        float balance_correction = pid_balance.compute(currentOrientation.pitch, desired_pitch_angle);

        // Compute the differential component based on desired relative heading and current heading
        float heading_correction = pid_heading.compute(currentOrientation.yaw, desired_relative_heading);

        // Temporary values for motorSpeeds
        float motorLeftSpeed = balance_correction - heading_correction;
        float motorRightSpeed = balance_correction + heading_correction;

        // Send motor speeds to motors
        // motionController.setMotorSpeeds(motorLeftSpeed, motorRightSpeed);

        LOG_DEBUG("Balance controller set motor speeds  to %d, %d.", motorLeftSpeed, motorRightSpeed);
    }
}