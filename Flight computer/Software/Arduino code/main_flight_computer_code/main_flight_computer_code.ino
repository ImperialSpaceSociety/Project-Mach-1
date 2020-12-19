/* Code for the Rocket Flight computer
 * Imperial College Space Society
 * version : 1.0
 * Date: 18/02/2020
 * Currently the code only polls the H2LIS100 acclerometer and prints out the values.
 * TODO: 
 * 1. get all the other sensors to work and print out values
 * 2. get the SPI flash chip to record down the values
 * 3. Get the radio to transmit its position.
 */

//this is a comment

#include "H3LIS100DL.h"
#include "MS5607.h"
#include "Ublox.h"
#include "SparkFunLSM9DS1.h"
#include "Si446x.h"

#include <Wire.h>

///radio stuff
#define CHANNEL 1
#define MAX_PACKET_SIZE 500
#define TIMEOUT 1000

#define PACKET_NONE    0
#define PACKET_OK   1
#define PACKET_INVALID  2

//please get these value by running H3LIS331DL_AdjVal Sketch.
#define VAL_X_AXIS  203
#define VAL_Y_AXIS  165
#define VAL_Z_AXIS  141

H3LIS331DL h3lis;
SFE_UBLOX_GPS ubloxGps;
MS5xxx ms5(&Wire);
LSM9DS1 imu;

typedef struct{
  uint8_t ready;
  uint32_t timestamp;
  int16_t rssi;
  uint8_t length;
  uint8_t buffer[MAX_PACKET_SIZE];
} pingInfo_t;

static volatile pingInfo_t pingInfo;

void SI446X_CB_RXCOMPLETE(uint8_t length, int16_t rssi)
{
  if(length > MAX_PACKET_SIZE)
    length = MAX_PACKET_SIZE;

  pingInfo.ready = PACKET_OK;
  pingInfo.timestamp = millis();
  pingInfo.rssi = rssi;
  pingInfo.length = length;

  Si446x_read((uint8_t*)pingInfo.buffer, length);

  // Radio will now be in idle mode
}

void SI446X_CB_RXINVALID(int16_t rssi)
{
  pingInfo.ready = PACKET_INVALID;
  pingInfo.rssi = rssi;
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Si446x_init();
  Si446x_setTxPower(SI446X_MAX_TX_POWER);
  h3lis.init();
  if (!ubloxGps.begin())
  {
    Serial.println(F("Ublox GPS not detected at default I2C address."));
    while (1);
  }
  ubloxGps.setI2COutput(COM_TYPE_UBX);
  h3lis.importPara(VAL_X_AXIS,VAL_Y_AXIS,VAL_Z_AXIS); //3deg Accelerometer
  imu.begin();
  //imu.settings.device.commInterface = IMU_MODE_I2C;
  Serial.print("=========================================");
  Serial.print("This is the Rocket Flight Computer, v1.0");
  Serial.print("=========================================");
}

void readGps(long *latitude, long *longitude, long *altitude) {
  *latitude = ubloxGps.getLatitude();
  *longitude = ubloxGps.getLongitude();
  *altitude = ubloxGps.getAltitude();
}

void loop() {
  int16_t x,y,z;
  long latitude, longitude, altitude;
  readGps(&latitude, &longitude, &altitude);
  
  //convert to string (not sure if neccessary but dont know how to do it differently)
  char dataLat[MAX_PACKET_SIZE] = {0};
  char dataLon[MAX_PACKET_SIZE] = {0};
  char dataAlt[MAX_PACKET_SIZE] = {0};
  sprintf_P(dataLat, "%ld", latitude);
  sprintf_P(dataLon, "%ld", latitude);
  sprintf_P(dataAlt, "%ld", latitude);
  // Send the data (not sure if this works, maybe can do in one pulse?)
  Si446x_TX(dataLat, sizeof(dataLat), CHANNEL, SI446X_STATE_RX);
  Si446x_TX(dataLon, sizeof(dataLon), CHANNEL, SI446X_STATE_RX);
  Si446x_TX(dataAlt, sizeof(dataAlt), CHANNEL, SI446X_STATE_RX);
  
  h3lis.readXYZ(&x,&y,&z);
  Serial.print("x, y, z = ");
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.println(z);

  double xyz[3];
  h3lis.getAcceleration(xyz);
  Serial.print("accelerate of x, y, z = ");
  Serial.print(xyz[0]);
  Serial.print("g");
  Serial.print("\t");
  Serial.print(xyz[1]);
  Serial.print("g");
  Serial.print("\t");
  Serial.print(xyz[2]);
  Serial.println("g");

  imu.readGyro();
  imu.readAccel();
  imu.readMag();
  imu.readTemp();
  Serial.print(imu.calcGyro(imu.gx), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gy), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gz), 2);
  Serial.println(" deg/s");
  Serial.print(imu.calcAccel(imu.ax), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.ay), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.az), 2);
  Serial.println(" g");
  Serial.print(imu.calcMag(imu.mx), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.my), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.mz), 2);
  Serial.println(" gauss");
  Serial.print("9degTemperature: ");
  Serial.println(imu.temperature);
  
  ms5.ReadProm();
  ms5.Readout();

  Serial.print("Temperature: ");
  Serial.println(ms5.GetTemp());
  Serial.print("Pressure: ");
  Serial.println(ms5.GetPres());
  
  delay(100);
}
