// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xuz_hls_testip.h"

extern XUz_hls_testip_Config XUz_hls_testip_ConfigTable[];

XUz_hls_testip_Config *XUz_hls_testip_LookupConfig(u16 DeviceId) {
	XUz_hls_testip_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XUZ_HLS_TESTIP_NUM_INSTANCES; Index++) {
		if (XUz_hls_testip_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XUz_hls_testip_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XUz_hls_testip_Initialize(XUz_hls_testip *InstancePtr, u16 DeviceId) {
	XUz_hls_testip_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XUz_hls_testip_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XUz_hls_testip_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

