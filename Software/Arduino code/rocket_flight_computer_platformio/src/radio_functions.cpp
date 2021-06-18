#include "Si446x.h"
#include "stdint.h"
#include "datapacket.hpp"

///radio stuff
#define CHANNEL 1
#define MAX_PACKET_SIZE 500U
#define TIMEOUT 1000U

#define PACKET_NONE 0
#define PACKET_OK 1
#define PACKET_INVALID 2

typedef struct
{
  uint8_t ready;
  int16_t rssi;
  uint8_t length;
  uint8_t buffer[MAX_PACKET_SIZE];
} pingInfo_t;

static volatile pingInfo_t pingInfo;

void SI446X_CB_RXCOMPLETE(uint8_t length, int16_t rssi)
{
  if (length > MAX_PACKET_SIZE)
    length = MAX_PACKET_SIZE;

  pingInfo.ready = PACKET_OK;
  pingInfo.rssi = rssi;
  pingInfo.length = length;

  Si446x_read((uint8_t *)pingInfo.buffer, length);

  // Radio will now be in idle mode
}

void SI446X_CB_RXINVALID(int16_t rssi)
{
  pingInfo.ready = PACKET_INVALID;
  pingInfo.rssi = rssi;
}

void manage_radio()
{

  char commands[] = {'0', '1', '3'};

  if (Serial.available())
  {
    String command = Serial.readStringUntil('\n');
    if (command.equals("Fire"))
    {
      Si446x_TX(&commands[0], sizeof(char), CHANNEL, SI446X_STATE_RX);
    }
    else if (command.equals("Clear"))
    {
      Si446x_TX(&commands[1], sizeof(char), CHANNEL, SI446X_STATE_RX);
    }
    else if (command.equals("Parachute"))
    {
      Si446x_TX(&commands[2], sizeof(char), CHANNEL, SI446X_STATE_RX);
    }
    else
    {
      Serial.println("Invalid command");
    }
  }
}

void radio_send_data(dataPacket_t *dp)
{
  //convert to string (not sure if neccessary but dont know how to do it differently)
  String data = String(dp->latitude) + "," + String(dp->longitude) + "," + String(dp->altitude);
  Serial.print(data);
  // Send the data
  // TODO: send the only every second, not every 10 milliseconds.
  Si446x_TX(&data, sizeof(data), CHANNEL, SI446X_STATE_RX);
}
