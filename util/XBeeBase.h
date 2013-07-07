#ifndef XBEE_BASE_H
#define XBEE_BASE_H

#include <Arduino.h>

//#include <HardwareSerial.h>

#define XBEE_FRAME_DELIMITER 0x7E
#define XBEE_ESCAPE 0x7D

#define XBEE_XON 0x11
#define XBEE_XOFF 0x13

#define XBEE_UNESCAPE 0x20;

#define XBEE_DUMMY_FRAME_ID 0x00
#define XBEE_TEMPORARY_FRAME_ID 0x01

#define XBEE_API_REMOTE_COMMAND_REQUEST 0x07
#define XBEE_API_AT_COMMAND 0x08
#define XBEE_API_AT_QUEUE_PARAMETER_VALUE 0x09
#define XBEE_API_TX_IPV4 0x20
#define XBEE_API_RX64_INDICATOR 0x80
#define XBEE_API_IO_SAMPLE_RX_INDICATOR 0x82
#define XBEE_API_REMOTE_COMMAND_RESPONSE 0x87
#define XBEE_API_AT_COMMAND_RESPONSE 0x88
#define XBEE_API_TX_STATUS 0x89
#define XBEE_API_MODEM_STATUS 0x8A
#define XBEE_API_RX_IPV4 0xB0

/**
 * Base class for all XBee devices supporting API mode. It provides ability to send and receive raw data
 * and limited support for reading and writing API frames. Currently it is used as a base class for
 * classes XBeeS2 and XBeeS6.
 */
class XBeeBase
{
	public:
		/**
		 * Constructor.
		 *
		 * @param controlPort Pointer to the stream (i.e. instance of HardwareSerial or SoftwareSerial)
		 * used to control target XBee module. You should pass here &Serial for any ATmega328-based
		 * Arduino board with I/O Expansion Shield v5.0 (and probably most other XBee-enabled shields),
		 * &Serial1 for any ATmega32u4-based board (Arduino Leonardo, DFRduino Leonardo, DFRduino Romeo v2, etc),
		 * and &Serial, &Serial1 or &Serial2 for Arduino Mega with MEGA I/O Shield (choose port according to
		 * XBee socket you installed the module to).
		 */
		XBeeBase(Stream* controlPort);

		
		void readData();
		
	protected:
		Stream* _controlPort;
		
		boolean _escapementRequired;
		
		byte _checksum;
		
		/**
		 * Resets the checksum. Must be called before the transmission starts
		 */
		void resetChecksum()
		{
			_checksum = 0xFF;
		}
		
		/**
		 * Applies specified byte to the checksum.
		 *
		 * @param value Byte to add to checksum.
		 */
		void addByteToChecksum(byte value)
		{
			_checksum -= value;
		}
		
		/**
		 * Sends the checksum to the module.
		 */
		void writeChecksum()
		{
			writeByte(_checksum);
		}
		


		/**
		 * Writes raw byte of data - just sends it to the control stream as-is. This method
		 * must be used when sent byte must not be escaped - i.e. for frame delimiter (first byte
		 * of the API frame) and for data when escapement is disabled in settings (AP = 1).
		 *
		 * @param data Byte of data to send.
		 */
		void writeRawByte(byte data)
		{
			_controlPort -> write(data);
		}
		
		/**
		 * Writes byte of data and applies escapement if needed. This method must be used
		 * to write any byte of data except for frame delimiter with escapement enabled (AP = 2).
		 *
		 * @param data Byte of data to escape (if needed) and send.
		 */
		void writeEscapedByte(byte data)
		{
			byte dataToWrite = data;
			
			if (byteMustBeEscaped(data))
			{
				writeRawByte(XBEE_ESCAPE);
				dataToWrite ^= XBEE_UNESCAPE;
			}
			
			writeRawByte(dataToWrite);
		}
		
		/**
		 * Writes byte of data and applies escapement if it is required by settings. This method is
		 * advised to use for any data transmission except for writing frame delimiter regardless of
		 * escapement settings - it tracks AP setting itself.
		 *
		 * @param data Byte of data to escape (if needed and required by settings) and send.
		 */
		void writeByte(byte data)
		{
			if (_escapementRequired)
				writeEscapedByte(data);
			else
				writeByte(data);
		}

		/**
		 * Writes byte and adds it to checksum. This method is advised to use for every API frame byte
		 * except for frame delimiter and checksum.
		 *
		 * @param data Byte of data to escape (if needed and required by settings), send and
		 * add to checksum.
		 */
		void writeDataByte(byte data)
		{
			writeByte(data);
				
			addByteToChecksum(data);
		}
		
		/**
		 * Writes 16-bit integer in big-endian style (as required by XBee modules). May be used to write 
		 * length of frame or any 16-bit frame-specific data.
		 */
		void writeDataInt(int data)
		{
			writeDataByte((byte)(data >> 8));
			writeDataByte((byte)(data & 0xFF));
		}

		/**
		 * Writes 64-bit integer in big-endian style (as required by XBee modules).
		 */
		void writeDataInt64(uint64_t data)
		{
			for (byte i = 0; i < sizeof(uint64_t); i++)
			{
				byte offset = (7 - i) * 8;
				writeDataByte((byte)((data >> offset) & 0xFF));
			}
		}
		
		/**
		 * Decides whether given byte must be escaped or not.
		 * 
		 * @param value Byte of data to check.
		 * @return true if value must be escaped.
		 */
		boolean byteMustBeEscaped(byte value)
		{
			return (value == XBEE_FRAME_DELIMITER || value == XBEE_ESCAPE ||
					value == XBEE_XON || value == XBEE_XOFF);
		}
		
		
		/**
		 * Writes API frame header (frame delimiter and frame length).
		 *
		 * @param length Length of frame that will follow this header.
		 */
		void writeHeader(int length);
};

#endif