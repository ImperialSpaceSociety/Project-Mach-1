/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef DRIVER_INIT_INCLUDED
#define DRIVER_INIT_INCLUDED

#include "atmel_start_pins.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <hal_atomic.h>
#include <hal_delay.h>
#include <hal_gpio.h>
#include <hal_init.h>
#include <hal_io.h>
#include <hal_sleep.h>

#include <hal_i2c_m_sync.h>

#include <hal_usart_sync.h>

#include <hal_i2c_m_sync.h>
#include <hal_spi_m_sync.h>
#include <hal_spi_m_sync.h>

extern struct i2c_m_sync_desc I2C_breakout;

extern struct usart_sync_descriptor USART_GPS;

extern struct i2c_m_sync_desc       I2C_GPS_Sensors;
extern struct spi_m_sync_descriptor SPI_Radio;
extern struct spi_m_sync_descriptor SPI_Flash_mem;

void I2C_breakout_CLOCK_init(void);
void I2C_breakout_init(void);
void I2C_breakout_PORT_init(void);

void USART_GPS_PORT_init(void);
void USART_GPS_CLOCK_init(void);
void USART_GPS_init(void);

void I2C_GPS_Sensors_CLOCK_init(void);
void I2C_GPS_Sensors_init(void);
void I2C_GPS_Sensors_PORT_init(void);

void SPI_Radio_PORT_init(void);
void SPI_Radio_CLOCK_init(void);
void SPI_Radio_init(void);

void SPI_Flash_mem_PORT_init(void);
void SPI_Flash_mem_CLOCK_init(void);
void SPI_Flash_mem_init(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_INCLUDED
