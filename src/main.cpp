/********************************************************************************
   BB-1 Self balancing robot by Juerd Mispelblom Beyer
   V1

   CONNECTIONS:
   Arduino D3  - Motor Driver PWM 1 Input
   Arduino D4  - Motor Driver DIR 1 Input
   Arduino D9  - Motor Driver PWM 2 Input
   Arduino D10 - Motor Driver DIR 2 Input
   Arduino GND - Motor Driver GND

 ********************************************************************************/

#define desiredLoopDuration 5

#include <Arduino.h>
#include "Logger.h"
#include "IRS.h"
#include "Ros.h"

#define motorLeftPWM 5
#define motorRightPWM 6

// ROS
ros::NodeHandle nh;
geometry_msgs::PoseStamped pose_msg; // Pose message
ros::Publisher pose_pub("IRS/Pose", &pose_msg);
IRS irs(&nh);

void setup()
{
  Serial.begin(115200);
  irs.initialize();

  nh.advertise(pose_pub);

  // xTaskCreatePinnedToCore();   // IRS that runs on ESP core 1
  // xTaskCreatePinnedToCore();   // Motor control system that runs on ESP core 2
}

void loop()
{
  // Empty loop. All is done inside the assigned tasks.
}

void IRS_task(void *pvParameters)
{
  IRS irs(&nh);
  irs.initialize();

  while (true)
  {
    if (irs.update())
    {

      // Publish new pose information
      pose_pub.publish(&irs.getPose());

      if (!irs.runChecks())
      {
        // If something really bad happened, fix it here
      }
    }

    nh.spinOnce();

    // Delay for appropriate sampling rate
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void Motor_Control_Task(void *pvParameters)
{
  // Subscribe to Pose topic, when new data available, compute motor net values. Control motors at fixed intervals.
}