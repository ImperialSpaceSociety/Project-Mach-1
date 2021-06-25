/**
 * @file telemetry.hpp
 * @author Medad Rufus Newman (mailto@medadnewman.co.uk)
 * @brief 
 * @version 0.1
 * @date 2021-06-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __TELEMETRY_H__
#define __TELEMETRY_H__

#include "datapacket.hpp"

void radio_send_data(dataPacket_t *dp);

#endif // __TELEMETRY_H__