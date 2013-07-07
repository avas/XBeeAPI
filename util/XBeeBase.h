#ifndef XBEE_BASE_H
#define XBEE_BASE_H

#include <Arduino.h>

//#include <HardwareSerial.h>

#define XBEE_FRAME_DELIMITER 0x7E
#define XBEE_ESCAPE 0x7D

#define XBEE_XON 0x11
#define XBEE_XOFF 0x13

#define XBEE_UNESCAPE 0x20;

#define XBEE_DUMMY_FRAME_ID 0x01

#define XBEE_API_TX64_REQUEST 0x00
#define XBEE_API_AT_COMMAND 0x08
#define XBEE_API_AT_QUEUE_PARAMETER_VALUE 0x09
#define XBEE_API_REMOTE_COMMAND_REQUEST 0x07
#define XBEE_API_TX_IPV4 0x20
#define XBEE_API_RX64_INDICATOR 0x80
#define XBEE_API_AT_COMMAND_RESPONSE 0x88
#define XBEE_API_TX_STATUS 0x89
#define XBEE_API_MODEM_STATUS 0x8A
#define XBEE_API_IO_SAMPLE_RX_INDICATOR 0x82
#define XBEE_API_REMOTE_COMMAND_RESPONSE 0x87
#define XBEE_API_RX_IPV4 0xB0

#define XBEE_API_TX64_REQUEST_HEADER_LENGTH 0x000B
#define XBEE_API_TX64_REQUEST_DATA_MAX_LENGTH 1398

#define XBEE_API_TX64_REQUEST_DISABLE_ACK_MASK 0x01

//#include "../XBeeATCommands.h"

/**
 * Base class for all XBee devices supporting API mode.
 */
class XBeeBase
{
	public:
		XBeeBase(Stream* controlPort);

		void readData();
		
	protected:
		Stream* _controlPort;
		
		boolean _escapementRequired;
		
		byte _checksum;
		
		void resetChecksum()
		{
			_checksum = 0xFF;
		}
		
		void addByteToChecksum(byte value)
		{
			_checksum -= value;
		}
		
		void writeChecksum()
		{
			writeDataByte(_checksum);
		}
		


		void writeByte(byte data)
		{
			_controlPort -> write(data);
		}
		
		void writeEscapedByte(byte data)
		{
			byte dataToWrite = data;
			
			if (byteMustBeEscaped(data))
			{
				writeByte(XBEE_ESCAPE);
				dataToWrite ^= XBEE_UNESCAPE;
			}
			
			writeByte(dataToWrite);
		}
		
		void writeDataInt(int data)
		{
			writeDataByte((byte)(data >> 8));
			writeDataByte((byte)(data & 0xFF));
		}

		void writeDataInt64(uint64_t data)
		{
			for (byte i = 0; i <= 7; i++)
			{
				byte offset = (7 - i) * 8;
				writeDataByte((byte)((data >> offset) & 0xFF));
			}
		}
		
		boolean byteMustBeEscaped(byte value)
		{
			return (value == XBEE_FRAME_DELIMITER || value == XBEE_ESCAPE ||
					value == XBEE_XON || value == XBEE_XOFF);
		}
		
		void writeDataByte(byte data)
		{
			if (_escapementRequired)
				writeEscapedByte(data);
			else
				writeByte(data);
				
			addByteToChecksum(data);
		}
		
		void writeHeader(int length);
		
		void writeData(int length, byte* data);	
};

#endif