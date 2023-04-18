/*
 * Copyright (c) 2022 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Configuration of XCP implementation
 */

#ifndef XCP_CONFIG_H_
#define XCP_CONFIG_H_

#define XCP_HEADER_LEN          4

/*-----------------------------------------------
 * Configuration for CANape
 */
#define XCP_EVENT_FAST          0
#define XCP_EVENT_1MS           1
#define XCP_EVENT_10MS          2
#define XCP_EVENT_100MS         3
#define XCP_EVENT_1S            4

/*-----------------------------------------------
 * Configuration for XCP over CAN
 */
//#define USE_XCP_CAN

#ifdef USE_XCP_CAN
#define kXcpMaxCTO              8
#define kXcpMaxDTO              8
#define XCP_CAN_ID_TX			(uint16_t) 0x23
/*
 * No filter implemented.
 * In this setup XCP master from CANape is the only other participant on the
 * CAN bus. So filtering incoming CAN messages is not necessary.
 */
//#define XCP_CAN_ID_RX           (uint16_t) 0x24
#endif

/*-----------------------------------------------
 * Configuration for XCP over Ethernet
 */
#define USE_XCP_ETH

#ifdef USE_XCP_ETH
#define kXcpMaxCTO              100
#define kXcpMaxDTO              100
#define XCP_ETH_PORT            (uint16_t) 12340
#endif

/*-----------------------------------------------
 * XCP driver configuration
 */
#define XCP_ENABLE_UNALIGNED_MEM_ACCESS

/*-----------------------------------------------
 * Plausability check
 */
#if (defined(USE_XCP_ETH) && defined(USE_XCP_CAN))
#error "Define either ETH or CAN for XCP"
#endif

#endif /* XCP_CONFIG_H_ */
