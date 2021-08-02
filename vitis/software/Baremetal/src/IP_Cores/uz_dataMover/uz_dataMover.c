#include "uz_dataMover.h"
#include "uz_dataMover_hwAddresses.h"

// Hard coded base-addresses
#define R5_0_BTCM_SPLIT_REG	0x20000
// ADC Card Slot A1
#define ADC_A1_ChA1_REG		(R5_0_BTCM_SPLIT_REG + 0x00)
#define ADC_A1_ChA2_REG		(R5_0_BTCM_SPLIT_REG + 0x02)
#define ADC_A1_ChA3_REG		(R5_0_BTCM_SPLIT_REG + 0x04)
#define ADC_A1_ChA4_REG		(R5_0_BTCM_SPLIT_REG + 0x06)

#define ADC_A1_ChB5_REG		(R5_0_BTCM_SPLIT_REG + 0x08)
#define ADC_A1_ChB6_REG		(R5_0_BTCM_SPLIT_REG + 0x0A)
#define ADC_A1_ChB7_REG		(R5_0_BTCM_SPLIT_REG + 0x0C)
#define ADC_A1_ChB8_REG		(R5_0_BTCM_SPLIT_REG + 0x0E)

// ADC Card Slot
#define ADC_A2_ChA1_REG		(R5_0_BTCM_SPLIT_REG + 0x10)
#define ADC_A2_ChA2_REG		(R5_0_BTCM_SPLIT_REG + 0x12)
#define ADC_A2_ChA3_REG		(R5_0_BTCM_SPLIT_REG + 0x14)
#define ADC_A2_ChA4_REG		(R5_0_BTCM_SPLIT_REG + 0x16)

#define ADC_A2_ChB5_REG		(R5_0_BTCM_SPLIT_REG + 0x18)
#define ADC_A2_ChB6_REG		(R5_0_BTCM_SPLIT_REG + 0x1A)
#define ADC_A2_ChB7_REG		(R5_0_BTCM_SPLIT_REG + 0x1C)
#define ADC_A2_ChB8_REG		(R5_0_BTCM_SPLIT_REG + 0x1E)

// ADC Card Slot 
#define ADC_A3_ChA1_REG		(R5_0_BTCM_SPLIT_REG + 0x20)
#define ADC_A3_ChA2_REG		(R5_0_BTCM_SPLIT_REG + 0x22)
#define ADC_A3_ChA3_REG		(R5_0_BTCM_SPLIT_REG + 0x24)
#define ADC_A3_ChA4_REG		(R5_0_BTCM_SPLIT_REG + 0x26)

#define ADC_A3_ChB5_REG		(R5_0_BTCM_SPLIT_REG + 0x28)
#define ADC_A3_ChB6_REG		(R5_0_BTCM_SPLIT_REG + 0x2A)
#define ADC_A3_ChB7_REG		(R5_0_BTCM_SPLIT_REG + 0x2C)
#define ADC_A3_ChB8_REG		(R5_0_BTCM_SPLIT_REG + 0x2E)

// Number of elements in one array
#define UZ_DATAMOVER_ARRAY_LENGTH 8

static int16_t buffer[UZ_DATAMOVER_ARRAY_LENGTH]={0};

void uz_dataMover_initialize(void){
    
    }

uz_array_float_t uz_dataMover_get_data(void){
    buffer[0] = Xil_In16(ADC_A2_ChA1_REG);
	buffer[1] = Xil_In16(ADC_A2_ChA2_REG);
	buffer[2] = Xil_In16(ADC_A2_ChA3_REG);
	buffer[3] = Xil_In16(ADC_A2_ChA4_REG);
	buffer[4] = Xil_In16(ADC_A2_ChB5_REG);
	buffer[5] = Xil_In16(ADC_A2_ChB6_REG);
	buffer[6] = Xil_In16(ADC_A2_ChB7_REG);
	buffer[7] = Xil_In16(ADC_A2_ChB8_REG);
    uz_array_float_t data_array={
        .length=UZ_ARRAY_SIZE(buffer),
        .data=&buffer[0]
    };
    return data_array;
}