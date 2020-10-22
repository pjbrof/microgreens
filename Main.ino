#include <Time.h>
#include <TimeLib.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2

#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

time_t date;

const int soilMoistureUpperLimit = 473;
const int soilMoistureLowerLimit = 210;
int growTray1soil1 = 0;
int growTray1soil2 = 0;
int growTray2soil1 = 0;
int growTray2soil2 = 0;
int lightSensor1 = 0;
int lightSensor2 = 0;

void setup()
{
    Serial.begin(9600);

    dht.begin();

    // Print temperature sensor details.
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    /* Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C")); */
    // Serial.println(F("------------------------------------"));

    // Print humidity sensor details.
    dht.humidity().getSensor(&sensor);
    /* Serial.println(F("Humidity Sensor"));
   Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
   Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
   Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
   Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
   Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
   Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%")); */
    // Serial.println(F("------------------------------------"));

    // Set delay between sensor readings based on sensor details.
    // delayMS = sensor.min_delay / 1000;
    delayMS = 60000;
}

void loop()
{
    // Delay between measurements.
    delay(delayMS);

    // Get temperature event and print its value.
    /* sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }*/

    date = now();

    Serial.print("{");
    Serial.print("\"date\":\"");
    Serial.print(date);
    Serial.print("\",");

    sensors_event_t event;
    dht.temperature().getEvent(&event);
    Serial.print("\"temp\": \"");
    Serial.print(event.temperature);
    Serial.print("\",");

    dht.humidity().getEvent(&event);
    Serial.print("\"humidity\": \"");
    Serial.print(event.relative_humidity);
    Serial.print("\",");

    lightSensor1 = analogRead(A0);
    lightSensor2 = analogRead(A1);

    Serial.print("\"light1\": \"");
    Serial.print(lightSensor1);
    Serial.print("\",");

    Serial.print("\"light2\": \"");
    Serial.print(lightSensor2);
    Serial.print("\",");

    growTray1soil1 = analogRead(A2);
    //  growTray1soil2 = analogRead(A3);
    //  growTray2soil1 = analogRead(A4);
    //  growTray2soil2 = analogRead(A5);

    // soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);

    Serial.print("\"soil1\": \"");
    Serial.print(growTray1soil1);
    Serial.print("\"");

    //  Serial.print("Grow Tray 1 Soil Moisture Sensor 2: ");
    //  Serial.println(growTray1soil2);
    //
    //
    //  Serial.print("Grow Tray 2 Soil Moisture Sensor 1: ");
    //  Serial.println(growTray2soil1);
    //
    //  Serial.print("Grow Tray 2 Soil Moisture Sensor 2: ");
    //  Serial.println(growTray2soil2);

    Serial.print("},");

    // Serial.println(F("------------------------------------"));
}