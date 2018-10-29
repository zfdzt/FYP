#ifndef _SDKDLL_H_
#define _SDKDLL_H_

#define EXPORTDLL extern "C" __declspec (dllimport) 

struct PictureRange
{
    WORD Width;
    WORD Hight;
    WORD Left;
    WORD Right;
    WORD Top;
    WORD Bottom;
};

struct ControlStruct
{
    WORD TriggerSource;
    WORD ChannelSelect;
    WORD TIMEBASE;
    WORD TriggerAddress;
    WORD DataLength;
	WORD BufferSize;
    WORD IsAlt;
};

struct LineColor
{
	WORD R;
	WORD G;
	WORD B;
};

struct AutosetStruct
{
	WORD WhichChannel;
	WORD Ch1Voltage;
	WORD Ch2Voltage;
	WORD Ch1Timebase;
	WORD Ch2Timebase;
	WORD Ch1InGND;
	WORD Ch2InGND;
	WORD Ch1Enabled;
	WORD Ch2Enabled;
};

struct StateStruct
{
	WORD Ch1Filt;
	WORD Ch2Filt;
	WORD TriggerFilt;
	WORD TriggerMode;
	WORD TriggerSlope;
};

struct LeversStruct
{
    WORD Ch1Lever;
    WORD Ch2Lever;
    WORD Ch1TrigLever;
    WORD Ch2TrigLever;
    WORD ExtTrigLever;
};

struct TimeStruct{
	double Timer;
	double Time;
	double ScrollTime;
	double ScrollStart;
};


//Functions For Softwear
EXPORTDLL WORD __stdcall sdMainPanelDrawGrid(HDC ,struct PictureRange * );
EXPORTDLL WORD __stdcall sdDisplayDataXYMode(HDC ,struct PictureRange *, WORD , WORD * , WORD * );
EXPORTDLL WORD __stdcall sdGetDisplayData(struct ControlStruct *,WORD * , WORD * );
EXPORTDLL WORD __stdcall sdDisplayData(HDC ,struct PictureRange *, WORD , WORD * ,struct LineColor * );
EXPORTDLL WORD __stdcall sdChannelDataBuffer(struct ControlStruct *, WORD ,  WORD * ,WORD * );
EXPORTDLL WORD __stdcall sdAutoset(WORD ,struct ControlStruct *,struct AutosetStruct *,struct StateStruct *,struct LeversStruct * ,WORD *);
EXPORTDLL WORD __stdcall sdGetScrollData(WORD ,struct ControlStruct *,struct LeversStruct *,struct TimeStruct *,
									   WORD ,WORD ,WORD *,WORD *,WORD *,WORD *,WORD ,bool ,bool );
EXPORTDLL double __stdcall sdDisplaySampling(bool ,bool ,WORD ,WORD ,WORD ,double *);
EXPORTDLL double __stdcall sdDisplaySampling(bool ,bool ,WORD ,WORD ,WORD ,double *);



//Function For Hardware
EXPORTDLL WORD __stdcall sdSearchDevice(WORD);
EXPORTDLL bool __stdcall sdSetOffset(WORD ,struct LeversStruct * ,WORD ,WORD ,WORD ,WORD* );
EXPORTDLL WORD __stdcall sdSetTriggerAndSampleRate(WORD,WORD,struct ControlStruct *);
EXPORTDLL WORD __stdcall sdSetFilt(WORD ,struct StateStruct *);
EXPORTDLL WORD __stdcall sdSetVoltageAndCoupling(WORD,WORD,WORD,WORD,WORD,WORD);
EXPORTDLL WORD __stdcall sdCaptureStart(WORD);
EXPORTDLL long __stdcall sdTriggerEnabled(WORD);
EXPORTDLL WORD __stdcall sdGetLevel(WORD,WORD*);
EXPORTDLL WORD __stdcall sdChannelInGND(WORD,WORD*);
EXPORTDLL WORD __stdcall sdGetData(WORD ,WORD ,WORD ,WORD * , WORD * ,struct ControlStruct *,
								 struct StateStruct *,struct LeversStruct *,WORD *,int );

















#endif