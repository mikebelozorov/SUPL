// uBlox LEA-6T Data Structures
#ifndef UBLOXSTRUCTURES_H
#define UBLOXSTRUCTURES_H

#include "stdint.h"


#define UBX_SYNC_BYTE_1 0xB5
#define UBX_SYNC_BYTE_2 0x62

#define MSG_CLASS_AID 0x0B
    #define MSG_ID_AID_ALM 0x30
    #define MSG_ID_AID_ALPSRV 0X32
    #define MSG_ID_AID_ALP 0x50
    #define MSG_ID_AID_AOP 0x33
    #define MSG_ID_AID_DATA 0x10
    #define MSG_ID_AID_EPH 0x31
    #define MSG_ID_AID_HUI 0x02
    #define MSG_ID_AID_INI 0x01
    #define MSG_ID_AID_REQ 0x00


#define MAX_NOUT_SIZE      (5000)   // Maximum size of a NovAtel log buffer (ALMANAC logs are big!)
                    // find MAX_NOUT_SIZE for ublox (ask Scott how he go this one for Novatel)

#define MAXCHAN		50  // Maximum number of signal channels
#define MAX_SAT     33  // maximum number of prns - max prn is 32 plus prn 0 is 33

// define macro to pack structures correctly with both GCC and MSVC compilers
#ifdef _MSC_VER // using MSVC
	#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#else
	#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif


PACK(
    struct UbloxHeader {
        uint8_t sync1;   //!< start of packet first byte (0xB5)
        uint8_t sync2;   //!< start of packet second byte (0x62)
        uint8_t message_class; //!< Class that defines basic subset of message (NAV, RXM, etc.)
        uint8_t message_id;		//!< Message ID
        uint16_t payload_length; //!< length of the payload data, excluding header and checksum
});


//////////////////////////////////////////////////////////////
// AIDING DATA MESSAGES
//////////////////////////////////////////////////////////////
/*!
 * AID-INI Message Structure
 * Reciever Position, Time, Clock Drift, Frequency
 * ID: 0x0B  0x01 Payload Length=48 bytes
 */
#define PAYLOAD_LENGTH_AID_INI 48
#define FULL_LENGTH_AID_INI 48+8
PACK(
    struct AidIni {
        struct UbloxHeader header;		//!< Ublox header
        int32_t ecefXorLat;  //!< ECEF x position or latitude [cm or deg*1e-7]
        int32_t ecefYorLon;  //!< ECEF y position or longitude [cm or deg*1e-7]
        int32_t ecefZorAlt;  //!< ECEF z position or altitude [cm]
        uint32_t position_accuracy; //!< position accuracy - std dev [cm]
        uint16_t time_configuration; //!< time configuration bit misk
        uint16_t week_number; //!< actual week number
        uint32_t time_of_week; //!< actual time of week [ms]
        int32_t time_of_week_ns; //!< fractional part of time of week [ns]
        uint32_t time_accuracy_ms; //!< time accuracy [ms]
        uint32_t time_accuracy_ns; //!< time accuracy [ns]
        int32_t clock_drift_or_freq; //!< clock drift or frequency [ns/s or Hz*1e-2]
        uint32_t clock_drift_or_freq_accuracy; //!< clock drift or frequency accuracy [ns/s or ppb]
        uint32_t flags; //!< bit field that determines contents of other fields
        uint8_t checksum[2];
});

// defines for AidIni flags
#define AIDINI_FLAG_POSITION_VALID 0x01
#define AIDINI_FLAG_TIME_VALID 0x02
#define AIDINI_FLAG_CLOCK_DRIFT_VALID 0x04
#define AIDINI_FLAG_USE_TIME_PULSE 0X08
#define AIDINI_FLAG_CLOCK_FREQ_VALID 0x10
#define AIDINI_FLAG_USE_LLA 0x20
#define AIDINI_FLAG_ALTITUDE_INVALID 0X40
#define AIDINI_USE_PREV_TIME_PULSE 0X80

/*!
 * AID-HUI Message Structure
 * GPS Health, Ionospheric, and UTC Parameters
 * ID: 0x0B  0x02 Payload Length: 72
 */
#define PAYLOAD_LENGTH_AID_HUI 72
#define FULL_LENGTH_AID_HUI 72+8
PACK(
    struct AidHui{
		struct UbloxHeader header;
        uint32_t health;
        double a0;
        double a1;
        uint32_t tow;
        int16_t week;
        int16_t beforeleapsecs;
        int16_t nextleapsecweek;
        int16_t nextleapsec;
        int16_t afterleapsecs;
        int16_t spare;
        float kloba0;
        float kloba1;
        float kloba2;
        float kloba3;
        float klobb0;
        float klobb1;
        float klobb2;
        float klobb3;
        uint32_t flags;
        uint8_t checksum[2];
});
// defines for AID-HUI flags
#define AIDHUI_FLAG_HEALTH_VALID 0b001
#define AIDHUI_FLAG_UTC_VALID 0b010
#define AIDHUI_FLAG_KLOB_VALID 0b100

/*!
 * AID-EPH Message Structure
 * This message contains ephemeris for a satellite.
 * ID: 0x0B 0x31 Payload Length = (16) or (112) bytes
 */
#define PAYLOAD_LENGTH_AID_EPH_WITH_DATA 104
#define PAYLOAD_LENGTH_AID_EPH_NO_DATA 8
#define FULL_LENGTH_AID_EPH_WITH_DATA 104+8
#define FULL_LENGTH_AID_EPH_NO_DATA 8+8
PACK(
    struct EphemW{
        uint8_t byte[4];				// Each Word contains 4 bytes (4th is ignored)
});

PACK(
    struct EphemSF{
        //uint32_t W[8];				// Words 3-10 of Subframes
		struct EphemW W[8];
});

PACK(
    struct EphemSV{					// Ephemeris for a Satellite
		struct UbloxHeader header;			// Header
        uint32_t svprn;				// Satellite Number
        uint32_t HOW;				// Hand Over Word
        struct EphemSF SF[3];				// Subframes
        uint8_t checksum[2];		// Checksum
});

PACK(
    struct Ephemerides{             // Holds EphemSV message for all SVs
		struct EphemSV ephemsv[MAX_SAT];
});

// Parsed Ephemeris Parameters for a SV - NOT FINISHED
PACK(
    struct ParsedEphemData {
        uint32_t prn;				//PRN number
        uint8_t tow;				//time stamp of subframe 0 (s)
        //uint8_t tow;				//time stamp of subframe 0 (s)
        unsigned long health;		//health status, defined in ICD-GPS-200
        unsigned long iode1;		//issue of ephemeris data 1
        unsigned long iode2;		//issue of ephemeris data 2
        unsigned long week;			//GPS week number
        unsigned long zweek;		//z count week number
        double toe;					//reference time for ephemeris (s)
        double majaxis;				//semi major axis (m)
        double dN;					//Mean motion difference (rad/s)
        double anrtime;				//mean anomoly reference time (rad)
        double ecc;					//eccentricity
        double omega;				//arguement of perigee (rad)
        double cuc;					//arugument of latitude - cos (rad)
        double cus;					//argument of latitude - sine (rad)
        double crc;					//orbit radius - cos (rad)
        double crs;					//orbit radius - sine (rad)
        double cic;					//inclination - cos (rad)
        double cis;					//inclination - sine (rad)
        double ia;					//inclination angle (rad)
        double dia;					//rate of inclination angle (rad/s)
        double wo;					//right ascension (rad)
        double dwo;					//rate of right ascension (rad/s)
        unsigned long iodc;			//issue of data clock
        double toc;					//SV clock correction term (s)
        double tgd;					//estimated group delay difference
        double af0;					//clock aiging parameter 0
        double af1;					//clock aiging parameter 1
        double af2;					//clock aiging parameter 2
//      yes_no spoof;			//anti spoofing on
        double cmot;				//corrected mean motion
        unsigned int ura;			//user range accuracy variance (value 0-15)
});

// Contains Ephemeris Parameters for all SVs
PACK(
    struct ParsedEphemeridesData{
		struct ParsedEphemData sv_eph_data[MAX_SAT];
});

/*!
 * AID-ALM Message Structure
 * This message contains GPS almanac data for a satellite
 * ID: 0x0B 0x30 Payload Length = (8) or (48) bytes
 */
#define PAYLOAD_LENGTH_AID_ALM_WITH_DATA 40
#define PAYLOAD_LENGTH_AID_ALM_NO_DATA 8
#define FULL_LENGTH_AID_ALM_WITH_DATA 40+8
#define FULL_LENGTH_AID_ALM_NO_DATA 8+8
PACK(
    struct AlmSV{
		struct UbloxHeader header;			// Header
        uint32_t svprn;				// Satellite Number
        uint32_t issue_week;                    // Issue date of Almanac
        uint32_t words[8];			// Words 3-10 of Almanac data for an SV
        uint8_t checksum[2];                    // Checksum
});

// Holds Almanac data for all SVs
PACK(
    struct UbloxAlmanac{
		struct AlmSV almsv[MAX_SAT];
});


enum Message_ID
{
    CFG_PRT = 1536,                 // (ID 0x06 0x00) I/O Protocol Settings
    CFG_NAV5 = 1572,                // (ID 0x06 0x24) Navigation Algorithm Parameter Settings
    NAV_STATUS = 259,               // (ID 0x01 0x03) TTFF, GPS Fix type, time since startup/reset
    NAV_SOL = 262,                  // (ID 0x01 0x06) ECEF Pos,Vel, TOW, Accuracy,
    NAV_VELNED = 274,               // (ID 0x01 0x12) Vel (North, East, Down), Speed, Ground Speed
    NAV_POSLLH = 258,               // (ID 0x01 0x02) Pos (Lat,Long,Height)
    NAV_SVINFO = 304,               // (ID 0x01 0x30) Info on Channels and the SVs they're tracking
    NAV_GPSTIME = 288,              // (ID 0x01 0x20) GPS Time
    NAV_DGPS = 305,                 // (ID 0x01 0x31) Outputs correction data used for the nav solution
    NAV_DOP = 260,                  // (ID 0x01 0x04) Various Dilution of Precisions
    NAV_UTCTIME = 289,              // (ID 0x01 0x21) UTC Time
    NAV_CLK = 290,                  // (ID 0x01 0x22) Clock information
    AID_REQ = 2816,                 // (ID 0x0B 0x00) Receiver Requests Aiding data if not present at startup
    AID_EPH = 2865,					// (ID 0x0B 0x31) Ephemerides
    AID_ALM = 2864,					// (ID 0x0B 0x30) Almanac
    AID_HUI = 2818,                 // (ID 0x0B 0x02) GPS Health, Ionospheric, UTC
    AID_INI = 2817,                 // (ID 0x0B 0x01) Position, Time, Frequency, Clock Drift
    MON_VER = 2564,                 // (ID 0x0A 0x04) Reciever/Software/ROM Version
    RXM_RAW = 528,                  // (ID 0x02 0x10) Raw DGPS Data
    RXM_SFRB = 529,                 // (ID 0x02 0x11) GPS Subframe Data
    RXM_SVSI = 544,                 // (ID 0x02 0x20) SV Status Info
};

#endif
