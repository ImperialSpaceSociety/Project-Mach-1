/**
 * @file rtos.hpp
 * @author Medad Rufus Newman (mailto@medadnewman.co.uk)
 * @brief 
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef RTOS_HPP
#define RTOS_HPP

#include <FreeRTOS_SAMD21.h>

void myDelayUs(int us);
void myDelayMs(int ms);
void myDelayMsUntil(TickType_t *previousWakeTime, int ms);

#endif // RTOS_HPP
