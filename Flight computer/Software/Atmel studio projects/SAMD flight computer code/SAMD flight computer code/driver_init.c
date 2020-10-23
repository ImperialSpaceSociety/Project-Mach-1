/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include <hpl_gclk_base.h>
#include <hpl_pm_base.h>

struct spi_m_sync_descriptor SPI_Radio;
struct spi_m_sync_descriptor SPI_Flash_mem;

struct i2c_m_sync_desc I2C_breakout;

struct usart_sync_descriptor USART_GPS;

struct i2c_m_sync_desc I2C_GPS_Sensors;

void I2C_breakout_PORT_init(void)
{

	gpio_set_pin_pull_mode(PA08,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA08, PINMUX_PA08C_SERCOM0_PAD0);

	gpio_set_pin_pull_mode(PA09,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA09, PINMUX_PA09C_SERCOM0_PAD1);
}

void I2C_breakout_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM0);
	_gclk_enable_channel(SERCOM0_GCLK_ID_CORE, CONF_GCLK_SERCOM0_CORE_SRC);
	_gclk_enable_channel(SERCOM0_GCLK_ID_SLOW, CONF_GCLK_SERCOM0_SLOW_SRC);
}

void I2C_breakout_init(void)
{
	I2C_breakout_CLOCK_init();
	i2c_m_sync_init(&I2C_breakout, SERCOM0);
	I2C_breakout_PORT_init();
}

void USART_GPS_PORT_init(void)
{

	gpio_set_pin_function(PA16, PINMUX_PA16C_SERCOM1_PAD0);

	gpio_set_pin_function(PA17, PINMUX_PA17C_SERCOM1_PAD1);
}

void USART_GPS_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM1);
	_gclk_enable_channel(SERCOM1_GCLK_ID_CORE, CONF_GCLK_SERCOM1_CORE_SRC);
}

void USART_GPS_init(void)
{
	USART_GPS_CLOCK_init();
	usart_sync_init(&USART_GPS, SERCOM1, (void *)NULL);
	USART_GPS_PORT_init();
}

void I2C_GPS_Sensors_PORT_init(void)
{

	gpio_set_pin_pull_mode(PA22,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA22, PINMUX_PA22C_SERCOM3_PAD0);

	gpio_set_pin_pull_mode(PA23,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA23, PINMUX_PA23C_SERCOM3_PAD1);
}

void I2C_GPS_Sensors_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM3);
	_gclk_enable_channel(SERCOM3_GCLK_ID_CORE, CONF_GCLK_SERCOM3_CORE_SRC);
	_gclk_enable_channel(SERCOM3_GCLK_ID_SLOW, CONF_GCLK_SERCOM3_SLOW_SRC);
}

void I2C_GPS_Sensors_init(void)
{
	I2C_GPS_Sensors_CLOCK_init();
	i2c_m_sync_init(&I2C_GPS_Sensors, SERCOM3);
	I2C_GPS_Sensors_PORT_init();
}

void SPI_Radio_PORT_init(void)
{

	gpio_set_pin_level(PB12,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(PB12, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(PB12, PINMUX_PB12C_SERCOM4_PAD0);

	gpio_set_pin_level(PB13,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(PB13, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(PB13, PINMUX_PB13C_SERCOM4_PAD1);

	// Set pin direction to input
	gpio_set_pin_direction(PB14, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PB14,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PB14, PINMUX_PB14C_SERCOM4_PAD2);
}

void SPI_Radio_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM4);
	_gclk_enable_channel(SERCOM4_GCLK_ID_CORE, CONF_GCLK_SERCOM4_CORE_SRC);
}

void SPI_Radio_init(void)
{
	SPI_Radio_CLOCK_init();
	spi_m_sync_init(&SPI_Radio, SERCOM4);
	SPI_Radio_PORT_init();
}

void SPI_Flash_mem_PORT_init(void)
{

	gpio_set_pin_level(PB02,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(PB02, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(PB02, PINMUX_PB02D_SERCOM5_PAD0);

	gpio_set_pin_level(PB03,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(PB03, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(PB03, PINMUX_PB03D_SERCOM5_PAD1);

	// Set pin direction to input
	gpio_set_pin_direction(PB00, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PB00,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PB00, PINMUX_PB00D_SERCOM5_PAD2);
}

void SPI_Flash_mem_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM5);
	_gclk_enable_channel(SERCOM5_GCLK_ID_CORE, CONF_GCLK_SERCOM5_CORE_SRC);
}

void SPI_Flash_mem_init(void)
{
	SPI_Flash_mem_CLOCK_init();
	spi_m_sync_init(&SPI_Flash_mem, SERCOM5);
	SPI_Flash_mem_PORT_init();
}

void system_init(void)
{
	init_mcu();

	I2C_breakout_init();

	USART_GPS_init();

	I2C_GPS_Sensors_init();

	SPI_Radio_init();

	SPI_Flash_mem_init();
}
