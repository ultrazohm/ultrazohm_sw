// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xuz_pi_controller_sample.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XUz_pi_controller_sample_CfgInitialize(XUz_pi_controller_sample *InstancePtr, XUz_pi_controller_sample_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Din_BaseAddress = ConfigPtr->Din_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XUz_pi_controller_sample_Start(XUz_pi_controller_sample *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_AP_CTRL) & 0x80;
    XUz_pi_controller_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_AP_CTRL, Data | 0x01);
}

u32 XUz_pi_controller_sample_IsDone(XUz_pi_controller_sample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XUz_pi_controller_sample_IsIdle(XUz_pi_controller_sample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XUz_pi_controller_sample_IsReady(XUz_pi_controller_sample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XUz_pi_controller_sample_EnableAutoRestart(XUz_pi_controller_sample *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_AP_CTRL, 0x80);
}

void XUz_pi_controller_sample_DisableAutoRestart(XUz_pi_controller_sample *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_AP_CTRL, 0);
}

void XUz_pi_controller_sample_Set_self(XUz_pi_controller_sample *InstancePtr, XUz_pi_controller_sample_Self Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_SELF_DATA + 0, Data.word_0);
    XUz_pi_controller_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_SELF_DATA + 4, Data.word_1);
    XUz_pi_controller_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_SELF_DATA + 8, Data.word_2);
    XUz_pi_controller_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_SELF_DATA + 12, Data.word_3);
    XUz_pi_controller_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_SELF_DATA + 16, Data.word_4);
}

XUz_pi_controller_sample_Self XUz_pi_controller_sample_Get_self(XUz_pi_controller_sample *InstancePtr) {
    XUz_pi_controller_sample_Self Data;

    Data.word_0 = XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_SELF_DATA + 0);
    Data.word_1 = XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_SELF_DATA + 4);
    Data.word_2 = XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_SELF_DATA + 8);
    Data.word_3 = XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_SELF_DATA + 12);
    Data.word_4 = XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_SELF_DATA + 16);
    return Data;
}

void XUz_pi_controller_sample_Set_I_rst(XUz_pi_controller_sample *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_I_RST_DATA, Data);
}

u32 XUz_pi_controller_sample_Get_I_rst(XUz_pi_controller_sample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_I_RST_DATA);
    return Data;
}

void XUz_pi_controller_sample_Set_referenceValue(XUz_pi_controller_sample *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_REFERENCEVALUE_DATA, Data);
}

u32 XUz_pi_controller_sample_Get_referenceValue(XUz_pi_controller_sample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_REFERENCEVALUE_DATA);
    return Data;
}

void XUz_pi_controller_sample_Set_actualValue(XUz_pi_controller_sample *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_ACTUALVALUE_DATA, Data);
}

u32 XUz_pi_controller_sample_Get_actualValue(XUz_pi_controller_sample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_ACTUALVALUE_DATA);
    return Data;
}

void XUz_pi_controller_sample_Set_ext_clamping(XUz_pi_controller_sample *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_EXT_CLAMPING_DATA, Data);
}

u32 XUz_pi_controller_sample_Get_ext_clamping(XUz_pi_controller_sample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_EXT_CLAMPING_DATA);
    return Data;
}

u32 XUz_pi_controller_sample_Get_output_r(XUz_pi_controller_sample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_OUTPUT_R_DATA);
    return Data;
}

u32 XUz_pi_controller_sample_Get_output_r_vld(XUz_pi_controller_sample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_OUTPUT_R_CTRL);
    return Data & 0x1;
}

void XUz_pi_controller_sample_InterruptGlobalEnable(XUz_pi_controller_sample *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_GIE, 1);
}

void XUz_pi_controller_sample_InterruptGlobalDisable(XUz_pi_controller_sample *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_GIE, 0);
}

void XUz_pi_controller_sample_InterruptEnable(XUz_pi_controller_sample *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_IER);
    XUz_pi_controller_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_IER, Register | Mask);
}

void XUz_pi_controller_sample_InterruptDisable(XUz_pi_controller_sample *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_IER);
    XUz_pi_controller_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_IER, Register & (~Mask));
}

void XUz_pi_controller_sample_InterruptClear(XUz_pi_controller_sample *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_pi_controller_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_ISR, Mask);
}

u32 XUz_pi_controller_sample_InterruptGetEnabled(XUz_pi_controller_sample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_IER);
}

u32 XUz_pi_controller_sample_InterruptGetStatus(XUz_pi_controller_sample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XUz_pi_controller_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_ISR);
}

