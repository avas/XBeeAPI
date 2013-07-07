#ifndef XBEE_S6_H
#define XBEE_S6_H

#define XBEE_S6

#include "util/XBeeBase.h"

class XBeeS6 : public XBeeBase
{
	public:
		uint64_t getIP(byte octet0, byte octet1, byte octet2, byte octet3);
		void sendTx64Request(uint64_t ip, boolean disableACK, int length, byte* data);
};

#endif