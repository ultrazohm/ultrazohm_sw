/******************************************************************************
 *
 * load_testvector.cpp
 *
 * Copyright (C) 2020 Institute EAL, TU München, All rights reserved.
 *
 *  Created on: 12.05.2020
 *      Author: Eyke Liegmann (EL)
 *
******************************************************************************/

#include "../include/pred_ctrl_sw_N1.h"


void load_plant_model(plant_str* plant_model)
{
	#include "plant_model_from_matlab.h"

	// plant model
	memcpy(plant_model->A_mat, A_mat, sizeof(A_mat));
	memcpy(plant_model->B_mat, B_mat, sizeof(B_mat));

}

