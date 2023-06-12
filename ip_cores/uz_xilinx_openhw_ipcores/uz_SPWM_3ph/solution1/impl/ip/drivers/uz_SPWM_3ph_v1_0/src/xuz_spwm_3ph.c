// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xuz_spwm_3ph.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XUz_spwm_3ph_CfgInitialize(XUz_spwm_3ph *InstancePtr, XUz_spwm_3ph_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XUz_spwm_3ph_Set_u_dc(XUz_spwm_3ph *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_spwm_3ph_WriteReg(InstancePtr->Control_BaseAddress, XUZ_SPWM_3PH_CONTROL_ADDR_U_DC_DATA, Data);
}

u32 XUz_spwm_3ph_Get_u_dc(XUz_spwm_3ph *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_spwm_3ph_ReadReg(InstancePtr->Control_BaseAddress, XUZ_SPWM_3PH_CONTROL_ADDR_U_DC_DATA);
    return Data;
}

