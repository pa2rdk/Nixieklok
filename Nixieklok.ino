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
