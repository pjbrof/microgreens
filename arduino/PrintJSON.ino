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

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);

  dht.humidity().getSensor(&sensor);

  // delayMS = sensor.min_delay / 1000;
  delayMS = 60000;
}

void loop()
{
  // Delay between measurements.
  delay(delayMS);

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

  /* Serial.print("\"soil2\": \"");
  Serial.print(growTray1soil2);
  Serial.print("\"");

  Serial.print("\"soil3\": \"");
  Serial.print(growTray1soil3);
  Serial.print("\"");

  Serial.print("\"soil4\": \"");
  Serial.print(growTray1soil4);
  Serial.print("\""); */

  Serial.print("},");
}