// Serial test script

int setTempCar1 = 55;
int setTempCar2 = 50;
int radioCar1 = 0;
int radioCar2 = 0;
int radioCar3 = 0;
String readString;
float inTemp = 0;
float car1Temp = 0;
float car2Temp = 0;
float car3Temp = 0;
int coolStatus = 0;
int heat1Status = 0;
int heat2Status = 0;
int insideFanStatus = 0;
int car3FanStatus = 0;

void setup()
{

  Serial.begin(9600);  // initialize serial communications at 9600 bps

}

void loop()
{
  String receive(readString);  //function to receive info from python
  receiveProcess();  //processes the received string to update the global variables
  
  /// do some stuff
  inTemp = 73.245;
  car1Temp = 72.3456;
  car2Temp = 65.2346;
  car3Temp = 87.56232;
  coolStatus = 1;
  heat1Status = 0;
  heat2Status = 1;
  insideFanStatus = 1;
  car3FanStatus = 1;
  
  void send();  // sends info to python
}




