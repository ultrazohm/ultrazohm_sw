#ifndef _XCP_R5_H_
#define _XCP_R5_H_

#include <stdint.h>

//--------------------------------------------------------------------
// Configuration
// -------------------------------------------------------------------
#define SECTION_XCP_TS      __attribute__ ((section (".section_xcp_timestamp")))
#define SECTION_XCP_MEAS    __attribute__ ((section (".section_xcp_meas")))

//--------------------------------------------------------------------
// Types
// -------------------------------------------------------------------

//--------------------------------------------------------------------
// Global Variables
// -------------------------------------------------------------------

//--------------------------------------------------------------------
// Global functions
// -------------------------------------------------------------------
void xcp_R5_cache_flush_stimulate(void);
void xcp_R5_cache_flush_measure(void);
void xcp_R5_set_timestamp(void);

#endif /* _XCP_R5_H_ */
