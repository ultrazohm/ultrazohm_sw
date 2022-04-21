// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xbgd.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XBgd_CfgInitialize(XBgd *InstancePtr, XBgd_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XBgd_Set_axiMlpResultsInput(XBgd *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIMLPRESULTSINPUT_DATA, (u32)(Data));
    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIMLPRESULTSINPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XBgd_Get_axiMlpResultsInput(XBgd *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIMLPRESULTSINPUT_DATA);
    Data += (u64)XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIMLPRESULTSINPUT_DATA + 4) << 32;
    return Data;
}

void XBgd_Set_axiClassesInput(XBgd *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXICLASSESINPUT_DATA, (u32)(Data));
    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXICLASSESINPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XBgd_Get_axiClassesInput(XBgd *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXICLASSESINPUT_DATA);
    Data += (u64)XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXICLASSESINPUT_DATA + 4) << 32;
    return Data;
}

void XBgd_Set_axiWeightInput(XBgd *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIWEIGHTINPUT_DATA, (u32)(Data));
    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIWEIGHTINPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XBgd_Get_axiWeightInput(XBgd *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIWEIGHTINPUT_DATA);
    Data += (u64)XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIWEIGHTINPUT_DATA + 4) << 32;
    return Data;
}

void XBgd_Set_axiBiasInput(XBgd *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIBIASINPUT_DATA, (u32)(Data));
    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIBIASINPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XBgd_Get_axiBiasInput(XBgd *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIBIASINPUT_DATA);
    Data += (u64)XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIBIASINPUT_DATA + 4) << 32;
    return Data;
}

void XBgd_Set_axiWeightOutput(XBgd *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIWEIGHTOUTPUT_DATA, (u32)(Data));
    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIWEIGHTOUTPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XBgd_Get_axiWeightOutput(XBgd *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIWEIGHTOUTPUT_DATA);
    Data += (u64)XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIWEIGHTOUTPUT_DATA + 4) << 32;
    return Data;
}

void XBgd_Set_axiBiasOutput(XBgd *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIBIASOUTPUT_DATA, (u32)(Data));
    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIBIASOUTPUT_DATA + 4, (u32)(Data >> 32));
}

u64 XBgd_Get_axiBiasOutput(XBgd *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIBIASOUTPUT_DATA);
    Data += (u64)XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_AXIBIASOUTPUT_DATA + 4) << 32;
    return Data;
}

void XBgd_Set_numberInputs(XBgd *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_NUMBERINPUTS_DATA, Data);
}

u32 XBgd_Get_numberInputs(XBgd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_NUMBERINPUTS_DATA);
    return Data;
}

void XBgd_Set_numberOutputs(XBgd *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_NUMBEROUTPUTS_DATA, Data);
}

u32 XBgd_Get_numberOutputs(XBgd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_NUMBEROUTPUTS_DATA);
    return Data;
}

void XBgd_Set_numberLayers(XBgd *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_NUMBERLAYERS_DATA, Data);
}

u32 XBgd_Get_numberLayers(XBgd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_NUMBERLAYERS_DATA);
    return Data;
}

void XBgd_Set_numberNeurons(XBgd *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_NUMBERNEURONS_DATA, Data);
}

u32 XBgd_Get_numberNeurons(XBgd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_NUMBERNEURONS_DATA);
    return Data;
}

void XBgd_Set_loadParameters(XBgd *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_LOADPARAMETERS_DATA, Data);
}

u32 XBgd_Get_loadParameters(XBgd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_LOADPARAMETERS_DATA);
    return Data;
}

void XBgd_Set_batchSize(XBgd *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_BATCHSIZE_DATA, Data);
}

u32 XBgd_Get_batchSize(XBgd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_BATCHSIZE_DATA);
    return Data;
}

void XBgd_Set_learningRate(XBgd *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBgd_WriteReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_LEARNINGRATE_DATA, Data);
}

u32 XBgd_Get_learningRate(XBgd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBgd_ReadReg(InstancePtr->Control_BaseAddress, XBGD_CONTROL_ADDR_LEARNINGRATE_DATA);
    return Data;
}

