#ifndef RELAYS_H
#define RELAYS_H

#include "sensors.h"
#include "vegetables.h"

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

void setupRelays() {
  pinMode(relayAirVent      , OUTPUT);
  pinMode(relayHeater       , OUTPUT);
  pinMode(relayCooler       , OUTPUT);
  pinMode(relayHumidifier   , OUTPUT);
  pinMode(relayWaterHeater  , OUTPUT);
  pinMode(relayWaterCooler  , OUTPUT);
  pinMode(relayPump1        , OUTPUT);
  pinMode(relayPump2        , OUTPUT);
  pinMode(relayPump3        , OUTPUT);
  pinMode(relayLight        , OUTPUT);

  // Initialize all relays to OFF
  controlRelay(relayAirVent     , false);
  controlRelay(relayHeater      , false);
  controlRelay(relayCooler      , false);
  controlRelay(relayHumidifier  , false);
  controlRelay(relayWaterHeater , false);
  controlRelay(relayWaterCooler , false);
  controlRelay(relayPump1       , false);
  controlRelay(relayPump2       , false);
  controlRelay(relayPump3       , false);
  controlRelay(relayLight       , false);
}

void controlRelay(int relay, bool state) {
  digitalWrite(relay, state ? HIGH : LOW);
}

void controlRelays() {
  // Relay control logic based on the current phase
  if (sensorData.airTemperature < currentPhase.daylightTempLow) controlRelay(relayHeater, true);
  else controlRelay(relayHeater, false);

  if (sensorData.airTemperature > currentPhase.daylightTempHigh) controlRelay(relayCooler, true);
  else controlRelay(relayCooler, false);

  if (sensorData.airHumidity < currentPhase.humidityLow) controlRelay(relayHumidifier, true);
  else controlRelay(relayHumidifier, false);

  if (sensorData.waterTemperature < currentPhase.waterTempLow) controlRelay(relayWaterHeater, true);
  else controlRelay(relayWaterHeater, false);

  if (sensorData.waterTemperature > currentPhase.waterTempHigh) controlRelay(relayWaterCooler, true);
  else controlRelay(relayWaterCooler, false);

  // Light control logic based on the current vegetable
  if (sensorData.hour >= 6 && sensorData.hour < (6 + currentVegetable.lightDurationHours)) controlRelay(relayLight, true);
  else controlRelay(relayLight, false);
}

#endif
