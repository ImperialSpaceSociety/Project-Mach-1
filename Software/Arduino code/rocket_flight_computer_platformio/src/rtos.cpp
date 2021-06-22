//**************************************************************************
// Can use these function for RTOS delays
// Takes into account processor speed
// Use these instead of delay(...) in rtos tasks
//**************************************************************************

#include "rtos.hpp"


void myDelayUs(int us)
{
    vTaskDelay(us / portTICK_PERIOD_US);
}

void myDelayMs(int ms)
{
    vTaskDelay((ms * 1000) / portTICK_PERIOD_US);
}

void myDelayMsUntil(TickType_t *previousWakeTime, int ms)
{
    vTaskDelayUntil(previousWakeTime, (ms * 1000) / portTICK_PERIOD_US);
}
