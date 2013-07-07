#include "XBeeS6.h"

uint64_t XBeeS6::getIP(byte octet0, byte octet1, byte octet2, byte octet3)
{
	uint64_t result = (octet0 << 24) | (octet1 << 16) | (octet2 << 8) | octet3;
	return result;
}

void XBeeS6::sendTx64Request(uint64_t ip, boolean disableACK, int length, byte* data)
{
	writeHeader(length + XBEE_API_TX64_REQUEST_HEADER_LENGTH);
	
	writeByte(XBEE_API_TX64_REQUEST);
	writeEscapedByte(XBEE_DUMMY_FRAME_ID); // frame ID
	writeDataInt64(ip);
	
	byte txOptions = disableACK ? XBEE_API_TX64_REQUEST_DISABLE_ACK_MASK : 0x00;
	writeByte(txOptions);
	
	writeData(length, data);
}