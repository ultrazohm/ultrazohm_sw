// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xmatrixmultiplication.h"

extern XMatrixmultiplication_Config XMatrixmultiplication_ConfigTable[];

XMatrixmultiplication_Config *XMatrixmultiplication_LookupConfig(u16 DeviceId) {
	XMatrixmultiplication_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XMATRIXMULTIPLICATION_NUM_INSTANCES; Index++) {
		if (XMatrixmultiplication_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XMatrixmultiplication_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XMatrixmultiplication_Initialize(XMatrixmultiplication *InstancePtr, u16 DeviceId) {
	XMatrixmultiplication_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XMatrixmultiplication_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XMatrixmultiplication_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

