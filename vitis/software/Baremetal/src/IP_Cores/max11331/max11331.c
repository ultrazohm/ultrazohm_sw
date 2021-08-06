///*
// * max11331.c
// *
// *  Created on: 14.10.2020
// *      Author: Thomas Kreppel
// */
//
//#include "../include/max11331.h"
//#include "max11331_defines.h"
//
//
///*
// * Daughter Board driver instances
// * Parameter are accessed with interface functions (e.g. Config_Daughter_Board_1...)
// */
//MAX11331_Daughter_Board slot_1 = {
//		.AXI_BASEADDR = A2_MAX11331_1_AXIADDR,
//		.RESET_MASK = RESET_SLOT_1,
//		.ENABLE_MASK = ENABLE_SLOT_1,
//		.TCM_BASEADDR = MAX11331_1_TCM_BASEADDR,
//		.status = adc_disabled,
//		.conversion_factor = MAX11331_CONVERSION_FACTOR,
//		.ADC1.offset = {
//				SLOT1_ADC1_J1_CH1_OFFSET,
//				SLOT1_ADC1_J1_CH2_OFFSET,
//				SLOT1_ADC1_J1_CH3_OFFSET,
//				SLOT1_ADC1_J1_CH4_OFFSET,
//				SLOT1_ADC1_J2_CH1_OFFSET,
//				SLOT1_ADC1_J2_CH2_OFFSET,
//				SLOT1_ADC1_J2_CH3_OFFSET,
//				SLOT1_ADC1_J2_CH4_OFFSET
//		},
//		.ADC2.offset = {
//				SLOT1_ADC2_J1_CH1_OFFSET,
//				SLOT1_ADC2_J1_CH2_OFFSET,
//				SLOT1_ADC2_J1_CH3_OFFSET,
//				SLOT1_ADC2_J1_CH4_OFFSET,
//				SLOT1_ADC2_J2_CH1_OFFSET,
//				SLOT1_ADC2_J2_CH2_OFFSET,
//				SLOT1_ADC2_J2_CH3_OFFSET,
//				SLOT1_ADC2_J2_CH4_OFFSET
//		},
//		.ADC3.offset = {
//				SLOT1_ADC3_J1_CH1_OFFSET,
//				SLOT1_ADC3_J1_CH2_OFFSET,
//				SLOT1_ADC3_J1_CH3_OFFSET,
//				SLOT1_ADC3_J1_CH4_OFFSET,
//				SLOT1_ADC3_J2_CH1_OFFSET,
//				SLOT1_ADC3_J2_CH2_OFFSET,
//				SLOT1_ADC3_J2_CH3_OFFSET,
//				SLOT1_ADC3_J2_CH4_OFFSET
//		},
//		.ADC4.offset = {
//				SLOT1_ADC4_J1_CH1_OFFSET,
//				SLOT1_ADC4_J1_CH2_OFFSET,
//				SLOT1_ADC4_J1_CH3_OFFSET,
//				SLOT1_ADC4_J1_CH4_OFFSET,
//				SLOT1_ADC4_J2_CH1_OFFSET,
//				SLOT1_ADC4_J2_CH2_OFFSET,
//				SLOT1_ADC4_J2_CH3_OFFSET,
//				SLOT1_ADC4_J2_CH4_OFFSET
//		}
//};
//MAX11331_Daughter_Board slot_2 = {
//		.AXI_BASEADDR = A2_MAX11331_2_AXIADDR,
//		.RESET_MASK = RESET_SLOT_2,
//		.ENABLE_MASK = ENABLE_SLOT_2,
//		.TCM_BASEADDR = MAX11331_2_TCM_BASEADDR,
//		.status = adc_disabled,
//		.conversion_factor = MAX11331_CONVERSION_FACTOR,
//		.ADC1.offset = {
//				SLOT2_ADC1_J1_CH1_OFFSET,
//				SLOT2_ADC1_J1_CH2_OFFSET,
//				SLOT2_ADC1_J1_CH3_OFFSET,
//				SLOT2_ADC1_J1_CH4_OFFSET,
//				SLOT2_ADC1_J2_CH1_OFFSET,
//				SLOT2_ADC1_J2_CH2_OFFSET,
//				SLOT2_ADC1_J2_CH3_OFFSET,
//				SLOT2_ADC1_J2_CH4_OFFSET
//		},
//		.ADC2.offset = {
//				SLOT2_ADC2_J1_CH1_OFFSET,
//				SLOT2_ADC2_J1_CH2_OFFSET,
//				SLOT2_ADC2_J1_CH3_OFFSET,
//				SLOT2_ADC2_J1_CH4_OFFSET,
//				SLOT2_ADC2_J2_CH1_OFFSET,
//				SLOT2_ADC2_J2_CH2_OFFSET,
//				SLOT2_ADC2_J2_CH3_OFFSET,
//				SLOT2_ADC2_J2_CH4_OFFSET
//		},
//		.ADC3.offset = {
//				SLOT2_ADC3_J1_CH1_OFFSET,
//				SLOT2_ADC3_J1_CH2_OFFSET,
//				SLOT2_ADC3_J1_CH3_OFFSET,
//				SLOT2_ADC3_J1_CH4_OFFSET,
//				SLOT2_ADC3_J2_CH1_OFFSET,
//				SLOT2_ADC3_J2_CH2_OFFSET,
//				SLOT2_ADC3_J2_CH3_OFFSET,
//				SLOT2_ADC3_J2_CH4_OFFSET
//		},
//		.ADC4.offset = {
//				SLOT2_ADC4_J1_CH1_OFFSET,
//				SLOT2_ADC4_J1_CH2_OFFSET,
//				SLOT2_ADC4_J1_CH3_OFFSET,
//				SLOT2_ADC4_J1_CH4_OFFSET,
//				SLOT2_ADC4_J2_CH1_OFFSET,
//				SLOT2_ADC4_J2_CH2_OFFSET,
//				SLOT2_ADC4_J2_CH3_OFFSET,
//				SLOT2_ADC4_J2_CH4_OFFSET
//		}
//};
//MAX11331_Daughter_Board slot_3 = {
//		.AXI_BASEADDR = A2_MAX11331_3_AXIADDR,
//		.RESET_MASK = RESET_SLOT_3,
//		.ENABLE_MASK = ENABLE_SLOT_3,
//		.TCM_BASEADDR = MAX11331_3_TCM_BASEADDR,
//		.status = adc_disabled,
//		.conversion_factor = MAX11331_CONVERSION_FACTOR,
//		.ADC1.offset = {
//				SLOT3_ADC1_J1_CH1_OFFSET,
//				SLOT3_ADC1_J1_CH2_OFFSET,
//				SLOT3_ADC1_J1_CH3_OFFSET,
//				SLOT3_ADC1_J1_CH4_OFFSET,
//				SLOT3_ADC1_J2_CH1_OFFSET,
//				SLOT3_ADC1_J2_CH2_OFFSET,
//				SLOT3_ADC1_J2_CH3_OFFSET,
//				SLOT3_ADC1_J2_CH4_OFFSET
//		},
//		.ADC2.offset = {
//				SLOT3_ADC2_J1_CH1_OFFSET,
//				SLOT3_ADC2_J1_CH2_OFFSET,
//				SLOT3_ADC2_J1_CH3_OFFSET,
//				SLOT3_ADC2_J1_CH4_OFFSET,
//				SLOT3_ADC2_J2_CH1_OFFSET,
//				SLOT3_ADC2_J2_CH2_OFFSET,
//				SLOT3_ADC2_J2_CH3_OFFSET,
//				SLOT3_ADC2_J2_CH4_OFFSET
//		},
//		.ADC3.offset = {
//				SLOT3_ADC3_J1_CH1_OFFSET,
//				SLOT3_ADC3_J1_CH2_OFFSET,
//				SLOT3_ADC3_J1_CH3_OFFSET,
//				SLOT3_ADC3_J1_CH4_OFFSET,
//				SLOT3_ADC3_J2_CH1_OFFSET,
//				SLOT3_ADC3_J2_CH2_OFFSET,
//				SLOT3_ADC3_J2_CH3_OFFSET,
//				SLOT3_ADC3_J2_CH4_OFFSET
//		},
//		.ADC4.offset = {
//				SLOT3_ADC4_J1_CH1_OFFSET,
//				SLOT3_ADC4_J1_CH2_OFFSET,
//				SLOT3_ADC4_J1_CH3_OFFSET,
//				SLOT3_ADC4_J1_CH4_OFFSET,
//				SLOT3_ADC4_J2_CH1_OFFSET,
//				SLOT3_ADC4_J2_CH2_OFFSET,
//				SLOT3_ADC4_J2_CH3_OFFSET,
//				SLOT3_ADC4_J2_CH4_OFFSET
//		}
//};
////AXI GPIO driver instance
//static XGpio A2_Reset;
//
///* Adapter A2 initialization
// * 	- AXI GPIO for reset and enable signals
// */
//int AnalogAdapter_A2_Initialize() {
//	int status;
//	// Initialize XGpio for MAX11331
//	status = XGpio_Initialize(&A2_Reset, A2_MAX11331_RESET_ID);
//	if(status != XST_SUCCESS){
//		xil_printf("Initialization of GPIO failed. Xstatus = %d",status);
//		return status;
//	}
//	XGpio_SetDataDirection(&A2_Reset, GPIO_CHANNEL_1,0x00);
//	status = XGpio_SelfTest(&A2_Reset);
//	if(status != XST_SUCCESS){
//		xil_printf("Self Test of GPIO failed. Xstatus = %d",status);
//		return status;
//	}
//
//	return status;
//}
//
///* private Daughter Board configuration function
// * 	- sets SCLK frequency
// * 	- select active ADCs
// */
//void Config_Daughter_Board(MAX11331_Daughter_Board* self,SCLK_freq f,u32 ADC_select) {
//	self->f_clk = f;
//	self->ADC_select = ADC_select;
//}
//
///*
// * Public interface functions
// */
//void Config_Daughter_Board_1(SCLK_freq f, u32 ADC_select) {
//	Config_Daughter_Board(&slot_1,f,ADC_select);
//}
//
//void Config_Daughter_Board_2(SCLK_freq f, u32 ADC_select) {
//	Config_Daughter_Board(&slot_2,f,ADC_select);
//}
//
//void Config_Daughter_Board_3(SCLK_freq f, u32 ADC_select) {
//	Config_Daughter_Board(&slot_3,f,ADC_select);
//}
//
//void Reset_Daughter_Board(MAX11331_Daughter_Board* self) {
//	u32 temp = 0;
//	int status;
//
//	self->status = adc_init;
//
//	self->error_counter = 0;
//
//	// Reset MAX11331 IP core
//	XGpio_DiscreteClear(&A2_Reset, GPIO_CHANNEL_1, self->RESET_MASK | self->ENABLE_MASK);
//	ADC_MAX11331_AXI_mWriteReg(self->AXI_BASEADDR, MAX11331_ADC_SELECTOR_OFFSET, self->ADC_select);
//	ADC_MAX11331_AXI_mWriteReg(self->AXI_BASEADDR, MAX11331_CLK_DIVISION_OFFSET, self->f_clk);
//	XGpio_DiscreteSet(&A2_Reset, GPIO_CHANNEL_1, self->RESET_MASK | self->ENABLE_MASK);
//
//	do{
//		status = ADC_MAX11331_AXI_mReadReg(self->AXI_BASEADDR, MAX11331_STATUS_OFFSET);
//		// init ready
//		if(status & 0x00000001) self->status = adc_ready;
//		// ADC_meas_done = (status & 0x00000100) >> 8;
//		if(status & 0x00010000) {
//			self->status = adc_error;
//			self->error_counter = ADC_MAX11331_AXI_mReadReg(self->AXI_BASEADDR, MAX11331_ERROR_COUNTER_OFFSET);
//			return;
//		}
//
//		temp = ADC_MAX11331_AXI_mReadReg(self->AXI_BASEADDR, MAX11331_ECHOED_BIPOLAR_12_OFFSET);
//			self->ADC1.config_bipolar = temp & 0x0000FFFF;		//expect 0x97f8
//			self->ADC2.config_bipolar = (temp & 0xFFFF0000) >> 16;
//		temp = ADC_MAX11331_AXI_mReadReg(self->AXI_BASEADDR, MAX11331_ECHOED_BIPOLAR_34_OFFSET);
//			self->ADC3.config_bipolar = temp & 0x0000FFFF;
//			self->ADC4.config_bipolar = (temp & 0xFFFF0000) >> 16;
//
//		temp = ADC_MAX11331_AXI_mReadReg(self->AXI_BASEADDR, MAX11331_ECHOED_UNIPOLAR_12_OFFSET);
//			self->ADC1.config_unipolar = temp & 0x0000FFFF;	//expect 0x8800
//			self->ADC2.config_unipolar = (temp & 0xFFFF0000) >> 16;
//		temp = ADC_MAX11331_AXI_mReadReg(self->AXI_BASEADDR, MAX11331_ECHOED_UNIPOLAR_34_OFFSET);
//			self->ADC3.config_unipolar = temp & 0x0000FFFF;
//			self->ADC4.config_unipolar = (temp & 0xFFFF0000) >> 16;
//
//	} while(self->status != adc_ready);
//}
//
//void Reset_Daughter_Board_1() {
//	Reset_Daughter_Board(&slot_1);
//}
//
//void Reset_Daughter_Board_2() {
//	Reset_Daughter_Board(&slot_2);
//}
//
//void Reset_Daughter_Board_3() {
//	Reset_Daughter_Board(&slot_3);
//}
//
//void Update_Values(MAX11331_Daughter_Board* self) {
//	int error;
//
//	self->status = adc_reading_data;
//
//	// Error evaluation
//	// The error counter of the driver ip core is read and compared to the the counter of the C driver,
//	// to detect if an error between now and the last time the counter was evaluated, happened
//	error = ADC_MAX11331_AXI_mReadReg(self->AXI_BASEADDR, MAX11331_ERROR_COUNTER_OFFSET);
//	if(self->error_counter != error) {
//		// error detected
//		self->status = adc_error;
//		self->error_counter = error;
//		return;
//	}
//
//	//Read ADC values from Tightly Coupled Memory
//	//ADC1
//	self->ADC1.Data_raw[0] = Xil_In16(self->TCM_BASEADDR + 0x00);
//	self->ADC1.Data_raw[1] = Xil_In16(self->TCM_BASEADDR + 0x02);
//	self->ADC1.Data_raw[2] = Xil_In16(self->TCM_BASEADDR + 0x04);
//	self->ADC1.Data_raw[3] = Xil_In16(self->TCM_BASEADDR + 0x06);
//	self->ADC1.Data_raw[4] = Xil_In16(self->TCM_BASEADDR + 0x08);
//	self->ADC1.Data_raw[5] = Xil_In16(self->TCM_BASEADDR + 0x0A);
//	self->ADC1.Data_raw[6] = Xil_In16(self->TCM_BASEADDR + 0x0C);
//	self->ADC1.Data_raw[7] = Xil_In16(self->TCM_BASEADDR + 0x0E);
//	//ADC2
//	self->ADC2.Data_raw[0] = Xil_In16(self->TCM_BASEADDR + 0x10);
//	self->ADC2.Data_raw[1] = Xil_In16(self->TCM_BASEADDR + 0x12);
//	self->ADC2.Data_raw[2] = Xil_In16(self->TCM_BASEADDR + 0x14);
//	self->ADC2.Data_raw[3] = Xil_In16(self->TCM_BASEADDR + 0x16);
//	self->ADC2.Data_raw[4] = Xil_In16(self->TCM_BASEADDR + 0x18);
//	self->ADC2.Data_raw[5] = Xil_In16(self->TCM_BASEADDR + 0x1A);
//	self->ADC2.Data_raw[6] = Xil_In16(self->TCM_BASEADDR + 0x1C);
//	self->ADC2.Data_raw[7] = Xil_In16(self->TCM_BASEADDR + 0x1E);
//	//ADC3
//	self->ADC3.Data_raw[0] = Xil_In16(self->TCM_BASEADDR + 0x20);
//	self->ADC3.Data_raw[1] = Xil_In16(self->TCM_BASEADDR + 0x22);
//	self->ADC3.Data_raw[2] = Xil_In16(self->TCM_BASEADDR + 0x24);
//	self->ADC3.Data_raw[3] = Xil_In16(self->TCM_BASEADDR + 0x26);
//	self->ADC3.Data_raw[4] = Xil_In16(self->TCM_BASEADDR + 0x28);
//	self->ADC3.Data_raw[5] = Xil_In16(self->TCM_BASEADDR + 0x2A);
//	self->ADC3.Data_raw[6] = Xil_In16(self->TCM_BASEADDR + 0x2C);
//	self->ADC3.Data_raw[7] = Xil_In16(self->TCM_BASEADDR + 0x2E);
//	//ADC4
//	self->ADC4.Data_raw[0] = Xil_In16(self->TCM_BASEADDR + 0x30);
//	self->ADC4.Data_raw[1] = Xil_In16(self->TCM_BASEADDR + 0x32);
//	self->ADC4.Data_raw[2] = Xil_In16(self->TCM_BASEADDR + 0x34);
//	self->ADC4.Data_raw[3] = Xil_In16(self->TCM_BASEADDR + 0x36);
//	self->ADC4.Data_raw[4] = Xil_In16(self->TCM_BASEADDR + 0x38);
//	self->ADC4.Data_raw[5] = Xil_In16(self->TCM_BASEADDR + 0x3A);
//	self->ADC4.Data_raw[6] = Xil_In16(self->TCM_BASEADDR + 0x3C);
//	self->ADC4.Data_raw[7] = Xil_In16(self->TCM_BASEADDR + 0x3E);
//
//	//Convert
//	self->ADC1.Data[0] = (self->ADC1.Data_raw[0] + self->ADC1.offset[0]) * self->conversion_factor;
//	self->ADC1.Data[1] = (self->ADC1.Data_raw[1] + self->ADC1.offset[1]) * self->conversion_factor;
//	self->ADC1.Data[2] = (self->ADC1.Data_raw[2] + self->ADC1.offset[2]) * self->conversion_factor;
//	self->ADC1.Data[3] = (self->ADC1.Data_raw[3] + self->ADC1.offset[3]) * self->conversion_factor;
//	self->ADC1.Data[4] = (self->ADC1.Data_raw[4] + self->ADC1.offset[4]) * self->conversion_factor;
//	self->ADC1.Data[5] = (self->ADC1.Data_raw[5] + self->ADC1.offset[5]) * self->conversion_factor;
//	self->ADC1.Data[6] = (self->ADC1.Data_raw[6] + self->ADC1.offset[6]) * self->conversion_factor;
//	self->ADC1.Data[7] = (self->ADC1.Data_raw[7] + self->ADC1.offset[7]) * self->conversion_factor;
//	self->ADC2.Data[0] = (self->ADC2.Data_raw[0] + self->ADC2.offset[0]) * self->conversion_factor;
//	self->ADC2.Data[1] = (self->ADC2.Data_raw[1] + self->ADC2.offset[1]) * self->conversion_factor;
//	self->ADC2.Data[2] = (self->ADC2.Data_raw[2] + self->ADC2.offset[2]) * self->conversion_factor;
//	self->ADC2.Data[3] = (self->ADC2.Data_raw[3] + self->ADC2.offset[3]) * self->conversion_factor;
//	self->ADC2.Data[4] = (self->ADC2.Data_raw[4] + self->ADC2.offset[4]) * self->conversion_factor;
//	self->ADC2.Data[5] = (self->ADC2.Data_raw[5] + self->ADC2.offset[5]) * self->conversion_factor;
//	self->ADC2.Data[6] = (self->ADC2.Data_raw[6] + self->ADC2.offset[6]) * self->conversion_factor;
//	self->ADC2.Data[7] = (self->ADC2.Data_raw[7] + self->ADC2.offset[7]) * self->conversion_factor;
//	self->ADC3.Data[0] = (self->ADC3.Data_raw[0] + self->ADC3.offset[0]) * self->conversion_factor;
//	self->ADC3.Data[1] = (self->ADC3.Data_raw[1] + self->ADC3.offset[1]) * self->conversion_factor;
//	self->ADC3.Data[2] = (self->ADC3.Data_raw[2] + self->ADC3.offset[2]) * self->conversion_factor;
//	self->ADC3.Data[3] = (self->ADC3.Data_raw[3] + self->ADC3.offset[3]) * self->conversion_factor;
//	self->ADC3.Data[4] = (self->ADC3.Data_raw[4] + self->ADC3.offset[4]) * self->conversion_factor;
//	self->ADC3.Data[5] = (self->ADC3.Data_raw[5] + self->ADC3.offset[5]) * self->conversion_factor;
//	self->ADC3.Data[6] = (self->ADC3.Data_raw[6] + self->ADC3.offset[6]) * self->conversion_factor;
//	self->ADC3.Data[7] = (self->ADC3.Data_raw[7] + self->ADC3.offset[7]) * self->conversion_factor;
//	self->ADC4.Data[0] = (self->ADC4.Data_raw[0] + self->ADC4.offset[0]) * self->conversion_factor;
//	self->ADC4.Data[1] = (self->ADC4.Data_raw[1] + self->ADC4.offset[1]) * self->conversion_factor;
//	self->ADC4.Data[2] = (self->ADC4.Data_raw[2] + self->ADC4.offset[2]) * self->conversion_factor;
//	self->ADC4.Data[3] = (self->ADC4.Data_raw[3] + self->ADC4.offset[3]) * self->conversion_factor;
//	self->ADC4.Data[4] = (self->ADC4.Data_raw[4] + self->ADC4.offset[4]) * self->conversion_factor;
//	self->ADC4.Data[5] = (self->ADC4.Data_raw[5] + self->ADC4.offset[5]) * self->conversion_factor;
//	self->ADC4.Data[6] = (self->ADC4.Data_raw[6] + self->ADC4.offset[6]) * self->conversion_factor;
//	self->ADC4.Data[7] = (self->ADC4.Data_raw[7] + self->ADC4.offset[7]) * self->conversion_factor;
//
//	self->status = adc_ready;
//}
//
//void Update_Values_Board_1() {
//	Update_Values(&slot_1);
//}
//
//void Update_Values_Board_2() {
//	Update_Values(&slot_2);
//}
//
//void Update_Values_Board_3() {
//	Update_Values(&slot_3);
//}
//
//ADCstatus Board_1_Status() {
//	return slot_1.status;
//}
//
//ADCstatus Board_2_Status() {
//	return slot_2.status;
//}
//
//ADCstatus Board_3_Status() {
//	return slot_3.status;
//}
