#ifndef __FLASH_FUNCTIONS_H__
#define __FLASH_FUNCTIONS_H__

#include "datapacket.hpp"
#include <SPIMemory.h>

extern SPIFlash flash;

void dumpFlash();
bool write_info(dataPacket_t dp);
void flash_init();
void get_user_decision_flash();

//utility variables

typedef struct
{
    bool limit;
    uint8_t command;
    int n;
} user_cmds_t;

extern user_cmds_t user_cmds;

#endif // __FLASH_FUNCTIONS_H__