// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xuz_foc_sample.h"

extern XUz_foc_sample_Config XUz_foc_sample_ConfigTable[];

XUz_foc_sample_Config *XUz_foc_sample_LookupConfig(u16 DeviceId) {
	XUz_foc_sample_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XUZ_FOC_SAMPLE_NUM_INSTANCES; Index++) {
		if (XUz_foc_sample_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XUz_foc_sample_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XUz_foc_sample_Initialize(XUz_foc_sample *InstancePtr, u16 DeviceId) {
	XUz_foc_sample_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XUz_foc_sample_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XUz_foc_sample_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

