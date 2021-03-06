EESchema Schematic File Version 2
LIBS:rubi-cpu
LIBS:rubi-ic
LIBS:rubi-discrete
LIBS:rubi-conn
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:puntel-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "18 jul 2017"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LPC11U23FBD48 U3
U 1 1 596C78F7
P 3425 2650
F 0 "U3" H 2375 4100 50  0000 C CNN
F 1 "LPC11U23FBD48" H 2625 1430 50  0000 C CNN
F 2 "LQFP48" H 4375 1450 50  0000 C CNN
F 3 "~" H 3425 1175 50  0001 C CNN
	1    3425 2650
	1    0    0    -1  
$EndComp
$Comp
L WS2812B U7
U 1 1 596C7910
P 9925 5525
F 0 "U7" H 9925 5375 60  0000 C CNN
F 1 "WS2812B" H 9925 5675 50  0000 C CNN
F 2 "~" H 9925 5525 60  0000 C CNN
F 3 "~" H 9925 5525 60  0000 C CNN
	1    9925 5525
	1    0    0    -1  
$EndComp
$Comp
L WS2812B U6
U 1 1 596C792E
P 9925 5025
F 0 "U6" H 9925 4875 60  0000 C CNN
F 1 "WS2812B" H 9925 5175 50  0000 C CNN
F 2 "~" H 9925 5025 60  0000 C CNN
F 3 "~" H 9925 5025 60  0000 C CNN
	1    9925 5025
	1    0    0    -1  
$EndComp
$Comp
L WS2812B U5
U 1 1 596C793D
P 9925 4525
F 0 "U5" H 9925 4375 60  0000 C CNN
F 1 "WS2812B" H 9925 4675 50  0000 C CNN
F 2 "~" H 9925 4525 60  0000 C CNN
F 3 "~" H 9925 4525 60  0000 C CNN
	1    9925 4525
	1    0    0    -1  
$EndComp
Wire Wire Line
	9675 4575 9625 4575
Wire Wire Line
	9625 4575 9625 4775
Wire Wire Line
	9625 4775 10225 4775
Wire Wire Line
	10225 4775 10225 4975
Wire Wire Line
	10225 4975 10175 4975
Wire Wire Line
	9675 5075 9625 5075
Wire Wire Line
	9625 5075 9625 5275
Wire Wire Line
	9625 5275 10225 5275
Wire Wire Line
	10225 5275 10225 5475
Wire Wire Line
	10225 5475 10175 5475
$Comp
L WS2812B U9
U 1 1 596C79CE
P 9925 6525
F 0 "U9" H 9925 6375 60  0000 C CNN
F 1 "WS2812B" H 9925 6675 50  0000 C CNN
F 2 "~" H 9925 6525 60  0000 C CNN
F 3 "~" H 9925 6525 60  0000 C CNN
	1    9925 6525
	1    0    0    -1  
$EndComp
Wire Wire Line
	9675 6075 9625 6075
Wire Wire Line
	9625 6075 9625 6275
Wire Wire Line
	9625 6275 10225 6275
Wire Wire Line
	10225 6275 10225 6475
Wire Wire Line
	10225 6475 10175 6475
$Comp
L WS2812B U8
U 1 1 596C79E1
P 9925 6025
F 0 "U8" H 9925 5875 60  0000 C CNN
F 1 "WS2812B" H 9925 6175 50  0000 C CNN
F 2 "~" H 9925 6025 60  0000 C CNN
F 3 "~" H 9925 6025 60  0000 C CNN
	1    9925 6025
	1    0    0    -1  
$EndComp
Wire Wire Line
	9675 5575 9625 5575
Wire Wire Line
	9625 5575 9625 5775
Wire Wire Line
	9625 5775 10225 5775
Wire Wire Line
	10225 5775 10225 5975
Wire Wire Line
	10225 5975 10175 5975
Wire Wire Line
	9675 6575 9275 6575
Text Label 9325 6575 0    40   ~ 0
Dout
Wire Wire Line
	10175 4475 10475 4475
Text Label 10325 4475 0    40   ~ 0
Din
$Comp
L MINI-USB_SMD J3
U 1 1 596C7A1C
P 7625 5025
F 0 "J3" H 7375 5475 60  0000 C CNN
F 1 "USB-power" H 7575 4525 60  0000 C CNN
F 2 "~" H 7625 5025 60  0000 C CNN
F 3 "~" H 7625 5025 60  0000 C CNN
	1    7625 5025
	1    0    0    -1  
$EndComp
$Comp
L MINI-USB_SMD J4
U 1 1 596C7A36
P 7625 6175
F 0 "J4" H 7375 6625 60  0000 C CNN
F 1 "USB-comm" H 7575 5675 60  0000 C CNN
F 2 "~" H 7625 6175 60  0000 C CNN
F 3 "~" H 7625 6175 60  0000 C CNN
	1    7625 6175
	1    0    0    -1  
$EndComp
Wire Wire Line
	7075 4725 6725 4725
Wire Wire Line
	6725 4725 6725 4525
$Comp
L +5V #PWR01
U 1 1 596C7A81
P 6725 4525
F 0 "#PWR01" H 6725 4615 20  0001 C CNN
F 1 "+5V" H 6725 4615 30  0000 C CNN
F 2 "" H 6725 4525 60  0000 C CNN
F 3 "" H 6725 4525 60  0000 C CNN
	1    6725 4525
	1    0    0    -1  
$EndComp
NoConn ~ 8175 4725
NoConn ~ 8175 4875
NoConn ~ 8175 5175
NoConn ~ 8175 5325
NoConn ~ 8175 5875
NoConn ~ 8175 6025
NoConn ~ 8175 6325
NoConn ~ 8175 6475
$Comp
L SOLDER-JUMPER JS1
U 1 1 596C7A9D
P 6675 5875
F 0 "JS1" H 6675 6025 60  0000 C CNN
F 1 "SOLDER-JUMPER" H 6675 5775 30  0001 C CNN
F 2 "solder-jumper" H 6725 5725 10  0001 C CNN
F 3 "~" H 6675 5875 60  0000 C CNN
	1    6675 5875
	1    0    0    -1  
$EndComp
Wire Wire Line
	6775 5875 7075 5875
Wire Wire Line
	6575 5875 6425 5875
Wire Wire Line
	6425 5875 6425 5625
$Comp
L +5V #PWR02
U 1 1 596C7AE8
P 6425 5625
F 0 "#PWR02" H 6425 5715 20  0001 C CNN
F 1 "+5V" H 6425 5715 30  0000 C CNN
F 2 "" H 6425 5625 60  0000 C CNN
F 3 "" H 6425 5625 60  0000 C CNN
	1    6425 5625
	1    0    0    -1  
$EndComp
Wire Wire Line
	7075 5325 6925 5325
Wire Wire Line
	6925 5325 6925 5525
$Comp
L GND #PWR03
U 1 1 596C7B0D
P 6925 5525
F 0 "#PWR03" H 6925 5525 30  0001 C CNN
F 1 "GND" H 6925 5455 30  0001 C CNN
F 2 "" H 6925 5525 60  0000 C CNN
F 3 "" H 6925 5525 60  0000 C CNN
	1    6925 5525
	1    0    0    -1  
$EndComp
Wire Wire Line
	7075 6475 6925 6475
Wire Wire Line
	6925 6475 6925 6675
$Comp
L GND #PWR04
U 1 1 596C7B1C
P 6925 6675
F 0 "#PWR04" H 6925 6675 30  0001 C CNN
F 1 "GND" H 6925 6605 30  0001 C CNN
F 2 "" H 6925 6675 60  0000 C CNN
F 3 "" H 6925 6675 60  0000 C CNN
	1    6925 6675
	1    0    0    -1  
$EndComp
NoConn ~ 7075 4875
NoConn ~ 7075 5025
NoConn ~ 7075 5175
NoConn ~ 7075 6325
Wire Wire Line
	7075 6025 6825 6025
Wire Wire Line
	7075 6175 6825 6175
Text Label 6875 6175 0    40   ~ 0
DP
Text Label 6875 6025 0    40   ~ 0
DM
$Comp
L LED D2
U 1 1 596C812D
P 10000 1375
F 0 "D2" H 10400 1375 50  0000 C CNN
F 1 "red" H 10000 1275 50  0000 C CNN
F 2 "~" H 10000 1375 60  0000 C CNN
F 3 "~" H 10000 1375 60  0000 C CNN
	1    10000 1375
	1    0    0    -1  
$EndComp
$Comp
L LED D3
U 1 1 596C8133
P 10000 1600
F 0 "D3" H 10400 1600 50  0000 C CNN
F 1 "yellow" H 10000 1500 50  0000 C CNN
F 2 "~" H 10000 1600 60  0000 C CNN
F 3 "~" H 10000 1600 60  0000 C CNN
	1    10000 1600
	1    0    0    -1  
$EndComp
$Comp
L LED D4
U 1 1 596C8139
P 10000 1825
F 0 "D4" H 10400 1825 50  0000 C CNN
F 1 "green" H 10000 1725 50  0000 C CNN
F 2 "~" H 10000 1825 60  0000 C CNN
F 3 "~" H 10000 1825 60  0000 C CNN
	1    10000 1825
	1    0    0    -1  
$EndComp
$Comp
L R-SMALL R5
U 1 1 596C813F
P 9625 1375
F 0 "R5" H 9525 1475 60  0000 C CNN
F 1 "1k" H 9625 1375 40  0000 C CNN
F 2 "~" H 9625 1375 60  0000 C CNN
F 3 "~" H 9625 1375 60  0000 C CNN
	1    9625 1375
	1    0    0    -1  
$EndComp
$Comp
L R-SMALL R6
U 1 1 596C8145
P 9625 1600
F 0 "R6" H 9525 1700 60  0000 C CNN
F 1 "470" H 9625 1600 40  0000 C CNN
F 2 "~" H 9625 1600 60  0000 C CNN
F 3 "~" H 9625 1600 60  0000 C CNN
	1    9625 1600
	1    0    0    -1  
$EndComp
$Comp
L R-SMALL R7
U 1 1 596C814B
P 9625 1825
F 0 "R7" H 9525 1925 60  0000 C CNN
F 1 "470" H 9625 1825 40  0000 C CNN
F 2 "~" H 9625 1825 60  0000 C CNN
F 3 "~" H 9625 1825 60  0000 C CNN
	1    9625 1825
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 596C8151
P 10300 1925
F 0 "#PWR05" H 10300 1925 30  0001 C CNN
F 1 "GND" H 10300 1855 30  0001 C CNN
F 2 "" H 10300 1925 60  0000 C CNN
F 3 "" H 10300 1925 60  0000 C CNN
	1    10300 1925
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 1825 10300 1825
Connection ~ 10300 1825
Wire Wire Line
	9475 1375 9200 1375
Wire Wire Line
	9475 1600 9200 1600
Text Label 9250 1600 0    40   ~ 0
YLED
Wire Wire Line
	9475 1825 9200 1825
Text Label 9250 1825 0    40   ~ 0
GLED
Wire Wire Line
	9775 1375 9800 1375
Wire Wire Line
	9800 1600 9775 1600
Wire Wire Line
	9775 1825 9800 1825
Wire Wire Line
	10200 1375 10300 1375
Wire Wire Line
	10300 1125 10300 1925
Text Notes 1000 4700 0    60   ~ 12
Microcontroller
$Comp
L AP2111H U1
U 1 1 596C8180
P 7600 1250
F 0 "U1" H 7600 1400 60  0000 C CNN
F 1 "AP2111H" H 7600 1650 60  0000 C CNN
F 2 "~" H 7600 1250 60  0000 C CNN
F 3 "~" H 7600 1250 60  0000 C CNN
	1    7600 1250
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 596C8186
P 7800 1700
F 0 "#PWR06" H 7800 1700 30  0001 C CNN
F 1 "GND" H 7800 1630 30  0001 C CNN
F 2 "" H 7800 1700 60  0000 C CNN
F 3 "" H 7800 1700 60  0000 C CNN
	1    7800 1700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7400 1600 7400 1500
$Comp
L INDUCTOR_SMALL L1
U 1 1 596C818D
P 7150 1250
F 0 "L1" V 6900 1300 50  0000 C CNN
F 1 "10u" V 6750 1250 50  0000 C CNN
F 2 "~" H 7150 1250 60  0000 C CNN
F 3 "~" H 7150 1250 60  0000 C CNN
	1    7150 1250
	0    1    -1   0   
$EndComp
$Comp
L C C2
U 1 1 596C8193
P 7300 2000
F 0 "C2" H 7300 2100 40  0000 L CNN
F 1 "22" H 7306 1915 40  0000 L CNN
F 2 "~" H 7338 1850 30  0000 C CNN
F 3 "~" H 7300 2000 60  0000 C CNN
	1    7300 2000
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 596C8199
P 7300 2200
F 0 "#PWR07" H 7300 2200 30  0001 C CNN
F 1 "GND" H 7300 2130 30  0001 C CNN
F 2 "" H 7300 2200 60  0000 C CNN
F 3 "" H 7300 2200 60  0000 C CNN
	1    7300 2200
	-1   0    0    -1  
$EndComp
Text Notes 7300 950  2    40   ~ 0
0805\n
$Comp
L C C1
U 1 1 596C81A0
P 7025 1875
F 0 "C1" H 7025 1975 40  0000 L CNN
F 1 "22" H 7031 1790 40  0000 L CNN
F 2 "~" H 7063 1725 30  0000 C CNN
F 3 "~" H 7025 1875 60  0000 C CNN
	1    7025 1875
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 596C81A6
P 7025 2075
F 0 "#PWR08" H 7025 2075 30  0001 C CNN
F 1 "GND" H 7025 2005 30  0001 C CNN
F 2 "" H 7025 2075 60  0000 C CNN
F 3 "" H 7025 2075 60  0000 C CNN
	1    7025 2075
	-1   0    0    -1  
$EndComp
$Comp
L R-SMALL R1
U 1 1 596C81AC
P 6900 1050
F 0 "R1" V 6775 925 60  0000 C CNN
F 1 "1R0" H 6900 1050 40  0000 C CNN
F 2 "~" H 6900 1050 60  0000 C CNN
F 3 "~" H 6900 1050 60  0000 C CNN
	1    6900 1050
	0    -1   1    0   
$EndComp
Wire Wire Line
	7150 1000 7050 1000
Text Notes 7100 850  2    40   ~ 0
0805\n
Wire Wire Line
	7025 1600 7400 1600
Wire Wire Line
	7150 1600 7150 1500
Wire Wire Line
	6900 800  6900 900 
Connection ~ 7150 1600
Wire Wire Line
	6900 1200 7050 1200
Wire Wire Line
	7050 1200 7050 1000
Wire Wire Line
	7600 1800 7300 1800
Connection ~ 7600 1800
Wire Wire Line
	7800 2175 7800 2075
$Comp
L +3.3V #PWR09
U 1 1 596C81BD
P 7800 2075
F 0 "#PWR09" H 7800 2035 30  0001 C CNN
F 1 "+3.3V" H 7800 2185 30  0000 C CNN
F 2 "" H 7800 2075 60  0001 C CNN
F 3 "" H 7800 2075 60  0001 C CNN
	1    7800 2075
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 1500 7800 1700
$Comp
L +5V #PWR010
U 1 1 596C81C4
P 6900 800
F 0 "#PWR010" H 6900 890 20  0001 C CNN
F 1 "+5V" H 6900 890 30  0000 C CNN
F 2 "" H 6900 800 60  0000 C CNN
F 3 "" H 6900 800 60  0000 C CNN
	1    6900 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7025 1600 7025 1675
Text Notes 6450 2550 0    60   ~ 12
3.3V Regulator
Wire Wire Line
	7600 2175 7800 2175
Wire Wire Line
	3325 1150 3325 950 
Wire Wire Line
	3525 950  3525 1150
Wire Wire Line
	3425 825  4825 825 
Connection ~ 3425 950 
Wire Wire Line
	3325 3950 3325 4100
Wire Wire Line
	3325 4100 3525 4100
Wire Wire Line
	3525 4100 3525 3950
Connection ~ 3425 4100
$Comp
L GND #PWR011
U 1 1 596C81EB
P 3425 4500
F 0 "#PWR011" H 3425 4500 30  0001 C CNN
F 1 "GND" H 3425 4430 30  0001 C CNN
F 2 "" H 3425 4500 60  0000 C CNN
F 3 "" H 3425 4500 60  0000 C CNN
	1    3425 4500
	1    0    0    -1  
$EndComp
$Comp
L R-SMALL R8
U 1 1 596C81F1
P 5025 3100
F 0 "R8" H 4925 3200 60  0000 C CNN
F 1 "33" H 5025 3100 40  0000 C CNN
F 2 "~" H 5025 3100 60  0000 C CNN
F 3 "~" H 5025 3100 60  0000 C CNN
	1    5025 3100
	1    0    0    -1  
$EndComp
$Comp
L R-SMALL R9
U 1 1 596C81F7
P 5025 3300
F 0 "R9" H 4925 3400 60  0000 C CNN
F 1 "33" H 5025 3300 40  0000 C CNN
F 2 "~" H 5025 3300 60  0000 C CNN
F 3 "~" H 5025 3300 60  0000 C CNN
	1    5025 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4725 3150 4625 3150
Wire Wire Line
	4725 2950 4725 3150
Wire Wire Line
	4725 3100 4875 3100
Wire Wire Line
	4625 3250 4725 3250
Wire Wire Line
	4725 3250 4725 3300
Wire Wire Line
	4725 3300 4875 3300
Wire Wire Line
	5175 3100 5375 3100
Wire Wire Line
	5175 3300 5375 3300
Text Label 1975 1350 0    40   ~ 0
RST*
Text Label 1975 3250 0    40   ~ 0
TXD
Text Label 1975 3150 0    40   ~ 0
RXD
Text Label 1975 1750 0    40   ~ 0
SCL
Text Label 1975 1850 0    40   ~ 0
SDA
Text Label 1975 2150 0    40   ~ 0
MISO
Text Label 1975 2250 0    40   ~ 0
MOSI
Text Label 1975 2350 0    40   ~ 0
SCK
Text Label 4675 1750 0    40   ~ 0
SSEL
Wire Wire Line
	1500 3250 2225 3250
Wire Wire Line
	1600 3150 2225 3150
Wire Wire Line
	1875 2150 2225 2150
Wire Wire Line
	1875 2250 2225 2250
Wire Wire Line
	1875 2350 2225 2350
Wire Wire Line
	4975 1750 4625 1750
Wire Wire Line
	1875 1750 2225 1750
Wire Wire Line
	1875 1850 2225 1850
$Comp
L CLOCK-MODULE U4
U 1 1 596C8236
P 4175 4300
F 0 "U4" H 4175 4300 60  0000 C CNN
F 1 "CLOCK-MODULE" H 4175 4050 60  0000 C CNN
F 2 "~" H 4175 4300 60  0000 C CNN
F 3 "~" H 4175 4300 60  0000 C CNN
	1    4175 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5125 4200 4775 4200
Wire Wire Line
	4625 3550 4825 3550
Wire Wire Line
	4825 4400 4775 4400
Wire Wire Line
	3575 4400 3425 4400
Connection ~ 3425 4400
NoConn ~ 3575 4200
$Comp
L CSMALL C4
U 1 1 596C8242
P 4025 1025
F 0 "C4" H 4050 1075 30  0000 L CNN
F 1 "100" H 4050 975 30  0000 L CNN
F 2 "~" H 4025 1025 60  0000 C CNN
F 3 "~" H 4025 1025 60  0000 C CNN
	1    4025 1025
	1    0    0    -1  
$EndComp
$Comp
L CSMALL C5
U 1 1 596C8248
P 4375 1025
F 0 "C5" H 4400 1075 30  0000 L CNN
F 1 "100" H 4400 975 30  0000 L CNN
F 2 "~" H 4375 1025 60  0000 C CNN
F 3 "~" H 4375 1025 60  0000 C CNN
	1    4375 1025
	1    0    0    -1  
$EndComp
Wire Wire Line
	4025 925  4025 825 
Connection ~ 4025 825 
Wire Wire Line
	4375 825  4375 925 
Connection ~ 4375 825 
$Comp
L GND #PWR012
U 1 1 596C8252
P 4025 1125
F 0 "#PWR012" H 4025 1125 30  0001 C CNN
F 1 "GND" H 4025 1055 30  0001 C CNN
F 2 "" H 4025 1125 60  0000 C CNN
F 3 "" H 4025 1125 60  0000 C CNN
	1    4025 1125
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 596C8258
P 4375 1125
F 0 "#PWR013" H 4375 1125 30  0001 C CNN
F 1 "GND" H 4375 1055 30  0001 C CNN
F 2 "" H 4375 1125 60  0000 C CNN
F 3 "" H 4375 1125 60  0000 C CNN
	1    4375 1125
	1    0    0    -1  
$EndComp
NoConn ~ 4625 1850
NoConn ~ 4625 1950
NoConn ~ 4625 2050
NoConn ~ 4625 2150
NoConn ~ 4625 2450
NoConn ~ 4625 2750
NoConn ~ 4625 2850
NoConn ~ 4625 3650
NoConn ~ 2225 3650
NoConn ~ 2225 3550
NoConn ~ 2225 3350
NoConn ~ 2225 3050
NoConn ~ 2225 2450
NoConn ~ 2225 2050
$Comp
L 3906 Q1
U 1 1 596C826D
P 5475 2500
F 0 "Q1" H 5525 2500 60  0000 C CNN
F 1 "DTA114" H 5300 2725 60  0000 C CNN
F 2 "~" H 5475 2700 60  0000 C CNN
F 3 "~" H 5475 2700 60  0000 C CNN
	1    5475 2500
	1    0    0    -1  
$EndComp
Text Label 5175 2500 0    40   ~ 0
USBC*
Wire Wire Line
	5525 2350 5525 2200
$Comp
L R-SMALL R10
U 1 1 596C8275
P 5525 2800
F 0 "R10" V 5575 2650 60  0000 C CNN
F 1 "1k5" H 5525 2800 40  0000 C CNN
F 2 "~" H 5525 2800 60  0000 C CNN
F 3 "~" H 5525 2800 60  0000 C CNN
	1    5525 2800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5175 2500 5375 2500
Wire Wire Line
	2225 1950 1875 1950
Text Label 1975 1950 0    40   ~ 0
USBC*
Wire Wire Line
	5525 2950 4725 2950
Connection ~ 4725 3100
Wire Wire Line
	1950 1350 2225 1350
Wire Wire Line
	2225 1450 1950 1450
Text Label 1975 1450 0    40   ~ 0
PRG*
Wire Wire Line
	3425 4100 3425 4500
Wire Wire Line
	4825 3550 4825 4400
Text Label 5275 3100 0    40   ~ 0
DP
Text Label 5275 3300 0    40   ~ 0
DM
$Comp
L +3.3V #PWR014
U 1 1 596C8287
P 5525 2200
F 0 "#PWR014" H 5525 2160 30  0001 C CNN
F 1 "+3.3V" H 5525 2310 30  0000 C CNN
F 2 "" H 5525 2200 60  0001 C CNN
F 3 "" H 5525 2200 60  0001 C CNN
	1    5525 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 1500 7600 2175
Wire Wire Line
	3425 825  3425 950 
Wire Wire Line
	3325 950  3525 950 
$Comp
L +3.3V #PWR015
U 1 1 596C8290
P 4825 825
F 0 "#PWR015" H 4825 785 30  0001 C CNN
F 1 "+3.3V" H 4825 935 30  0000 C CNN
F 2 "" H 4825 825 60  0001 C CNN
F 3 "" H 4825 825 60  0001 C CNN
	1    4825 825 
	1    0    0    -1  
$EndComp
$Comp
L R-SMALL R3
U 1 1 596C8296
P 1725 1850
F 0 "R3" H 1675 1750 60  0000 C CNN
F 1 "1K5" H 1725 1850 40  0000 C CNN
F 2 "~" H 1725 1850 60  0000 C CNN
F 3 "~" H 1725 1850 60  0000 C CNN
	1    1725 1850
	1    0    0    -1  
$EndComp
$Comp
L R-SMALL R2
U 1 1 596C829C
P 1725 1750
F 0 "R2" H 1525 1800 60  0000 C CNN
F 1 "1K5" H 1725 1750 40  0000 C CNN
F 2 "~" H 1725 1750 60  0000 C CNN
F 3 "~" H 1725 1750 60  0000 C CNN
	1    1725 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1575 1750 1575 1850
Wire Wire Line
	1400 1800 1575 1800
Wire Wire Line
	1400 1550 1400 1800
Connection ~ 1575 1800
$Comp
L +3.3V #PWR016
U 1 1 596C82A6
P 1400 1550
F 0 "#PWR016" H 1400 1510 30  0001 C CNN
F 1 "+3.3V" H 1400 1660 30  0000 C CNN
F 2 "" H 1400 1550 60  0001 C CNN
F 3 "" H 1400 1550 60  0001 C CNN
	1    1400 1550
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR017
U 1 1 596C82B2
P 5125 4200
F 0 "#PWR017" H 5125 4160 30  0001 C CNN
F 1 "+3.3V" H 5125 4310 30  0000 C CNN
F 2 "" H 5125 4200 60  0001 C CNN
F 3 "" H 5125 4200 60  0001 C CNN
	1    5125 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2225 3450 1750 3450
Text Label 1900 3450 0    40   ~ 0
W1
Wire Wire Line
	1400 1650 2225 1650
Connection ~ 1400 1650
Wire Wire Line
	2225 2650 1950 2650
Text Label 2000 2750 0    40   ~ 0
RLED
Wire Wire Line
	2225 2550 1950 2550
Text Label 2000 2650 0    40   ~ 0
YLED
NoConn ~ 4625 1350
NoConn ~ 4625 1450
NoConn ~ 4625 1550
NoConn ~ 4625 2250
NoConn ~ 4625 2550
NoConn ~ 2225 2850
NoConn ~ 2225 2950
$Comp
L BUTTON SW1
U 1 1 596C8982
P 9450 3000
F 0 "SW1" H 9450 3000 60  0000 C CNN
F 1 "BUTTON" H 9450 2850 60  0000 C CNN
F 2 "~" H 9450 3000 60  0000 C CNN
F 3 "~" H 9450 3000 60  0000 C CNN
	1    9450 3000
	1    0    0    -1  
$EndComp
$Comp
L BUTTON SW2
U 1 1 596C8988
P 10050 3000
F 0 "SW2" H 10050 3000 60  0000 C CNN
F 1 "BUTTON" H 10050 2850 60  0000 C CNN
F 2 "~" H 10050 3000 60  0000 C CNN
F 3 "~" H 10050 3000 60  0000 C CNN
	1    10050 3000
	1    0    0    -1  
$EndComp
Connection ~ 9950 3350
Wire Wire Line
	9350 3350 10150 3350
Connection ~ 9550 3350
Wire Wire Line
	9750 3350 9750 3500
Connection ~ 9750 3350
$Comp
L GND #PWR018
U 1 1 596C8993
P 9750 3500
F 0 "#PWR018" H 9750 3500 30  0001 C CNN
F 1 "GND" H 9750 3430 30  0001 C CNN
F 2 "" H 9750 3500 60  0000 C CNN
F 3 "" H 9750 3500 60  0000 C CNN
	1    9750 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 2800 9550 2800
Text Label 9200 2800 0    40   ~ 0
RST*
Connection ~ 9350 2800
Wire Wire Line
	10150 2800 9750 2800
Text Label 9800 2800 0    40   ~ 0
PRG*
Connection ~ 9950 2800
Wire Wire Line
	10200 1600 10300 1600
Connection ~ 10300 1600
$Comp
L LED D1
U 1 1 596C8A43
P 10000 1125
F 0 "D1" H 10400 1125 50  0000 C CNN
F 1 "red" H 10000 1025 50  0000 C CNN
F 2 "~" H 10000 1125 60  0000 C CNN
F 3 "~" H 10000 1125 60  0000 C CNN
	1    10000 1125
	1    0    0    -1  
$EndComp
$Comp
L R-SMALL R4
U 1 1 596C8A49
P 9625 1125
F 0 "R4" H 9525 1225 60  0000 C CNN
F 1 "4k7" H 9625 1125 40  0000 C CNN
F 2 "~" H 9625 1125 60  0000 C CNN
F 3 "~" H 9625 1125 60  0000 C CNN
	1    9625 1125
	1    0    0    -1  
$EndComp
Wire Wire Line
	9475 1125 9200 1125
Wire Wire Line
	9200 1125 9200 1000
Wire Wire Line
	9775 1125 9800 1125
Wire Wire Line
	10200 1125 10300 1125
Text Label 9250 1375 0    40   ~ 0
RLED
Wire Wire Line
	1950 2750 2225 2750
Text Label 2000 2550 0    40   ~ 0
GLED
$Comp
L STRIP-3 J2
U 1 1 596C8B08
P 1500 3025
F 0 "J2" H 1250 3025 60  0000 C CNN
F 1 "STRIP-3" H 1500 3125 60  0000 C CNN
F 2 "~" H 1450 3025 60  0000 C CNN
F 3 "~" H 1450 3025 60  0000 C CNN
	1    1500 3025
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 3075 1400 3225
$Comp
L GND #PWR019
U 1 1 596C8C83
P 1400 3225
F 0 "#PWR019" H 1400 3225 30  0001 C CNN
F 1 "GND" H 1400 3155 30  0001 C CNN
F 2 "" H 1400 3225 60  0000 C CNN
F 3 "" H 1400 3225 60  0000 C CNN
	1    1400 3225
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 3075 1600 3150
Wire Wire Line
	1500 3075 1500 3250
Connection ~ 10300 1375
Wire Wire Line
	9425 4250 9425 6475
$Comp
L +5V #PWR020
U 1 1 596C8FF6
P 9425 4250
F 0 "#PWR020" H 9425 4340 20  0001 C CNN
F 1 "+5V" H 9425 4340 30  0000 C CNN
F 2 "" H 9425 4250 60  0000 C CNN
F 3 "" H 9425 4250 60  0000 C CNN
	1    9425 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9425 4475 9675 4475
Wire Wire Line
	9425 4975 9675 4975
Connection ~ 9425 4475
Wire Wire Line
	9425 5475 9675 5475
Connection ~ 9425 4975
Wire Wire Line
	9425 5975 9675 5975
Connection ~ 9425 5475
Wire Wire Line
	9425 6475 9675 6475
Connection ~ 9425 5975
Wire Wire Line
	10175 6575 10350 6575
Wire Wire Line
	10350 4575 10350 6725
$Comp
L GND #PWR021
U 1 1 596C94DB
P 10350 6725
F 0 "#PWR021" H 10350 6725 30  0001 C CNN
F 1 "GND" H 10350 6655 30  0001 C CNN
F 2 "" H 10350 6725 60  0000 C CNN
F 3 "" H 10350 6725 60  0000 C CNN
	1    10350 6725
	1    0    0    -1  
$EndComp
Wire Wire Line
	10350 4575 10175 4575
Connection ~ 10350 6575
Wire Wire Line
	10175 5075 10350 5075
Connection ~ 10350 5075
Wire Wire Line
	10175 5575 10350 5575
Connection ~ 10350 5575
Wire Wire Line
	10175 6075 10350 6075
Connection ~ 10350 6075
$Comp
L STRIP-4 J5
U 1 1 596C97D6
P 7025 3425
F 0 "J5" V 6725 3425 60  0000 C CNN
F 1 "STRIP-4" H 7025 3525 60  0000 C CNN
F 2 "~" H 6925 3425 60  0000 C CNN
F 3 "~" H 6925 3425 60  0000 C CNN
	1    7025 3425
	0    -1   -1   0   
$EndComp
$Comp
L STRIP-4 J6
U 1 1 596C97E5
P 7850 3425
F 0 "J6" V 7550 3425 60  0000 C CNN
F 1 "STRIP-4" H 7850 3525 60  0000 C CNN
F 2 "~" H 7750 3425 60  0000 C CNN
F 3 "~" H 7750 3425 60  0000 C CNN
	1    7850 3425
	0    1    -1   0   
$EndComp
Wire Wire Line
	7075 3575 7800 3575
Wire Wire Line
	7075 3475 7800 3475
Wire Wire Line
	7075 3375 7800 3375
Wire Wire Line
	7075 3275 7800 3275
Wire Wire Line
	7400 3275 7400 3075
Connection ~ 7400 3275
$Comp
L +5V #PWR022
U 1 1 596C9C93
P 7400 3075
F 0 "#PWR022" H 7400 3165 20  0001 C CNN
F 1 "+5V" H 7400 3165 30  0000 C CNN
F 2 "" H 7400 3075 60  0000 C CNN
F 3 "" H 7400 3075 60  0000 C CNN
	1    7400 3075
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 596C9CA2
P 7400 3775
F 0 "#PWR023" H 7400 3775 30  0001 C CNN
F 1 "GND" H 7400 3705 30  0001 C CNN
F 2 "" H 7400 3775 60  0000 C CNN
F 3 "" H 7400 3775 60  0000 C CNN
	1    7400 3775
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 3575 7400 3775
Connection ~ 7400 3575
Text Label 7275 3375 0    40   ~ 0
Din
Text Label 7400 3475 0    40   ~ 0
Dout
NoConn ~ 2225 1550
NoConn ~ 4625 1650
Wire Wire Line
	4625 2350 4900 2350
Text Label 4750 2350 0    40   ~ 0
Din
$Comp
L LM75 U10
U 1 1 596D0A7C
P 1950 5450
F 0 "U10" H 1950 5150 60  0000 C CNN
F 1 "LM75BD" H 1950 5700 60  0000 C CNN
F 2 "~" H 1950 5450 60  0000 C CNN
F 3 "~" H 1950 5450 60  0000 C CNN
	1    1950 5450
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR024
U 1 1 596D0A82
P 2400 5175
F 0 "#PWR024" H 2400 5135 30  0001 C CNN
F 1 "+3.3V" H 2400 5285 30  0000 C CNN
F 2 "" H 2400 5175 60  0001 C CNN
F 3 "" H 2400 5175 60  0001 C CNN
	1    2400 5175
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 5300 2650 5300
Text Label 1350 5300 0    40   ~ 0
SDA
Text Label 1350 5400 0    40   ~ 0
SCL
Wire Wire Line
	1300 5400 1600 5400
Wire Wire Line
	1300 5300 1600 5300
$Comp
L GND #PWR025
U 1 1 596D0A8E
P 1500 5750
F 0 "#PWR025" H 1500 5750 30  0001 C CNN
F 1 "GND" H 1500 5680 30  0001 C CNN
F 2 "" H 1500 5750 60  0000 C CNN
F 3 "" H 1500 5750 60  0000 C CNN
	1    1500 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 5600 1500 5600
Wire Wire Line
	1500 5600 1500 5750
$Comp
L GND #PWR026
U 1 1 596D0A96
P 2450 5750
F 0 "#PWR026" H 2450 5750 30  0001 C CNN
F 1 "GND" H 2450 5680 30  0001 C CNN
F 2 "" H 2450 5750 60  0000 C CNN
F 3 "" H 2450 5750 60  0000 C CNN
	1    2450 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 5750 2450 5400
Wire Wire Line
	2450 5400 2300 5400
Wire Wire Line
	2300 5500 2450 5500
Connection ~ 2450 5500
Wire Wire Line
	2300 5600 2650 5600
Connection ~ 2450 5600
NoConn ~ 1600 5500
Text Notes 1250 6050 0    60   ~ 0
Thermo: Bus address 0x48 (90/91)
Text Notes 3875 7450 0    60   ~ 0
Accel: Bus address 0x1d (3a/3b)
$Comp
L MMA8653 U11
U 1 1 596D0AA5
P 4650 6750
F 0 "U11" H 4650 6450 60  0000 C CNN
F 1 "MMA8653" H 4650 7050 60  0000 C CNN
F 2 "~" H 4850 6450 60  0000 C CNN
F 3 "~" H 4850 6450 60  0000 C CNN
	1    4650 6750
	1    0    0    -1  
$EndComp
$Comp
L CSMALL C6
U 1 1 596D0AAB
P 2650 5400
F 0 "C6" H 2675 5450 30  0000 L CNN
F 1 "100n" H 2675 5350 30  0000 L CNN
F 2 "~" H 2650 5400 60  0000 C CNN
F 3 "~" H 2650 5400 60  0000 C CNN
	1    2650 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 5600 2650 5500
Connection ~ 2400 5300
$Comp
L CSMALL C7
U 1 1 596D0AB3
P 3850 6700
F 0 "C7" H 3875 6750 30  0000 L CNN
F 1 "100n" H 3875 6650 30  0000 L CNN
F 2 "~" H 3850 6700 60  0000 C CNN
F 3 "~" H 3850 6700 60  0000 C CNN
	1    3850 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 6800 3850 7100
$Comp
L +3.3V #PWR027
U 1 1 596D0ABA
P 3850 6450
F 0 "#PWR027" H 3850 6410 30  0001 C CNN
F 1 "+3.3V" H 3850 6560 30  0000 C CNN
F 2 "" H 3850 6450 60  0001 C CNN
F 3 "" H 3850 6450 60  0001 C CNN
	1    3850 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 6550 3850 6550
Connection ~ 3850 6550
Wire Wire Line
	3850 7100 5450 7100
Wire Wire Line
	5200 7100 5200 6650
Wire Wire Line
	5200 6650 5050 6650
Wire Wire Line
	5050 6850 5050 6950
Wire Wire Line
	5050 6900 5200 6900
Connection ~ 5200 6900
Connection ~ 5050 6900
Wire Wire Line
	4000 6650 4250 6650
Text Label 4050 6650 0    40   ~ 0
SCL
Wire Wire Line
	5050 6550 5350 6550
Text Label 5100 6550 0    40   ~ 0
SDA
$Comp
L CSMALL C12
U 1 1 596D0ACE
P 5450 6950
F 0 "C12" H 5475 7000 30  0000 L CNN
F 1 "100n" H 5475 6900 30  0000 L CNN
F 2 "~" H 5450 6950 60  0000 C CNN
F 3 "~" H 5450 6950 60  0000 C CNN
	1    5450 6950
	1    0    0    -1  
$EndComp
$Comp
L CSMALL C9
U 1 1 596D0AD4
P 4050 7000
F 0 "C9" H 4075 7050 30  0000 L CNN
F 1 "100n" H 4075 6950 30  0000 L CNN
F 2 "~" H 4050 7000 60  0000 C CNN
F 3 "~" H 4050 7000 60  0000 C CNN
	1    4050 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 6900 4050 6850
Wire Wire Line
	4050 6850 4250 6850
NoConn ~ 4250 6750
NoConn ~ 4250 6950
Wire Wire Line
	5050 6750 5450 6750
Connection ~ 5450 6750
Wire Wire Line
	5450 7100 5450 7050
Connection ~ 5200 7100
Wire Wire Line
	4350 7100 4350 7200
Connection ~ 4350 7100
$Comp
L GND #PWR028
U 1 1 596D0AE5
P 4350 7200
F 0 "#PWR028" H 4350 7200 30  0001 C CNN
F 1 "GND" H 4350 7130 30  0001 C CNN
F 2 "" H 4350 7200 60  0000 C CNN
F 3 "" H 4350 7200 60  0000 C CNN
	1    4350 7200
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR029
U 1 1 596D0AEB
P 5450 6450
F 0 "#PWR029" H 5450 6410 30  0001 C CNN
F 1 "+3.3V" H 5450 6560 30  0000 C CNN
F 2 "" H 5450 6450 60  0001 C CNN
F 3 "" H 5450 6450 60  0001 C CNN
	1    5450 6450
	1    0    0    -1  
$EndComp
$Comp
L 24AA64F U2
U 1 1 596D0AF1
P 2100 6550
F 0 "U2" H 2100 6250 60  0000 C CNN
F 1 "24AA64F" H 2100 6800 60  0000 C CNN
F 2 "~" H 2100 6550 60  0000 C CNN
F 3 "~" H 2100 6550 60  0000 C CNN
	1    2100 6550
	1    0    0    -1  
$EndComp
Text Notes 1350 7075 0    60   ~ 0
EEPROM: Bus address 0x57 (ae/af)
$Comp
L +3.3V #PWR030
U 1 1 596D0AF8
P 1400 6450
F 0 "#PWR030" H 1400 6410 30  0001 C CNN
F 1 "+3.3V" H 1400 6560 30  0000 C CNN
F 2 "" H 1400 6450 60  0001 C CNN
F 3 "" H 1400 6450 60  0001 C CNN
	1    1400 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 6400 1550 6400
Wire Wire Line
	1550 6400 1550 6600
Wire Wire Line
	1550 6600 1750 6600
Wire Wire Line
	1750 6500 1550 6500
Connection ~ 1550 6500
Wire Wire Line
	1550 6550 1400 6550
Wire Wire Line
	1400 6550 1400 6450
Connection ~ 1550 6550
Wire Wire Line
	1250 6700 1750 6700
Wire Wire Line
	1400 6700 1400 6750
$Comp
L GND #PWR031
U 1 1 596D0B08
P 1400 6750
F 0 "#PWR031" H 1400 6750 30  0001 C CNN
F 1 "GND" H 1400 6680 30  0001 C CNN
F 2 "" H 1400 6750 60  0000 C CNN
F 3 "" H 1400 6750 60  0000 C CNN
	1    1400 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 6500 2900 6500
Wire Wire Line
	2900 6500 2900 6650
$Comp
L GND #PWR032
U 1 1 596D0B10
P 2900 6650
F 0 "#PWR032" H 2900 6650 30  0001 C CNN
F 1 "GND" H 2900 6580 30  0001 C CNN
F 2 "" H 2900 6650 60  0000 C CNN
F 3 "" H 2900 6650 60  0000 C CNN
	1    2900 6650
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR033
U 1 1 596D0B16
P 2650 6350
F 0 "#PWR033" H 2650 6310 30  0001 C CNN
F 1 "+3.3V" H 2650 6460 30  0000 C CNN
F 2 "" H 2650 6350 60  0001 C CNN
F 3 "" H 2650 6350 60  0001 C CNN
	1    2650 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 6350 2650 6400
Wire Wire Line
	2650 6400 2450 6400
Wire Wire Line
	2450 6600 2700 6600
Wire Wire Line
	2450 6700 2700 6700
$Comp
L CSMALL C3
U 1 1 596D0B20
P 1250 6600
F 0 "C3" H 1275 6650 30  0000 L CNN
F 1 "100n" H 1275 6550 30  0000 L CNN
F 2 "~" H 1250 6600 60  0000 C CNN
F 3 "~" H 1250 6600 60  0000 C CNN
	1    1250 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 6500 1400 6500
Connection ~ 1400 6500
Connection ~ 1400 6700
Text Label 2550 6600 0    40   ~ 0
SCL
Text Label 2550 6700 0    40   ~ 0
SDA
Connection ~ 4050 7100
$Comp
L MAG3110 U12
U 1 1 596D1380
P 4850 5500
F 0 "U12" H 4600 5200 60  0000 C CNN
F 1 "MAG3110" H 4850 5800 60  0000 C CNN
F 2 "" H 4850 5500 60  0000 C CNN
F 3 "" H 4850 5500 60  0000 C CNN
	1    4850 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 5700 4375 5700
Wire Wire Line
	5250 5300 5675 5300
NoConn ~ 5250 5400
Text Label 5450 5700 0    40   ~ 0
SDA
$Comp
L CSMALL C8
U 1 1 596D138C
P 3850 5725
F 0 "C8" H 3875 5775 30  0000 L CNN
F 1 "100n" H 3875 5675 30  0000 L CNN
F 2 "~" H 3850 5725 60  0000 C CNN
F 3 "~" H 3850 5725 60  0000 C CNN
	1    3850 5725
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 5300 4450 5300
$Comp
L +3.3V #PWR034
U 1 1 596D1393
P 4025 5200
F 0 "#PWR034" H 4025 5160 30  0001 C CNN
F 1 "+3.3V" H 4025 5310 30  0000 C CNN
F 2 "" H 4025 5200 60  0000 C CNN
F 3 "" H 4025 5200 60  0000 C CNN
	1    4025 5200
	1    0    0    -1  
$EndComp
$Comp
L CSMALL C10
U 1 1 596D1399
P 4025 5725
F 0 "C10" H 4050 5775 30  0000 L CNN
F 1 "100n" H 4050 5675 30  0000 L CNN
F 2 "~" H 4025 5725 60  0000 C CNN
F 3 "~" H 4025 5725 60  0000 C CNN
	1    4025 5725
	1    0    0    -1  
$EndComp
$Comp
L CSMALL C11
U 1 1 596D139F
P 4200 5725
F 0 "C11" H 4225 5775 30  0000 L CNN
F 1 "100n" H 4225 5675 30  0000 L CNN
F 2 "~" H 4200 5725 60  0000 C CNN
F 3 "~" H 4200 5725 60  0000 C CNN
	1    4200 5725
	1    0    0    -1  
$EndComp
Wire Wire Line
	5625 5700 5250 5700
Wire Wire Line
	3850 5300 3850 5625
Wire Wire Line
	4450 5400 4025 5400
Wire Wire Line
	4025 5200 4025 5625
Wire Wire Line
	4450 5600 4200 5600
Wire Wire Line
	4200 5600 4200 5625
Connection ~ 4025 5400
Wire Wire Line
	3850 5825 4375 5825
Wire Wire Line
	4375 5825 4375 5700
Connection ~ 4025 5825
Wire Wire Line
	4125 5825 4125 5925
Connection ~ 4125 5825
$Comp
L GND #PWR035
U 1 1 596D13B1
P 4125 5925
F 0 "#PWR035" H 4125 5925 30  0001 C CNN
F 1 "GND" H 4125 5855 30  0001 C CNN
F 2 "" H 4125 5925 60  0000 C CNN
F 3 "" H 4125 5925 60  0000 C CNN
	1    4125 5925
	1    0    0    -1  
$EndComp
Wire Wire Line
	5675 5300 5675 5350
$Comp
L GND #PWR036
U 1 1 596D13B8
P 5675 5350
F 0 "#PWR036" H 5675 5350 30  0001 C CNN
F 1 "GND" H 5675 5280 30  0001 C CNN
F 2 "" H 5675 5350 60  0000 C CNN
F 3 "" H 5675 5350 60  0000 C CNN
	1    5675 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5375 5500 5375 5200
$Comp
L +3.3V #PWR037
U 1 1 596D13BF
P 5375 5200
F 0 "#PWR037" H 5375 5160 30  0001 C CNN
F 1 "+3.3V" H 5375 5310 30  0000 C CNN
F 2 "" H 5375 5200 60  0000 C CNN
F 3 "" H 5375 5200 60  0000 C CNN
	1    5375 5200
	1    0    0    -1  
$EndComp
Text Label 5450 5600 0    40   ~ 0
SCL
Wire Wire Line
	5250 5600 5625 5600
Wire Wire Line
	5250 5500 5375 5500
Connection ~ 4200 5825
Text Notes 3750 6175 0    60   ~ 0
Magnetometer: Bus address 0x0e (1c/1d)
$Comp
L +5V #PWR038
U 1 1 596D02D3
P 9200 1000
F 0 "#PWR038" H 9200 1090 20  0001 C CNN
F 1 "+5V" H 9200 1090 30  0000 C CNN
F 2 "" H 9200 1000 60  0000 C CNN
F 3 "" H 9200 1000 60  0000 C CNN
	1    9200 1000
	1    0    0    -1  
$EndComp
NoConn ~ 4625 2650
Wire Notes Line
	850  600  6000 600 
Wire Notes Line
	6000 600  6000 4800
Wire Notes Line
	6000 4800 850  4800
Wire Notes Line
	850  4800 850  600 
Wire Wire Line
	3850 6450 3850 6600
Wire Wire Line
	5450 6450 5450 6850
Wire Notes Line
	6000 4950 6000 7650
Wire Notes Line
	6000 7650 850  7650
Wire Notes Line
	850  7650 850  4950
Wire Notes Line
	850  4950 6000 4950
Wire Wire Line
	2400 5175 2400 5300
Text Notes 1050 7475 0    60   ~ 12
I2C Peripherals\n
Wire Notes Line
	6250 600  8500 600 
Wire Notes Line
	6250 2850 8500 2850
Wire Notes Line
	6250 600  6250 2650
Wire Notes Line
	6250 2650 8500 2650
Wire Notes Line
	8500 2650 8500 600 
Wire Notes Line
	6250 2850 6250 4200
Wire Notes Line
	6250 4200 8500 4200
Wire Notes Line
	8500 4200 8500 2850
Text Notes 6350 4100 0    60   ~ 12
Side Connectors
Wire Notes Line
	6250 4350 8500 4350
Wire Notes Line
	8500 4350 8500 7050
Wire Notes Line
	8500 7050 6250 7050
Wire Notes Line
	6250 7050 6250 4350
Text Notes 6350 6950 0    60   ~ 12
USB Power and Communication\n
Wire Notes Line
	8750 600  10700 600 
Wire Notes Line
	10700 600  10700 2450
Wire Notes Line
	10700 2450 8750 2450
Wire Notes Line
	8750 2450 8750 600 
Wire Notes Line
	8750 2650 10700 2650
Wire Notes Line
	10700 2650 10700 3950
Wire Notes Line
	10700 3950 8750 3950
Wire Notes Line
	8750 3950 8750 2650
Wire Notes Line
	8750 4050 10700 4050
Wire Notes Line
	10700 4050 10700 7050
Wire Notes Line
	10700 7050 8750 7050
Wire Notes Line
	8750 7050 8750 4050
Text Notes 8850 3800 0    60   ~ 12
User Buttons
Text Notes 8850 6950 0    60   ~ 12
Pixels
Text Notes 8850 2250 0    60   ~ 12
Diagnostic Leds
$EndSCHEMATC
