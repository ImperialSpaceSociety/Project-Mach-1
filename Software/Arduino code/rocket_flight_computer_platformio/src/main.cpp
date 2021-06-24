
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
#include "config.h"

#include "H3LIS331DL.h"
#include <Wire.h>
#include <MS5xxx.h>
#include "SparkFunLSM9DS1.h"
#include "Si446x.h"
#include <SPIMemory.h>
#include <FreeRTOS_SAMD21.h>

#include "file_system.hpp"
#include "datapacket.hpp"
#include "radio_functions.hpp"
#include "util.hpp"
#include "gps.hpp"
#include "rtos.hpp"

//**************************************************************************
// Type Defines and Constants
//**************************************************************************

// Select the serial port the project should use and communicate over
// Some boards use SerialUSB, some use Serial
//#define SERIAL SerialUSB //Sparkfun Samd21 Boards
#define SERIAL Serial //Adafruit, other Samd21 Boards

//**************************************************************************
// global variables
//**************************************************************************
//sensor objects
H3LIS331DL h3lis;
LSM9DS1 imu;
MS5xxx sensor(&Wire);

TaskHandle_t Handle_TaskBlink;
TaskHandle_t Handle_SensorRead;
TaskHandle_t Handle_monitorTask;

//time-sensitive util variables
long starttime;
long lasttime;

//the one datapacket reference we iterate on every run
dataPacket_t dp;
OurFile ourfile;

//**************************************************************************
// Function Prototypes
//**************************************************************************

void print_info(dataPacket_t *dp);
void sensor_init();
void setup_rtos();
void fill_tx_buffer_with_location(uint16_t start_point, uint8_t *buffer, uint16_t latitude, uint16_t longitude, uint16_t altitude);

//**************************************************************************
// Function definitions
//**************************************************************************

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  ourfile.init_file_system();
  sensor_init();

  Serial.println("=========================================");
  Serial.println("This is the Rocket Flight Computer, v1.0");
  Serial.println("Press 1 and enter at any time to dump results from flash and exit the main loop.");
  Serial.println("=========================================");
  starttime = millis();

  setup_rtos();
}

void sensor_init()
{
  /* Radio init */
  Si446x_init();
  Si446x_setTxPower(22); // 10 dbm/ 10 mW

  /* 3 axis accelerometer init */
  h3lis.init();
  h3lis.importPara(VAL_X_AXIS, VAL_Y_AXIS, VAL_Z_AXIS);

  /* GPS init */
  gps_init();

  /* MS5607 Init */
  sensor.setI2Caddr(0x77); // Set i2c address specific to our board
  if (sensor.connect() > 0)
  {
    Serial.println("Error connecting to MS5607...");
  }

  sensor.ReadProm();

  /* init 9 Axis accelerometer/gyro/mag */
  imu.begin();
}

//read info into a datapacket
void read_info(dataPacket_t *dp)
{
  //TODO: Add try-catch around the data collections, return a dummy value if failed.
  h3lis.readXYZ(&(dp->location[0]), &(dp->location[1]), &(dp->location[2]));
  h3lis.getAcceleration(dp->acc);

  // readGps(&(dp->latitude), &(dp->longitude), &(dp->altitude));
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

/*
  Blink
  Turns on an LED on for BLINK_INTERVAL, then off for BLINK_INTERVAL, repeatedly.
*/
void TaskBlink(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = BLINK_INTERVAL;

  bool led_state = false; // false is OFF, true is ON

  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(PIN_LED_BLUE, OUTPUT);
  digitalWrite(PIN_LED_BLUE, led_state ? HIGH : LOW);

  // Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount();
  for (;;)
  {
    // Wait for the next cycle.
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    led_state = !led_state;
    digitalWrite(PIN_LED_BLUE, led_state ? HIGH : LOW);
  }
}

/**
 * @brief Read the sensors and save to flash
 * 
 * @param pvParameters 
 */
static void threadSensorRead(void *pvParameters)
{
  (void)pvParameters;

  TickType_t xLastWakeTime;
  const TickType_t xFrequency = INA226_SAMPLE_INTERVAL;

  // Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount();
  for (;;)
  {
    // Wait for the next cycle.
    vTaskDelayUntil(&xLastWakeTime, xFrequency);

    // run task here.
    read_info(&dp);
    print_info(&dp);
    write_info(dp);
    radio_send_data(&dp);
  }
}

//*****************************************************************
// Task will periodically print out useful information about the tasks running
// Is a useful tool to help figure out stack sizes being used
// Run time stats are generated from all task timing collected since startup
// No easy way yet to clear the run time stats yet
//*****************************************************************
static char ptrTaskList[400]; //temporary string buffer for task stats

void taskMonitor(void *pvParameters)
{
  int x;
  int measurement;

  SERIAL.println("Task Monitor: Started");

  // run this task afew times before exiting forever
  while (1)
  {
    myDelayMs(10000); // print every 10 seconds

    SERIAL.flush();
    SERIAL.println("");
    SERIAL.println("****************************************************");
    SERIAL.print("Free Heap: ");
    SERIAL.print(xPortGetFreeHeapSize());
    SERIAL.println(" bytes");

    SERIAL.print("Min Heap: ");
    SERIAL.print(xPortGetMinimumEverFreeHeapSize());
    SERIAL.println(" bytes");
    SERIAL.flush();

    SERIAL.println("****************************************************");
    SERIAL.println("Task            ABS             %Util");
    SERIAL.println("****************************************************");

    vTaskGetRunTimeStats(ptrTaskList); //save stats to char array
    SERIAL.println(ptrTaskList);       //prints out already formatted stats
    SERIAL.flush();

    SERIAL.println("****************************************************");
    SERIAL.println("Task            State   Prio    Stack   Num     Core");
    SERIAL.println("****************************************************");

    vTaskList(ptrTaskList);      //save stats to char array
    SERIAL.println(ptrTaskList); //prints out already formatted stats
    SERIAL.flush();

    SERIAL.println("****************************************************");
    SERIAL.println("[Stacks Free Bytes Remaining] ");

    measurement = uxTaskGetStackHighWaterMark(Handle_TaskBlink);
    SERIAL.print("Thread A: ");
    SERIAL.println(measurement);

    measurement = uxTaskGetStackHighWaterMark(Handle_SensorRead);
    SERIAL.print("Thread B: ");
    SERIAL.println(measurement);

    measurement = uxTaskGetStackHighWaterMark(Handle_monitorTask);
    SERIAL.print("Monitor Stack: ");
    SERIAL.println(measurement);

    SERIAL.println("****************************************************");
    SERIAL.flush();
  }

  // delete ourselves.
  // Have to call this or the system crashes when you reach the end bracket and then get scheduled.
  SERIAL.println("Task Monitor: Deleting");
  vTaskDelete(NULL);
}

//*****************************************************************

void setup_rtos()
{
  // Set the led the rtos will blink when we have a fatal rtos error
  // RTOS also Needs to know if high/low is the state that turns on the led.
  // Error Blink Codes:
  //    3 blinks - Fatal Rtos Error, something bad happened. Think really hard about what you just changed.
  //    2 blinks - Malloc Failed, Happens when you couldn't create a rtos object.
  //               Probably ran out of heap.
  //    1 blink  - Stack overflow, Task needs more bytes defined for its stack!
  //               Use the taskMonitor thread to help gauge how much more you need
  vSetErrorLed(ERROR_LED_PIN, ERROR_LED_LIGHTUP_STATE);

  // sets the serial port to print errors to when the rtos crashes
  // if this is not set, serial information is not printed by default
  vSetErrorSerial(&SERIAL);

  // Create the threads that will be managed by the rtos
  // Sets the stack size and priority of each task
  // Also initializes a handler pointer to each task, which are important to communicate with and retrieve info from tasks
  xTaskCreate(TaskBlink, "TaskBlink", 256, NULL, tskIDLE_PRIORITY + 3, &Handle_TaskBlink);
  xTaskCreate(threadSensorRead, "threadSensorRead", 1000, NULL, tskIDLE_PRIORITY + 2, &Handle_SensorRead);
  xTaskCreate(taskMonitor, "Task Monitor", 256, NULL, tskIDLE_PRIORITY + 1, &Handle_monitorTask);

  // Start the RTOS, this function will never return and will schedule the tasks.
  vTaskStartScheduler();

  // error scheduler failed to start
  // should never get here
  while (1)
  {
    SERIAL.println("Scheduler Failed! \n");
    SERIAL.flush();
    delay(1000);
  }
}

void loop()
{
}