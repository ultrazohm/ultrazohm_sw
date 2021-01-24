#ifndef CAN_H
#define CAN_H

#include "inttypes.h"
typedef struct
{
	uint16_t std_id;
	uint8_t dlc;
	uint8_t data[8];
} can_frame_t;

int hal_can_init(uint32_t can_base_address, uint32_t can_device_id);
int hal_can_send_frame_blocking(can_frame_t* can_frame_tx_p);
int hal_can_send_frame_blocking_wrapper(uint16_t std_id, uint8_t dlc, uint8_t* data);
int hal_can_receive_frame_blocking(can_frame_t *data);
int hal_can_is_tx_done(void);
int hal_can_is_rx_empty(void);

#endif