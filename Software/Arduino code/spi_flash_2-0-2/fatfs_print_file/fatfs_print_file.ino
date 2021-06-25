// Adafruit SPI Flash FatFs Simple Datalogging Example
// Author: Tony DiCola
//
// This is a simple example that opens a file and prints its
// entire contents to the serial monitor.  Note that
// you MUST have a flash chip that's formatted with a flash
// filesystem before running, and there should be some sort
// of text file on it to open and read.  See the fatfs_format
// example to perform this formatting, and the fatfs_datalogging
// example to write a simple text file.
//
// Usage:
// - Modify the pins and type of fatfs object in the config
//   section below if necessary (usually not necessary).
// - Upload this sketch to your M0 express board.
// - Open the serial monitor at 115200 baud.  You should see the
//   example start to run and messages printed to the monitor.
//   If you don't see anything close the serial monitor, press
//   the board reset buttton, wait a few seconds, then open the
//   serial monitor again.
#include <SPI.h>
#include <Adafruit_SPIFlash.h>
#include <Adafruit_SPIFlash_FatFs.h>


// Configuration of the flash chip pins and flash fatfs object.
// You don't normally need to change these if using a Feather/Metro
// M0 express board.
#define FLASH_TYPE     SPIFLASHTYPE_W25Q64  // Flash chip type.
                                              // If you change this be
                                              // sure to change the fatfs
                                              // object type below to match.


#if defined(__SAMD51__)
  // Alternatively you can define and use non-SPI pins, QSPI isnt on a sercom
  Adafruit_SPIFlash flash(PIN_QSPI_SCK, PIN_QSPI_IO1, PIN_QSPI_IO0, PIN_QSPI_CS);
#else
  #if (SPI_INTERFACES_COUNT == 1)
    #define FLASH_SS       SS                    // Flash chip SS pin.
    #define FLASH_SPI_PORT SPI                   // What SPI port is Flash on?
  #else
    #define FLASH_SS       SS1                    // Flash chip SS pin.
    #define FLASH_SPI_PORT SPI1                   // What SPI port is Flash on?
  #endif

Adafruit_SPIFlash flash(FLASH_SS, &FLASH_SPI_PORT);     // Use hardware SPI
#endif

Adafruit_W25Q16BV_FatFs fatfs(flash);

// Configuration for the file to open and read:
#define FILE_NAME      "data.csv"


typedef struct{
  int count;
  float longitude;
  float latitude;
  float altitude;
} data_t;

void setup() {
  // Initialize serial port and wait for it to open before continuing.
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Serial.println("Adafruit SPI Flash FatFs Simple File Printing Example");

  // Initialize flash library and check its chip ID.
  if (!flash.begin(FLASH_TYPE)) {
    Serial.println("Error, failed to initialize flash chip!");
    while(1);
  }
  Serial.print("Flash chip JEDEC ID: 0x"); Serial.println(flash.GetJEDECID(), HEX);

  // First call begin to mount the filesystem.  Check that it returns true
  // to make sure the filesystem was mounted.
  if (!fatfs.begin()) {
    Serial.println("Error, failed to mount newly formatted filesystem!");
    Serial.println("Was the flash chip formatted with the fatfs_format example?");
    while(1);
  }
  Serial.println("Mounted filesystem!");

  // Open the file for reading and check that it was successfully opened.
  // The FILE_READ mode will open the file for reading.
  Adafruit_SPIFlash_FAT::File dataFile = fatfs.open(FILE_NAME, FILE_READ);
  if (dataFile) {
    // File was opened, now print out data character by character until at the
    // end of the file.
    Serial.println("Opened file, printing contents below:");
    while (dataFile.available()) {
      // Use the read function to read the next character.
      // You can alternatively use other functions like readUntil, readString, etc.
      // See the fatfs_full_usage example for more details.
      data_t rx_data;
      dataFile.read((uint8_t *)&rx_data, sizeof(data_t));
            
      Serial.print(" Count= ");
      Serial.print(rx_data.count);
      Serial.print(" Longitude= ");
      Serial.print(rx_data.longitude);
      Serial.print(" Latitude= ");
      Serial.print(rx_data.latitude);
      Serial.print(" Altitude= ");
      Serial.print(rx_data.altitude);
      Serial.println();
    
    }
  }
  else {
    Serial.println("Failed to open data file! Does it exist?");
  }
}

void loop() {
  // Nothing to do in main loop.
  delay(100);
}