// Serial test script

int setTemp1 = 55;
int setTemp2 = 50;
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
  while(!Serial.available()) {
  }
  // serial read section
  while (Serial.available())  //only runs while serial connection is available
  {
    //Prints the initial settings
    Serial.print("Set Temp 1: ");
    Serial.println(setTemp1);
    Serial.print("Set Temp 2: ");
    Serial.println(setTemp2);
    Serial.print("Radio Carboy 1: ");
    Serial.println(radioCar1);
    Serial.print("Radio Carboy 2: ");
    Serial.println(radioCar2);
    Serial.print("Radio Carboy 3: ");
    Serial.println(radioCar3);


    if (Serial.available() > 0)  //reads serial buffer if anything is there
    {
      char c = Serial.read();  //gets one byte from serial buffer
      if (c == 'S')   // checks to see if the byte is the S -> begining the message
      {
        readString += c;  // puts the 'S' in the string index 0
        int n = 0;
        while (n < 18)  //while the index is < 18 --- first S already entered above
        {
          c = Serial.read();  // read the byte
          readString += c; //makes the string readString
          n ++;
        }
      }
    }


    //once the entire message is received, starts breaking it up to update variables
    //if statements protect against garbled messages

    if (readString[0] == 'S' && readString[1] == '1')
    {
      String set1 = readString.substring(2,4);
      setTemp1 = set1.toInt();

      String setString1;
      setString1 = String(setTemp1);
      Serial.print("New Set Temp 1: ");
      Serial.println(setString1);
    }

    if (readString[4] == 'S' && readString[5] == '2')
    {
      String set2 = readString.substring(6,8);
      setTemp2 = set2.toInt();

      String setString2;
      setString2 = String(setTemp2);
      Serial.print("New Set Temp 2: ");
      Serial.println(setString2);
    }

    if (readString[8] == 'C' && readString[9] == '1')
    {
      String C1 = readString.substring(10,11);
      radioCar1 = C1.toInt();

      String carString1;
      carString1 = String(radioCar1);
      Serial.print("New Radio Car 1: ");
      Serial.println(carString1);
    }

    if (readString[11] == 'C' && readString[12] == '2')
    {
      String C2 = readString.substring(13,14);
      radioCar2 = C2.toInt();

      String carString2;
      carString2 = String(radioCar2);
      Serial.print("New Radio Car 2: ");
      Serial.println(carString2);
    }

    if (readString[14] == 'C' && readString[15] == '3')
    {
      String C3 = readString.substring(16,17);
      radioCar3 = C3.toInt();

      String carString3;
      carString3 = String(radioCar3);
      Serial.print("New Radio Car 3: ");
      Serial.println(carString3);
    }

    // prints to serial connection what was received by the alamode
    Serial.println("Arduino received: ");  
    Serial.println(readString); //see what was received
    readString = "";  //resets readString to blank

    //flush the serial connection after message is completely received
    Serial.flush();
  }

  delay(500);

  //serial send section for transfer of temp and status
  inTemp = 73.245;
  car1Temp = 72.3456;
  car2Temp = 65.2346;
  car3Temp = 87.56232;
  coolStatus = 1;
  heat1Status = 0;
  heat2Status = 1;
  insideFanStatus = 1;
  car3FanStatus = 1;
  
  
  /*String iTemp = String((int)inTemp);
  String c1Temp = String((int)car1Temp);
  String c2Temp = String((int)car2Temp);
  String c3Temp = String((int)car3Temp);
  String cStatus = String(coolStatus);
  String h1Status = String(heat1Status);
  String h2Status = String(heat2Status);
  String iFStatus = String(insideFanStatus);
  String c3FStatus = String(car3FanStatus);
  */

  Serial.println("Temps and Status:");
  Serial.println(inTemp,1);
  Serial.println(car1Temp,1);
  Serial.println(car2Temp,1);
  Serial.println(car3Temp,1);
  

}




