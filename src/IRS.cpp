#include "IRS.h"

IRS::IRS(ros::NodeHandle *nh) : nodeHandle_(nh)
{
}

void IRS::initialize()
{
    Wire.begin();
    Wire.setClock(400000);

    bool initialized = false;
    while (!initialized)
    {
        myICM.begin(Wire, AD0_VAL);

        Serial.print(F("Initialization of the sensor returned: "));
        Serial.println(myICM.statusString());
        if (myICM.status != ICM_20948_Stat_Ok)
        {
            Serial.println("Trying again...");
            delay(500);
        }
        else
        {
            initialized = true;
        }
    }
}

bool IRS::update()
{
    while (!myICM.dataReady())
    {
        // Wait and do nothing
        Serial.println("ICM not ready, waiting for data");
        delay(5);
    }

    // Update the ICM
    myICM.getAGMT();

    float rawAccData[3] = {myICM.accX(), myICM.accY(), myICM.accZ()};
    float rawGyrData[3] = {myICM.gyrX(), myICM.gyrY(), myICM.gyrZ()};
    float rawMagData[3] = {myICM.magX(), myICM.magY(), myICM.magZ()};

    // Do calculations to compute Transformation and Rotation vectors, and Quaternion from rawAccData, rawGyrData, rawMagData
    // This is where the kalman filter would come in, or I could use a simpler complementary filter

    current_pitch = computePitchComplementaryFilter();

    // Update pose and orientation TEMP
    pose.position.x = 0.0;
    pose.position.y = 0.0;
    pose.position.z = 0.0;

    pose.orientation.x = 0.0;
    pose.orientation.y = 0.0;
    pose.orientation.z = 0.0;
    pose.orientation.w = 1.0;

    // TODO: Fill rotation through convenient functions
    // pose.orientation.setRPY(/*Roll*/ 0, /*Pitch*/ 0, /*Yaw*/ 0); // Insert current pitch into quaternion

    // Publish pose message as stamped pose
    geometry_msgs::PoseStamped poseMessage;
    std_msgs::Header header; // Create header for pose
    poseMessage.header = header;
    poseMessage.pose = pose;

    // Save to history so we can do checks before overwritten
    // storePoseToHistory(pose);

    // Do calculations on pose history
    // runPoseChecks();

    // If all is succesful, return true
    // if(){}
    return true;
}