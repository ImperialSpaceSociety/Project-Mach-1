



/*
 * Read Radio Information
 *
 *The Si446x_config.h file in the library needs to be modified 
 *to have the correct pins for the flight computer as follows
 *
///////////////////
// Pin stuff
///////////////////

// Arduino pin assignments
#define SI446X_CSN      35
#define SI446X_SDN      31
#define SI446X_IRQ      30 // This needs to be an interrupt pin
 *
 */

#include <Si446x.h>


si446x_info_t info;


void setup()
{
	Serial.begin(115200);
  while(!Serial);
  Serial.println("\nGet Radio Information");
	// Start up
	Si446x_init();
  Serial.println("\nRadio Init Complete");
}

void loop()
{
	Serial.println("\n\n\nGet Device Info:");

  Si446x_getInfo(&info);
  
  
  Serial.print("\nRevision: ");
  Serial.print(info.chipRev,HEX);
  Serial.print("\nPart: Si");
  Serial.print(info.part,HEX);
  Serial.print("\nPart Build: ");
  Serial.print(info.partBuild,HEX);
  Serial.print("\nId: ");
  Serial.print(info.id,HEX);
  Serial.print("\nCustomer: ");
  Serial.print(info.customer,HEX);
  Serial.print("\nROM_ID: ");
  Serial.print(info.romId,HEX);
  Serial.print("  (3 = revB1B, 6 = revC2A)");
  Serial.print("\nRev External: ");
  Serial.print(info.revExternal,HEX);
  Serial.print("\nRev Branch: ");
  Serial.print(info.revBranch,HEX);
  Serial.print("\nRev Internal: ");
  Serial.print(info.revInternal,HEX);
  Serial.print("\nPatch: ");
  Serial.print(info.patch,HEX);
  Serial.print("\nFunc: ");
  Serial.print(info.func,HEX);

  Serial.print("\nRadio Temperature: ");
  Serial.print(Si446x_adc_temperature());
  Serial.print(" deg C");
  Serial.print("\nRadio Voltage: ");
  Serial.print((float) Si446x_adc_battery()/1000);
  Serial.print(" Volts");


  delay(2000);

}
