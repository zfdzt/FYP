#ifndef _GLOBALSVARIABLES_H_
#define _GLOBALSVARIABLES_H_
#include "SDKDLL.h"
#include "Channel.h"



CChannel Ch1,Ch2;
CTrigger Trigger;

WORD Level[62];

struct ControlStruct ControlState;	
struct StateStruct FiltAndTrigger;
struct LeversStruct Levers;
struct AutosetStruct AutosetData;
struct TimeStruct TimeData;

int StartCapture;
int StartMonitor;
int InterpolationLineMode;
int PointOrLine;
int DeviceIndex;
int ScrollMode;
int Unit;
bool Ch1InGND,Ch2InGND;
bool XYMode;
double Sampling;
double Time;

double Time_saved_1, Time_saved_2;
double Data1[32780];
double Data2[32780];
double Data1_b[32780];
double Data2_b[32780];
double Data1_c[32780];
double Data2_c[32780];
double Data1_m[32780]; 
double Data2_m[32780]; 
double Data1_n[32780]; 
double Data2_n[32780];
double Data1_HardWareData[32780];
double Data2_HardWareData[32780];
double Capacitance;
int span = 500;
#endif