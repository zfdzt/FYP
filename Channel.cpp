#include "windows.h"
#include "Channel.h"

CChannel::CChannel()
{
	Voltage = 8;
	ACDC = 0;
	GND = 0;
}
void CChannel::SetPosition(int Position)
{
	this->Position = Position;
}
