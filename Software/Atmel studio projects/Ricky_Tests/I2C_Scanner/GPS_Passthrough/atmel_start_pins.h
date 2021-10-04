/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAMD21 has 8 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7

#define BUZZER GPIO(GPIO_PORTA, 0)
#define GPS_SAFEBOOT GPIO(GPIO_PORTA, 1)
#define GPS_PPS GPIO(GPIO_PORTA, 2)
#define GPS_RES GPIO(GPIO_PORTA, 3)
#define SENSE_A GPIO(GPIO_PORTA, 4)
#define PA05 GPIO(GPIO_PORTA, 5)
#define PA08 GPIO(GPIO_PORTA, 8)
#define PA09 GPIO(GPIO_PORTA, 9)
#define FIRE_A GPIO(GPIO_PORTA, 10)
#define FIRE_B GPIO(GPIO_PORTA, 11)
#define RF_GPIO1 GPIO(GPIO_PORTA, 12)
#define RF_GPIO0 GPIO(GPIO_PORTA, 13)
#define PA16 GPIO(GPIO_PORTA, 16)
#define PA17 GPIO(GPIO_PORTA, 17)
#define GYRO_RDY GPIO(GPIO_PORTA, 18)
#define ACCL_RDY GPIO(GPIO_PORTA, 19)
#define HACC_INT2 GPIO(GPIO_PORTA, 20)
#define HACC_INT1 GPIO(GPIO_PORTA, 21)
#define PA22 GPIO(GPIO_PORTA, 22)
#define PA23 GPIO(GPIO_PORTA, 23)
#define USB_DM GPIO(GPIO_PORTA, 24)
#define USB_DP GPIO(GPIO_PORTA, 25)
#define PB00 GPIO(GPIO_PORTB, 0)
#define MEM_NSEL GPIO(GPIO_PORTB, 1)
#define PB02 GPIO(GPIO_PORTB, 2)
#define PB03 GPIO(GPIO_PORTB, 3)
#define PWR_BVOLTS GPIO(GPIO_PORTB, 8)
#define RF_NIRQ GPIO(GPIO_PORTB, 10)
#define RF_SHTDN GPIO(GPIO_PORTB, 11)
#define PB12 GPIO(GPIO_PORTB, 12)
#define PB13 GPIO(GPIO_PORTB, 13)
#define PB14 GPIO(GPIO_PORTB, 14)
#define RF_NSEL GPIO(GPIO_PORTB, 15)
#define MAG_RDY GPIO(GPIO_PORTB, 17)
#define LED_RED GPIO(GPIO_PORTB, 22)
#define LED_BLUE GPIO(GPIO_PORTB, 23)

#endif // ATMEL_START_PINS_H_INCLUDED
