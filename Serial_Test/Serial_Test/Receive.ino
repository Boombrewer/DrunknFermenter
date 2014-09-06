String receive(String readString)
{

  //hangs until serial is available
  while(!Serial.available()) {
  }

  while (Serial.available())  //only runs while serial connection is available
  {
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
  }
  return(readString);
}


