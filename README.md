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
1. burn boot loader into samd21 with atmel studio. ensure that the samd21 is selected chip instead of saml21
2. follow https://learn.adafruit.com/introducing-itsy-bitsy-m0/setup to install the boards files for the itsybitsym0 which our flight computer is based off
3. Find out where your board file are found by going here to the file > preferences: ![image](https://user-images.githubusercontent.com/26815217/97037529-4e069f80-1561-11eb-9e55-63b4ba6fe1d4.png)
4. Now go to this directory with the ArduinoData is stored. Then go down to `ArduinoData\packages\adafruit\hardware\samd` where you will find a folder like `1.5.9`. Now you need to delete this file, and replace it with our custom folder of board files that can be found in this repo: `Project-Mach-1\Flight computer\Software\Custom board files for flight computer`.


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
