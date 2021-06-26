/*
  Configuring the GNSS to automatically send position reports over I2C and display them using a callback
  By: Paul Clark
  SparkFun Electronics
  Date: December 30th, 2020
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  This example shows how to configure the u-blox GNSS to send navigation reports automatically
  and access the data via a callback. No more polling!

  Feel like supporting open source hardware?
  Buy a board from SparkFun!
  ZED-F9P RTK2: https://www.sparkfun.com/products/15136
  NEO-M8P RTK: https://www.sparkfun.com/products/15005
  SAM-M8Q: https://www.sparkfun.com/products/15106

  Hardware Connections:
  Plug a Qwiic cable into the GPS and a BlackBoard
  If you don't have a platform with a Qwiic connection use the SparkFun Qwiic Breadboard Jumper (https://www.sparkfun.com/products/14425)
  Open the serial monitor at 115200 baud to see the output
*/

/**
 * @file gps.cpp
 * @author Medad Rufus Newman (mailto@medadnewman.co.uk)
 * @brief 
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Wire.h> //Needed for I2C to GPS
#include "config.h"

#include <SparkFun_u-blox_GNSS_Arduino_Library.h> //http://librarymanager/All#SparkFun_u-blox_GNSS
#include "main.hpp"
#include <time.h>
SFE_UBLOX_GNSS myGNSS;

unsigned long tmConvert_t(short YY, short MM, short DD, short hh, short mm, short ss)
{

    struct tm t;
    time_t t_of_day;

    t.tm_year = YY - 1900; // Year - 1900
    t.tm_mon = MM - 1;     // Month, where 0 = jan
    t.tm_mday = DD;        // Day of the month
    t.tm_hour = hh;
    t.tm_min = mm;
    t.tm_sec = ss;
    t.tm_isdst = 0; // Is DST on? 1 = yes, 0 = no, -1 = unknown
    t_of_day = mktime(&t);

    return (unsigned long)t_of_day;
}

// Callback: printPVTdata will be called when new NAV PVT data arrives
// See u-blox_structs.h for the full definition of UBX_NAV_PVT_data_t
//         _____  You can use any name you like for the callback. Use the same name when you call setAutoPVTcallback
//        /                  _____  This _must_ be UBX_NAV_PVT_data_t
//        |                 /               _____ You can use any name you like for the struct
//        |                 |              /
//        |                 |              |
void printPVTdata(UBX_NAV_PVT_data_t ubxDataStruct)
{
    Serial.println();

    Serial.printf(" GPS time: %02d/%02d/%04d, %02d:%02d:%02d.%04d ",
                  ubxDataStruct.day,
                  ubxDataStruct.month,
                  ubxDataStruct.year,
                  ubxDataStruct.hour,
                  ubxDataStruct.min,
                  ubxDataStruct.sec,
                  ubxDataStruct.iTOW % 1000);

    long latitude = ubxDataStruct.lat; // Print the latitude
    Serial.print(F(" Lat: "));
    Serial.print(latitude);

    long longitude = ubxDataStruct.lon; // Print the longitude
    Serial.print(F(" Long: "));
    Serial.print(longitude);
    Serial.print(F(" (degrees * 10^-7)"));

    long altitude = ubxDataStruct.hMSL; // Print the height above mean sea level
    Serial.print(F(" Height above MSL: "));
    Serial.print(altitude);
    Serial.println(F(" (mm)"));

    unsigned long unix_time = tmConvert_t(
        ubxDataStruct.year,
        ubxDataStruct.month - 1,
        ubxDataStruct.day,
        ubxDataStruct.hour,
        ubxDataStruct.min,
        ubxDataStruct.sec);

    dp.longitude = ubxDataStruct.lon;
    dp.latitude = ubxDataStruct.lat;
    dp.altitude = ubxDataStruct.hMSL;
    dp.gps_unix_time = unix_time;
    dp.gps_ms_in_second = ubxDataStruct.iTOW % 1000;
}

void gps_init()
{
    //myGNSS.enableDebugging(); // Uncomment this line to enable helpful debug messages on Serial

    if (myGNSS.begin() == false) //Connect to the u-blox module using Wire port
    {
        Serial.println(F("u-blox GNSS not detected at default I2C address. Please check wiring. Freezing."));
        //while (1);
    }

    myGNSS.setI2COutput(COM_TYPE_UBX);                 //Set the I2C port to output UBX only (turn off NMEA noise)
    myGNSS.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT); //Save (only) the communications port settings to flash and BBR

    myGNSS.setNavigationFrequency(FIXS_PER_SECOND); //Produce 10 solutions per second

    myGNSS.setAutoPVTcallback(&printPVTdata); // Enable automatic NAV PVT messages with callback to printPVTdata
}

void gps_check()
{
    myGNSS.checkUblox();     // Check for the arrival of new data and process it.
    myGNSS.checkCallbacks(); // Check if any callbacks are waiting to be processed.
}