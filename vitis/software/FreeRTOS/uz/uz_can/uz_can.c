/******************************************************************************
 * Copyright Contributors to the UltraZohm project.
 * Copyright 2026 Tobias Schindler
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 ******************************************************************************/

#include "uz_can.h"
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "xcanps.h"

#define UZ_CAN_MAX_INSTANCES 2U

#define CAN_BAUD_RATE_PRESCALER 25

#define CAN_SYNCJUMPWIDTH 1
#define CAN_SECOND_TIMESEGMENT 2
#define CAN_FIRST_TIMESEGMENT 5

struct uz_can_t
{
    bool is_ready;
    struct uz_can_config_t config;
    XCanPs can_inst;
    XCanPs_Config can_config;
};

static uint32_t instance_counter = 0U;
static uz_can_t instances[UZ_CAN_MAX_INSTANCES] = {0};

static uz_can_t *uz_can_allocation(void);

static uz_can_t *uz_can_allocation(void)
{
    uz_assert(instance_counter < UZ_CAN_MAX_INSTANCES);
    uz_can_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

// private function declarations
static void write_config_to_pl(uz_can_t *self);

uz_can_t *uz_can_init(struct uz_can_config_t config)
{
    uz_assert(0U != config.base_address);
    uz_assert(0U != config.ip_core_frequency_Hz);
    uz_can_t *self = uz_can_allocation();
    self->config = config;

    self->can_config.BaseAddr = self->config.base_address; // e.g.: XPAR_PS7_CAN_0_BASEADDR;
    self->can_config.DeviceId = self->config.can_device_id;    // e.g.: XPAR_PS7_CAN_0_DEVICE_ID;

    uint32_t status = XCanPs_CfgInitialize(&self->can_inst, &self->can_config, self->can_config.BaseAddr);
    uz_assert(status==UZ_SUCCESS);

    status = XCanPs_SelfTest(&self->can_inst);
    uz_assert(status == UZ_SUCCESS);

    XCanPs_EnterMode(&self->can_inst, XCANPS_MODE_CONFIG);
    while (XCanPs_GetMode(&self->can_inst) != XCANPS_MODE_CONFIG) {
        // do nothing, just wait until the mode is entered
    }

    XCanPs_SetBaudRatePrescaler(&self->can_inst, CAN_BAUD_RATE_PRESCALER - 1); // register value of prescaler is (prescaler - 1) !!

    XCanPs_SetBitTiming(&self->can_inst,
                        CAN_SYNCJUMPWIDTH - 1,
                        CAN_SECOND_TIMESEGMENT - 1,
                        CAN_FIRST_TIMESEGMENT - 1);

    XCanPs_EnterMode(&self->can_inst, XCANPS_MODE_NORMAL); // go into final mode
    while (XCanPs_GetMode(&self->can_inst) != XCANPS_MODE_NORMAL) {
        // do nothing, just wait until the mode is entered
    }

    return (self);
}

uint32_t uz_can_is_rx_empty(uz_can_t* self)
{
    return XCanPs_IsRxEmpty(&self->can_inst);
}

uint32_t uz_can_is_tx_done(uz_can_t* self)
{
    return XCanPs_IsTxDone(&self->can_inst);
}

uint32_t uz_can_send_frame_blocking(uz_can_t *self, uz_can_frame_t *can_frame_tx_p)
{
    uint32_t tx_frame[4]= {0};

    // set identifier
    tx_frame[0] = XCanPs_CreateIdValue(can_frame_tx_p->std_id, 0, 0, 0, 0);

    // set data length
    tx_frame[1] = XCanPs_CreateDlcValue(can_frame_tx_p->dlc);

    // copy data
    uint8_t *data_frame_copy_pointer = (uint8_t *)(&tx_frame[2]);
    for (uint32_t lc = 0; lc < can_frame_tx_p->dlc; lc++)
    {
        *(data_frame_copy_pointer++) = (uint8_t)can_frame_tx_p->data[lc];
    }

    // Wait until TX FIFO has room
    while (XCanPs_IsTxFifoFull(&self->can_inst) == TRUE){
        // do nothing, just wait until there is room in the TX FIFO
    }

    /*
     * Now send the frame.
     *
     * Another way to send a frame is keep calling XCan_Send() until it
     * returns XST_SUCCESS. No check on if TX FIFO is full is needed anymore
     * in that case.
     */
    uint32_t status = XCanPs_Send(&self->can_inst, tx_frame);

    return status;
}

uint32_t uz_can_send_frame_blocking_wrapper(uz_can_t *self,uint16_t std_id, uint8_t dlc, uint8_t *data)
{
    uz_can_frame_t can_frame_tx = {0};

    can_frame_tx.std_id = std_id;
    can_frame_tx.dlc = dlc;

    for (uint32_t lc = 0; lc < dlc; lc++)
    {
        can_frame_tx.data[lc] = data[lc];
    }

    uint32_t status = uz_can_send_frame_blocking(self, &can_frame_tx);

    return status;
}

uint32_t uz_can_receive_frame_blocking(uz_can_t *self, uz_can_frame_t *can_frame_rx_p)
{
    while (XCanPs_IsRxEmpty(&self->can_inst) == TRUE){
    }

    uint32_t rx_data_block[4]= {0};
    uint32_t status = XCanPs_Recv(&self->can_inst, rx_data_block);

    can_frame_rx_p->std_id = (rx_data_block[0] & XCANPS_IDR_ID1_MASK) >> XCANPS_IDR_ID1_SHIFT;
    can_frame_rx_p->dlc = (rx_data_block[1] & XCANPS_DLCR_DLC_MASK) >> XCANPS_DLCR_DLC_SHIFT;
    *((uint32_t *)&can_frame_rx_p->data[0]) = rx_data_block[2];
    *((uint32_t *)&can_frame_rx_p->data[4]) = rx_data_block[3];

    return status;
}
