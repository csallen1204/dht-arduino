#include <DHT.h>


String output;
String tempBuffer;
int incomingByte = 0;   // for incoming serial data

int PIN_TEMPERATURE = 0;

int PIN_DTH = 8;
#define DHTTYPE DHT11
DHT dht(PIN_DTH, DHTTYPE);


void setup()
{
  analogReference(INTERNAL);
  Serial.begin(9600);
  dht.begin();
}


void loop()
{
  output = "";
  senseTemperature();
  senseDTH();
  Serial.println(output);
}


void senseTemperature()
{
  float tempC;
  float tempF;
  int reading;
  reading = analogRead(PIN_TEMPERATURE);
  tempC = reading / 9.31;
  writeFloat("KEYT", ctof(tempC));
}

void senseDTH()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(t) || isnan(h)) {
    Serial.println("ERROR\tsenseDTH: Failed to read from DHT");
  }
  else {
    writeFloat("DTHT", ctof(t));
    writeFloat("DTHH", h);
  }
}


float ctof(float tempC)
{
  return (9.0F / 5.0F) * tempC + 32.0F;
}

void writeFloat(String sensorType, float sensorValue)
{
  tempBuffer = sensorValue;
  if(output.length() > 0) {
    output = output + "|";
  }
  output = output + sensorType;
  output = output + "=";
  output = output +  tempBuffer;
}

