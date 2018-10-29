#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include "SDKDLL.h"

class CChannel
{
public:
	
	int Voltage;
	int Position;
	int ACDC;
	int GND;
	int TriggerLevel;
	bool Enable;
	WORD HardwareData[32780];
	WORD BufferData[32780];
	WORD DisplayData[500];
	WORD ScrollData[32780];
	struct LineColor ChannelColor;
	CChannel();
	void SetChannelColor(int,int,int);
};
CChannel::CChannel()
{
	Voltage = 8;
	ACDC = 0;
	GND = 0;
	Enable = TRUE;
}
void CChannel::SetChannelColor(int r,int g,int b)
{
	ChannelColor.R = r;
	ChannelColor.G = g;
	ChannelColor.B = b;
}

class CTrigger
{
public:
	int Slope;
	int Source;
	int Mode;
	int TPosition;

	CTrigger();
};

CTrigger::CTrigger()
{
	Slope = 0;
	Source = 0;
	Mode = 0;
}

#endif