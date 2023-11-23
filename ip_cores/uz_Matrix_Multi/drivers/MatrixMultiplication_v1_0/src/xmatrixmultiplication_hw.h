// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read/COR)
//        bit 4  - ap_continue (Read/Write/SC)
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
// 0x10 : Data signal of A_rows
//        bit 31~0 - A_rows[31:0] (Read/Write)
// 0x14 : Data signal of A_rows
//        bit 31~0 - A_rows[63:32] (Read/Write)
// 0x18 : reserved
// 0x60 : Data signal of B_rows
//        bit 31~0 - B_rows[31:0] (Read/Write)
// 0x64 : Data signal of B_rows
//        bit 31~0 - B_rows[63:32] (Read/Write)
// 0x68 : reserved
// 0x6c : Data signal of B_columns
//        bit 31~0 - B_columns[31:0] (Read/Write)
// 0x70 : Data signal of B_columns
//        bit 31~0 - B_columns[63:32] (Read/Write)
// 0x74 : reserved
// 0x20 ~
// 0x3f : Memory 'A' (5 * 32b)
//        Word n : bit [31:0] - A[n]
// 0x40 ~
// 0x5f : Memory 'C_out' (5 * 32b)
//        Word n : bit [31:0] - C_out[n]
// 0x80 ~
// 0xff : Memory 'B' (25 * 32b)
//        Word n : bit [31:0] - B[n]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XMATRIXMULTIPLICATION_CONTROL_ADDR_AP_CTRL        0x00
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_GIE            0x04
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_IER            0x08
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_ISR            0x0c
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_A_ROWS_DATA    0x10
#define XMATRIXMULTIPLICATION_CONTROL_BITS_A_ROWS_DATA    64
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_B_ROWS_DATA    0x60
#define XMATRIXMULTIPLICATION_CONTROL_BITS_B_ROWS_DATA    64
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_B_COLUMNS_DATA 0x6c
#define XMATRIXMULTIPLICATION_CONTROL_BITS_B_COLUMNS_DATA 64
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_A_BASE         0x20
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_A_HIGH         0x3f
#define XMATRIXMULTIPLICATION_CONTROL_WIDTH_A             32
#define XMATRIXMULTIPLICATION_CONTROL_DEPTH_A             5
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_BASE     0x40
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_HIGH     0x5f
#define XMATRIXMULTIPLICATION_CONTROL_WIDTH_C_OUT         32
#define XMATRIXMULTIPLICATION_CONTROL_DEPTH_C_OUT         5
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_B_BASE         0x80
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_B_HIGH         0xff
#define XMATRIXMULTIPLICATION_CONTROL_WIDTH_B             32
#define XMATRIXMULTIPLICATION_CONTROL_DEPTH_B             25

