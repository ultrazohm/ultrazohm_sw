#ifndef UZ_PLATFORM_GPIOPS_H
#define UZ_PLATFORM_GPIOPS_H

#include <stdint.h>
#include "xgpiops.h"

#define GPIOPS_DIRECTION_OUT			(1U)
#define GPIOPS_OUTPUTENABLE_DISABLEOP	(0U)
#define GPIOPS_OUTPUTENABLE_ENABLEOP	(1U)

void uz_platform_gpiops_initxlnxcfg(XGpioPs *InstancePtr, uintptr_t xlnx_baseaddress, uint16_t xlnx_deviceid);

#endif
