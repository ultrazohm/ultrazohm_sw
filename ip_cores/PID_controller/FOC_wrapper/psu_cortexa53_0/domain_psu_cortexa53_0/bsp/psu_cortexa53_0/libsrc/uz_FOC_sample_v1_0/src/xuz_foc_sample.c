// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xuz_foc_sample.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XUz_foc_sample_CfgInitialize(XUz_foc_sample *InstancePtr, XUz_foc_sample_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->Din_BaseAddress = ConfigPtr->Din_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XUz_foc_sample_Start(XUz_foc_sample *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_AP_CTRL) & 0x80;
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_AP_CTRL, Data | 0x01);
}

u32 XUz_foc_sample_IsDone(XUz_foc_sample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XUz_foc_sample_IsIdle(XUz_foc_sample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XUz_foc_sample_IsReady(XUz_foc_sample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XUz_foc_sample_EnableAutoRestart(XUz_foc_sample *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_AP_CTRL, 0x80);
}

void XUz_foc_sample_DisableAutoRestart(XUz_foc_sample *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_AP_CTRL, 0);
}

void XUz_foc_sample_Set_output_volts_d(XUz_foc_sample *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_sample_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_SAMPLE_CONTROL_ADDR_OUTPUT_VOLTS_D_DATA, (u32)(Data));
    XUz_foc_sample_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_SAMPLE_CONTROL_ADDR_OUTPUT_VOLTS_D_DATA + 4, (u32)(Data >> 32));
}

u64 XUz_foc_sample_Get_output_volts_d(XUz_foc_sample *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_sample_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_SAMPLE_CONTROL_ADDR_OUTPUT_VOLTS_D_DATA);
    Data += (u64)XUz_foc_sample_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_SAMPLE_CONTROL_ADDR_OUTPUT_VOLTS_D_DATA + 4) << 32;
    return Data;
}

void XUz_foc_sample_Set_output_volts_q(XUz_foc_sample *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_sample_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_SAMPLE_CONTROL_ADDR_OUTPUT_VOLTS_Q_DATA, (u32)(Data));
    XUz_foc_sample_WriteReg(InstancePtr->Control_BaseAddress, XUZ_FOC_SAMPLE_CONTROL_ADDR_OUTPUT_VOLTS_Q_DATA + 4, (u32)(Data >> 32));
}

u64 XUz_foc_sample_Get_output_volts_q(XUz_foc_sample *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_sample_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_SAMPLE_CONTROL_ADDR_OUTPUT_VOLTS_Q_DATA);
    Data += (u64)XUz_foc_sample_ReadReg(InstancePtr->Control_BaseAddress, XUZ_FOC_SAMPLE_CONTROL_ADDR_OUTPUT_VOLTS_Q_DATA + 4) << 32;
    return Data;
}

void XUz_foc_sample_Set_i_reference_Ampere(XUz_foc_sample *InstancePtr, XUz_foc_sample_I_reference_ampere Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_I_REFERENCE_AMPERE_DATA + 0, Data.word_0);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_I_REFERENCE_AMPERE_DATA + 4, Data.word_1);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_I_REFERENCE_AMPERE_DATA + 8, Data.word_2);
}

XUz_foc_sample_I_reference_ampere XUz_foc_sample_Get_i_reference_Ampere(XUz_foc_sample *InstancePtr) {
    XUz_foc_sample_I_reference_ampere Data;

    Data.word_0 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_I_REFERENCE_AMPERE_DATA + 0);
    Data.word_1 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_I_REFERENCE_AMPERE_DATA + 4);
    Data.word_2 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_I_REFERENCE_AMPERE_DATA + 8);
    return Data;
}

void XUz_foc_sample_Set_self_i(XUz_foc_sample *InstancePtr, XUz_foc_sample_Self_i Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_I_DATA + 0, Data.word_0);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_I_DATA + 4, Data.word_1);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_I_DATA + 8, Data.word_2);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_I_DATA + 12, Data.word_3);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_I_DATA + 16, Data.word_4);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_I_DATA + 20, Data.word_5);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_I_DATA + 24, Data.word_6);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_I_DATA + 28, Data.word_7);
}

XUz_foc_sample_Self_i XUz_foc_sample_Get_self_i(XUz_foc_sample *InstancePtr) {
    XUz_foc_sample_Self_i Data;

    Data.word_0 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_I_DATA + 0);
    Data.word_1 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_I_DATA + 4);
    Data.word_2 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_I_DATA + 8);
    Data.word_3 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_I_DATA + 12);
    Data.word_4 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_I_DATA + 16);
    Data.word_5 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_I_DATA + 20);
    Data.word_6 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_I_DATA + 24);
    Data.word_7 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_I_DATA + 28);
    return Data;
}

XUz_foc_sample_Self_o XUz_foc_sample_Get_self_o(XUz_foc_sample *InstancePtr) {
    XUz_foc_sample_Self_o Data;

    Data.word_0 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_O_DATA + 0);
    Data.word_1 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_O_DATA + 4);
    Data.word_2 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_O_DATA + 8);
    Data.word_3 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_O_DATA + 12);
    Data.word_4 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_O_DATA + 16);
    Data.word_5 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_O_DATA + 20);
    Data.word_6 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_O_DATA + 24);
    Data.word_7 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_O_DATA + 28);
    return Data;
}

u32 XUz_foc_sample_Get_self_o_vld(XUz_foc_sample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_SELF_O_CTRL);
    return Data & 0x1;
}

void XUz_foc_sample_Set_i_actual_Ampere(XUz_foc_sample *InstancePtr, XUz_foc_sample_I_actual_ampere Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_I_ACTUAL_AMPERE_DATA + 0, Data.word_0);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_I_ACTUAL_AMPERE_DATA + 4, Data.word_1);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_I_ACTUAL_AMPERE_DATA + 8, Data.word_2);
}

XUz_foc_sample_I_actual_ampere XUz_foc_sample_Get_i_actual_Ampere(XUz_foc_sample *InstancePtr) {
    XUz_foc_sample_I_actual_ampere Data;

    Data.word_0 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_I_ACTUAL_AMPERE_DATA + 0);
    Data.word_1 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_I_ACTUAL_AMPERE_DATA + 4);
    Data.word_2 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_I_ACTUAL_AMPERE_DATA + 8);
    return Data;
}

void XUz_foc_sample_Set_V_dc_volts(XUz_foc_sample *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_V_DC_VOLTS_DATA, Data);
}

u32 XUz_foc_sample_Get_V_dc_volts(XUz_foc_sample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_V_DC_VOLTS_DATA);
    return Data;
}

void XUz_foc_sample_Set_omega_el_rad_per_sec(XUz_foc_sample *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_OMEGA_EL_RAD_PER_SEC_DATA, Data);
}

u32 XUz_foc_sample_Get_omega_el_rad_per_sec(XUz_foc_sample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_OMEGA_EL_RAD_PER_SEC_DATA);
    return Data;
}

void XUz_foc_sample_Set_Controller_id(XUz_foc_sample *InstancePtr, XUz_foc_sample_Controller_id Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_ID_DATA + 0, Data.word_0);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_ID_DATA + 4, Data.word_1);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_ID_DATA + 8, Data.word_2);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_ID_DATA + 12, Data.word_3);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_ID_DATA + 16, Data.word_4);
}

XUz_foc_sample_Controller_id XUz_foc_sample_Get_Controller_id(XUz_foc_sample *InstancePtr) {
    XUz_foc_sample_Controller_id Data;

    Data.word_0 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_ID_DATA + 0);
    Data.word_1 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_ID_DATA + 4);
    Data.word_2 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_ID_DATA + 8);
    Data.word_3 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_ID_DATA + 12);
    Data.word_4 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_ID_DATA + 16);
    return Data;
}

void XUz_foc_sample_Set_Controller_iq(XUz_foc_sample *InstancePtr, XUz_foc_sample_Controller_iq Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_IQ_DATA + 0, Data.word_0);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_IQ_DATA + 4, Data.word_1);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_IQ_DATA + 8, Data.word_2);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_IQ_DATA + 12, Data.word_3);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_IQ_DATA + 16, Data.word_4);
}

XUz_foc_sample_Controller_iq XUz_foc_sample_Get_Controller_iq(XUz_foc_sample *InstancePtr) {
    XUz_foc_sample_Controller_iq Data;

    Data.word_0 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_IQ_DATA + 0);
    Data.word_1 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_IQ_DATA + 4);
    Data.word_2 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_IQ_DATA + 8);
    Data.word_3 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_IQ_DATA + 12);
    Data.word_4 = XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_IQ_DATA + 16);
    return Data;
}

void XUz_foc_sample_InterruptGlobalEnable(XUz_foc_sample *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_GIE, 1);
}

void XUz_foc_sample_InterruptGlobalDisable(XUz_foc_sample *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_GIE, 0);
}

void XUz_foc_sample_InterruptEnable(XUz_foc_sample *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_IER);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_IER, Register | Mask);
}

void XUz_foc_sample_InterruptDisable(XUz_foc_sample *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_IER);
    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_IER, Register & (~Mask));
}

void XUz_foc_sample_InterruptClear(XUz_foc_sample *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_foc_sample_WriteReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_ISR, Mask);
}

u32 XUz_foc_sample_InterruptGetEnabled(XUz_foc_sample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_IER);
}

u32 XUz_foc_sample_InterruptGetStatus(XUz_foc_sample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XUz_foc_sample_ReadReg(InstancePtr->Din_BaseAddress, XUZ_FOC_SAMPLE_DIN_ADDR_ISR);
}

