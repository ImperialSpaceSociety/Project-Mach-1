
/* Code for the Rocket Flight computer
 * Imperial College Space Society
 * version : 1.0
 * Date: 18/02/2020
 * Currently the code only polls the H2LIS100 acclerometer and prints out the values.
 * 
 * Rocket Flight computer modes
 * - Preflight mode - empty loop, constant running checks, listen to arming command, sent n seconds before launch
 * - Armed mode - Test ignition continueity. wait for launch command.
 * - Flight mode - Recording data, transmitting position every second
 * - Recovery mode - No longer records data, Transmits position, LEDs and Buzzer light up for easy recovery
 * - Groundstation mode - Continueously logging data from a flight computer in the field, Must send commands
 */

/* Set whether the device is mounted on the rocket or on the ground */
#define GND_STATION 1
#define ROCKET 2

#define DEVICE_PURPOSE ROCKET // Either ROCKET or GND_STATION

#include <Arduino.h>

#include "main.hpp"
#include "H3LIS331DL.h"
#include <Wire.h>
#include <MS5xxx.h>
#include "SparkFunLSM9DS1.h"
#include "Si446x.h"
#include <SPIMemory.h>

#include "datapacket.hpp"
#include "radio_functions.hpp"
#include "flash_functions.hpp"
#include "flash_test_functions.hpp"
#include "util.hpp"
#include "gps.hpp"

//please get these value by running H3LIS331DL_AdjVal Sketch.
#define VAL_X_AXIS 203
#define VAL_Y_AXIS 165
#define VAL_Z_AXIS 141

#define READ_INTERVAL 10 /* Milliseconds */

//sensor objects
H3LIS331DL h3lis;
LSM9DS1 imu;
MS5xxx sensor(&Wire);

//time-sensitive util variables
long starttime;
long lasttime;

void fill_tx_buffer_with_location(uint16_t start_point, uint8_t *buffer, uint16_t latitude, uint16_t longitude, uint16_t altitude);

//the one datapacket reference we iterate on every run
dataPacket_t dp;

/**
 * Function prototypes
 */

void print_info(dataPacket_t *dp);
void sensor_init();
void get_user_decision_flash();

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  sensor_init();

  get_user_decision_flash();

  flash_init();
  Serial.println("=========================================");
  Serial.println("This is the Rocket Flight Computer, v1.0");
  Serial.println("Press 1 and enter at any time to dump results from flash and exit the main loop.");
  Serial.println("=========================================");
  starttime = millis();
}

void sensor_init()
{
  /* Radio init */
  Si446x_init();
  Si446x_setTxPower(22); // 10 dbm/ 10 mW

  /* 3 axis accelerometer init */
  h3lis.init();
  h3lis.importPara(VAL_X_AXIS, VAL_Y_AXIS, VAL_Z_AXIS);

  /* Flash init */
  if (flash.error())
  {
    Serial.println(flash.error(VERBOSE));
  }
  flash.begin();

  /* GPS init */
  gps_init();

  /* MS5607 Init */
  if (sensor.connect() > 0)
  {
    Serial.println("Error connecting to MS5607...");
  }

  sensor.ReadProm();

  /* init 9 Axis accelerometer/gyro/mag */
  imu.begin();

  /* test all functionalities on the flash chip, pauses for confirmation */
  Serial.println("Running tests on flash....");
  run_all_tests();
  Serial.println("Tests on Flash chip complete.");
}

void test_crc()
{
  sensor.ReadProm();
  sensor.Readout();
  Serial.print("CRC=0x");
  Serial.print(sensor.Calc_CRC4(), HEX);
  Serial.print(" (should be 0x");
  Serial.print(sensor.Read_CRC4(), HEX);
  Serial.print(")\n");
}

//read info into a datapacket
void read_info(dataPacket_t *dp)
{
  //TODO: Add try-catch around the data collections, return a dummy value if failed.
  h3lis.readXYZ(&(dp->location[0]), &(dp->location[1]), &(dp->location[2]));
  h3lis.getAcceleration(dp->acc);

  //readGps(&(dp->latitude), &(dp->longitude), &(dp->altitude));
  gps_check();

  sensor.Readout();
  dp->temp = sensor.GetTemp();
  dp->pressure = sensor.GetPres();

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

void loop()
{

  if (millis() - lasttime > READ_INTERVAL)
  {
    lasttime = millis(); //Update the timer

    // dumpFlash();

    read_info(&dp);
    print_info(&dp);
    write_info(dp);
    //Serial.println(_addr);

    if (user_cmds.command == 1)
    {
      dumpFlash();
      exit(0);
      user_cmds.command = 0;
    }

    radio_send_data(&dp);
  }

  if (Serial.available() > 0)
  {
    user_cmds.command = Serial.parseInt();
  }

#if DEVICE_PURPOSE == GND_STATION
  manage_radio();
#endif
}

//print to serial port
void print_info(dataPacket_t *dp)
{
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

  Serial.print("Temperature [0.01 C]: ");
  Serial.print(dp->temp);
  Serial.print("Pressure [Pa]: ");
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
