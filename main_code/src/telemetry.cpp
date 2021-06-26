/*
 * Project: Si4463 Radio Library for AVR and Arduino (Ping client example)
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2017 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/si4463-radio-library-avr-arduino/
 */

/*
 * Ping client
 *
 * Time how long it takes to send some data and get a reply
 * Should be around 5-6ms with default settings
 */

#include <Si446x.h>
#include "telemetry.hpp"
#include <FreeRTOS_SAMD21.h>

#define CHANNEL 0
#define MAX_PACKET_SIZE 50
#define TIMEOUT 1000

#define PACKET_NONE 0
#define PACKET_OK 1
#define PACKET_INVALID 2

typedef struct
{
    uint8_t ready;
    uint32_t timestamp;
    int16_t rssi;
    uint8_t length;
    uint8_t buffer[MAX_PACKET_SIZE];
} pingInfo_t;

static volatile pingInfo_t pingInfo;

typedef struct
{
    int count;
    float longitude;
    float latitude;
    float altitude;
} data_t;

static data_t tx_data = {.count = 0, .longitude = 0.2, .latitude = 52.3, .altitude = 120.2};

void SI446X_CB_RXCOMPLETE(uint8_t length, int16_t rssi)
{
    if (length > MAX_PACKET_SIZE)
        length = MAX_PACKET_SIZE;

    pingInfo.ready = PACKET_OK;
    pingInfo.timestamp = millis();
    pingInfo.rssi = rssi;
    pingInfo.length = length;

    Si446x_read((uint8_t *)pingInfo.buffer, length);

    // Radio will now be in idle mode
}

void SI446X_CB_RXINVALID(int16_t rssi)
{
    pingInfo.ready = PACKET_INVALID;
    pingInfo.rssi = rssi;
}

void telemetry_init()
{
    Serial.begin(115200);

    pinMode(PIN_LED_BLUE, OUTPUT); // LED

    // Start up
    Si446x_init();

    /**
     *  This is the legal EIRP limit in this frequency band(434 Mhz) in the Uk 
     */
    Si446x_setTxPower(22); // 10 mW/ 10 dbm.
}

void send()
{
    static uint8_t counter;
    static uint32_t sent;
    static uint32_t replies;
    static uint32_t timeouts;
    static uint32_t invalids;

    Serial.print(F("Sending data"));
    uint32_t startTime = millis();

    // Send the data
    Si446x_TX(&tx_data, sizeof(data_t), CHANNEL, SI446X_STATE_SLEEP);
    sent++;

    tx_data.count++;

    Serial.println(F("Data sent, waiting for reply..."));

    uint8_t success;

    // Wait for reply with timeout
    uint32_t sendStartTime = millis();
    while (1)
    {
        vTaskDelay((1 * 1000) / portTICK_PERIOD_US);
        success = pingInfo.ready;
        if (success != PACKET_NONE)
            break;
        else if (millis() - sendStartTime > TIMEOUT) // Timeout // TODO typecast to uint16_t
            break;
    }

    pingInfo.ready = PACKET_NONE;

    if (success == PACKET_NONE)
    {
        Serial.println(F("Ping timed out"));
        timeouts++;
    }
    else if (success == PACKET_INVALID)
    {
        Serial.print(F("Invalid packet! Signal: "));
        Serial.print(pingInfo.rssi);
        Serial.println(F("dBm"));
        invalids++;
    }
    else
    {
        // If success toggle LED and send ping time over UART
        uint16_t totalTime = pingInfo.timestamp - startTime;

        static uint8_t ledState;
        digitalWrite(PIN_LED_BLUE, ledState ? HIGH : LOW);
        ledState = !ledState;

        replies++;

        Serial.print(F("Ping time: "));
        Serial.print(totalTime);
        Serial.println(F("ms"));

        Serial.print(F("Signal strength: "));
        Serial.print(pingInfo.rssi);
        Serial.println(F("dBm"));

        // Print out ping contents
        Serial.print(F("Data from server: "));
        Serial.write((uint8_t *)pingInfo.buffer, sizeof(pingInfo.buffer));
        Serial.println();
    }

    Serial.print(F("Totals: "));
    Serial.print(sent);
    Serial.print(F(" Sent, "));
    Serial.print(replies);
    Serial.print(F(" Replies, "));
    Serial.print(timeouts);
    Serial.print(F(" Timeouts, "));
    Serial.print(invalids);
    Serial.println(F(" Invalid"));
    Serial.println(F("------"));
}

void radio_send_data(dataPacket_t *dp)
{

    tx_data.altitude = dp->altitude;
    tx_data.latitude = dp->latitude;
    tx_data.altitude = dp->altitude;
    send();
}
