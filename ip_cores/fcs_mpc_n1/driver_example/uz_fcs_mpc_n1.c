/******************************************************************************
 *
 * pred_ctrl_sw.c
 *
 * Copyright (C) 2020 Institute EAL, TU München, All rights reserved.
 *
 *  Created on: 29.04.2020
 *      Author: Eyke Liegmann (EL)
 *
 ******************************************************************************/
#include "../include/pred_ctrl_sw_N1.h"
#include "xbasic_types.h"

// todo: replace these function with the uz versions
static u32 double_to_u32(double value);
static u32 float_to_u32(float value);

int pred_ctrl_N1_intialize(plant_str *plant, float lambda_u)
{
	// Look Up the device configuration
	HLS_predictive_ctrl_N1_config = XCtrl_wrapper_LookupConfig(XPAR_CTRL_PRED_CTRL_0_DEVICE_ID);

	if(!HLS_predictive_ctrl_N1_config){
		xil_printf("ERROR: Lookup of predictive_controller configuration failed.\n\r");
		return XST_FAILURE;
	}

	// Initialize the Device
	int status = XCtrl_wrapper_CfgInitialize(&HLS_predictive_ctrl_N1, HLS_predictive_ctrl_N1_config);
	if (status != XST_SUCCESS) {
		print("ERROR: Could not initialize predictive_controller.\n\r");
		return(-1);
	}

	pred_ctrl_N1_update_matrices(plant);

	// set lambda_u
	pred_ctrl_N1_set_lambda_u((float)lambda_u);

	// copy flag
	XCtrl_wrapper_Set_copy_mats_flag(&HLS_predictive_ctrl_N1, 0); //1=true

	//Enable global interrupt
	XCtrl_wrapper_InterruptGlobalEnable(&HLS_predictive_ctrl_N1);

	//Enable ap_done interrupt - bit 0: ap_done, bit 1: ap_ready
	XCtrl_wrapper_InterruptEnable(&HLS_predictive_ctrl_N1, 0b1);

	//Start of predictive controller
	auto_start_pred_ctrl_N1();

	xil_printf("FCS MPC N=1 Module initialized\n\r");

	return status;
}

void pred_ctrl_N1_update_matrices(plant_str *plant){
	//Set the input parameters of the HLS block
	u32 temp_data;
	int offsetA, offsetB;
	// A_matrix
	for(int col= 0; col<4; col++)
	{
		for(int row = 0; row<4; row++)
		{
			temp_data = double_to_u32(plant->A_mat[row][col]);

			//offsetA = (col*4 + row); //row-major
			offsetA = (col   + row*4); //column-major

			XCtrl_wrapper_Write_plant_A_mat_Words(&HLS_predictive_ctrl_N1, offsetA, &temp_data, 1);
		}
	}

	// B_matrix
	for(int col= 0; col<3; col++)
	{
		for(int row = 0; row<4; row++)
		{
         temp_data = double_to_u32(plant->B_mat[row][col]);

//			offsetB = (col*4+row); //row-major
			offsetB = (col  +row*3); //column-major
			XCtrl_wrapper_Write_plant_B_mat_Words(&HLS_predictive_ctrl_N1, offsetB, &temp_data, 1);
		}
	}
}

void pred_ctrl_N1_set_copy_flag(u32 copy_flag){
	XCtrl_wrapper_Set_copy_mats_flag(&HLS_predictive_ctrl_N1, copy_flag );
}

void pred_ctrl_N1_set_lambda_u(float lambda_u){
	XCtrl_wrapper_Set_lambda_u_in(&HLS_predictive_ctrl_N1, float_to_u32(lambda_u) );
	pred_ctrl_N1_set_copy_flag(1);
}

void auto_start_pred_ctrl_N1()
{

	//Enable auto start
	XCtrl_wrapper_EnableAutoRestart(&HLS_predictive_ctrl_N1);

	//Start of predictive controller
	XCtrl_wrapper_Start(&HLS_predictive_ctrl_N1);

	printf("FCS MPC N=1 auto-start initiated.\n");
}

void pred_ctrl_N1_read_Uopt(int Uopt[3]){
	XCtrl_wrapper_Read_U_OPT_out_Words(&HLS_predictive_ctrl_N1, 0, Uopt, 3);
}

void pred_ctrl_N1_autostart_disable(){
	XCtrl_wrapper_DisableAutoRestart(&HLS_predictive_ctrl_N1);
}



u32 double_to_u32(double value)
{
	u32 result;
	union float_bytes{
		float fl;
		u32 U;
	} data;

	data.fl=(float)value;
	result=data.U;

	return result;
}


u32 float_to_u32(float value)
{
	u32 result;
	union float_bytes{
		float fl;
		u32 U;
	} data;

	data.fl=value;
	result=data.U;

	return result;
}