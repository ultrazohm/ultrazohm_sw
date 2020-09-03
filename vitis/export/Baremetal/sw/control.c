/******************************************************************************
*
* control.c
*
* Copyright (C) 2019 UltraZohm Community, All rights reserved.
*
*  Created on: 22.10.2019
*      Author: Wendel Sebastian (SW)
*
******************************************************************************/

#include "xbasic_types.h" 								//Include for Data types
#include "../main.h"
#include "../defines.h"

#include "../include/control.h"

//CODEGEN Simulink
//#include "../include/blac_drive/PI_BLAC_n_Bueh_V6_codegen.h" //SW 07.02.2018 PI for speed

//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE & SET THE FPGA CONTROL ALGORITHM
// - set constants (i.e. weighting factors)
// - enables different operation modes
//----------------------------------------------------
int Initialize_FPGAController(DS_Data* data){

	int Status = 0;

	//Enable the speed control (0 = current control and 0x1 = speed control)
//	Xil_Out8(Control_EN_SPEED_REG, 0x0);	// Input to the IP-Core
	//Write down the weighting factor for the id error
	//Xil_Out32(Control_q_fid_REG, (Xint32)(ldexpf(1.0,Q4))); 			// Shift 4 Bit for fixed-point // Input to the IP-Core
	//Write down the weighting factor for the iq error
	//Xil_Out32(Control_q_fiq_REG, (Xint32)(ldexpf(1.0,Q4))); 			// Shift 4 Bit for fixed-point // Input to the IP-Core
	//Write down the voltage of U_dc
	//Xil_Out32(Control_u_dc_REG, (Xint32)(ldexpf(data->av.U_ZK,Q11)));	// Shift 11 Bit for fixed-point // Input to the IP-Core
	//Write down the init load inertia
	//Xil_Out32(Control_M_L_REG, (Xint32)(ldexpf(0.0,Q11)));				// Shift 11 Bit for fixed-point // Input to the IP-Core
	//Write down the init frictional torque
	//Xil_Out32(Control_M_Reib_REG, (Xint32)(ldexpf(0.0,Q11)));			// Shift 11 Bit for fixed-point // Input to the IP-Core

	//Write down the maximal allowed phase current
	//Xil_Out32(Control_I_max_REG, (Xint32)((Xint8)data->mrp.motorMaximumCurrentContinuousOperation)); 											//
	//Write down the minimal allowed phase current
	//Xil_Out32(Control_I_min_REG, (Xint32)(((Xint16)data->mrp.motorMaximumCurrentContinuousOperation) | 0b00000000000000000000001000000000)); 	//Or Mask in order to add the minus as 10th Bit
	//Write down the phase resistance
	//Xil_Out32(Control_R_ph_REG, (Xint32)(ldexpf(data->mrp.motorStatorResistance,Q11)));															// Shift 11 Bit for fixed-point // Input to the IP-Core
	//Write down T/Ld
	//Xil_Out32(Control_Scal_T_REG, (Xint32)(ldexpf((data->mrp.FCS_MPC_Time_Period/data->mrp.motorDirectInductance),Q11)));						// Shift 11 Bit for fixed-point // Input to the IP-Core
	//Write down omega_mech*p*Psi = n *(2*pi/60)*p*Psi
	//Xil_Out32(Control_Scal_nq_REG, (Xint32)(ldexpf(((2.0*PI/60.0)*data->mrp.motorPolePairNumber*data->mrp.motorFluxConstant),Q17)));			// Shift 17 Bit for fixed-point // Input to the IP-Core
	//Write down omega_mech*p*Lq = n *(2*pi/60)*p*Lq
	//Xil_Out32(Control_Scal_nd_REG, (Xint32)(ldexpf(((2.0*PI/60.0)*data->mrp.motorPolePairNumber*data->mrp.motorQuadratureInductance),Q17)));	// Shift 17 Bit for fixed-point // Input to the IP-Core

return Status;
}

//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE & SET THE ARM CONTROL ALGORITHM
// - set constants (i.e. weighting factors)
// - enables different operation modes
//----------------------------------------------------
int Initialize_ARMController(DS_Data* data){

	int Status = 0;

//	init_user_PI_BLAC_n_Bueh_V6(); //Call the init function of the codegen functionality


return Status;
}

//==============================================================================================================================================================
//----------------------------------------------------
// CONFIGURE THE SYSTEM FOR FOC CONTROL
// - set the modulator
// - enable Duty cycle for modulator
//----------------------------------------------------
int Configure_FOC_Control(DS_Data* data){

	int Status = 0;

	//PWM and SS control module
	data->cw.switchingMode = DutyFromAXI; //data->cw.switchingMode = DutyFromAXI; else noDuty//
    data->cw.modulationMode = pwmModulation; //data->cw.modulationMode = pwmModulation; else noModulation//
    data->rasv.halfBridge1DutyCycle = 0.0;
    data->rasv.halfBridge2DutyCycle = 0.0;
    data->rasv.halfBridge3DutyCycle = 0.0;
    data->ctrl.pwmFrequency = 100000; 	//[Hz]
    data->ctrl.pwmPeriod = 10;			//[us]
    data->rasv.TriState[0]=0;
    data->rasv.TriState[1]=0;
    data->rasv.TriState[2]=0;

return Status;
}

//==============================================================================================================================================================
//----------------------------------------------------
// CONFIGURE THE SYSTEM FOR MPC CONTROL
// - switch off the modulator
// - configure the system for MPC control
//----------------------------------------------------
int Configure_MPC_Control(DS_Data* data){

	int Status = 0;

	//PWM and SS control module
	data->cw.switchingMode = noDuty;
    data->cw.modulationMode = noModulation;
    data->rasv.halfBridge1DutyCycle = 0.0;
    data->rasv.halfBridge2DutyCycle = 0.0;
    data->rasv.halfBridge3DutyCycle = 0.0;
    data->ctrl.pwmFrequency = 100000; 	//[Hz]
    data->ctrl.pwmPeriod = 10;			//[us]
    data->rasv.TriState[0]=0;
    data->rasv.TriState[1]=0;
    data->rasv.TriState[2]=0;


return Status;
}

//==============================================================================================================================================================
//----------------------------------------------------
// CONFIGURE THE SYSTEM FOR DTC CONTROL
// - switch off the modulator
// - configure the system for DTC control
//----------------------------------------------------
int Configure_DTC_Control(DS_Data* data){

	int Status = 0;

	//toDO

return Status;
}

//==============================================================================================================================================================
//----------------------------------------------------
// CONFIGURE THE SYSTEM FOR HALF-BRIDGE CONTROL
// - switch on the modulator
// - configure the system for Duty-Cycle control
//----------------------------------------------------
int Configure_HalfBridge_Control(DS_Data* data){

	int Status = 0;

	//PWM and SS control module
	data->cw.switchingMode = DutyFromAXI;
	data->cw.modulationMode = pwmModulation;
	data->rasv.halfBridge1DutyCycle = 0.0;
	data->rasv.halfBridge2DutyCycle = 0.0;
	data->rasv.halfBridge3DutyCycle = 0.0;
	data->rasv.TriState[0]=0;
	data->rasv.TriState[1]=0;
	data->rasv.TriState[2]=0;

return Status;
}

//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE MOTOR RELATED PARAMETERS
//
//----------------------------------------------------
int Initialize_MotorRelatedParameters(DS_Data* data){

	int Status = 0;

	//General parameters which mainly depend on the system and not on the motor
	data->mrp.motorMaximumCurrentShortTimeOperation= 12.5; 	// [A] maximum value which is measurable with the shunts from the K�brich-Board.
	data->mrp.motorMaximumDcLinkVoltage = 48.0; 			// [V] maximum value which is measurable with the K�brich-Board.
	data->mrp.motorMaximumSpeed = 10000;					// [rpm] maximum speed which the encoder can detect.

	//	//Motor Buehler ??? (Comment strg+shift+/  Uncomment strg+shift+/)
	//	data->mrp.motorMaximumCurrentContinuousOperation = 16.0; // [A]
	//	data->av.U_ZK = 24.0*0.93; 		//[V] DC-Link voltage 300ns from InterLock-module + 400ns from IRS driver -> 700ns @ 100KHz the DC-Link is reduced about 7%
	//	data->mrp.FCS_MPC_Time_Period = 10.0000e-06; //FCS-IP-Core current control Period
	//	data->mrp.motorDirectInductance = 4.4450e-04; // [H]
	//	data->mrp.motorQuadratureInductance = 4.4450e-04; // [H]
	//	data->mrp.motorStatorResistance = 0.1085; //[Ohm]
	//	data->mrp.motorPolePairNumber = 4; // Number of pole pairs in the motor (necessary for the encoder)
	//	data->mrp.motorFluxConstant = 0.0092; //[Vs] Psi_sinus

	//Motor B�hler 1.25.058.401 (Comment strg+shift+/  Uncomment strg+shift+/)
	data->mrp.motorMaximumCurrentContinuousOperation = 11.0; // [A]
	data->mrp.FCS_MPC_Time_Period = 10.0000e-06; //FCS-IP-Core current control Period
	data->mrp.motorDirectInductance = 2.00e-04; // [H] Identified-ID-Run: Ld= 191 uH (Motor+Mosfet+Leitung+Klemme) //Identified LCR-Meter: L_ph_ph= 410uH -> Ld= 205uH
	data->mrp.motorQuadratureInductance = 2.00e-04; // [H]
	data->mrp.motorStatorResistance = 0.07; //[Ohm] Identified-ID-Run: Rs= 0.0718 (Motor+Mosfet+Leitung+Klemme) //R_ds,on Mosfet(BSC094N06LS5) = 0.0094 Ohm //Identified LCR-Meter: R_ph_ph= 0.118 -> Rs= 0.118/2 + 2*0.0094 = 0.0778 Ohm
	data->mrp.motorPolePairNumber = 4; // Number of pole pairs in the motor (necessary for the encoder)
	data->mrp.motorFluxConstant = 0.005950905; //[Vs] Psi_sinus
	data->mrp.motorNominalCurrent=8; //8;
	data->mrp.motorNominalSpeed=3000;
	data->mrp.motorRotorInertia=1.585e-05;
	data->ctrl.foc.cc.Kp_id=0.2;
	data->ctrl.foc.cc.Tn_id=0.003;
	data->ctrl.foc.cc.Kp_iq=0.2;
	data->ctrl.foc.cc.Tn_iq=0.003;
	data->ctrl.foc.sc.Kp=0.04;
	data->ctrl.foc.sc.Tn=0.1;
	data->ctrl.foc.cc.Kp_id_Custom=0.2;
	data->ctrl.foc.cc.Tn_id_Custom=0.003;
	data->ctrl.foc.cc.Kp_iq_Custom=0.2;
	data->ctrl.foc.cc.Tn_iq_Custom=0.003;
	data->ctrl.foc.sc.Kp_Custom=0.04;
	data->ctrl.foc.sc.Tn_Custom=0.1;
	data->mrp.ViscousFriction=0.000164;
	data->mrp.CoulombFriction=0.0145;
	data->mrp.BreakawayTorque=0.0284;

	//	//Motor B�hler 1.25.058.201 (Comment strg+shift+/  Uncomment strg+shift+/)
	//	data->mrp.motorMaximumCurrentContinuousOperation = 16.0; // [A]
	//	data->mrp.FCS_MPC_Time_Period = 10.0000e-06; //FCS-IP-Core current control Period
	//	data->mrp.motorDirectInductance = 3.750e-04; // [H]
	//	data->mrp.motorQuadratureInductance = 3.750e-04; // [H]
	//	data->mrp.motorStatorResistance = 0.07; //[Ohm]
	//	data->mrp.motorPolePairNumber = 4; // Number of pole pairs in the motor (necessary for the encoder)
	//	data->mrp.motorFluxConstant = 0.009161; //[Vs] Psi_sinus   //0.010194; //
	//	data->mrp.motorNominalCurrent=8;
	// 	data->mrp.motorNominalSpeed=3000;
	//	data->mrp.motorRotorInertia=1.585e-05;
	//	data->ctrl.foc.cc.Kp_id=0.2;
	//	data->ctrl.foc.cc.Tn_id=0.003;
	//	data->ctrl.foc.cc.Kp_iq=0.2;
	//	data->ctrl.foc.cc.Tn_iq=0.003;
	//	data->ctrl.foc.sc.Kp=0.04;
	//	data->ctrl.foc.sc.Tn=0.1;
	//	data->ctrl.foc.cc.Kp_id_Custom=0.2;
	//	data->ctrl.foc.cc.Tn_id_Custom=0.003;
	//	data->ctrl.foc.cc.Kp_iq_Custom=0.2;
	//	data->ctrl.foc.cc.Tn_iq_Custom=0.003;
	//	data->ctrl.foc.sc.Kp_Custom=0.04;
	//	data->ctrl.foc.sc.Tn_Custom=0.1;
	// 	data->mrp.ViscousFriction=0.000164;
	// 	data->mrp.CoulombFriction=0.0145;
	//  data->mrp.BreakawayTorque=0.0284;

	//	//Motor Buehler 201 (Comment strg+shift+/  Uncomment strg+shift+/)
	//	data->mrp.motorMaximumCurrentContinuousOperation = 16.0; // [A]
	//	data->mrp.FCS_MPC_Time_Period = 10.0000e-06; //FCS-IP-Core current control Period
	//	data->mrp.motorDirectInductance = 3e-04; // [H]
	//	data->mrp.motorQuadratureInductance = 3e-04; // [H]
	//	data->mrp.motorStatorResistance = 0.07; //[Ohm]
	//	data->mrp.motorPolePairNumber = 4; // Number of pole pairs in the motor (necessary for the encoder)
	//	data->mrp.motorFluxConstant = 0.0075; //[Vs] Psi_sinus   //0.010194; //
	//	data->mrp.motorNominalCurrent=8;
	// 	data->mrp.motorNominalSpeed=3000;
	//	data->mrp.motorRotorInertia=1.585e-05;
	//	data->ctrl.foc.cc.Kp_id=0.2;
	//	data->ctrl.foc.cc.Tn_id=0.003;
	//	data->ctrl.foc.cc.Kp_iq=0.2;
	//	data->ctrl.foc.cc.Tn_iq=0.003;
	//	data->ctrl.foc.sc.Kp=0.04;
	//	data->ctrl.foc.sc.Tn=0.1;
	//	data->ctrl.foc.cc.Kp_id_Custom=0.2;
	//	data->ctrl.foc.cc.Tn_id_Custom=0.003;
	//	data->ctrl.foc.cc.Kp_iq_Custom=0.2;
	//	data->ctrl.foc.cc.Tn_iq_Custom=0.003;
	//	data->ctrl.foc.sc.Kp_Custom=0.04;
	//	data->ctrl.foc.sc.Tn_Custom=0.1;
	// 	data->mrp.ViscousFriction=0.000164;
	// 	data->mrp.CoulombFriction=0.0145;
	//  data->mrp.BreakawayTorque=0.0284;

	//	//Motor EBM ECI63.20.B00 ( Comment strg+shift+/  Uncomment strg+shift+/)
	//	data->mrp.motorMaximumCurrentContinuousOperation = 16.0; // [A]
	//	data->mrp.FCS_MPC_Time_Period = 10.0000e-06; //FCS-IP-Core current control Period
	//	data->mrp.motorDirectInductance = 1.45e-04; // [H]
	//	data->mrp.motorQuadratureInductance = 2.94e-04; // [H]
	//	data->mrp.motorStatorResistance = 0.10; //[Ohm]
	//	data->mrp.motorPolePairNumber = 4; // Number of pole pairs in the motor (necessary for the encoder)
	//	data->mrp.motorFluxConstant = 0.006; //[Vs] Psi_sinus   //0.010194; //
	//	data->mrp.motorNominalCurrent=8.5;
	// 	data->mrp.motorNominalSpeed=4000;
	//	data->mrp.motorRotorInertia=1.78e-05;
	//	data->ctrl.foc.cc.Kp_id=0.2;
	//	data->ctrl.foc.cc.Tn_id=0.003;
	//	data->ctrl.foc.cc.Kp_iq=0.2;
	//	data->ctrl.foc.cc.Tn_iq=0.003;
	//	data->ctrl.foc.sc.Kp=0.04;
	//	data->ctrl.foc.sc.Tn=0.1;
	//	data->ctrl.foc.cc.Kp_id_Custom=0.2;
	//	data->ctrl.foc.cc.Tn_id_Custom=0.003;
	//	data->ctrl.foc.cc.Kp_iq_Custom=0.2;
	//	data->ctrl.foc.cc.Tn_iq_Custom=0.003;
	//	data->ctrl.foc.sc.Kp_Custom=0.04;
	//	data->ctrl.foc.sc.Tn_Custom=0.1;
	// 	data->mrp.ViscousFriction=0.00015;
	// 	data->mrp.CoulombFriction=0.015;
	//  data->mrp.BreakawayTorque=0.03;

		//Motor EBM ECI63.20.D00 ( Comment strg+shift+/  Uncomment strg+shift+/)
	//	data->mrp.motorMaximumCurrentContinuousOperation = 16.0; // [A]
	//	data->mrp.FCS_MPC_Time_Period = 10.0000e-06; //FCS-IP-Core current control Period
	//	data->mrp.motorDirectInductance = 2.5e-04; // [H]
	//	data->mrp.motorQuadratureInductance = 5.5e-04; // [H]
	//	data->mrp.motorStatorResistance = 0.219; //[Ohm]
	//	data->mrp.motorPolePairNumber = 4; // Number of pole pairs in the motor (necessary for the encoder)
	//	data->mrp.motorFluxConstant = 0.010; //[Vs] Psi_sinus   //0.010194; //
	//	data->mrp.motorNominalCurrent=4.5;
	// 	data->mrp.motorNominalSpeed=4000;
	//	data->mrp.motorRotorInertia=1.7e-05;
	//	data->ctrl.foc.cc.Kp_id=0.2;
	//	data->ctrl.foc.cc.Tn_id=0.003;
	//	data->ctrl.foc.cc.Kp_iq=0.2;
	//	data->ctrl.foc.cc.Tn_iq=0.003;
	//	data->ctrl.foc.sc.Kp=0.04;
	//	data->ctrl.foc.sc.Tn=0.1;
	//	data->ctrl.foc.cc.Kp_id_Custom=0.2;
	//	data->ctrl.foc.cc.Tn_id_Custom=0.003;
	//	data->ctrl.foc.cc.Kp_iq_Custom=0.2;
	//	data->ctrl.foc.cc.Tn_iq_Custom=0.003;
	//	data->ctrl.foc.sc.Kp_Custom=0.04;
	//	data->ctrl.foc.sc.Tn_Custom=0.1;
	// 	data->mrp.ViscousFriction=0.00015;
	// 	data->mrp.CoulombFriction=0.015;
	//  data->mrp.BreakawayTorque=0.03;

	//	//Motor Hoerner Prototyp AKA Dicke Berta ( Comment strg+shift+/  Uncomment strg+shift+/)
	//	data->mrp.motorMaximumCurrentContinuousOperation = 20.0; // [A]
	//	data->mrp.FCS_MPC_Time_Period = 10.0000e-06; //FCS-IP-Core current control Period
	//	data->mrp.motorDirectInductance = 4.4e-04; // [H]
	//	data->mrp.motorQuadratureInductance = 2.45e-03; // [H]
	//	data->mrp.motorStatorResistance = 0.320; //[Ohm]
	//	data->mrp.motorPolePairNumber = 4; // Number of pole pairs in the motor (necessary for the encoder)
	//	data->mrp.motorFluxConstant = 0.0194; //[Vs] Psi_sinus   //0.010194; //
	//	data->mrp.motorNominalCurrent=8;
	// 	data->mrp.motorNominalSpeed=2000;
	//	data->mrp.motorRotorInertia=8.4e-05;
	//	data->ctrl.foc.cc.Kp_id=0.2;
	//	data->ctrl.foc.cc.Tn_id=0.003;
	//	data->ctrl.foc.cc.Kp_iq=0.2;
	//	data->ctrl.foc.cc.Tn_iq=0.003;
	//	data->ctrl.foc.sc.Kp=0.04;
	//	data->ctrl.foc.sc.Tn=0.1;
	//	data->ctrl.foc.cc.Kp_id_Custom=0.2;
	//	data->ctrl.foc.cc.Tn_id_Custom=0.003;
	//	data->ctrl.foc.cc.Kp_iq_Custom=0.2;
	//	data->ctrl.foc.cc.Tn_iq_Custom=0.003;
	//	data->ctrl.foc.sc.Kp_Custom=0.04;
	//	data->ctrl.foc.sc.Tn_Custom=0.1;
	//	data->mrp.ViscousFriction=0.0002;
	//	data->mrp.CoulombFriction=0.03;
	//	data->mrp.BreakawayTorque=0.05;

//		//Motor Brose Lenkungsmotor C54771-101 (m. Hoerner) (Comment strg+shift+/  Uncomment strg+shift+/)
//		data->mrp.motorMaximumCurrentContinuousOperation = 16.0; // [A]
//		data->mrp.FCS_MPC_Time_Period = 10.0000e-06; //FCS-IP-Core current control Period
//		data->mrp.motorDirectInductance = 4.052e-05; // [H] Identified-ID-Run: Ld= 191 uH (Motor+Mosfet+Leitung+Klemme) //Identified LCR-Meter: L_ph_ph= 410uH -> Ld= 205uH
//		data->mrp.motorQuadratureInductance = 4.052e-05; // [H]
//		data->mrp.motorStatorResistance = 0.0386; //[Ohm] Identified-ID-Run: Rs= 0.0718 (Motor+Mosfet+Leitung+Klemme) //R_ds,on Mosfet(BSC094N06LS5) = 0.0094 Ohm //Identified LCR-Meter: R_ph_ph= 0.118 -> Rs= 0.118/2 + 2*0.0094 = 0.0778 Ohm
//		data->mrp.motorPolePairNumber = 5; // Number of pole pairs in the motor (necessary for the encoder)
//		data->mrp.motorFluxConstant = 0.006898; //[Vs] Psi_sinus
//		data->mrp.motorNominalCurrent=8; //8;
//		data->mrp.motorNominalSpeed=3000;
//		data->mrp.motorRotorInertia=2.5581e-04;
//		data->ctrl.foc.cc.Kp_id=0.2;
//		data->ctrl.foc.cc.Tn_id=0.003;
//		data->ctrl.foc.cc.Kp_iq=0.2;
//		data->ctrl.foc.cc.Tn_iq=0.003;
//		data->ctrl.foc.sc.Kp=0.04;
//		data->ctrl.foc.sc.Tn=0.1;
//		data->ctrl.foc.cc.Kp_id_Custom=0.2;
//		data->ctrl.foc.cc.Tn_id_Custom=0.003;
//		data->ctrl.foc.cc.Kp_iq_Custom=0.2;
//		data->ctrl.foc.cc.Tn_iq_Custom=0.003;
//		data->ctrl.foc.sc.Kp_Custom=0.04;
//		data->ctrl.foc.sc.Tn_Custom=0.1;
//	 	data->mrp.ViscousFriction=0.000164;
//	 	data->mrp.CoulombFriction=0.0145;
//	 	data->mrp.BreakawayTorque=0.0284;

//	//Motor Faulhaber 3274...BP4 165mNM1 (Comment strg+shift+/  Uncomment strg+shift+/)
//	data->mrp.motorMaximumCurrentContinuousOperation = 11.0; // [A]
//	data->mrp.FCS_MPC_Time_Period = 10.0000e-06; //FCS-IP-Core current control Period
//	data->mrp.motorDirectInductance = 30e-06; // [H] Identified-ID-Run: Ld= 191 uH (Motor+Mosfet+Leitung+Klemme) //Identified LCR-Meter: L_ph_ph= 410uH -> Ld= 205uH
//	data->mrp.motorQuadratureInductance = 30e-06; // [H]
//	data->mrp.motorStatorResistance = 0.125; //[Ohm] Identified-ID-Run: Rs= 0.0718 (Motor+Mosfet+Leitung+Klemme) //R_ds,on Mosfet(BSC094N06LS5) = 0.0094 Ohm //Identified LCR-Meter: R_ph_ph= 0.118 -> Rs= 0.118/2 + 2*0.0094 = 0.0778 Ohm
//	data->mrp.motorPolePairNumber = 2; // Number of pole pairs in the motor (necessary for the encoder)
//	data->mrp.motorFluxConstant = 0.003; //[Vs] Psi_sinus
//	data->mrp.motorNominalCurrent=8; //8;
//	data->mrp.motorNominalSpeed=3000;
//	data->mrp.motorRotorInertia=1.585e-05;
//	data->ctrl.foc.cc.Kp_id=0.2;
//	data->ctrl.foc.cc.Tn_id=0.003;
//	data->ctrl.foc.cc.Kp_iq=0.2;
//	data->ctrl.foc.cc.Tn_iq=0.003;
//	data->ctrl.foc.sc.Kp=0.04;
//	data->ctrl.foc.sc.Tn=0.1;
//	data->ctrl.foc.cc.Kp_id_Custom=0.2;
//	data->ctrl.foc.cc.Tn_id_Custom=0.003;
//	data->ctrl.foc.cc.Kp_iq_Custom=0.2;
//	data->ctrl.foc.cc.Tn_iq_Custom=0.003;
//	data->ctrl.foc.sc.Kp_Custom=0.04;
//	data->ctrl.foc.sc.Tn_Custom=0.1;
//	data->mrp.ViscousFriction=0.000164;
//	data->mrp.CoulombFriction=0.0145;
//	data->mrp.BreakawayTorque=0.0284;

	//Two Mass System
	data->mrp.loadRotorInertia=0.0001; 		// in kgm^2
	data->mrp.totalRotorInertia=data->mrp.loadRotorInertia+data->mrp.motorRotorInertia;
	data->mrp.TwoMassSystemStiffness=50;	//in Nm/rad
	data->mrp.TwoMassSystemDamping=0.005;	// in Nms

return Status;
}
