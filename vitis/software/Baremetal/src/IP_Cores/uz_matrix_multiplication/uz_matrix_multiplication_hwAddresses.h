#ifndef UZ_MATRIX_MULTIPLICATION_ADDRESSES_H_
#define UZ_MATRIX_MULTIPLICATION_ADDRESSES_H_


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
// 0x10 : Data signal of A_input
//        bit 31~0 - A_input[31:0] (Read/Write)
// 0x14 : Data signal of A_input
//        bit 31~0 - A_input[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of B1_input
//        bit 31~0 - B1_input[31:0] (Read/Write)
// 0x20 : Data signal of B1_input
//        bit 31~0 - B1_input[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of B2_input
//        bit 31~0 - B2_input[31:0] (Read/Write)
// 0x2c : Data signal of B2_input
//        bit 31~0 - B2_input[63:32] (Read/Write)
// 0x30 : reserved
// 0x34 : Data signal of C_output
//        bit 31~0 - C_output[31:0] (Read/Write)
// 0x38 : Data signal of C_output
//        bit 31~0 - C_output[63:32] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of copy_mats_flag
//        bit 0  - copy_mats_flag[0] (Read/Write)
//        others - reserved
// 0x44 : reserved
// 0x48 : Data signal of A_rows
//        bit 31~0 - A_rows[31:0] (Read/Write)
// 0x4c : reserved
// 0x50 : Data signal of B1_rows
//        bit 31~0 - B1_rows[31:0] (Read/Write)
// 0x54 : reserved
// 0x58 : Data signal of B1_columns
//        bit 31~0 - B1_columns[31:0] (Read/Write)
// 0x5c : reserved
// 0x60 : Data signal of B2_columns
//        bit 31~0 - B2_columns[31:0] (Read/Write)
// 0x64 : reserved
// 0x68 : Data signal of copy_flag_out
//        bit 0  - copy_flag_out[0] (Read)
//        others - reserved
// 0x6c : reserved
// 0x78 : Data signal of matrices_updated_out
//        bit 0  - matrices_updated_out[0] (Read)
//        others - reserved
// 0x7c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XMATRIXMULTIPLICATION_CONTROL_ADDR_AP_CTRL                   0x00
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_GIE                       0x04
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_IER                       0x08
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_ISR                       0x0c
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_A_INPUT_DATA              0x10
#define XMATRIXMULTIPLICATION_CONTROL_BITS_A_INPUT_DATA              64
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_B1_INPUT_DATA             0x1c
#define XMATRIXMULTIPLICATION_CONTROL_BITS_B1_INPUT_DATA             64
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_B2_INPUT_DATA             0x28
#define XMATRIXMULTIPLICATION_CONTROL_BITS_B2_INPUT_DATA             64
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUTPUT_DATA             0x34
#define XMATRIXMULTIPLICATION_CONTROL_BITS_C_OUTPUT_DATA             64
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_COPY_MATS_FLAG_DATA       0x40
#define XMATRIXMULTIPLICATION_CONTROL_BITS_COPY_MATS_FLAG_DATA       1
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_A_ROWS_DATA               0x48
#define XMATRIXMULTIPLICATION_CONTROL_BITS_A_ROWS_DATA               32
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_B1_ROWS_DATA              0x50
#define XMATRIXMULTIPLICATION_CONTROL_BITS_B1_ROWS_DATA              32
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_B1_COLUMNS_DATA           0x58
#define XMATRIXMULTIPLICATION_CONTROL_BITS_B1_COLUMNS_DATA           32
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_B2_COLUMNS_DATA           0x60
#define XMATRIXMULTIPLICATION_CONTROL_BITS_B2_COLUMNS_DATA           32
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_COPY_FLAG_OUT_DATA        0x68
#define XMATRIXMULTIPLICATION_CONTROL_BITS_COPY_FLAG_OUT_DATA        1
#define XMATRIXMULTIPLICATION_CONTROL_ADDR_MATRICES_UPDATED_OUT_DATA 0x78
#define XMATRIXMULTIPLICATION_CONTROL_BITS_MATRICES_UPDATED_OUT_DATA 1

#endif
