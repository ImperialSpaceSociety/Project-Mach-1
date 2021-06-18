#include "Arduino.h"
#include "flash_functions.hpp"
#include "datapacket.hpp"
#include "main.hpp"

//starting address and cursor pointer
uint32_t run_start;
uint32_t _addr;

user_cmds_t user_cmds = {.limit = false, .command = 0, .n = 0};

// bool limit = false;
// uint8_t command = 0;
// int n;

SPIFlash flash(SS_FLASH, &SPI1);

void flash_init()
{
  //find suitable starting place for writing (should be 0)
  run_start = flash.getAddress(PACKET_SIZE);
  _addr = run_start;
}

void read_from_flash(uint32_t addr)
{
  dataPacket_t out;
  flash.readAnything(addr - PACKET_SIZE, out);
  print_info(&out);
}

bool write_info(dataPacket_t dp)
{
  if (flash.writeAnything(_addr, dp))
  {
    //increment address pointer
    _addr += PACKET_SIZE;

    return true;
  }
  else
  {
    Serial.println("Problem writing to flash.");
    return false;
  }
}

void dumpFlash()
{
  int num_packets = _addr / PACKET_SIZE;
  for (int i = 1; i < num_packets; i++)
  {
    read_from_flash(run_start + i * PACKET_SIZE);
  }
}

void get_user_decision_flash()
{
  while (true) // remain here until told to break
  {
    if (Serial.available() > 0)
      if (Serial.read() == 'y')
        break;
  }

  Serial.println("Erase chip before run? enter y/n");
  bool erase = false;
  while (true) // remain here until told to break
  {
    if (Serial.available() > 0)
    {
      char res = Serial.read();
      if (res == 'y' || res == 'n')
      {
        erase = (res == 'y');
        break;
      }
    }
  }
  if (erase)
  {
    //erase chip before run
    Serial.println("Erasing chip in preparation for run...");
    flash.eraseChip();
  }

  Serial.println("Run for n seconds? y/n");
  while (true) // remain here until told to break
  {
    if (Serial.available() > 0)
    {
      char res = Serial.read();
      if (res == 'y' || res == 'n')
      {
        user_cmds.limit = (res == 'y');
        break;
      }
    }
  }
  if (user_cmds.limit)
  {
    Serial.println("How many seconds to record for. Insert number:");
    while (true) // remain here until told to break
    {
      if (Serial.available() > 0)
      {
        String st = Serial.readString();
        if (st.toInt() > 0)
        {
          user_cmds.n = st.toInt();
          break;
        }
      }
    }
  }
}
