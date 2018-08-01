#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2018-03-04 18:08:53

#include "Arduino.h"
#include "Arduino.h"
#include <Arduino.h>
#include <Wire.h>

void turnAllOff() ;
byte getNumericValue() ;
void serialFlush() ;
void setKlok() ;
byte decToBcd(byte val) ;
byte bcdToDec(byte val) ;
void setDS3231time() ;
void readDS3231time()  ;
void displayTime() ;
void turnOnNixie(byte whichNixie, byte figure) ;
ISR(TIMER2_COMPA_vect)  ;
void setup() ;
void loop() ;

#include "Nixieklok.ino"

#include "Helpers.ino"

#endif
