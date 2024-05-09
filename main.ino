#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "relays.h"
#include "sensors.h"
#include "vegetables.h"

// WiFi credentials
const char* ssid = "Hydroponic_Monitoring";
const char* password = "123456";

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// WiFi server
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.backlight();

  setupRelays();
  setupSensors();

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi!");
  lcd.setCursor(0, 1);
  lcd.print("WiFi Connected!");

  server.begin();
}

void loop() {
  readSensors();
  updateLCD();

  // Handle HTTP Requests
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();
    handleClientRequest(request);
    client.stop();
  }

  controlRelays();
}

void updateLCD() {
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(sensorData.airTemperature);
  lcd.print("C H:");
  lcd.print(sensorData.airHumidity);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("CO2:");
  lcd.print(sensorData.co2Value);
  lcd.print("ppm ");

  // Show Time
  lcd.setCursor(12, 1);
  lcd.print(sensorData.formattedTime);
}

void handleClientRequest(String request) {
  // Vegetable selection
  if (request.indexOf("/VEGETABLE=CELERY") != -1) selectVegetable(celery);
  if (request.indexOf("/VEGETABLE=SPINACH") != -1) selectVegetable(spinach);
  if (request.indexOf("/VEGETABLE=SPRING_ONIONS") != -1) selectVegetable(springOnions);
  if (request.indexOf("/VEGETABLE=TOMATOES") != -1) selectVegetable(tomatoes);
  if (request.indexOf("/VEGETABLE=MINT") != -1) selectVegetable(mint);
  if (request.indexOf("/VEGETABLE=CILANTRO") != -1) selectVegetable(cilantro);
  if (request.indexOf("/VEGETABLE=KALE") != -1) selectVegetable(kale);
  if (request.indexOf("/VEGETABLE=LETTUCE") != -1) selectVegetable(lettuce);
  if (request.indexOf("/VEGETABLE=BASIL") != -1) selectVegetable(basil);
  if (request.indexOf("/VEGETABLE=BEANS") != -1) selectVegetable(beans);
  if (request.indexOf("/VEGETABLE=CHARD") != -1) selectVegetable(chard);
  if (request.indexOf("/VEGETABLE=PEPPERS") != -1) selectVegetable(peppers);
  if (request.indexOf("/VEGETABLE=CUCUMBERS") != -1) selectVegetable(cucumbers);
  if (request.indexOf("/VEGETABLE=BEETS") != -1) selectVegetable(beets);
  if (request.indexOf("/VEGETABLE=RADISHES") != -1) selectVegetable(radishes);

  // Phase selection
  if (request.indexOf("/PHASE=GERMINATION") != -1) selectPhase(germination);
  if (request.indexOf("/PHASE=SEEDING") != -1) selectPhase(seeding);
  if (request.indexOf("/PHASE=VEGETATIVE_GROWTH") != -1) selectPhase(vegetativeGrowth);
  if (request.indexOf("/PHASE=FLOWERING") != -1) selectPhase(flowering);
  if (request.indexOf("/PHASE=POLLINATION") != -1) selectPhase(pollination);
  if (request.indexOf("/PHASE=FRUIT") != -1) selectPhase(fruit);

  // Relay control requests
  if (request.indexOf("/AIRVENT=ON") != -1) controlRelay(relayAirVent, true);
  if (request.indexOf("/AIRVENT=OFF") != -1) controlRelay(relayAirVent, false);
  if (request.indexOf("/HEATER=ON") != -1) controlRelay(relayHeater, true);
  if (request.indexOf("/HEATER=OFF") != -1) controlRelay(relayHeater, false);
  if (request.indexOf("/COOLER=ON") != -1) controlRelay(relayCooler, true);
  if (request.indexOf("/COOLER=OFF") != -1) controlRelay(relayCooler, false);
  if (request.indexOf("/HUMIDIFIER=ON") != -1) controlRelay(relayHumidifier, true);
  if (request.indexOf("/HUMIDIFIER=OFF") != -1) controlRelay(relayHumidifier, false);
  if (request.indexOf("/LIGHT=ON") != -1) controlRelay(relayLight, true);
  if (request.indexOf("/LIGHT=OFF") != -1) controlRelay(relayLight, false);
  if (request.indexOf("/WATERHEATER=ON") != -1) controlRelay(relayWaterHeater, true);
  if (request.indexOf("/WATERHEATER=OFF") != -1) controlRelay(relayWaterHeater, false);
  if (request.indexOf("/WATERCOOLER=ON") != -1) controlRelay(relayWaterCooler, true);
  if (request.indexOf("/WATERCOOLER=OFF") != -1) controlRelay(relayWaterCooler, false);
  if (request.indexOf("/PUMP1=ON") != -1) controlRelay(relayPump1, true);
  if (request.indexOf("/PUMP1=OFF") != -1) controlRelay(relayPump1, false);
  if (request.indexOf("/PUMP2=ON") != -1) controlRelay(relayPump2, true);
  if (request.indexOf("/PUMP2=OFF") != -1) controlRelay(relayPump2, false);
  if (request.indexOf("/PUMP3=ON") != -1) controlRelay(relayPump3, true);
  if (request.indexOf("/PUMP3=OFF") != -1) controlRelay(relayPump3, false);
}
