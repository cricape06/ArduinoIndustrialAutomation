/*
||
|| @file Objects.h
|| @version 1.0
|| @author Cristian Castro, cricape06@hotmail.com
||
*/

#include "Arduino.h"
#include "Objects.h"

Analog_Output::Analog_Output()
{
}

Analog_Output::Analog_Output(uint8_t Address, float Cfg_CVEUMin, float Cfg_CVEUMax, int SP_Manual): 
_Address(Address), 
_Cfg_CVEUMin(Cfg_CVEUMin),
_Cfg_CVEUMax(Cfg_CVEUMax), 
_SP_Manual(SP_Manual)
{
}

void Analog_Output::SetVal()
{
    if (_SetPoint > _Cfg_MaxCV)
    {
        _SetPoint = _Cfg_MaxCV;
    }
    Out_CV = ((_Cfg_CVRawMax - _Cfg_CVRawMin)/(_Cfg_CVEUMax - _Cfg_CVEUMin))*(_SetPoint - _Cfg_CVEUMin) + _Cfg_CVRawMin;
    analogWrite(_Address, Out_CV);
}

void Analog_Output::Manual_SetPoint()
{
    Out_CV = ((_Cfg_CVRawMax - _Cfg_CVRawMin)/(_Cfg_CVEUMax - _Cfg_CVEUMin))*(_SP_Manual - _Cfg_CVEUMin) + _Cfg_CVRawMin;
    analogWrite(_Address, Out_CV);
}

float Analog_Output::GetVal()
{
	return Out_CV;
}
