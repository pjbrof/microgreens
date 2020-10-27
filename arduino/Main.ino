#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2

#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

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
  delay(delayMS);

  sensors_event_t event;

  dht.temperature().getEvent(&event);

  dht.humidity().getEvent(&event);

  lightSensor1 = analogRead(A0);
  lightSensor2 = analogRead(A1);

  growTray1soil1 = analogRead(A2);
  growTray1soil2 = analogRead(A3);
  growTray2soil1 = analogRead(A4);
  growTray2soil2 = analogRead(A5);

  Serial.print(event.temperature);
  Serial.print(",");

  Serial.print(event.relative_humidity);
  Serial.print(",");

  Serial.print(lightSensor1);
  Serial.print(",");

  Serial.print(lightSensor2);
  Serial.print(",");

  Serial.print(growTray1soil1);
  Serial.print(",");

  Serial.print(growTray1soil2);
  Serial.print(",");

  Serial.print(growTray1soil3);
  Serial.print(",");

  Serial.println(growTray1soil4);
}