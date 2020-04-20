#line 1 "/Users/robertdekok/Dropbox/Arduino-workspace/Nixieklok/Nixieklok.ino"
//By R.J. de Kok - (c) 2018
#include "Arduino.h"
#include <Arduino.h>
#include <Wire.h>

#define DS3231_I2C_ADDRESS 0x68

int x = 0;

int timer1_counter = 34286;
byte actNixie = 1;
byte digit1 = 0;
byte digit2 = 1;
byte digit3 = 2;
byte digit4 = 3;
bool secLed = 0;
bool isSummerTime = 0;

char receivedString[8];
char chkGS[3] = "GS";
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;

#line 23 "/Users/robertdekok/Dropbox/Arduino-workspace/Nixieklok/Nixieklok.ino"
void turnOnNixie(byte whichNixie, byte figure);
#line 70 "/Users/robertdekok/Dropbox/Arduino-workspace/Nixieklok/Nixieklok.ino"
void setup();
#line 126 "/Users/robertdekok/Dropbox/Arduino-workspace/Nixieklok/Nixieklok.ino"
void loop();
#line 1 "/Users/robertdekok/Dropbox/Arduino-workspace/Nixieklok/Helpers.ino"
void turnAllOff();
#line 12 "/Users/robertdekok/Dropbox/Arduino-workspace/Nixieklok/Helpers.ino"
byte getNumericValue();
#line 41 "/Users/robertdekok/Dropbox/Arduino-workspace/Nixieklok/Helpers.ino"
void serialFlush();
#line 50 "/Users/robertdekok/Dropbox/Arduino-workspace/Nixieklok/Helpers.ino"
void setKlok();
#line 75 "/Users/robertdekok/Dropbox/Arduino-workspace/Nixieklok/Helpers.ino"
byte decToBcd(byte val);
#line 79 "/Users/robertdekok/Dropbox/Arduino-workspace/Nixieklok/Helpers.ino"
byte bcdToDec(byte val);
#line 84 "/Users/robertdekok/Dropbox/Arduino-workspace/Nixieklok/Helpers.ino"
void setDS3231time();
#line 98 "/Users/robertdekok/Dropbox/Arduino-workspace/Nixieklok/Helpers.ino"
void readDS3231time();
#line 120 "/Users/robertdekok/Dropbox/Arduino-workspace/Nixieklok/Helpers.ino"
void displayTime();
#line 23 "/Users/robertdekok/Dropbox/Arduino-workspace/Nixieklok/Nixieklok.ino"
void turnOnNixie(byte whichNixie, byte figure) {
  digitalWrite(A0, ((figure & 2) == 2));
  digitalWrite(A1, ((figure & 4) == 4));
  digitalWrite(A2, ((figure & 8) == 8));
  switch (whichNixie) {
    case 1:
      digitalWrite(2, ((figure & 1) == 0));
      digitalWrite(3, ((figure & 1) == 1));
      break;
    case 2:
      digitalWrite(4, ((figure & 1) == 0));
      digitalWrite(5, ((figure & 1) == 1));
      break;
    case 3:
      digitalWrite(6, ((figure & 1) == 0));
      digitalWrite(7, ((figure & 1) == 1));
      break;
    case 4:
      digitalWrite(8, ((figure & 1) == 0));
      digitalWrite(9, ((figure & 1) == 1));
      break;
  }
  digitalWrite(10, secLed);
}

ISR(TIMER2_COMPA_vect) // Timer1_COMPA_vect timer compare interrupt service routine
{
  //TCNT1 = timer1_counter;            // preload timer
  actNixie++;
  if (actNixie == 5) actNixie = 1;
  turnAllOff();
  switch (actNixie) {
    case 1:
      turnOnNixie(1, digit1);
      break;
    case 2:
      turnOnNixie(2, digit2);
      break;
    case 3:
      turnOnNixie(3, digit3);
      break;
    case 4:
      turnOnNixie(4, digit4);
      break;
  }
}

void setup() {
  // put your setup code here, to run once:

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  turnAllOff();
  Serial.begin(9600);
  Serial.println(F("Lets start"));
  Wire.begin();

  noInterrupts();           // disable all interrupts
  TCCR2A = 0;// set entire TCCR0A register to 0
  TCCR2B = 0;// same for TCCR0B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR2A = 250;// = (16*10^6) / (500*256) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS22 for 256 prescaler
  TCCR2B |= (1 << CS22); //| (1 << CS00);
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  interrupts();             // enable all interrupts
  for (int i = 0; i < 10; i++) {
    digit1 = i;
    digit2 = i;
    digit3 = i;
    digit4 = i;
    delay(500);
  }

  Serial.println(F("Type GS to enter setup:"));
  delay(5000);
  if (Serial.available()) {
    Serial.println(F("Check for setup"));
    if (Serial.find(chkGS)) {
      setKlok();
    }
  }
  readDS3231time();
  if (month == 3 && dayOfMonth > 24)  isSummerTime = 1;
  if (month == 10 && dayOfMonth < 24) isSummerTime = 1;
  if (month > 3 && month < 10) isSummerTime = 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  displayTime();

  if (month == 3 && dayOfMonth > 24 && dayOfWeek == 1 && hour == 2 && isSummerTime == 0) {
    isSummerTime = 1;
    hour++;
    setDS3231time();
  }
  if (month == 10 && dayOfMonth > 24 && dayOfWeek == 1 && hour == 2  && isSummerTime == 1) {
    isSummerTime = 0;
    hour--;
    setDS3231time();
  }
}

// Convert binary coded decimal to normal decimal numbers

#line 1 "/Users/robertdekok/Dropbox/Arduino-workspace/Nixieklok/Helpers.ino"
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

