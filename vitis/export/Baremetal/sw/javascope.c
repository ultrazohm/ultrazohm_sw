/******************************************************************************
 *
 * javascope.c
 *
 * Copyright (C) 2018 Institute ELSYS, TH N�rnberg, All rights reserved.
 *
 *  Created on: 21.08.2018
 *      Author: Sebastian Wendel (SW) & Philipp L�hdefink (PL)
 *
******************************************************************************/

#include "../main.h"
#include "../defines.h"
#include "../include/javascope.h"

float myIQfactor[15] = {1.0, 2.0, 4.0, 8.0, 16.0, 32.0, 64.0, 128.0, 256.0, 512.0, 1024.0, 2048.0, 4096.0, 8192.0, 16384.0};
// Int16 Datentyp geht von −32.768 bis 32.767
// Wertebereiche mit myIQfactor:
// 0  :  −32768 bis 32767				Auflösung 1.0
// 1  :  −16384 bis 16383.5				Auflösung 0.5
// 2  :  −8192  bis 8191.75				Auflösung 0.25
// 3  :  −4096  bis 4095.875			Auflösung 0.125
// 4  :  −2048  bis 2047.9375			Auflösung 0.0625
// 5  :  −1024  bis 1023.96875			Auflösung 0.03125
// 6  :  −512   bis 511.984375			Auflösung 0.015625
// 7  :  −256   bis 255.9921875			Auflösung 0.0078125
// 8  :  −128   bis 127.99609375  		Auflösung 0.00390625
// 9  :  −64    bis 63.998046875		Auflösung 0.001953125
// 10 :  −32    bis 31.999023437		Auflösung 0.000976563
// 11 :  −16    bis 15.999511719		Auflösung 0.000488281
// 12 :  −8     bis 7.999755859			Auflösung 0.000244141
// 13 :  −4     bis 3.999877930			Auflösung 0.000122070
// 14 :  −2 	bis 1.999938965			Auflösung 0.000061035

#define IPI_HEADER			0x1E0000 /* 1E - Target Module ID */
#define IPI_R5toA53_MSG_LEN		8U //27U
#define IPI_A53toR5_MSG_LEN		3U

extern ARM_to_Oszi_Data_shared_struct OsziData;//Data from A9_0 to A9_1 (from BareMetal to FreeRTOS) in order to provide data for the GUI (Ethernet-Plot)
extern Oszi_to_ARM_Data_shared_struct ControlData; //Data from A9_1 to A9_0 (from FreeRTOS to BareMetal) in order to receive control data from the GUI
Xuint32 cnt_javascope=0, cnt_slowData=0;
extern XGpioPs Gpio_OUT;											/* GPIO Device driver instance for the real GPIOs */

Xuint16 js_factor1 = 0, js_factor2 = 0, js_factor3 = 0, js_factor4 = 0;

// Channel-pointer and pointer array
Xfloat32 *js_ptr_arr[JSO_ENDMARKER];
Xfloat32 *js_ptr[4];	// channel ptr
Xfloat32 zerovalue = 0.0;

Xint16  TransferSendAllowed = 1;
Xint32  i_fetchDataLifeCheck=0;

//Initialize the Interrupt structure
extern XScuGic INTCInst;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts!
extern XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

Xint16 values[20];
union SlowData js_slowDataArray[JSSD_ENDMARKER];

int Initialize_JavaScope()
{
	int Status = 0;
	//Initialize all variables with zero
	int j=0;

	for (j=0; j<JSO_ENDMARKER; j++)
	{
		js_ptr_arr[j] = &zerovalue;
	}

	js_ptr[0] = &zerovalue;
	js_ptr[1] = &zerovalue;
	js_ptr[2] = &zerovalue;
	js_ptr[3] = &zerovalue;

	for (j=0; j<JSSD_ENDMARKER; j++)
	{
		js_slowDataArray[j].i = (Xuint32) zerovalue;
	}

	//Initialize the RAM with zeros
	ControlData.digInputs =0;
	ControlData.id =0;
	ControlData.value =0;

	//Do not initialize the shared-RAM, because during power-on, read/write occurs problems! Therefore, allow read/write only a specific time (e.g. 1000 cycles of 100us)
	return Status;
}


void js_fetchData4CH()
{
	Xint32 status;
	u32 MsgPtr[IPI_R5toA53_MSG_LEN] = {0};
	u32 RespBuf[IPI_A53toR5_MSG_LEN] = {0};

	Xint16 data1_int = (Xint16)( myIQfactor[js_factor1] * *js_ptr[0]);
	Xint16 data2_int = (Xint16)( myIQfactor[js_factor2] * *js_ptr[1]);
	Xint16 data3_int = (Xint16)( myIQfactor[js_factor3] * *js_ptr[2]);
	Xint16 data4_int = (Xint16)( myIQfactor[js_factor4] * *js_ptr[3]);

	values[0] = (Xint16) data1_int;
	values[1] = (Xint16) data2_int;
	values[2] = (Xint16) data3_int;
	values[3] = (Xint16) data4_int;

	MsgPtr[0] = values[0];
	MsgPtr[1] = values[1];
	MsgPtr[2] = values[2];
	MsgPtr[3] = values[3];
	memcpy(&(MsgPtr[4]), &(js_slowDataArray[cnt_slowData]), sizeof(Xint32));		// copy without automatic float -> int conversion
	MsgPtr[5] = cnt_slowData;
	MsgPtr[6] = OsziData.status_BareToRTOS;
	MsgPtr[7] = OsziData.schiebereg_ausgaenge;

	cnt_javascope++;
	if (cnt_javascope >= 5) //Send a new SlowData only every 5th cycle
	{
		cnt_javascope =0;
		cnt_slowData++;
		if (cnt_slowData >= JSSD_ENDMARKER)
			cnt_slowData = 0;
	}

	i_fetchDataLifeCheck++; //LiveCheck
	if(i_fetchDataLifeCheck > 10000){
		i_fetchDataLifeCheck =0;
	}


		//Start: send interrupt/message to the other processor with the FreeRTOS----------------------------
//		if(OsziData.SampledDataReadDone == 0){ 	// error
//			OsziData.SampledDataError = 1;		// notify FreeRTOS and BareMetal that the transfer (write->read) was not possible in time
//		}else{									// all ok
//			OsziData.SampledDataReadDone = 0; 	// Reset the ReadDone-flag
//			OsziData.SampledDataWriteDone = 1;	// notify FreeRTOS that new data is available/written
//		}

		//SW: Write message for interrupt to APU
		status = XIpiPsu_WriteMessage(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK, MsgPtr, IPI_R5toA53_MSG_LEN, XIPIPSU_BUF_TYPE_MSG);


		//SW: Send an interrupt to APU
		status = XIpiPsu_TriggerIpi(&INTCInst_IPI,XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK);
		if(status != (u32)XST_SUCCESS) {
			xil_printf("RPU: IPI Trigger failed\r\n");
		}

		//SW: Afterwards an acknowledge and a message from the APU can be read/checked, but we don't do it in order to guarantee that the control-ISR never waits and always runs! -> This is due to the Polling of the acknowledge flag.
		//status = XIpiPsu_PollForAck(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK, (~0));
		status = XIpiPsu_ReadMessage(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK, RespBuf,IPI_A53toR5_MSG_LEN, XIPIPSU_BUF_TYPE_RESP);

		ControlData.id = (Xuint16)RespBuf[0];
		ControlData.value = (Xuint16)RespBuf[1];
		ControlData.digInputs = (Xuint16)RespBuf[2];
//		XGpio_DiscreteClear(&Gpio_OUT,GPIO_CHANNEL, 8);//Stop to the ADC module to set an offset value    0b0100);  	// "Enable_Gate" On //Consider, this is a inverse signal AND "Acknowledge" the set of ADC offset value.

		//TODO check error
		//End: send interrupt/message to the other processor with the FreeRTOS----------------------------
}

void js_fetchData2CH()
{
	//static Xint16 values[20];
	Xint32 status;

	Xint16 data1_int = (Xint16)( myIQfactor[js_factor1] * *js_ptr[0]);
	Xint16 data2_int = (Xint16)( myIQfactor[js_factor2] * *js_ptr[1]);

	if (cnt_javascope < 10)
	{
		values[cnt_javascope] = (Xint16) data1_int;
		values[10+cnt_javascope] = (Xint16) data2_int;
	}

	cnt_javascope++;

	if (cnt_javascope >= 10)
	{
		int j=0;

		if(TransferSendAllowed){
			for (j=0; j<20; j++)
			{
				OsziData.val[j] = values[j];
			}

			memcpy(&(OsziData.slowDataContent), &(js_slowDataArray[cnt_slowData]), sizeof(Xint32));		// copy without automatic float -> int conversion
			OsziData.slowDataID = cnt_slowData;
			cnt_slowData++;
			if (cnt_slowData >= JSSD_ENDMARKER)
				cnt_slowData = 0;
		}
		cnt_javascope = 0;

		i_fetchDataLifeCheck++; //LiveCheck
		if(i_fetchDataLifeCheck > 100000){
			i_fetchDataLifeCheck =0;
			TransferSendAllowed = 1; //Only allow reading from memory after a specific time (e.g. 100ms) in order to avoid memory-access errors during power-on of the two processors
			//xil_printf("var_mess new period\r\n");
		}

		//Start: send interrupt/message to the other processor with the FreeRTOS----------------------------
//		if(OsziData.SampledDataReadDone == 0){ 	// error
//			OsziData.SampledDataError = 1;		// notify FreeRTOS and BareMetal that the transfer (write->read) was not possible in time
//		}else{									// all ok
//			OsziData.SampledDataReadDone = 0; 	// Reset the ReadDone-flag
//			OsziData.SampledDataWriteDone = 1;	// notify FreeRTOS that new data is available/written
//		}
		//Software-generated interrupt (SGI) with the interrupt-number = "INTC_IPC_Shared_INTERRUPT_ID" and the target-processor is cpu1 = "XSCUGIC_SPI_CPU0_MASK" -> cpu0 do not see/recognize this interrupt
		status = XScuGic_SoftwareIntr(&INTCInst, INTC_IPC_Shared_INTERRUPT_ID, XSCUGIC_SPI_CPU1_MASK);
		//TODO check error
		//End: send interrupt/message to the other processor with the FreeRTOS----------------------------
	}
}

