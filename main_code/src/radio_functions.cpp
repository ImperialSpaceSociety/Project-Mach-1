#include "Si446x.h"
#include "datapacket.hpp"

#if 0 // Not yet implemented commands from ground.
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
#endif
