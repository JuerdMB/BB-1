#pragma once

/*  This is the Inertial reference System of the robot.
 *   It provides access to filtered data from the sensors.
 *   It takes care of all error checking and filtering, which it abstracts away.
 *
 *   The class acts as a ROS node with namespace "IRS"
 */

#include "ICM_20948.h"
#include <SimpleKalmanFilter.h>
#include <ros.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/QuaternionStamped.h>
#include <std_msgs/Header.h>

#define NAMESPACE "IRS"
#define AD0_VAL 1

#define ICM_SDA_PORT 13
#define ICM_SCK_PORT 12

class IRS
{
public:
    IRS(ros::NodeHandle *nh);
    ~IRS();

    void initialize();
    bool update();
    bool runChecks();

    const geometry_msgs::PoseStamped& getPose() const;

private:
    ros::NodeHandle *nodeHandle_;

    /* ICM-20948 sensor object and ports, to be defined upon startup */
    ICM_20948_I2C myICM;

    // Temporary pitch as double, and function to calculate it
    double computePitchComplementaryFilter();

    // Variables to store robot pose information
    geometry_msgs::Pose pose; // The robot's current transform relative to the static world frame, based on IRS
    geometry_msgs::PoseArray poseHistory[10]; // Records past transforms, to check for anomalies
    void storePoseToHistory(geometry_msgs::Pose pose);
};

