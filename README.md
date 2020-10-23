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
1. Burn the custom Arduino boot loader into SAMD21 on the flight computer with Atmel Studio. The bootloader is found in `Project-Mach-1\Flight computer\Software\bootloader for samd21j` and the filename is `bootloader-itsybitsy_m0-v2.0.0-adafruit.5.elf`. This can only be done with a Segger Debugger. Ideally, once the Arduino bootloader is uploaded, the Segger debugger will not be necessary anymore; All future programming can be done with the Arduino IDE.
2. Follow https://learn.adafruit.com/introducing-itsy-bitsy-m0/setup to install the boards files and drivers for the itsybitsym0 which our flight computer is based off. It will install the board files in the right directories automatically.
3. Find out where your board files are found by going here to the file > preferences. In this case the board files are in `C:\Users\Medad\Documents\ArduinoData`. ![image](https://user-images.githubusercontent.com/26815217/97037529-4e069f80-1561-11eb-9e55-63b4ba6fe1d4.png).
4. Now you will have to replace these board files with our own custom board files. Go to the directory found in the previous step and navigate to`ArduinoData\packages\adafruit\hardware\samd` where you will find a folder like `1.5.9`. Now you need to delete this file, and replace it with our custom folder of board files that can be found in this repo: `Project-Mach-1\Flight computer\Software\Custom board files for flight computer\1.5.9`.
5. Now restart Arduino IDE so that it can update the board file location.
6. Now select the rocket flight computer as the board to use, like so in the picture: ![image](https://user-images.githubusercontent.com/26815217/97038067-26640700-1562-11eb-93f9-622826eb055e.png)
4. Now run the i2c scanner program in `Project-Mach-1\Flight computer\Software\Arduino code\i2c_scanner` on the arduino editor. You will see data on the serial port like this: ![image](https://user-images.githubusercontent.com/26815217/97045258-5a90f500-156d-11eb-95d6-a1918af80ee6.png)

 


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
