String send(String sendString)
{
  //serial send section for transfer of temp and status

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

/*
// for debugging to ensure global variables are being updated
  Serial.println("Set Temps and Radio");
  Serial.println(setTempCar1);
  Serial.println(setTempCar2);
  Serial.println(radioCar1);
  Serial.println(radioCar2);
  Serial.println(radioCar3);
*/
}

