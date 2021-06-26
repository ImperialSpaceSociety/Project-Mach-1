/*
 * Project: Si4463 Radio Library for AVR and Arduino (Ping server example)
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2017 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/si4463-radio-library-avr-arduino/
 */

/*
 * Ping server
 *
 * Listen for packets and send them back
 */

#include <Si446x.h>

#define CHANNEL 0
#define MAX_PACKET_SIZE 50

#define PACKET_NONE		0
#define PACKET_OK		1
#define PACKET_INVALID	2

typedef struct{
	uint8_t ready;
	int16_t rssi;
	uint8_t length;
	uint8_t buffer[MAX_PACKET_SIZE];
} pingInfo_t;

static volatile pingInfo_t pingInfo;

typedef struct{
  int count;
  float longitude;
  float latitude;
  float altitude;
} data_t;


static volatile data_t rx_data;

void SI446X_CB_RXCOMPLETE(uint8_t length, int16_t rssi)
{
	if(length > MAX_PACKET_SIZE)
		length = MAX_PACKET_SIZE;

	pingInfo.ready = PACKET_OK;
	pingInfo.rssi = rssi;
	pingInfo.length = length;

	Si446x_read((uint8_t*)pingInfo.buffer, length);

	// Radio will now be in idle mode
}

void SI446X_CB_RXINVALID(int16_t rssi)
{
	pingInfo.ready = PACKET_INVALID;
	pingInfo.rssi = rssi;
}

void setup()
{
	Serial.begin(115200);
    while (!Serial){
     delay(100); // wait for native usb
    }

	pinMode(PIN_LED_BLUE, OUTPUT); // LED

	// Start up
	Si446x_init();
	Si446x_setTxPower(22);
}

void loop()
{
	static uint32_t pings;
	static uint32_t invalids;

	// Put into receive mode
	Si446x_RX(CHANNEL);

	Serial.println(F("Waiting for ping..."));

	// Wait for data
	while(pingInfo.ready == PACKET_NONE);
		
	if(pingInfo.ready != PACKET_OK)
	{
		invalids++;
		pingInfo.ready = PACKET_NONE;
		Serial.print(F("Invalid packet! Signal: "));
		Serial.print(pingInfo.rssi);
		Serial.println(F("dBm"));
		Si446x_RX(CHANNEL);
	}
	else
	{
		pings++;
		pingInfo.ready = PACKET_NONE;

		Serial.println(F("Got ping, sending reply..."));

		// Send back the data, once the transmission has completed go into receive mode
		Si446x_TX((uint8_t*)pingInfo.buffer, pingInfo.length, CHANNEL, SI446X_STATE_RX);

		Serial.println(F("Reply sent"));

		// Toggle LED
		static uint8_t ledState;
		digitalWrite(PIN_LED_BLUE, ledState ? HIGH : LOW);
		ledState = !ledState;

		Serial.print(F("Signal strength: "));
		Serial.print(pingInfo.rssi);
		Serial.println(F("dBm"));

		// Print out ping contents
		Serial.print(F("Data from server: "));
		Serial.write((uint8_t*)pingInfo.buffer, sizeof(pingInfo.buffer));
		Serial.println();

    Serial.print(F("Position Data from server: "));
    // Convert bytes to struct. Ref: https://snipplr.com/view/1254?codeview=

    data_t* msg = (data_t*)pingInfo.buffer;
    Serial.print(" Count= ");
    Serial.print(msg->count);
    Serial.print(" Longitude= ");
    Serial.print(msg->longitude/1e7,8);
    Serial.print(" Latitude= ");
    Serial.print(msg->latitude/1e7,8);
    Serial.print(" Altitude= ");
    Serial.print(msg->altitude/1e3);
    Serial.println();
	}

	Serial.print(F("Totals: "));
	Serial.print(pings);
	Serial.print(F("Pings, "));
	Serial.print(invalids);
	Serial.println(F("Invalid"));
	Serial.println(F("------"));
}
