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

/* Set whether the device is mounted on the rocket or on the ground */
#define GND_STATION 1
#define ROCKET 2

#define DEVICE_PURPOSE ROCKET // Either ROCKET or GND_STATION



#include "H3LIS100DL.h"
#include "MS5607.h"
#include "Ublox.h"
#include "SparkFunLSM9DS1.h"
#include "Si446x.h"

#include <Wire.h>
#include <SPIMemory.h>

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

//sensor objects
H3LIS331DL h3lis;
SFE_UBLOX_GPS ubloxGps;
LSM9DS1 imu;
MS5xxx ms5(&Wire);

//flash
SPIFlash flash(SS_FLASH, &SPI1);

//time-sensitive util variables
long starttime;
long lasttime;

struct dataPacket{
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
};

#define PACKET_SIZE sizeof(dataPacket)

//the one datapacket reference we iterate on every run
dataPacket dp;

//starting address and cursor pointer
uint32_t run_start;
uint32_t _addr;

//utility variables
bool limit = false;
uint8_t command = 0;
int n;

struct pingInfo_t{
  uint8_t ready;
  uint32_t timestamp;
  int16_t rssi;
  uint8_t length;
  uint8_t buffer[MAX_PACKET_SIZE];
}; 

static volatile pingInfo_t pingInfo;

//Why do we need these???
static uint8_t tx_str_buffer[MAX_PACKET_SIZE];
void fill_tx_buffer_with_location(uint16_t start_point, uint8_t * buffer, uint16_t latitude, uint16_t longitude, uint16_t altitude );

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Si446x_init();
  Si446x_setTxPower(SI446X_MAX_TX_POWER);
  h3lis.init();
  h3lis.importPara(VAL_X_AXIS,VAL_Y_AXIS,VAL_Z_AXIS);
  ubloxGps.setI2COutput(COM_TYPE_UBX);
  
  if (flash.error()) {
    Serial.println(flash.error(VERBOSE));
  }
  flash.begin();
  
  if (!ubloxGps.begin())
  {
    Serial.println(F("Ublox GPS not detected at default I2C address."));
    while (1);
  }
  
  imu.begin();
  //imu.settings.device.commInterface = IMU_MODE_I2C;

  //test all functionalities on the flash chip, pauses for confirmation
  delay(3000);
  Serial.println("Running tests on flash....");
  run_all_tests();
  Serial.println("Tests complete. If all looks good, enter y to continue");

  while(true) // remain here until told to break
  {
    if(Serial.available() > 0)
      if(Serial.read() == 'y')
        break;
  }

  Serial.println("Erase chip before run? enter y/n");
  bool erase = false;
  while(true) // remain here until told to break
  {
    if(Serial.available() > 0){
      char res = Serial.read();
      if(res == 'y' || res == 'n'){
        erase = res == 'y';
        break; 
      } 
    }
  }
  if(erase){
    //erase chip before run
    Serial.println("Erasing chip in preparation for run...");
    flash.eraseChip();
  }

  Serial.println("Run for n seconds? y/n");
  while(true) // remain here until told to break
  {
    if(Serial.available() > 0){
      char res = Serial.read();
      if(res == 'y' || res == 'n'){
        limit = res == 'y';
        break; 
      } 
    }
  }
  if(limit){
    Serial.println("How many seconds to record for. Insert number:");
    while(true) // remain here until told to break
    {
      if(Serial.available() > 0){
        String st = Serial.readString();
        if(st.toInt() > 0){
           n = st.toInt();
           break;
        }
      }
    }
  }
  
  //find suitable starting place for writing (should be 0)
  run_start = flash.getAddress(PACKET_SIZE);
  _addr = run_start;
  Serial.println("=========================================");
  Serial.println("This is the Rocket Flight Computer, v1.0");
  Serial.println("Press 1 and enter at any time to dump results from flash and exit the main loop.");
  Serial.println("=========================================");
  starttime = millis();
}

void loop() { 
  

  if(millis() - lasttime > 10){
    if(limit && lasttime > (starttime + n * 1000)){
      dumpFlash();
      exit(0);
    }
    
    lasttime = millis(); //Update the timer
    read_info(&dp);
    //print_info(&dp);
    write_info(dp);
    Serial.println(_addr);

    if (command == 1){
      dumpFlash();
      exit(0);
      command = 0;
    }

    radio_send_data(&dp);
  }

  if (Serial.available() > 0){
    command = Serial.parseInt();      
  }

  
  #if DEVICE_PURPOSE == GND_STATION
  manage_radio();
  #endif
}


//read info into a datapacket
void read_info(dataPacket *dp){
  //TODO: Add try-catch around the data collections, return a dummy value if failed.
  h3lis.readXYZ(&(dp->location[0]),&(dp->location[1]),&(dp->location[2]));
  h3lis.getAcceleration(dp->acc);

  readGps(&(dp->latitude), &(dp->longitude), &(dp->altitude));

  ms5.ReadProm();
  ms5.Readout();

  dp->temp = ms5.GetTemp();
  dp->pressure = ms5.GetPres();

  imu.readGyro();
  imu.readAccel();
  imu.readMag();
  imu.readTemp();

  dp->gyro[0] = imu.calcGyro(imu.gx);
  dp->gyro[1] = imu.calcGyro(imu.gy);
  dp->gyro[2] = imu.calcGyro(imu.gz);

  dp->accel[0] = imu.calcGyro(imu.ax);
  dp->accel[1] = imu.calcGyro(imu.ay);
  dp->accel[2] = imu.calcGyro(imu.az);

  dp->mag[0] = imu.calcGyro(imu.mx);
  dp->mag[1] = imu.calcGyro(imu.my);
  dp->mag[2] = imu.calcGyro(imu.mz);
  
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

    Serial.print("Gyro: ");
    Serial.print(dp->gyro[0], 2);
    Serial.print(", ");
    Serial.print(dp->gyro[1], 2);
    Serial.print(", ");
    Serial.print(dp->gyro[2], 2);
    Serial.println(" deg/s");
    Serial.print("Acceleration: ");
    Serial.print(dp->accel[0], 2);
    Serial.print(", ");
    Serial.print(dp->accel[1], 2);
    Serial.print(", ");
    Serial.print(dp->accel[2], 2);
    Serial.println(" g");
    Serial.print("Mag: ");
    Serial.print(dp->mag[0], 2);
    Serial.print(", ");
    Serial.print(dp->mag[1], 2);
    Serial.print(", ");
    Serial.print(dp->mag[2], 2);
    Serial.println(" gauss");

    Serial.print("GPS info: ");
    Serial.print(dp->longitude);
    Serial.print(", ");
    Serial.print(dp->latitude);
    Serial.print(", ");
    Serial.print(dp->altitude);
    Serial.println();
}
