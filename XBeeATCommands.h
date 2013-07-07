#ifndef XBEE_AT_COMMANDS_H
#define XBEE_AT_COMMANDS_H

#include "Arduino.h"
#include <avr/pgmspace.h>

/**

Table of AT commands supported by different XBee devices:

-------------+------------------+------------------+------------------------
   Command   |     XBee S6      |     XBee S2      |    Comments
             | (XB24-WFWIT-001) | (XB24-Z7WIT-004) |
-------------+------------------+------------------+------------------------
             |                  |                  |
    ATDH     |                  |       CRE        | Destination address high (not supported in API mode)
    ATDL     |        +         |       CRE        | Destination address low
	ATZA     |                  |       CRE        | ZigBee: application layer addressing
	ATSE     |                  |       CRE        | ZigBee: source endpoint
	ATCI     |                  |       CRE        | ZigBee: cluster identifier
	ATBI     |                  |       CRE        | ZigBee: binding table index
    ATMY     |        +         |       CRE        | Address of local module
	ATMP     |                  |        E         | ZigBee: parent network address
    ATMK     |        +         |                  | WiFi: network mask
    ATGW     |        +         |                  | WiFi: gateway IP address
    ATSH     |        +         |       CRE        | High 32 bits of module's unique serial number
    ATSL     |        +         |       CRE        | Low 32 bits of module's unique serial number
    ATNI     |        +         |       CRE        | Node identifier
    ATDE     |        +         |       CRE        | Destination port / endpoint
    ATC0     |        +         |                  | WiFi: serial communication service port
    ATDD     |        +         |                  | WiFi: Device type
    ATNP     |        +         |                  | WiFi: Maximum RF Payload bytes
             |                  |                  |
             |                  |                  |
	ATBH     |                  |       CRE        | ZigBee: Maximum broadcast hops
	ATNT     |                  |       CRE        | ZigBee: node discover timeout
	ATND     |                  |       CRE        | ZigBee: node discover
	ATDN     |                  |       CRE        | ZigBee: destination node
	ATJN     |                  |       CRE        | ZigBee: join notification
	ATSC     |                  |       CRE        | ZigBee: scan channels
	ATSD     |                  |       CRE        | ZigBee: scan duration
	ATNJ     |                  |       CR         | ZigBee: node join time
	ATAR     |                  |       CR         | ZigBee: aggregate routing notification
    ATID     |        +         |       CRE        | SSID / PAN ID
    ATAH     |        +         |                  | WiFi: network type
    ATIP     |        +         |                  | WiFi: IP protocol
    ATMA     |        +         |                  | WiFi: IP addressing mode
    ATTM     |        +         |                  | WiFi: TCP timeout
             |                  |                  |
             |                  |                  |
    ATEE     |        +         |                  | WiFi: encryption enable
    ATPK     |        +         |                  | WiFi: security key
             |                  |                  |
             |                  |                  |
	ATPM     |                  |       CRE        | ZigBee: power mode
    ATPL     |        +         |       CRE        | Power level
    ATCH     |        +         |       CRE        | Operating channel
    ATBR     |        +         |                  | WiFi: bit rate on IBSS creator
             |                  |                  |
             |                  |                  |
    ATAP     |        +         |       CRE        | API mode enable
    ATAO     |                  |       CRE        | API mode options
    ATBD     |        +         |       CRE        | Interface data rate
    ATNB     |        +         |                  | S6: UART parity
    ATSB     |        +         |                  | S6: UART stop bits
    ATRO     |        +         |       CRE        | Packetization timeout
    ATFT     |        +         |                  | S6: UART flow control threshold
    ATD7     |        +         |       CRE        | DIO7 configuration
    ATD6     |        +         |       CRE        | DIO6 configuration
             |                  |                  |
             |                  |                  |
    ATIR     |        +         |                  | S6: IO sample rate
    ATIC     |        +         |                  | S6: IO digital change detection
    ATIF     |        +         |                  | S6: samples from sleep rate
    ATP0     |        +         |       CRE        | PWM0 / DIO10 configuration
    ATP1     |        +         |       CRE        | DIO11 configuration
    ATP2     |        +         |       CRE        | DIO12 configuration
    ATD0     |        +         |       CRE        | AD0/DIO0 configuration
    ATD1     |        +         |       CRE        | AD1/DIO1 configuration
    ATD2     |        +         |       CRE        | AD2/DIO2 configuration
    ATD3     |        +         |       CRE        | AD3/DIO3 configuration
    ATD4     |        +         |       CRE        | DIO4 configuration
    ATD5     |        +         |       CRE        | DIO5 configuration (associated LED)
    ATD8     |        +         |                  | DIO8 / SLEEP_RQ configuration (not supported by S2)
    ATD9     |        +         |                  | DIO9 / ON_SLEEP configuration (not supported by S2)
    ATLT     |        +         |                  | S6: Assoc LED blink time
    ATPR     |        +         |                  | S6: pull-up resistors state
	ATRP     |                  |       CRE        | ZigBee: RSSI PWM timer
    ATIS     |        +         |       CRE        | Force samples to be read
             |                  |                  |
             |                  |                  |
    ATVR     |        +         |       CRE        | Firmware version
    ATHV     |        +         |       CRE        | Hardware version
    ATAI     |        +         |       CRE        | Association Indication
    ATAS     |        +         |                  | WiFi: active scan
    ATTP     |        +         |                  | S6: read temperature (degrees Celsius)
    ATCK     |        +         |                  | S6: configuration code
    AT%V     |        +         |                  | S6: read VCC (mV)
             |                  |                  |
             |                  |                  |
    ATCT     |        +         |       CRE        | Command mode timeout
    ATCN     |        +         |       CRE        | Exit command mode
    ATGT     |        +         |       CRE        | Guard times (before/after entering command mode)
    ATCC     |        +         |       CRE        | Command sequence character
             |                  |                  |
             |                  |                  |
    ATSM     |        +         |       RE         | Sleep mode
    ATSP     |        +         |       CRE        | Sleep period
	ATSN     |                  |       RE         | Number of sleep periods
    ATSO     |        +         |                  | WiFi: sleep options
    ATWH     |        +         |                  | Wake host timer
    ATST     |        +         |       RE         | Time before sleep
             |                  |                  |
             |                  |                  |
    ATAC     |        +         |                  | Apply changes
    ATWR     |        +         |       CRE        | Write settings to non-volatile memory
	ATWB     |                  |       CRE        | Write binding table to non-volatile memory
    ATRE     |        +         |       CRE        | Restore default settings
    ATFR     |        +         |       CRE        | Software reset
    ATNR     |        +         |       CRE        | Network reset
             |                  |                  |
 */

#define XBEE_AT_PREFIX_LENGTH 2
#define XBEE_AT_COMMAND_LENGTH 2
 
typedef prog_char XBeeATPrefix[XBEE_AT_PREFIX_LENGTH];
typedef prog_char XBeeAT[XBEE_AT_COMMAND_LENGTH];
 
const XBeeATPrefix XBEE_AT_PREFIX = { 'A', 'T' };

void copyCommand(XBeeAT* command, char* destination)
{

}

void writeFullCommand(XBeeAT* command, Stream* stream)
{

}

/**
 * Addressing commands
 */
const XBeeAT XBEE_ATDL = { 'D', 'L' };
const XBeeAT XBEE_ATMY = { 'M', 'Y' };
const XBeeAT XBEE_ATSH = { 'S', 'H' };
const XBeeAT XBEE_ATSL = { 'S', 'L' };
const XBeeAT XBEE_ATNI = { 'N', 'I' };
const XBeeAT XBEE_ATDE = { 'D', 'E' };

/**
 * Networking commands
 */
const XBeeAT XBEE_ATID = { 'I', 'D' };

/**
 * RF interfacing commands
 */
const XBeeAT XBEE_ATPL = { 'P', 'L' };
const XBeeAT XBEE_ATCH = { 'C', 'H' };

#define XBEE_ATAH_IBSS_CREATOR   0
#define XBEE_ATAH_IBSS_JOINER    1
#define XBEE_ATAH_INFRASTRUCTURE 2

#define XBEE_ATIP_UDP 0
#define XBEE_ATIP_TCP 1

#define XBEE_ATMA_DHCP   0
#define XBEE_ATMA_STATIC 1

#define XBEE_ATJN_DISABLED    0
#define XBEE_ATJN_COORDINATOR 1
#define XBEE_ATJN_BROADCAST   2

/**
 * Security commands
 */

#define XBEE_ATEE 0x4545 // Encryption Enable (XBEE_ATEE_*)
#define XBEE_ATPK 0x504B // Security key (write-only)

#define XBEE_ATEE_DISABLED 0
#define XBEE_ATEE_WPA      1
#define XBEE_ATEE_WPA2     2

/**
 * RF interfacing commands
 */

#define XBEE_ATPL 0x504C // Power Level (XBEE_ATPL_*)
#define XBEE_ATPM 0x504D // ZigBee: power mode (XBEE_ATPM_*)
#define XBEE_ATCH 0x4348 // Operating channel
#define XBEE_ATBR 0x4252 // Bitrate, usable only for IBSS-creator (XBEE_ATBR_*)

#define XBEE_ATPL_LOWEST  0
#define XBEE_ATPL_LOW     1
#define XBEE_ATPL_MEDIUM  2
#define XBEE_ATPL_HIGH    3
#define XBEE_ATPL_HIGHEST 4
 
#define XBEE_ATPM_BOOST_DISABLED 0
#define XBEE_ATPM_BOOST_ENABLED 1
 
#define XBEE_ATBR_AUTO 0
#define XBEE_ATBR_1MBPS 1
#define XBEE_ATBR_2MBPS 2
#define XBEE_ATBR_5_5MBPS 3
#define XBEE_ATBR_11MBPS 4
#define XBEE_ATBR_6MBPS 5
#define XBEE_ATBR_9MBPS 6
#define XBEE_ATBR_12MBPS 7
#define XBEE_ATBR_18MBPS 8
#define XBEE_ATBR_24MBPS 9
#define XBEE_ATBR_36MBPS 0x0A
#define XBEE_ATBR_48MBPS 0x0B
#define XBEE_ATBR_54MBPS 0x0C
#define XBEE_ATBR_MCS0 0x0D
#define XBEE_ATBR_MCS1 0x0E
#define XBEE_ATBR_MCS2 0x0F
#define XBEE_ATBR_MCS3 0x10
#define XBEE_ATBR_MCS4 0x11
#define XBEE_ATBR_MCS5 0x12
#define XBEE_ATBR_MCS6 0x13
#define XBEE_ATBR_MCS7 0x14
 
/**
 * Serial interfacing
 */
 
#define XBEE_ATAP 0x4150 // API enable (XBEE_ATAP_*)
#define XBEE_ATBD 0x4244 // BauDrate (XBEE_ATBD_*)
#define XBEE_ATNB 0x4E42 // Serial parity (XBEE_ATNB_*)
#define XBEE_ATSB 0x5342 // Stop bits (XBEE_ATSB_*)
#define XBEE_ATRO 0x524F // Packetization timeout (x100 us)
#define XBEE_ATFT 0x4654 // Flow control Threshold
#define XBEE_ATD7 0x4437 // DIO7 configuration (XBEE_ATDX_* except for XBEE_ATDX_ANALOG_INPUT, XBEE_ATD7_*)
#define XBEE_ATD6 0x4436 // DIO6 configuration (XBEE_ATDX_* except for XBEE_ATDX_ANALOG_INPUT, XBEE_ATD6_*)

#define XBEE_ATAP_TRANSPARENT 0
#define XBEE_ATAP_API         1
#define XBEE_ATAP_API_ESCAPED 2

#define XBEE_ATBD_1200   0
#define XBEE_ATBD_2400   1
#define XBEE_ATBD_4800   2
#define XBEE_ATBD_9600   3
#define XBEE_ATBD_19200  4
#define XBEE_ATBD_38400  5
#define XBEE_ATBD_57600  6
#define XBEE_ATBD_115200 7
#define XBEE_ATBD_230400 8

#define XBEE_ATNB_NO_PARITY   0
#define XBEE_ATNB_EVEN_PARITY 1
#define XBEE_ATNB_ODD_PARITY  2

#define XBEE_ATSB_1 0
#define XBEE_ATSB_2 1

#define XBEE_ATDX_DISABLED     0
#define XBEE_ATDX_ANALOG_INPUT 2
#define XBEE_ATDX_INPUT        3
#define XBEE_ATDX_OUTPUT_LOW   4
#define XBEE_ATDX_OUTPUT_HIGH  5

#define XBEE_ATD7_CTS_FLOW_CONTROL  1
#define XBEE_ATD7_RS485_LOW_ENABLE  6
#define XBEE_ATD7_RS485_HIGH_ENABLE 7

#define XBEE_ATD6_CTS_FLOW_CONTROL 1

/**
 * I/O settings
 */

#define XBEE_ATIR 0x4952 // IO sample rate (x1 ms)
#define XBEE_ATIC 0x4943 // IO digital change detection
#define XBEE_ATIF 0x4946 // Sample from sleep rate
#define XBEE_ATP0 0x5030 // DIO10 configuration (XBEE_ATDX_* except for XBEE_ATDX_ANALOG_INPUT)
#define XBEE_ATP1 0x5031 // DIO11 configuration (XBEE_ATDX_* except for XBEE_ATDX_ANALOG_INPUT)
#define XBEE_ATP2 0x5032 // DIO12 configuration (XBEE_ATDX_* except for XBEE_ATDX_ANALOG_INPUT, XBEE_ATP2_SPI_MISO)
#define XBEE_ATD0 0x4430 // AD0/DIO0 configuration (XBEE_ATDX_*)
#define XBEE_ATD1 0x4431 // AD1/DIO1 configuration (XBEE_ATDX_*)
#define XBEE_ATD2 0x4432 // AD2/DIO2 configuration (XBEE_ATDX_*, XBEE_ATD2_SPI_MOSI)
#define XBEE_ATD3 0x4433 // AD3/DIO3 configuration (XBEE_ATDX_*, XBEE_ATD3_SPI_SSEL)
#define XBEE_ATD4 0x4434 // DIO4 configuration (XBEE_ATDX_*, XBEE_ATD4_SPI_MOSI)
#define XBEE_ATD5 0x4435 // DIO5 configuration (XBEE_ATDX_* except for XBEE_ATDX_ANALOG_INPUT, XBEE_ATD5_ASSOC_LED)
#define XBEE_ATD8 0x4438 // DIO8 configuration (XBEE_ATDX_* except for XBEE_ATDX_ANALOG_INPUT, XBEE_ATD8_SLEEP_RQ)
#define XBEE_ATD9 0x4439 // DIO9 configuration (XBEE_ATDX_* except for XBEE_ATDX_ANALOG_INPUT, XBEE_ATD9_*)
#define XBEE_ATLT 0x4C54 // Assoc LED blink period (0x00 - 250 ms, 0x14-0xFF x 10 ms)
#define XBEE_ATPR 0x5052 // Pull-up resistor (XBEE_ATPR_*, refer to datasheet)

#define XBEE_ATP2_SPI_MISO  1
#define XBEE_ATD2_SPI_MOSI  1
#define XBEE_ATD3_SPI_SSEL  1
#define XBEE_ATD4_SPI_MOSI  1
#define XBEE_ATD5_ASSOC_LED 1
#define XBEE_ATD8_SLEEP_RQ  1

#define XBEE_ATD9_SLEEP_LED 1
#define XBEE_ATD9_SPI_ATTN  6

#define XBEE_ATPR_NONE    0x0000
#define XBEE_ATPR_ALL     0x7FFF
#define XBEE_ATPR_DEFAULT 0x7F7F

#define XBEE_ATPR_DIO4  (1 << 0)
#define XBEE_ATPR_DIO3  (1 << 1)
#define XBEE_ATPR_DIO2  (1 << 2)
#define XBEE_ATPR_DIO1  (1 << 3)
#define XBEE_ATPR_DIO0  (1 << 4)
#define XBEE_ATPR_DIO6  (1 << 5)
#define XBEE_ATPR_DIO8  (1 << 6) // Sleep request
#define XBEE_ATPR_DIN   (1 << 7)
#define XBEE_ATPR_DIO5  (1 << 8) // Assoc LED
#define XBEE_ATPR_DIO9  (1 << 9) // On/Sleep
#define XBEE_ATPR_DIO12 (1 << 10)
#define XBEE_ATPR_DIO10 (1 << 11)
#define XBEE_ATPR_DIO11 (1 << 12)
#define XBEE_ATPR_DIO7  (1 << 13) // CTS

/**
 * Diagnostics interfacing
 */

#define XBEE_ATVR 0x5652 // Firmware version
#define XBEE_ATHV 0x4856 // Hardware version
#define XBEE_ATAI 0x4149 // Association indication (XBEE_ATAI_*, read-only)
#define XBEE_ATAS 0x4153 // Active scan (may only be issued after ATNR)
#define XBEE_ATTP 0x5450 // Module temperature
#define XBEE_ATCK 0x434B // Configuration code
#define XBEE_AT_V 0x2556 // Supply voltage, mV (originally named AT%V)

#define XBEE_ATAI_SUCCESS             0x00 // joined an AP, established IP addresses and IP listening sockets
#define XBEE_ATAI_INIT                0x01 // WiFi initialization is in progress
#define XBEE_ATAI_SSID_NOT_FOUND      0x22 // SSID not found
#define XBEE_ATAI_SSID_NOT_CONFIGURED 0x23 // SSID not configured
#define XBEE_ATAI_JOIN_FAILED         0x27 // SSID was found, but join failed
#define XBEE_ATAI_LOOKING_FOR_SSID    0xFF // scanning for configured SSID
#define XBEE_ATAI_WAITING_FOR_IP      0x41 // joined network, but waiting for IP (usually caused by DHCP)
#define XBEE_ATAI_SETTING_UP_SOCKETS  0x42 // joined network, got an IP, setting up sockets

#define XBEE_ATAI_NO_PANS             0x21
#define XBEE_ATAI_NO_VALID_PANS       0x22
#define XBEE_ATAI_NJ_EXPIRED          0x23
#define XBEE_NODE_JOIN_FAILED         0x27
#define XBEE_COORDINATOR_START_FAILED 0x2A
#define XBEE_LOOKING_FOR_PARENT       0xFF

/**
 * AT command options
 */

#define XBEE_ATCT 0x4354 // Command mode timeout (x100 ms)
#define XBEE_ATCN 0x434E // Exit command mode
#define XBEE_ATGT 0x4754 // Guard time (x1 ms)
#define XBEE_ATCC 0x4343 // Command mode character (any ASCII character, default is 0x2B)

/**
 * Sleep commands
 */

#define XBEE_ATSM 0x534D // Sleep mode (XBEE_ATSM_*)
#define XBEE_ATSP 0x5350 // Sleep period (x10 ms)
#define XBEE_ATSO 0x534F // Sleep options (combined from XBEE_ATSO_*)
#define XBEE_ATWH 0x5748 // Wake host timer (x1 ms)
#define XBEE_ATST 0x5354 // Wake time (x1 ms)

#define XBEE_ATSM_NO_SLEEP              0
#define XBEE_ATSM_PIN_SLEEP             1
#define XBEE_ATSM_CYCLIC_SLEEP          2
#define XBEE_ATSM_CYCLIC_SLEEP_PIN_WAKE 3

#define XBEE_ATSO_NONE              0x0000
#define XBEE_ATSO_STAY_ASSOCIATED   0x0040
#define XBEE_ATSO_DO_NOT_RESTART_ST 0x0100 // must be always turned on

/**
 * Execution commands
 */

#define XBEE_ATAC 0x4143 // Apply changes
#define XBEE_ATWR 0x5752 // Write configuration to non-volatile memory
#define XBEE_ATRE 0x5245 // Restore default settings
#define XBEE_ATFR 0x4652 // Software reset (returns OK and resets in ~2 seconds)
#define XBEE_ATNR 0x4E52 // Network reset (XBEE_ATNR_*)
#define XBEE_ATIS 0x4953 // Force all enabled digital and analog inputs to be read

#define XBEE_ATNR_RESET_LOCAL_NODE 0 // Reset only this node
#define XBEE_ATNR_RESET_ALL_NODES  1 // Reset all nodes in PAN (not applicable to XBee-WiFi)

#endif