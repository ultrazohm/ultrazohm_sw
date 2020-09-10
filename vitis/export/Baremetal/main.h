/******************************************************************************
*
* main.h
*
* Copyright (C) 2019 UltraZohm Community, All rights reserved.
*
*  Created on: 22.08.2018
*      Author: Wendel Sebastian (SW)
* Description: Zynq UltraScale+
*
******************************************************************************/

#ifndef main_H_
#define main_H_


/* Include Files */
#include "xparameters.h"								//Include for the implemented IP-Blocks from the PL
#include "xgpiops.h"
#include "xstatus.h"
#include "xil_printf.h"
#include "xscugic.h"									//Include for Interrupt handler (necessary for all GIC interrupts)
#include "xipipsu.h"									//Include for Interrupt handler (necessary for all IPI interrupts)
#include "xbasic_types.h" 								//Include for Datatypes
//#include "xadcps.h"									//Include of ADC-Block
//#include "xsysmon.h"									//Include of ADC-Block
#include "xtmrctr.h"									//Include of the Timer-Blocks
#include "math.h"										//Include for math operations
#include <stdio.h>


/* Definitions */
//#define LED 0xC3									/* Initial LED value - XX0000XX */
#define LED_DELAY 10000000							/* Software delay length */
// xil_printf is a smaller, optimised printf */

// ========== Definitions =========================================================================
#define PI 3.141592653589
#define PI2 6.2832

#define OUTPUT_PIN							1 								//This Pin is an Output
#define INPUT_PIN							0 								//This Pin is an Input

#define ENABLE_PIN							1 								//This Pin is enabled
#define DISABLE_PIN							0 								//This Pin is disabled

#define GPIO_CHANNEL 						1								/* GPIO port for GPIOs */


// Defines that map the number of the MIO PIN of the PS to the signal name of the signal on the carrier board (X13)
#define PS_DIG_GPIO_01	30
#define PS_DIG_GPIO_02	31
#define PS_ANL_GPIO_01	44
#define PS_ANL_GPIO_02	45
#define EXT_GPIO_1 		13
#define EXT_GPIO_2 		33
#define EXT_GPIO_3 		34
#define EXT_GPIO_4 		39
#define EXT_GPIO_5 		40
#define EXT_GPIO_6 		52
#define EXT_GPIO_7 		53
#define EXT_GPIO_8 		55

// LED on carrier board and frontpanel
#define LED_1								EXT_GPIO_1
#define LED_2								EXT_GPIO_2
#define LED_3								EXT_GPIO_3
#define LED_4								EXT_GPIO_4

// Names of LED on frontpanel
#define LED_ready 	LED_1
#define LED_running LED_2
#define LED_error 	LED_3
#define LED_user 	LED_4

// Switches on frontpanel
#define SW_1 EXT_GPIO_6
#define SW_2 EXT_GPIO_7
#define SW_3 EXT_GPIO_5

#define SW_system  SW_1
#define SW_control SW_2
#define SW_stop    SW_3


//ADC define
#define TX_BUFFER_SIZE						1
#define RX_BUFFER_SIZE  					64
//Defines for averaging the speed from the encoder
#define SPEED_BUF_SIZE  					2 //3== erster CCS-Versuch
#define SPEED_BUF_SIZE_INVERS 				1/SPEED_BUF_SIZE
//Defines for averaging the current from the ADC
#define  CURRENT_BUF_SIZE 					6
#define  CURRENT_BUF_SIZE_INVERS 			1/CURRENT_BUF_SIZE

//ADC define
#define XAdcPL_RAWToCurrent_6A			0.0036747685 //Faktor 12 Bit vergleiche Excel: "Auslegung Stromsensoren LEM"

#define MAXIMUM_LENGTH_MTPA_TABLE 16

//Fractional Bit defines
#define   Q32         32
#define   Q31         31
#define   Q30         30
#define   Q29         29
#define   Q28         28
#define   Q27         27
#define   Q26         26
#define   Q25         25
#define   Q24         24
#define   Q23         23
#define   Q22         22
#define   Q21         21
#define   Q20         20
#define   Q19         19
#define   Q18         18
#define   Q17         17
#define   Q16         16
#define   Q15         15
#define   Q14         14
#define   Q13         13
#define   Q12         12
#define   Q11         11
#define   Q10         10
#define   Q9          9
#define   Q8          8
#define   Q7          7
#define   Q6          6
#define   Q5          5
#define   Q4          4
#define   Q3          3
#define   Q2          2
#define   Q1          1

//Inverse fractional Bit defines
#define   Q30toF		-Q30
#define   Q29toF		-Q29
#define   Q28toF		-Q28
#define   Q27toF		-Q27
#define   Q26toF		-Q26
#define   Q25toF		-Q25
#define   Q24toF		-Q24
#define   Q23toF		-Q23
#define   Q22toF		-Q22
#define   Q21toF		-Q21
#define   Q20toF		-Q20
#define   Q19toF		-Q19
#define   Q18toF		-Q18
#define   Q17toF		-Q17
#define   Q16toF		-Q16
#define   Q15toF		-Q15
#define   Q14toF		-Q14
#define   Q13toF		-Q13
#define   Q12toF		-Q12
#define   Q11toF		-Q11
#define   Q10toF		-Q10
#define   Q09toF		-Q9
#define   Q08toF		-Q8
#define   Q07toF		-Q7
#define   Q06toF		-Q6
#define   Q05toF		-Q5
#define   Q04toF		-Q4
#define   Q03toF		-Q3
#define   Q02toF		-Q2
#define   Q01toF		-Q1

//Frequencies in the system
#define FPGA_100MHz		100000000.0f		//Clock frequency
#define FPGA_50MHz		50000000.0f			//Clock frequency
#define FPGA_20MHz		20000000.0f			//Clock frequency
#define FPGA_10MHz		10000000.0f			//Clock frequency

// ========== JavaScope-Ethernet =========================================================================
//Defines for JavaScope (4 or 2 channels)
#define chJavaScope			4
//#define chJavaScope		2

// ========== Structures =========================================================================
typedef struct
{
	float I_d;
	float I_q;
	float U_d;
	float U_q;
	float theta_elec;
	float theta_mech;
	float theta_offset; //in rad/s
} ParkTrans_struct; //für Gleichgrößen von der Parktransformation (dq)

typedef struct
{
	Xuint32 status_BareToRTOS;
	Xboolean SampledDataWriteDone;
	Xboolean SampledDataReadDone;
	Xboolean SampledDataError;
	Xuint16 schiebereg_ausgaenge;
	Xuint32 slowDataContent;
	Xuint16 slowDataID;
	Xuint16 val[20];
} ARM_to_Oszi_Data_shared_struct;

typedef struct
{
	Xuint16 id;
	Xuint16 value;
	Xuint16 digInputs;
} Oszi_to_ARM_Data_shared_struct;

//========================
typedef enum {
  sector_100 = 0,           //!< E2A = 1, E2B = 0, E2C = 0 //SW: Hall1 =1, Hall2 = 0, Hall3 = 0
  sector_110,               //!< E2A = 1, E2B = 1, E2C = 0
  sector_010,               //!< E2A = 0, E2B = 1, E2C = 0
  sector_011,               //!< E2A = 0, E2B = 1, E2C = 1
  sector_001,               //!< E2A = 0, E2B = 0, E2C = 1
  sector_101,               //!< E2A = 1, E2B = 0, E2C = 1
  initStateRotorSector,     //!< Initialization state
  errorStateRotorSector     //!< Impossible hall signal combination
} rotorSector;

typedef enum {
  noEvent = 0,            //!< Initialization state

  	  	  	  	  	  	  //!< CounterClockwise rotation
  event_010_011,          //!< sector_010 -> sector_011
  event_011_001,          //!< sector_011 -> sector_001
  event_001_101,          //!< sector_001 -> sector_101
  event_101_100,          //!< sector_101 -> sector_100
  event_100_110,          //!< sector_100 -> sector_110
  event_110_010,          //!< sector_110 -> sector_010

  	  	  	  	  	  	  //!< Clockwise rotation
  event_011_010,          //!< sector_010 <- sector_011
  event_001_011,          //!< sector_011 <- sector_001
  event_101_001,          //!< sector_001 <- sector_101
  event_100_101,          //!< sector_101 <- sector_100
  event_110_100,          //!< sector_100 <- sector_110
  event_010_110,          //!< sector_110 <- sector_010
}  hallEvent;

typedef enum {
  scheme_zpm = 0,		// p=Halbbruecke auf Plus, m=Halbbrücke auf Minus, z=Halbbrücke in HighZ-Zustand
  scheme_mpz,
  scheme_mzp,
  scheme_zmp,
  scheme_pmz,
  scheme_pzm,
  initStateCommutationScheme, //!< Initialization state
  clearedStateCommutationScheme,
  errorStateCommutationScheme
} commutationScheme;

typedef enum {
   scheme_zpz= 0,		// p=Halbbruecke auf Plus, z=Halbbrücke auf Minus (z=zero in diesem Fall?)
   scheme_zpp,
   scheme_zzp,
   scheme_pzp,
   scheme_pzz,
   scheme_ppz,
  initStateCommutationScheme180, //!< Initialization state
  clearedStateCommutationScheme180,
  errorStateCommutationScheme180
} commutationScheme180; //SW: Standart für 180° Kommutierung wie es in Tabelle von Tobi Roth gefordert ist

typedef enum {
	flagDisabled = 0,
	flagEnabled
} enableFlag;

typedef enum {
	Clockwise = 0,		//CW
	CounterClockwise  	//CCW
} senseOfRotation;

typedef enum {
	valueFalse = 0,
	valueTrue
} boolean;

typedef enum {
  DirectTorqueControl =0,
  fieldOrientedControl,     //!< sinusoidal commutation
  ModelPredictiveControl,   //!< control MPC
  sixStepCommutation,     	//!< six step commutation
  halfBridgeControl         //!< control each half bridge separately
} currentControlMethod;

typedef enum {
  TorqueControl =0,
  CurrentControl,
  SpeedControl,
  PositionControl
} ControlReference;

typedef enum {
	commutationAngle120 = 0,
	commutationAngle180
} sixStepCommutationMethod;

typedef enum {
	rotorSectorHallBased = 0,
	rotorAngleHallBased,
	rotorAngleVoltageCurrentBased
} rotorAngleCalculationMethod;

typedef enum
{
  analogHall = 0,				//
  hallSensors120Degree,
  HiperFace,					//
  incrementalEncoder,			//
  sensorless,
  forcedAngle,					// ok
  //sinCosEncoder,				// ### nicht mehr benötigt
  //pwmPositionSensor,			// ### nicht mehr benötigt
  //spiPositionSensor,			// ### nicht mehr benötigt
  hallSensors180Degree			//
} rotorAngleEstimationMethod;

typedef enum
{
  noModulation = 0,			//for FCS-MPC
  pwmModulation,
  svmModulation
}gatesignalsModulationMethod;

typedef enum
{
  DutyFromAXI = 0,			//Duty-Cycle from processor over AXI
  DutyFromDirect,			//Duty-Cycle direct in FPGA
  noDuty					//for FCS-MPC
}SwitchingMethod;

typedef enum {
  ManuelParams =0,			//Do no offline identification
  ElekID,					//Do only the offline identification of the electrical system
  ElekAndMechID,			//Do the offline identification of the electrical and mechanical system
  MechID					//Do only the offline identification of the mechanical system
} MotorID_Method;

typedef struct _mtpaTable_ {
	float_t currentReferenceValues[MAXIMUM_LENGTH_MTPA_TABLE];
	float_t currentControlAngles[MAXIMUM_LENGTH_MTPA_TABLE];
} mtpaTable;

typedef struct _hallSensorVars_ {
	Xuint32 eCapCount;
	Xuint32 eCapCountArray[6];
	Xuint32 estimatedEcapCount;
	hallEvent latestHallEvent;
	rotorSector currentRotorSector;
	rotorSector previousRotorSector;
	Xfloat32 electricPositionObserved;
	Xfloat32 iq_electricFrequencyObserved;
	Xfloat32 loadTorqueObserved;
	Xfloat32 electricTorqueEstimated;
	Xfloat32 resetObserver;
	Xint32 cap123_gefiltert[3];
} hallSensorVars;

typedef struct _singleHallSensorVars_ {
	Xuint32 ticksCommutationTimer;
	boolean commutationBurstInitiated;
	boolean burstEnableRequest;
	Xuint32 timerReloads;
} singleHallSensorVars;

typedef struct _controlWord_ {	// 26 bits
	enableFlag enableSystem:1;
	enableFlag enableControl:1;
	senseOfRotation rotationDirection:1;
	currentControlMethod ControlMethod:5;
	ControlReference ControlReference:3;
	sixStepCommutationMethod sixStepCommutationMode:1;
	//enableFlag enableClosedLoopCurrentControl:1;
	enableFlag enableMTPA:1;
	rotorAngleEstimationMethod rotorAngleEstimationMode:5;
	gatesignalsModulationMethod modulationMode:3;
	SwitchingMethod switchingMode:3;
	enableFlag useCustomControllerParameters:1;
	enableFlag enableParameterID:1;
} controlWord;

typedef struct _statusWord_ { // 10 bits, combined status & warning word
	senseOfRotation rotationDirection:1;
	boolean readyForSystemEnable:1;
	boolean currentControllerAntiWindUpActive:1;
	boolean speedControllerAntiWindUpActive:1;
	boolean currentProtectionControllerActive:1;
	boolean controllerSamplingTimeTooHigh:1;
	boolean invalidControlWord:1;
	boolean rsvd1:1;
	boolean rsvd2:1;
	boolean rsvd3:1;
	//boolean communicationTimeoutOccured:1;
} statusWord;


typedef struct _statusReset_ { // 3 bits
	//boolean maximumShortTermCurrentReached:1;
	//boolean maximumContinuousCurrentExceeded:1;
	//boolean calculationTimeInterruptServiceRoutineExceeded:1;
	//boolean communicationTimeoutOccured:1;
	boolean rsvd1:1;
	boolean rsvd2:1;
	boolean rsvd3:1;
	//boolean rsvd4:1;
} statusReset;


typedef struct _errorWord_ { // 18 bits
	uint16_t errorCodeXilinx:8;
	boolean mtpaTableError:1;
	boolean dcLinkOvervoltageOccured:1;
	boolean maximumShortTermCurrentReached:1;
	boolean maximumContinuousCurrentExceeded:1;
	boolean communicationTimeoutOccured:1;
	boolean pwmFrequencyError:1;
	boolean rsvd1:1;
	boolean rsvd2:1;
	boolean rsvd3:1;
	boolean rsvd4:1;
} errorWord;

typedef struct _errorReset_ { // 10 bits
	boolean dcLinkOvervoltageOccured:1;
	boolean maximumShortTermCurrentReached:1;
	boolean maximumContinuousCurrentExceeded:1;
	boolean communicationTimeoutOccured:1;
	boolean pwmFrequencyError:1;
	boolean rsvd1:1;
	boolean rsvd2:1;
	boolean rsvd3:1;
	boolean rsvd4:1;
	//boolean rsvd5:1; // PL 14.03.2018 ein Bit zu viel
} errorReset;

typedef struct _motorRelatedParameters_ {
	Xfloat32 motorPolePairNumber;
	Xfloat32 motorStatorResistance;
	Xfloat32 motorDirectInductance;
	Xfloat32 motorQuadratureInductance;
	Xfloat32 motorVoltageConstant;
	Xfloat32 motorFluxConstant;
	Xfloat32 FCS_MPC_Time_Period;
	Xfloat32 motorVoltageConstantDistortionFactor;
	Xfloat32 motorRotorInertia;
	Xfloat32 motorMaximumCurrentContinuousOperation;	// [A] This is the maximum current which is allowed per phase for several control cycles/ a specific time.
	Xfloat32 motorMaximumCurrentShortTimeOperation;		// [A] This is the maximum current which can be detected per phase. The system switches off, if this limit is reached. Typically this is the maximum current which is measurable or allowed for the power electronics at all.
	Xfloat32 motorMaximumDcLinkVoltage;
	Xfloat32 motorMaximumDcLinkImbalance;				// For 3 Level Inverter
	Xfloat32 motorMaximumSpeed;
	mtpaTable mtpaTab;
	Xfloat32 incrementalEncoderResolution;
	Xfloat32 incrementalEncoderOffset;
	Xfloat32 incrementalEncoderOversamplingFactor;
	Xfloat32 potiMaxSpeed;
	Xfloat32 potiMaxCurrent;
	Xfloat32 CurrentContiniousOperationOvershootToleranceTime; // [s]
	Xfloat32 CurrentContiniousOperationControlTime; // [s]
	Xfloat32 MotorMaximumCurrentContinuousOperationTolerance; // [%]
	Xfloat32 TimeConstantGainHallSpeedFilter; //Factor, which is used to make the Hall-speed filter faster or slower (3 = very fast and 16 = slow, 8 = default)
	Xuint32 uiTimeConstantGainHallSpeedFilter; //Factor, which is used to make the Hall-speed filter faster or slower (3 = very fast and 16 = slow, 8 = default)
	Xfloat32 ADCConversionFactorIph; 	//Phase current
	Xfloat32 ADCConversionFactorVph;	//Phase voltage
	Xfloat32 ADCConversionFactorIdc;	//DC current
	Xfloat32 ADCConversionFactorVdc;	//DC voltage
	Xfloat32 ADCConversionFactorTrq;	//Torque
	Xfloat32 ADCConversionFactorTmp; 	//Temperature
	Xfloat32 ADCconvFactorReadback;
	Xfloat32 motorNominalCurrent;		// Ampere
	Xfloat32 motorNominalSpeed;			// [rpm] This speed is necessary for the online Parameter-ID. Because in the online ID, a percentual speed is requested in order to determine if a steady-state situation is given. This percentage is based on this nominal speed.
	Xfloat32 loadRotorInertia;			//Rotorinertia on Loadside
	Xfloat32 totalRotorInertia;			// Motor+Load Rotorinertia
	Xfloat32 TwoMassSystemStiffness;	//rotational torsion stiffness of drivetrain considered as two mass system
	Xfloat32 TwoMassSystemDamping;		//rotational torsion damping of drivetrain considered as two mass system
	Xfloat32 BreakawayTorque;			//Breakawaytorque in Nm
	Xfloat32 CoulombFriction;			//Coulombfriction in Nm
	Xfloat32 ViscousFriction;			// Viscous Frictioncoefficient in Nms
} motorRelatedParameters;		// = 32 x 4bytes ohne mtpaTable, mit mtpaTable (2 x 16 x 4bytes) --> gesamt 64 x 4bytes

// union allows to access the values as array and individual variables
// see also this link for more information: https://hackaday.com/2018/03/02/unionize-your-variables-an-introduction-to-advanced-data-types-in-c/
typedef union _ConversionFactors_ {
	struct{
		Xfloat32 ADC_A1;
		Xfloat32 ADC_A2;
		Xfloat32 ADC_A3;
		Xfloat32 ADC_A4;
		Xfloat32 ADC_B5;
		Xfloat32 ADC_B6;
		Xfloat32 ADC_B7;
		Xfloat32 ADC_B8;
		};
	float ADC_array[8];
} ConversionFactors;

typedef union _Measurements_ {
	struct{
		Xfloat32 ADC_A1;
		Xfloat32 ADC_A2;
		Xfloat32 ADC_A3;
		Xfloat32 ADC_A4;
		Xfloat32 ADC_B5;
		Xfloat32 ADC_B6;
		Xfloat32 ADC_B7;
		Xfloat32 ADC_B8;
		};
	float ADC_array[8];
} Measurements;

typedef struct _ADCcard_ {
	ConversionFactors 	cf;
	Measurements		me;
} ADCcard;

typedef struct _AnalogAdapters_ {
	ADCcard A1;
	ADCcard A2;
	ADCcard A3;
} AnalogAdapters;

typedef struct _actualValues_ {
	Xfloat32 I_L1; 		// Grid side current in A
	Xfloat32 I_L2; 		// Grid side current in A
	Xfloat32 I_L3; 		// Grid side current in A
	Xfloat32 U_L1; 		// Grid side voltage in V
	Xfloat32 U_L2; 		// Grid side voltage in V
	Xfloat32 U_L3; 		// Grid side voltage in V
	Xfloat32 I_U; 		// Machine side current in A
	Xfloat32 I_V; 		// Machine side current in A
	Xfloat32 I_W; 		// Machine side current in A
	Xfloat32 U_U; 		// Machine side voltage in V
	Xfloat32 U_V; 		// Machine side voltage in V
	Xfloat32 U_W; 		// Machine side voltage in V
	Xfloat32 U_ZK; 		// DC-Link voltage in V
	Xfloat32 U_ZK2; 	// DC-Link voltage 2 in V
	Xfloat32 Res1; 		// Reserveeingang 1 - X51 (normiert auf 0...1 --> 0...4095)
	Xfloat32 Res2; 		// Reserveeingang 2 - X50 (normiert auf 0...1 --> 0...4095)
	Xfloat32 mechanicalRotorSpeed; 		// in rpm
	Xfloat32 mechanicalPosition; 		// in m
	Xfloat32 mechanicalTorque; 			// in Nm
	Xfloat32 mechanicalTorqueSensitive; // in Nm
	Xfloat32 mechanicalTorqueObserved; 	// in Nm for observing the load torque
	Xfloat32 I_d;
	Xfloat32 I_q;
	Xfloat32 U_d;
	Xfloat32 U_q;
	Xfloat32 theta_elec;
	Xfloat32 theta_mech;
	Xfloat32 theta_offset; //in rad/s
	Xfloat32 temperature;
	Xuint32  heartbeatframe_content;
} actualValues;

typedef struct _referenceAndSetValues_ {
	Xfloat32 referenceCurrent_iq;
	Xfloat32 referenceCurrent_id;
	Xfloat32 referenceFrequency;
	Xfloat32 referenceSpeed;
	Xfloat32 referenceTorque;
	Xfloat32 referencePosition;
	Xfloat32 halfBridge1DutyCycle;
	Xfloat32 halfBridge2DutyCycle;
	Xfloat32 halfBridge3DutyCycle;
	Xfloat32 sixStepCommutationDutyCycle;
	Xfloat32 phaseAdvanceAngle;
	Xfloat32 currentControlAngle;
	Xfloat32 ModifiedReferenceCurrent_id;	//The manipulated reference current in the d-axis, e.g. by the online ID
	Xfloat32 ModifiedReferenceCurrent_iq;   //The manipulated reference current in the q-axis, e.g. by the online ID
	Xint32   TriState[3];
	Xfloat32 pwmMinPulseWidth;				//Minimal Duty Cycle which is allowed. e.g. if the Duty Cycle wants to switch only for, lets say 100ns, we should avoid switching at all.
} referenceAndSetValues;

typedef struct _communicationStateVariables_ {
	boolean communicationTimeoutOccured;
	boolean mtpaTableError;
//	messageType returnMessage;
	Xuint32 headerCounter;
	Xuint32 messageCounter;
	Xfloat32 testCommTimeout;
} communicationStateVariables;

typedef struct _rotorAngleEstimationVars_ {
	hallSensorVars hs;
	Xfloat32 electricFrequency;
	Xfloat32 electricPosition;
	Xfloat32 estimatedTorque;
	Xfloat32 mechanicSpeedRpm;
	Xfloat32 rotorAngle_pu_FAST;					// added PL 14.07.2017
	rotorSector currentRotorSector_FAST;	// added PL 14.07.2017
} rotorAngleEstimationVars;

typedef struct _currentControllerVars_ {
	Xfloat32 Kp_id;			//This is for the FOC on the processor (e.g. for the ID run or for the calculated control gains from the GUI)
	Xfloat32 Tn_id;			//This is for the FOC on the processor (e.g. for the ID run or for the calculated control gains from the GUI)
	Xfloat32 Kp_iq;			//This is for the FOC on the processor (e.g. for the ID run or for the calculated control gains from the GUI)
	Xfloat32 Tn_iq;			//This is for the FOC on the processor (e.g. for the ID run or for the calculated control gains from the GUI)
	Xfloat32 Kp_id_Custom; 	//This is for an own FOC which is e.g. is running on the FPGA
	Xfloat32 Tn_id_Custom; 	//This is for an own FOC which is e.g. is running on the FPGA
	Xfloat32 Kp_iq_Custom; 	//This is for an own FOC which is e.g. is running on the FPGA
	Xfloat32 Tn_iq_Custom; 	//This is for an own FOC which is e.g. is running on the FPGA
	boolean FOCFeedForward; //in order to activate a decoupling network
} currentControllerVars;

typedef struct _speedControllerVars_ {
	Xfloat32 Kp;			//This is for the FOC on the processor (e.g. for the ID run or for the calculated control gains from the GUI)
	Xfloat32 Tn;			//This is for the FOC on the processor (e.g. for the ID run or for the calculated control gains from the GUI)
	Xfloat32 Kp_Custom; 	//This is for an own FOC which is e.g. is running on the FPGA
	Xfloat32 Tn_Custom; 	//This is for an own FOC which is e.g. is running on the FPGA
	Xfloat32 referenceSpeedRamped;
} speedControllerVars;

typedef struct _fluxControllerVars_ {
	Xfloat32 Kp;			//This is for the FOC on the processor (e.g. for the ID run or for the calculated control gains from the GUI)
	Xfloat32 Tn;			//This is for the FOC on the processor (e.g. for the ID run or for the calculated control gains from the GUI)
	Xfloat32 Kp_Custom; 	//This is for an own FOC which is e.g. is running on the FPGA
	Xfloat32 Tn_Custom; 	//This is for an own FOC which is e.g. is running on the FPGA
} fluxControllerVars;

typedef struct _finiteControlSetVars_ {
	Xfloat32 lambda_dU;		//This weighting factor is to punish switching and therefore to minimize the switching frequency!
	Xfloat32 lambda_2;		//This weighting factor is to punish ...
	Xfloat32 lambda_3;		//This weighting factor is to punish ...
	Xfloat32 lambda_4;		//This weighting factor is to punish ...
	Xboolean bEnableVSP2CC; //This is to activate the variable switching approach for FCS-MPC
} finiteControlSetVars;

typedef struct _continuousControlSetVars_ {
	Xfloat32 rw;			//This is the overall tuning factor
	Xfloat32 Np;			//This is the prediction horizon
	Xfloat32 Nc; 			//This is the control horizon
} continuousControlSetVars;

typedef struct _sixStepCommutationVars_ {
	currentControllerVars cc;
	Xfloat32 dutyCycle;
	Xfloat32 modifiedDutyCycle;
	Xfloat32 manualDutyCycle;
	Xfloat32 phaseAdvanceAngle;
	Xfloat32 iq_phaseAdvanceAngle;
	Xfloat32 iq_phaseAdvanceAngle_pu;
	Xfloat32 phaseAdvanceAnglePrescaler;
	Xfloat32 iq_phaseAdvanceAnglePrescaler;
	int16_t phaseAdvanceSectors;
	Xfloat32 dcLinkCurrent;
	Xfloat32 iq_dcLinkCurrent;
	commutationScheme currentScheme;
	commutationScheme nextScheme;
	commutationScheme180 currentScheme180;
	commutationScheme180 nextScheme180;
	speedControllerVars sc;
	uint16_t sensorlessNoDoubleCommutationsCounter;
	rotorSector sensorlessLastCommutatedSector;
	rotorSector sensorlessNextSector;
	int16_t phaseAdvanceSectorsNew;
} sixStepCommutationVars;

typedef struct _fieldOrientedControlVars_ {
	currentControllerVars cc;
	speedControllerVars sc;
	uint16_t numberValidValuesInMTPA;
} fieldOrientedControlVars;


typedef struct _halfBridgeControlVars_ {
	Xfloat32 halfBridge1DutyCycle;
	Xfloat32 halfBridge2DutyCycle;
	Xfloat32 halfBridge3DutyCycle;
} halfBridgeControlVars;

typedef struct _modelPredictiveControlVars_ {
	finiteControlSetVars fcs;
	continuousControlSetVars ccs;
} modelPredictiveControlVars;

typedef struct _parameterIdentificationVars_ {
	//Automatic Current Reference Control for Online ID
	// Inputs
	Xboolean bEnableAutoCurrentControl; //Flag enables Auto Current Reference Control
	Xfloat32 d_current_steps; 			// Amount of d_current_steps of Auto Current Reference Control
	Xfloat32 q_current_steps;			//Amount of q_current_steps of Auto Current Reference Control
	Xfloat32 max_res_ref_current;		// Maximum absolute current of Auto Current Reference Control

	//Outputs
	Xboolean bRefAutomaticControlled;	//Flag recognizes when Auto Current Reference is activated
	Xfloat32 ParameterID_I_d;			// d-current based on dq-transformation on the processor (this is necessary, because the "fast" d-current comes from the FPGA into the av-Structure)
	Xfloat32 ParameterID_I_q;			// q-current based on dq-transformation on the processor (this is necessary, because the "fast" q-current comes from the FPGA into the av-Structure)

	//Offline ID Stateflow Inputs
	Xuint16  MotorID; 				//Enable parameter identification and chooses parameter being identified
//	Xuint16  controlType; 			//Choose current or speed FOC in OfflineIDStateflow
	Xboolean accept;				//Accept for Offline ID Stateflow
	Xboolean reset_Offl;			//Reset for Offline ID Stateflow
	Xfloat32 sampleTimeISR;			//SampleTime of Offline ID Stateflow
	Xfloat32 dutyCyc;				//DutyCyc for Offline ID of R and L
	Xfloat32 n_ref_measurement; 	//speed for fluxconstant identification
	Xuint16  identLq;				// Flag for identifying Lq
	Xuint16  VibON;					// Adds Vibration for inertia identification
	Xfloat32 VibAmp;				// chooses amplitude of Vibration
	Xuint16  VibFreq;				// chooses frequency of vibration
	Xuint16  identR;				// Flag for Enabling Identification of R in Automated Measuring Mode
	Xuint16  AMM_ON;				// Activates Automated Measuring Mode in Offline ID Stateflow
	Xuint16  AMM_RUN;				// Recognizes if Automated Measuring Mode runs
	Xfloat32 IDstart;				// Start value of d-Current in Automated Measuring Mode
	Xfloat32 IDstop;				// Stop value of d-Current in Automated Measuring Mode
	Xfloat32 IDstepsize;			// Step size of d-Current steps in Automated Measuring Mode
	Xfloat32 IQstart;				// Start value of q-Current in Automated Measuring Mode
	Xfloat32 IQstop;				// Stop value of q-Current in Automated Measuring Mode
	Xfloat32 IQstepsize;			// Step size of d-Current in Automated Measuring Mode
	Xfloat32 LogIntervals;			// LogIntervals in Automated Measuring Mode
	Xuint32  NumberOfSamples;		// Amount of Samples in Automated Measuring Mode
	Xfloat32 settlingTime;			// Settlingtime of Automated Measuring Mode
	Xfloat32 n_visco_max;			// Maximum speed for viscous friction ID
	Xfloat32 N_Brk;					// Amount of Breakaway
	Xfloat32 Brk_Count;				// Counter for recognizing breakaway
	Xfloat32 N_visco;				// Amount of Measurement values of viscous friction ID
	Xfloat32 eta_omega_Reib;		// Threshold of steady State Recognizing in  viscous friction ID
	Xfloat32 StepScale;				// Size of Steps in Breakaway friction ID in Percent of rated Current
	Xuint16  f_min;					// Minimum identified frequency of two mass system ID
	Xuint16  f_max;					// Maximum identified frequency of two mass system ID
	Xfloat32 d_TMS_start;			// Startvalue of damping for two mass system ID
	Xfloat32 ScaleTorquePRBS;		// Amplitude of Pseudo Random Binary Noise Currentexcitation in A of q-Current
	Xfloat32 goertzlAmp;			// Amplitude of Sinus q-current Excitation for J-ident via Goertzl Algorithm

	//Online and Offline ID Stateflow Inputs
	Xfloat32 identRAmp;				// d-Current Step Amplitude for R-Identification in ONLINE and OFFLINE ID
	Xfloat32 Temp_ref;				// Reference Temperature for Reference Resistance

	//Online ID Stateflow Inputs
	Xboolean bEnableOnlineID;		// Enable Online ID
	Xfloat32 DevSpeed;				// Threshold for SteadyStateDetection in percent of actual Value
	Xfloat32 DevCurrent;			// Threshold for SteadyStateDetection in percent of actual Value
	Xuint16  AverageTransParams;	// En/Disables Averaging of Online Parameters (Debug)
	Xuint16  AllowStepFlag;			// Allows d-Current step in steady state
	Xuint16  ResetOnline;			// Reset all Online ID values


	//Offline ID Stateflow Outputs
	Xuint16  activeState;			//active State of Offline ID Stateflow
	Xuint16  offsetLock;			// offset Lock of identified mechanical encoder offset
	Xfloat32 array_counter;			// counter for array slow data communication of Mech ID Plot
	Xuint16  controlArrCounter;		// controlcounter for successful communication
	Xboolean AdmitParamsFlag; 		// Set electrical identified Parameters as motor related ones
	Xboolean AdmitMechParamsFlag;	// Set mechanical identified Parameters as motor related ones
	Xfloat32 Offline_Ld;			// Offline identified L_d inductance
	Xfloat32 Offline_Lq;			// Offline identified L_q inductance
	Xfloat32 Offline_Rs;			// Offline identified R_ph resistance
	Xfloat32 Offline_Psi_PM;					// Offline identified psi_pm flux constant
	Xfloat32 Offline_polePairs;					// Offline identified pole pairs
	Xfloat32 Offline_motorRotorInertia;			// Rotorinertia on Motorside
	Xfloat32 Offline_loadRotorInertia;			// Rotorinertia on Loadside
	Xfloat32 Offline_totalRotorInertia;			// Motor+Load Rotorinertia
	Xfloat32 Offline_TwoMassSystemStiffness;	// rotational torsion stiffness of drivetrain considered as two mass system
	Xfloat32 Offline_TwoMassSystemDamping;		// rotational torsion damping of drivetrain considered as two mass system
	Xfloat32 Offline_BreakawayTorque;			// Breakawaytorque in Nm
	Xfloat32 Offline_CoulombFriction;			// Coulombfriction in Nm
	Xfloat32 Offline_ViscousFriction;			// Viscous Frictioncoefficient in Nms
	Xfloat32 Offline_TwoMassSystem_c_0;
	Xfloat32 Offline_ud_ref;			// Reference voltage from the FOC inside the Parameter Identification
	Xfloat32 Offline_uq_ref;			// Reference voltage from the FOC inside the Parameter Identification


	// Online ID Stateflow Outputs
	Xboolean bOnlineIDenabled; 			//recognize if online ID is enabled
	Xfloat32 map_counter;				//counter for array slow data communication of flux maps
	Xuint16  ControlMapCounter;			// controlcounter for successful fluxmapcommunication
	Xfloat32 WindingTemp;				// WindingTemp of Online ID
	Xfloat32 Online_Ld;					// in mH : Online identified L_d inductance
	Xfloat32 Online_Lq;					// in mH : Online identified L_q inductance
	Xfloat32 Online_Rs;					// in mOhm : Online identified R_ph resistance
	Xfloat32 Online_Psi_PM;				// in mVs : Online identified psi_pm flux constant

	// Interpolation of Flux Maps
	Xfloat32 psi_array[600];			// Storage of Flux mesurement values
	Xfloat32 FluxMap_d[400];			// Map of d-Flux
	Xfloat32 xAxis_FluxMap_d[20];		// x-Axis of d-Flux Map
	Xfloat32 yAxis_FluxMap_d[20];		// y-Axis of d-Flux Map
	Xfloat32 FluxMap_q[400];			// Map of q-Flux
	Xfloat32 xAxis_FluxMap_q[20];		// x-Axis of q-Flux Map
	Xfloat32 yAxis_FluxMap_q[20];		// y-Axis of q-Flux Map
	Xfloat32 InvFluxMap_d[400];			// d-Current Map
	Xfloat32 xAxis_InvFluxMap_d[20];	// x-Axis of d-Current Map
	Xfloat32 yAxis_InvFluxMap_d[20];	// y-Axis of d-Current Map
	Xfloat32 InvFluxMap_q[400];			// q-Curret Map
	Xfloat32 xAxis_InvFluxMap_q[20];	// x-Axis of q-Current Map
	Xfloat32 yAxis_InvFluxMap_q[20];	// y-Axis of q-Current Map
	Xfloat32 *FluxpointerUncleaned;		// Pointer to uncleaned Psi-Array
	Xfloat32 *FluxpointerCleaned;		// Pointer to cleaned Psi-Array
	Xfloat32 *FluxTempPointer;			// Pointer to Array with Delta T-Delta Psi Values
	Xfloat32 FluxTemp[200];				// Array eith Delta T - Delta Psi values
	Xfloat32 FluxTempConst;				// Calculated Constant of Temperaturedependency of FluxConstant
	Xfloat32 FluxTempError;				// Error of calculated FluxConstant at Temp_ref
	Xboolean bCleanPsiArray;			// Flag for cleaning Psi arrays from similar values
	Xboolean bPsiArrayCleaned;			// Flag that recognizes a cleaned Psi_array
	Xfloat32 n_FluxPoints;				// Amount of independend Flux Measuring Points
	Xfloat32 eta_curr;					// Threshold for similar Measuring Points
	Xboolean bCalcPsi;					// Flag for Refreshing Flux Maps
	Xfloat32 Online_MessArray_Element; 	// One Element of the "measArray1" for the data transfer of the online identified data
	Xfloat32 Online_i_est_Element;		// One Element of the "i_est" for the data transfer of the online identified data
} parameterIdentificationVars;

typedef struct _controllerVars_ {
	sixStepCommutationVars ssc;
	fieldOrientedControlVars foc;
	halfBridgeControlVars hbc;
	modelPredictiveControlVars mpc;
	Xfloat32 pwmFrequency;
	Xfloat32 samplingTime;
	Xfloat32 dcLinkVoltage;
	Xfloat32 terminalCurrents[3];
	Xfloat32 terminalVoltages[3];
	boolean  ctrlObjectReinitRequest;
	Xfloat32 pwmPeriod;
	Xfloat32 FullScaleCurrent_IQ_A;	// PL 19.12.2017 Welchem float-Wert entspricht der Full-Scale-IQ Faktor? = USER_IQ_FULL_SCALE_CURRENT_A aus user.h
	Xfloat32 OneOverFullScaleCurrent_IQ_A; // PL 19.12.2017 1 / (USER_IQ_FULL_SCALE_CURRENT_A) aus user.h
	Xfloat32 FullScaleVoltage_IQ_V;	// PL 19.12.2017 Welchem float-Wert entspricht der Full-Scale-IQ Faktor? = USER_IQ_FULL_SCALE_VOLTAGE_V aus user.h
} controllerVars;

typedef struct _debugVariables_ {
	Xuint32  counter;
//	Xfloat32 SSC_SystemVs;
//	Xfloat32 SSC_SystemT1;
//	Xfloat32 SSC_SystemTSigma;
//	Xfloat32 SSC_ControllerVr;
//	Xfloat32 SSC_ControllerTn;
//	Xfloat32 SC_System_Tsigma;
//	Xfloat32 SC_System_VsDivByT1;
//	Xfloat32 SC_ControllerTn;
//	Xfloat32 SC_Controller_Vr;
	Xfloat32 finalReferenceCurrent;
//	Xfloat32 iq_Var;
//	Xfloat32 finalDutyCycle;
	Xfloat32 controlError;
//	Xfloat32 errorSum;
//	Xfloat32 controlSignal;
	Xfloat32 referenceSpeedLimited;
	Xfloat32 positionWithPhaseAdvance;
	//Xuint32 eCapCountAdcIsr;
	/*rotorSector commutationSector;
	uint16_t numberOfHallEvents;
	Xfloat3215 speedPu;
	Xint32 sectorDifference;
	Xint32 controllerSamplingTimesCounter;
	Xint32 controllerSamplingTimesBetweenHallEvents;
	rotorSector previousRotorSector;
	Xfloat32 lastMeasuredRotorAngle;
	Xfloat32 rotorSectorsTravelled;
	Xfloat32 rotorAngleElectric;
	hallEvent latestHallEvent;
	Xint32 hallEventSectorDifference;
	Xint32 speedPuInteger;
	Xint32 product;
	Xint32 divBySix;
	Xint32 shiftBy16;*/
//	Xfloat32 terminalCurrent1IQ;
//	Xfloat32 terminalCurrent1;
//	Xfloat32 oc[3];
	Xuint32  timeStampCounter;
	uint16_t isrCyclesFor10Millisec;
	Xint32 sw1;
	Xint32 sw2;
	Xint32 sw3;
} debugVariables;


typedef struct _DS_Data_ {
	controlWord cw;
	statusWord sw;
	errorWord ew;
	errorReset er;
	referenceAndSetValues rasv;
	actualValues av;
	motorRelatedParameters mrp;
	rotorAngleEstimationVars rae;
	parameterIdentificationVars pID;
	controllerVars ctrl;
	debugVariables dv;
	AnalogAdapters aa;
} DS_Data;



//----------------------------------------------------
// FUNCTIONS
//----------------------------------------------------
void delayy(void);
int plotData(DS_Data* data);
int turnPowerElectronicsOff(DS_Data* data);
int turnPowerElectronicsOn(DS_Data* data);
int AXI2TCM_on(void);
int ControllerOff(DS_Data* data);
int ErrorHandling(DS_Data* data);
int ErrorReset(DS_Data* data);
int ControllerOn(DS_Data* data);
int ADC_Set_Offset(void);
int ADC_Clear_Offset(void);
int InitializeDataStructure(DS_Data* data);


#endif /* main_H_ */
