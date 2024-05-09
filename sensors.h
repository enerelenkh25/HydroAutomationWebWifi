// sensors.h
#ifndef SENSORS_H
#define SENSORS_H

#include "OneWire.h"
#include "DallasTemperature.h"
#include "DFRobot_PH.h"
#include "DFRobot_EC.h"
#include "MQ135.h"
#include "DHT.h"
#include "YF_S201.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "vegetables.h"

// Sensor Pins
#define ONE_WIRE_BUS 2  // DS18B20 (Not needed with DHT11 but left for future compatibility)
#define PH_PIN A1       // SEN0161 pH Sensor
#define EC_PIN A2       // DFR0300 EC Sensor
#define MQ135_PIN A3    // MQ135 CO2 Sensor

#define DHT_PIN 3       // DHT11 Temperature and Humidity Sensor
#define DHT_TYPE DHT11

#define FLOW_TANK_PIN 4
#define FLOW_FILTER_PIN 5
#define FLOW_RESERVOIR_PIN 6

// NTP Client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000);  // Update every minute

// Sensor Instances
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature waterTempSensor(&oneWire); // For future use
DFRobot_PH phSensor(PH_PIN);
DFRobot_EC ecSensor;
MQ135 mq135Sensor(MQ135_PIN);
DHT dht(DHT_PIN, DHT_TYPE);
YF_S201 flowTank(FLOW_TANK_PIN);
YF_S201 flowFilter(FLOW_FILTER_PIN);
YF_S201 flowReservoir(FLOW_RESERVOIR_PIN);

// Uniform Sensor Data
struct SensorData {
    float airTemperature;
    float airHumidity;
    float waterTemperature;
    float phValue;
    float ecValue;
    float co2Value;
    float flowRateTank;
    float flowRateFilter;
    float flowRateReservoir;
    int hour;
    String formattedTime;
};

SensorData sensorData = {};

void setupSensors() {
    waterTempSensor.begin(); // For future use
    phSensor.begin();
    ecSensor.begin();
    dht.begin();
    flowTank.begin();
    flowFilter.begin();
    flowReservoir.begin();
    timeClient.begin();
}

void readSensors() {
    // Read air temperature and humidity
    sensorData.airTemperature = dht.readTemperature();
    sensorData.airHumidity = dht.readHumidity();

    // Read water temperature (left as an example)
    waterTempSensor.requestTemperatures();
    sensorData.waterTemperature = waterTempSensor.getTempCByIndex(0);

    // Read pH
    sensorData.phValue = phSensor.readPH();

    // Read EC
    sensorData.ecValue = ecSensor.readEC();

    // Read CO2
    sensorData.co2Value = mq135Sensor.getPPM();

    // Read flow meters
    sensorData.flowRateTank = flowTank.getFlowRate();
    sensorData.flowRateFilter = flowFilter.getFlowRate();
    sensorData.flowRateReservoir = flowReservoir.getFlowRate();

    // Update and read the time
    timeClient.update();
    sensorData.hour = timeClient.getHours();
    sensorData.formattedTime = timeClient.getFormattedTime();
}

#endif
