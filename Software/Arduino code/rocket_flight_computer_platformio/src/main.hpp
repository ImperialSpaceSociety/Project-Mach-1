#ifndef __MAIN_H__
#define __MAIN_H__

#include "datapacket.hpp"
#include "SparkFun_Ublox_Arduino_Library.h" //http://librarymanager/All#SparkFun_u-blox_GNSS

void print_info(dataPacket_t *dp);
extern SFE_UBLOX_GPS ubloxGps;

#endif // __MAIN_H__