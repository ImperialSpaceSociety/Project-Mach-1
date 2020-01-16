/**
 * \file
 *
 * \brief Application implement
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "atmel_start.h"
#include "atmel_start_pins.h"
#include <stdio.h>


#if CONF_USBD_HS_SP
static uint8_t single_desc_bytes[] = {
	/* Device descriptors and Configuration descriptors list. */
CDCD_ACM_HS_DESCES_LS_FS};
static uint8_t single_desc_bytes_hs[] = {
	/* Device descriptors and Configuration descriptors list. */
CDCD_ACM_HS_DESCES_HS};
#define CDCD_ECHO_BUF_SIZ CONF_USB_CDCD_ACM_DATA_BULKIN_MAXPKSZ_HS
#else
static uint8_t single_desc_bytes[] = {
	/* Device descriptors and Configuration descriptors list. */
CDCD_ACM_DESCES_LS_FS};
#define CDCD_ECHO_BUF_SIZ CONF_USB_CDCD_ACM_DATA_BULKIN_MAXPKSZ
#endif

static struct usbd_descriptors single_desc[]
= {{single_desc_bytes, single_desc_bytes + sizeof(single_desc_bytes)}
#if CONF_USBD_HS_SP
,
{single_desc_bytes_hs, single_desc_bytes_hs + sizeof(single_desc_bytes_hs)}
#endif
};

volatile bool usb_connected = false;
volatile bool usb_out_busy = false;
uint32_t bus_number = 0;

/** Buffers to receive and echo the communication bytes. */
static char From_USB_buffer[CDCD_ECHO_BUF_SIZ];
static char To_USB_buffer[CDCD_ECHO_BUF_SIZ];


/** Ctrl endpoint buffer */
static uint8_t ctrl_buffer[64];


/**
 * \brief Callback invoked when bulk IN data received
 */
static bool usb_device_cb_bulk_in(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count)
{
	usb_out_busy = false;
	
	/* No error. */
	return false;
}

/**
 * \brief Callback invoked when bulk OUT data received
 */
static bool usb_device_cb_bulk_out(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count)
{
	
	

	/* No error. */
	return false;
}
/**
 * \brief Callback invoked when Line State Change
 */
static bool usb_device_cb_state_c(usb_cdc_control_signal_t state)
{
	if (state.rs232.DTR) {
		/* Callbacks must be registered after endpoint allocation */
		cdcdf_acm_register_callback(CDCDF_ACM_CB_READ, (FUNC_PTR)usb_device_cb_bulk_out);
		cdcdf_acm_register_callback(CDCDF_ACM_CB_WRITE, (FUNC_PTR)usb_device_cb_bulk_in);	
		cdcdf_acm_read((uint8_t *)From_USB_buffer, sizeof(From_USB_buffer));
		usb_connected = true;
	}

	/* No error. */
	return false;
}

static void tx_cb_USART_0(const struct usart_async_descriptor *const io_descr)
{
	/* USART_0_ Transmit completed */
	
}

static void rx_cb_USART_0(const struct usart_async_descriptor *const io_descr)
{
	/* USART_0 character received */
	
}


int main(void)
{
	
	uint32_t error=0;
	uint8_t address, nDevices;
	struct _i2c_m_msg       msg;
	uint8_t I2C_buffer[16];
	
	atmel_start_init();
	
	// Setup USART
		struct io_descriptor *gpsio;
		
		usart_async_register_callback(&USART_0, USART_ASYNC_TXC_CB, tx_cb_USART_0);
		usart_async_register_callback(&USART_0, USART_ASYNC_RXC_CB, rx_cb_USART_0);
		/*usart_async_register_callback(&USART_0, USART_ASYNC_ERROR_CB, err_cb_USART_0);*/
		usart_async_get_io_descriptor(&USART_0, &gpsio);
		//usart_async_enable(&USART_0);
		
	// Setup internal I2C Bus
	
		i2c_m_sync_set_baudrate(&I2C_0,0,100000);
		i2c_m_sync_enable(&I2C_0);
		
	// Setup external I2C Bus
		
		i2c_m_sync_set_baudrate(&I2C_1,0,100000);
		i2c_m_sync_enable(&I2C_1);
		
	// Setup radio SPI Bus
		struct io_descriptor *radioio;
		spi_m_sync_get_io_descriptor(&SPI_1, &radioio);
		spi_m_sync_enable(&SPI_1);
		gpio_set_pin_level(RF_NSEL,true);  // radio not selected
		gpio_set_pin_level(RF_SHTDN,true); // radio in shutdown state

	
	// Setup memory SPI Bus
	
		struct io_descriptor *memio;
		spi_m_sync_get_io_descriptor(&SPI_0, &memio);
		spi_m_sync_enable(&SPI_0);
		gpio_set_pin_level(MEM_NSEL,true); // memory not selected
		
		
	// Start USB
	/* usb stack init */
	
		usbdc_init(ctrl_buffer);

		/* usbdc_register_funcion inside */
		cdcdf_acm_init();

		usbdc_start(single_desc);
		usbdc_attach();
		
	// Wait until USB enabled
		while (!cdcdf_acm_is_enabled()) {
			// wait cdc acm to be installed
		};

		cdcdf_acm_register_callback(CDCDF_ACM_CB_STATE_C, (FUNC_PTR)usb_device_cb_state_c);
		
	// Wait for USB to connect
	
		while(!usb_connected);
		
		sprintf(To_USB_buffer, "\r\nFlight Computer Bus Scanner\r\n");
		usb_out_busy=true;
		cdcdf_acm_write((uint8_t *)To_USB_buffer, strlen(To_USB_buffer));	
		
	
	while (1) {
		while(usb_out_busy);
		if (bus_number == 0)
		sprintf(To_USB_buffer, "Scanning Internal I2C Bus...");	
		else if (bus_number == 1)
		sprintf(To_USB_buffer, "Scanning External I2C Bus...");	
		else if (bus_number == 2)
		sprintf(To_USB_buffer, "Checking Radio SPI Bus...");
		else if (bus_number == 3)
		sprintf(To_USB_buffer, "Checking Memory SPI Bus...");
		else
		sprintf(To_USB_buffer, "Checking Battery Voltage...");
		usb_out_busy=true;	
		cdcdf_acm_write((uint8_t *)To_USB_buffer, strlen(To_USB_buffer));
		
		if(bus_number < 2){
			nDevices = 0;
			for(address = 1; address < 127; address++ )
			{
			
				msg.addr   = address;
				msg.len    = 01;
				msg.flags  = I2C_M_SEVEN;
				msg.buffer = I2C_buffer;
				if(bus_number == 0){
				error = i2c_m_sync_transfer(&I2C_0, &msg);
				i2c_m_sync_send_stop(&I2C_0);
				}
				else{
				error = i2c_m_sync_transfer(&I2C_1, &msg);
				i2c_m_sync_send_stop(&I2C_1);	
				}
			
				if (error == 0)
				{
					while(usb_out_busy);
					sprintf(To_USB_buffer,"\r\nI2C device found at address 0x0%x!", address);
					usb_out_busy=true;		
					cdcdf_acm_write((uint8_t *)To_USB_buffer, strlen(To_USB_buffer));			
					nDevices++;
				}
				else if(error != -2)
				{
					while(usb_out_busy);
					sprintf(To_USB_buffer,"\r\nI2C error found at address 0x0%x, error=%d !", address, (int) error);
					usb_out_busy=true;		
					cdcdf_acm_write((uint8_t *)To_USB_buffer, strlen(To_USB_buffer));			
					nDevices++;
				}
				delay_ms(20);
			
			}
			if (nDevices == 0){
			while(usb_out_busy);	
			sprintf(To_USB_buffer,"\r\nNo I2C devices found\r\n");
			usb_out_busy=true;		
			cdcdf_acm_write((uint8_t *)To_USB_buffer, strlen(To_USB_buffer));
			}
			else{
			while(usb_out_busy);		
			sprintf(To_USB_buffer, "\r\ndone\r\n");
			usb_out_busy=true;		
			cdcdf_acm_write((uint8_t *)To_USB_buffer, strlen(To_USB_buffer));
			}
		}
		if(bus_number == 2){
			gpio_set_pin_level(RF_NSEL,false);  // radio selected
			gpio_set_pin_level(RF_SHTDN,false); // radio out of shutdown state
			
			// need to add test code here
			while(usb_out_busy);
			sprintf(To_USB_buffer, "\r\n Radio done\r\n");
			usb_out_busy=true;
			cdcdf_acm_write((uint8_t *)To_USB_buffer, strlen(To_USB_buffer));	
			
			gpio_set_pin_level(RF_NSEL,true);  // radio not selected
			gpio_set_pin_level(RF_SHTDN,true); // radio in shutdown state
		}
		
		if(bus_number == 3){
			gpio_set_pin_level(MEM_NSEL,false); // memory selected
			// need to add test code here
			
			while(usb_out_busy);
			sprintf(To_USB_buffer, "\r\n Memory done\r\n");
			usb_out_busy=true;
			cdcdf_acm_write((uint8_t *)To_USB_buffer, strlen(To_USB_buffer));	
			
			gpio_set_pin_level(MEM_NSEL,true); // memory not selected
		}
		if(bus_number == 4){
			
			// need to add test code here
			while(usb_out_busy);
			sprintf(To_USB_buffer, "\r\n Battery Voltage done\r\n");
			usb_out_busy=true;
			cdcdf_acm_write((uint8_t *)To_USB_buffer, strlen(To_USB_buffer));
		}
		
		if(++bus_number == 2) bus_number = 0;
		
	}
}
