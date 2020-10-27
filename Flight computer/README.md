# Project-Mach-1
# **Flight Computer**

## Rocket flight computer requirements:
* flexible for two stage or one stage rocket
* must have buzzer
* must have flashing LEDs to help with recovery on the ground
* must have usb programmer and possibly for accessing stored data
* 3 mosfets for rocket trigger, parachute triggering, spare
* rocket to ground telemetry link
* GPS for tracking and recovery
* runs at 3.3V logic levels(CMOS)
* 9 dof acclermoeter, gyroscope, compass. Max accleration would be 20g
* pressure(and temperature) sensor to measure altitude
* current sensing to see the amount of current going into fuses
* Mosfet must be able to supply 1.2 amps for at least 10milliseconds. Bridge wire resistance is 1.2-1.8 Ohms
* Must be able to run for at least 1 hour continueously
* must be hand solderable. Perferably
* 100Hz sample rate from sensors(except GPS)
* must record data continueously for at least 3min
* 14 parameters to record: *4 characters*:{accl_x, accl_y, accl_z, gyro_x, gyro_y, gyro_z, compass_x, compass_y, compass_z} + *6 characters:*{pressure}+ *3 characters:*{temperature}+ *7 characters*{Longitude, latitude}+*4 characters:*{altitude}
Assuming ascii encoding, 504 bits per string for raw data. Including commas and carriage return, each reading is ~600 bits.
* Total data storage required: 600bits * 60s * 100hz * 3min = 10.8 Mbits = 10800000 bits

## Major components of V1.1 flight computer
* ST Microelectronics H3LIS100DL: 100g 3-axis accelerometer
* ST Microelectronics LSM9DS1: 9 degree-of-freedom Accelerometer, Gyroscope and Magnetometer in 3 axis
* TE Connectivity MS5607: Temperature and pressure sensor
* Sillicon Labs SI4463: 433 Mhz ISM band Telemetry radio transceiver
* Ublox MAX M8Q: GPS module
* Atmel SAMD21J18: Microcontroller 64 pin TQFP package
* Vishay Si7232DN: Dual N-Channel 20 V (D-S) MOSFET for 2 channel pyros
* Molex 2066400001: GNSS Active Patch Antenna with Low-Noise Amplifier
* Winbond w25q64JV: Flash chip 64 Mbytes
