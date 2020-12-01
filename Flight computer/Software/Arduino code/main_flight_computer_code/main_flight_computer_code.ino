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
#include <SPIMemory.h>

//please get these value by running H3LIS331DL_AdjVal Sketch.
#define VAL_X_AXIS  203
#define VAL_Y_AXIS  165
#define VAL_Z_AXIS  141

H3LIS331DL h3lis;
MS5xxx ms5(&Wire);
SPIFlash flash(SS_FLASH, &SPI1);

long lasttime = 0;

struct dataPacket{
  //h3lis, location and accuracy
  int16_t location[3];
  double acc[3];

  //m5 temp + pressure
  double temp;
  double pressure;
};

dataPacket dp;

void setup() {
  Serial.begin(9600);
  h3lis.init();
  h3lis.importPara(VAL_X_AXIS,VAL_Y_AXIS,VAL_Z_AXIS);
  
  flash.begin();
  Serial.print("=========================================");
  Serial.print("This is the Rocket Flight Computer, v1.0");
  Serial.print("=========================================");

}

void loop() {
  //I think 10 ms is too little, there is something that stalls the process
  if(millis() - lasttime > 10){
    lasttime = millis(); //Update the timer

    long t1 = millis();
    read_info(&dp);
    long t2 = millis();
    Serial.print(t2-t1);
    print_info(&dp);

    //write_info(&dp);
    
  }

}


//read info into a datapacket
void read_info(dataPacket *dp){
  //TODO: Add try-catch around the data collections, return a dummy value if failed.
  h3lis.readXYZ(&(dp->location[0]),&(dp->location[1]),&(dp->location[2]));
  h3lis.getAcceleration(dp->acc);

  ms5.ReadProm();
  ms5.Readout();

  dp->temp = ms5.GetTemp();
  dp->pressure = ms5.GetPres();
}

//print to serial port
void print_info(dataPacket *dp) {
    Serial.print("x, y, z = ");
    Serial.print(dp->location[0]);
    Serial.print("\t");
    Serial.print(dp->location[1]);
    Serial.print("\t");
    Serial.println(dp->location[2]);

    Serial.print("accelerate of x, y, z = ");
    Serial.print(dp->acc[0]);
    Serial.print("g");
    Serial.print("\t");
    Serial.print(dp->acc[1]);
    Serial.print("g");
    Serial.print("\t");
    Serial.print(dp->acc[2]);
    Serial.println("g");

    Serial.print("Temperature: ");
    Serial.println(dp->temp);
    Serial.print("Pressure: ");
    Serial.println(dp->pressure);
}

//TODO: figure out what to do if the write fails.
//bool write_info(dataPacket *dp){
//  if (flash.writeShort(addr, _d)) {
//    wTime = flash.functionRunTime();
//  }
//}
