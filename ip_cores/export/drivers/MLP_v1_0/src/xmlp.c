// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xmlp.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XMlp_CfgInitialize(XMlp *InstancePtr, XMlp_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XMlp_Start(XMlp *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AP_CTRL) & 0x80;
    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XMlp_IsDone(XMlp *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XMlp_IsIdle(XMlp *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XMlp_IsReady(XMlp *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XMlp_EnableAutoRestart(XMlp *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XMlp_DisableAutoRestart(XMlp *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AP_CTRL, 0);
}

void XMlp_Set_input_r(XMlp *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_INPUT_R_DATA, (u32)(Data));
    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_INPUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XMlp_Get_input_r(XMlp *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_INPUT_R_DATA);
    Data += (u64)XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_INPUT_R_DATA + 4) << 32;
    return Data;
}

void XMlp_Set_output_r(XMlp *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_OUTPUT_R_DATA, (u32)(Data));
    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_OUTPUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XMlp_Get_output_r(XMlp *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_OUTPUT_R_DATA);
    Data += (u64)XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_OUTPUT_R_DATA + 4) << 32;
    return Data;
}

void XMlp_Set_axiWeightInput(XMlp *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AXIWEIGHTINPUT_DATA, (u32)(Data));
    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AXIWEIGHTINPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XMlp_Get_axiWeightInput(XMlp *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AXIWEIGHTINPUT_DATA);
    Data += (u64)XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AXIWEIGHTINPUT_DATA + 4) << 32;
    return Data;
}

void XMlp_Set_axiBiasInput(XMlp *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AXIBIASINPUT_DATA, (u32)(Data));
    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AXIBIASINPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XMlp_Get_axiBiasInput(XMlp *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AXIBIASINPUT_DATA);
    Data += (u64)XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AXIBIASINPUT_DATA + 4) << 32;
    return Data;
}

void XMlp_Set_axiLayerOutput(XMlp *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AXILAYEROUTPUT_DATA, (u32)(Data));
    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AXILAYEROUTPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XMlp_Get_axiLayerOutput(XMlp *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AXILAYEROUTPUT_DATA);
    Data += (u64)XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_AXILAYEROUTPUT_DATA + 4) << 32;
    return Data;
}

void XMlp_Set_numberInputs(XMlp *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_NUMBERINPUTS_DATA, Data);
}

u32 XMlp_Get_numberInputs(XMlp *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_NUMBERINPUTS_DATA);
    return Data;
}

void XMlp_Set_numberOutputs(XMlp *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_NUMBEROUTPUTS_DATA, Data);
}

u32 XMlp_Get_numberOutputs(XMlp *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_NUMBEROUTPUTS_DATA);
    return Data;
}

void XMlp_Set_numberLayers(XMlp *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_NUMBERLAYERS_DATA, Data);
}

u32 XMlp_Get_numberLayers(XMlp *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_NUMBERLAYERS_DATA);
    return Data;
}

void XMlp_Set_numberNeurons(XMlp *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_NUMBERNEURONS_DATA, Data);
}

u32 XMlp_Get_numberNeurons(XMlp *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_NUMBERNEURONS_DATA);
    return Data;
}

void XMlp_Set_loadParameters(XMlp *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_LOADPARAMETERS_DATA, Data);
}

u32 XMlp_Get_loadParameters(XMlp *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_LOADPARAMETERS_DATA);
    return Data;
}

void XMlp_Set_exportLayers(XMlp *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_EXPORTLAYERS_DATA, Data);
}

u32 XMlp_Get_exportLayers(XMlp *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_EXPORTLAYERS_DATA);
    return Data;
}

void XMlp_InterruptGlobalEnable(XMlp *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_GIE, 1);
}

void XMlp_InterruptGlobalDisable(XMlp *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_GIE, 0);
}

void XMlp_InterruptEnable(XMlp *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_IER);
    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_IER, Register | Mask);
}

void XMlp_InterruptDisable(XMlp *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_IER);
    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_IER, Register & (~Mask));
}

void XMlp_InterruptClear(XMlp *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMlp_WriteReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_ISR, Mask);
}

u32 XMlp_InterruptGetEnabled(XMlp *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_IER);
}

u32 XMlp_InterruptGetStatus(XMlp *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMlp_ReadReg(InstancePtr->Control_BaseAddress, XMLP_CONTROL_ADDR_ISR);
}

