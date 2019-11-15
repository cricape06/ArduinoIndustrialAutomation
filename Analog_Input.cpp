/*
||
|| @file Objects.h
|| @version 1.0
|| @author Cristian Castro, cricape06@hotmail.com
||
*/

#include "Arduino.h"
#include "Objects.h"

Analog_Input::Analog_Input()
{
}

Analog_Input::Analog_Input(uint8_t Address, float Osh, float Osl): _Address(Address), Osh(Osh), Osl(Osl)
{
	Osh_Real=Osh+Scaled_OffSet;
	Osl_Real=Osl+Scaled_OffSet;
}

int Analog_Input::GetVal()
{
	Iv = (analogRead(_Address)*Ref_Volt)/1023;
	Val = ((Osh_Real-Osl_Real)/(Ish-Isl))*(Iv-Isl)+Osl_Real;
	return Val;		
}

void Analog_Input::OffSet()
{
	Osh_Real=Osh+Scaled_OffSet;
	Osl_Real=Osl+Scaled_OffSet;
	return;
}