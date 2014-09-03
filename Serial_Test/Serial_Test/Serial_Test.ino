// Serial test script

int setTemp1 = 55;
int setTemp2 = 50;
String readString;

void setup()
{

  Serial.begin(9600);  // initialize serial communications at 9600 bps

}

void loop()
{
  while(!Serial.available()) {
  }
  // serial read section
  while (Serial.available())
  {
    Serial.print("Set Temp 1: ");
    Serial.println(setTemp1);
    Serial.print("Set Temp 2: ");
    Serial.println(setTemp2);
    
    if (Serial.available() >0)
    {
      char c = Serial.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
    }
  }

  if (readString.length() >=3)
  {
    if (readString[0] == 'S' && readString[1] == '1')
    {
      String set1 = readString.substring(2,4);
      setTemp1 = set1.toInt();
      //String setString;
      //setString = String(setTemp1);

      //Serial.print("Set Temp 1: ");
      //Serial.println(setString);
      //Serial.print("\n");
    }
  }

  String setString1;
  setString1 = String(setTemp1);
  Serial.print("New Set Temp 1: ");
  Serial.println(setString1);
  Serial.print("\n");

  if (readString.length() >=8)
  {
    if (readString[4] == 'S' && readString[5] == '2')
    {
      String set2 = readString.substring(6,8);
      setTemp2 = set2.toInt();
    }
  }

  String setString2;
  setString2 = String(setTemp2);
  Serial.print("New Set Temp 2: ");
  Serial.println(setString2);
  Serial.print("\n");

  if (readString.length() >3)
  {
    Serial.println("Arduino received: ");  
    Serial.println(readString); //see what was received
    readString = "";
  }

  delay(500);

  // serial write section


  Serial.flush();
}






