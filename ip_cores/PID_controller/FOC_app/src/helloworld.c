/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* cofoces of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all cofoces or substantial portions of the Software.
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
#include "uz_foc.h"

// Define global values for HLS example IP
XUz_foc_sample foc;
XUz_foc_sample_Config *foc_cfg;

// Initialize the HLS example IP
void init_foc(){

		int status;
		// Create HLS example IP pointer
		foc_cfg = XUz_foc_sample_LookupConfig(
				XPAR_UZ_FOC_SAMPLE_0_DEVICE_ID);

		if (!foc_cfg) {
			xil_printf(
					"Error loading configuration for foc_cfg \n\r");
		}

		status = XUz_foc_sample_CfgInitialize(&foc,
				foc_cfg);
		if (status != XST_SUCCESS) {
			xil_printf("Error initializing for foc \n\r");
		}

		XUz_foc_sample_Initialize(&foc,
				XPAR_UZ_FOC_SAMPLE_0_DEVICE_ID);
}
void foc_hls(float values_id, float values_iq , float omega_el_rad_per_sec){
	XUz_foc_sample_I_actual_ampere i_actual_Ampere;
	i_actual_Ampere.word_0 = *((u32*)&values_id);
	i_actual_Ampere.word_1 = *((u32*)&values_iq);
	i_actual_Ampere.word_2 = 0;
	// Write inputs
	XUz_foc_sample_Set_i_actual_Ampere(&foc, i_actual_Ampere);
	XUz_foc_sample_Set_omega_el_rad_per_sec(&foc,*((u32*)&omega_el_rad_per_sec));

	// Start HLS IP
	XUz_foc_sample_Start(&foc);

	// Wait until it is finished
	while (!XUz_foc_sample_IsDone(&foc))
		;
}

int main() {
	// setup
	init_platform();
	init_foc();
	XUz_foc_sample_Self_i self = {0};
	//XUz_foc_sample_I_actual_ampere i_actual_Ampere = {0};
	XUz_foc_sample_I_reference_ampere i_reference_Ampere = {0};
	XUz_foc_sample_Controller_id Controller_id = {0};
	XUz_foc_sample_Controller_iq Controller_iq = {0};

	self.word_0 = 1; // Decoupling select
	self.word_1 = 0; // I_rst
	self.word_2 = 0; //ext_clamping
	self.word_4 = *((u32*)&values[0]);//0.00027f;
	self.word_5 = *((u32*)&values[1]);//0.00027f;
	self.word_6 = *((u32*)&values[2]);//0.0082f;
	self.word_7 = *((u32*)&values[2]);
	//i_actual_Ampere.word_0 =*((u32*)&values[3]);// 0.0f;
	//i_actual_Ampere.word_1 = *((u32*)&values[4]);//0.0f;
	//i_actual_Ampere.word_2 =*((u32*)&values[5]); //0.0f;
	i_reference_Ampere.word_0 =*((u32*)&values[6]);// 1.0f;
	i_reference_Ampere.word_1 = *((u32*)&values[7]);//1.0f;
	i_reference_Ampere.word_2 = *((u32*)&values[8]);//0.0f;
	Controller_id.word_0 = *((u32*)&values[9]);//6.75f;
	Controller_id.word_1 = *((u32*)&values[10]);//2000.0f;
	Controller_id.word_2 = *((u32*)&values[11]);//0.00001f;
	Controller_id.word_3 = *((u32*)&values[12]);//10.0f;
	Controller_id.word_4 = *((u32*)&values[13]);//-10.0f;
	Controller_iq.word_0 = *((u32*)&values[14]);//6.75f;
	Controller_iq.word_1 = *((u32*)&values[15]);//2000.0f;
	Controller_iq.word_2 = *((u32*)&values[16]);//0.00001f;
	Controller_iq.word_3 = *((u32*)&values[17]);//10.0f;
	Controller_iq.word_4 = *((u32*)&values[18]);//-10.0f;

	XUz_foc_sample_Set_self_i(&foc, self );
	XUz_foc_sample_Set_Controller_id(&foc, Controller_id );
	XUz_foc_sample_Set_Controller_iq(&foc, Controller_iq );
	XUz_foc_sample_Set_i_reference_Ampere(&foc, i_reference_Ampere);

	float *result_d = (float*)D_mem;
	float *result_q = (float*)Q_mem;

	XUz_foc_sample_Set_V_dc_volts(&foc, *((u32*)&V_dc_volts));
	print("The code is executed\n\r ");
	for(int i=0;i<11;i++){
		result_d[i]= 0;
		result_q[i]= 0;
		}

	Xil_DCacheFlushRange(0x10000000, 0x100);

	for(int j=0;j<11;j++){
	// perform foc controller in HLS IP
		XUz_foc_sample_Set_output_volts_d(&foc, D_mem);
		XUz_foc_sample_Set_output_volts_q(&foc, Q_mem);
		foc_hls(values_id[j],values_iq[j],values_omega[j]);
		D_mem = D_mem +4;
		Q_mem = Q_mem +4;
	}
	print("D Values\n\r ");
	for(int k=0;k<11;k++){
		printf("result = %f \n", result_d[k]);
		if(ud_out[k]-result_d[k] == 0.0f){
			print("Equal- pass \n");
		}
		else if (ud_out[k]-result_d[k]< .000000001){
			print("In range-pass \n");
		}
		else{
			printf("Not acceptable - fail %f \n",ud_out[k]-result_d[k] );
		}
	}
	print("\n Q Values \n ");
	for(int l=0;l<11;l++){
		printf("result = %f \n", result_q[l]);
		if(uq_out[l]-result_q[l] == 0.0f){
			print("Equal- pass \n");
		}
		else if (uq_out[l]-result_q[l]< .1){
			print("In range-pass \n");
		}
		else{
			printf("Not acceptable - fail %f \n",uq_out[l]-result_q[l]);
		}
	}
	print("\n end\n ");
	cleanup_platform();
	return 0;
}


