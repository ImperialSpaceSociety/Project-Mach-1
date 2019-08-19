## Rocket flight computer requirements:
flexible for two stage or one stage rocket
must have buzzer
must have flashing LEDs
must have usb programmer and possibly for accessing stored data
3 mosfets for rocket trigger, parachute triggering, spare
rocket to ground telemetry link
GPS for tracking and recovery
runs at 3.3V logic levels(CMOS)
9 dof acclermoeter, gyroscope, compass
current sensing to see the amount of current going into fuses
Mosfet must be able to supply 1.2 amps for at least 10milliseconds. Bridge wire resistance is 1.2-1.8 Ohms


## Tentative Bill of Materials for rocket flight computer
Ublox MAX-M8Q 
Si4463 for radio
MS5611 for altimeter
3 mosfets for fuses(not chosen)
9dof acclerometer(not chosen)
3.7v lipo(not chosen)
buck converter to bring to 3.3V(not chosen)
