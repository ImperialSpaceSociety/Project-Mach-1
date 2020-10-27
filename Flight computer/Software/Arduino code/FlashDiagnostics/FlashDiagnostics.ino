/*
  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
  |                                                             FlashDiagnostics.ino                                                              |
  |                                                               SPIMemory library                                                                |
  |                                                                   v 3.4.0                                                                     |
  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
  |                                                                    Marzogh                                                                    |
  |                                                                  01.06.2019                                                                   |
  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
  |                                                                                                                                               |
  |                                  For a full diagnostics rundown - with error codes and details of the errors                                  |
  |                                 uncomment #define RUNDIAGNOSTIC in SPIMemory.h in the library before compiling                                 |
  |                                             and loading this application onto your Arduino.                                                   |
  |                                                                                                                                               |
  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
*/

#include<SPIMemory.h>




#define TRUE 1
#define FALSE 0


SPIFlash flash(SS_FLASH, &SPI1);       //Use this constructor if using an SPI bus other than the default SPI. Only works with chips with more than one hardware SPI bus

void setup() {

  Serial.begin(115200);
  while (!Serial) ; // Wait for Serial monitor to open

  Serial.print(F("Initialising"));
  for (uint8_t i = 0; i < 10; ++i)
  {
    Serial.print(F("."));
  }
  Serial.println();
  randomSeed(analogRead(RANDPIN));
  
  if (flash.error()) {
    Serial.println(flash.error(VERBOSE));
  }
  
  flash.begin();
  //To use a custom flash memory size (if using memory from manufacturers not officially supported by the library) - declare a size variable according to the list in defines.h
  //flash.begin(MB(32));

  if (getID()) {

    printLine();
    printTab(7);
    Serial.print("Testing library code");
    printLine();
    printTab(3);
    Serial.print("Function");
    printTab(2);
    Serial.print("Test result");
    printTab(3);
    Serial.print("     Runtime");
    printLine();

    powerDownTest();
    Serial.println();
    powerUpTest();
    Serial.println();

    Serial.println();

    eraseChipTest();
    Serial.println();
    eraseSectionTest();
    Serial.println();
    eraseBlock64KTest();
    Serial.println();
    eraseBlock32KTest();
    Serial.println();
    eraseSectorTest();
    //Serial.println();


    /* #if defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_ESP8266)
        delay(10);
        powerDownTest();
        powerUpTest();
        Serial.println();
      #endif */
    printLine();
    printTab(3);
    Serial.print("Data type");
    printTab(2);
    Serial.print("I/O Result");
    printTab(1);
    Serial.print("      Write time");
    printTab(1);
    Serial.print("      Read time");
    printLine();

    byteTest();
    Serial.println();
    charTest();
    Serial.println();
    wordTest();
    Serial.println();
    shortTest();
    Serial.println();
    uLongTest();
    Serial.println();
    /*#if defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_ESP8266)
        delay(10);
      #endif */
    longTest();
    Serial.println();
    floatTest();
    Serial.println();
    structTest();
    Serial.println();
    arrayTest();
    Serial.println();
    stringTest();

    /* #if !defined(ARDUINO_ARCH_SAM) || !defined(ARDUINO_ARCH_ESP8266)
        Serial.println();
        powerDownTest();
        powerUpTest();
      #endif */
    printLine();
    if (!flash.functionRunTime()) {
      Serial.println(F("To see function runtimes ncomment RUNDIAGNOSTIC in SPIMemory.h."));
    }
  }
}

void loop() {

}
