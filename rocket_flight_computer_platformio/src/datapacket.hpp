#ifndef __DATAPACKET_H__
#define __DATAPACKET_H__

#include <stdint.h>

typedef struct
{
    //h3lis, location and accuracy
    int16_t location[3];
    double acc[3];

    //m5 temp + pressure
    double temp;
    double pressure;

    //GPS latitude, longitude, altitude
    long latitude;
    long longitude;
    long altitude;

    //imu gyro, mag, alt, temp
    double gyro[3];
    double accel[3];
    double mag[3];
} dataPacket_t;

#define PACKET_SIZE sizeof(dataPacket_t)

#endif // __DATAPACKET_H__