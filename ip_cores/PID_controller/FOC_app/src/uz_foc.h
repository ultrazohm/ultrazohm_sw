#include "platform.h"
#include "xbasic_types.h"
#include "xparameters.h" // Contains definitions for all peripherals
#include "xuz_foc_sample.h" // Contains hls example (axilite) IP macros and functions
#include "stdbool.h"
#include "stdio.h"
#include "xil_cache.h"
#include <math.h>

u64 D_mem = 0x10000000;
u64 Q_mem = 0x10000050;
float values[19]= {0.00027f,0.00027f,0.0082f,0.0f,0.0f,0.0f,1.0f,1.0f,0.0f,6.75f,2000.0f,0.00001f,10.0f,-10.0f,6.75f,2000.0f,0.00001f,10.0f,-10.0f};
float V_dc_volts = 24.0f;
float values_iq[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.76f, 0.819f, 0.863f, 0.895f, 0.919f, 0.937f};
float values_id[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.761f, 0.82f, 0.865f, 0.899f, 0.924f, 0.943f};
float values_omega[11]={0.0f, 0.0f, 0.0178f, 0.0876f, 0.264f, 0.622f, 1.26f, 2.29f, 3.85f, 6.08f, 9.13f};
//Reference results
float ud_out[11]={6.750000,5.089250,3.842018,2.901536,2.201211,1.674242,1.280621,0.980216,0.753020,0.585711,0.458180};
float uq_out[11]={6.750000,5.089250,3.842168,2.902282,2.203474,1.686348,1.298281,1.013603,0.813535,0.672503,0.578441};
