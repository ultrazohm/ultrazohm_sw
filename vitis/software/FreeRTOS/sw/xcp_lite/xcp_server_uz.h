/******************************************************************************
 * xcp_server_uz.h
 *
 * Public interface for the UltraZohm XCPlite integration layer.
 *
 * Call xcp_server_uz_start() from main.c once the lwIP network is up,
 * under LOGGING_PATH_XCP_LITE.
 *
 * Copyright 2024 Eyke Liegmann -- Apache-2.0
 ******************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* UDP port the XCPlite slave listens on (CANape / xcp_poll.py connect here). */
#define XCP_UDP_PORT 5556u

/*---------------------------------------------------------------------------
 * xcp_server_uz_start
 *
 * Initialises XCPlite, registers the UZ clock callback, creates the Phase 1
 * demo DAQ task and the Phase 3 MEAS event task, then starts the XCPlite
 * Ethernet server (UDP, port 5556).
 *
 * Must be called after the lwIP network interface is up and has an IP.
 * Returns 0 on success, negative on error.
 *--------------------------------------------------------------------------*/
int xcp_server_uz_start(void);

#ifdef __cplusplus
}
#endif
