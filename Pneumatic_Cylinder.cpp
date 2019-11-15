/*
||
|| @file Objects.h
|| @version 1.0
|| @author Cristian Castro, cricape06@hotmail.com
||
*/

#include "Arduino.h"
#include "Objects.h"

Cylinder::Cylinder()
{
}
Cylinder::Cylinder(uint8_t Switch1, uint8_t Switch2, uint8_t Switch3, Valve& Valve01, Valve& Valve02): 
  _Switch1(Switch1),
  _Switch2(Switch2),
  _Switch3(Switch3),
  _Valve01(Valve01),
  _Valve02(Valve02)
{
}
Cylinder::Cylinder(uint8_t Switch1, uint8_t Switch2, uint8_t Switch3, Valve& Valve01):
  _Switch1(Switch1),
  _Switch2(Switch2),
  _Switch3(Switch3),
  _Valve01(Valve01)
{   
}
Cylinder::Cylinder(uint8_t Switch1, uint8_t Switch2, Valve& Valve01):
  _Switch1(Switch1),
  _Switch2(Switch2),
  _Valve01(Valve01)
{  
}
void Cylinder::Extend()
{
  _Valve01.Sol1Out(HIGH);
  Failure_Timer=millis();
}	
void Cylinder::Retract()
{
  _Valve01.Sol1Out(LOW);
  Failure_Timer=millis();
}
void Cylinder::Extend_Three()
{
  _Valve01.Sol1Out(HIGH);
  _Valve02.Sol1Out(HIGH);
  _Valve02.Sol2Out(LOW);
  Failure_Timer=millis();
}
void Cylinder::Retract_Three()
{
  _Valve01.Sol1Out(LOW);
  _Valve02.Sol1Out(LOW);
  _Valve02.Sol2Out(HIGH);
  Failure_Timer=millis();
}
void Cylinder::Intermediate_Three()
{
  _Valve01.Sol1Out(HIGH);
  _Valve02.Sol1Out(LOW);
  _Valve02.Sol2Out(HIGH);
  Failure_Timer=millis();
}
void Cylinder::NoPressure_Three()
{
  _Valve01.Sol1Out(LOW); //Probably it needs to be HIGH, "Test Cylinder" 
  _Valve02.Sol1Out(LOW);
  _Valve02.Sol2Out(LOW);
  Failure_Timer=millis();
}
uint8_t Cylinder::GetState()
{
  if (_Switch1!=0 && _Switch2!=0 && _Switch3!=0){

    if ((digitalRead(_Switch1)==1) && (digitalRead(_Switch2)==0) && (digitalRead(_Switch3)==0)){
      State=RETRACTED;
      return State;
    }
    else if ((digitalRead(_Switch1)==0) && (digitalRead(_Switch2)==1) && (digitalRead(_Switch3)==0)){
      State=EXTENDED;
      return State;
    }
    else if ((digitalRead(_Switch1)==0) && (digitalRead(_Switch2)==0) && (digitalRead(_Switch3)==1)){
      State=INTERMEDIATE;
      return State;
    }
    else if ((digitalRead(_Switch1)==0) && (digitalRead(_Switch2)==0) && (digitalRead(_Switch3)==0)){
      State=NOSIGNAL;
    }
    if(millis() - Failure_Timer > Failure_Delay) {
      State=FAULTY;
      return State;
    }  
  }
  else if (_Switch1!=0 && _Switch2!=0 && _Switch3==0){
    
    if ((digitalRead(_Switch1)==1) && (digitalRead(_Switch2)==0)){
      State=RETRACTED;
      return State;
    }
    else if ((digitalRead(_Switch1)==0) && (digitalRead(_Switch2)==1)){
      State=EXTENDED;
      return State;
    }
    else if ((digitalRead(_Switch1)==0) && (digitalRead(_Switch2)==0)){
      State=NOSIGNAL;
    }
    if(millis() - Failure_Timer > Failure_Delay) {
      State=FAULTY;
      return State;
    }
  }
  else if (_Switch1!=0 && _Switch2==0 && _Switch3==0){

    if ((digitalRead(_Switch1)==1)){
      State=RETRACTED;
      return State;
    }
    else if ((digitalRead(_Switch1)==0)){
      State=EXTENDED;
      return State;
    }
    if(millis() - Failure_Timer > Failure_Delay) {
      State=FAULTY;
      return State;
    } 
  }
}


