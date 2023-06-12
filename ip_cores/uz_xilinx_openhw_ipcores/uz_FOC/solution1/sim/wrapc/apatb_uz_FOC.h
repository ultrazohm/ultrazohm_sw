// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================

extern "C" void AESL_WRAP_uz_FOC (
float axi_id_reference,
float axi_iq_reference,
float axi_sampletime,
float axi_id_KI,
float axi_id_KP,
float axi_iq_KI,
float axi_iq_KP,
float axi_limit,
char axi_reset,
float id_actual,
float iq_actual,
char reset_PL,
volatile void* ud_ref,
volatile void* uq_ref);
