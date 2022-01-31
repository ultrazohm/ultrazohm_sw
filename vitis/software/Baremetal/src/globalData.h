#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_d_gan_inverter/uz_d_gan_inverter.h"
#define MAXIMUM_LENGTH_MTPA_TABLE 16
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
} ParkTrans_struct;

typedef struct
{
	uint32_t status_BareToRTOS;
	_Bool SampledDataWriteDone;
	_Bool SampledDataReadDone;
	_Bool SampledDataError;
	uint16_t schiebereg_ausgaenge;
	uint32_t slowDataContent;
	uint16_t slowDataID;
//	uint16_t val[20];
} ARM_to_Oszi_Data_shared_struct;

typedef struct
{
	uint16_t id;
	uint16_t value;
	uint16_t digInputs;
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
	Clockwise = 0,		//CW
	CounterClockwise  	//CCW
} senseOfRotation;

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
	float currentReferenceValues[MAXIMUM_LENGTH_MTPA_TABLE];
	float currentControlAngles[MAXIMUM_LENGTH_MTPA_TABLE];
} mtpaTable;

typedef struct _hallSensorVars_ {
	uint32_t eCapCount;
	uint32_t eCapCountArray[6];
	uint32_t estimatedEcapCount;
	hallEvent latestHallEvent;
	rotorSector currentRotorSector;
	rotorSector previousRotorSector;
	float electricPositionObserved;
	float iq_electricFrequencyObserved;
	float loadTorqueObserved;
	float electricTorqueEstimated;
	float resetObserver;
	int cap123_gefiltert[3];
} hallSensorVars;

typedef struct _singleHallSensorVars_ {
	uint32_t ticksCommutationTimer;
	_Bool commutationBurstInitiated;
	_Bool burstEnableRequest;
	uint32_t timerReloads;
} singleHallSensorVars;

typedef struct _controlWord_ {	// 26 bits
	_Bool enableSystem:1;
	_Bool enableControl:1;
	senseOfRotation rotationDirection:1;
	currentControlMethod ControlMethod:5;
	ControlReference ControlReference:3;
	sixStepCommutationMethod sixStepCommutationMode:1;
	//enableFlag enableClosedLoopCurrentControl:1;
	_Bool enableMTPA:1;
	rotorAngleEstimationMethod rotorAngleEstimationMode:5;
	gatesignalsModulationMethod modulationMode:3;
	SwitchingMethod switchingMode:3;
	_Bool useCustomControllerParameters:1;
	_Bool enableParameterID:1;
} controlWord;

typedef struct _statusWord_ { // 10 bits, combined status & warning word
	senseOfRotation rotationDirection:1;
	_Bool readyForSystemEnable:1;
	_Bool currentControllerAntiWindUpActive:1;
	_Bool speedControllerAntiWindUpActive:1;
	_Bool currentProtectionControllerActive:1;
	_Bool controllerSamplingTimeTooHigh:1;
	_Bool invalidControlWord:1;
	_Bool rsvd1:1;
	_Bool rsvd2:1;
	_Bool rsvd3:1;
} statusWord;


typedef struct _statusReset_ { // 3 bits
	_Bool rsvd1:1;
	_Bool rsvd2:1;
	_Bool rsvd3:1;
} statusReset;


typedef struct _errorWord_ { // 18 bits
	uint16_t errorCodeXilinx:8;
	_Bool mtpaTableError:1;
	_Bool dcLinkOvervoltageOccured:1;
	_Bool maximumShortTermCurrentReached:1;
	_Bool maximumContinuousCurrentExceeded:1;
	_Bool communicationTimeoutOccured:1;
	_Bool pwmFrequencyError:1;
	_Bool rsvd1:1;
	_Bool rsvd2:1;
	_Bool rsvd3:1;
	_Bool rsvd4:1;
} errorWord;

typedef struct _errorReset_ { // 10 bits
	_Bool dcLinkOvervoltageOccured:1;
	_Bool maximumShortTermCurrentReached:1;
	_Bool maximumContinuousCurrentExceeded:1;
	_Bool communicationTimeoutOccured:1;
	_Bool pwmFrequencyError:1;
	_Bool rsvd1:1;
	_Bool rsvd2:1;
	_Bool rsvd3:1;
	_Bool rsvd4:1;
} errorReset;

typedef struct _motorRelatedParameters_ {
	float motorPolePairNumber;
	float motorStatorResistance;
	float motorDirectInductance;
	float motorQuadratureInductance;
	float motorVoltageConstant;
	float motorFluxConstant;
	float FCS_MPC_Time_Period;
	float motorVoltageConstantDistortionFactor;
	float motorRotorInertia;
	float motorMaximumCurrentContinuousOperation;	// [A] This is the maximum current which is allowed per phase for several control cycles/ a specific time.
	float motorMaximumCurrentShortTimeOperation;		// [A] This is the maximum current which can be detected per phase. The system switches off, if this limit is reached. Typically this is the maximum current which is measurable or allowed for the power electronics at all.
	float motorMaximumDcLinkVoltage;
	float motorMaximumDcLinkImbalance;				// For 3 Level Inverter
	float motorMaximumSpeed;
	mtpaTable mtpaTab;
	float incrementalEncoderResolution;
	float incrementalEncoderOffset;
	float incrementalEncoderOversamplingFactor;
	float potiMaxSpeed;
	float potiMaxCurrent;
	float CurrentContiniousOperationOvershootToleranceTime; // [s]
	float CurrentContiniousOperationControlTime; // [s]
	float MotorMaximumCurrentContinuousOperationTolerance; // [%]
	float TimeConstantGainHallSpeedFilter; //Factor, which is used to make the Hall-speed filter faster or slower (3 = very fast and 16 = slow, 8 = default)
	uint32_t uiTimeConstantGainHallSpeedFilter; //Factor, which is used to make the Hall-speed filter faster or slower (3 = very fast and 16 = slow, 8 = default)
	float ADCConversionFactorIph; 	//Phase current
	float ADCConversionFactorVph;	//Phase voltage
	float ADCConversionFactorIdc;	//DC current
	float ADCConversionFactorVdc;	//DC voltage
	float ADCConversionFactorTrq;	//Torque
	float ADCConversionFactorTmp; 	//Temperature
	float ADCconvFactorReadback;
	float motorNominalCurrent;		// Ampere
	float motorNominalSpeed;			// [rpm] This speed is necessary for the online Parameter-ID. Because in the online ID, a percentual speed is requested in order to determine if a steady-state situation is given. This percentage is based on this nominal speed.
	float loadRotorInertia;			//Rotorinertia on Loadside
	float totalRotorInertia;			// Motor+Load Rotorinertia
	float TwoMassSystemStiffness;	//rotational torsion stiffness of drivetrain considered as two mass system
	float TwoMassSystemDamping;		//rotational torsion damping of drivetrain considered as two mass system
	float BreakawayTorque;			//Breakawaytorque in Nm
	float CoulombFriction;			//Coulombfriction in Nm
	float ViscousFriction;			// Viscous Frictioncoefficient in Nms
	float IncEncoderLPF_freq;		// corner frequency of low pass filter for incremental encoder readings
} motorRelatedParameters;		// = 32 x 4bytes ohne mtpaTable, mit mtpaTable (2 x 16 x 4bytes) --> gesamt 64 x 4bytes

// union allows to access the values as array and individual variables
// see also this link for more information: https://hackaday.com/2018/03/02/unionize-your-variables-an-introduction-to-advanced-data-types-in-c/
typedef union _ConversionFactors_ {
	struct{
		float ADC_A1;
		float ADC_A2;
		float ADC_A3;
		float ADC_A4;
		float ADC_B5;
		float ADC_B6;
		float ADC_B7;
		float ADC_B8;
		};
	float ADC_array[8];
} ConversionFactors;

typedef union _Measurements_ {
	struct{
		float ADC_A1;
		float ADC_A2;
		float ADC_A3;
		float ADC_A4;
		float ADC_B5;
		float ADC_B6;
		float ADC_B7;
		float ADC_B8;
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

typedef struct _DigitalAdapters_ {
	uz_d_gan_inverter_t *D4;
	uz_d_gan_inverter_t *D3;
} DigitalAdapters;

typedef struct _actualValues_ {
	float I_L1; 		// Grid side current in A
	float I_L2; 		// Grid side current in A
	float I_L3; 		// Grid side current in A
	float U_L1; 		// Grid side voltage in V
	float U_L2; 		// Grid side voltage in V
	float U_L3; 		// Grid side voltage in V
	float I_a1; 		// Machine side current in A
	float I_b1; 		// Machine side current in A
	float I_c1; 		// Machine side current in A
	float I_a2; 		// Machine side current in A
	float I_b2; 		// Machine side current in A
	float I_c2; 		// Machine side current in A
	float U_U; 		// Machine side voltage in V
	float U_V; 		// Machine side voltage in V
	float U_W; 		// Machine side voltage in V
	float U_ZK; 		// DC-Link voltage in V
	float U_ZK2; 	// DC-Link voltage 2 in V
	float Res1; 		// Reserveeingang 1 - X51 (normiert auf 0...1 --> 0...4095)
	float Res2; 		// Reserveeingang 2 - X50 (normiert auf 0...1 --> 0...4095)
	float mechanicalRotorSpeed; 		// in rpm
	float mechanicalRotorSpeed_filtered; // in rpm
	float mechanicalPosition; 		// in m
	float mechanicalTorque; 			// in Nm
	float mechanicalTorqueSensitive; // in Nm
	float mechanicalTorqueObserved; 	// in Nm for observing the load torque
	float I_d;
	float I_q;
	float I_x;
	float I_y;
	float U_d;
	float U_q;
	float theta_elec;
	float theta_elec_offset_compensated;
	float theta_mech;
	float theta_offset; //in rad/s
	float temperature;
	uint32_t  heartbeatframe_content;
	uint16_t activeState;
	float Temp_H1_D4;
} actualValues;

typedef struct _referenceAndSetValues_ {
	float referenceCurrent_iq;
	float referenceCurrent_id;
	float referenceFrequency;
	float referenceSpeed;
	float referenceTorque;
	float referencePosition;
	float halfBridge1DutyCycle;
	float halfBridge2DutyCycle;
	float halfBridge3DutyCycle;
	float halfBridge4DutyCycle;
	float halfBridge5DutyCycle;
	float halfBridge6DutyCycle;
	float sixStepCommutationDutyCycle;
	float phaseAdvanceAngle;
	float currentControlAngle;
	float ModifiedReferenceCurrent_id;	//The manipulated reference current in the d-axis, e.g. by the online ID
	float ModifiedReferenceCurrent_iq;   //The manipulated reference current in the q-axis, e.g. by the online ID
	int   TriState[3];
	float pwmMinPulseWidth;				//Minimal Duty Cycle which is allowed. e.g. if the Duty Cycle wants to switch only for, lets say 100ns, we should avoid switching at all.
	float open_loop_sin_amplitude;
	float open_loop_sin_frequency;
	_Bool NEXT;
	//_Bool RESET;
	uint16_t PERIOD;
	_Bool currentORspeedControl;
} referenceAndSetValues;

typedef struct _communicationStateVariables_ {
	_Bool communicationTimeoutOccured;
	_Bool mtpaTableError;
//	messageType returnMessage;
	uint32_t headerCounter;
	uint32_t messageCounter;
	float testCommTimeout;
} communicationStateVariables;

typedef struct _rotorAngleEstimationVars_ {
	hallSensorVars hs;
	float electricFrequency;
	float electricPosition;
	float estimatedTorque;
	float mechanicSpeedRpm;
	float rotorAngle_pu_FAST;					// added PL 14.07.2017
	rotorSector currentRotorSector_FAST;	// added PL 14.07.2017
} rotorAngleEstimationVars;

typedef struct _currentControllerVars_ {
	float Kp_id;			//This is for the FOC on the processor (e.g. for the ID run or for the calculated control gains from the GUI)
	float Tn_id;			//This is for the FOC on the processor (e.g. for the ID run or for the calculated control gains from the GUI)
	float Kp_iq;			//This is for the FOC on the processor (e.g. for the ID run or for the calculated control gains from the GUI)
	float Tn_iq;			//This is for the FOC on the processor (e.g. for the ID run or for the calculated control gains from the GUI)
	float Kp_id_Custom; 	//This is for an own FOC which is e.g. is running on the FPGA
	float Tn_id_Custom; 	//This is for an own FOC which is e.g. is running on the FPGA
	float Kp_iq_Custom; 	//This is for an own FOC which is e.g. is running on the FPGA
	float Tn_iq_Custom; 	//This is for an own FOC which is e.g. is running on the FPGA
	_Bool FOCFeedForward; //in order to activate a decoupling network
} currentControllerVars;

typedef struct _speedControllerVars_ {
	float Kp;			//This is for the FOC on the processor (e.g. for the ID run or for the calculated control gains from the GUI)
	float Tn;			//This is for the FOC on the processor (e.g. for the ID run or for the calculated control gains from the GUI)
	float Kp_Custom; 	//This is for an own FOC which is e.g. is running on the FPGA
	float Tn_Custom; 	//This is for an own FOC which is e.g. is running on the FPGA
	float referenceSpeedRamped;
} speedControllerVars;

typedef struct _fluxControllerVars_ {
	float Kp;			//This is for the FOC on the processor (e.g. for the ID run or for the calculated control gains from the GUI)
	float Tn;			//This is for the FOC on the processor (e.g. for the ID run or for the calculated control gains from the GUI)
	float Kp_Custom; 	//This is for an own FOC which is e.g. is running on the FPGA
	float Tn_Custom; 	//This is for an own FOC which is e.g. is running on the FPGA
} fluxControllerVars;

typedef struct _finiteControlSetVars_ {
	float lambda_dU;		//This weighting factor is to punish switching and therefore to minimize the switching frequency!
	float lambda_2;		//This weighting factor is to punish ...
	float lambda_3;		//This weighting factor is to punish ...
	float lambda_4;		//This weighting factor is to punish ...
	_Bool bEnableVSP2CC; //This is to activate the variable switching approach for FCS-MPC
} finiteControlSetVars;

typedef struct _continuousControlSetVars_ {
	float rw;			//This is the overall tuning factor
	float Np;			//This is the prediction horizon
	float Nc; 			//This is the control horizon
} continuousControlSetVars;

typedef struct _sixStepCommutationVars_ {
	currentControllerVars cc;
	float dutyCycle;
	float modifiedDutyCycle;
	float manualDutyCycle;
	float phaseAdvanceAngle;
	float iq_phaseAdvanceAngle;
	float iq_phaseAdvanceAngle_pu;
	float phaseAdvanceAnglePrescaler;
	float iq_phaseAdvanceAnglePrescaler;
	int16_t phaseAdvanceSectors;
	float dcLinkCurrent;
	float iq_dcLinkCurrent;
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
	float halfBridge1DutyCycle;
	float halfBridge2DutyCycle;
	float halfBridge3DutyCycle;
} halfBridgeControlVars;

typedef struct _modelPredictiveControlVars_ {
	finiteControlSetVars fcs;
	continuousControlSetVars ccs;
} modelPredictiveControlVars;

typedef struct _parameterIdentificationVars_ {
	//Automatic Current Reference Control for Online ID
	// Inputs
	_Bool bEnableAutoCurrentControl; //Flag enables Auto Current Reference Control
	float d_current_steps; 			// Amount of d_current_steps of Auto Current Reference Control
	float q_current_steps;			//Amount of q_current_steps of Auto Current Reference Control
	float max_res_ref_current;		// Maximum absolute current of Auto Current Reference Control

	//Outputs
	_Bool bRefAutomaticControlled;	//Flag recognizes when Auto Current Reference is activated
	float ParameterID_I_d;			// d-current based on dq-transformation on the processor (this is necessary, because the "fast" d-current comes from the FPGA into the av-Structure)
	float ParameterID_I_q;			// q-current based on dq-transformation on the processor (this is necessary, because the "fast" q-current comes from the FPGA into the av-Structure)

	//Offline ID Stateflow Inputs
	uint16_t  MotorID; 				//Enable parameter identification and chooses parameter being identified
	_Bool accept;				//Accept for Offline ID Stateflow
	_Bool reset_Offl;			//Reset for Offline ID Stateflow
	float sampleTimeISR;			//SampleTime of Offline ID Stateflow
	float dutyCyc;				//DutyCyc for Offline ID of R and L
	float n_ref_measurement; 	//speed for fluxconstant identification
	uint16_t  identLq;				// Flag for identifying Lq
	uint16_t  VibON;					// Adds Vibration for inertia identification
	float VibAmp;				// chooses amplitude of Vibration
	uint16_t  VibFreq;				// chooses frequency of vibration
	uint16_t  identR;				// Flag for Enabling Identification of R in Automated Measuring Mode
	uint16_t  AMM_ON;				// Activates Automated Measuring Mode in Offline ID Stateflow
	uint16_t  AMM_RUN;				// Recognizes if Automated Measuring Mode runs
	float IDstart;				// Start value of d-Current in Automated Measuring Mode
	float IDstop;				// Stop value of d-Current in Automated Measuring Mode
	float IDstepsize;			// Step size of d-Current steps in Automated Measuring Mode
	float IQstart;				// Start value of q-Current in Automated Measuring Mode
	float IQstop;				// Stop value of q-Current in Automated Measuring Mode
	float IQstepsize;			// Step size of d-Current in Automated Measuring Mode
	float LogIntervals;			// LogIntervals in Automated Measuring Mode
	uint32_t  NumberOfSamples;		// Amount of Samples in Automated Measuring Mode
	float settlingTime;			// Settlingtime of Automated Measuring Mode
	float n_visco_max;			// Maximum speed for viscous friction ID
	float N_Brk;					// Amount of Breakaway
	float Brk_Count;				// Counter for recognizing breakaway
	float N_visco;				// Amount of Measurement values of viscous friction ID
	float eta_omega_Reib;		// Threshold of steady State Recognizing in  viscous friction ID
	float StepScale;				// Size of Steps in Breakaway friction ID in Percent of rated Current
	uint16_t  f_min;					// Minimum identified frequency of two mass system ID
	uint16_t  f_max;					// Maximum identified frequency of two mass system ID
	float d_TMS_start;			// Startvalue of damping for two mass system ID
	float ScaleTorquePRBS;		// Amplitude of Pseudo Random Binary Noise Currentexcitation in A of q-Current
	float goertzlAmp;			// Amplitude of Sinus q-current Excitation for J-ident via Goertzl Algorithm

	//Online and Offline ID Stateflow Inputs
	float identRAmp;				// d-Current Step Amplitude for R-Identification in ONLINE and OFFLINE ID
	float Temp_ref;				// Reference Temperature for Reference Resistance

	//Online ID Stateflow Inputs
	_Bool bEnableOnlineID;		// Enable Online ID
	float DevSpeed;				// Threshold for SteadyStateDetection in percent of actual Value
	float DevCurrent;			// Threshold for SteadyStateDetection in percent of actual Value
	uint16_t  AverageTransParams;	// En/Disables Averaging of Online Parameters (Debug)
	uint16_t  AllowStepFlag;			// Allows d-Current step in steady state
	uint16_t  ResetOnline;			// Reset all Online ID values


	//Offline ID Stateflow Outputs
	uint16_t  activeState;			//active State of Offline ID Stateflow
	uint16_t  offsetLock;			// offset Lock of identified mechanical encoder offset
	float array_counter;			// counter for array slow data communication of Mech ID Plot
	uint16_t  controlArrCounter;		// controlcounter for successful communication
	_Bool AdmitParamsFlag; 		// Set electrical identified Parameters as motor related ones
	_Bool AdmitMechParamsFlag;	// Set mechanical identified Parameters as motor related ones
	float Offline_Ld;			// Offline identified L_d inductance
	float Offline_Lq;			// Offline identified L_q inductance
	float Offline_Rs;			// Offline identified R_ph resistance
	float Offline_Psi_PM;					// Offline identified psi_pm flux constant
	float Offline_polePairs;					// Offline identified pole pairs
	float Offline_motorRotorInertia;			// Rotorinertia on Motorside
	float Offline_loadRotorInertia;			// Rotorinertia on Loadside
	float Offline_totalRotorInertia;			// Motor+Load Rotorinertia
	float Offline_TwoMassSystemStiffness;	// rotational torsion stiffness of drivetrain considered as two mass system
	float Offline_TwoMassSystemDamping;		// rotational torsion damping of drivetrain considered as two mass system
	float Offline_BreakawayTorque;			// Breakawaytorque in Nm
	float Offline_CoulombFriction;			// Coulombfriction in Nm
	float Offline_ViscousFriction;			// Viscous Frictioncoefficient in Nms
	float Offline_TwoMassSystem_c_0;
	float Offline_ud_ref;			// Reference voltage from the FOC inside the Parameter Identification
	float Offline_uq_ref;			// Reference voltage from the FOC inside the Parameter Identification


	// Online ID Stateflow Outputs
	_Bool bOnlineIDenabled; 			//recognize if online ID is enabled
	float map_counter;				//counter for array slow data communication of flux maps
	uint16_t  ControlMapCounter;			// controlcounter for successful fluxmapcommunication
	float WindingTemp;				// WindingTemp of Online ID
	float Online_Ld;					// in mH : Online identified L_d inductance
	float Online_Lq;					// in mH : Online identified L_q inductance
	float Online_Rs;					// in mOhm : Online identified R_ph resistance
	float Online_Psi_PM;				// in mVs : Online identified psi_pm flux constant

	// Interpolation of Flux Maps
	float psi_array[600];			// Storage of Flux mesurement values
	float FluxMap_d[400];			// Map of d-Flux
	float xAxis_FluxMap_d[20];		// x-Axis of d-Flux Map
	float yAxis_FluxMap_d[20];		// y-Axis of d-Flux Map
	float FluxMap_q[400];			// Map of q-Flux
	float xAxis_FluxMap_q[20];		// x-Axis of q-Flux Map
	float yAxis_FluxMap_q[20];		// y-Axis of q-Flux Map
	float InvFluxMap_d[400];			// d-Current Map
	float xAxis_InvFluxMap_d[20];	// x-Axis of d-Current Map
	float yAxis_InvFluxMap_d[20];	// y-Axis of d-Current Map
	float InvFluxMap_q[400];			// q-Curret Map
	float xAxis_InvFluxMap_q[20];	// x-Axis of q-Current Map
	float yAxis_InvFluxMap_q[20];	// y-Axis of q-Current Map
	float *FluxpointerUncleaned;		// Pointer to uncleaned Psi-Array
	float *FluxpointerCleaned;		// Pointer to cleaned Psi-Array
	float *FluxTempPointer;			// Pointer to Array with Delta T-Delta Psi Values
	float FluxTemp[200];				// Array eith Delta T - Delta Psi values
	float FluxTempConst;				// Calculated Constant of Temperaturedependency of FluxConstant
	float FluxTempError;				// Error of calculated FluxConstant at Temp_ref
	_Bool bCleanPsiArray;			// Flag for cleaning Psi arrays from similar values
	_Bool bPsiArrayCleaned;			// Flag that recognizes a cleaned Psi_array
	float n_FluxPoints;				// Amount of independend Flux Measuring Points
	float eta_curr;					// Threshold for similar Measuring Points
	_Bool bCalcPsi;					// Flag for Refreshing Flux Maps
	float Online_MessArray_Element; 	// One Element of the "measArray1" for the data transfer of the online identified data
	float Online_i_est_Element;		// One Element of the "i_est" for the data transfer of the online identified data
} parameterIdentificationVars;

typedef struct _controllerVars_ {
	sixStepCommutationVars ssc;
	fieldOrientedControlVars foc;
	halfBridgeControlVars hbc;
	modelPredictiveControlVars mpc;
	float pwmFrequency;
	float pwmPeriod;
	float samplingPeriod;
	float samplingFrequency;
	float dcLinkVoltage;
	float terminalCurrents[3];
	float terminalVoltages[3];
	_Bool  ctrlObjectReinitRequest;
	float FullScaleCurrent_IQ_A;	// PL 19.12.2017 Welchem float-Wert entspricht der Full-Scale-IQ Faktor? = USER_IQ_FULL_SCALE_CURRENT_A aus user.h
	float OneOverFullScaleCurrent_IQ_A; // PL 19.12.2017 1 / (USER_IQ_FULL_SCALE_CURRENT_A) aus user.h
	float FullScaleVoltage_IQ_V;	// PL 19.12.2017 Welchem float-Wert entspricht der Full-Scale-IQ Faktor? = USER_IQ_FULL_SCALE_VOLTAGE_V aus user.h
} controllerVars;

typedef struct _debugVariables_ {
	uint32_t  counter;
	float finalReferenceCurrent;
	float controlError;
	float referenceSpeedLimited;
	float positionWithPhaseAdvance;
	uint32_t  timeStampCounter;
	uint32_t isrCyclesFor10Millisec;
	int sw1;
	int sw2;
	int sw3;
	int ADC_scope_display;
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
	DigitalAdapters da;
	struct uz_d_gan_inverter_outputs_t outs_of_D4;
	struct uz_d_gan_inverter_outputs_t outs_of_D3;
} DS_Data;

#endif

