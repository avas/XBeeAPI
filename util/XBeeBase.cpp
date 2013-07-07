#include "XBeeBase.h"

XBeeBase::XBeeBase(Stream* controlPort)
{
	_controlPort = controlPort;
	_escapementRequired = false;
}

void XBeeBase::writeHeader(int length)
{
	writeByte(XBEE_FRAME_DELIMITER);
	
	writeDataInt(length);
	
	// Since data transmission will be started soon, we have to reset checksum.
	resetChecksum();
}