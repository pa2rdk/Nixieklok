void turnAllOff() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}

byte getNumericValue() {
  serialFlush();
  byte myByte = 0;
  byte inChar = 0;
  bool isNegative = false;
  receivedString[0] = 0;

  int i = 0;
  while (inChar != 13) {
    if (Serial.available() > 0) {
      inChar = Serial.read();
      if (inChar > 47 && inChar < 58) {
        receivedString[i] = inChar;
        i++;
        Serial.write(inChar);
        myByte = (myByte * 10) + (inChar - 48);
      }
      if (inChar == 45) {
        Serial.write(inChar);
        isNegative = true;
      }
    }
  }
  receivedString[i] = 0;
  if (isNegative == true) myByte = myByte * -1;
  serialFlush();
  return myByte;
}

void serialFlush() {
  for (int i = 0; i < 10; i++)
  {
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}

void setKlok() {
  Serial.print("Year:");
  year = getNumericValue();
  Serial.println(year);
  Serial.print("Month:");
  month = getNumericValue();
  Serial.println(month);
  Serial.print("Day:");
  dayOfMonth = getNumericValue();
  Serial.println(dayOfMonth);
  Serial.print("Day of week (1=sunday):");
  dayOfWeek = getNumericValue();
  Serial.println(dayOfWeek);
  Serial.print("Hour:");
  hour = getNumericValue();
  Serial.println(hour);
  Serial.print("Minute:");
  minute = getNumericValue();
  Serial.println(minute);
  Serial.print("Second:");
  second = getNumericValue();
  Serial.println(second);
  setDS3231time();
}

byte decToBcd(byte val) {
  return ( (val / 10 * 16) + (val % 10) );
}

byte bcdToDec(byte val) {
  return ( (val / 16 * 10) + (val % 16) );
}


void setDS3231time() {
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}

void readDS3231time()
//byte * second, byte * minute, byte * hour, byte * dayOfWeek, byte * dayOfMonth, byte * month, byte * year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  second = bcdToDec(Wire.read() & 0x7f);
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read() & 0x3f);
  dayOfWeek = bcdToDec(Wire.read());
  dayOfMonth = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year = bcdToDec(Wire.read());
  digit4 = (hour / 10);
  digit3 = hour - (digit4 * 10);
  digit2 = (minute / 10);
  digit1 = minute - (digit2 * 10);
  secLed = ((second & 1) == 1);
}

void displayTime()
{
  // retrieve data from DS3231
  readDS3231time();
  // send it to the serial monitor
  Serial.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
  Serial.print(":");
  if (minute < 10)
  {
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second < 10)
  {
    Serial.print("0");
  }
  Serial.print(second, DEC);
  Serial.print(" ");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
  if (isSummerTime==1) Serial.print(" Summertime"); else Serial.print(" Wintertime");
  Serial.print(" Day of week: ");
  switch (dayOfWeek) {
    case 1:
      Serial.println("Sunday");
      break;
    case 2:
      Serial.println("Monday");
      break;
    case 3:
      Serial.println("Tuesday");
      break;
    case 4:
      Serial.println("Wednesday");
      break;
    case 5:
      Serial.println("Thursday");
      break;
    case 6:
      Serial.println("Friday");
      break;
    case 7:
      Serial.println("Saturday");
      break;
  }
}
