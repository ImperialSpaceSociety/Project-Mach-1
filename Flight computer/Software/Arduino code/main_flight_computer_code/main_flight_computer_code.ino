/* Code for the Rocket Flight computer
 * Imperial College Space Society
 * version : 1.0
 * Date: 18/02/2020
 * Currently the code only polls the H2LIS100 acclerometer and prints out the values.
 * TODO: 
 * 1. get all the other sensors to work and print out values
 * 2. get the SPI flash chip to record down the values
 * 3. Get the radio to transmit its position.
 */

//this is a comment

#include "H3LIS100DL.h"
#include "MS5607.h"
#include "Ublox.h"
#include <Wire.h>
#include <SPIMemory.h>

//please get these value by running H3LIS331DL_AdjVal Sketch.
#define VAL_X_AXIS  203
#define VAL_Y_AXIS  165
#define VAL_Z_AXIS  141

H3LIS331DL h3lis;
MS5xxx ms5(&Wire);
SPIFlash flash(SS_FLASH, &SPI1);

long starttime;
long lasttime;

struct dataPacket{
  //h3lis, location and accuracy
  int16_t location[3];
  double acc[3];

  //m5 temp + pressure
  double temp;
  double pressure;
};

#define PACKET_SIZE sizeof(dataPacket)

//the one datapacket reference we iterate on every run
dataPacket dp;

//starting address and cursor pointer
uint32_t run_start;
uint32_t _addr;

bool limit = false;
int n;

void setup() {
  Serial.begin(9600);
  h3lis.init();
  h3lis.importPara(VAL_X_AXIS,VAL_Y_AXIS,VAL_Z_AXIS);
  
  if (flash.error()) {
    Serial.println(flash.error(VERBOSE));
  }
  flash.begin();

  //test all functionalities on the flash chip, pauses for confirmation
  delay(3000);
  Serial.println("Running tests on flash....");
  run_all_tests();
  Serial.println("Tests complete. If all looks good, enter y to continue");

  while(true) // remain here until told to break
  {
    if(Serial.available() > 0)
      if(Serial.read() == 'y')
        break;
  }

  Serial.println("Erase chip before run? enter y/n");
  bool erase = false;
  while(true) // remain here until told to break
  {
    if(Serial.available() > 0){
      char res = Serial.read();
      if(res == 'y' || res == 'n'){
        erase = res == 'y';
        break; 
      } 
    }
  }
  if(erase){
    //erase chip before run
    Serial.println("Erasing chip in preparation for run...");
    flash.eraseChip();
  }

  Serial.println("Run for n seconds? y/n");
  while(true) // remain here until told to break
  {
    if(Serial.available() > 0){
      char res = Serial.read();
      if(res == 'y' || res == 'n'){
        limit = res == 'y';
        break; 
      } 
    }
  }
  if(limit){
    Serial.println("How many seconds to record for. Insert number:");
    while(true) // remain here until told to break
    {
      if(Serial.available() > 0){
        String st = Serial.readString();
        if(st.toInt() > 0){
           n = st.toInt();
           break;
        }
      }
    }
  }
  
  
  //find suitable starting place for writing (should be 0)
  run_start = flash.getAddress(PACKET_SIZE);
  _addr = run_start;
  Serial.println("=========================================");
  Serial.println("This is the Rocket Flight Computer, v1.0");
  Serial.println("Press 1 and enter at any time to dump results from flash and exit the main loop.");
  Serial.println("=========================================");
  starttime = millis();
  
}
uint8_t command = 0;

void loop() {
  if(millis() - lasttime > 10){
    if(limit && lasttime > (starttime + n * 1000)){
      Serial.println(lasttime);
      Serial.println(starttime);
      Serial.println(n * 1000);
      dumpFlash();
      exit(0);
    }
    
    lasttime = millis(); //Update the timer
    read_info(&dp);
    //print_info(&dp);
    write_info(dp);
    Serial.println(_addr);

    if (command == 1){
      dumpFlash();
      exit(0);
      command = 0;
    }
  }

  if (Serial.available() > 0){
    command = Serial.parseInt();      
  }
}


//read info into a datapacket
void read_info(dataPacket *dp){
  //TODO: Add try-catch around the data collections, return a dummy value if failed.
  h3lis.readXYZ(&(dp->location[0]),&(dp->location[1]),&(dp->location[2]));
  h3lis.getAcceleration(dp->acc);

  ms5.ReadProm();
  ms5.Readout();

  dp->temp = ms5.GetTemp();
  dp->pressure = ms5.GetPres();
}

void read_from_flash(uint32_t addr){
  dataPacket out;
  flash.readAnything(addr - PACKET_SIZE, out);
  print_info(&out);
}

//print to serial port
void print_info(dataPacket *dp) {
    Serial.print("x, y, z = ");
    Serial.print(dp->location[0]);
    Serial.print("\t");
    Serial.print(dp->location[1]);
    Serial.print("\t");
    Serial.println(dp->location[2]);

    Serial.print("accelerate of x, y, z = ");
    Serial.print(dp->acc[0]);
    Serial.print("g");
    Serial.print("\t");
    Serial.print(dp->acc[1]);
    Serial.print("g");
    Serial.print("\t");
    Serial.print(dp->acc[2]);
    Serial.println("g");

    Serial.print("Temperature: ");
    Serial.println(dp->temp);
    Serial.print("Pressure: ");
    Serial.println(dp->pressure);
}

bool write_info(dataPacket dp){
  if (flash.writeAnything(_addr, dp)){
    //increment address pointer
    _addr += PACKET_SIZE;

    return true;
  }
  else{
    Serial.print("Problem writing to flash.");
    return false;
  }
}

void dumpFlash(){
  int num_packets = _addr / PACKET_SIZE;
  for(int i = 1; i < num_packets; i++){
    read_from_flash(run_start + i * PACKET_SIZE);
  }
}

void run_all_tests(){
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

int isNumeric (const char *s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}
