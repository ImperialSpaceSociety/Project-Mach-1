#include <Arduino.h>

/*
  Blink for Flight Computer Turns LEDs alternatively on for one second, then off for one second, repeatedly. This example code is in the public domain. http://www.arduino.cc/en/Tutorial/Blink
*/

#ifndef PIN_LED_RED
#define PIN_LED_RED (38u)
#endif

#ifndef PIN_LED_BLUE
#define PIN_LED_BLUE (39u)
#endif

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins as output.
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(PIN_LED_RED, HIGH); // turn the LED on (HIGH is the voltage level)
  digitalWrite(PIN_LED_BLUE, LOW); // turn the LED off by making the voltage LOW
  delay(200); // wait for a second
  digitalWrite(PIN_LED_RED, LOW); // turn the LED off by making the voltage LOW
  digitalWrite(PIN_LED_BLUE, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(500); // wait for half a second
}