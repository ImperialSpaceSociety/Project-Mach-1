/**
 * @file file_system.hpp
 * @author Medad Rufus Newman (mailto@medadnewman.co.uk)
 * @brief 
 * @version 0.1
 * @date 2021-06-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__

#include <Arduino_MKRMEM.h>

#include "datapacket.hpp"

class OurFile
{
public:
    OurFile();
    void init_file_system();
    bool write_info(dataPacket_t dp);
    void flush_file();
    void unmounting();
    void read_file();
    void write_string(char *string_to_write);

    File file;
};

#endif // __FILE_SYSTEM_H__