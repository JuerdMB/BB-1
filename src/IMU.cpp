#include "IMU.h"
#include "Logger.h"

IMU::IMU() : mpu(), pitch_previous(0), roll_previous(0), yaw_previous(0)
{
}

bool IMU::initialize()
{
    Logger &logger = Logger::getInstance();
    Wire.begin();
    if (!mpu.setup(0x68))
    {
        logger.log(LOG_LEVEL_WARN, "Failed to initialize MPU9250!");
        return false;
    }
    mpu.calibrateAccelGyro();
    logger.log(LOG_LEVEL_INFO, "MPU9250 initialized and calibrated");
    return true;
}

float IMU::getPitch()
{
    return pitch;
}

float IMU::getYaw()
{
    return yaw;
}

bool IMU::update(float deltaTime)
{
    Logger &logger = Logger::getInstance();

    // Get new values from IMU
    if (!mpu.update())
    {
        logger.log(LOG_LEVEL_ERROR, "Failed to update vectors");
        return false;
    }

    float ax = mpu.getAccX();
    float ay = mpu.getAccY();
    float az = mpu.getAccZ();
    float gx = mpu.getGyroX();
    float gy = mpu.getGyroY();
    float gz = mpu.getGyroZ();
    float mx = mpu.getMagX();
    float my = mpu.getMagY();
    float mz = mpu.getMagZ();

    // Calculate pitch from accelerometers x and z, and yaw change from gyro_y. 
    float pitch_accelerometers = atan2(ax, az) * RAD_TO_DEG; 
    float deltaPitch_gyros = gy * deltaTime;

    // Combine with complementary filter.
    pitch = (pitch_previous + deltaPitch_gyros) * ALPHA_PITCH + pitch_accelerometers * (1. - ALPHA_PITCH);
    pitch_previous = pitch;

    /* Don't assume roll for now */
    roll = 0;
    // float roll_measured = atan2(ay, az) * RAD_TO_DEG;
    // float dRoll = gx * deltaTime;
    // roll = (roll_previous + dRoll) * ALPHA_ROLL + roll_measured * (1. - ALPHA_ROLL);
    // roll_previous = roll;

    // Compensate x and y magnetometer values for pitch and roll
    float mx_compensated = mx * cos(roll * DEG_TO_RAD) + my * sin(pitch * DEG_TO_RAD) * sin(roll * DEG_TO_RAD) - mz * cos(pitch * DEG_TO_RAD) * sin(roll * DEG_TO_RAD);
    float my_compensated = my * cos(pitch * DEG_TO_RAD) + mz * sin(pitch * DEG_TO_RAD);

    // Calculate yaw and compensate for arctan limits
    float yaw_magnetometers = atan2(my_compensated, mx_compensated) * RAD_TO_DEG; /* [Deg] */
    if (yaw < 0)
        yaw += 360.0;

    // Rotational speed about the world's z-axis, compensated for pitch and roll
    float omega_z_prime = gx * sin(roll) + gy * -sin(pitch) * cos(roll) + gz * cos(pitch) * cos(roll); 
    float deltaYaw_gyros = omega_z_prime * deltaTime;

    // Combine with complementary filter
    yaw = (yaw_previous + deltaYaw_gyros) * ALPHA_YAW + yaw_magnetometers * (1. - ALPHA_YAW);
    yaw_previous = yaw;

    return true;
}

void IMU::calibrate()
{
    mpu.verbose(true);
    delay(5000);
    mpu.calibrateAccelGyro();
    delay(5000);
    mpu.calibrateMag();
    mpu.verbose(false);
}