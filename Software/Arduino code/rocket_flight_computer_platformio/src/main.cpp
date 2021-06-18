
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
#include <MS5xxx.h>
#include "SparkFunLSM9DS1.h"
#include "Si446x.h"
#include <SPIMemory.h>

#include <Wire.h>
#include "datapacket.hpp"
#include "radio_functions.hpp"
#include "flash_functions.hpp"
#include "flash_test_functions.hpp"
#include "util.hpp"

//please get these value by running H3LIS331DL_AdjVal Sketch.
#define VAL_X_AXIS 203
#define VAL_Y_AXIS 165
#define VAL_Z_AXIS 141

//sensor objects
H3LIS331DL h3lis;
SFE_UBLOX_GNSS ubloxGps;
LSM9DS1 imu;
MS5xxx ms5(&Wire);

//time-sensitive util variables
long starttime;
long lasttime;

//utility variables
bool limit = false;
uint8_t command = 0;
int n;

void fill_tx_buffer_with_location(uint16_t start_point, uint8_t *buffer, uint16_t latitude, uint16_t longitude, uint16_t altitude);

//the one datapacket reference we iterate on every run
dataPacket_t dp;

/**
 * Function prototypes
 */

void print_info(dataPacket_t *dp);
void sensor_init();

void setup()
{
  Wire.begin();
  Serial.begin(115200);

  while (true) // remain here until told to break
  {
    if (Serial.available() > 0)
      if (Serial.read() == 'y')
        break;
  }

  Serial.println("Erase chip before run? enter y/n");
  bool erase = false;
  while (true) // remain here until told to break
  {
    if (Serial.available() > 0)
    {
      char res = Serial.read();
      if (res == 'y' || res == 'n')
      {
        erase = res == 'y';
        break;
      }
    }
  }
  if (erase)
  {
    //erase chip before run
    Serial.println("Erasing chip in preparation for run...");
    flash.eraseChip();
  }

  Serial.println("Run for n seconds? y/n");
  while (true) // remain here until told to break
  {
    if (Serial.available() > 0)
    {
      char res = Serial.read();
      if (res == 'y' || res == 'n')
      {
        limit = res == 'y';
        break;
      }
    }
  }
  if (limit)
  {
    Serial.println("How many seconds to record for. Insert number:");
    while (true) // remain here until told to break
    {
      if (Serial.available() > 0)
      {
        String st = Serial.readString();
        if (st.toInt() > 0)
        {
          n = st.toInt();
          break;
        }
      }
    }
  }

  flash_init();
  Serial.println("=========================================");
  Serial.println("This is the Rocket Flight Computer, v1.0");
  Serial.println("Press 1 and enter at any time to dump results from flash and exit the main loop.");
  Serial.println("=========================================");
  starttime = millis();
}

void sensor_init()
{
  Si446x_init();
  Si446x_setTxPower(SI446X_MAX_TX_POWER);
  h3lis.init();
  h3lis.importPara(VAL_X_AXIS, VAL_Y_AXIS, VAL_Z_AXIS);

  if (flash.error())
  {
    Serial.println(flash.error(VERBOSE));
  }
  flash.begin();

  if (!ubloxGps.begin())
  {
    Serial.println(F("Ublox GPS not detected at default I2C address."));
  }

  ubloxGps.setI2COutput(COM_TYPE_UBX);

  if (ms5.connect() > 0)
  {
    Serial.println("Error connecting to MS5607...");
  }

  ms5.ReadProm();

  imu.begin();
  //imu.settings.device.commInterface = IMU_MODE_I2C;

  //test all functionalities on the flash chip, pauses for confirmation
  delay(100);
  Serial.println("Running tests on flash....");
  run_all_tests();
  Serial.println("Tests complete. If all looks good, enter y to continue");
}

//read info into a datapacket
void read_info(dataPacket_t *dp)
{
  //TODO: Add try-catch around the data collections, return a dummy value if failed.
  h3lis.readXYZ(&(dp->location[0]), &(dp->location[1]), &(dp->location[2]));
  h3lis.getAcceleration(dp->acc);

  readGps(&(dp->latitude), &(dp->longitude), &(dp->altitude));

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

void loop()
{

  if (millis() - lasttime > 10)
  {
    if (limit && lasttime > (starttime + n * 1000))
    {
      dumpFlash();
      exit(0);
    }

    lasttime = millis(); //Update the timer
    read_info(&dp);
    print_info(&dp);
    write_info(dp);
    //Serial.println(_addr);

    if (command == 1)
    {
      dumpFlash();
      exit(0);
      command = 0;
    }

    radio_send_data(&dp);
  }

  if (Serial.available() > 0)
  {
    command = Serial.parseInt();
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
