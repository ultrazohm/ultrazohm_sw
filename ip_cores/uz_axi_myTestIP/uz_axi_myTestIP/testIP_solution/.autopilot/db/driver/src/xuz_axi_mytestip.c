// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xuz_axi_mytestip.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XUz_axi_mytestip_CfgInitialize(XUz_axi_mytestip *InstancePtr, XUz_axi_mytestip_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XUz_axi_mytestip_Set_a(XUz_axi_mytestip *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_axi_mytestip_WriteReg(InstancePtr->Control_BaseAddress, XUZ_AXI_MYTESTIP_CONTROL_ADDR_A_DATA, Data);
}

u32 XUz_axi_mytestip_Get_a(XUz_axi_mytestip *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_axi_mytestip_ReadReg(InstancePtr->Control_BaseAddress, XUZ_AXI_MYTESTIP_CONTROL_ADDR_A_DATA);
    return Data;
}

void XUz_axi_mytestip_Set_b(XUz_axi_mytestip *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_axi_mytestip_WriteReg(InstancePtr->Control_BaseAddress, XUZ_AXI_MYTESTIP_CONTROL_ADDR_B_DATA, Data);
}

u32 XUz_axi_mytestip_Get_b(XUz_axi_mytestip *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_axi_mytestip_ReadReg(InstancePtr->Control_BaseAddress, XUZ_AXI_MYTESTIP_CONTROL_ADDR_B_DATA);
    return Data;
}

u32 XUz_axi_mytestip_Get_result(XUz_axi_mytestip *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_axi_mytestip_ReadReg(InstancePtr->Control_BaseAddress, XUZ_AXI_MYTESTIP_CONTROL_ADDR_RESULT_DATA);
    return Data;
}

u32 XUz_axi_mytestip_Get_result_vld(XUz_axi_mytestip *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_axi_mytestip_ReadReg(InstancePtr->Control_BaseAddress, XUZ_AXI_MYTESTIP_CONTROL_ADDR_RESULT_CTRL);
    return Data & 0x1;
}

