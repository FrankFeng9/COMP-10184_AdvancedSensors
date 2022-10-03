
//I Yizhe Feng, 000798153 certify that this material is my original work. No other person's work has been used without due acknowledgement. 
//I have not made my work available to anyone else.

#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>
// Pin that the DS18B20 is connected to
const int oneWireBus = D3;
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);
//sensor address
DeviceAddress sensorAddress;

void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);
  // Start the DS18B20 sensor
  DS18B20.begin();

  Serial.println("Temperature Application");

  // check DS18B20 connection
  if (DS18B20.getAddress(sensorAddress, 0))
  {

    //get DS18B20 device address
    String DS18B20Address = "";

    for (uint8_t i = 0; i < 8; i++)
    {
      DS18B20Address += String(sensorAddress[i], HEX);
    }
    Serial.println("Found DS18B20 sensor with address: " + DS18B20Address);
  }
  else
  { 
    //no connection
    Serial.println("No DS18B20 temperature sensors are installed");
  }
}
void loop()
{

  if (DS18B20.getAddress(sensorAddress, 0))
  {

    float fTemp;
    // ask DS18B20 for the current temperature
    DS18B20.requestTemperatures();
    // fetch the temperature. We only have 1 sensor, so the index is 0.
    fTemp = DS18B20.getTempCByIndex(0);

    String output;
    if (fTemp < 10)
    {
      output = "Cold!";
    }
    else if ((fTemp >= 10) && (fTemp < 15))
    {
      output = "Cool";
    }
    else if ((fTemp >= 15) && (fTemp < 25))
    {
      output = "Perfect";
    }
    else if ((fTemp >= 25) && (fTemp < 30))
    {
      output = "Warm";
    }
    else if ((fTemp >= 30) && (fTemp <= 35))
    {
      output = "Hot";
    }
    else if (fTemp > 35)
    {
      output = "Too Hot!";
    }

    Serial.println("Current temperature is: " + String(fTemp) + "° C or " + output);

    // wait 5s (5000ms) before doing this again °
    delay(5000);
  }
}

