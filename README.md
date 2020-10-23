# Project-Mach-1
This repository contains information to support the high powered rocketry project at the Imperial College Space Society. It documents the electronic Command and Control Modules which are used within the project.

## Repository Structure
The repository structure is based on the high level electronics modules:

* [Ground control module](https://github.com/ImperialSpaceSociety/Project-Mach-1/blob/master/Ground%20Control%20module)
* [Flight Computer](https://github.com/ImperialSpaceSociety/Project-Mach-1/blob/master/Flight%20computer)
* [Parachute deployer](https://github.com/ImperialSpaceSociety/Project-Mach-1/blob/master/Parachute%20deployer)
* [docs - Top Level Specfications and Documents](https://github.com/ImperialSpaceSociety/Project-Mach-1/blob/master/docs)

Each Module description has the following structure:

* ICSS Specifications
* External specifications, references and documentation
* Electronic Hardware (schematics and PCB)
* Firmware
* Physical Hardware (CAD)

## Quick Reference
The following is intended to provide a view for the casual browser of the project content.

The repository describes the four electronic Modules:

* The [Ground control module](https://github.com/ImperialSpaceSociety/Project-Mach-1/blob/master/Ground%20Control%20module) has these key roles:
  * Ensure a safe launch by control of safety mechanisms and firing control
  * Ensure time synchronization of all electronic modules and launch procedures
  * Support successful recovery of rocket parts
  * Recover flight data from the **Flight Computer**

* The [Flight Computer](https://github.com/ImperialSpaceSociety/Project-Mach-1/blob/master/Flight%20computer) has these key role:
  * Unambiguously capture flight data for subsequent analysis
  * Verify and prove performance record data ( Mach)
  * Support it's own successful recovery

* The [Parachute Deployer](https://github.com/ImperialSpaceSociety/Project-Mach-1/blob/master/Parachute%20deployer) has these key roles:
  * To trigger the deployment of the main parachute when 300m above ground to ensure the rocket does not drift too far
  * To trigger the deployment of the main parachute to aid recovery

## How to setup
# Burning the bootloader
1. Install Atmel studio. It can be downloaded from the [atmel site](https://www.microchip.com/mplab/avr-support/atmel-studio-7). Ensure that you download the SMART ARM MCU option like so: ![image](https://user-images.githubusercontent.com/26815217/97048803-8e224e00-1572-11eb-8974-1dc5bd169e97.png)
2. Connect up the flight computer to the J-Link EDU like so. Note the positions and colours of wires. Getting them the wrong way around could cause reverse polarity issues. The usb connector on the flight computer must be connected to the Computer.![image](https://user-images.githubusercontent.com/26815217/97048803-8e224e00-1572-11eb-8974-1dc5bd169e97.png)
3. Open up Atmel Studio and navigate to Tools > Device Programming like so: ![image](https://user-images.githubusercontent.com/26815217/97049151-1bfe3900-1573-11eb-92dd-a2e1868a808a.png)
4. Ensure that the device selected is the SAMD21J18A. The default name may be a very similar looking name so make sure you don't mix it up. Click apply.: ![image](https://user-images.githubusercontent.com/26815217/97049270-5b2c8a00-1573-11eb-8d83-f50c7edb5846.png)
5. Now navigate to the `Memories` tab. You will now burn the custom Arduino boot loader into SAMD21 on the flight computer with Atmel Studio. The bootloader is found in `Project-Mach-1\Flight computer\Software\bootloader for samd21j` and the filename is `bootloader-itsybitsy_m0-v2.0.0-adafruit.5.elf`. Click the `Program` button once selected the right bootloader: ![image](https://user-images.githubusercontent.com/26815217/97049436-a3e44300-1573-11eb-92fe-02f36d6b8130.png)

Ideally, once the Arduino bootloader is uploaded, the Segger debugger will not be necessary anymore; All future programming can be done with the Arduino IDE.

# Using Arduino to program
1. Install the Arduino IDE
2. Install Arduino support for the SAMD series of microcontrollers. To do so, go to file > preferences and add `https://adafruit.github.io/arduino-board-index/package_adafruit_index.json` to Additional Board Manager Urls like so: ![image](https://user-images.githubusercontent.com/26815217/97046336-228ab180-156f-11eb-9b23-e58ebe139e13.png)
3. Then go to Tools > Boards > Boards Manager like so:![image](https://user-images.githubusercontent.com/26815217/97046437-4cdc6f00-156f-11eb-8568-0db63647302c.png)
4. Then install the SAMD core by searching for Arduino SAMD Boards (32-bits Arm Cortex-M0+) like so: ![image](https://user-images.githubusercontent.com/26815217/97046683-a47ada80-156f-11eb-993c-f97d2ba23dc1.png)
5. Then install the Boards support for Adafruit SAMD boards, which our Flight computer is based off. Install version 1.5.9. Put in `Adafruit SAMD Boards` into the search bar.![image](https://user-images.githubusercontent.com/26815217/97047112-5d411980-1570-11eb-8788-4c5ba38919c8.png)
6. Find out where your newly downloaded board files are found by going here to the file > preferences. In this case the board files are in `C:\Users\Medad\Documents\ArduinoData`. ![image](https://user-images.githubusercontent.com/26815217/97037529-4e069f80-1561-11eb-9e55-63b4ba6fe1d4.png).
7. Now you will have to replace these board files with our own custom board files. Go to the directory found in the previous step and navigate to`ArduinoData\packages\adafruit\hardware\samd` where you will find a folder like `1.5.9`. Now you need to delete this folder, and replace it with our custom folder of board files that can be found in this repo: `Project-Mach-1\Flight computer\Software\Custom board files for flight computer\1.5.9`.
8. Now restart Arduino IDE so that it can update the board file location.
9. Now select the rocket flight computer as the board to use, like so in the picture: ![image](https://user-images.githubusercontent.com/26815217/97038067-26640700-1562-11eb-93f9-622826eb055e.png)
10. Now run the i2c scanner program in `Project-Mach-1\Flight computer\Software\Arduino code\i2c_scanner` on the arduino editor. You will see data on the serial port like this: ![image](https://user-images.githubusercontent.com/26815217/97045258-5a90f500-156d-11eb-95d6-a1918af80ee6.png)

 


## Current progress
* 25/9/19: The circuit board design files have been sent for manufacturing. Renders are as shown below.
![alt text](https://github.com/ImperialSpaceSociety/Project-Mach-1/blob/master/Flight%20computer/Hardware/circuit%20board%20design%20v1.1/Capture%20ft1.PNG)
![alt text](https://github.com/ImperialSpaceSociety/Project-Mach-1/blob/master/Flight%20computer/Hardware/circuit%20board%20design%20v1.1/Capture%20ft2.PNG)

## TODO
* build a base station
* build the rocket
* write all driver code for rocket flight computer(consider using FreeRTOS)
* assemble all flight computer PCBs by soldering
* Test all functions
* Launch!


## License

Hardware is Licensed under CERN OHL v.1.2 or later https://www.ohwr.org/documents/294 No warranty is provided for this documentation implied or otherwise.

Software is licensed under MIT License.

MIT License

Copyright (c) 2018 Imperial College Space Society

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
