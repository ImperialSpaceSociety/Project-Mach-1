/* SPIFFSUsage.ino
 * 
 * This sketch demonstrates various file operations utilizing
 * the Arduino MKR MEM Shield port for the SPIFFS.
 * 
 * Alexander Entinger
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include "file_system.hpp"

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

/* A pangram is a sentence using every letter of a given alphabet at least once. */
static char PANGRAM[] = "The quick brown fox jumps over the lazy dog.";
#define FILE_NAME "data.bin"

/**************************************************************************************
 * SETUP/LOOP
 **************************************************************************************/

OurFile::OurFile()
{
}

void OurFile::init_file_system()
{

    flash.begin();

    Serial.println("Mounting ...");
    if (SPIFFS_OK != filesystem.mount())
    {
        Serial.println("mount() failed with error code ");
        Serial.println(filesystem.err());
        return;
    }

    Serial.println("Checking ...");
    if (SPIFFS_OK != filesystem.check())
    {
        Serial.println("check() failed with error code ");
        Serial.println(filesystem.err());
        return;
    }

    Serial.print("Checking for file ... ");
    File fnf = filesystem.open("404.txt", READ_ONLY);
    if (!fnf)
    {
        Serial.println(" 404.txt does not exist.");
    }

    Serial.print("Checking for file ... ");
    File fox = filesystem.open(FILE_NAME, READ_ONLY);
    if (fox)
    {
        Serial.printf("File %s exists. Data will be appended to it.", FILE_NAME);
        Serial.println();
    }

    Serial.println("Open for writing ...");
    /* Create file if it doesn't exist (SPIFFS_CREAT) and open in 
   * write only mode (SPIFFS_WRONLY). If the file does exist
   * delete the existing content (SPIFFS_TRUNC).
   */
    File file1 = filesystem.open(FILE_NAME, CREATE | READ_WRITE | APPEND);
    file = &file1;
    writing();
}

void OurFile::writing()
{
    Serial.println("Writing ...");

    for (int i = 0; i < 100; i++)
    {
        write_string(file, PANGRAM);
    }

    Serial.println("Retrieving filesystem info ...");
    unsigned int bytes_total = 0,
                 bytes_used = 0;
    if (SPIFFS_OK != filesystem.info(bytes_total, bytes_used))
    {
        Serial.println("check() failed with error code ");
        Serial.println(filesystem.err());
        return;
    }
    else
    {
        char msg[64] = {0};
        snprintf(msg, sizeof(msg), "SPIFFS Info:\nBytes Total: %d\nBytes Used:  %d", bytes_total, bytes_used);
        Serial.println(msg);
    }
}

void OurFile::write_string(File *file, char *string_to_write)
{
    int const bytes_to_write = strlen(string_to_write);
    int const bytes_written = file->write((void *)string_to_write, bytes_to_write);

    if (bytes_written != bytes_to_write)
    {
        Serial.println("write() failed with error code ");
        Serial.println(filesystem.err());
        return;
    }
    else
    {
        Serial.print(bytes_written);
        Serial.println(" bytes written");
    }
}
void OurFile::flush_file(File *file)
{
    Serial.println("Flushing ...");
    file->flush();
}

void OurFile::unmounting()
{
    Serial.println("Unmounting ...");
    filesystem.unmount();
}

void OurFile::read_file(File *file)
{
    Serial.println("Reading ...");
    file->lseek(0, START); /* Rewind file pointer to the start */

    char buf[64] = {0};
    int const bytes_read = file->read(buf, sizeof(buf));
    buf[bytes_read] = '\0';

    file->close();
    Serial.print("[");
    Serial.print(bytes_read);
    Serial.print("] ");
    Serial.println(buf);
}

// bool write_info(dataPacket_t dp)
// {
//     if (flash.writeAnything(_addr, dp))
//     {
//         //increment address pointer
//         _addr += PACKET_SIZE;

//         return true;
//     }
//     else
//     {
//         Serial.println("Problem writing to flash.");
//         return false;
//     }
// }