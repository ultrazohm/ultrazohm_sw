/*****************************************************************************
| Project Name:   XCP on CAN demo for Infineon Tricore TC17x7
|    File Name:
|
|  Description:   XCP Configuration
|
|-----------------------------------------------------------------------------
|               D E M O
|-----------------------------------------------------------------------------
|
|       Please note, that the demo and example programs
|       only show special aspects of the software.
|       With regard to the fact that these programs are meant
|       for demonstration purposes only,
|       Vector Informatik's liability shall be expressly excluded in cases
|       of ordinary negligence, to the extent admissible by law or statute.
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2010 by Vector Informatik GmbH.           All rights reserved.
|
|       This software is copyright protected and
|       proporietary to Vector Informatik GmbH.
|       Vector Informatik GmbH grants to you only
|       those rights as set out in the license conditions.
|       All other rights remain with Vector Informatik GmbH.
|
|       Diese Software ist urheberrechtlich geschuetzt.
|       Vector Informatik GmbH raeumt Ihnen an dieser Software nur
|       die in den Lizenzbedingungen ausdruecklich genannten Rechte ein.
|       Alle anderen Rechte verbleiben bei Vector Informatik GmbH.
|
|-----------------------------------------------------------------------------
|***************************************************************************/

#ifndef  __XCP_CFG_H__

#include <stdint.h>
#include "xcpBasic.h"
#include "../xcp_config.h"

/*----------------------------------------------------------------------------*/
/* Project specific includes */
extern void XcpHandler( void );


/*----------------------------------------------------------------------------*/
/* Test */

/* Use XCP_PRINT to generate diagnostic messages */
//#define XCP_ENABLE_TESTMODE
#ifdef XCP_ENABLE_TESTMODE
  #define ApplXcpPrint XcpPrintf
  #define XCP_ASSERT(x) if (!(x)) XcpPrintf("Assertion failed in line %u",__LINE__);
#else
  #define XCP_ASSERT(x)
#endif


/*----------------------------------------------------------------------------*/
/* Data types */

  /* 8-Bit qualifier */
typedef uint8_t  	vuint8;
typedef int8_t		vsint8;

/* 16-Bit qualifier */
typedef uint16_t	vuint16;
typedef int16_t		vsint16;

/* 32-Bit qualifier */
typedef uint32_t	vuint32;
typedef int32_t		vsint32;


/*----------------------------------------------------------------------------*/

/* XCP slave device identification (optional) */
//#define kXcpStationIdLength 7       /* Slave device identification length */
#define kXcpStationIdString "UZ--XCP"

#if defined ( kXcpStationIdLength )
  extern vuint8 kXcpStationId[];
#endif


/*----------------------------------------------------------------------------*/
/* XCP protocol parameters */

/* Copy routine */
#define xcpMemCpy memcpy

/* Byte order */
#define C_CPUTYPE_LITTLEENDIAN /* Intel */

#define XCP_DISABLE_PARAMETER_CHECK

/* Enable COMM_MODE_INFO */
#define XCP_ENABLE_COMM_MODE_INFO

/* Enable GET_SEED and UNLOCK */
//#define XCP_ENABLE_SEED_KEY

/* Enable xcpUserService() to handle user defined commands */
//#define XCP_ENABLE_USER_COMMAND

/* Enable transmission of event messages */
#define XCP_ENABLE_SEND_EVENT

/* Enable xcpPrintf() and xcpPutChar() via SERV_TEXT events */
#if defined(XCP_CC_AUTOSAR) || defined(XCP_CC_TC_OVRAM)
  #include <stdio.h>
  #include <stdarg.h>
  #define XCP_ENABLE_SERV_TEXT
  #define XCP_ENABLE_SERV_TEXT_PUTCHAR
  #define XCP_ENABLE_SERV_TEXT_PRINT
  #define XCP_ENABLE_SERV_TEXT_PRINTF
#endif

#define XCP_DISABLE_SERV_TEXT
#define XCP_DISABLE_SERV_TEXT_PUTCHAR
#define XCP_DISABLE_SERV_TEXT_PRINT


/* Disable FLASH programming */
/* Implement the flash programming feature in the ECU */
/* Not available in xcpBasic ! */
#define XCP_DISABLE_PROGRAM

/* Activate the flash programming kernel download support */
#define XCP_ENABLE_BOOTLOADER_DOWNLOAD


/*----------------------------------------------------------------------------*/
/* Additional user call backs */

#if defined(XCP_CC_AUTOSAR) || defined(XCP_CC_TC_OVRAM)
  #define ApplXcpInit ApplXcpInit
  extern void ApplXcpInit( void );
#endif



/*----------------------------------------------------------------------------*/
/* XCP Calibration Parameters */

#define XCP_ENABLE_CALIBRATION
#define XCP_DISABLE_CALIBRATION_PAGE

#define XCP_ENABLE_SHORT_DOWNLOAD
#define XCP_ENABLE_SHORT_UPLOAD

/* Enable block transfer */
#define XCP_ENABLE_BLOCK_UPLOAD
#define XCP_ENABLE_BLOCK_DOWNLOAD

/* Enable memory checksum */
/* The checksum will be calculated in XcpBackground() */
/* This may be implementation specific */
//#define XCP_ENABLE_CHECKSUM
#define kXcpChecksumMethod XCP_CHECKSUM_TYPE_ADD14

/* Enable Calibration Page switching and dynamic calibration overlay RAM allocation */
#if defined(XCP_CC_AUTOSAR) || defined(XCP_CC_TC_OVRAM)
  #define XCP_ENABLE_CALIBRATION_MEM_ACCESS_BY_APPL
  #define XCP_ENABLE_CALIBRATION_PAGE
  #define XCP_ENABLE_PAGE_COPY
#endif
#define XCP_DISABLE_SEGMENT_INFO
#define XCP_DISABLE_PAGE_INFO
#define XCP_DISABLE_PAGE_FREEZE


/*----------------------------------------------------------------------------*/
/* XCP Data Stimulation Parameters */

/* Synchronous Data Stimulation (STIM) */
//#define XCP_ENABLE_STIM
//#define XCP_DISABLE_STIM
//#define kXcpStimOdtCount 16


/*----------------------------------------------------------------------------*/
/* XCP Data Acquisition Parameters */

/* Enable data acquisition */
#define XCP_ENABLE_DAQ
//#define XCP_ENABLE_DAQ_HDR_ODT_DAQ
#define XCP_DISABLE_DAQ_HDR_ODT_DAQ

#define XCP_ENABLE_DAQ_PRESCALER
#define XCP_ENABLE_DAQ_OVERRUN_INDICATION
//#define XCP_ENABLE_DAQ_RESUME
#define XCP_ENABLE_DAQ_PROCESSOR_INFO
#define XCP_ENABLE_DAQ_RESOLUTION_INFO

#define XCP_ENABLE_WRITE_DAQ_MULTIPLE

/* Memory space reserved for DAQ */
/* This memory is also shared with the VX, so the size was set to fullfill VX max requirement */
#define kXcpDaqMemSize (1024*2)
#define XCP_ENABLE_SEND_QUEUE
#define XCP_DISABLE_SEND_BUFFER

/* DAQ Timestamp */
#define XCP_ENABLE_DAQ_TIMESTAMP
#ifdef XCP_ENABLE_DAQ_TIMESTAMP
  /*
   * Example:
   * Timestamp is TTC10
   * One tick of timestamp counter is = (1 / (100 MHz / (2 ^ 12))) s = 40.96 us
   * TicksPerUnit == "how many (ticks * unit) is one timer tick:
   *  => 40.96 us = (4096 * 10 ns)
   * Results in code:
   *   #define kXcpDaqTimestampUnit DAQ_TIMESTAMP_UNIT_10NS
   *   #define kXcpDaqTimestampTicksPerUnit 4096
   */
#define kXcpDaqTimestampSize DAQ_TIMESTAMP_DWORD	//WORD == uint16, DWORD == uint32
#define kXcpDaqTimestampUnit DAQ_TIMESTAMP_UNIT_10NS
#define kXcpDaqTimestampTicksPerUnit 1

//  #define ApplXcpGetTimestamp()     xcp_interface_getTimestamp()
//  #define ApplXcpDaqGetTimestamp()  xcp_interface_daqGetTimestamp()
#endif

/* Enable Plug&Play for the event definitions */
//#define XCP_ENABLE_DAQ_EVENT_INFO

#endif
