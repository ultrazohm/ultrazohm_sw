#include "uz_platform_gpiops.h"
#include "../uz_HAL.h"

// Loosely re-implements selected functions in bsp/psu_cortexa53_0/libsrc/gpiops_v3_10/src/xgpiops.c without side-effect-prone hw initialization/accesses

#if defined (versal) || defined (__microblaze__) || defined (ARMR5) || defined (PSU_PMU)
#error Unsupported platform
#elif defined (__aarch64__) || defined (ARMA53_32)

void uz_platform_gpiops_initxlnxcfg(XGpioPs *InstancePtr, uintptr_t xlnx_baseaddress, uint16_t xlnx_deviceid)
{
	uz_assert_not_NULL(InstancePtr);

	InstancePtr->IsReady = XIL_COMPONENT_IS_READY;
	InstancePtr->GpioConfig.BaseAddr = xlnx_baseaddress;
	InstancePtr->GpioConfig.DeviceId = xlnx_deviceid;
	InstancePtr->Handler = NULL;							// NB: Do *not* extend this layer to use interrupts without registering a stub here...
	InstancePtr->Platform = XPLAT_ZYNQ_ULTRA_MP;

	/*
	 *	Max pins in the ZynqMP GPIO device
	 *	0 - 25,  Bank 0
	 *	26 - 51, Bank 1
	 *	52 - 77, Bank 2
	 *	78 - 109, Bank 3
	 *	110 - 141, Bank 4
	 *	142 - 173, Bank 5
	 */
	InstancePtr->MaxPinNum = (u32)174;
	InstancePtr->MaxBanks = (u8)6;
}

#else
#error Unsupported platform
#endif
