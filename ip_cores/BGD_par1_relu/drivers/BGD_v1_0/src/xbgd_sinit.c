// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xbgd.h"

extern XBgd_Config XBgd_ConfigTable[];

XBgd_Config *XBgd_LookupConfig(u16 DeviceId) {
	XBgd_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XBGD_NUM_INSTANCES; Index++) {
		if (XBgd_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XBgd_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XBgd_Initialize(XBgd *InstancePtr, u16 DeviceId) {
	XBgd_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XBgd_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XBgd_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

