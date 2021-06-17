/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _VARIANT_ROCKET_FLIGHT_COMPUTER_
#define _VARIANT_ROCKET_FLIGHT_COMPUTER_

// The definitions here needs a SAMD core >=1.6.10
#define ARDUINO_SAMD_VARIANT_COMPLIANCE 10610

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC		(32768ul)

/** Master clock frequency */
#define VARIANT_MCK	(F_CPU)

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
#include "SERCOM.h"
#include "Uart.h"
#endif // __cplusplus

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

// Number of pins defined in PinDescription array
#define PINS_COUNT           (45u)
#define NUM_DIGITAL_PINS     (42u)
#define NUM_ANALOG_INPUTS    (3u)
#define NUM_ANALOG_OUTPUTS   (0u)

#define digitalPinToPort(P)        ( &(PORT->Group[g_APinDescription[P].ulPort]) )
#define digitalPinToBitMask(P)     ( 1 << g_APinDescription[P].ulPin )
//#define analogInPinToBit(P)        ( )
#define portOutputRegister(port)   ( &(port->OUT.reg) )
#define portInputRegister(port)    ( &(port->IN.reg) )
#define portModeRegister(port)     ( &(port->DIR.reg) )
#define digitalPinHasPWM(P)        ( g_APinDescription[P].ulPWMChannel != NOT_ON_PWM || g_APinDescription[P].ulTCChannel != NOT_ON_TIMER )

/*
 * digitalPinToTimer(..) is AVR-specific and is not defined for SAMD
 * architecture. If you need to check if a pin supports PWM you must
 * use digitalPinHasPWM(..).
 *
 * https://github.com/arduino/Arduino/issues/1833
 */
// #define digitalPinToTimer(P)

// Interrupts
#define digitalPinToInterrupt(P)   ( g_APinDescription[P].ulExtInt )

// LEDs

#define PIN_LED_38			 (38u)
#define PIN_LED_39			 (39u)
#define PIN_LED_RED          PIN_LED_38
#define PIN_LED_BLUE         PIN_LED_39
#define LED_BUILTIN          PIN_LED_RED

/*
 * Analog pins
 */
#define PIN_A0               (42ul)
#define PIN_A1               (PIN_A0 + 1)
#define PIN_A2               (PIN_A0 + 2)



static const uint8_t A0  = PIN_A0 ;
static const uint8_t A1  = PIN_A1 ;
static const uint8_t A2  = PIN_A2 ;

#define ADC_RESOLUTION      12

/*
 * Serial interfaces
 */
// Serial
#define PIN_SERIAL_RX       (0ul)
#define PIN_SERIAL_TX       (1ul)
#define PAD_SERIAL_TX       (UART_TX_PAD_2)
#define PAD_SERIAL_RX       (SERCOM_RX_PAD_1)

// Serial1
#define PIN_SERIAL1_RX       (13ul)
#define PIN_SERIAL1_TX       (12ul)

#define PAD_SERIAL1_TX       (UART_TX_PAD_0)
#define PAD_SERIAL1_RX       (SERCOM_RX_PAD_1)


/*
 * SPI Interfaces
 */


#define SPI_INTERFACES_COUNT 2


// SPI Radio SPI
#define PIN_SPI_MISO         (34u) // pad 2
#define PIN_SPI_SS           (35u) // pad 3
#define PIN_SPI_MOSI         (32u) // pad 0
#define PIN_SPI_SCK          (33u) // pad 1

#define PERIPH_SPI           sercom4
#define PAD_SPI_TX           SPI_PAD_0_SCK_1
#define PAD_SPI_RX           SERCOM_RX_PAD_2





static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SS   = PIN_SPI_SS ;
static const uint8_t SS_RADIO  = PIN_SPI_SS ;
static const uint8_t MOSI = PIN_SPI_MOSI ;
static const uint8_t SCK  = PIN_SPI_SCK ;

// SPI1 Flash SPI
#define PIN_SPI1_MISO        (21u)
#define PIN_SPI1_SS          (22u)
#define PIN_SPI1_MOSI        (23u)
#define PIN_SPI1_SCK         (24u)

#define PERIPH_SPI1           sercom5
#define PAD_SPI1_TX          SPI_PAD_0_SCK_1
#define PAD_SPI1_RX          SERCOM_RX_PAD_2

static const uint8_t MISO1 = PIN_SPI1_MISO;
static const uint8_t SS1   = PIN_SPI1_SS;
static const uint8_t SS_FLASH  = PIN_SPI1_SS;
static const uint8_t MOSI1 = PIN_SPI1_MOSI;
static const uint8_t SCK1  = PIN_SPI1_SCK;

// Analog

static const uint8_t PIN_DAC0     = PIN_A0; // or (35u) implications for cores/arduino/wiring_analog.c analogWrite()

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 2

#define PIN_WIRE_SDA         (18u)
#define PIN_WIRE_SCL         (19u)

#define PERIPH_WIRE          sercom3
#define WIRE_IT_HANDLER      SERCOM3_Handler

#define PIN_WIRE1_SDA         (6u)
#define PIN_WIRE1_SCL         (7u)

#define PERIPH_WIRE1          sercom0
#define WIRE1_IT_HANDLER      SERCOM0_Handler

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

static const uint8_t SDA1 = PIN_WIRE1_SDA;
static const uint8_t SCL1 = PIN_WIRE1_SCL;
/*
 * USB
 */
#define PIN_USB_DM          (47ul)
#define PIN_USB_DP          (48ul)

#define PIN_USB_HOST_ENABLE (51ul) // pin is actually not connected to anything

/*
 * I2S Interfaces
 */
#define I2S_INTERFACES_COUNT 0

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus

/*  =========================
 *  ===== SERCOM DEFINITION
 *  =========================
*/
extern SERCOM sercom0;
extern SERCOM sercom1;
extern SERCOM sercom2;
extern SERCOM sercom3;
extern SERCOM sercom4;
extern SERCOM sercom5;

//extern Uart Serial;
extern Uart Serial1;

#endif

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_USBVIRTUAL      SerialUSB
#define SERIAL_PORT_MONITOR         SerialUSB

// Serial has no physical pins broken out, so it's not listed as HARDWARE port
#define SERIAL_PORT_HARDWARE        Serial
#define SERIAL_PORT_HARDWARE_OPEN   Serial



#endif /* _VARIANT_ROCKET_FLIGHT_COMPUTER */
