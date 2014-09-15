void receiveProcess()
{
  //once the entire message is received, starts breaking it up to update variables
  //if statements protect against garbled messages
  if (readString.length() == 18)
  {
    if (readString[0] == 'S' && readString[1] == '1')
    {
      String set1 = readString.substring(2,4);
      setTempCar1 = set1.toInt();
    }

    if (readString[4] == 'S' && readString[5] == '2')
    {
      String set2 = readString.substring(6,8);
      setTempCar2 = set2.toInt();
    }

    if (readString[8] == 'C' && readString[9] == '1')
    {
      String C1 = readString.substring(10,11);
      radioCar1 = C1.toInt();
    }

    if (readString[11] == 'C' && readString[12] == '2')
    {
      String C2 = readString.substring(13,14);
      radioCar2 = C2.toInt();
    }

    if (readString[14] == 'C' && readString[15] == '3')
    {
      String C3 = readString.substring(16,17);
      radioCar3 = C3.toInt();
    }

    readString = "";  //resets readString to blank

    //flush the serial connection after the message is processed
    Serial.flush();
  }
}


