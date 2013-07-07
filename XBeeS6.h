#ifndef XBEE_S6_H
#define XBEE_S6_H

#define XBEE_S6

#include "util/XBeeBase.h"

#define XBEE_API_TX64_REQUEST 0x00

#define XBEE_API_TX64_REQUEST_HEADER_LENGTH 0x000B
#define XBEE_API_TX64_REQUEST_DATA_MAX_LENGTH 1398

#define XBEE_API_TX64_REQUEST_DISABLE_ACK_MASK 0x01

/**
 * Class for XBee S6 WiFi modules (implementing IEEE 802.11b/g/n).
 */
class XBeeS6 : public XBeeBase
{
	public:
		/**
		 * Converts the human-readable IPv4 address (like 192.168.10.25) to the 64-bit form
		 * acceptable by XBee S6 (like 0x00000000C0A80A19). Can be used to form IP address
		 * used by sendTx64Request() method.
		 *
		 * @param octet0 First octet of source IPv4 address.
		 * @param octet1 Second octet of source IPv4 address.
		 * @param octet2 Third octet of source IPv4 address.
		 * @param octet3 Fourth octet of source IPv4 address.
		 *
		 * @return 64-bit integer containing the IP address acceptable by XBee module.
		 */
		static uint64_t getIP(byte octet0, byte octet1, byte octet2, byte octet3);
		
		/**
		 * Sends data to the module with specified address.
		 *
		 * @param ip 64-bit IP address of destination module. You can get it using
		 * getIP() method of this class.
		 * @param disableACK Shows whether the destination module must omit 
		 * the acknowledgement for this request or not.
		 * @param length Length of buffer containing data.
		 * @param data Byte buffer containing data to send.
		 */
		void sendTx64Request(uint64_t ip, boolean disableACK, int length, byte* data);
};

#endif