// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x000 : Control signals
//         bit 0  - ap_start (Read/Write/COH)
//         bit 1  - ap_done (Read/COR)
//         bit 2  - ap_idle (Read)
//         bit 3  - ap_ready (Read/COR)
//         bit 7  - auto_restart (Read/Write)
//         bit 9  - interrupt (Read)
//         others - reserved
// 0x004 : Global Interrupt Enable Register
//         bit 0  - Global Interrupt Enable (Read/Write)
//         others - reserved
// 0x008 : IP Interrupt Enable Register (Read/Write)
//         bit 0 - enable ap_done interrupt (Read/Write)
//         bit 1 - enable ap_ready interrupt (Read/Write)
//         others - reserved
// 0x00c : IP Interrupt Status Register (Read/TOW)
//         bit 0 - ap_done (Read/TOW)
//         bit 1 - ap_ready (Read/TOW)
//         others - reserved
// 0x010 : Data signal of Observation_Input
//         bit 31~0 - Observation_Input[31:0] (Read/Write)
// 0x014 : reserved
// 0x018 : Data signal of L_1_Weights_input
//         bit 31~0 - L_1_Weights_input[31:0] (Read/Write)
// 0x01c : reserved
// 0x020 : Data signal of L_2_Weights_input
//         bit 31~0 - L_2_Weights_input[31:0] (Read/Write)
// 0x024 : reserved
// 0x028 : Data signal of L_3_Weights_input
//         bit 31~0 - L_3_Weights_input[31:0] (Read/Write)
// 0x02c : reserved
// 0x030 : Data signal of L_4_Weights_input
//         bit 31~0 - L_4_Weights_input[31:0] (Read/Write)
// 0x034 : reserved
// 0x038 : Data signal of L_5_Weights_input
//         bit 31~0 - L_5_Weights_input[31:0] (Read/Write)
// 0x03c : reserved
// 0x040 : Data signal of L_6_Weights_input
//         bit 31~0 - L_6_Weights_input[31:0] (Read/Write)
// 0x044 : reserved
// 0x048 : Data signal of L_7_Weights_input
//         bit 31~0 - L_7_Weights_input[31:0] (Read/Write)
// 0x04c : reserved
// 0x050 : Data signal of L_8_Weights_input
//         bit 31~0 - L_8_Weights_input[31:0] (Read/Write)
// 0x054 : reserved
// 0x058 : Data signal of L_9_Weights_input
//         bit 31~0 - L_9_Weights_input[31:0] (Read/Write)
// 0x05c : reserved
// 0x060 : Data signal of L_10_Weights_input
//         bit 31~0 - L_10_Weights_input[31:0] (Read/Write)
// 0x064 : reserved
// 0x068 : Data signal of L_Output_Weights_input
//         bit 31~0 - L_Output_Weights_input[31:0] (Read/Write)
// 0x06c : reserved
// 0x070 : Data signal of Action_output
//         bit 31~0 - Action_output[31:0] (Read/Write)
// 0x074 : reserved
// 0x078 : Data signal of L_1_Bias_input
//         bit 31~0 - L_1_Bias_input[31:0] (Read/Write)
// 0x07c : reserved
// 0x080 : Data signal of L_2_Bias_input
//         bit 31~0 - L_2_Bias_input[31:0] (Read/Write)
// 0x084 : reserved
// 0x088 : Data signal of L_3_Bias_input
//         bit 31~0 - L_3_Bias_input[31:0] (Read/Write)
// 0x08c : reserved
// 0x090 : Data signal of L_4_Bias_input
//         bit 31~0 - L_4_Bias_input[31:0] (Read/Write)
// 0x094 : reserved
// 0x098 : Data signal of L_5_Bias_input
//         bit 31~0 - L_5_Bias_input[31:0] (Read/Write)
// 0x09c : reserved
// 0x0a0 : Data signal of L_6_Bias_input
//         bit 31~0 - L_6_Bias_input[31:0] (Read/Write)
// 0x0a4 : reserved
// 0x0a8 : Data signal of L_7_Bias_input
//         bit 31~0 - L_7_Bias_input[31:0] (Read/Write)
// 0x0ac : reserved
// 0x0b0 : Data signal of L_8_Bias_input
//         bit 31~0 - L_8_Bias_input[31:0] (Read/Write)
// 0x0b4 : reserved
// 0x0b8 : Data signal of L_9_Bias_input
//         bit 31~0 - L_9_Bias_input[31:0] (Read/Write)
// 0x0bc : reserved
// 0x0c0 : Data signal of L_10_Bias_input
//         bit 31~0 - L_10_Bias_input[31:0] (Read/Write)
// 0x0c4 : reserved
// 0x0c8 : Data signal of L_Output_Bias_input
//         bit 31~0 - L_Output_Bias_input[31:0] (Read/Write)
// 0x0cc : reserved
// 0x0d0 : Data signal of copy_mats_flag
//         bit 0  - copy_mats_flag[0] (Read/Write)
//         others - reserved
// 0x0d4 : reserved
// 0x0d8 : Data signal of Observation_size_input
//         bit 31~0 - Observation_size_input[31:0] (Read/Write)
// 0x0dc : reserved
// 0x0e0 : Data signal of Action_size_input
//         bit 31~0 - Action_size_input[31:0] (Read/Write)
// 0x0e4 : reserved
// 0x0e8 : Data signal of copy_flag_out
//         bit 0  - copy_flag_out[0] (Read)
//         others - reserved
// 0x0ec : reserved
// 0x0f8 : Data signal of matrices_updated_out
//         bit 0  - matrices_updated_out[0] (Read)
//         others - reserved
// 0x0fc : reserved
// 0x108 : Data signal of compute_flag
//         bit 0  - compute_flag[0] (Read/Write)
//         others - reserved
// 0x10c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL                     0x000
#define XUZ_NN_ACC_CONTROL_ADDR_GIE                         0x004
#define XUZ_NN_ACC_CONTROL_ADDR_IER                         0x008
#define XUZ_NN_ACC_CONTROL_ADDR_ISR                         0x00c
#define XUZ_NN_ACC_CONTROL_ADDR_OBSERVATION_INPUT_DATA      0x010
#define XUZ_NN_ACC_CONTROL_BITS_OBSERVATION_INPUT_DATA      32
#define XUZ_NN_ACC_CONTROL_ADDR_L_1_WEIGHTS_INPUT_DATA      0x018
#define XUZ_NN_ACC_CONTROL_BITS_L_1_WEIGHTS_INPUT_DATA      32
#define XUZ_NN_ACC_CONTROL_ADDR_L_2_WEIGHTS_INPUT_DATA      0x020
#define XUZ_NN_ACC_CONTROL_BITS_L_2_WEIGHTS_INPUT_DATA      32
#define XUZ_NN_ACC_CONTROL_ADDR_L_3_WEIGHTS_INPUT_DATA      0x028
#define XUZ_NN_ACC_CONTROL_BITS_L_3_WEIGHTS_INPUT_DATA      32
#define XUZ_NN_ACC_CONTROL_ADDR_L_4_WEIGHTS_INPUT_DATA      0x030
#define XUZ_NN_ACC_CONTROL_BITS_L_4_WEIGHTS_INPUT_DATA      32
#define XUZ_NN_ACC_CONTROL_ADDR_L_5_WEIGHTS_INPUT_DATA      0x038
#define XUZ_NN_ACC_CONTROL_BITS_L_5_WEIGHTS_INPUT_DATA      32
#define XUZ_NN_ACC_CONTROL_ADDR_L_6_WEIGHTS_INPUT_DATA      0x040
#define XUZ_NN_ACC_CONTROL_BITS_L_6_WEIGHTS_INPUT_DATA      32
#define XUZ_NN_ACC_CONTROL_ADDR_L_7_WEIGHTS_INPUT_DATA      0x048
#define XUZ_NN_ACC_CONTROL_BITS_L_7_WEIGHTS_INPUT_DATA      32
#define XUZ_NN_ACC_CONTROL_ADDR_L_8_WEIGHTS_INPUT_DATA      0x050
#define XUZ_NN_ACC_CONTROL_BITS_L_8_WEIGHTS_INPUT_DATA      32
#define XUZ_NN_ACC_CONTROL_ADDR_L_9_WEIGHTS_INPUT_DATA      0x058
#define XUZ_NN_ACC_CONTROL_BITS_L_9_WEIGHTS_INPUT_DATA      32
#define XUZ_NN_ACC_CONTROL_ADDR_L_10_WEIGHTS_INPUT_DATA     0x060
#define XUZ_NN_ACC_CONTROL_BITS_L_10_WEIGHTS_INPUT_DATA     32
#define XUZ_NN_ACC_CONTROL_ADDR_L_OUTPUT_WEIGHTS_INPUT_DATA 0x068
#define XUZ_NN_ACC_CONTROL_BITS_L_OUTPUT_WEIGHTS_INPUT_DATA 32
#define XUZ_NN_ACC_CONTROL_ADDR_ACTION_OUTPUT_DATA          0x070
#define XUZ_NN_ACC_CONTROL_BITS_ACTION_OUTPUT_DATA          32
#define XUZ_NN_ACC_CONTROL_ADDR_L_1_BIAS_INPUT_DATA         0x078
#define XUZ_NN_ACC_CONTROL_BITS_L_1_BIAS_INPUT_DATA         32
#define XUZ_NN_ACC_CONTROL_ADDR_L_2_BIAS_INPUT_DATA         0x080
#define XUZ_NN_ACC_CONTROL_BITS_L_2_BIAS_INPUT_DATA         32
#define XUZ_NN_ACC_CONTROL_ADDR_L_3_BIAS_INPUT_DATA         0x088
#define XUZ_NN_ACC_CONTROL_BITS_L_3_BIAS_INPUT_DATA         32
#define XUZ_NN_ACC_CONTROL_ADDR_L_4_BIAS_INPUT_DATA         0x090
#define XUZ_NN_ACC_CONTROL_BITS_L_4_BIAS_INPUT_DATA         32
#define XUZ_NN_ACC_CONTROL_ADDR_L_5_BIAS_INPUT_DATA         0x098
#define XUZ_NN_ACC_CONTROL_BITS_L_5_BIAS_INPUT_DATA         32
#define XUZ_NN_ACC_CONTROL_ADDR_L_6_BIAS_INPUT_DATA         0x0a0
#define XUZ_NN_ACC_CONTROL_BITS_L_6_BIAS_INPUT_DATA         32
#define XUZ_NN_ACC_CONTROL_ADDR_L_7_BIAS_INPUT_DATA         0x0a8
#define XUZ_NN_ACC_CONTROL_BITS_L_7_BIAS_INPUT_DATA         32
#define XUZ_NN_ACC_CONTROL_ADDR_L_8_BIAS_INPUT_DATA         0x0b0
#define XUZ_NN_ACC_CONTROL_BITS_L_8_BIAS_INPUT_DATA         32
#define XUZ_NN_ACC_CONTROL_ADDR_L_9_BIAS_INPUT_DATA         0x0b8
#define XUZ_NN_ACC_CONTROL_BITS_L_9_BIAS_INPUT_DATA         32
#define XUZ_NN_ACC_CONTROL_ADDR_L_10_BIAS_INPUT_DATA        0x0c0
#define XUZ_NN_ACC_CONTROL_BITS_L_10_BIAS_INPUT_DATA        32
#define XUZ_NN_ACC_CONTROL_ADDR_L_OUTPUT_BIAS_INPUT_DATA    0x0c8
#define XUZ_NN_ACC_CONTROL_BITS_L_OUTPUT_BIAS_INPUT_DATA    32
#define XUZ_NN_ACC_CONTROL_ADDR_COPY_MATS_FLAG_DATA         0x0d0
#define XUZ_NN_ACC_CONTROL_BITS_COPY_MATS_FLAG_DATA         1
#define XUZ_NN_ACC_CONTROL_ADDR_OBSERVATION_SIZE_INPUT_DATA 0x0d8
#define XUZ_NN_ACC_CONTROL_BITS_OBSERVATION_SIZE_INPUT_DATA 32
#define XUZ_NN_ACC_CONTROL_ADDR_ACTION_SIZE_INPUT_DATA      0x0e0
#define XUZ_NN_ACC_CONTROL_BITS_ACTION_SIZE_INPUT_DATA      32
#define XUZ_NN_ACC_CONTROL_ADDR_COPY_FLAG_OUT_DATA          0x0e8
#define XUZ_NN_ACC_CONTROL_BITS_COPY_FLAG_OUT_DATA          1
#define XUZ_NN_ACC_CONTROL_ADDR_MATRICES_UPDATED_OUT_DATA   0x0f8
#define XUZ_NN_ACC_CONTROL_BITS_MATRICES_UPDATED_OUT_DATA   1
#define XUZ_NN_ACC_CONTROL_ADDR_COMPUTE_FLAG_DATA           0x108
#define XUZ_NN_ACC_CONTROL_BITS_COMPUTE_FLAG_DATA           1

