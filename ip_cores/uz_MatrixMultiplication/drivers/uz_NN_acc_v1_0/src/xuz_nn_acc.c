// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xuz_nn_acc.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XUz_nn_acc_CfgInitialize(XUz_nn_acc *InstancePtr, XUz_nn_acc_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XUz_nn_acc_Start(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL) & 0x80;
    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XUz_nn_acc_IsDone(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XUz_nn_acc_IsIdle(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XUz_nn_acc_IsReady(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XUz_nn_acc_EnableAutoRestart(XUz_nn_acc *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XUz_nn_acc_DisableAutoRestart(XUz_nn_acc *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL, 0);
}

void XUz_nn_acc_Set_Observation_Input(XUz_nn_acc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_OBSERVATION_INPUT_DATA, Data);
}

u32 XUz_nn_acc_Get_Observation_Input(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_OBSERVATION_INPUT_DATA);
    return Data;
}

void XUz_nn_acc_Set_L_Input_Weights_input(XUz_nn_acc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_L_INPUT_WEIGHTS_INPUT_DATA, Data);
}

u32 XUz_nn_acc_Get_L_Input_Weights_input(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_L_INPUT_WEIGHTS_INPUT_DATA);
    return Data;
}

void XUz_nn_acc_Set_L_1_Weights_input(XUz_nn_acc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_L_1_WEIGHTS_INPUT_DATA, Data);
}

u32 XUz_nn_acc_Get_L_1_Weights_input(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_L_1_WEIGHTS_INPUT_DATA);
    return Data;
}

void XUz_nn_acc_Set_L_2_Weights_input(XUz_nn_acc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_L_2_WEIGHTS_INPUT_DATA, Data);
}

u32 XUz_nn_acc_Get_L_2_Weights_input(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_L_2_WEIGHTS_INPUT_DATA);
    return Data;
}

void XUz_nn_acc_Set_L_3_Weights_input(XUz_nn_acc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_L_3_WEIGHTS_INPUT_DATA, Data);
}

u32 XUz_nn_acc_Get_L_3_Weights_input(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_L_3_WEIGHTS_INPUT_DATA);
    return Data;
}

void XUz_nn_acc_Set_Action_output(XUz_nn_acc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_ACTION_OUTPUT_DATA, Data);
}

u32 XUz_nn_acc_Get_Action_output(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_ACTION_OUTPUT_DATA);
    return Data;
}

void XUz_nn_acc_Set_L_Input_Bias_input(XUz_nn_acc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_L_INPUT_BIAS_INPUT_DATA, Data);
}

u32 XUz_nn_acc_Get_L_Input_Bias_input(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_L_INPUT_BIAS_INPUT_DATA);
    return Data;
}

void XUz_nn_acc_Set_L_1_Bias_input(XUz_nn_acc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_L_1_BIAS_INPUT_DATA, Data);
}

u32 XUz_nn_acc_Get_L_1_Bias_input(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_L_1_BIAS_INPUT_DATA);
    return Data;
}

void XUz_nn_acc_Set_L_2_Bias_input(XUz_nn_acc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_L_2_BIAS_INPUT_DATA, Data);
}

u32 XUz_nn_acc_Get_L_2_Bias_input(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_L_2_BIAS_INPUT_DATA);
    return Data;
}

void XUz_nn_acc_Set_L_3_Bias_input(XUz_nn_acc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_L_3_BIAS_INPUT_DATA, Data);
}

u32 XUz_nn_acc_Get_L_3_Bias_input(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_L_3_BIAS_INPUT_DATA);
    return Data;
}

void XUz_nn_acc_Set_copy_mats_flag(XUz_nn_acc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_COPY_MATS_FLAG_DATA, Data);
}

u32 XUz_nn_acc_Get_copy_mats_flag(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_COPY_MATS_FLAG_DATA);
    return Data;
}

void XUz_nn_acc_Set_Observation_size_input(XUz_nn_acc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_OBSERVATION_SIZE_INPUT_DATA, Data);
}

u32 XUz_nn_acc_Get_Observation_size_input(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_OBSERVATION_SIZE_INPUT_DATA);
    return Data;
}

void XUz_nn_acc_Set_Action_size_input(XUz_nn_acc *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_ACTION_SIZE_INPUT_DATA, Data);
}

u32 XUz_nn_acc_Get_Action_size_input(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_ACTION_SIZE_INPUT_DATA);
    return Data;
}

u32 XUz_nn_acc_Get_copy_flag_out(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_COPY_FLAG_OUT_DATA);
    return Data;
}

u32 XUz_nn_acc_Get_matrices_updated_out(XUz_nn_acc *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_MATRICES_UPDATED_OUT_DATA);
    return Data;
}

void XUz_nn_acc_InterruptGlobalEnable(XUz_nn_acc *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_GIE, 1);
}

void XUz_nn_acc_InterruptGlobalDisable(XUz_nn_acc *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_GIE, 0);
}

void XUz_nn_acc_InterruptEnable(XUz_nn_acc *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_IER);
    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_IER, Register | Mask);
}

void XUz_nn_acc_InterruptDisable(XUz_nn_acc *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_IER);
    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_IER, Register & (~Mask));
}

void XUz_nn_acc_InterruptClear(XUz_nn_acc *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XUz_nn_acc_WriteReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_ISR, Mask);
}

u32 XUz_nn_acc_InterruptGetEnabled(XUz_nn_acc *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_IER);
}

u32 XUz_nn_acc_InterruptGetStatus(XUz_nn_acc *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XUz_nn_acc_ReadReg(InstancePtr->Control_BaseAddress, XUZ_NN_ACC_CONTROL_ADDR_ISR);
}

