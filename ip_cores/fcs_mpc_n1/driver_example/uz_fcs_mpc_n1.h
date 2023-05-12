/******************************************************************************
 *
 * pred_ctrl_sw.h
 *
 * Copyright (C) 2020 Institute EAL, TU München, All rights reserved.
 *
 *  Created on: 29.04.2020
 *      Author: Eyke Liegmann (EL)
 *
******************************************************************************/


#pragma once

#include "xctrl_wrapper.h"
#include "xparameters.h"
#include <stdio.h>

XCtrl_wrapper 				HLS_predictive_ctrl_N1;
XCtrl_wrapper_Config 	*HLS_predictive_ctrl_N1_config;


typedef struct
{
	double A_mat[4][4];
	double B_mat[4][3];
} plant_str;


int pred_ctrl_N1_intialize(plant_str *plant, float lambda_u);
void auto_start_pred_ctrl_N1();

void pred_ctrl_N1_update_matrices(plant_str *plant);

void pred_ctrl_N1_set_lambda_u(float lambda_u);
void pred_ctrl_N1_read_Uopt(int Uopt[3]);
void pred_ctrl_N1_set_copy_flag(u32 copy_flag);
void pred_ctrl_N1_autostart_disable();

void load_plant_model(plant_str* plant_model);
