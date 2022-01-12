// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xmultilayerperceptrondecoupled.h"

extern XMultilayerperceptrondecoupled_Config XMultilayerperceptrondecoupled_ConfigTable[];

XMultilayerperceptrondecoupled_Config *XMultilayerperceptrondecoupled_LookupConfig(u16 DeviceId) {
	XMultilayerperceptrondecoupled_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XMULTILAYERPERCEPTRONDECOUPLED_NUM_INSTANCES; Index++) {
		if (XMultilayerperceptrondecoupled_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XMultilayerperceptrondecoupled_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XMultilayerperceptrondecoupled_Initialize(XMultilayerperceptrondecoupled *InstancePtr, u16 DeviceId) {
	XMultilayerperceptrondecoupled_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XMultilayerperceptrondecoupled_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XMultilayerperceptrondecoupled_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

