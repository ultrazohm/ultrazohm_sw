/*
 * MAX11331.h
 *
 *  Created on: 05.03.2021
 *      Author: Thomas Kreppel
 */

#ifndef SRC_INCLUDE_MAX11331_H_
#define SRC_INCLUDE_MAX11331_H_

#include "xgpio.h"
#include "xstatus.h"
#include "xil_types.h" 									//Include for Datatypes
#include "../IP_Cores/ADC_max11331_AXI.h"
#include "../defines.h"

#define A2_MAX11331_1_AXIADDR XPAR_A2_MAX11331_ADC_MAX11331_1_S_AXI_LITE_BASEADDR
#define A2_MAX11331_2_AXIADDR XPAR_A2_MAX11331_ADC_MAX11331_2_S_AXI_LITE_BASEADDR
#define A2_MAX11331_3_AXIADDR XPAR_A2_MAX11331_ADC_MAX11331_3_S_AXI_LITE_BASEADDR
#define A2_MAX11331_RESET_ID  XPAR_A2_MAX11331_AXI_GPIO_RESET_A2_DEVICE_ID
#define RESET_SLOT_1 0x01
#define RESET_SLOT_2 0x04
#define RESET_SLOT_3 0x10
#define ENABLE_SLOT_1 0x02
#define ENABLE_SLOT_2 0x08
#define ENABLE_SLOT_3 0x20
#define GPIO_CHANNEL_1 1
#define GPIO_CHANNEL_2 2

//TCM register address
#define MAX11331_1_TCM_BASEADDR	0x20020
#define MAX11331_2_TCM_BASEADDR 0x20060
#define MAX11331_3_TCM_BASEADDR 0x200A0

// ADC offsets
// Slot 1
#define SLOT1_ADC1_J1_CH1_OFFSET 0
#define SLOT1_ADC1_J1_CH2_OFFSET 0
#define SLOT1_ADC1_J1_CH3_OFFSET 0
#define SLOT1_ADC1_J1_CH4_OFFSET 0
#define SLOT1_ADC1_J2_CH1_OFFSET 0
#define SLOT1_ADC1_J2_CH2_OFFSET 0
#define SLOT1_ADC1_J2_CH3_OFFSET 0
#define SLOT1_ADC1_J2_CH4_OFFSET 0
#define SLOT1_ADC2_J1_CH1_OFFSET 0
#define SLOT1_ADC2_J1_CH2_OFFSET 0
#define SLOT1_ADC2_J1_CH3_OFFSET 0
#define SLOT1_ADC2_J1_CH4_OFFSET 0
#define SLOT1_ADC2_J2_CH1_OFFSET 0
#define SLOT1_ADC2_J2_CH2_OFFSET 0
#define SLOT1_ADC2_J2_CH3_OFFSET 0
#define SLOT1_ADC2_J2_CH4_OFFSET 0
#define SLOT1_ADC3_J1_CH1_OFFSET 0
#define SLOT1_ADC3_J1_CH2_OFFSET 0
#define SLOT1_ADC3_J1_CH3_OFFSET 0
#define SLOT1_ADC3_J1_CH4_OFFSET 0
#define SLOT1_ADC3_J2_CH1_OFFSET 0
#define SLOT1_ADC3_J2_CH2_OFFSET 0
#define SLOT1_ADC3_J2_CH3_OFFSET 0
#define SLOT1_ADC3_J2_CH4_OFFSET 0
#define SLOT1_ADC4_J1_CH1_OFFSET 0
#define SLOT1_ADC4_J1_CH2_OFFSET 0
#define SLOT1_ADC4_J1_CH3_OFFSET 0
#define SLOT1_ADC4_J1_CH4_OFFSET 0
#define SLOT1_ADC4_J2_CH1_OFFSET 0
#define SLOT1_ADC4_J2_CH2_OFFSET 0
#define SLOT1_ADC4_J2_CH3_OFFSET 0
#define SLOT1_ADC4_J2_CH4_OFFSET 0
// Slot 2
#define SLOT2_ADC1_J1_CH1_OFFSET 0
#define SLOT2_ADC1_J1_CH2_OFFSET 0
#define SLOT2_ADC1_J1_CH3_OFFSET 0
#define SLOT2_ADC1_J1_CH4_OFFSET 0
#define SLOT2_ADC1_J2_CH1_OFFSET 0
#define SLOT2_ADC1_J2_CH2_OFFSET 0
#define SLOT2_ADC1_J2_CH3_OFFSET 0
#define SLOT2_ADC1_J2_CH4_OFFSET 0
#define SLOT2_ADC2_J1_CH1_OFFSET 0
#define SLOT2_ADC2_J1_CH2_OFFSET 0
#define SLOT2_ADC2_J1_CH3_OFFSET 0
#define SLOT2_ADC2_J1_CH4_OFFSET 0
#define SLOT2_ADC2_J2_CH1_OFFSET 0
#define SLOT2_ADC2_J2_CH2_OFFSET 0
#define SLOT2_ADC2_J2_CH3_OFFSET 0
#define SLOT2_ADC2_J2_CH4_OFFSET 0
#define SLOT2_ADC3_J1_CH1_OFFSET 0
#define SLOT2_ADC3_J1_CH2_OFFSET 0
#define SLOT2_ADC3_J1_CH3_OFFSET 0
#define SLOT2_ADC3_J1_CH4_OFFSET 0
#define SLOT2_ADC3_J2_CH1_OFFSET 0
#define SLOT2_ADC3_J2_CH2_OFFSET 0
#define SLOT2_ADC3_J2_CH3_OFFSET 0
#define SLOT2_ADC3_J2_CH4_OFFSET 0
#define SLOT2_ADC4_J1_CH1_OFFSET 0
#define SLOT2_ADC4_J1_CH2_OFFSET 0
#define SLOT2_ADC4_J1_CH3_OFFSET 0
#define SLOT2_ADC4_J1_CH4_OFFSET 0
#define SLOT2_ADC4_J2_CH1_OFFSET 0
#define SLOT2_ADC4_J2_CH2_OFFSET 0
#define SLOT2_ADC4_J2_CH3_OFFSET 0
#define SLOT2_ADC4_J2_CH4_OFFSET 0
// Slot 3
#define SLOT3_ADC1_J1_CH1_OFFSET 0
#define SLOT3_ADC1_J1_CH2_OFFSET 0
#define SLOT3_ADC1_J1_CH3_OFFSET 0
#define SLOT3_ADC1_J1_CH4_OFFSET 0
#define SLOT3_ADC1_J2_CH1_OFFSET 0
#define SLOT3_ADC1_J2_CH2_OFFSET 0
#define SLOT3_ADC1_J2_CH3_OFFSET 0
#define SLOT3_ADC1_J2_CH4_OFFSET 0
#define SLOT3_ADC2_J1_CH1_OFFSET 0
#define SLOT3_ADC2_J1_CH2_OFFSET 0
#define SLOT3_ADC2_J1_CH3_OFFSET 0
#define SLOT3_ADC2_J1_CH4_OFFSET 0
#define SLOT3_ADC2_J2_CH1_OFFSET 0
#define SLOT3_ADC2_J2_CH2_OFFSET 0
#define SLOT3_ADC2_J2_CH3_OFFSET 0
#define SLOT3_ADC2_J2_CH4_OFFSET 0
#define SLOT3_ADC3_J1_CH1_OFFSET 0
#define SLOT3_ADC3_J1_CH2_OFFSET 0
#define SLOT3_ADC3_J1_CH3_OFFSET 0
#define SLOT3_ADC3_J1_CH4_OFFSET 0
#define SLOT3_ADC3_J2_CH1_OFFSET 0
#define SLOT3_ADC3_J2_CH2_OFFSET 0
#define SLOT3_ADC3_J2_CH3_OFFSET 0
#define SLOT3_ADC3_J2_CH4_OFFSET 0
#define SLOT3_ADC4_J1_CH1_OFFSET 0
#define SLOT3_ADC4_J1_CH2_OFFSET 0
#define SLOT3_ADC4_J1_CH3_OFFSET 0
#define SLOT3_ADC4_J1_CH4_OFFSET 0
#define SLOT3_ADC4_J2_CH1_OFFSET 0
#define SLOT3_ADC4_J2_CH2_OFFSET 0
#define SLOT3_ADC4_J2_CH3_OFFSET 0
#define SLOT3_ADC4_J2_CH4_OFFSET 0

#define MAX11331_CONVERSION_FACTOR (1.0f/30)

/*********************************************************************
 * MAX11331 type definitions, for ADC, daughter board and adapter slot
 **********************************************************************/
typedef struct max11331 {
	u16 	config_bipolar;
	u16 	config_unipolar;
	int16_t	Data_raw[8];
	float 	Data[8];
	int16_t offset[8];
} MAX11331;

typedef enum SCLK_freq {f_50MHz=0x01,f_25MHz=0x02,f_16_67MHz=0x03,f_12_5MHz=0x04,f_6_25MHz=0x08} SCLK_freq;

typedef struct max11331_daughter_board{
	// Slot specific parameter
	//slot_number slot_id;
	const u32 AXI_BASEADDR;
	const u32 RESET_MASK;
	const u32 ENABLE_MASK;
	const u32 TCM_BASEADDR;
	// Status & general parameter
	ADCstatus status;
	SCLK_freq f_clk;
	u32 error_counter;
	u32 ADC_select;
	float conversion_factor;
	// ADC data objects
	MAX11331 ADC1;
	MAX11331 ADC2;
	MAX11331 ADC3;
	MAX11331 ADC4;
} MAX11331_Daughter_Board;

// Declare driver objects to make them globally available
extern MAX11331_Daughter_Board slot_1;
extern MAX11331_Daughter_Board slot_2;
extern MAX11331_Daughter_Board slot_3;

/*********************************************************************
 * MAX11331 interface functions declaration
 *********************************************************************/
int AnalogAdapter_A2_Initialize();
//void Config_Daughter_Board(MAX11331_Daughter_Board* slot,SCLK_freq f,u32 ADC_select);
void Config_Daughter_Board_1(SCLK_freq f, u32 ADC_select);
void Config_Daughter_Board_2(SCLK_freq f, u32 ADC_select);
void Config_Daughter_Board_3(SCLK_freq f, u32 ADC_select);
//void Reset_Daughter_Board(MAX11331_Daughter_Board* slot);
void Reset_Daughter_Board_1();
void Reset_Daughter_Board_2();
void Reset_Daughter_Board_3();
//void Update_Values(MAX11331_Daughter_Board* slot);
void Update_Values_Board_1();
void Update_Values_Board_2();
void Update_Values_Board_3();
ADCstatus Board_1_Status();
ADCstatus Board_2_Status();
ADCstatus Board_3_Status();
#endif /* SRC_INCLUDE_MAX11331_H_ */
