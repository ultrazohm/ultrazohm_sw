// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xuz_nn_acc.h"

extern XUz_nn_acc_Config XUz_nn_acc_ConfigTable[];

XUz_nn_acc_Config *XUz_nn_acc_LookupConfig(u16 DeviceId) {
	XUz_nn_acc_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XUZ_NN_ACC_NUM_INSTANCES; Index++) {
		if (XUz_nn_acc_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XUz_nn_acc_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XUz_nn_acc_Initialize(XUz_nn_acc *InstancePtr, u16 DeviceId) {
	XUz_nn_acc_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XUz_nn_acc_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XUz_nn_acc_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

