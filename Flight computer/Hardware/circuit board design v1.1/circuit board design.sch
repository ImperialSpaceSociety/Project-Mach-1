EESchema Schematic File Version 4
LIBS:circuit board design-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 7
Title "flight computer for rocket"
Date "2019-09-09"
Rev "1.0"
Comp "Imperial College Space Society"
Comment1 "Based on the Picotracker MK II"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 7900 3000 2350 1300
U 5D5B1586
F0 "sensors" 50
F1 "sensors.sch" 50
F2 "SENS_SDA" B L 7900 3550 50 
F3 "SENS_SCL" B L 7900 3700 50 
F4 "MAG_RDY" O L 7900 4000 50 
F5 "ACCL_RDY" O L 7900 4200 50 
F6 "GYRO_RDY" O L 7900 4100 50 
F7 "H_ACCL_INT1" I L 7900 3800 50 
F8 "H_ACCL_INT2" I L 7900 3900 50 
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
F7 "GPS_NRES" I L 7900 2350 50 
F8 "GPS_1PPS" O L 7900 2200 50 
$EndSheet
Wire Wire Line
	7900 3550 7350 3550
Wire Wire Line
	7900 3700 7150 3700
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
	2700 5700 1650 5700
Wire Wire Line
	2700 5550 1850 5550
Wire Wire Line
	2450 4950 2700 4950
Wire Wire Line
	2700 5250 2150 5250
Wire Wire Line
	2700 5400 2000 5400
Wire Wire Line
	2700 5100 2300 5100
$Sheet
S 2700 4550 2350 1600
U 5D5B17D8
F0 "telemetry_radio" 50
F1 "telemetry_radio.sch" 50
F2 "RF_SCLK" I L 2700 5100 50 
F3 "RF_MISO" O L 2700 5400 50 
F4 "RF_MOSI" I L 2700 5250 50 
F5 "RF_NSEL" I L 2700 4950 50 
F6 "RF_SDN" I L 2700 5550 50 
F7 "RF_NIRQ" O L 2700 5700 50 
F8 "RF_GPIO0" B L 2700 5850 50 
F9 "RF_GPIO1" B L 2700 6000 50 
$EndSheet
Wire Wire Line
	6450 3450 6450 5050
Wire Wire Line
	6450 5050 7900 5050
Wire Wire Line
	7900 5150 6350 5150
Wire Wire Line
	6350 5150 6350 3550
Wire Wire Line
	2700 5850 1450 5850
Wire Wire Line
	2700 6000 1250 6000
Wire Wire Line
	5750 4000 5050 4000
Wire Wire Line
	5050 3900 5850 3900
Wire Wire Line
	6350 3550 5050 3550
Wire Wire Line
	5050 3450 6450 3450
Wire Wire Line
	5050 1450 7900 1450
Wire Wire Line
	5050 1900 7150 1900
Wire Wire Line
	5050 1750 7350 1750
Wire Wire Line
	1850 2700 1850 5550
Wire Wire Line
	2450 3300 2450 4950
Wire Wire Line
	1650 2550 2700 2550
Wire Wire Line
	1450 2400 2700 2400
Wire Wire Line
	1850 2700 2700 2700
Wire Wire Line
	2150 3000 2700 3000
Wire Wire Line
	2300 3150 2700 3150
Wire Wire Line
	2700 3300 2450 3300
Wire Wire Line
	1250 2250 2700 2250
Wire Wire Line
	1250 6000 1250 2250
Wire Wire Line
	1450 5850 1450 2400
Wire Wire Line
	1650 5700 1650 2550
Wire Wire Line
	2150 5250 2150 3000
Wire Wire Line
	2300 5100 2300 3150
Wire Wire Line
	2700 6700 900  6700
Wire Wire Line
	900  6700 900  1600
Wire Wire Line
	900  1600 2700 1600
$Sheet
S 2700 6400 2350 1200
U 5D5B1705
F0 "power_supply" 50
F1 "power_supply.sch" 50
F2 "PWR_BVOLTS" O L 2700 6700 50 
F3 "USB_DM" I L 2700 6800 50 
F4 "USB_DP" I L 2700 6900 50 
$EndSheet
Wire Wire Line
	2700 6800 800  6800
Wire Wire Line
	800  6800 800  1500
Wire Wire Line
	800  1500 2700 1500
Wire Wire Line
	2700 1400 700  1400
Wire Wire Line
	700  1400 700  6900
Wire Wire Line
	700  6900 2700 6900
Wire Wire Line
	5750 5800 5750 4000
Wire Wire Line
	7900 5800 5750 5800
Wire Wire Line
	5850 5700 7900 5700
Wire Wire Line
	5850 3900 5850 5700
Wire Wire Line
	6750 4000 7900 4000
Wire Wire Line
	6750 2900 6750 4000
Wire Wire Line
	7900 3800 6950 3800
Wire Wire Line
	6950 2700 5050 2700
Wire Wire Line
	6850 2800 5050 2800
Wire Wire Line
	5050 2900 6750 2900
Wire Wire Line
	5050 1300 7900 1300
Wire Wire Line
	2000 2850 2700 2850
Wire Wire Line
	2000 2850 2000 5400
Wire Wire Line
	5050 2050 7900 2050
Wire Wire Line
	7900 2200 5050 2200
Wire Wire Line
	5050 2350 7900 2350
$Sheet
S 7900 4700 2350 1600
U 5D6468D5
F0 "pyro_driver" 50
F1 "pyro_driver.sch" 50
F2 "SENSE_FET_A" O L 7900 5050 50 
F3 "FIRE_A" O L 7900 5700 50 
F4 "SENSE_FET_B" O L 7900 5150 50 
F5 "FIRE_B" O L 7900 5800 50 
$EndSheet
Wire Wire Line
	6950 3800 6950 2700
Wire Wire Line
	6850 3900 6850 2800
Wire Wire Line
	6850 3900 7900 3900
$Sheet
S 2700 1100 2350 3200
U 5D5B15F7
F0 "MCU" 50
F1 "MCU.sch" 50
F2 "MCU_MOSI1" O L 2700 3000 50 
F3 "MCU_SCLK1" O L 2700 3150 50 
F4 "MCU_NSEL1" I L 2700 3300 50 
F5 "MCU_MISO1" O L 2700 2850 50 
F6 "MCU_SDA3" B R 5050 1750 50 
F7 "MCU_SCL3" B R 5050 1900 50 
F8 "MCU_PA02" I R 5050 2200 50 
F9 "MCU_PA05" B R 5050 3550 50 
F10 "MCU_PA20" I R 5050 2700 50 
F11 "MCU_PA21" I R 5050 2800 50 
F12 "USB_DP" I L 2700 1500 50 
F13 "USB_DM" I L 2700 1400 50 
F14 "GPS_TXD0" O R 5050 1450 50 
F15 "GPS_RXD0" I R 5050 1300 50 
F16 "MCU_PA10" B R 5050 3900 50 
F17 "MCU_PA11" B R 5050 4000 50 
F18 "MCU_PA04" B R 5050 3450 50 
F19 "MCU_PA12" B L 2700 2250 50 
F20 "MCU_PA13" B L 2700 2400 50 
F21 "MCU_PB11" I L 2700 2700 50 
F22 "MCU_PB17" I R 5050 2900 50 
F23 "MCU_PB08" I L 2700 1600 50 
F24 "MCU_PA01" I R 5050 2050 50 
F25 "MCU_PA03" I R 5050 2350 50 
F26 "MCU_PB10" I L 2700 2550 50 
F27 "MCU_PA18" I R 5050 3000 50 
F28 "MCU_PA19" I R 5050 3100 50 
$EndSheet
Wire Wire Line
	5050 3000 6650 3000
Wire Wire Line
	6650 3000 6650 4100
Wire Wire Line
	6650 4100 7900 4100
Wire Wire Line
	7900 4200 6550 4200
Wire Wire Line
	6550 4200 6550 3100
Wire Wire Line
	6550 3100 5050 3100
$EndSCHEMATC
