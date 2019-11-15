/*
||
|| @file Objects.h
|| @version 1.0
|| @author Cristian Castro, cricape06@hotmail.com
||
*/

#include "Arduino.h"
#include "Objects.h"

Valve::Valve()
{ 
}

Valve::Valve(uint8_t Sol1): _Sol1(Sol1)
{
}

Valve::Valve(uint8_t Sol1, uint8_t Sol2): _Sol1(Sol1), _Sol2(Sol2)
{
}
/*
Valve::Valve(uint8_t Sol1, uint8_t* FB_Open1): _Sol1(Sol1), _FB_Open1(FB_Open1)
{  //Enable When Feedback Sensor Installed
}
Valve::Valve(uint8_t Sol1, uint8_t Sol2, uint8_t* FB_Open1, uint8_t* FB_Open2):
  _Sol1(Sol1), 
  _Sol2(Sol2),
  _FB_Open1(FB_Open1),
  _FB_Open2(FB_Open2)
{
}
*/

void Valve::Sol1Out(bool Out)
{
  if (Out==1){
    digitalWrite(_Sol1, HIGH);
  }
  else {
    digitalWrite(_Sol1, LOW);
    }
}

void Valve::Sol2Out(bool Out)
{
  if (Out==1){
    digitalWrite(_Sol2, HIGH);
  }
  else {
    digitalWrite(_Sol2, LOW);
    }
}




