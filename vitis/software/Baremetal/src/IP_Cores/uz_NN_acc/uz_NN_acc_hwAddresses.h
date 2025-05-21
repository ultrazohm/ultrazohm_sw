#ifndef UZ_NN_ACC_HWADDRESSES_H
#define UZ_NN_ACC_HWADDRESSES_H

// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read/COR)
//        bit 7  - auto_restart (Read/Write)
//        bit 9  - interrupt (Read)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0 - enable ap_done interrupt (Read/Write)
//        bit 1 - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0 - ap_done (Read/TOW)
//        bit 1 - ap_ready (Read/TOW)
//        others - reserved
// 0x10 : Data signal of Observation_Input
//        bit 31~0 - Observation_Input[31:0] (Read/Write)
// 0x14 : Data signal of Observation_Input
//        bit 31~0 - Observation_Input[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of L_1_Weights_input
//        bit 31~0 - L_1_Weights_input[31:0] (Read/Write)
// 0x20 : Data signal of L_1_Weights_input
//        bit 31~0 - L_1_Weights_input[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of L_2_Weights_input
//        bit 31~0 - L_2_Weights_input[31:0] (Read/Write)
// 0x2c : Data signal of L_2_Weights_input
//        bit 31~0 - L_2_Weights_input[63:32] (Read/Write)
// 0x30 : reserved
// 0x34 : Data signal of L_3_Weights_input
//        bit 31~0 - L_3_Weights_input[31:0] (Read/Write)
// 0x38 : Data signal of L_3_Weights_input
//        bit 31~0 - L_3_Weights_input[63:32] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of L_Output_Weights_input
//        bit 31~0 - L_Output_Weights_input[31:0] (Read/Write)
// 0x44 : Data signal of L_Output_Weights_input
//        bit 31~0 - L_Output_Weights_input[63:32] (Read/Write)
// 0x48 : reserved
// 0x4c : Data signal of Action_output
//        bit 31~0 - Action_output[31:0] (Read/Write)
// 0x50 : Data signal of Action_output
//        bit 31~0 - Action_output[63:32] (Read/Write)
// 0x54 : reserved
// 0x58 : Data signal of L_1_Bias_input
//        bit 31~0 - L_1_Bias_input[31:0] (Read/Write)
// 0x5c : Data signal of L_1_Bias_input
//        bit 31~0 - L_1_Bias_input[63:32] (Read/Write)
// 0x60 : reserved
// 0x64 : Data signal of L_2_Bias_input
//        bit 31~0 - L_2_Bias_input[31:0] (Read/Write)
// 0x68 : Data signal of L_2_Bias_input
//        bit 31~0 - L_2_Bias_input[63:32] (Read/Write)
// 0x6c : reserved
// 0x70 : Data signal of L_3_Bias_input
//        bit 31~0 - L_3_Bias_input[31:0] (Read/Write)
// 0x74 : Data signal of L_3_Bias_input
//        bit 31~0 - L_3_Bias_input[63:32] (Read/Write)
// 0x78 : reserved
// 0x7c : Data signal of L_Output_Bias_input
//        bit 31~0 - L_Output_Bias_input[31:0] (Read/Write)
// 0x80 : Data signal of L_Output_Bias_input
//        bit 31~0 - L_Output_Bias_input[63:32] (Read/Write)
// 0x84 : reserved
// 0x88 : Data signal of copy_mats_flag
//        bit 0  - copy_mats_flag[0] (Read/Write)
//        others - reserved
// 0x8c : reserved
// 0x90 : Data signal of Observation_size_input
//        bit 31~0 - Observation_size_input[31:0] (Read/Write)
// 0x94 : reserved
// 0x98 : Data signal of Action_size_input
//        bit 31~0 - Action_size_input[31:0] (Read/Write)
// 0x9c : reserved
// 0xa0 : Data signal of copy_flag_out
//        bit 0  - copy_flag_out[0] (Read)
//        others - reserved
// 0xa4 : reserved
// 0xb0 : Data signal of matrices_updated_out
//        bit 0  - matrices_updated_out[0] (Read)
//        others - reserved
// 0xb4 : reserved
// 0xc0 : Data signal of compute_flag
//        bit 0  - compute_flag[0] (Read/Write)
//        others - reserved
// 0xc4 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL                     0x00
#define XUZ_NN_ACC_CONTROL_ADDR_GIE                         0x04
#define XUZ_NN_ACC_CONTROL_ADDR_IER                         0x08
#define XUZ_NN_ACC_CONTROL_ADDR_ISR                         0x0c
#define XUZ_NN_ACC_CONTROL_ADDR_OBSERVATION_INPUT_DATA      0x10
#define XUZ_NN_ACC_CONTROL_BITS_OBSERVATION_INPUT_DATA      64
#define XUZ_NN_ACC_CONTROL_ADDR_L_1_WEIGHTS_INPUT_DATA      0x1c
#define XUZ_NN_ACC_CONTROL_BITS_L_1_WEIGHTS_INPUT_DATA      64
#define XUZ_NN_ACC_CONTROL_ADDR_L_2_WEIGHTS_INPUT_DATA      0x28
#define XUZ_NN_ACC_CONTROL_BITS_L_2_WEIGHTS_INPUT_DATA      64
#define XUZ_NN_ACC_CONTROL_ADDR_L_3_WEIGHTS_INPUT_DATA      0x34
#define XUZ_NN_ACC_CONTROL_BITS_L_3_WEIGHTS_INPUT_DATA      64
#define XUZ_NN_ACC_CONTROL_ADDR_L_OUTPUT_WEIGHTS_INPUT_DATA 0x40
#define XUZ_NN_ACC_CONTROL_BITS_L_OUTPUT_WEIGHTS_INPUT_DATA 64
#define XUZ_NN_ACC_CONTROL_ADDR_ACTION_OUTPUT_DATA          0x4c
#define XUZ_NN_ACC_CONTROL_BITS_ACTION_OUTPUT_DATA          64
#define XUZ_NN_ACC_CONTROL_ADDR_L_1_BIAS_INPUT_DATA         0x58
#define XUZ_NN_ACC_CONTROL_BITS_L_1_BIAS_INPUT_DATA         64
#define XUZ_NN_ACC_CONTROL_ADDR_L_2_BIAS_INPUT_DATA         0x64
#define XUZ_NN_ACC_CONTROL_BITS_L_2_BIAS_INPUT_DATA         64
#define XUZ_NN_ACC_CONTROL_ADDR_L_3_BIAS_INPUT_DATA         0x70
#define XUZ_NN_ACC_CONTROL_BITS_L_3_BIAS_INPUT_DATA         64
#define XUZ_NN_ACC_CONTROL_ADDR_L_OUTPUT_BIAS_INPUT_DATA    0x7c
#define XUZ_NN_ACC_CONTROL_BITS_L_OUTPUT_BIAS_INPUT_DATA    64
#define XUZ_NN_ACC_CONTROL_ADDR_COPY_MATS_FLAG_DATA         0x88
#define XUZ_NN_ACC_CONTROL_BITS_COPY_MATS_FLAG_DATA         1
#define XUZ_NN_ACC_CONTROL_ADDR_OBSERVATION_SIZE_INPUT_DATA 0x90
#define XUZ_NN_ACC_CONTROL_BITS_OBSERVATION_SIZE_INPUT_DATA 32
#define XUZ_NN_ACC_CONTROL_ADDR_ACTION_SIZE_INPUT_DATA      0x98
#define XUZ_NN_ACC_CONTROL_BITS_ACTION_SIZE_INPUT_DATA      32
#define XUZ_NN_ACC_CONTROL_ADDR_COPY_FLAG_OUT_DATA          0xa0
#define XUZ_NN_ACC_CONTROL_BITS_COPY_FLAG_OUT_DATA          1
#define XUZ_NN_ACC_CONTROL_ADDR_MATRICES_UPDATED_OUT_DATA   0xb0
#define XUZ_NN_ACC_CONTROL_BITS_MATRICES_UPDATED_OUT_DATA   1
#define XUZ_NN_ACC_CONTROL_ADDR_COMPUTE_FLAG_DATA           0xc0
#define XUZ_NN_ACC_CONTROL_BITS_COMPUTE_FLAG_DATA           1

#endif
