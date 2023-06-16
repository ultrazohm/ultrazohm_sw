// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xuz_foc.h"

extern XUz_foc_Config XUz_foc_ConfigTable[];

XUz_foc_Config *XUz_foc_LookupConfig(u16 DeviceId) {
	XUz_foc_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XUZ_FOC_NUM_INSTANCES; Index++) {
		if (XUz_foc_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XUz_foc_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XUz_foc_Initialize(XUz_foc *InstancePtr, u16 DeviceId) {
	XUz_foc_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XUz_foc_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XUz_foc_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

