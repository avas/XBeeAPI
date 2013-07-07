#ifndef XBEE_S2_H
#define XBEE_S2_H

#define XBEE_S2

#include "util/XBeeBase.h"

#define XBEE_S2_MODEM_STATUS 0x8A

/**
 * Class for XBee series 2 modules. Note that it probably can not be used with 
 * Series 1 modules or Series 2 Pro modules. If your module has label "MaxStream XBee Series 2"
 * or "Digi International XBee S2" then you can safely use this class.
 */
class XBeeS2 : public XBeeBase
{
	public:
		
};

#endif