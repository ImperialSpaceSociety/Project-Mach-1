/*
Blink for Flight Computer Turns LEDs alternatively on for one second, then off for one second, repeatedly. This example code is in the public domain. http://www.arduino.cc/en/Tutorial/Blink
*/
#define LED1 37
#define LED2 38// the setup function runs once when you press reset or power the board
void setup() {
// initialize digital pins as output.
pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);
}// the loop function runs over and over again forever
void loop() {
digitalWrite(LED1, HIGH); // turn the LED on (HIGH is the voltage level)
digitalWrite(LED2, LOW); // turn the LED off by making the voltage LOW
delay(1000); // wait for a second
digitalWrite(LED1, LOW); // turn the LED off by making the voltage LOW
digitalWrite(LED2, HIGH); // turn the LED on (HIGH is the voltage level)
delay(1000); // wait for a second
}
