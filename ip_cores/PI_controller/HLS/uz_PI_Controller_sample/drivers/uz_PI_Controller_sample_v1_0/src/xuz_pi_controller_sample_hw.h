// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of output_r
//        bit 31~0 - output_r[31:0] (Read/Write)
// 0x14 : Data signal of output_r
//        bit 31~0 - output_r[63:32] (Read/Write)
// 0x18 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XUZ_PI_CONTROLLER_SAMPLE_CONTROL_ADDR_OUTPUT_R_DATA 0x10
#define XUZ_PI_CONTROLLER_SAMPLE_CONTROL_BITS_OUTPUT_R_DATA 64

// Din
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
// 0x10 : Data signal of self
//        bit 31~0 - self[31:0] (Read/Write)
// 0x14 : Data signal of self
//        bit 31~0 - self[63:32] (Read/Write)
// 0x18 : Data signal of self
//        bit 31~0 - self[95:64] (Read/Write)
// 0x1c : Data signal of self
//        bit 31~0 - self[127:96] (Read/Write)
// 0x20 : Data signal of self
//        bit 31~0 - self[159:128] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of I_rst
//        bit 31~0 - I_rst[31:0] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of referenceValue
//        bit 31~0 - referenceValue[31:0] (Read/Write)
// 0x34 : reserved
// 0x38 : Data signal of actualValue
//        bit 31~0 - actualValue[31:0] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of ext_clamping
//        bit 31~0 - ext_clamping[31:0] (Read/Write)
// 0x44 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_AP_CTRL             0x00
#define XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_GIE                 0x04
#define XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_IER                 0x08
#define XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_ISR                 0x0c
#define XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_SELF_DATA           0x10
#define XUZ_PI_CONTROLLER_SAMPLE_DIN_BITS_SELF_DATA           160
#define XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_I_RST_DATA          0x28
#define XUZ_PI_CONTROLLER_SAMPLE_DIN_BITS_I_RST_DATA          32
#define XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_REFERENCEVALUE_DATA 0x30
#define XUZ_PI_CONTROLLER_SAMPLE_DIN_BITS_REFERENCEVALUE_DATA 32
#define XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_ACTUALVALUE_DATA    0x38
#define XUZ_PI_CONTROLLER_SAMPLE_DIN_BITS_ACTUALVALUE_DATA    32
#define XUZ_PI_CONTROLLER_SAMPLE_DIN_ADDR_EXT_CLAMPING_DATA   0x40
#define XUZ_PI_CONTROLLER_SAMPLE_DIN_BITS_EXT_CLAMPING_DATA   32

