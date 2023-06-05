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
// 0x10 : Data signal of referenceValue
//        bit 31~0 - referenceValue[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of sampletime
//        bit 31~0 - sampletime[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of KI
//        bit 31~0 - KI[31:0] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of KP
//        bit 31~0 - KP[31:0] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of limit
//        bit 31~0 - limit[31:0] (Read/Write)
// 0x34 : reserved
// 0x38 : Data signal of reset
//        bit 0  - reset[0] (Read/Write)
//        others - reserved
// 0x3c : reserved
// 0x40 : Data signal of axi_referenceValue
//        bit 31~0 - axi_referenceValue[31:0] (Read)
// 0x44 : Control signal of axi_referenceValue
//        bit 0  - axi_referenceValue_ap_vld (Read/COR)
//        others - reserved
// 0x50 : Data signal of axi_actualValue
//        bit 31~0 - axi_actualValue[31:0] (Read)
// 0x54 : Control signal of axi_actualValue
//        bit 0  - axi_actualValue_ap_vld (Read/COR)
//        others - reserved
// 0x60 : Data signal of error
//        bit 31~0 - error[31:0] (Read)
// 0x64 : Control signal of error
//        bit 0  - error_ap_vld (Read/COR)
//        others - reserved
// 0x70 : Data signal of P_sum
//        bit 31~0 - P_sum[31:0] (Read)
// 0x74 : Control signal of P_sum
//        bit 0  - P_sum_ap_vld (Read/COR)
//        others - reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XUZ_PI_CONTROLLER_CONTROL_ADDR_REFERENCEVALUE_DATA     0x10
#define XUZ_PI_CONTROLLER_CONTROL_BITS_REFERENCEVALUE_DATA     32
#define XUZ_PI_CONTROLLER_CONTROL_ADDR_SAMPLETIME_DATA         0x18
#define XUZ_PI_CONTROLLER_CONTROL_BITS_SAMPLETIME_DATA         32
#define XUZ_PI_CONTROLLER_CONTROL_ADDR_KI_DATA                 0x20
#define XUZ_PI_CONTROLLER_CONTROL_BITS_KI_DATA                 32
#define XUZ_PI_CONTROLLER_CONTROL_ADDR_KP_DATA                 0x28
#define XUZ_PI_CONTROLLER_CONTROL_BITS_KP_DATA                 32
#define XUZ_PI_CONTROLLER_CONTROL_ADDR_LIMIT_DATA              0x30
#define XUZ_PI_CONTROLLER_CONTROL_BITS_LIMIT_DATA              32
#define XUZ_PI_CONTROLLER_CONTROL_ADDR_RESET_DATA              0x38
#define XUZ_PI_CONTROLLER_CONTROL_BITS_RESET_DATA              1
#define XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_REFERENCEVALUE_DATA 0x40
#define XUZ_PI_CONTROLLER_CONTROL_BITS_AXI_REFERENCEVALUE_DATA 32
#define XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_REFERENCEVALUE_CTRL 0x44
#define XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_ACTUALVALUE_DATA    0x50
#define XUZ_PI_CONTROLLER_CONTROL_BITS_AXI_ACTUALVALUE_DATA    32
#define XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_ACTUALVALUE_CTRL    0x54
#define XUZ_PI_CONTROLLER_CONTROL_ADDR_ERROR_DATA              0x60
#define XUZ_PI_CONTROLLER_CONTROL_BITS_ERROR_DATA              32
#define XUZ_PI_CONTROLLER_CONTROL_ADDR_ERROR_CTRL              0x64
#define XUZ_PI_CONTROLLER_CONTROL_ADDR_P_SUM_DATA              0x70
#define XUZ_PI_CONTROLLER_CONTROL_BITS_P_SUM_DATA              32
#define XUZ_PI_CONTROLLER_CONTROL_ADDR_P_SUM_CTRL              0x74

