// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of output_volts_d
//        bit 31~0 - output_volts_d[31:0] (Read/Write)
// 0x14 : Data signal of output_volts_d
//        bit 31~0 - output_volts_d[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of output_volts_q
//        bit 31~0 - output_volts_q[31:0] (Read/Write)
// 0x20 : Data signal of output_volts_q
//        bit 31~0 - output_volts_q[63:32] (Read/Write)
// 0x24 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XUZ_FOC_SAMPLE_CONTROL_ADDR_OUTPUT_VOLTS_D_DATA 0x10
#define XUZ_FOC_SAMPLE_CONTROL_BITS_OUTPUT_VOLTS_D_DATA 64
#define XUZ_FOC_SAMPLE_CONTROL_ADDR_OUTPUT_VOLTS_Q_DATA 0x1c
#define XUZ_FOC_SAMPLE_CONTROL_BITS_OUTPUT_VOLTS_Q_DATA 64

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
// 0x10 : Data signal of i_reference_Ampere
//        bit 31~0 - i_reference_Ampere[31:0] (Read/Write)
// 0x14 : Data signal of i_reference_Ampere
//        bit 31~0 - i_reference_Ampere[63:32] (Read/Write)
// 0x18 : Data signal of i_reference_Ampere
//        bit 31~0 - i_reference_Ampere[95:64] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of self_i
//        bit 31~0 - self_i[31:0] (Read/Write)
// 0x24 : Data signal of self_i
//        bit 31~0 - self_i[63:32] (Read/Write)
// 0x28 : Data signal of self_i
//        bit 31~0 - self_i[95:64] (Read/Write)
// 0x2c : Data signal of self_i
//        bit 31~0 - self_i[127:96] (Read/Write)
// 0x30 : Data signal of self_i
//        bit 31~0 - self_i[159:128] (Read/Write)
// 0x34 : Data signal of self_i
//        bit 31~0 - self_i[191:160] (Read/Write)
// 0x38 : Data signal of self_i
//        bit 31~0 - self_i[223:192] (Read/Write)
// 0x3c : Data signal of self_i
//        bit 31~0 - self_i[255:224] (Read/Write)
// 0x40 : reserved
// 0x44 : Data signal of self_o
//        bit 31~0 - self_o[31:0] (Read)
// 0x48 : Data signal of self_o
//        bit 31~0 - self_o[63:32] (Read)
// 0x4c : Data signal of self_o
//        bit 31~0 - self_o[95:64] (Read)
// 0x50 : Data signal of self_o
//        bit 31~0 - self_o[127:96] (Read)
// 0x54 : Data signal of self_o
//        bit 31~0 - self_o[159:128] (Read)
// 0x58 : Data signal of self_o
//        bit 31~0 - self_o[191:160] (Read)
// 0x5c : Data signal of self_o
//        bit 31~0 - self_o[223:192] (Read)
// 0x60 : Data signal of self_o
//        bit 31~0 - self_o[255:224] (Read)
// 0x64 : Control signal of self_o
//        bit 0  - self_o_ap_vld (Read/COR)
//        others - reserved
// 0x70 : Data signal of i_actual_Ampere
//        bit 31~0 - i_actual_Ampere[31:0] (Read/Write)
// 0x74 : Data signal of i_actual_Ampere
//        bit 31~0 - i_actual_Ampere[63:32] (Read/Write)
// 0x78 : Data signal of i_actual_Ampere
//        bit 31~0 - i_actual_Ampere[95:64] (Read/Write)
// 0x7c : reserved
// 0x80 : Data signal of V_dc_volts
//        bit 31~0 - V_dc_volts[31:0] (Read/Write)
// 0x84 : reserved
// 0x88 : Data signal of omega_el_rad_per_sec
//        bit 31~0 - omega_el_rad_per_sec[31:0] (Read/Write)
// 0x8c : reserved
// 0x90 : Data signal of Controller_id
//        bit 31~0 - Controller_id[31:0] (Read/Write)
// 0x94 : Data signal of Controller_id
//        bit 31~0 - Controller_id[63:32] (Read/Write)
// 0x98 : Data signal of Controller_id
//        bit 31~0 - Controller_id[95:64] (Read/Write)
// 0x9c : Data signal of Controller_id
//        bit 31~0 - Controller_id[127:96] (Read/Write)
// 0xa0 : Data signal of Controller_id
//        bit 31~0 - Controller_id[159:128] (Read/Write)
// 0xa4 : reserved
// 0xa8 : Data signal of Controller_iq
//        bit 31~0 - Controller_iq[31:0] (Read/Write)
// 0xac : Data signal of Controller_iq
//        bit 31~0 - Controller_iq[63:32] (Read/Write)
// 0xb0 : Data signal of Controller_iq
//        bit 31~0 - Controller_iq[95:64] (Read/Write)
// 0xb4 : Data signal of Controller_iq
//        bit 31~0 - Controller_iq[127:96] (Read/Write)
// 0xb8 : Data signal of Controller_iq
//        bit 31~0 - Controller_iq[159:128] (Read/Write)
// 0xbc : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XUZ_FOC_SAMPLE_DIN_ADDR_AP_CTRL                   0x00
#define XUZ_FOC_SAMPLE_DIN_ADDR_GIE                       0x04
#define XUZ_FOC_SAMPLE_DIN_ADDR_IER                       0x08
#define XUZ_FOC_SAMPLE_DIN_ADDR_ISR                       0x0c
#define XUZ_FOC_SAMPLE_DIN_ADDR_I_REFERENCE_AMPERE_DATA   0x10
#define XUZ_FOC_SAMPLE_DIN_BITS_I_REFERENCE_AMPERE_DATA   96
#define XUZ_FOC_SAMPLE_DIN_ADDR_SELF_I_DATA               0x20
#define XUZ_FOC_SAMPLE_DIN_BITS_SELF_I_DATA               256
#define XUZ_FOC_SAMPLE_DIN_ADDR_SELF_O_DATA               0x44
#define XUZ_FOC_SAMPLE_DIN_BITS_SELF_O_DATA               256
#define XUZ_FOC_SAMPLE_DIN_ADDR_SELF_O_CTRL               0x64
#define XUZ_FOC_SAMPLE_DIN_ADDR_I_ACTUAL_AMPERE_DATA      0x70
#define XUZ_FOC_SAMPLE_DIN_BITS_I_ACTUAL_AMPERE_DATA      96
#define XUZ_FOC_SAMPLE_DIN_ADDR_V_DC_VOLTS_DATA           0x80
#define XUZ_FOC_SAMPLE_DIN_BITS_V_DC_VOLTS_DATA           32
#define XUZ_FOC_SAMPLE_DIN_ADDR_OMEGA_EL_RAD_PER_SEC_DATA 0x88
#define XUZ_FOC_SAMPLE_DIN_BITS_OMEGA_EL_RAD_PER_SEC_DATA 32
#define XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_ID_DATA        0x90
#define XUZ_FOC_SAMPLE_DIN_BITS_CONTROLLER_ID_DATA        160
#define XUZ_FOC_SAMPLE_DIN_ADDR_CONTROLLER_IQ_DATA        0xa8
#define XUZ_FOC_SAMPLE_DIN_BITS_CONTROLLER_IQ_DATA        160

