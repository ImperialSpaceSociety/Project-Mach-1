EESchema Schematic File Version 4
LIBS:circuit board design-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 7
Title "Pyro drivers"
Date "2019-09-02"
Rev ""
Comp ""
Comment1 "Pyro drivers based on the Telementrum design"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Comparator:LM2903 U1
U 1 1 5D6C6230
P 2600 1050
F 0 "U1" H 2600 1417 50  0000 C CNN
F 1 "LM2903" H 2600 1326 50  0000 C CNN
F 2 "" H 2600 1050 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm393-n.pdf" H 2600 1050 50  0001 C CNN
	1    2600 1050
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:Si7232DN-Driver_FET U6
U 1 1 5D696EFB
P 3950 1000
AR Path="/5D696EFB" Ref="U6"  Part="1" 
AR Path="/5D6468D5/5D696EFB" Ref="U6"  Part="1" 
F 0 "U6" H 4056 546 50  0000 L CNN
F 1 "Si7232DN" H 4056 455 50  0000 L CNN
F 2 "Package_SO:Vishay_PowerPAK_1212-8_Dual" H 3800 1250 50  0001 C CNN
F 3 "https://www.vishay.com/docs/68986/si7232dn.pdf" H 3950 1000 50  0001 C CNN
	1    3950 1000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR024
U 1 1 5D69AE81
P 3950 1900
F 0 "#PWR024" H 3950 1650 50  0001 C CNN
F 1 "GND" H 3955 1727 50  0000 C CNN
F 2 "" H 3950 1900 50  0001 C CNN
F 3 "" H 3950 1900 50  0001 C CNN
	1    3950 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 1900 3950 1650
$Comp
L Device:R R5
U 1 1 5D6A50BE
P 4600 1250
F 0 "R5" V 4800 1250 50  0000 C CNN
F 1 "100K" V 4700 1250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4530 1250 50  0001 C CNN
F 3 "~" H 4600 1250 50  0001 C CNN
	1    4600 1250
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 5D6A6316
P 5050 1700
F 0 "R6" H 5120 1746 50  0000 L CNN
F 1 "27K" H 5120 1655 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4980 1700 50  0001 C CNN
F 3 "~" H 5050 1700 50  0001 C CNN
	1    5050 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 1250 5050 1250
Wire Wire Line
	5050 1550 5050 1250
Wire Wire Line
	5050 1900 5050 1850
$Comp
L power:GND #PWR025
U 1 1 5D6A67BF
P 5050 1900
F 0 "#PWR025" H 5050 1650 50  0001 C CNN
F 1 "GND" H 5055 1727 50  0000 C CNN
F 2 "" H 5050 1900 50  0001 C CNN
F 3 "" H 5050 1900 50  0001 C CNN
	1    5050 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 1250 4250 1250
Wire Wire Line
	4050 1150 4250 1150
Wire Wire Line
	4250 1250 4250 1150
Connection ~ 4250 1250
Wire Wire Line
	4250 1250 4450 1250
Connection ~ 4250 1150
Wire Wire Line
	4250 1150 5550 1150
Connection ~ 5050 1250
Wire Wire Line
	5050 1250 5550 1250
Text HLabel 5550 1250 2    50   Output ~ 0
SENSE_FET_A
Text Label 5550 1150 0    50   ~ 0
FET_A
Wire Wire Line
	2900 1050 3350 1050
Wire Wire Line
	3350 1050 3350 1450
Wire Wire Line
	3350 1450 3650 1450
Wire Wire Line
	3350 1450 3050 1450
Connection ~ 3350 1450
Wire Wire Line
	2550 1450 2550 1600
Connection ~ 2550 1450
Wire Wire Line
	2550 1450 1800 1450
$Comp
L power:GND #PWR023
U 1 1 5D6AF664
P 2550 2000
F 0 "#PWR023" H 2550 1750 50  0001 C CNN
F 1 "GND" H 2555 1827 50  0000 C CNN
F 2 "" H 2550 2000 50  0001 C CNN
F 3 "" H 2550 2000 50  0001 C CNN
	1    2550 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5D6AFE1F
P 2550 1750
F 0 "R3" H 2620 1796 50  0000 L CNN
F 1 "3.3K" H 2620 1705 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2480 1750 50  0001 C CNN
F 3 "~" H 2550 1750 50  0001 C CNN
	1    2550 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 1900 2550 2000
$Comp
L Device:R R4
U 1 1 5D6B06F6
P 2900 1450
F 0 "R4" V 2693 1450 50  0000 C CNN
F 1 "100" V 2784 1450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2830 1450 50  0001 C CNN
F 3 "~" H 2900 1450 50  0001 C CNN
	1    2900 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	2750 1450 2550 1450
Text HLabel 1800 1450 0    50   Output ~ 0
FIRE_A
$Comp
L power:GND #PWR027
U 1 1 5D6B2880
P 10150 4200
F 0 "#PWR027" H 10150 3950 50  0001 C CNN
F 1 "GND" H 10155 4027 50  0000 C CNN
F 2 "" H 10150 4200 50  0001 C CNN
F 3 "" H 10150 4200 50  0001 C CNN
	1    10150 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 3950 10150 4200
$Comp
L power:+3.3V #PWR026
U 1 1 5D6B231C
P 10150 3200
F 0 "#PWR026" H 10150 3050 50  0001 C CNN
F 1 "+3.3V" H 10165 3373 50  0000 C CNN
F 2 "" H 10150 3200 50  0001 C CNN
F 3 "" H 10150 3200 50  0001 C CNN
	1    10150 3200
	1    0    0    -1  
$EndComp
$Comp
L Comparator:LM2903 U5
U 3 1 5D6B191C
P 10250 3650
F 0 "U5" H 10208 3696 50  0000 L CNN
F 1 "LM2903" H 10208 3605 50  0000 L CNN
F 2 "" H 10250 3650 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm393-n.pdf" H 10250 3650 50  0001 C CNN
	3    10250 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 3350 10150 3200
Text Notes 1050 4850 0    50   ~ 0
Put in a block connector, like the TE connectivity ones\n
$Comp
L Connector:Conn_01x06_Female J4
U 1 1 5D6BBFA3
P 2100 4100
F 0 "J4" H 2128 4076 50  0000 L CNN
F 1 "Conn_01x06_Female" H 2128 3985 50  0000 L CNN
F 2 "" H 2100 4100 50  0001 C CNN
F 3 "~" H 2100 4100 50  0001 C CNN
	1    2100 4100
	1    0    0    -1  
$EndComp
NoConn ~ 2300 1150
NoConn ~ 2300 950 
NoConn ~ 1900 4000
NoConn ~ 1900 4100
NoConn ~ 1900 4200
NoConn ~ 1900 4300
NoConn ~ 1900 4400
Text Label 1350 3900 2    50   ~ 0
FET_A
Wire Wire Line
	1350 3900 1900 3900
$Comp
L Comparator:LM2903 U5
U 2 1 5D743B77
P 4450 3250
F 0 "U5" H 4450 3617 50  0000 C CNN
F 1 "LM2903" H 4450 3526 50  0000 C CNN
F 2 "" H 4450 3250 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm393-n.pdf" H 4450 3250 50  0001 C CNN
	2    4450 3250
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:Si7232DN-Driver_FET U?
U 2 1 5D743B81
P 5800 3200
AR Path="/5D743B81" Ref="U?"  Part="1" 
AR Path="/5D6468D5/5D743B81" Ref="U6"  Part="2" 
F 0 "U6" H 5906 2746 50  0000 L CNN
F 1 "Si7232DN" H 5906 2655 50  0000 L CNN
F 2 "Package_SO:Vishay_PowerPAK_1212-8_Dual" H 5650 3450 50  0001 C CNN
F 3 "https://www.vishay.com/docs/68986/si7232dn.pdf" H 5800 3200 50  0001 C CNN
	2    5800 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR043
U 1 1 5D743B8B
P 5800 4100
F 0 "#PWR043" H 5800 3850 50  0001 C CNN
F 1 "GND" H 5805 3927 50  0000 C CNN
F 2 "" H 5800 4100 50  0001 C CNN
F 3 "" H 5800 4100 50  0001 C CNN
	1    5800 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R15
U 1 1 5D743B96
P 6450 3450
F 0 "R15" V 6650 3450 50  0000 C CNN
F 1 "100K" V 6550 3450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6380 3450 50  0001 C CNN
F 3 "~" H 6450 3450 50  0001 C CNN
	1    6450 3450
	0    1    1    0   
$EndComp
$Comp
L Device:R R16
U 1 1 5D743BA0
P 6900 3900
F 0 "R16" H 6970 3946 50  0000 L CNN
F 1 "27K" H 6970 3855 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6830 3900 50  0001 C CNN
F 3 "~" H 6900 3900 50  0001 C CNN
	1    6900 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 3450 6900 3450
Wire Wire Line
	6900 3750 6900 3450
Wire Wire Line
	6900 4100 6900 4050
$Comp
L power:GND #PWR044
U 1 1 5D743BAD
P 6900 4100
F 0 "#PWR044" H 6900 3850 50  0001 C CNN
F 1 "GND" H 6905 3927 50  0000 C CNN
F 2 "" H 6900 4100 50  0001 C CNN
F 3 "" H 6900 4100 50  0001 C CNN
	1    6900 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 3450 6100 3450
Wire Wire Line
	5900 3350 6100 3350
Wire Wire Line
	6100 3450 6100 3350
Connection ~ 6100 3450
Wire Wire Line
	6100 3450 6300 3450
Connection ~ 6100 3350
Wire Wire Line
	6100 3350 7400 3350
Connection ~ 6900 3450
Wire Wire Line
	6900 3450 7400 3450
Text HLabel 7400 3450 2    50   Output ~ 0
SENSE_FET_B
Text Label 7400 3350 0    50   ~ 0
FET_B
Wire Wire Line
	4750 3250 5200 3250
Wire Wire Line
	5200 3250 5200 3650
Wire Wire Line
	5200 3650 5500 3650
Wire Wire Line
	5200 3650 4900 3650
Connection ~ 5200 3650
Wire Wire Line
	4400 3650 4400 3800
Connection ~ 4400 3650
Wire Wire Line
	4400 3650 3650 3650
$Comp
L power:GND #PWR042
U 1 1 5D743BCA
P 4400 4200
F 0 "#PWR042" H 4400 3950 50  0001 C CNN
F 1 "GND" H 4405 4027 50  0000 C CNN
F 2 "" H 4400 4200 50  0001 C CNN
F 3 "" H 4400 4200 50  0001 C CNN
	1    4400 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R13
U 1 1 5D743BD4
P 4400 3950
F 0 "R13" H 4470 3996 50  0000 L CNN
F 1 "3.3K" H 4470 3905 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4330 3950 50  0001 C CNN
F 3 "~" H 4400 3950 50  0001 C CNN
	1    4400 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 4100 4400 4200
$Comp
L Device:R R14
U 1 1 5D743BDF
P 4750 3650
F 0 "R14" V 4543 3650 50  0000 C CNN
F 1 "100" V 4634 3650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4680 3650 50  0001 C CNN
F 3 "~" H 4750 3650 50  0001 C CNN
	1    4750 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	4600 3650 4400 3650
Text HLabel 3650 3650 0    50   Output ~ 0
FIRE_B
NoConn ~ 4150 3350
NoConn ~ 4150 3150
Text Label 1350 4000 2    50   ~ 0
FET_B
Wire Wire Line
	1350 4000 1900 4000
Wire Wire Line
	5800 4100 5800 3850
$EndSCHEMATC
