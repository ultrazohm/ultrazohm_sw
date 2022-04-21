// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xmlp.h"

extern XMlp_Config XMlp_ConfigTable[];

XMlp_Config *XMlp_LookupConfig(u16 DeviceId) {
	XMlp_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XMLP_NUM_INSTANCES; Index++) {
		if (XMlp_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XMlp_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XMlp_Initialize(XMlp *InstancePtr, u16 DeviceId) {
	XMlp_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XMlp_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XMlp_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

