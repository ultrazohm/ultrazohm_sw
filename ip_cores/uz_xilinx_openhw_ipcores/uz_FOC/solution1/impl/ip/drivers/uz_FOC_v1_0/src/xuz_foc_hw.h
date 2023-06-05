// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of sampletime
//        bit 31~0 - sampletime[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of set_i_d
//        bit 31~0 - set_i_d[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of set_i_q
//        bit 31~0 - set_i_q[31:0] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of KP_d
//        bit 31~0 - KP_d[31:0] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of KI_d
//        bit 31~0 - KI_d[31:0] (Read/Write)
// 0x34 : reserved
// 0x38 : Data signal of KP_q
//        bit 31~0 - KP_q[31:0] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of KI_q
//        bit 31~0 - KI_q[31:0] (Read/Write)
// 0x44 : reserved
// 0x48 : Data signal of reset_PS
//        bit 0  - reset_PS[0] (Read/Write)
//        others - reserved
// 0x4c : reserved
// 0x50 : Data signal of limit
//        bit 31~0 - limit[31:0] (Read/Write)
// 0x54 : reserved
// 0x58 : Data signal of out_KP_d
//        bit 31~0 - out_KP_d[31:0] (Read)
// 0x5c : Control signal of out_KP_d
//        bit 0  - out_KP_d_ap_vld (Read/COR)
//        others - reserved
// 0x68 : Data signal of out_idref
//        bit 31~0 - out_idref[31:0] (Read)
// 0x6c : Control signal of out_idref
//        bit 0  - out_idref_ap_vld (Read/COR)
//        others - reserved
// 0x78 : Data signal of out_status
//        bit 0  - out_status[0] (Read)
//        others - reserved
// 0x7c : Control signal of out_status
//        bit 0  - out_status_ap_vld (Read/COR)
//        others - reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XUZ_FOC_CONTROL_ADDR_SAMPLETIME_DATA 0x10
#define XUZ_FOC_CONTROL_BITS_SAMPLETIME_DATA 32
#define XUZ_FOC_CONTROL_ADDR_SET_I_D_DATA    0x18
#define XUZ_FOC_CONTROL_BITS_SET_I_D_DATA    32
#define XUZ_FOC_CONTROL_ADDR_SET_I_Q_DATA    0x20
#define XUZ_FOC_CONTROL_BITS_SET_I_Q_DATA    32
#define XUZ_FOC_CONTROL_ADDR_KP_D_DATA       0x28
#define XUZ_FOC_CONTROL_BITS_KP_D_DATA       32
#define XUZ_FOC_CONTROL_ADDR_KI_D_DATA       0x30
#define XUZ_FOC_CONTROL_BITS_KI_D_DATA       32
#define XUZ_FOC_CONTROL_ADDR_KP_Q_DATA       0x38
#define XUZ_FOC_CONTROL_BITS_KP_Q_DATA       32
#define XUZ_FOC_CONTROL_ADDR_KI_Q_DATA       0x40
#define XUZ_FOC_CONTROL_BITS_KI_Q_DATA       32
#define XUZ_FOC_CONTROL_ADDR_RESET_PS_DATA   0x48
#define XUZ_FOC_CONTROL_BITS_RESET_PS_DATA   1
#define XUZ_FOC_CONTROL_ADDR_LIMIT_DATA      0x50
#define XUZ_FOC_CONTROL_BITS_LIMIT_DATA      32
#define XUZ_FOC_CONTROL_ADDR_OUT_KP_D_DATA   0x58
#define XUZ_FOC_CONTROL_BITS_OUT_KP_D_DATA   32
#define XUZ_FOC_CONTROL_ADDR_OUT_KP_D_CTRL   0x5c
#define XUZ_FOC_CONTROL_ADDR_OUT_IDREF_DATA  0x68
#define XUZ_FOC_CONTROL_BITS_OUT_IDREF_DATA  32
#define XUZ_FOC_CONTROL_ADDR_OUT_IDREF_CTRL  0x6c
#define XUZ_FOC_CONTROL_ADDR_OUT_STATUS_DATA 0x78
#define XUZ_FOC_CONTROL_BITS_OUT_STATUS_DATA 1
#define XUZ_FOC_CONTROL_ADDR_OUT_STATUS_CTRL 0x7c

