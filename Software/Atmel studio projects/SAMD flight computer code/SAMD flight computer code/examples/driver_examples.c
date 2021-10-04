/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

void I2C_breakout_example(void)
{
	struct io_descriptor *I2C_breakout_io;

	i2c_m_sync_get_io_descriptor(&I2C_breakout, &I2C_breakout_io);
	i2c_m_sync_enable(&I2C_breakout);
	i2c_m_sync_set_slaveaddr(&I2C_breakout, 0x12, I2C_M_SEVEN);
	io_write(I2C_breakout_io, (uint8_t *)"Hello World!", 12);
}

/**
 * Example of using USART_GPS to write "Hello World" using the IO abstraction.
 */
void USART_GPS_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART_GPS, &io);
	usart_sync_enable(&USART_GPS);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

void I2C_GPS_Sensors_example(void)
{
	struct io_descriptor *I2C_GPS_Sensors_io;

	i2c_m_sync_get_io_descriptor(&I2C_GPS_Sensors, &I2C_GPS_Sensors_io);
	i2c_m_sync_enable(&I2C_GPS_Sensors);
	i2c_m_sync_set_slaveaddr(&I2C_GPS_Sensors, 0x12, I2C_M_SEVEN);
	io_write(I2C_GPS_Sensors_io, (uint8_t *)"Hello World!", 12);
}

/**
 * Example of using SPI_Radio to write "Hello World" using the IO abstraction.
 */
static uint8_t example_SPI_Radio[12] = "Hello World!";

void SPI_Radio_example(void)
{
	struct io_descriptor *io;
	spi_m_sync_get_io_descriptor(&SPI_Radio, &io);

	spi_m_sync_enable(&SPI_Radio);
	io_write(io, example_SPI_Radio, 12);
}

/**
 * Example of using SPI_Flash_mem to write "Hello World" using the IO abstraction.
 */
static uint8_t example_SPI_Flash_mem[12] = "Hello World!";

void SPI_Flash_mem_example(void)
{
	struct io_descriptor *io;
	spi_m_sync_get_io_descriptor(&SPI_Flash_mem, &io);

	spi_m_sync_enable(&SPI_Flash_mem);
	io_write(io, example_SPI_Flash_mem, 12);
}
