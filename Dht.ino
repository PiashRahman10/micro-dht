#include <SoftwareSerial.h>
#include "DHT.h"

#define DHTPIN 7
#define DHTTYPE DHT11

SoftwareSerial B(10, 11); // 10-RX,  11-TX
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  B.begin(9600);
  Serial.begin(9600);
  dht.begin(); // Initialize the DHT sensor
}

void loop() {
  delay(2000);

  // Read humidity and temperature
  float humi = dht.readHumidity();
  float tempC = dht.readTemperature();        // Temperature in Celsius
  float tempF = dht.readTemperature(true);    // Temperature in Fahrenheit

  // Check if the reading failed
  if (isnan(humi) || isnan(tempC) || isnan(tempF)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print("%");

    Serial.print("  |  ");

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print("°C ~ ");
    Serial.print(tempF);
    Serial.println("°F");

    // Send data via Bluetooth
    B.print(humi);
    B.print(" %");
    B.print(",");
    B.print(tempC);
    B.print(" C");
    B.print(",");
    B.print(tempF);
    B.print(" F");
    B.print(";");
  }
  
  delay(20);
}
