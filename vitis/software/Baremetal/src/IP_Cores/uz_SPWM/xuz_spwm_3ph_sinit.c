// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xuz_spwm_3ph.h"

extern XUz_spwm_3ph_Config XUz_spwm_3ph_ConfigTable[];

XUz_spwm_3ph_Config *XUz_spwm_3ph_LookupConfig(u16 DeviceId) {
	XUz_spwm_3ph_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XUZ_SPWM_3PH_NUM_INSTANCES; Index++) {
		if (XUz_spwm_3ph_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XUz_spwm_3ph_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XUz_spwm_3ph_Initialize(XUz_spwm_3ph *InstancePtr, u16 DeviceId) {
	XUz_spwm_3ph_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XUz_spwm_3ph_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XUz_spwm_3ph_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

