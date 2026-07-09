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
#define kXcpMaxDTO              kXcpMaxCTO
#define XCP_CAN_ID_TX            (uint16_t) 0x23
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
/* kXcpMaxDTO sets the ODT payload size and thereby the packets-per-sample:
 * at 64, a ~30-signal DAQ list needs 8 ODTs = 8 frames per event; at 220 it
 * fits in 2-3. The transport ceiling is per-FRAME cost (queue ops, ISR
 * staging, batch appends, headers), not per-byte, so bigger DTOs raise the
 * sustainable DAQ rate ~3x (measured: 40 kHz x 8 ODTs sat at 100.003% of
 * the drain rate -> constant 0.003% tail-drop). Upper bound 255 (XcpBasic);
 * 220 keeps the framed message (+4) comfortably inside the u8 chain-length
 * encoding of the OCM exchange. Mirror of this value in OCM_eth_adapter.c
 * (A53) -- keep them identical, rebuild BOTH ELFs. */
#define kXcpMaxCTO              32
#define kXcpMaxDTO              220
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
