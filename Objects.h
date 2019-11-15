/*
||
|| @file Objects.h
|| @version 1.0
|| @author Cristian Castro, cricape06@hotmail.com
||
|| @description
|| | It Provides an easy way (Object Oriented) to structure a program where Pneumatic
|| | Pneumatic equipment is used.
|| #
||
*/

#ifndef Objects_h
#define Objects_h

#include "Arduino.h"
#include "lin_defines.h"


class Valve{ 
  /*Created as a 2 Solenoid Valve. However,
   * it can be defined as a single Solenoid
   * Valve
   */
	
	public:
	
		#define V_OPEN  1
    #define V_CLOSE 0
    
    Valve();                           //Constructor #1
    Valve(uint8_t Sol1);               //Constructor #2
		Valve(uint8_t Sol1, uint8_t Sol2); //Constructor #3
    //Valve(uint8_t Sol1, uint8_t* FB_Open1);                                  //Enable When Feedback Sensor Installed       
    //Valve(uint8_t Sol1, uint8_t Sol2, uint8_t* FB_Open1, uint8_t* FB_Open2); //Enable When Feedback Sensor Installed 
    
		//uint8_t State;      //Enable when Feedback Sensor Installed
    //uint8_t GetState(); //Enable when Feedback Sensor Installed
    uint8_t Emergency_Stop=1;
		void Sol1Out(bool); //Solenoid 1 Open Command
		void Sol2Out(bool); //Solenoid 2 Open Command 

   private:
    uint8_t _Sol1;
    uint8_t _Sol2;
    //uint8_t *_FB_Open1; //Enable when Feedback Sensor Installed
    //uint8_t *_FB_Open2; //Enable when Feedback Sensor Installed


		
};

class Cylinder{
  /*Defined for Thre position cylinders. It has 2 valves and three switches.
   *Objects (Cylinders) can be defined to work with either one or two valves,  
   *and either two or three reed switches.
   */
	
  public:
  
	#define NOSIGNAL  0
	#define RETRACTED 1
	#define EXTENDED  2
	#define INTERMEDIATE 3
	#define FAULTY    4

    Cylinder(); 
    Cylinder(uint8_t Switch1, uint8_t Switch2, uint8_t Switch3, Valve& , Valve&);  //Three-Position Cylinder 2-Valves 3-Switches
    Cylinder(uint8_t Switch1, uint8_t Switch2, uint8_t Switch3, Valve&);           //Cylinder 1-Valve 3-Switches
    Cylinder(uint8_t Switch1, uint8_t Switch2, Valve&);                            //Cylinder 1-Valve 2-Switches
	
  uint8_t State;
  uint8_t GetState();
  uint8_t Emergency_Stop=1;
	void Extend();       //Extend Cylinder Command
	void Retract();      //Retract Cylinder Command
  void Extend_Three();
  void Retract_Three();
	void Intermediate_Three(); //Used just for 3-Position Cylinder
  void NoPressure_Three();
     
  private: 
    void Control();
    unsigned long Failure_Timer;
    unsigned long Failure_Delay=5000; //Standard:1500 (1.5seg)
    uint8_t _Switch1=0;
    uint8_t _Switch2=0;
    uint8_t _Switch3=0;
    Valve _Valve01;
    Valve _Valve02;

};

class Analog_Input
{

  public:

    #define Sts_PVBad 5 //PV Bad Quality or Out of Range

    Analog_Input();
    Analog_Input(uint8_t Address, float Osh, float Osl);

    int Val;
    int GetVal();
    void OffSet();
    
    float Scaled_OffSet=0; //Offset Scaled Value
    float Osh;  //Output Scale High -- Max Sensor Range
    float Osl;  //Output Scale Low  -- Min Sensor Range
    float Ish=10; //Analog Input Scale High --1023
    float Isl=0;  //Analog Input Scale Low  --0   //1.024 For LoadCell

    float Cfg_FailHiLim=104;     //Out-of-Range (fail) High threshold
    float Cfg_FailLoLim=-2;      //Out-of-Range (fail) Low threshold
    float PSet_HiLim=1.5000000;  //High Status threshold
    float PSet_LoLim=-1.5000000; //Low Status threshold
    

    private:
    float Iv; //Analog Input Value (Volts)
    uint8_t _Address; //PIN Number Controller
    float Osh_Real;   //Osh+Offset
    float Osl_Real;   //Osl+Offset

    float Ref_Volt=10;  //Reference Voltage (10V for Arduino PLC)
};

class Analog_Output
{
  public:

  #define Sts_PVBad 5 //PV Bad Quality or Out of Range

  Analog_Output();
  Analog_Output(uint8_t Address, float Cfg_CVEUMax, float Cfg_CVEUMin, int SP_Manual);

  int _SetPoint; //Iv in Analog_Input
  int _SP_Manual; //Manual SetPoint to be set from UI
  float GetVal();
  
  void SetVal();
  void Manual_SetPoint();
  float _Scaled_OffSet=0; //Offset Scaled Value
  float _Cfg_MinCV = 0;  //Minimum CV (in engineering units, for limiting)
  float _Cfg_MaxCV = 5;  //Maximum CV (in engineering units, for limiting)
  float _Cfg_CVEUMin = 0;  //CV minimum in engineering units (for scaling)
  float _Cfg_CVEUMax = 10;//CV maximum in engineering units (for scaling)
  float _Cfg_CVRawMin = 0; //CV minimum in I/O (raw) units (for scaling)
  float _Cfg_CVRawMax = 255; //CV Maximum in I/O (raw) units (for scaling)


  private:
  float Out_CV;    //CV output in raw (I/O Card) units
  uint8_t _Address; //PIN Number Controller

  //Cut and paste following formula in Analog_Output.cpp file
	//Out_CV = ((Cfg_CVRawMax-Cfg_CVRawMin)/(Cfg_CVEUMax-Cfg_CVEUMin))*(SetPoint-Cfg_CVEUMin)+Cfg_CVRawMin;


};

#endif
