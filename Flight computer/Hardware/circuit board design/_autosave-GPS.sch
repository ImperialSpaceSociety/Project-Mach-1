EESchema Schematic File Version 4
LIBS:circuit board design-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L flight-computer:ICSSPicoTracker_SAFEB1G57KE0F00 U13
U 1 1 5D44BB5C
P 3400 2450
F 0 "U13" H 3725 2925 50  0000 C CNN
F 1 "SAFEB1G57KE0F00" H 3725 2834 50  0000 C CNN
F 2 "pico_tracker:Murata SAFE" H 3400 2450 50  0001 C CNN
F 3 "https://www.murata.com/en-eu/products/productdata/8797690593310/DS-SAFEB1G57KE0F00.pdf?1453347007000" H 3400 2450 50  0001 C CNN
F 4 "https://www.rf-microwave.com/en/murata/safeb1g57ke0f00/1575-5-mhz-band-pass-saw/fw-safeb1g57/" H 3400 2450 50  0001 C CNN "Purchase link"
	1    3400 2450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR053
U 1 1 5D459323
P 3200 2700
F 0 "#PWR053" H 3200 2450 50  0001 C CNN
F 1 "GND" H 3205 2527 50  0000 C CNN
F 2 "" H 3200 2700 50  0001 C CNN
F 3 "" H 3200 2700 50  0001 C CNN
	1    3200 2700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR058
U 1 1 5D459A04
P 4250 2750
F 0 "#PWR058" H 4250 2500 50  0001 C CNN
F 1 "GND" H 4255 2577 50  0000 C CNN
F 2 "" H 4250 2750 50  0001 C CNN
F 3 "" H 4250 2750 50  0001 C CNN
	1    4250 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 2400 4250 2400
Wire Wire Line
	4250 2400 4250 2750
Wire Wire Line
	3300 2300 3200 2300
Wire Wire Line
	3200 2300 3200 2400
Wire Wire Line
	3300 2400 3200 2400
Connection ~ 3200 2400
Wire Wire Line
	3200 2400 3200 2700
Wire Wire Line
	3250 2050 3250 1900
Text HLabel 7200 4350 2    50   Output ~ 0
GPS_1PPS
Text Notes 3000 5800 0    50   ~ 0
Arranged according to Figure 7 in the MAX-8 / MAX-M8 u-blox 8 / M8 GNSS modules Hardware Integration Manual. Page 12.
Wire Wire Line
	3250 1900 6800 1900
Text Notes 7850 4950 0    50   ~ 0
http://www.explorelabs.com/blog/designing-a-gps-receiver/#ref-ublox-datasheet\n\nImportant info on why we use the components\n
NoConn ~ 5450 4250
$Comp
L RF_GPS:MAX-M8C U4
U 1 1 5D610F77
P 6050 4050
F 0 "U4" H 6050 4900 50  0000 C CNN
F 1 "MAX-M8C" H 6050 5250 50  0000 C CNN
F 2 "RF_GPS:ublox_MAX" H 6450 3400 50  0001 C CNN
F 3 "https://www.u-blox.com/sites/default/files/MAX-M8-FW3_DataSheet_%28UBX-15031506%29.pdf" H 6050 4050 50  0001 C CNN
F 4 "11.99" H 6050 4050 50  0001 C CNN "Cost"
F 5 "https://store.uputronics.com/index.php?route=product/product&product_id=71&search=ublox" H 6050 4050 50  0001 C CNN "Purchase link"
	1    6050 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 4800 6050 4800
$Comp
L Device:R R2
U 1 1 5D69D778
P 6450 4800
F 0 "R2" V 6700 4800 50  0000 C CNN
F 1 "10K" V 6600 4800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6380 4800 50  0001 C CNN
F 3 "~" H 6450 4800 50  0001 C CNN
	1    6450 4800
	0    1    1    0   
$EndComp
Wire Wire Line
	6050 4800 6050 4750
Connection ~ 6050 4800
Connection ~ 6800 3850
Wire Wire Line
	6800 4800 6600 4800
Wire Wire Line
	6800 3850 6800 4800
Wire Wire Line
	6050 4900 6050 4800
Wire Wire Line
	6650 4350 7200 4350
$Comp
L power:+3.3V #PWR010
U 1 1 5D692740
P 5850 3150
F 0 "#PWR010" H 5850 3000 50  0001 C CNN
F 1 "+3.3V" H 5865 3323 50  0000 C CNN
F 2 "" H 5850 3150 50  0001 C CNN
F 3 "" H 5850 3150 50  0001 C CNN
	1    5850 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 1900 6800 3850
Wire Wire Line
	6800 3850 6650 3850
$Comp
L power:GND #PWR011
U 1 1 5D67FE0F
P 6050 4900
F 0 "#PWR011" H 6050 4650 50  0001 C CNN
F 1 "GND" H 6055 4727 50  0000 C CNN
F 2 "" H 6050 4900 50  0001 C CNN
F 3 "" H 6050 4900 50  0001 C CNN
	1    6050 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 4050 6650 4050
Wire Wire Line
	4150 2200 6900 2200
Wire Wire Line
	6900 2200 6900 4050
Wire Wire Line
	3150 1800 3150 1900
Wire Wire Line
	6250 3350 6250 1800
Wire Wire Line
	6250 1800 3150 1800
Wire Wire Line
	5850 3150 5850 3250
Wire Wire Line
	5950 3350 5950 3250
Wire Wire Line
	5950 3250 5850 3250
Connection ~ 5850 3250
Wire Wire Line
	5850 3250 5850 3350
NoConn ~ 6050 3350
$Comp
L power:GND #PWR052
U 1 1 5D458C8C
P 2000 2550
F 0 "#PWR052" H 2000 2300 50  0001 C CNN
F 1 "GND" H 2005 2377 50  0000 C CNN
F 2 "" H 2000 2550 50  0001 C CNN
F 3 "" H 2000 2550 50  0001 C CNN
	1    2000 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 2050 2000 2200
Connection ~ 2000 2200
Wire Wire Line
	2000 2200 2000 2550
Wire Wire Line
	2100 2050 2000 2050
Wire Wire Line
	2100 2200 2000 2200
$Comp
L flight-computer:ICSSPicoTracker_MAX2659ELT+ U12
U 1 1 5D44B218
P 2200 2350
F 0 "U12" H 2500 3115 50  0000 C CNN
F 1 "MAX2659ELT+" H 2500 3024 50  0000 C CNN
F 2 "pico_tracker:uDFN-6_1.0x1.5mm_P0.5mm" H 2200 2350 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX2659.pdf" H 2200 2350 50  0001 C CNN
F 4 "https://www.mouser.co.uk/ProductDetail/Maxim-Integrated/MAX2659ELT+T?qs=GxOUx7aO6nyMDHP%2F45gvTg==" H 2200 2350 50  0001 C CNN "Purchase link"
	1    2200 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 1900 2900 1900
Wire Wire Line
	2900 2050 3250 2050
Wire Wire Line
	3300 2200 2900 2200
Wire Wire Line
	1800 1500 1700 1500
$Comp
L flight-computer:ICSSPicoTracker_Johanson1575 ANT1
U 1 1 5D521711
P 1300 1500
AR Path="/5D521711" Ref="ANT1"  Part="1" 
AR Path="/5D2ABE03/5D521711" Ref="ANT1"  Part="1" 
AR Path="/5D5B165E/5D521711" Ref="ANT1"  Part="1" 
F 0 "ANT1" H 1250 1765 50  0000 C CNN
F 1 "Johanson1575" H 1250 1674 50  0000 C CNN
F 2 "pico_tracker:Johanson1575" H 1300 1500 50  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/611/JTI_Antenna-1575AT43A40_2006-09-399627.pdf" H 1300 1500 50  0001 C CNN
F 4 "0.753" H 1300 1500 50  0001 C CNN "Cost"
F 5 "https://www.mouser.co.uk/ProductDetail/Johanson-Technology/1575AT43A0040E?qs=qF3SSroohZWOIHwrK8wTew%3D%3D" H 1300 1500 50  0001 C CNN "Purchase link"
	1    1300 1500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5450 3950 5150 3950
Text HLabel 5150 3750 0    50   Output ~ 0
GPS_TXD
Text HLabel 5150 3650 0    50   Input ~ 0
GPS_RXD
Text HLabel 5150 4050 0    50   BiDi ~ 0
GPS_SCL
Text HLabel 5150 3950 0    50   BiDi ~ 0
GPS_SDA
Text HLabel 5150 4350 0    50   Input ~ 0
GPS_NSAFEBOOT
Text HLabel 5150 4450 0    50   Input ~ 0
GPS_NRES
Wire Wire Line
	5450 3650 5150 3650
Wire Wire Line
	5450 4350 5150 4350
Wire Wire Line
	5150 3750 5450 3750
Wire Wire Line
	5150 4450 5450 4450
Wire Wire Line
	5150 4050 5450 4050
Wire Wire Line
	1800 1900 1800 1500
Wire Wire Line
	1800 1900 2100 1900
$EndSCHEMATC
