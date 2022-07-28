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


#include "uz_pi_controller.h"

// Define global values for HLS example IP
XUz_pi_controller_sample pi;
XUz_pi_controller_sample_Config *pi_cfg;

// Initialize the HLS example IP
void init_pi_controller(){

		int status;
		// Create HLS pi controller IP pointer
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

void pi_controller_hls(float referenceValue, float actualValue) {
	// Write inputs
	XUz_pi_controller_sample_Set_referenceValue(&pi, *((u32*)&referenceValue));
	XUz_pi_controller_sample_Set_actualValue(&pi, *((u32*)&actualValue));

	// Start HLS IP
	XUz_pi_controller_sample_Start(&pi);

	// Wait until it is finished
	while (!XUz_pi_controller_sample_IsDone(&pi))
		;
}

int main() {
	// setup
	init_platform();
	init_pi_controller();

    self.word_0 = *((u32*)&Kp);
    self.word_1 = *((u32*)&Ki);
    self.word_2 = *((u32*)&samplingTime_sec);
    self.word_3 = *((u32*)&upper_limit);
    self.word_4 = *((u32*)&lower_limit);

	print("The code is executed\n ");
	float mem[NO_ELEMENTS];
	float *result;
	result = mem;
	//u64 loc;
	XUz_pi_controller_sample_Set_self(&pi, self );
	XUz_pi_controller_sample_Set_I_rst(&pi, *((u32*)&I_rst) );
	XUz_pi_controller_sample_Set_ext_clamping(&pi, *((u32*)&ext_clamping));
	/*for(int i=0;i<NO_ELEMENTS;i++){
		printf("Result address[%d]:  %p\n",i, result );
		result[i]= 0;
		result = result+1;
		}
	result = mem;*/
	//loc = (u64)result;
	printf("Memory address before cache flush:  %lx\n", (u64)result );
	// flushes cache content into the ddr memory
		Xil_DCacheFlushRange((u64)result, (sizeof(mem)*NO_ELEMENTS));
	for(int j=0;j<NO_ELEMENTS;j++){
		//loc = (u64)result;
		printf("Memory address before calling code:  %lx\n", (u64)result );
		XUz_pi_controller_sample_Set_output_r(&pi,(u64)result);
		printf("result = %f \n", result[j]);
		pi_controller_hls(referenceValue[j],actualValue[j]);
		result = result+1;
	}
	//result = mem;
	/*for(int k=0;k<NO_ELEMENTS;k++){
			printf("result = %f \n", result[k]);
			printf("Memory address before calling code:  %lx\n", (u64)result );
			if(test[k]-result[k] == 0.0f){
				print("Equal- pass \n");
			}
			else if (test[k]-result[k]< 0.01){
				print("In range-pass \n");
			}
			else{
				printf("Not acceptable - fail %f \n",test[k]-result[k] );
			}
			//result = result+1;
		}*/

	print("\n end\n ");
	cleanup_platform();
	return 0;
}


