/*----------------------------------------------------------------------------
| ocm_xcp_fifo.h
|   Option Z — OCM FIFO between the R5 (XCPlite engine) and the A53 (Ethernet
|   gateway). One shared implementation for both cores; the side is selected by
|   the ARMR5 compiler define (R5) vs. its absence (A53).
|
|   Sweep model (per exchange cycle, coordinated by the existing IPI):
|     writer:  prepare_write() -> writeOCM()* -> cache_flush_after_write()
|     reader:  cache_invalidate_before_read() -> prepare_read() -> readOCM()*
|
|   Adapted from uz_sw_xcp_hedrive_andi RPU_APU_exchange (Jens Wenzl, 2023),
|   which is hardware-proven (see its XCP_BOTTLENECK_ANALYSIS.md). UltraZohm.
 ----------------------------------------------------------------------------*/
#ifndef OCM_XCP_FIFO_H_
#define OCM_XCP_FIFO_H_

#include <stdint.h>

void ocm_xcp_fifo_init(void);
void ocm_xcp_fifo_prepare_read(void);
void ocm_xcp_fifo_prepare_write(void);
void ocm_xcp_fifo_cache_invalidate_before_read(void);
void ocm_xcp_fifo_cache_flush_after_write(void);

/* Append one framed message to the write region.
 * Returns 1 if written, 0 if the region is full (caller drops/retries). */
int ocm_xcp_fifo_write(uint8_t len, const uint8_t *data);

/* Return 1 and point *data_p at the next message (length in *len), or 0 at the
 * end of the chain / on a corrupt length / at the region end. */
int ocm_xcp_fifo_read(uint8_t *len, uint8_t **data_p);

#endif /* OCM_XCP_FIFO_H_ */
