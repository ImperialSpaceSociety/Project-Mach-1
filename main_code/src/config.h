/**
 * @file config.h
 * @author Medad Rufus Newman (mailto@medadnewman.co.uk)
 * @brief 
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifdef __cplusplus
extern "C"
{
#endif

#ifndef Config_h
#define Config_h

  /* ==================================================================== */
  /* ========================== include files =========================== */
  /* ==================================================================== */

  /* Inclusion of system and local header files goes here */

  /* ==================================================================== */
  /* ============================ constants ============================= */
  /* ==================================================================== */

  /* #define and enum statements go here */

/* Config section */

//please get these value by running H3LIS331DL_AdjVal Sketch.
#define VAL_X_AXIS 203
#define VAL_Y_AXIS 165
#define VAL_Z_AXIS 141

#define READ_INTERVAL 10 /* Milliseconds */

// Arduino pin assignments
#undef SI446X_CSN
#undef SI446X_SDN
#undef SI446X_IRQ
#define SI446X_CSN 35
#define SI446X_SDN 31
#define SI446X_IRQ 30 // This needs to be an interrupt pin

#define ERROR_LED_PIN PIN_LED_BLUE   //Led Pin: Typical Arduino Board
#define ERROR_LED_LIGHTUP_STATE HIGH // the state that makes the led light up on your board, either low or high

/*
  Set to true or false to poll/not poll
*/
#define POLL_BARO (true)
#define POLL_GPS (true)
#define POLL_IMU (true)
#define POLL_INA226 (true)
#define POLL_PAS (true)
#define POLL_MOTOR_SPEED (true)
#define POLL_BRAKE (true)

#define HEAP_ANALYSIS (false)
#define PERIODIC_CLOSE_FILE (true)
#define INTERVAL_BETWEEN_FLUSHING_FILE 10000UL

/* poll intervals in milliseconds */
#define INA226_SAMPLE_INTERVAL 50
#define GNSS_SAMPLE_INTERVAL 50
#define BARO_SAMPLE_INTERVAL 250
#define IMU_SAMPLE_INTERVAL 10
#define BLINK_INTERVAL 100
#define BRAKE_INTERVAL 100
#define SPEED_INTERVAL 100
#define TELEMETRY_INTERVAL 1000

/* Number of GPS fixes in a second */
#define FIXS_PER_SECOND 10

#define FILE_NAME "data.bin"

  /* ==================================================================== */
  /* ========================== public data ============================= */
  /* ==================================================================== */

  /* Definition of public (external) data types go here */

  /* ==================================================================== */
  /* ======================= public functions =========================== */
  /* ==================================================================== */

  /* Function prototypes for public (external) functions go here */

#endif
#ifdef __cplusplus
}
#endif
