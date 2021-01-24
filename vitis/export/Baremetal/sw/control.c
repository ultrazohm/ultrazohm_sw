/******************************************************************************
* Copyright 2021 Eyke Liegmann, Sebastian Wendel
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/

#include "xbasic_types.h" 								//Include for Data types
#include "../main.h"
#include "../defines.h"

#include "../include/control.h"


//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE & SET THE FPGA CONTROL ALGORITHM
// - set constants (i.e. weighting factors)
// - enables different operation modes
//----------------------------------------------------
int Initialize_FPGAController(DS_Data* data){

	int Status = 0;

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
    //data->ctrl.pwmFrequency = 100000; 	//[Hz]
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
    //data->ctrl.pwmFrequency = 100000; 	//[Hz]
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

	return Status;
}
