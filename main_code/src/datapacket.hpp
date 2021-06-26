#ifndef __DATAPACKET_H__
#define __DATAPACKET_H__

#include <stdint.h>

typedef struct
{
    uint32_t timestamp;
    uint32_t gps_unix_time;
    uint32_t gps_ms_in_second;

    //GPS latitude, longitude, altitude
    int32_t latitude;
    int32_t longitude;
    int32_t altitude;

    uint8_t numSV;   // Number of satellites used in Nav Solution
    int32_t velN;    // NED north velocity: mm/s
    int32_t velE;    // NED east velocity: mm/s
    int32_t velD;    // NED down velocity: mm/s
    int32_t gSpeed;  // Ground Speed (2-D): mm/s
    int32_t headMot; // Heading of motion (2-D): deg * 1e-5

    //h3lis, location and accuracy
    int16_t location[3];
    double acc[3];

    //m5 temp + pressure
    double temp;
    double pressure;

    //imu gyro, mag, alt, temp
    float gyro[3];
    float accel[3];
    float mag[3];
} dataPacket_t;

#define PACKET_SIZE sizeof(dataPacket_t)

#endif // __DATAPACKET_H__