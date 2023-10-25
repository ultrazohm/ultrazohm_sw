// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x000 : reserved
// 0x004 : reserved
// 0x008 : reserved
// 0x00c : reserved
// 0x010 : Data signal of A_rows
//         bit 31~0 - A_rows[31:0] (Read/Write)
// 0x014 : Data signal of A_rows
//         bit 31~0 - A_rows[63:32] (Read/Write)
// 0x018 : reserved
// 0x060 : Data signal of B_rows
//         bit 31~0 - B_rows[31:0] (Read/Write)
// 0x064 : Data signal of B_rows
//         bit 31~0 - B_rows[63:32] (Read/Write)
// 0x068 : reserved
// 0x06c : Data signal of B_columns
//         bit 31~0 - B_columns[31:0] (Read/Write)
// 0x070 : Data signal of B_columns
//         bit 31~0 - B_columns[63:32] (Read/Write)
// 0x074 : reserved
// 0x078 : Data signal of trigger
//         bit 0  - trigger[0] (Read/Write)
//         others - reserved
// 0x07c : reserved
// 0x100 : Data signal of is_done_i
//         bit 0  - is_done_i[0] (Read/Write)
//         others - reserved
// 0x104 : reserved
// 0x108 : Data signal of is_done_o
//         bit 0  - is_done_o[0] (Read)
//         others - reserved
// 0x10c : Control signal of is_done_o
//         bit 0  - is_done_o_ap_vld (Read/COR)
//         others - reserved
// 0x020 ~
// 0x03f : Memory 'A' (5 * 32b)
//         Word n : bit [31:0] - A[n]
// 0x040 ~
// 0x05f : Memory 'C_out' (5 * 32b)
//         Word n : bit [31:0] - C_out[n]
// 0x080 ~
// 0x0ff : Memory 'B' (25 * 32b)
//         Word n : bit [31:0] - B[n]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XMATRIXMULTIPLICATION_CONTROL_ADDR_A_ROWS_DATA    0x010
#define XMATRIXMULTIPLICATION_CONTROL_BITS_A_ROWS_DATA    64
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_B_ROWS_DATA    0x060
#define XMATRIXMULTIPLICATION_CONTROL_BITS_B_ROWS_DATA    64
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_B_COLUMNS_DATA 0x06c
#define XMATRIXMULTIPLICATION_CONTROL_BITS_B_COLUMNS_DATA 64
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_TRIGGER_DATA   0x078
#define XMATRIXMULTIPLICATION_CONTROL_BITS_TRIGGER_DATA   1
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_IS_DONE_I_DATA 0x100
#define XMATRIXMULTIPLICATION_CONTROL_BITS_IS_DONE_I_DATA 1
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_IS_DONE_O_DATA 0x108
#define XMATRIXMULTIPLICATION_CONTROL_BITS_IS_DONE_O_DATA 1
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_IS_DONE_O_CTRL 0x10c
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_A_BASE         0x020
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_A_HIGH         0x03f
#define XMATRIXMULTIPLICATION_CONTROL_WIDTH_A             32
#define XMATRIXMULTIPLICATION_CONTROL_DEPTH_A             5
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_BASE     0x040
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_HIGH     0x05f
#define XMATRIXMULTIPLICATION_CONTROL_WIDTH_C_OUT         32
#define XMATRIXMULTIPLICATION_CONTROL_DEPTH_C_OUT         5
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_B_BASE         0x080
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_B_HIGH         0x0ff
#define XMATRIXMULTIPLICATION_CONTROL_WIDTH_B             32
#define XMATRIXMULTIPLICATION_CONTROL_DEPTH_B             25

