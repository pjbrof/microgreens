#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 5

#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

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
  delayMS = 3000; // 300000
}

void loop()
{
  delay(delayMS);

  sensors_event_t event;

  dht.temperature().getEvent(&event);

  Serial.print(event.temperature);
  Serial.print(",");

  dht.humidity().getEvent(&event);

  Serial.print(event.relative_humidity);
  Serial.print(",");

  lightSensor1 = analogRead(A0);
  lightSensor2 = analogRead(A2);

  Serial.print(lightSensor1);
  Serial.print(",");

  Serial.println(lightSensor2);
}
