/* This code is for monitoring and maintaining temperature for up to 2 carboys and just monitoring the third carboy utilizing
 four DS18B20 temperature sensors, two heating pads, and the existing thermastat wiring to control the freezer.  The setpoints
 are controlled via a web interface hosted on a raspberry pi and data is logged and passed via a python script on the raspberry pi.
 Written by Casey McHenry
 Version 1.0*/


#include <OneWire.h>
#include <DallasTemperature.h>

const int ONE_WIRE_BUS = 8;  //data wire is plugged into pin 8

//Defines which pins the relays are connected to
const int relay1Heat = 9;  // receptacle 1 for carboy 1 heating pad
const int relay2Heat = 10;  // receptacle 2 for carboy 2 heating pad
const int relayCool = 11;  // freezer thermostat for cycling compressor
const int insideFan = 12; // controls lid mounted recirc fan (assuming 110V fan)
const int recircFans = 13;  // controls 2 recirc fans near carboy 3  (assuming 5V fans)

//Define global variables
int setTempCar1 = 55;
int setTempCar2 = 55;
float inTemp = 0;
float car1Temp = 0;
float car2Temp = 0;
float car3Temp = 0;
int coolStatus = 0;
int heat1Status = 0;
int heat2Status = 0;
int insideFanStatus = 0;
int recircFanStatus = 0;

OneWire oneWire(ONE_WIRE_BUS);  //setup a OneWire instance to communicate to device

DallasTemperature sensors(&oneWire);  //Pass the oneWire reference to Dallas Temperature

DeviceAddress insideTemp = { 
  0x28, 0xF5, 0x4B, 0x4C, 0x05, 0x00, 0x00, 0xD9 };  // #6
DeviceAddress carboy1Temp = { 
  0x28, 0x54, 0x05, 0x22, 0x05, 0x00, 0x00, 0x7C };  // #7
DeviceAddress carboy2Temp = { 
  0x28, 0xDD, 0x79, 0x21, 0x05, 0x00, 0x00, 0xC4 }; // #8
DeviceAddress carboy3Temp = { 
  0x28, 0x02, 0x02, 0x22, 0x05, 0x00, 0x00, 0xB1 }; // #9
// add in any other device address that you want on the bus

void setup()
{

  Serial.begin(9600);  // initialize serial communications at 9600 bps
  
  // sets pin modes for relays
  pinMode (relay1Heat, OUTPUT);  
  pinMode (relay2Heat, OUTPUT); 
  pinMode (relayCool, OUTPUT);
  pinMode (insideFan, OUTPUT); 
  pinMode (recircFans, OUTPUT); 


  sensors.begin();  //start up the library

  sensors.setResolution(insideTemp, 8);  //set the resolution to 10 bit
  sensors.setResolution(carboy1Temp, 8);  //set the resolution to 10 bit
  sensors.setResolution(carboy2Temp, 8);  //set the resolution to 10 bit
  sensors.setResolution(carboy3Temp, 8);  //set the resolution to 10 bit

}

void loop()
{
  setTempCar1 = 45;
  Serial.print("This is initial set temp 1: ");
  Serial.println(setTempCar1);
  
  // run functions to retrieve carboy set temps
  setTempCar1 = getCar1SetTemp(setTempCar1);
  setTempCar2 = getCar2SetTemp(setTempCar2);
  
  sensors.requestTemperatures();  //requests temperature from sensors

  float inTempC = sensors.getTempC(insideTemp);
  inTemp = (DallasTemperature::toFahrenheit(inTempC));
  float car1TempC = sensors.getTempC(carboy1Temp);
  car1Temp = (DallasTemperature::toFahrenheit(car1TempC));
  float car2TempC = sensors.getTempC(carboy2Temp);
  car2Temp = (DallasTemperature::toFahrenheit(car2TempC));
  float car3TempC = sensors.getTempC(carboy3Temp);
  car3Temp = (DallasTemperature::toFahrenheit(car3TempC));
  

  if (inTemp < setTempCar1 - 10  && inTemp < setTempCar2 - 10)  // keeps freezer from getting too far below both set temps
  {
    digitalWrite(relayCool, LOW);
    coolStatus = 0;
  }

  if (inTemp > setTempCar1 - 10 && inTemp > setTempCar2 - 10) // keeps freezer from turning on too far below set temp
  {
    // if the carboy temp is greater than 2 degrees above the set temp OR inside Temp is more than 5F above set temp => energizes the freezer
    if (car1Temp > setTempCar1 + 2 || car2Temp > setTempCar2 + 2)
    {  
      digitalWrite(relayCool, HIGH);  //energizes the solid state relay for the freezer
      coolStatus = 1;
    }
  }
  if (car1Temp < setTempCar1 - 2)  // if the carboy temp is less than 2 degrees below the set temp energizes the heater
  {
    digitalWrite(relay1Heat, HIGH);  //energizes the solid state relay for heater 1 receptacle
    heat1Status = 1;
  }
  if (car2Temp < setTempCar2 - 2)  // if the carboy temp is less than 2 degrees below the set temp energizes the heater
  {
    digitalWrite(relay2Heat, HIGH);  //energizes the solid state relay for the heater 2 receptacle
    heat2Status = 1;
  }

  // if the carboy temp reaches the set temp or inside temp drops less than 10F below set temp => de-energizes the freezer 
  if (car1Temp <= setTempCar1 && car2Temp <= setTempCar2 || inTemp <= setTempCar1 - 10 || inTemp <= setTempCar2 - 10) 
  {  
    digitalWrite(relayCool, LOW);  //de-energizes the solid state relay for the freezer
    coolStatus = 0;
  }
  if (car1Temp >= setTempCar1)  // if the carboy temp equals set temp, de-energizes the heater
  {
    digitalWrite(relay1Heat, LOW);  //de-energizes the solid state relay for heater 1 receptacle
    heat1Status = 0;
  }
  if (car2Temp >= setTempCar2)  // if the carboy temp equals set temp, de-energizes the heater
  {
    digitalWrite(relay2Heat, LOW);  //de-energizes the solid state relay for the heater 2 receptacle
    heat2Status = 0;
  }

  int tempDiff = 10;  // provides band for differential temp 
  int tempDiff3 = 3;  // privides band for diff temp of carboy 3
  float diffTempHigh = inTemp + tempDiff;
  float diffTempLow = inTemp - tempDiff;

  if (car1Temp >= diffTempHigh || car1Temp <= diffTempLow)
  {
    digitalWrite(insideFan, HIGH);
    insideFanStatus = 1;
  }  
  if (car2Temp >= diffTempHigh || car2Temp <= diffTempLow)
  {
    digitalWrite(insideFan, HIGH);
    insideFanStatus = 1;
  }
  if (car1Temp && car2Temp <= diffTempHigh || car1Temp && car2Temp >= diffTempLow)  
  {
    digitalWrite(insideFan, LOW);
    insideFanStatus = 0;
  }
  if (car3Temp >= inTemp + tempDiff3 || car3Temp <= inTemp - tempDiff3)
  {
    digitalWrite(recircFans, HIGH);
    recircFanStatus = 1;
  }
    else
    {
      digitalWrite(recircFans, LOW);
      recircFanStatus = 0;
    }
  
  delay(1000);
  
  Serial.print("This is set temp 1: ");
  Serial.println(setTempCar1);

    
  //void sendArdData();  
}

void sendArdData(float inTemp, float car1Temp, float car2Temp, float car3Temp, int coolStatus, int heat1Status, 
int heat2Status, int insideFanStatus, int recircFanStatus)
{
  Serial.println(inTemp, 2);
  Serial.print('; ');
  Serial.println(car1Temp, 2);
  Serial.println(car2Temp, 2);
  Serial.println(car3Temp, 2);
  Serial.print(coolStatus);
  Serial.print(heat1Status);
  Serial.print(heat2Status);
  Serial.print(insideFanStatus);
  Serial.print(recircFanStatus);
}
