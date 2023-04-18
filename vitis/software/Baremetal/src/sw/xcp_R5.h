#ifndef _XCP_R5_H_
#define _XCP_R5_H_

#include <stdint.h>

//--------------------------------------------------------------------
// Configuration
// -------------------------------------------------------------------
#define DUMMY_LEN			80

//--------------------------------------------------------------------
// Types
// -------------------------------------------------------------------
typedef struct {
	bool button_enable_system;
	bool button_enable_control;
	bool disable_calculation;
} xcp_stim_t;

typedef struct {
	int8_t sin_u8;
	int8_t cos_u8;
	int8_t saw_u8;
	float sin_f;
	float cos_f;
	float saw_f;
} xcp_meas_t;

//--------------------------------------------------------------------
// Variables
// -------------------------------------------------------------------
xcp_stim_t xcp_stim;
xcp_meas_t xcp_meas;

extern uint8_t xcp_80Byte_u8[DUMMY_LEN];
extern uint32_t xcp_80Byte_u32[DUMMY_LEN/4];

//--------------------------------------------------------------------
// Global functions
// -------------------------------------------------------------------
void xcp_R5_cache_flush_stimulate(void);
void xcp_R5_cache_flush_measure(void);
void xcp_R5_set_timestamp(void);

#endif /* _XCP_R5_H_ */
