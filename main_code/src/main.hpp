#ifndef __MAIN_H__
#define __MAIN_H__

#include "datapacket.hpp"

#undef ID // Undefine ID because it is causing a name clash in the GNSS library
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#undef ID

void print_info(dataPacket_t *dp);
extern SFE_UBLOX_GNSS ubloxGps;
extern dataPacket_t dp;

#endif // __MAIN_H__