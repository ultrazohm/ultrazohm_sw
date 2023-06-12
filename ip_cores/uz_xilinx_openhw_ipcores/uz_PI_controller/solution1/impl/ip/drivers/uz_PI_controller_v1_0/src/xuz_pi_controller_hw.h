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
// 0x10 : Data signal of axi_referenceValue
//        bit 31~0 - axi_referenceValue[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of axi_sampletime
//        bit 31~0 - axi_sampletime[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of axi_KI
//        bit 31~0 - axi_KI[31:0] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of axi_KP
//        bit 31~0 - axi_KP[31:0] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of axi_limit
//        bit 31~0 - axi_limit[31:0] (Read/Write)
// 0x34 : reserved
// 0x38 : Data signal of axi_reset
//        bit 0  - axi_reset[0] (Read/Write)
//        others - reserved
// 0x3c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_REFERENCEVALUE_DATA 0x10
#define XUZ_PI_CONTROLLER_CONTROL_BITS_AXI_REFERENCEVALUE_DATA 32
#define XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_SAMPLETIME_DATA     0x18
#define XUZ_PI_CONTROLLER_CONTROL_BITS_AXI_SAMPLETIME_DATA     32
#define XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_KI_DATA             0x20
#define XUZ_PI_CONTROLLER_CONTROL_BITS_AXI_KI_DATA             32
#define XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_KP_DATA             0x28
#define XUZ_PI_CONTROLLER_CONTROL_BITS_AXI_KP_DATA             32
#define XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_LIMIT_DATA          0x30
#define XUZ_PI_CONTROLLER_CONTROL_BITS_AXI_LIMIT_DATA          32
#define XUZ_PI_CONTROLLER_CONTROL_ADDR_AXI_RESET_DATA          0x38
#define XUZ_PI_CONTROLLER_CONTROL_BITS_AXI_RESET_DATA          1

