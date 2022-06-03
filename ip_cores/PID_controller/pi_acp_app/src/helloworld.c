/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/


#include "platform.h"
#include "xbasic_types.h"
#include "xparameters.h" // Contains definitions for all peripherals
#include "xuz_pi_controller_sample.h" // Contains hls example (axilite) IP macros and functions
#include "stdbool.h"
#include "stdio.h"
#include "xil_mmu.h"
#include "xil_cache.h"
#include <math.h>

//Xil_SetTlbAttributes(0xFFFF0000,0x401UL);
// Define global values for HLS example IP
XUz_pi_controller_sample pi;
XUz_pi_controller_sample_Config *pi_cfg;

//Beginning of DDR Memory(MIG)
#define MEM_BASE_ADDR 0x800000000
#define TX_BASE_ADDR  0x10000000//0x801000000//(MEM_BASE_ADDR + 0x00000100)

float *result = (float*)TX_BASE_ADDR;

// Initialize the HLS example IP
void init_pi_controller(){

		int status;
		// Create HLS example IP pointer
		pi_cfg = XUz_pi_controller_sample_LookupConfig(
		XPAR_UZ_PI_CONTROLLER_SAM_0_DEVICE_ID);

		if (!pi_cfg) {
			xil_printf(
					"Error loading configuration for pi_cfg \n\r");
		}

		status = XUz_pi_controller_sample_CfgInitialize(&pi,
				pi_cfg);
		if (status != XST_SUCCESS) {
			xil_printf("Error initializing for pi \n\r");
		}

		XUz_pi_controller_sample_Initialize(&pi,
		XPAR_UZ_PI_CONTROLLER_SAM_0_DEVICE_ID);
}

void pi_controller_hls(XUz_pi_controller_sample_Self self,  bool I_rst, float referenceValue, float actualValue, bool ext_clamping) {
	float output;
    output = 0.0f; // result output from HLS IP
    u64 op;

	// Write inputs
	XUz_pi_controller_sample_Set_self(&pi, self );
	XUz_pi_controller_sample_Set_I_rst(&pi, *((u32*)&I_rst) );
	XUz_pi_controller_sample_Set_referenceValue(&pi, *((u32*)&referenceValue));
	XUz_pi_controller_sample_Set_actualValue(&pi, *((u32*)&actualValue));
	XUz_pi_controller_sample_Set_ext_clamping(&pi, *((u32*)&ext_clamping));

	// Start HLS IP
	XUz_pi_controller_sample_Start(&pi);
	//print("Started HLS pi controller IP \n");

	// Wait until it is finished
	while (!XUz_pi_controller_sample_IsDone(&pi))
		;

	// Get hls returned value
	op = XUz_pi_controller_sample_Get_output_r(&pi);
	output = *((float*)&op);
	printf("output = %f \n", output);
}

int main() {
	// setup
	init_platform();
	init_pi_controller();
	XUz_pi_controller_sample_Self self;
	int I_rst_int = 0;
	bool I_rst;
	float Kp = 1.154f;
	float Ki = 1.0f;
    float samplingTime_sec = 1.0f;
	float upper_limit = 20.0f;
	float lower_limit = -20.0f;
	float referenceValue[13] = {2.54f, 5.0f, -1.45f, -1.23f, 5.54f, 10.32f, -9.45f, -15.23f, 2.0f, 1.0f, 12.0f, 12.0f, 2.0f};
	float actualValue[13]    = {1.62f, 6.5f, -3.25f, 2.54f, 1.62f, 6.5f, -3.25f, 2.54f, 1.0f, 2.0f, 2.0f, 12.1f, 12.0f};
	int ext_clamping_int = 0;
	bool ext_clamping;
	I_rst = I_rst_int;
	ext_clamping = ext_clamping_int;
	float test[13] = { 1.061680f,-0.811000f,1.497200f, -3.130580f, 1.973680f, 5.778280f,-1.964800f,-20.000000f, 0.144000f,-1.164000f,10.530001f,8.874599f,-2.650002f};

    self.word_0 = *((u32*)&Kp);
    self.word_1 = *((u32*)&Ki);
    self.word_2 = *((u32*)&samplingTime_sec);
    self.word_3 = *((u32*)&upper_limit);
    self.word_4 = *((u32*)&lower_limit);
	print("The code is executed\n\r ");
    long int mem = 0x10000000;
    long int addr[13] = {mem,mem+4,mem+8,mem+12,mem+16,mem+20,mem+24,mem+28,mem+32,mem+36,mem+40,mem+44,mem+48};

	for(int i=0;i<13;i++){
		result[i]= 0;
		}
	//XUz_pi_controller_sample_Set_output_r(&pi, mem);
	for(int j=0;j<13;j++){
	// perform pi controller in HLS IP
		XUz_pi_controller_sample_Set_output_r(&pi, addr[j]);
	pi_controller_hls(self,I_rst,referenceValue[j],actualValue[j],ext_clamping);
	}

	 Xil_DCacheFlushRange(TX_BASE_ADDR, 0x100);

	for(int k=0;k<13;k++){
			printf("result = %f \n", result[k]);
			if(test[k]-result[k] == 0.0f){
				print("Equal- pass \n");
			}
			else if (test[k]-result[k]< .000000001){
				print("In range-pass \n");
			}
			else{
				printf("Not acceptable - fail %f \n",test[k]-result[k] );
			}
		}

	print("\n end\n ");
	cleanup_platform();
	return 0;
}


