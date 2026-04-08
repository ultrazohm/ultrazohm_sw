// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xuz_axi_mytestip.h"

extern XUz_axi_mytestip_Config XUz_axi_mytestip_ConfigTable[];

XUz_axi_mytestip_Config *XUz_axi_mytestip_LookupConfig(u16 DeviceId) {
	XUz_axi_mytestip_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XUZ_AXI_MYTESTIP_NUM_INSTANCES; Index++) {
		if (XUz_axi_mytestip_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XUz_axi_mytestip_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XUz_axi_mytestip_Initialize(XUz_axi_mytestip *InstancePtr, u16 DeviceId) {
	XUz_axi_mytestip_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XUz_axi_mytestip_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XUz_axi_mytestip_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

