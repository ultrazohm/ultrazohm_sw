/******************************************************************************
 * uz_logging_path.h
 *
 * ONE switch for the data logging path of both processors. It lives in the
 * shared folder, so the R5 (Baremetal) and the A53 (FreeRTOS) application
 * always agree as long as both are rebuilt and flashed together.
 *
 *   UZ_LOGGING_PATH_JAVASCOPE  JavaScope: R5 JavaScope_update() -> OCM -> A53
 *                              TCP server -> JavaScope GUI
 *   UZ_LOGGING_PATH_XCP        XCP ("Option Z"): XCPlite engine on the R5 ->
 *                              OCM -> A53 UDP gateway -> CANape / xcp_poll.py
 *
 * Change UZ_LOGGING_PATH below, then rebuild and flash BOTH applications.
 * The R5 publishes its setting in the OCM at boot (APU_RPU_shared.h); the A53
 * prints a warning on the serial console if the two builds disagree.
 *
 * The per-application switches are derived from this value:
 *   Baremetal/src/defines.h : XCP_ENGINE_R5_ENABLE
 *   FreeRTOS/defines.h      : LOGGING_PATH_JAVASCOPE, LOGGING_PATH_XCP_R5_GATEWAY
 ******************************************************************************/
#ifndef UZ_LOGGING_PATH_H_
#define UZ_LOGGING_PATH_H_

#define UZ_LOGGING_PATH_JAVASCOPE 1
#define UZ_LOGGING_PATH_XCP       2

/* <<< select the logging path here >>> */
#define UZ_LOGGING_PATH UZ_LOGGING_PATH_XCP

#if (UZ_LOGGING_PATH != UZ_LOGGING_PATH_JAVASCOPE) && (UZ_LOGGING_PATH != UZ_LOGGING_PATH_XCP)
#error "uz_logging_path.h: UZ_LOGGING_PATH must be UZ_LOGGING_PATH_JAVASCOPE or UZ_LOGGING_PATH_XCP"
#endif

#endif /* UZ_LOGGING_PATH_H_ */
