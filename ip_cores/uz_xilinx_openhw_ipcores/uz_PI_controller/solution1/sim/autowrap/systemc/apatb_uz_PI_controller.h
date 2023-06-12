// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================

extern "C" float AESL_WRAP_uz_PI_controller (
float referenceValue,
float actualValue,
float sampletime,
float KI,
float KP,
float limit,
char reset,
volatile void* axi_referenceValue,
volatile void* axi_actualValue,
volatile void* error,
volatile void* P_sum);
