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



/** Buffers to receive and echo the communication bytes. */
static uint8_t From_GPS_buffer[CDCD_ECHO_BUF_SIZ];
static uint8_t To_GPS_buffer[CDCD_ECHO_BUF_SIZ];

/* USB Connect Status */

volatile bool USB_CDC_Connected = false;

/* USART Flags */

volatile bool USART_0__data_rx = false;

/* USB Flags */

volatile bool USB_CDC_data_rx = false;

/* Buffer Management Locks */

volatile bool From_GPS_buffer_Lock = false;
volatile bool To_GPS_buffer_Lock = false;
volatile bool USB_Out_Lock = false;
volatile bool USART_0_Out_Lock = false;


/** Ctrl endpoint buffer */
static uint8_t ctrl_buffer[64];


/**
 * \brief Callback invoked when bulk IN data received
 */
static bool usb_device_cb_bulk_in(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count)
{
	USB_Out_Lock = false;
	
	/* No error. */
	return false;
}

/**
 * \brief Callback invoked when bulk OUT data received
 */
static bool usb_device_cb_bulk_out(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count)
{
	
	USB_CDC_data_rx = true;

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
		/* Start Rx */
		cdcdf_acm_read((uint8_t *)To_GPS_buffer, sizeof(To_GPS_buffer));
		USB_CDC_Connected = true;
	}
	else
		USB_CDC_Connected = false;

	/* No error. */
	return false;
}

static void tx_cb_USART_0(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
	USART_0_Out_Lock = false;
	
}

static void rx_cb_USART_0(const struct usart_async_descriptor *const io_descr)
{
	/* USART_0 character received */
	
	USART_0__data_rx = true;
	
}

static void blocking_USB_CDC_send(uint8_t * buffer, uint8_t bcount){
	while(USB_Out_Lock);
	USB_Out_Lock = true;
	cdcdf_acm_write((uint8_t *)From_GPS_buffer, bcount);
	
}



int main(void)
{
	uint8_t rx_char_count, count;
	
	atmel_start_init();
	
	// Setup USART
		struct io_descriptor *gpsio;
		
		usart_async_register_callback(&USART_0, USART_ASYNC_TXC_CB, tx_cb_USART_0);
		usart_async_register_callback(&USART_0, USART_ASYNC_RXC_CB, rx_cb_USART_0);
		/*usart_async_register_callback(&USART_0, USART_ASYNC_ERROR_CB, err_cb_USART_0);*/
		usart_async_get_io_descriptor(&USART_0, &gpsio);
		usart_async_enable(&USART_0);

		
		
		
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
		
	

	
	while (1) {
		if(USB_CDC_Connected){
			if(USART_0__data_rx){
				rx_char_count = io_read(gpsio,(uint8_t *)From_GPS_buffer, sizeof(From_GPS_buffer));
				blocking_USB_CDC_send(From_GPS_buffer, rx_char_count);
				USART_0__data_rx = false;
			}
			
			if(USB_CDC_data_rx){
				count = sizeof(To_GPS_buffer);
				cdcdf_acm_read((uint8_t *)To_GPS_buffer, count);
				io_write(gpsio,(uint8_t *)To_GPS_buffer, count);
				USB_CDC_data_rx = false;
			}
			
		}
	}
}
