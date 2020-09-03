/******************************************************************************
*
* pwm.c
*
* Copyright (C) 2019 UltraZohm Community, All rights reserved.
*
*  Created on: 21.10.2018
*      Author: Sebastian Wendel (SW)
*
******************************************************************************/

#include "../include/pwm.h"
#include "../defines.h"

//----------------------------------------------------
// INITIALIZE PWM AND SS CONTROL MODULE
//----------------------------------------------------
int Initialize_PWM_SS_Control(DS_Data* data){

	int Status = 0;

	Xint32  	PWM_en = (Xint32) data->cw.enableControl;                     				//data register for Inport PWM_en_AXI
	Xint32  	Mode = (Xint32) data->cw.switchingMode;                       				//data register for Inport Mode_AXI
	Xfloat32  	PWM_Scal_f_carrier = (data->ctrl.pwmFrequency/(FPGA_100MHz*0.5));     		//data register for Inport PWM_f_carrier_kHz_AXI
	Xfloat32  	PWM_Scal_T_carrier = (data->ctrl.pwmPeriod*((FPGA_100MHz/1000000.0)*0.5));	//data register for Inport PWM_T_carrier_us_AXI (The factor 1000000 comes from the unit [us])
	Xint32  	PWM_min_pulse_width = (Xint32) (ldexpf(data->rasv.pwmMinPulseWidth,Q12)); 	//data register for Inport PWM_min_pulse_wiidth_AXI
	Xint32  	m_u1_norm = (Xint32)(ldexpf(data->rasv.halfBridge1DutyCycle,Q12)); 			//shift 12 Bits //data register for Inport m_u1_norm_AXI
	Xint32  	m_u2_norm = (Xint32)(ldexpf(data->rasv.halfBridge2DutyCycle,Q12)); 			//shift 12 Bits //data register for Inport m_u2_norm_AXI
	Xint32  	m_u3_norm = (Xint32)(ldexpf(data->rasv.halfBridge3DutyCycle,Q12)); 			//shift 12 Bits //data register for Inport m_u3_norm_AXI

	// PWM enable is set to 0 and disable the PWM Module
	Xil_Out32(PWM_SS_Con_Enable_REG, (Xint32)PWM_en);	// Input to the IP-Core

	// Mode is set to 0, which is the Mode for switch signals from the PWM module with reference from AXI
	Xil_Out32(PWM_SS_Con_Mode_REG, (Xint32)Mode);   // Input to the IP-Core
	//0 = PWM with modulation amplitude via AXI
	//1 = PWM with modulation amplitude via FPGA
	//2 = Control signals via FPGA (e.g. FCS-MPC)

	// PWM carrier signal frequency is set to e.g. 100 kHz
	Xil_Out32(PWM_SS_Con_Scal_f_car_REG, (Xint32)(ldexpf(PWM_Scal_f_carrier,Q26))); 		//shift 26 Bits

	// PWM carrier signal Period is set to 10 us
	Xil_Out32(PWM_SS_Con_Scal_T_car_REG, (Xint32)PWM_Scal_T_carrier);

	// PWM minimum pulse width is set between 0-1
	Xil_Out32(PWM_SS_Con_min_pulse_REG, (Xint32)PWM_min_pulse_width);

	// Reference for modulation amplitude (Duty Cycle) u1-u3  ->  value range must be inside 0-1
	Xil_Out32(PWM_SS_Con_m_u1_norm_REG, (Xint32)m_u1_norm);
	Xil_Out32(PWM_SS_Con_m_u2_norm_REG, (Xint32)m_u2_norm);
	Xil_Out32(PWM_SS_Con_m_u3_norm_REG, (Xint32)m_u3_norm);

	//Set the Tri-State to off (=default)
	Xil_Out32(PWM_SS_Con_TriState_HB1_REG, (Xint32)0); //Xil_Out32(PWM_SS_Con_TriState_HB1_REG, (Xint32)1);
	Xil_Out32(PWM_SS_Con_TriState_HB2_REG, (Xint32)0);
	Xil_Out32(PWM_SS_Con_TriState_HB3_REG, (Xint32)0);

return Status;
}

