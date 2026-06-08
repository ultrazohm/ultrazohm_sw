#ifndef UZ_CAN_H
#define UZ_CAN_H

#include <stdint.h>
#include <stdbool.h>


/**
 * @brief Object data type definition of the CAN driver
 *
 */
typedef struct uz_can_t uz_can_t;

/**
 * @brief Configuration struct for the CAN driver
 *
 */
struct uz_can_config_t
{
    uint32_t base_address;           /**< Base address of the IP-Core instance to which the driver is coupled */
    uint32_t ip_core_frequency_Hz;   /**< Clock frequency of IP-Core */
    uint32_t can_device_id;
};

typedef struct
{
    uint16_t std_id;
    uint8_t dlc;
    uint8_t data[8];
} uz_can_frame_t;

uz_can_t *uz_can_init(struct uz_can_config_t config);
uint32_t uz_can_is_rx_empty(uz_can_t *self);
uint32_t uz_can_is_tx_done(uz_can_t *self);
uint32_t uz_can_send_frame_blocking(uz_can_t *self, uz_can_frame_t *can_frame_tx_p);
uint32_t uz_can_send_frame_blocking_wrapper(uz_can_t *self, uint16_t std_id, uint8_t dlc, uint8_t *data);
uint32_t uz_can_receive_frame_blocking(uz_can_t *self, uz_can_frame_t *can_frame_rx_p);
void hal_can_debug_print_frame(uz_can_frame_t *can_frame_p);

#endif // UZ_CAN_H
