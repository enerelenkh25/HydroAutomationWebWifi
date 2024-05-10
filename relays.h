#ifndef RELAYS_H
#define RELAYS_H

#include "sensors.h"
#include "vegetables.h"
#include <RTClib.h>

// Relay Pin Definitions
const int relayAirVent = 12;
const int relayHeater = 13;
const int relayCooler = 14;
const int relayHumidifier = 15;
const int relayWaterHeater = 16;
const int relayWaterCooler = 17;
const int relayPump1 = 18;
const int relayPump2 = 19;
const int relayPump3 = 20;
const int relayLight = 21;

// RTC and Time Settings
RTC_DS3231 rtc;
const int lightOnHour = 6;  // Example time to turn on the light (6:00 AM)

// Seed Table Light Duration Data (Hours)
const String seedTable[15] = {
    "basil", "tomato", "lettuce", "beans", "beets", "celery", "chard",
    "cilantro", "cucumbers", "kale", "mint", "peppers", "radishes",
    "spinach", "springOnions"
};
const String lightDurationTable[15] = {
    "16", "18", "14", "16", "14", "18", "14", "14", "18", "16", "16",
    "18", "16", "16", "14"
};

// Relay Initialization
void setupRelays() {
    pinMode(relayAirVent, OUTPUT);
    pinMode(relayHeater, OUTPUT);
    pinMode(relayCooler, OUTPUT);
    pinMode(relayHumidifier, OUTPUT);
    pinMode(relayWaterHeater, OUTPUT);
    pinMode(relayWaterCooler, OUTPUT);
    pinMode(relayPump1, OUTPUT);
    pinMode(relayPump2, OUTPUT);
    pinMode(relayPump3, OUTPUT);
    pinMode(relayLight, OUTPUT);

    // Initialize all relays to OFF
    controlRelay(relayAirVent, false);
    controlRelay(relayHeater, false);
    controlRelay(relayCooler, false);
    controlRelay(relayHumidifier, false);
    controlRelay(relayWaterHeater, false);
    controlRelay(relayWaterCooler, false);
    controlRelay(relayPump1, false);
    controlRelay(relayPump2, false);
    controlRelay(relayPump3, false);
    controlRelay(relayLight, false);

    // Initialize the RTC
    if (!rtc.begin()) {
        Serial.println("RTC failed to initialize!");
        while (1);
    }
    if (rtc.lostPower()) {
        // Set the time to the last known time
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

// Relay Control Function
void controlRelay(int relay, bool state) {
    digitalWrite(relay, state ? HIGH : LOW);
}

// Light Relay Control Based on RTC
void controlLightRelayWithRTC(String selectedSeed) {
    DateTime now = rtc.now();

    // Get light duration for the selected seed
    int index = -1;
    for (int i = 0; i < 15; i++) {
        if (seedTable[i] == selectedSeed) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        int lightDuration = lightDurationTable[index].toInt();

        // Light on/off logic based on current time
        int currentHour = now.hour();
        if (currentHour >= lightOnHour && currentHour < (lightOnHour + lightDuration)) {
            controlRelay(relayLight, true);  // Turn light on
        } else {
            controlRelay(relayLight, false);  // Turn light off
        }
    }
}

// Control all relays
void controlRelays(String selectedSeed) {
    controlLightRelayWithRTC(selectedSeed);

    // Other relay logic here...
}

#endif
