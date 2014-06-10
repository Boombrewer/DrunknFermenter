// script to retrieve current temp setpoint from python script
int getCar1SetTemp(int setTempCar1)
{
  int serialData;
  
  if (Serial.available() > 0)
  {
    serialData = Serial.println();
    Serial.print("This is serial data: ");
    Serial.println(serialData);
    Serial.flush();
    delay(1000);
  }
  else
  {
  Serial.print("No data!");
  Serial.print('\n');
  }

  return setTempCar1;
}


