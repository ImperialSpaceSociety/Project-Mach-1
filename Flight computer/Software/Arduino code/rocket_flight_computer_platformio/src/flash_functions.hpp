#ifndef __FLASH_FUNCTIONS_H__
#define __FLASH_FUNCTIONS_H__

#include "datapacket.hpp"

void dumpFlash();
bool write_info(dataPacket_t dp);
void flash_init();
#endif // __FLASH_FUNCTIONS_H__