// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xuz_pi_controller_sample.h"

extern XUz_pi_controller_sample_Config XUz_pi_controller_sample_ConfigTable[];

XUz_pi_controller_sample_Config *XUz_pi_controller_sample_LookupConfig(u16 DeviceId) {
	XUz_pi_controller_sample_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XUZ_PI_CONTROLLER_SAMPLE_NUM_INSTANCES; Index++) {
		if (XUz_pi_controller_sample_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XUz_pi_controller_sample_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XUz_pi_controller_sample_Initialize(XUz_pi_controller_sample *InstancePtr, u16 DeviceId) {
	XUz_pi_controller_sample_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XUz_pi_controller_sample_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XUz_pi_controller_sample_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

