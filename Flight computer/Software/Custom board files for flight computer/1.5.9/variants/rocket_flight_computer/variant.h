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
#define PINS_COUNT           (49u)
#define NUM_DIGITAL_PINS     (16u)
#define NUM_ANALOG_INPUTS    (15u)
#define NUM_ANALOG_OUTPUTS   (1u)

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
#define PIN_LED_13           (13u)
#define PIN_LED              PIN_LED_13
#define LED_BUILTIN          PIN_LED_13

/*
 * Analog pins
 */
#define PIN_A0               (19ul)
#define PIN_A1               (PIN_A0 + 1)
#define PIN_A2               (PIN_A0 + 2)
#define PIN_A3               (PIN_A0 + 3)
#define PIN_A4               (PIN_A0 + 4)
#define PIN_A5               (PIN_A0 + 5)
#define PIN_A6               (PIN_A0 + 6)
#define PIN_A7               (PIN_A0 + 7)
#define PIN_A8               (PIN_A0 + 8)
#define PIN_A9               (PIN_A0 + 9)
#define PIN_A10              (PIN_A0 + 10)
#define PIN_A11              (PIN_A0 + 11)
#define PIN_A12              (PIN_A0 + 12)
#define PIN_A13              (PIN_A0 + 13)

static const uint8_t A0  = PIN_A0 ;
static const uint8_t A1  = PIN_A1 ;
static const uint8_t A2  = PIN_A2 ;
static const uint8_t A3  = PIN_A3 ;
static const uint8_t A4  = PIN_A4 ;
static const uint8_t A5  = PIN_A5 ;
static const uint8_t A6  = PIN_A6 ;
static const uint8_t A7  = PIN_A7 ;
static const uint8_t A8  = PIN_A8 ;
static const uint8_t A9  = PIN_A9 ;
static const uint8_t A10 = PIN_A10 ;
static const uint8_t A11 = PIN_A11 ;
static const uint8_t A12 = PIN_A12 ;
static const uint8_t A13 = PIN_A13 ;
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
#define PIN_SERIAL1_RX       (37ul)
#define PIN_SERIAL1_TX       (36ul)
#ifdef AUTONOMO_BETA
#define PAD_SERIAL1_TX       (UART_TX_PAD_0)
#else
#define PAD_SERIAL1_TX       (UART_TX_RTS_CTS_PAD_0_2_3)
#endif
#define PAD_SERIAL1_RX       (SERCOM_RX_PAD_1)

// Serial2
#define PIN_SERIAL2_RX       (49ul)
#define PIN_SERIAL2_TX       (50ul)
#define PAD_SERIAL2_TX       (UART_TX_PAD_2)
#define PAD_SERIAL2_RX       (SERCOM_RX_PAD_1)

// Serial3
#define PIN_SERIAL3_RX       (51ul)
#define PIN_SERIAL3_TX       (52ul)
#define PAD_SERIAL3_TX       (UART_TX_PAD_2)
#define PAD_SERIAL3_RX       (SERCOM_RX_PAD_1)

// Other Bee socket pins
// MCU_RTS <-> BEECTS
#ifdef AUTONOMO_BETA
static const uint8_t MCU_RTS = (39u);
static const uint8_t BEECTS = (39u);
#else
static const uint8_t MCU_RTS = (38u);
static const uint8_t BEECTS = (38u);
#endif

// MCU_CTS <-> BEERTS
#ifdef AUTONOMO_BETA
static const uint8_t MCU_CTS = (38u);
static const uint8_t BEERTS = (38u);
#else
static const uint8_t MCU_CTS = (39u);
static const uint8_t BEERTS = (39u);
#endif

static const uint8_t BEEDTR = PIN_A13;
static const uint8_t RI_AS = (18u);

/*
 * SPI Interfaces
 */

#ifdef ENABLE_SPI1
#define SPI_INTERFACES_COUNT 2
#else
#define SPI_INTERFACES_COUNT 1
#endif

// SPI
#define PIN_SPI_MISO         (61u)
#define PIN_SPI_SS           (62u)
#define PIN_SPI_MOSI         (63u)
#define PIN_SPI_SCK          (64u)

static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SS   = PIN_SPI_SS ;
static const uint8_t SS_DFLASH  = PIN_SPI_SS ;
static const uint8_t MOSI = PIN_SPI_MOSI ;
static const uint8_t SCK  = PIN_SPI_SCK ;

// SPI1
#define PIN_SPI1_MISO        (53u)
#define PIN_SPI1_SS          (54u)
#define PIN_SPI1_MOSI        (55u)
#define PIN_SPI1_SCK         (56u)

static const uint8_t MISO1 = PIN_SPI1_MISO;
static const uint8_t SS1   = PIN_SPI1_SS;
static const uint8_t MOSI1 = PIN_SPI1_MOSI;
static const uint8_t SCK1  = PIN_SPI1_SCK;

// SD Card CS/SS pin
static const uint8_t SS_2 = (46u);
static const uint8_t CS_SD = (46u);

// Other Digital Pins
static const uint8_t VCC_SW  = (16u);
static const uint8_t BEE_VCC = (17u);

// Other Analog Pins
static const uint8_t BAT_VOLT = (33u);
static const uint8_t AREF     = (34u);
static const uint8_t PIN_DAC0     = PIN_A0; // or (35u) implications for cores/arduino/wiring_analog.c analogWrite()

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 1

#define PIN_WIRE_SDA         (43u)
#define PIN_WIRE_SCL         (44u)

#define PERIPH_WIRE          sercom3
#define WIRE_IT_HANDLER      SERCOM3_Handler

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;


/*
 * USB
 */
#define PIN_USB_DM          (47ul)
#define PIN_USB_DP          (48ul)

#define PIN_USB_HOST_ENABLE (51ul) // pin is actually not connected to anything

/*
 * I2S Interfaces
 */
#define I2S_INTERFACES_COUNT 1

#define I2S_DEVICE          0
#define I2S_CLOCK_GENERATOR 3
#define PIN_I2S_SD          (14u)
#define PIN_I2S_SCK         (1u)
#define PIN_I2S_FS          (2u)

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
//extern Uart Serial1;
#ifdef ENABLE_SERIAL2
extern Uart Serial2;
#endif
#ifdef ENABLE_SERIAL3
extern Uart Serial3;
#endif

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


//#define PERIPH_WIRE          sercom2
//#define WIRE_IT_HANDLER      SERCOM2_Handler

#define PERIPH_SPI           sercom5
#define PAD_SPI_TX           SPI_PAD_0_SCK_1
#define PAD_SPI_RX           SERCOM_RX_PAD_2

#ifdef ENABLE_SPI1
#define PERIPH_SPI1          sercom4
#define PAD_SPI1_TX          SPI_PAD_2_SCK_3
#define PAD_SPI1_RX          SERCOM_RX_PAD_0
#endif

#endif /* _VARIANT_SODAQ_AUTONOMO */
