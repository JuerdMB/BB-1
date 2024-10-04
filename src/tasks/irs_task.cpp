#include "config.h"
#include "tasks/irs_task.h"
#include "IRS/IRS.h"
#include "utility/Logger.h"

void irs_task(void* parameters){

    IRS irs;

    while(true){
        
        if(irs.isDataReady()){
            irs.readRawData();
            irs.updateFilteredOrientation();
            irs.publishFilteredOrientation();
        }
        else{
            // Handle the case whe/re IMU is not ready
            Logger::warn("irs_task - IMU not ready.");
        }

        // Delay task with configured duration
        vTaskDelay(IMU_TASK_DELAY / portTICK_PERIOD_MS);
    }

}