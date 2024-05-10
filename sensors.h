#ifndef SENSORS_H
#define SENSORS_H

#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Pin Definitions
#define ONE_WIRE_BUS 2  // DS18B20 (OneWire Bus)
#define PH_PIN A1       // SEN0161 pH Sensor
#define EC_PIN A2       // DFR0300 EC Sensor
#define MQ135_PIN A3    // MQ135 CO2 Sensor
#define DHT_PIN 3       // DHT11 Temperature and Humidity Sensor
#define DHT_TYPE DHT11
#define FLOW_TANK_PIN 4
#define FLOW_FILTER_PIN 5
#define FLOW_RESERVOIR_PIN 6

// DHT11 Sensor
DHT dht(DHT_PIN, DHT_TYPE);

// DS18B20 Temperature Sensor
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature waterTempSensor(&oneWire);

// Flow Sensors Variables
volatile int flowTankCount = 0;
volatile int flowFilterCount = 0;
volatile int flowReservoirCount = 0;

// Flow Rates (L/min)
float flowTankRate = 0.0;
float flowFilterRate = 0.0;
float flowReservoirRate = 0.0;

// Sensor Data
struct SensorData {
    float airTemperature;
    float airHumidity;
    float waterTemperature;
    float co2Level;
    float phValue;
    float ecValue;
    float doValue;
    float flowTankRate;
    float flowFilterRate;
    float flowReservoirRate;
} sensorData;

// Flow Sensor ISR Functions
void flowTankISR() {
    flowTankCount++;
}

void flowFilterISR() {
    flowFilterCount++;
}

void flowReservoirISR() {
    flowReservoirCount++;
}

void sensorsInit() {
    // Initialize DHT11 Sensor
    dht.begin();

    // Initialize DS18B20 Temperature Sensor
    waterTempSensor.begin();

    // Initialize Flow Sensors
    pinMode(FLOW_TANK_PIN, INPUT);
    pinMode(FLOW_FILTER_PIN, INPUT);
    pinMode(FLOW_RESERVOIR_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(FLOW_TANK_PIN), flowTankISR, RISING);
    attachInterrupt(digitalPinToInterrupt(FLOW_FILTER_PIN), flowFilterISR, RISING);
    attachInterrupt(digitalPinToInterrupt(FLOW_RESERVOIR_PIN), flowReservoirISR, RISING);
}

void readSensors() {
    // Read DHT11 (Air Temperature & Humidity)
    sensorData.airTemperature = dht.readTemperature();
    sensorData.airHumidity = dht.readHumidity();

    // Read DS18B20 (Water Temperature)
    waterTempSensor.requestTemperatures();
    sensorData.waterTemperature = waterTempSensor.getTempCByIndex(0);

    // Placeholder readings for other sensors
    sensorData.co2Level = analogRead(MQ135_PIN);
    sensorData.phValue = analogRead(PH_PIN);
    sensorData.ecValue = analogRead(EC_PIN);
    sensorData.doValue = analogRead(A6);  // Example: OOM202 DO sensor

    // Calculate Flow Rates (L/min)
    noInterrupts();
    flowTankRate = (flowTankCount * 60.0) / 7.5;
    flowFilterRate = (flowFilterCount * 60.0) / 7.5;
    flowReservoirRate = (flowReservoirCount * 60.0) / 7.5;
    flowTankCount = flowFilterCount = flowReservoirCount = 0;
    interrupts();

    sensorData.flowTankRate = flowTankRate;
    sensorData.flowFilterRate = flowFilterRate;
    sensorData.flowReservoirRate = flowReservoirRate;
}

#endif
