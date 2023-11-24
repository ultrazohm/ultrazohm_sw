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
// 0x10 : Data signal of A_input
//        bit 31~0 - A_input[31:0] (Read/Write)
// 0x14 : Data signal of A_input
//        bit 31~0 - A_input[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of B_input
//        bit 31~0 - B_input[31:0] (Read/Write)
// 0x20 : Data signal of B_input
//        bit 31~0 - B_input[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of C_output
//        bit 31~0 - C_output[31:0] (Read/Write)
// 0x2c : Data signal of C_output
//        bit 31~0 - C_output[63:32] (Read/Write)
// 0x30 : reserved
// 0x34 : Data signal of A_rows
//        bit 31~0 - A_rows[31:0] (Read/Write)
// 0x38 : Data signal of A_rows
//        bit 31~0 - A_rows[63:32] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of B_rows
//        bit 31~0 - B_rows[31:0] (Read/Write)
// 0x44 : Data signal of B_rows
//        bit 31~0 - B_rows[63:32] (Read/Write)
// 0x48 : reserved
// 0x4c : Data signal of B_columns
//        bit 31~0 - B_columns[31:0] (Read/Write)
// 0x50 : Data signal of B_columns
//        bit 31~0 - B_columns[63:32] (Read/Write)
// 0x54 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define CONTROL_ADDR_AP_CTRL        0x00
#define CONTROL_ADDR_GIE            0x04
#define CONTROL_ADDR_IER            0x08
#define CONTROL_ADDR_ISR            0x0c
#define CONTROL_ADDR_A_INPUT_DATA   0x10
#define CONTROL_BITS_A_INPUT_DATA   64
#define CONTROL_ADDR_B_INPUT_DATA   0x1c
#define CONTROL_BITS_B_INPUT_DATA   64
#define CONTROL_ADDR_C_OUTPUT_DATA  0x28
#define CONTROL_BITS_C_OUTPUT_DATA  64
#define CONTROL_ADDR_A_ROWS_DATA    0x34
#define CONTROL_BITS_A_ROWS_DATA    64
#define CONTROL_ADDR_B_ROWS_DATA    0x40
#define CONTROL_BITS_B_ROWS_DATA    64
#define CONTROL_ADDR_B_COLUMNS_DATA 0x4c
#define CONTROL_BITS_B_COLUMNS_DATA 64
