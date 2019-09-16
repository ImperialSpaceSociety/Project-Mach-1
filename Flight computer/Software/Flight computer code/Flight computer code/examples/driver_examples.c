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

/**
 * Example of using SPI_RADIO to write "Hello World" using the IO abstraction.
 */
static uint8_t example_SPI_RADIO[12] = "Hello World!";

void SPI_RADIO_example(void)
{
	struct io_descriptor *io;
	spi_m_sync_get_io_descriptor(&SPI_RADIO, &io);

	spi_m_sync_enable(&SPI_RADIO);
	io_write(io, example_SPI_RADIO, 12);
}

/**
 * Example of using USART_0 to write "Hello World" using the IO abstraction.
 */
void USART_0_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART_0, &io);
	usart_sync_enable(&USART_0);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

void I2C_0_example(void)
{
	struct io_descriptor *I2C_0_io;

	i2c_m_sync_get_io_descriptor(&I2C_0, &I2C_0_io);
	i2c_m_sync_enable(&I2C_0);
	i2c_m_sync_set_slaveaddr(&I2C_0, 0x12, I2C_M_SEVEN);
	io_write(I2C_0_io, (uint8_t *)"Hello World!", 12);
}

/**
 * Example of using SPI_FLASH_CHIP to write "Hello World" using the IO abstraction.
 */
static uint8_t example_SPI_FLASH_CHIP[12] = "Hello World!";

void SPI_FLASH_CHIP_example(void)
{
	struct io_descriptor *io;
	spi_m_sync_get_io_descriptor(&SPI_FLASH_CHIP, &io);

	spi_m_sync_enable(&SPI_FLASH_CHIP);
	io_write(io, example_SPI_FLASH_CHIP, 12);
}
