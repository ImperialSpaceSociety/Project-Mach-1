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
/*
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * + Pin number +  Autonomo pin    |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Digital Low      |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 */


#include "variant.h"

/*
 * Pins descriptions for SODAQ Autonomo
 *
 *  0..15 digital
 * 16..31 analog, A0..A15
 */
const PinDescription g_APinDescription[]=
{ 
  /*
  | PORT | PIN | PIN_TYPE    | PIN_ATTRIBUTES                                    | ADC_CHANNEL   | PWM_CHANNEL | TIMER_CHANNEL | EXT. INTERRUPT |
  */

  // 0..1 - SERCOM/UART (Serial)
  { PORTA, 9,  PIO_SERCOM,     PIN_ATTR_DIGITAL,                                       No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9  }, // RX, SERCOM0/PAD[1], D0
  { PORTA, 10, PIO_SERCOM,     PIN_ATTR_DIGITAL,                                       No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10 }, // TX, SERCOM0/PAD[2], D1

  // 2..15 Digital
  { PORTA, 11, PIO_TIMER,      (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER),     No_ADC_Channel, PWM1_CH1,   TCC1_CH1,     EXTERNAL_INT_11 }, // TCC1[1], D2
  { PORTB, 10, PIO_TIMER_ALT,  (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH4,   TCC0_CH4,     EXTERNAL_INT_10 }, // TCC0[4], D3
  { PORTB, 11, PIO_TIMER_ALT,  (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH5,   TCC0_CH5,     EXTERNAL_INT_11 }, // TCC0[5], D4
  { PORTB, 12, PIO_TIMER,      (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER),     No_ADC_Channel, PWM4_CH0,   TC4_CH0,      EXTERNAL_INT_12 }, // TC4[0], D5
  { PORTB, 13, PIO_TIMER,      (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER),     No_ADC_Channel, PWM4_CH1,   TC4_CH1,      EXTERNAL_INT_13 }, // TC4[1], D6
  { PORTB, 14, PIO_TIMER,      (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER),     No_ADC_Channel, PWM5_CH0,   TC5_CH0,      EXTERNAL_INT_14 }, // TC5[0], D7
  { PORTB, 15, PIO_TIMER,      (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER),     No_ADC_Channel, PWM5_CH1,   TC5_CH1,      EXTERNAL_INT_15 }, // TC5[1], D8
  { PORTA, 14, PIO_TIMER,      (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER),     No_ADC_Channel, PWM3_CH0,   TC3_CH0,      EXTERNAL_INT_14 }, // TC3[0], D9
  { PORTA, 15, PIO_TIMER,      (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER),     No_ADC_Channel, PWM3_CH1,   TC3_CH1,      EXTERNAL_INT_15 }, // TC3[1], D10
  { PORTA, 16, PIO_TIMER,      (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER),     No_ADC_Channel, PWM2_CH0,   TCC2_CH0,     EXTERNAL_INT_0  }, // TCC2[0], D11
  { PORTA, 17, PIO_TIMER,      (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER),     No_ADC_Channel, PWM2_CH1,   TCC2_CH1,     EXTERNAL_INT_1  }, // TCC2[1], D12
  { PORTA, 18, PIO_TIMER_ALT,  (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH2,   TCC0_CH2,     EXTERNAL_INT_2  }, // TCC0[2], D13
  { PORTA, 19, PIO_TIMER_ALT,  (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH3,   TCC0_CH3,     EXTERNAL_INT_3  }, // TCC0[3], D14
  {},
  // 16..18 Other Digital
  { PORTA, 8,  PIO_OUTPUT,     PIN_ATTR_DIGITAL,                                       No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // VCC_SW
  { PORTA, 28, PIO_OUTPUT,     PIN_ATTR_DIGITAL,                                       No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // BEE_VCC
  { PORTB, 17, PIO_INPUT,      PIN_ATTR_DIGITAL,                                       No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1    }, // RI/AS

  // 19..32 A0..A13
  { PORTA,  2, PIO_ANALOG,     PIN_ATTR_ANALOG,                                        ADC_Channel0,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2  }, // ADC/AIN[0], A0
  { PORTA,  6, PIO_ANALOG,     PIN_ATTR_ANALOG,                                        ADC_Channel6,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6  }, // ADC/AIN[6], A1
  { PORTA,  5, PIO_ANALOG,     PIN_ATTR_ANALOG,                                        ADC_Channel5,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5  }, // ADC/AIN[5], A2
  { PORTA,  4, PIO_ANALOG,     PIN_ATTR_ANALOG,                                        ADC_Channel4,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_4  }, // ADC/AIN[4], A3
  { PORTB,  9, PIO_ANALOG,     PIN_ATTR_ANALOG,                                        ADC_Channel3,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9  }, // ADC/AIN[3], A4
  { PORTB,  8, PIO_ANALOG,     PIN_ATTR_ANALOG,                                        ADC_Channel2,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_8  }, // ADC/AIN[2], A5
  {},
  {},
  {},
  {},
  { PORTA,  7, PIO_ANALOG,     PIN_ATTR_ANALOG,                                        ADC_Channel7,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7  }, // ADC/AIN[7],  A10
  {}, // ADC/AIN[11], A11
  {}, // ADC/AIN[10], A12
  {},
  
  // 33-35 Other Analog + DAC
  {},
  { PORTA,  3, PIO_ANALOG,     PIN_ATTR_ANALOG,                                       No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE  }, // ADC/AIN[1], AREF
  { PORTA,  2, PIO_ANALOG,     PIN_ATTR_ANALOG,                                       DAC_Channel0,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2     }, // DAC

  // 36..39 - SERCOM/UART (Serial1)
  { PORTB, 30, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL,                                      No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_14 }, // TX: SERCOM5/PAD[0]
  { PORTB, 31, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL,                                      No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15 }, // RX: SERCOM5/PAD[1]
  { PORTB, 22, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL,                                      No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6  }, // RTS: SERCOM5/PAD[2]
  { PORTB, 23, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL,                                      No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7  }, // CTS: SERCOM5/PAD[3]

  // 40..41 - I2C pins (SDA/SCL)
  { PORTA, 12, PIO_SERCOM,     PIN_ATTR_DIGITAL,                                      No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_12 }, // SDA: SERCOM2/PAD[0]
  { PORTA, 13, PIO_SERCOM,     PIN_ATTR_DIGITAL,                                      No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_13 }, // SCL: SERCOM2/PAD[1]

  // 42..45 - SPI pins (ICSP: MISO, SS, MOSI, SCK)
  {},
  
  //i2c
  { PORTA, 22, PIO_SERCOM,     PIN_ATTR_DIGITAL,                                      No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_12 }, // SDA: SERCOM3/PAD[0]
  { PORTA, 23, PIO_SERCOM,     PIN_ATTR_DIGITAL,                                      No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_13 }, // SCL: SERCOM3/PAD[1]
  
  {},

  // 46 - SD CARD CS
  { PORTA, 27, PIO_OUTPUT,     PIN_ATTR_DIGITAL,                                      No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // SS_2 (CS for SD)
    
  // 47..48 - USB
  { PORTA, 24, PIO_COM,        PIN_ATTR_NONE,                                         No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB/DM
  { PORTA, 25, PIO_COM,        PIN_ATTR_NONE,                                         No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB/DP

  // 49..50 - Serial2 (alternative use for D6/D7)
  { PORTB, 13, PIO_SERCOM,     PIN_ATTR_DIGITAL,                                      No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_13 }, // RX, SERCOM4/PAD[1]
  { PORTB, 14, PIO_SERCOM,     PIN_ATTR_DIGITAL,                                      No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_14 }, // TX, SERCOM4/PAD[2]

  // 51..52 - Serial3 (alternative use for D12/D13)
  { PORTA, 17, PIO_SERCOM,     PIN_ATTR_DIGITAL,                                      No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1  }, // RX, SERCOM1/PAD[1]
  { PORTA, 18, PIO_SERCOM,     PIN_ATTR_DIGITAL,                                      No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2  }, // TX, SERCOM1/PAD[2]

  // 53..56 - SPI flash (alternative use for D5..D8)
  {}, // MISO1: SERCOM4/PAD[0]
  {}, // SS1: SERCOM4/PAD[1]},
  {}, // MOSI1: SERCOM4/PAD[2]
  {}, // SCK1: SERCOM4/PAD[3]

  // 57..60
  {},
  {},
  {},
  {},

  // 61..64
  { PORTB, 0, PIO_SERCOM,     PIN_ATTR_DIGITAL,                                      No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_0 }, // MISO1: SERCOM5/PAD[2]
  { PORTB, 1, PIO_SERCOM,     PIN_ATTR_DIGITAL,                                      No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1 }, // SS1: SERCOM5/PAD[1]},
  { PORTB, 2, PIO_SERCOM,     PIN_ATTR_DIGITAL,                                      No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 }, // MOSI1: SERCOM5/PAD[2]
  { PORTB, 3, PIO_SERCOM,     PIN_ATTR_DIGITAL,                                      No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3 }, // SCK1: SERCOM5/PAD[3]
};


const void* g_apTCInstances[]={ TCC0, TCC1, TCC2, TC3, TC4, TC5} ;

// Multi-serial objects instantiation
SERCOM sercom0( SERCOM0 ) ;	//
SERCOM sercom1( SERCOM1 ) ;	// 
SERCOM sercom2( SERCOM2 ) ;	// 
SERCOM sercom3( SERCOM3 ) ;	// I2C
SERCOM sercom4( SERCOM4 ) ;	//
SERCOM sercom5( SERCOM5 ) ;	// SPI

//Uart Serial( &sercom0, PIN_SERIAL_RX, PIN_SERIAL_TX, PAD_SERIAL_RX, PAD_SERIAL_TX );

//void SERCOM0_Handler()
//{
//  Serial.IrqHandler();
//}

Uart Serial1( &sercom5, PIN_SERIAL1_RX, PIN_SERIAL1_TX, PAD_SERIAL1_RX, PAD_SERIAL1_TX ) ;
void SERCOM5_Handler()
{
  Serial1.IrqHandler();
}

#ifdef ENABLE_SERIAL2
Uart Serial2( &sercom4, PIN_SERIAL2_RX, PIN_SERIAL2_TX, PAD_SERIAL2_RX, PAD_SERIAL2_TX );
void SERCOM4_Handler()
{
  Serial2.IrqHandler();
}
#endif

#ifdef ENABLE_SERIAL3
Uart Serial3( &sercom1, PIN_SERIAL3_RX, PIN_SERIAL3_TX, PAD_SERIAL3_RX, PAD_SERIAL3_TX );
void SERCOM1_Handler()
{
  Serial3.IrqHandler();
}
#endif
