// relays.h
#ifndef RELAYS_H
#define RELAYS_H

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
}

void controlRelay(int relay, bool state) {
  digitalWrite(relay, state ? HIGH : LOW);
}

void controlRelays() {
  // Example relay control logic:
  if (sensorData.airTemperature < 20) controlRelay(relayHeater, true);
  else controlRelay(relayHeater, false);

  if (sensorData.airTemperature > 30) controlRelay(relayCooler, true);
  else controlRelay(relayCooler, false);

  if (sensorData.airHumidity < 50) controlRelay(relayHumidifier, true);
  else controlRelay(relayHumidifier, false);
}

#endif
