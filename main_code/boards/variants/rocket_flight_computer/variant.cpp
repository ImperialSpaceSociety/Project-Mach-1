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
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * + Pin number | Flight Computer Pin | Processor Pin |Alternative Name | Comments (* is for default peripheral in use)
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |        0   |      Buzzer         |      PA00     |        D0       |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |        1   |  GPS_NSafeboot      |      PA01     |        D1       |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |        2   |     GPS_1PPS        |      PA02     |        D2       |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |        3   |    GPS_NRESET       |      PA03     |        D3       |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |        4   |       Unused        |      PA06     |        D4       |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |        5   |       Unused        |      PA07     |        D5       |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |        6   |  I2C_Grove_SDA      |      PA08     |        D6       | Sercom0  Wire1
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |        7   |  I2C_Grove_SCL      |      PA09     |        D7       | Sercom0  Wire1
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |        8   |       FIRE_A        |      PA10     |        D8       |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |        9   |       FIRE_B        |      PA11     |        D9       |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       10   |      RF_GPIO1       |      PA12     |        D10      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       11   |      RF_GPIO0       |      PA13     |        D11      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       12   |      GPS_TXD        |      PA16     |        D12      | Sercom1  Serial1
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       13   |      GPS_RXD        |      PA17     |        D13      | Sercom1  Serial1
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       14   |     GYRO_RDY        |      PA18     |        D14      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       15   |     ACCL_RDY        |      PA19     |        D15      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       16   |    ACCL_INT1        |      PA20     |        D16      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       17   |    ACCL_INT2        |      PA21     |        D17      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       18   |  Onboard_I2C_SDA    |      PA22     |        D18      | Sercom3  Wire
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       19   |  Onboard_I2C_SCL    |      PA23     |        D19      | Sercom3  Wire
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       20   |        Unused       |      PA27     |        D20      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       21   |   Flash_SPI_MISO    |      PB00     |        D21      | Sercom5/PAD[2]  SPI1
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       22   |   Flash_SPI_NSEL    |      PB01     |        D22      | Sercom5/PAD[3]  SPI1
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       23   |   Flash_SPI_MOSI    |      PB02     |        D23      | Sercom5/PAD[0]  SPI1
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       24   |   Flash_SPI_SCLK    |      PB03     |        D24      | Sercom5/PAD[1]  SPI1
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       25   |       Unused        |      PA04     |        D25      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       26   |       Unused        |      PB05     |        D26      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       27   |       Unused        |      PB06     |        D27      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       28   |       Unused        |      PB07     |        D28      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       29   |       Unused        |      PB09     |        D29      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       30   |      RF_NIRQ        |      PB10     |        D30      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       31   |      RF_SDN         |      PB11     |        D31      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       32   |   RF_SPI_MOSI       |      PB12     |        D32      | Sercom4/PAD[0]  SPI
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       33   |   RF_SPI_SCLK       |      PB13     |        D33      | Sercom4/PAD[1]  SPI
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       34   |   RF_SPI_MISO       |      PB14     |        D34      | Sercom4/PAD[2]  SPI
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       35   |   RF_SPI_NSEL       |      PB15     |        D35      | Sercom4/PAD[3]  SPI
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       36   |       Unused        |      PB16     |        D36      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       37   |       MAG_RDY       |      PB17     |        D37      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       38   |       LED_RED       |      PB22     |        D38      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       39   |       LED_BLUE      |      PB23     |        D39      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       40   |       Unused        |      PB16     |        D40      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       41   |       Unused        |      PB16     |        D41      |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       42   |      SENSE_A        |      PA08     |        A0       |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       43   |      SENSE_B        |      PA09     |        A1       |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------
 * |       44   |     PWR_BVOLTS      |      PB08     |        A2       |
 * +------------+---------------------+---------------+-----------------+--------------------------------------------------------------------------------------------------------


 */

#include "variant.h"

/*
 * Pins descriptions for SODAQ Autonomo
 *
 *  0..41 digital
 * 42..44 analog, A0..A2
 */
const PinDescription g_APinDescription[] =
    {
        /*
        | PORT | PIN | PIN_TYPE      | PIN_ATTRIBUTES                                       |ADC_CHANNEL  |PWM_CHANNEL |TIMER_CHANNEL |EXT. INTERRUPT |
        */
        // 0..5 Digital
        {PORTA, 0, PIO_OUTPUT, (PIN_ATTR_DIGITAL | PIN_ATTR_PWM), No_ADC_Channel, PWM2_CH0, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // Buzzer, D0
        {PORTA, 1, PIO_OUTPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},                // GPS_NSafeboot, D1
        {PORTA, 2, PIO_INPUT, (PIN_ATTR_DIGITAL | PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TCC2_CH0, EXTERNAL_INT_NONE},  // GPS 1PPS, D2
        {PORTA, 3, PIO_OUTPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},                // GPS_NReset, D3
        {PORTA, 6, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},                 // Unused, D4
        {PORTA, 7, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},                 // Unused, D5

        // 6..7 - SERCOM0/I2C (Wire1) Grove I2C Port

        {PORTA, 8, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // I2C Sercom0/PAD[0] SDA, D6
        {PORTA, 9, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // I2C Sercom0/PAD[1] SCL, D7

        // 8..11 Digital

        {PORTA, 10, PIO_OUTPUT, (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER), No_ADC_Channel, PWM0_CH1, TCC0_CH1, EXTERNAL_INT_NONE}, // FIRE_A, D8
        {PORTA, 11, PIO_OUTPUT, (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER), No_ADC_Channel, PWM1_CH0, TCC1_CH0, EXTERNAL_INT_NONE}, // FIRE_B, D9
        {PORTA, 12, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_12},                                // RF_GPIO1, D10
        {PORTA, 13, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_13},                                // RF_GPIO0, D11

        // 12..13 - SERCOM1/UART (Serial1) GPS UART
        {PORTA, 16, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // GPS_TXD, SERCOM1/PAD[0], D12
        {PORTA, 17, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // GPS_RXD, SERCOM1/PAD[1], D13

        // 14..17 Digital

        {PORTA, 18, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2}, // GYRO_RDY, D14
        {PORTA, 19, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3}, // ACCEL_RDY, D15
        {PORTA, 20, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_4}, // ACCEL_INT1, D16
        {PORTA, 21, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5}, // ACCEL_INT2, D17

        // 18..19 - SERCOM3/I2C (Wire) Onboard I2C Port

        {PORTA, 22, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // I2C Sercom3/PAD[0] SDA, D18
        {PORTA, 23, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // I2C Sercom3/PAD[1} SCL, D19

        // 20..20 Digital

        {PORTA, 27, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // Unused, D20

        // 21..24 - SERCOM5/SPI (SPI1) Flash Memory SPI

        {PORTB, 0, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // Flash MISO1: SERCOM5/PAD[2], D21
        {PORTB, 1, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // Flash SS1: SERCOM5/PAD[3]}, D22
        {PORTB, 2, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // Flash MOSI1: SERCOM5/PAD[0], D23
        {PORTB, 3, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // Flash SCK1: SERCOM5/PAD[1], D24

        // 25..31 Digital

        {PORTB, 4, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},   // Unused, D25
        {PORTB, 5, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},   // Unused, D26
        {PORTB, 6, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},   // Unused, D27
        {PORTB, 7, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},   // Unused, D28
        {PORTB, 9, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},   // Unused, D29
        {PORTB, 10, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10},    // RF_NIRQ, D30
        {PORTB, 11, PIO_OUTPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // RF_SDN, D31

        // 32..35 - SERCOM4/SPI (SPI) Radio RF SPI

        {PORTB, 12, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // RF MOSI: SERCOM4/PAD[0], D32
        {PORTB, 13, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // RF SS1: SERCOM4/PAD[1]}, D33
        {PORTB, 14, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // RF MOSI: SERCOM4/PAD[2], D34
        {PORTB, 15, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // RF SCK: SERCOM4/PAD[3], D35

        // 36..39 Digital

        {PORTB, 16, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},  // Unused, D36
        {PORTB, 17, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1},     // MAG_RDY, D37
        {PORTB, 22, PIO_OUTPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // LED RED, D38
        {PORTB, 23, PIO_OUTPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // LED BLUE, D39
        {PORTB, 30, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},  // Unused, D40
        {PORTB, 31, PIO_INPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},  // Unused, D41

        // 42..44 A0..A2
        {PORTA, 4, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel4, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // SENSE_A, D42, A0
        {PORTA, 5, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel5, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // SENSE_B, D43, A1
        {PORTB, 8, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel2, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // SENSE_C, D44, A2
};

const void *g_apTCInstances[] = {TCC0, TCC1, TCC2, TC3, TC4, TC5};

// Multi-serial objects instantiation
SERCOM sercom0(SERCOM0); // I2C Grove
SERCOM sercom1(SERCOM1); // GPS Serial
SERCOM sercom2(SERCOM2); // Unused
SERCOM sercom3(SERCOM3); // I2C onboard
SERCOM sercom4(SERCOM4); // Radio SPI
SERCOM sercom5(SERCOM5); // Flash SPI

Uart Serial1(&sercom1, PIN_SERIAL1_RX, PIN_SERIAL1_TX, PAD_SERIAL1_RX, PAD_SERIAL1_TX);
void SERCOM1_Handler()
{
  Serial1.IrqHandler();
}

// ADD
Uart Serial2(&sercom2, PIN_SERIAL2_RX, PIN_SERIAL2_TX, PAD_SERIAL2_RX, PAD_SERIAL2_TX);
void SERCOM2_Handler()
{
  Serial2.IrqHandler();
}
