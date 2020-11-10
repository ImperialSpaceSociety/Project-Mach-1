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

#include <Wire.h>

//please get these value by running H3LIS331DL_AdjVal Sketch.
#define VAL_X_AXIS  203
#define VAL_Y_AXIS  165
#define VAL_Z_AXIS  141

H3LIS331DL h3lis;
SFE_UBLOX_GPS ubloxGps;


void setup() {
  Wire.begin();
  Serial.begin(9600);
  h3lis.init();
  h3lis.importPara(VAL_X_AXIS, VAL_Y_AXIS, VAL_Z_AXIS);
  if (ubloxGps.begin() == false)
  {
    Serial.println(F("Ublox GPS not detected at default I2C address."));
    while (1);
  }
  ubloxGps.setI2COutput(COM_TYPE_UBX);
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
  
  delay(1);
}
