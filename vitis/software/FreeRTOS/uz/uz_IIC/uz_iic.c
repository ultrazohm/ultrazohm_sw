#include "uz_iic.h"

#include "../uz_HAL.h"
#include "xiicps.h"

#define UZ_IIC_MAX_BUSINSTANCES	(1U)

// Bus instances (NOT device instances)
static XIicPs instances[UZ_IIC_MAX_BUSINSTANCES];

/**
 * @brief Initializes an IIC bus
 *
 * @param businst ID of the IIC bus to be initialized.
 * @param xlnx_baseaddress as per Xilinx' xparameters.h
 * @param xlnx_deviceid as per Xilinx' xparameters.h
 * @param xlnx_inputclock_hz as per Xilinx' xparameters.h
 * @param busfreq_khz Desired IIC bus frequency
 * @return none
 */
void uz_iic_initbus(uint8_t businst, uintptr_t xlnx_baseaddress, uint16_t xlnx_deviceid, uint32_t xlnx_inputclock_hz, int busfreq_khz) {
	uz_assert(businst < UZ_IIC_MAX_BUSINSTANCES);
	XIicPs *iicbus_p = &instances[businst];

	int status;
	{
		// Create I²C bus
		XIicPs_Config iic_config;
		iic_config.BaseAddress = xlnx_baseaddress;
		iic_config.DeviceId = xlnx_deviceid;
		iic_config.InputClockHz = xlnx_inputclock_hz;
		status = XIicPs_CfgInitialize(iicbus_p, &iic_config, xlnx_baseaddress);
		uz_assert(XST_SUCCESS == status);
	}

	// Test I²C
	status = XIicPs_SelfTest(iicbus_p);
	uz_assert(XST_SUCCESS == status);

	// Configure I²C
	status = XIicPs_SetSClk(iicbus_p, 1000U*busfreq_khz);
	uz_assert(XST_SUCCESS == status);
	XIicPsSclHold(iicbus_p, 0);
}

/**
 * @brief Initializes an IIC device on a preinitialized IIC bus
 *
 * @param self Ptr to IIC device to be initialized.
 * @param businst ID of underlying and preinitialized IIC bus.
 * @param devaddr IIC address of the device in 7-bit notation.
 * @return none
 */
void uz_iic_initdev(uz_iic *self, uint8_t businst, uint8_t devaddr) {
	uz_assert_not_NULL(self);

	uz_assert(businst < UZ_IIC_MAX_BUSINSTANCES);
	XIicPs *iicbus_p = &instances[businst];
	uz_assert(iicbus_p->IsReady);

	uz_assert(devaddr < 128);
	self->businst = businst;
	self->devaddr = devaddr;
	self->is_ready = true;
}

int uz_iic_write_reg16(struct uz_iic_ *self, uint8_t regaddr, uint16_t data) {
	uint8_t txbuf[3];
	txbuf[0] = regaddr;
	txbuf[1] = data & 0xFF;
	txbuf[2] = (data>>8) & 0xFF;

	return( uz_iic_write_raw(self, txbuf, sizeof(txbuf)/sizeof(txbuf[0])) );
}
int uz_iic_write_raw(struct uz_iic_ *self, uint8_t* data, int32_t cnt) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	XIicPs *iicbus_p = &instances[self->businst];

	while( XIicPs_BusIsBusy(iicbus_p) );

	return( XIicPs_MasterSendPolled(iicbus_p, data, cnt, self->devaddr) );
}

int uz_iic_a8read_data(struct uz_iic_ *self, uint8_t regaddr, uint8_t* data, int32_t cnt) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	XIicPs *iicbus_p = &instances[self->businst];

	while( XIicPs_BusIsBusy(iicbus_p) );

	XIicPs_SetOptions(iicbus_p, XIICPS_REP_START_OPTION);

	int status;
	status = XIicPs_MasterSendPolled(iicbus_p, &regaddr, 1, self->devaddr);

	XIicPs_ClearOptions(iicbus_p, XIICPS_REP_START_OPTION);

	if ( XST_SUCCESS == status )
		status = XIicPs_MasterRecvPolled(iicbus_p, data, cnt, self->devaddr);

	return(status);
}

int uz_iic_a16read_data(struct uz_iic_ *self, uint16_t regaddr, uint8_t* data, int32_t cnt) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	XIicPs *iicbus_p = &instances[self->businst];

	while( XIicPs_BusIsBusy(iicbus_p) );

	XIicPs_SetOptions(iicbus_p, XIICPS_REP_START_OPTION);

	uint8_t txbuf[2];
	txbuf[0] = (regaddr>>8) & 0xFF;
	txbuf[1] = regaddr & 0xFF;

	int status;
	status = XIicPs_MasterSendPolled(iicbus_p, txbuf, sizeof(txbuf)/sizeof(txbuf[0]), self->devaddr);

	XIicPs_ClearOptions(iicbus_p, XIICPS_REP_START_OPTION);

	if ( XST_SUCCESS == status )
		status = XIicPs_MasterRecvPolled(iicbus_p, data, cnt, self->devaddr);

	return(status);
}
