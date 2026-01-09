//APU_RPU_shared.h

#pragma once

// OCM Bank 3 starts at         0xFFFF0000
// See UG1085 page 533 (https://www.xilinx.com/support/documentation/user_guides/ug1085-zynq-ultrascale-trm.pdf#G20.375357)

#define MEM_SHARED_START 	0xFFFF0000
#define JS_CHANNELS 		20

// update by hand when changing JS_CHANNELS
// Bank 3 of OCM has 64 KB, thus a maximum of 16K float values can be stored
#define JAVASCOPE_DATA_SIZE_2POW  	128

/* OCM Bank 3 memory for application specific data exchange variables
 *    Note: maximum struct size must not exceed 256 Byte (0x900 - 0x800) --> 64x 32 Bit variables
 *    If more variables are necessary the following range has to be adapted.
 *    Reserved memory range:
 *      - APU --> RPU: 0xFFFF0800 - 0xFFFF08FF
 *      - RPU --> APU: 0xFFFF0900 - 0xFFFF09FF
 *    */
#define MEM_SHARED_START_APP_A2R	MEM_SHARED_START + 0x800
#define MEM_SHARED_START_APP_R2A	MEM_SHARED_START + 0x900

struct javascope_data_t
{
	uint32_t    status;
	float	    slowDataContent;
	uint32_t    slowDataID;
	float       scope_ch[JS_CHANNELS];
};

struct APU_to_RPU_t
{
	uint32_t id;
	float value;
};

// Unidirectional data transfer A53 (APU) -> R5 (RPU)
struct data_A2R_t
{
	uint8_t State_Request;
	float Torque_Request;
	float Torque_Limit_Pos;
	float Torque_Limit_Neg;
	float Speed_Request;
	uint8_t Shutdown_Request;
	float MeasValue_Speed_Actual;
	float MeasValue_Torque_Actual;
	uint32_t LifeCheck_Cnt_A2R;
};

// Unidirectional data transfer R5 (RPU) -> A53 (APU)
struct data_R2A_t
{
	float Torque_Actual;
	float Speed_Actual;
	float Voltage_DC_Link;
	uint8_t SysState_Actual;
	uint8_t SysState_Requested;
	uint8_t SysState_Ack;
	uint32_t Diag_GateDriver_Status;
	uint32_t Diag_Limits_Status;
	uint32_t Diag_Warning_Status;
	float Temp_Inv_Phase_1;
	float Temp_Inv_Phase_2;
	float Temp_Inv_Phase_3;
	float Temp_Inv_Phase_4;
	float Temp_Inv_Phase_5;
	float Temp_Inv_Phase_6;
	float Temp_Mot_Phase_1;
	float Temp_Mot_Phase_2;
	float Temp_Mot_Phase_3;
	float Temp_Mot_Phase_4;
	float Temp_Mot_Phase_5;
	float Temp_Mot_Phase_6;
	uint32_t LifeCheck_Cnt_R2A;
};
