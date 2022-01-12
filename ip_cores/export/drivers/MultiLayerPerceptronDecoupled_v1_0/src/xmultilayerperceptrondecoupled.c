// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xmultilayerperceptrondecoupled.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XMultilayerperceptrondecoupled_CfgInitialize(XMultilayerperceptrondecoupled *InstancePtr, XMultilayerperceptrondecoupled_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->Configuration_BaseAddress = ConfigPtr->Configuration_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XMultilayerperceptrondecoupled_Start(XMultilayerperceptrondecoupled *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_AP_CTRL) & 0x80;
    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_AP_CTRL, Data | 0x01);
}

u32 XMultilayerperceptrondecoupled_IsDone(XMultilayerperceptrondecoupled *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XMultilayerperceptrondecoupled_IsIdle(XMultilayerperceptrondecoupled *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XMultilayerperceptrondecoupled_IsReady(XMultilayerperceptrondecoupled *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XMultilayerperceptrondecoupled_EnableAutoRestart(XMultilayerperceptrondecoupled *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_AP_CTRL, 0x80);
}

void XMultilayerperceptrondecoupled_DisableAutoRestart(XMultilayerperceptrondecoupled *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_AP_CTRL, 0);
}

void XMultilayerperceptrondecoupled_Set_input_r(XMultilayerperceptrondecoupled *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_INPUT_R_DATA, (u32)(Data));
    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_INPUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XMultilayerperceptrondecoupled_Get_input_r(XMultilayerperceptrondecoupled *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_INPUT_R_DATA);
    Data += (u64)XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_INPUT_R_DATA + 4) << 32;
    return Data;
}

void XMultilayerperceptrondecoupled_Set_output_r(XMultilayerperceptrondecoupled *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_OUTPUT_R_DATA, (u32)(Data));
    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_OUTPUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XMultilayerperceptrondecoupled_Get_output_r(XMultilayerperceptrondecoupled *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_OUTPUT_R_DATA);
    Data += (u64)XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_OUTPUT_R_DATA + 4) << 32;
    return Data;
}

void XMultilayerperceptrondecoupled_Set_axiWeightInput(XMultilayerperceptrondecoupled *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_AXIWEIGHTINPUT_DATA, (u32)(Data));
    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_AXIWEIGHTINPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XMultilayerperceptrondecoupled_Get_axiWeightInput(XMultilayerperceptrondecoupled *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_AXIWEIGHTINPUT_DATA);
    Data += (u64)XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_AXIWEIGHTINPUT_DATA + 4) << 32;
    return Data;
}

void XMultilayerperceptrondecoupled_Set_axiBiasInput(XMultilayerperceptrondecoupled *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_AXIBIASINPUT_DATA, (u32)(Data));
    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_AXIBIASINPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XMultilayerperceptrondecoupled_Get_axiBiasInput(XMultilayerperceptrondecoupled *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_AXIBIASINPUT_DATA);
    Data += (u64)XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_AXIBIASINPUT_DATA + 4) << 32;
    return Data;
}

void XMultilayerperceptrondecoupled_Set_axiWeightOutput(XMultilayerperceptrondecoupled *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_AXIWEIGHTOUTPUT_DATA, (u32)(Data));
    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_AXIWEIGHTOUTPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XMultilayerperceptrondecoupled_Get_axiWeightOutput(XMultilayerperceptrondecoupled *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_AXIWEIGHTOUTPUT_DATA);
    Data += (u64)XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_AXIWEIGHTOUTPUT_DATA + 4) << 32;
    return Data;
}

void XMultilayerperceptrondecoupled_Set_axiBiasOutput(XMultilayerperceptrondecoupled *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_AXIBIASOUTPUT_DATA, (u32)(Data));
    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_AXIBIASOUTPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XMultilayerperceptrondecoupled_Get_axiBiasOutput(XMultilayerperceptrondecoupled *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_AXIBIASOUTPUT_DATA);
    Data += (u64)XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Control_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONTROL_ADDR_AXIBIASOUTPUT_DATA + 4) << 32;
    return Data;
}

void XMultilayerperceptrondecoupled_Set_numberInputs(XMultilayerperceptrondecoupled *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_NUMBERINPUTS_DATA, Data);
}

u32 XMultilayerperceptrondecoupled_Get_numberInputs(XMultilayerperceptrondecoupled *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_NUMBERINPUTS_DATA);
    return Data;
}

void XMultilayerperceptrondecoupled_Set_numberOutputs(XMultilayerperceptrondecoupled *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_NUMBEROUTPUTS_DATA, Data);
}

u32 XMultilayerperceptrondecoupled_Get_numberOutputs(XMultilayerperceptrondecoupled *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_NUMBEROUTPUTS_DATA);
    return Data;
}

void XMultilayerperceptrondecoupled_Set_numberLayers(XMultilayerperceptrondecoupled *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_NUMBERLAYERS_DATA, Data);
}

u32 XMultilayerperceptrondecoupled_Get_numberLayers(XMultilayerperceptrondecoupled *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_NUMBERLAYERS_DATA);
    return Data;
}

void XMultilayerperceptrondecoupled_Set_numberNeurons(XMultilayerperceptrondecoupled *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_NUMBERNEURONS_DATA, Data);
}

u32 XMultilayerperceptrondecoupled_Get_numberNeurons(XMultilayerperceptrondecoupled *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_NUMBERNEURONS_DATA);
    return Data;
}

void XMultilayerperceptrondecoupled_Set_loadParameters(XMultilayerperceptrondecoupled *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_LOADPARAMETERS_DATA, Data);
}

u32 XMultilayerperceptrondecoupled_Get_loadParameters(XMultilayerperceptrondecoupled *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_LOADPARAMETERS_DATA);
    return Data;
}

void XMultilayerperceptrondecoupled_Set_exportLayers(XMultilayerperceptrondecoupled *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_EXPORTLAYERS_DATA, Data);
}

u32 XMultilayerperceptrondecoupled_Get_exportLayers(XMultilayerperceptrondecoupled *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_EXPORTLAYERS_DATA);
    return Data;
}

void XMultilayerperceptrondecoupled_InterruptGlobalEnable(XMultilayerperceptrondecoupled *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_GIE, 1);
}

void XMultilayerperceptrondecoupled_InterruptGlobalDisable(XMultilayerperceptrondecoupled *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_GIE, 0);
}

void XMultilayerperceptrondecoupled_InterruptEnable(XMultilayerperceptrondecoupled *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_IER);
    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_IER, Register | Mask);
}

void XMultilayerperceptrondecoupled_InterruptDisable(XMultilayerperceptrondecoupled *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_IER);
    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_IER, Register & (~Mask));
}

void XMultilayerperceptrondecoupled_InterruptClear(XMultilayerperceptrondecoupled *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMultilayerperceptrondecoupled_WriteReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_ISR, Mask);
}

u32 XMultilayerperceptrondecoupled_InterruptGetEnabled(XMultilayerperceptrondecoupled *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_IER);
}

u32 XMultilayerperceptrondecoupled_InterruptGetStatus(XMultilayerperceptrondecoupled *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMultilayerperceptrondecoupled_ReadReg(InstancePtr->Configuration_BaseAddress, XMULTILAYERPERCEPTRONDECOUPLED_CONFIGURATION_ADDR_ISR);
}

