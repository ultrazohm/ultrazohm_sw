/******************************************************************************
 *
 * adc.h
 *
 * Copyright (C) 2018 Institute ELSYS, TH Nürnberg, All rights reserved.
 *
 *  Created on: 21.08.2016
 *      Author: Sebastian Wendel (SW)
 *
******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "../main.h"


int Initialize_ADC_CONVERSION(void);									// INit for the ADC-conversion IP-Block
int Initialize_TRANS_123_DQ_CONVERSION(DS_Data* data);							// Init Park-transformation 123 to dq

#endif /* ADC_H_ */
