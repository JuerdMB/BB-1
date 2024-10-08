#include "IRS/IRS.h"
#include "utility/Logger.h"

IRS::IRS() : imu_(IMU())
{
}

bool IRS::init()
{
    // TODO - turn this into error type
    uint8_t imu_inited = imu_.init();

    if (!imu_inited)
    {
        Logger::debug("IRS - IRS initialization unsuccesful: IMU initialization failed with error code %d.", imu_inited);
        return false;
    }

    Logger::debug("IRS - IRS Succesfully inited.");
    return true;
}

void IRS::readRawData()
{
}

void IRS::updateFilteredOrientation()
{
}

void IRS::publishFilteredOrientation()
{
}

bool IRS::isDataReady()
{
    return imu_.isDataReady();
}
