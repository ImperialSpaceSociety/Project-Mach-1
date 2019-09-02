EESchema Schematic File Version 4
LIBS:circuit board design-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 7
Title "flight computer for rocket"
Date "2019-08-19"
Rev "1.1"
Comp "Imperial College Space Society"
Comment1 "Based on the Picotracker MK II"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 7900 3000 2350 1600
U 5D5B1586
F0 "sensors" 50
F1 "sensors.sch" 50
F2 "SENS_SDA" B L 7900 3550 50 
F3 "SENS_SCL" B L 7900 3700 50 
F4 "ACCL_RDY" I L 7900 3900 50 
F5 "GYRO_RDY" I L 7900 4050 50 
$EndSheet
$Sheet
S 2700 5700 2350 1200
U 5D5B1705
F0 "power_supply" 50
F1 "power_supply.sch" 50
F2 "PWR_BVOLTS" O L 2700 6050 50 
F3 "PWR_MEASURE" I L 2700 5900 50 
$EndSheet
$Sheet
S 7900 1150 2350 1550
U 5D5B165E
F0 "gps" 50
F1 "GPS.sch" 50
F2 "GPS_SCL" B L 7900 1900 50 
F3 "GPS_SDA" B L 7900 1750 50 
F4 "GPS_TXD" O L 7900 1300 50 
F5 "GPS_RXD" I L 7900 1450 50 
F6 "GPS_NSAFEBOOT" I L 7900 2050 50 
F7 "GPS_NRES" I L 7900 1600 50 
F8 "GPS_1PPS" O L 7900 2200 50 
$EndSheet
Wire Wire Line
	7900 3550 7350 3550
Wire Wire Line
	7900 3700 7150 3700
Wire Wire Line
	7900 1300 5050 1300
Wire Wire Line
	5050 1450 7900 1450
$Sheet
S 2700 1100 2350 2200
U 5D5B15F7
F0 "MCU" 50
F1 "MCU.sch" 50
F2 "MCU_MOSI1" O L 2700 2650 50 
F3 "MCU_SCLK1" O L 2700 2800 50 
F4 "MCU_NSEL1" I L 2700 2950 50 
F5 "MCU_MISO1" O L 2700 2500 50 
F6 "MCU_SDA3" B R 5050 1750 50 
F7 "MCU_SCL3" B R 5050 1900 50 
F8 "MCU_TXD0" O R 5050 1450 50 
F9 "MCU_RXD0" I R 5050 1300 50 
F10 "MCU_PA02" I L 2700 1550 50 
F11 "MCU_PA03" B R 5050 2400 50 
F12 "MCU_PA04" B R 5050 2550 50 
F13 "MCU_PA05" B R 5050 2700 50 
F14 "MCU_PA06" B R 5050 2850 50 
F15 "MCU_PA07" B R 5050 3000 50 
F16 "MCU_PA08" B R 5050 3150 50 
F17 "MCU_PA09" O L 2700 2350 50 
F18 "MCU_PA13" B L 2700 1700 50 
F19 "MCU_PB03" O R 5050 2050 50 
F20 "MCU_PB02" O R 5050 1600 50 
F21 "MCU_PB08" I R 5050 2200 50 
F22 "MCU_PA20" I L 2700 1900 50 
F23 "MCU_PA21" I L 2700 2050 50 
F24 "MCU_PA27" I L 2700 2200 50 
$EndSheet
Wire Wire Line
	5050 1750 7350 1750
Wire Wire Line
	5050 1900 7150 1900
Wire Wire Line
	7350 3550 7350 1750
Connection ~ 7350 1750
Wire Wire Line
	7350 1750 7900 1750
Wire Wire Line
	7150 3700 7150 1900
Connection ~ 7150 1900
Wire Wire Line
	7150 1900 7900 1900
Wire Wire Line
	5050 2050 7900 2050
Wire Wire Line
	7900 2200 5050 2200
Wire Wire Line
	5050 1600 7900 1600
$Sheet
S 7950 5000 2300 1200
U 5D6468D5
F0 "pyro_driver" 50
F1 "pyro_driver.sch" 50
F2 "SENSE_FET_A" O L 7950 5350 50 
F3 "FIRE_A" O L 7950 5650 50 
F4 "SENSE_FET_B" O L 7950 5500 50 
F5 "FIRE_B" O L 7950 5800 50 
$EndSheet
Wire Wire Line
	2700 1550 850  1550
Wire Wire Line
	850  1550 850  6050
Wire Wire Line
	850  6050 2700 6050
Wire Wire Line
	2700 1700 1000 1700
Wire Wire Line
	1000 1700 1000 5900
Wire Wire Line
	1000 5900 2700 5900
Wire Wire Line
	2000 2500 2700 2500
Wire Wire Line
	2150 2650 2700 2650
Wire Wire Line
	2300 2800 2700 2800
Wire Wire Line
	2700 2950 2450 2950
Wire Wire Line
	2450 4050 2700 4050
Wire Wire Line
	2700 4350 2150 4350
Wire Wire Line
	2700 4500 2000 4500
Wire Wire Line
	2700 4200 2300 4200
Wire Wire Line
	2300 4200 2300 2800
Wire Wire Line
	2150 4350 2150 2650
Wire Wire Line
	2000 4500 2000 2500
Wire Wire Line
	2450 2950 2450 4050
Wire Wire Line
	2700 4650 1850 4650
Wire Wire Line
	1850 2350 2700 2350
Wire Wire Line
	1850 2350 1850 4650
$Sheet
S 2700 3650 2350 1600
U 5D5B17D8
F0 "telemetry_radio" 50
F1 "telemetry_radio.sch" 50
F2 "RF_SCLK" I L 2700 4200 50 
F3 "RF_MISO" O L 2700 4500 50 
F4 "RF_MOSI" I L 2700 4350 50 
F5 "RF_NSEL" I L 2700 4050 50 
F6 "RF_SDN" I L 2700 4650 50 
F7 "RF_NIRQ" O L 2700 4800 50 
F8 "RF_GPIO0" B L 2700 4950 50 
F9 "RF_GPIO1" B L 2700 5100 50 
$EndSheet
Wire Wire Line
	2700 4800 1650 4800
Wire Wire Line
	1650 4800 1650 2200
Wire Wire Line
	1650 2200 2700 2200
Wire Wire Line
	2700 4950 1450 4950
Wire Wire Line
	1450 4950 1450 2050
Wire Wire Line
	1450 2050 2700 2050
Wire Wire Line
	2700 5100 1250 5100
Wire Wire Line
	1250 5100 1250 1900
Wire Wire Line
	1250 1900 2700 1900
Wire Wire Line
	7900 3900 6950 3900
Wire Wire Line
	6950 3900 6950 2400
Wire Wire Line
	6950 2400 5050 2400
Wire Wire Line
	7900 4050 6750 4050
Wire Wire Line
	6750 4050 6750 2550
Wire Wire Line
	6750 2550 5050 2550
Wire Wire Line
	5050 2700 6500 2700
Wire Wire Line
	6500 2700 6500 5350
Wire Wire Line
	6500 5350 7950 5350
Wire Wire Line
	5050 2850 6350 2850
Wire Wire Line
	6350 2850 6350 5500
Wire Wire Line
	6350 5500 7950 5500
Wire Wire Line
	7950 5650 6150 5650
Wire Wire Line
	6150 5650 6150 3000
Wire Wire Line
	6150 3000 5050 3000
Wire Wire Line
	5050 3150 5950 3150
Wire Wire Line
	5950 3150 5950 5800
Wire Wire Line
	5950 5800 7950 5800
$EndSCHEMATC
