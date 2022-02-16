// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - enable ap_done interrupt (Read/Write)
//        bit 1  - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - ap_done (COR/TOW)
//        bit 1  - ap_ready (COR/TOW)
//        others - reserved
// 0x10 : Data signal of input_r
//        bit 31~0 - input_r[31:0] (Read/Write)
// 0x14 : Data signal of input_r
//        bit 31~0 - input_r[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of output_r
//        bit 31~0 - output_r[31:0] (Read/Write)
// 0x20 : Data signal of output_r
//        bit 31~0 - output_r[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of axiWeightInput
//        bit 31~0 - axiWeightInput[31:0] (Read/Write)
// 0x2c : Data signal of axiWeightInput
//        bit 31~0 - axiWeightInput[63:32] (Read/Write)
// 0x30 : reserved
// 0x34 : Data signal of axiBiasInput
//        bit 31~0 - axiBiasInput[31:0] (Read/Write)
// 0x38 : Data signal of axiBiasInput
//        bit 31~0 - axiBiasInput[63:32] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of axiLayerOutput
//        bit 31~0 - axiLayerOutput[31:0] (Read/Write)
// 0x44 : Data signal of axiLayerOutput
//        bit 31~0 - axiLayerOutput[63:32] (Read/Write)
// 0x48 : reserved
// 0x4c : Data signal of numberInputs
//        bit 31~0 - numberInputs[31:0] (Read/Write)
// 0x50 : reserved
// 0x54 : Data signal of numberOutputs
//        bit 31~0 - numberOutputs[31:0] (Read/Write)
// 0x58 : reserved
// 0x5c : Data signal of numberLayers
//        bit 31~0 - numberLayers[31:0] (Read/Write)
// 0x60 : reserved
// 0x64 : Data signal of numberNeurons
//        bit 31~0 - numberNeurons[31:0] (Read/Write)
// 0x68 : reserved
// 0x6c : Data signal of loadParameters
//        bit 31~0 - loadParameters[31:0] (Read/Write)
// 0x70 : reserved
// 0x74 : Data signal of exportLayers
//        bit 31~0 - exportLayers[31:0] (Read/Write)
// 0x78 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XMLP_CONTROL_ADDR_AP_CTRL             0x00
#define XMLP_CONTROL_ADDR_GIE                 0x04
#define XMLP_CONTROL_ADDR_IER                 0x08
#define XMLP_CONTROL_ADDR_ISR                 0x0c
#define XMLP_CONTROL_ADDR_INPUT_R_DATA        0x10
#define XMLP_CONTROL_BITS_INPUT_R_DATA        64
#define XMLP_CONTROL_ADDR_OUTPUT_R_DATA       0x1c
#define XMLP_CONTROL_BITS_OUTPUT_R_DATA       64
#define XMLP_CONTROL_ADDR_AXIWEIGHTINPUT_DATA 0x28
#define XMLP_CONTROL_BITS_AXIWEIGHTINPUT_DATA 64
#define XMLP_CONTROL_ADDR_AXIBIASINPUT_DATA   0x34
#define XMLP_CONTROL_BITS_AXIBIASINPUT_DATA   64
#define XMLP_CONTROL_ADDR_AXILAYEROUTPUT_DATA 0x40
#define XMLP_CONTROL_BITS_AXILAYEROUTPUT_DATA 64
#define XMLP_CONTROL_ADDR_NUMBERINPUTS_DATA   0x4c
#define XMLP_CONTROL_BITS_NUMBERINPUTS_DATA   32
#define XMLP_CONTROL_ADDR_NUMBEROUTPUTS_DATA  0x54
#define XMLP_CONTROL_BITS_NUMBEROUTPUTS_DATA  32
#define XMLP_CONTROL_ADDR_NUMBERLAYERS_DATA   0x5c
#define XMLP_CONTROL_BITS_NUMBERLAYERS_DATA   32
#define XMLP_CONTROL_ADDR_NUMBERNEURONS_DATA  0x64
#define XMLP_CONTROL_BITS_NUMBERNEURONS_DATA  32
#define XMLP_CONTROL_ADDR_LOADPARAMETERS_DATA 0x6c
#define XMLP_CONTROL_BITS_LOADPARAMETERS_DATA 32
#define XMLP_CONTROL_ADDR_EXPORTLAYERS_DATA   0x74
#define XMLP_CONTROL_BITS_EXPORTLAYERS_DATA   32

