// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xuz_pi_controller.h"

extern XUz_pi_controller_Config XUz_pi_controller_ConfigTable[];

XUz_pi_controller_Config *XUz_pi_controller_LookupConfig(u16 DeviceId) {
	XUz_pi_controller_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XUZ_PI_CONTROLLER_NUM_INSTANCES; Index++) {
		if (XUz_pi_controller_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XUz_pi_controller_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XUz_pi_controller_Initialize(XUz_pi_controller *InstancePtr, u16 DeviceId) {
	XUz_pi_controller_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XUz_pi_controller_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XUz_pi_controller_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

