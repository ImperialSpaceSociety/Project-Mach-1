EESchema Schematic File Version 4
LIBS:circuit board design-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 7
Title "Silabs radio chip for telemetry to ground"
Date "2019-08-31"
Rev ""
Comp "Imperial College Space Society"
Comment1 "AN629 Figure 16 ideal according to Richard: CLE Switch TX/RX type matching network"
Comment2 "AN648 for matching network values"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RF_Switch:CG2179M2 U10
U 1 1 5D69DA03
P 3950 2900
F 0 "U10" H 3950 3215 50  0000 C CNN
F 1 "CG2179M2" H 3950 3124 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-363_SC-70-6_Handsoldering" H 3950 3250 50  0001 C CNN
F 3 "http://www.cel.com/pdf/datasheets/CG2179M2.pdf" H 3950 3250 50  0001 C CNN
	1    3950 2900
	1    0    0    -1  
$EndComp
Text Notes 2150 1500 0    50   ~ 0
Verify that the CG2179 has the right package. \nThe datasheet says 6 pi n mini mold but\n I suspect it is the more standard SOT-363. Verify
Wire Wire Line
	8150 4850 7800 4850
Text HLabel 8150 4850 2    50   Input ~ 0
RF_SCLK
Wire Wire Line
	8150 4950 7800 4950
Text HLabel 8150 4950 2    50   Input ~ 0
RF_MOSI
Wire Wire Line
	8150 5050 7800 5050
Text HLabel 8150 5050 2    50   Output ~ 0
RF_MISO
Wire Wire Line
	8150 5150 7800 5150
Text HLabel 8150 5150 2    50   Input ~ 0
RF_NSEL
Wire Wire Line
	7400 4050 7400 3900
$Comp
L power:+3.3V #PWR0101
U 1 1 5D62941F
P 7400 3750
F 0 "#PWR0101" H 7400 3600 50  0001 C CNN
F 1 "+3.3V" H 7415 3923 50  0000 C CNN
F 2 "" H 7400 3750 50  0001 C CNN
F 3 "" H 7400 3750 50  0001 C CNN
	1    7400 3750
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5D5CDCF8
P 7400 5900
F 0 "#PWR09" H 7400 5650 50  0001 C CNN
F 1 "GND" H 7405 5727 50  0000 C CNN
F 2 "" H 7400 5900 50  0001 C CNN
F 3 "" H 7400 5900 50  0001 C CNN
	1    7400 5900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7400 5450 7400 5900
$Comp
L RF:Si4463 U3
U 1 1 5D5CB5C3
P 7400 4750
F 0 "U3" H 7150 5450 50  0000 C CNN
F 1 "Si4463" H 7150 5550 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-20-1EP_4x4mm_P0.5mm_EP2.6x2.6mm_ThermalVias" H 7400 5950 50  0001 C CNN
F 3 "https://www.silabs.com/documents/public/data-sheets/Si4464-63-61-60.pdf" H 7100 4650 50  0001 C CNN
	1    7400 4750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3800 1900 3250 1900
Wire Wire Line
	3250 1900 3250 3050
Wire Wire Line
	3250 3050 3600 3050
Wire Wire Line
	3600 2850 3400 2850
Wire Wire Line
	3400 2850 3400 2050
Wire Wire Line
	3400 2050 3800 2050
Wire Wire Line
	3600 2950 3050 2950
Wire Wire Line
	4600 3050 4300 3050
$Comp
L Device:L L7
U 1 1 5D6C11E9
P 6250 4250
F 0 "L7" V 6069 4250 50  0000 C CNN
F 1 "33nH" V 6160 4250 50  0000 C CNN
F 2 "" H 6250 4250 50  0001 C CNN
F 3 "~" H 6250 4250 50  0001 C CNN
	1    6250 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	6100 4250 5950 4250
$Comp
L Device:C_Small C18
U 1 1 5D6C2505
P 5850 4250
F 0 "C18" V 5621 4250 50  0000 C CNN
F 1 "9.1pF" V 5712 4250 50  0000 C CNN
F 2 "" H 5850 4250 50  0001 C CNN
F 3 "~" H 5850 4250 50  0001 C CNN
	1    5850 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	4600 3050 4600 3300
Wire Wire Line
	4600 3750 4200 3750
$Comp
L Device:L L5
U 1 1 5D6C5384
P 5250 4250
F 0 "L5" V 5069 4250 50  0000 C CNN
F 1 "30nH" V 5160 4250 50  0000 C CNN
F 2 "" H 5250 4250 50  0001 C CNN
F 3 "~" H 5250 4250 50  0001 C CNN
	1    5250 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	5400 4250 5600 4250
Wire Wire Line
	4900 4250 4900 4500
Wire Wire Line
	4900 4250 5100 4250
$Comp
L power:GND #PWR016
U 1 1 5D6C66B7
P 4900 4850
F 0 "#PWR016" H 4900 4600 50  0001 C CNN
F 1 "GND" H 4905 4677 50  0000 C CNN
F 2 "" H 4900 4850 50  0001 C CNN
F 3 "" H 4900 4850 50  0001 C CNN
	1    4900 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 4250 5600 4500
Connection ~ 5600 4250
Wire Wire Line
	5600 4250 5750 4250
$Comp
L power:GND #PWR028
U 1 1 5D6C80F7
P 5600 4850
F 0 "#PWR028" H 5600 4600 50  0001 C CNN
F 1 "GND" H 5605 4677 50  0000 C CNN
F 2 "" H 5600 4850 50  0001 C CNN
F 3 "" H 5600 4850 50  0001 C CNN
	1    5600 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C12
U 1 1 5D6C92D3
P 4600 3400
F 0 "C12" H 4508 3354 50  0000 R CNN
F 1 "150pF" H 4508 3445 50  0000 R CNN
F 2 "" H 4600 3400 50  0001 C CNN
F 3 "~" H 4600 3400 50  0001 C CNN
	1    4600 3400
	-1   0    0    1   
$EndComp
Wire Wire Line
	4600 3500 4600 3750
Wire Wire Line
	4300 2950 4950 2950
Wire Wire Line
	4950 2950 4950 3150
$Comp
L power:GND #PWR017
U 1 1 5D6CA50E
P 4950 3150
F 0 "#PWR017" H 4950 2900 50  0001 C CNN
F 1 "GND" H 4955 2977 50  0000 C CNN
F 2 "" H 4950 3150 50  0001 C CNN
F 3 "" H 4950 3150 50  0001 C CNN
	1    4950 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 3500 5950 3550
$Comp
L power:GND #PWR030
U 1 1 5D6CBC88
P 5950 3550
F 0 "#PWR030" H 5950 3300 50  0001 C CNN
F 1 "GND" H 5955 3377 50  0000 C CNN
F 2 "" H 5950 3550 50  0001 C CNN
F 3 "" H 5950 3550 50  0001 C CNN
	1    5950 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 4250 6400 4250
Wire Wire Line
	6600 3500 6350 3500
Wire Wire Line
	6600 4250 6600 4000
Wire Wire Line
	6600 3500 6600 3300
Connection ~ 6600 3500
$Comp
L Device:C_Small C19
U 1 1 5D6CDD9C
P 6250 3500
F 0 "C19" V 6021 3500 50  0000 C CNN
F 1 "C_Small" V 6112 3500 50  0000 C CNN
F 2 "" H 6250 3500 50  0001 C CNN
F 3 "~" H 6250 3500 50  0001 C CNN
	1    6250 3500
	0    1    1    0   
$EndComp
Wire Wire Line
	6150 3500 5950 3500
$Comp
L Device:L L8
U 1 1 5D6CE249
P 6600 3850
F 0 "L8" H 6556 3804 50  0000 R CNN
F 1 "220nH" H 6556 3895 50  0000 R CNN
F 2 "" H 6600 3850 50  0001 C CNN
F 3 "~" H 6600 3850 50  0001 C CNN
	1    6600 3850
	-1   0    0    1   
$EndComp
Wire Wire Line
	6600 3700 6600 3500
$Comp
L power:+3.3V #PWR031
U 1 1 5D6CE7B6
P 6600 3300
F 0 "#PWR031" H 6600 3150 50  0001 C CNN
F 1 "+3.3V" H 6615 3473 50  0000 C CNN
F 2 "" H 6600 3300 50  0001 C CNN
F 3 "" H 6600 3300 50  0001 C CNN
	1    6600 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 2100 5800 2100
Wire Wire Line
	4700 2850 4300 2850
Wire Wire Line
	6950 1300 5800 1300
$Comp
L Device:C_Small C15
U 1 1 5D6D6FFF
P 5200 1300
F 0 "C15" V 5429 1300 50  0000 C CNN
F 1 "2.2pF" V 5338 1300 50  0000 C CNN
F 2 "" H 5200 1300 50  0001 C CNN
F 3 "~" H 5200 1300 50  0001 C CNN
	1    5200 1300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5100 1300 4700 1300
Wire Wire Line
	5800 1300 5800 1550
Connection ~ 5800 1300
Wire Wire Line
	5800 1300 5300 1300
Connection ~ 5800 2100
Wire Wire Line
	5800 2100 5350 2100
$Comp
L Device:L L6
U 1 1 5D6D8AED
P 5800 1700
F 0 "L6" H 5756 1654 50  0000 R CNN
F 1 "62nH" H 5756 1745 50  0000 R CNN
F 2 "" H 5800 1700 50  0001 C CNN
F 3 "~" H 5800 1700 50  0001 C CNN
	1    5800 1700
	-1   0    0    1   
$EndComp
Wire Wire Line
	5800 1850 5800 2100
$Comp
L Device:L L4
U 1 1 5D6D9105
P 5200 2100
F 0 "L4" V 5390 2100 50  0000 C CNN
F 1 "56nH" V 5299 2100 50  0000 C CNN
F 2 "" H 5200 2100 50  0001 C CNN
F 3 "~" H 5200 2100 50  0001 C CNN
	1    5200 2100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5800 2100 5800 2400
$Comp
L power:GND #PWR029
U 1 1 5D6DAF5F
P 5800 2700
F 0 "#PWR029" H 5800 2450 50  0001 C CNN
F 1 "GND" H 5805 2527 50  0000 C CNN
F 2 "" H 5800 2700 50  0001 C CNN
F 3 "" H 5800 2700 50  0001 C CNN
	1    5800 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C17
U 1 1 5D6DCF9F
P 5800 2500
F 0 "C17" H 5708 2454 50  0000 R CNN
F 1 "4.7pF" H 5708 2545 50  0000 R CNN
F 2 "" H 5800 2500 50  0001 C CNN
F 3 "~" H 5800 2500 50  0001 C CNN
	1    5800 2500
	-1   0    0    1   
$EndComp
Wire Wire Line
	5800 2600 5800 2700
Wire Wire Line
	7000 4750 6950 4750
$Comp
L Device:C_Small C14
U 1 1 5D6E3CAE
P 4900 4600
F 0 "C14" H 4992 4646 50  0000 L CNN
F 1 "12pF" H 4992 4555 50  0000 L CNN
F 2 "" H 4900 4600 50  0001 C CNN
F 3 "~" H 4900 4600 50  0001 C CNN
	1    4900 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 4700 4900 4850
$Comp
L Device:C_Small C16
U 1 1 5D6E42AD
P 5600 4600
F 0 "C16" H 5692 4646 50  0000 L CNN
F 1 "15pF" H 5692 4555 50  0000 L CNN
F 2 "" H 5600 4600 50  0001 C CNN
F 3 "~" H 5600 4600 50  0001 C CNN
	1    5600 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 4700 5600 4850
Text Notes 4050 5650 0    50   ~ 0
434 Mhz Low pass filter part 2. \nSee AN648 section 6:\nLowpass Filter Design Methodology \nfor RF Switch Board Configuration. \nRF switch is placed \nbetween 2 half filter sections.
Wire Wire Line
	6950 4750 6950 1300
Wire Wire Line
	6800 2100 6800 4650
Wire Wire Line
	6600 4250 7000 4250
Connection ~ 6600 4250
Wire Wire Line
	6800 4650 7000 4650
Wire Wire Line
	5050 2100 4700 2100
Wire Wire Line
	4700 2600 4700 2850
$Comp
L Device:C_Small C13
U 1 1 5D6D666F
P 4700 2500
F 0 "C13" H 4608 2454 50  0000 R CNN
F 1 "150pF" H 4608 2545 50  0000 R CNN
F 2 "" H 4700 2500 50  0001 C CNN
F 3 "~" H 4700 2500 50  0001 C CNN
	1    4700 2500
	-1   0    0    1   
$EndComp
Connection ~ 4700 2100
Wire Wire Line
	4700 1300 4700 2100
Wire Wire Line
	4700 2100 4700 2400
Connection ~ 4900 4250
Wire Wire Line
	4750 4250 4900 4250
$Comp
L Device:L L3
U 1 1 5D6C560A
P 4600 4250
F 0 "L3" V 4419 4250 50  0000 C CNN
F 1 "18nH" V 4510 4250 50  0000 C CNN
F 2 "" H 4600 4250 50  0001 C CNN
F 3 "~" H 4600 4250 50  0001 C CNN
	1    4600 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	4200 4250 4450 4250
Wire Wire Line
	4200 3750 4200 4250
Wire Notes Line
	6400 4050 6750 4050
Wire Notes Line
	6750 4050 6750 3650
Wire Notes Line
	6750 3650 6400 3650
Text Notes 6350 3650 0    50   ~ 0
Lchoke\n
Wire Wire Line
	7300 4050 7300 3900
Wire Wire Line
	7300 3900 7400 3900
Connection ~ 7400 3900
Wire Wire Line
	7400 3900 7400 3750
Wire Wire Line
	8150 4250 7800 4250
Text HLabel 8150 4250 2    50   Input ~ 0
RF_SDN_shutdown
NoConn ~ 7000 4450
Text Label 3800 1900 0    50   ~ 0
RF_GPIO_2
Wire Wire Line
	7000 4950 6800 4950
Wire Wire Line
	7000 5050 6800 5050
Text Label 3800 2050 0    50   ~ 0
RF_GPIO_0
Text Label 6800 4950 2    50   ~ 0
RF_GPIO_2
Text Label 6800 5050 2    50   ~ 0
RF_GPIO_0
Text Notes 3800 3250 0    50   ~ 0
RF switch
NoConn ~ 7000 5150
NoConn ~ 7000 5250
$Comp
L Oscillator:TM-32.000-AF3-33-S X1
U 1 1 5D6B4DFE
P 10000 3550
F 0 "X1" H 10344 3596 50  0000 L CNN
F 1 "TM-32.000-AF3-33-S" H 10200 3950 50  0000 L CNN
F 2 "" H 10450 3200 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/15dc/0900766b815dc7d9.pdf" H 9900 3550 50  0001 C CNN
	1    10000 3550
	-1   0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR032
U 1 1 5D6B5C3D
P 10000 2850
F 0 "#PWR032" H 10000 2700 50  0001 C CNN
F 1 "+3.3V" H 10015 3023 50  0000 C CNN
F 2 "" H 10000 2850 50  0001 C CNN
F 3 "" H 10000 2850 50  0001 C CNN
	1    10000 2850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10000 2850 10000 3000
NoConn ~ 10300 3550
$Comp
L power:GND #PWR033
U 1 1 5D6BDDD0
P 10000 4050
F 0 "#PWR033" H 10000 3800 50  0001 C CNN
F 1 "GND" H 10005 3877 50  0000 C CNN
F 2 "" H 10000 4050 50  0001 C CNN
F 3 "" H 10000 4050 50  0001 C CNN
	1    10000 4050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9700 3550 9250 3550
Wire Wire Line
	9250 3550 9250 3850
Wire Wire Line
	7800 4450 9250 4450
$Comp
L Device:C_Small C20
U 1 1 5D6C2DE3
P 9250 3950
F 0 "C20" H 9500 3950 50  0000 C CNN
F 1 "10nF" H 9500 3850 50  0000 C CNN
F 2 "" H 9250 3950 50  0001 C CNN
F 3 "~" H 9250 3950 50  0001 C CNN
	1    9250 3950
	-1   0    0    1   
$EndComp
Wire Wire Line
	9250 4050 9250 4450
Text HLabel 8150 5250 2    50   Input ~ 0
RF_NIRQ
Wire Wire Line
	7800 5250 8150 5250
$Comp
L Device:C_Small C21
U 1 1 5D6BC5E2
P 10700 3350
F 0 "C21" H 10950 3350 50  0000 C CNN
F 1 "33nF" H 10950 3250 50  0000 C CNN
F 2 "" H 10700 3350 50  0001 C CNN
F 3 "~" H 10700 3350 50  0001 C CNN
	1    10700 3350
	-1   0    0    1   
$EndComp
Wire Wire Line
	10000 3000 10700 3000
Wire Wire Line
	10700 3000 10700 3250
Connection ~ 10000 3000
Wire Wire Line
	10000 3000 10000 3250
Wire Wire Line
	10000 4050 10000 3950
Wire Notes Line
	4400 3850 4400 5150
Wire Notes Line
	5400 3850 5400 5150
Wire Notes Line
	6300 5150 6300 4400
Wire Notes Line
	6300 4400 6400 4400
Wire Notes Line
	4400 5150 6300 5150
Wire Notes Line
	6400 3650 6400 4400
Text Notes 5550 5250 0    50   ~ 0
434 Mhz TX Match
Wire Wire Line
	10000 3950 10700 3950
Wire Wire Line
	10700 3950 10700 3450
Connection ~ 10000 3950
Wire Wire Line
	10000 3950 10000 3850
Text Notes 1900 4500 0    50   ~ 0
The Capacitors connected to RFC, RF1 and RF2\n are DC blocking capacitors. "many switches contain \ndc bias voltage on their input and output \npins" according to AN642 v0.2 
Text Notes 1300 3900 0    50   ~ 0
434 Mhz Low Pass filter part 1\n
$Comp
L Device:C_Small C11
U 1 1 5D6B8167
P 2950 2950
F 0 "C11" V 2721 2950 50  0000 C CNN
F 1 "150pF" V 2812 2950 50  0000 C CNN
F 2 "" H 2950 2950 50  0001 C CNN
F 3 "~" H 2950 2950 50  0001 C CNN
	1    2950 2950
	0    1    1    0   
$EndComp
$Comp
L Device:Antenna AE1
U 1 1 5D6B791C
P 1500 2350
F 0 "AE1" H 1580 2339 50  0000 L CNN
F 1 "Antenna" H 1580 2248 50  0000 L CNN
F 2 "" H 1500 2350 50  0001 C CNN
F 3 "~" H 1500 2350 50  0001 C CNN
	1    1500 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 2950 1500 2550
Wire Notes Line
	1300 3800 2700 3800
Wire Notes Line
	4400 3850 6400 3850
$Comp
L Device:L L2
U 1 1 5D6B9674
P 2400 2950
F 0 "L2" V 2219 2950 50  0000 C CNN
F 1 "18nH" V 2310 2950 50  0000 C CNN
F 2 "" H 2400 2950 50  0001 C CNN
F 3 "~" H 2400 2950 50  0001 C CNN
	1    2400 2950
	0    1    1    0   
$EndComp
Wire Wire Line
	1500 2950 1650 2950
Wire Wire Line
	2150 2950 2150 3150
Connection ~ 2150 2950
Wire Wire Line
	2150 2950 2250 2950
$Comp
L power:GND #PWR07
U 1 1 5D6BD3AB
P 2150 3500
F 0 "#PWR07" H 2150 3250 50  0001 C CNN
F 1 "GND" H 2155 3327 50  0000 C CNN
F 2 "" H 2150 3500 50  0001 C CNN
F 3 "" H 2150 3500 50  0001 C CNN
	1    2150 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C8
U 1 1 5D6BF899
P 2150 3250
F 0 "C8" H 2242 3296 50  0000 L CNN
F 1 "10pF" H 2242 3205 50  0000 L CNN
F 2 "" H 2150 3250 50  0001 C CNN
F 3 "~" H 2150 3250 50  0001 C CNN
	1    2150 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 3350 2150 3500
Wire Notes Line
	1300 2650 2700 2650
Wire Notes Line
	2700 3800 2700 2650
Wire Notes Line
	1300 2650 1300 3800
Wire Wire Line
	2550 2950 2850 2950
$Comp
L Device:L L9
U 1 1 5D74056F
P 1800 2950
F 0 "L9" V 1619 2950 50  0000 C CNN
F 1 "22nH" V 1710 2950 50  0000 C CNN
F 2 "" H 1800 2950 50  0001 C CNN
F 3 "~" H 1800 2950 50  0001 C CNN
	1    1800 2950
	0    1    1    0   
$EndComp
Wire Wire Line
	1950 2950 2150 2950
Text Notes 1300 6400 0    50   ~ 0
Component values selected for matching network and filters \nfrom AN648 Table 2. Class-E Match Component \nValues vs. Frequency (Split TX/RX Board). L2 and L3 \nadd up to give the value of LM2 in the table. \nNot 100% sure if it will work.
Text Notes 5550 1100 0    50   ~ 0
AN648 section 2.3.2. Component Values for\nDirect Tie Board Configuration. Values taken \nfrom Table 3 for RX side. Must look at\nAN643: Si446x RX LNA Matching for more\nconcrete info.
$EndSCHEMATC
