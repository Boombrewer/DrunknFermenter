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
  Serial.flush();
  
  //String receive(readString);  //function to receive info from python
  //receiveProcess();  //processes the received string to update the global variables

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

  String iTemp = String((int)inTemp);
  String c1Temp = String((int)car1Temp);
  String c2Temp = String((int)car2Temp);
  String c3Temp = String((int)car3Temp);
  String cStatus = String(coolStatus);
  String h1Status = String(heat1Status);
  String h2Status = String(heat2Status);
  String iFStatus = String(insideFanStatus);
  String c3FStatus = String(car3FanStatus);

  //hangs until serial is available
  while(!Serial.available()) {
  }

  while (Serial.available())  //only runs while serial connection is available
  {
    Serial.flush();

    Serial.print("Temps and Status: ");
    Serial.print(";");
    Serial.print(iTemp);
    Serial.print(";");
    Serial.print(c1Temp);
    Serial.print(";");
    Serial.print(c2Temp);
    Serial.print(";");
    Serial.println(c3Temp);
  }

}

