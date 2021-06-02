 #include "toolbox_LTC2983.h"
 
 
 //Pointer ADC_Data
volatile unsigned * Temp_Channel_conf[CHANNEL_COUNT];
volatile unsigned * Temp_Channel_Data[CHANNEL_COUNT];

//Buffer
float Kurvenkompensation_m[CHANNEL_COUNT]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0.878594249};
float Kurvenkompensation_b[CHANNEL_COUNT]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float Kurvenkompbuffer;


//call example: adc_initialize_addresses(Parbankpointer+0x00000278);
void LTC_initialize_pointer(void * parbankpointer){
    //Temperaturen-KofigurationKurvenkompensation_m
    
    
    for(int i = 0; i < CHANNEL_COUNT; i++){
		Temp_Channel_conf[i] = (unsigned *) (parbankpointer+(i*4));
	}
	
    for(int i = 0; i < CHANNEL_COUNT; i++){
		Temp_Channel_Data[i] = (unsigned *) (parbankpointer+0x00000050+(i*4));
	}
	
	/*
	LTC_Config_CH0					= (unsigned*)(Parbankpointer+0x00000000);
	LTC_Config_CH1					= (unsigned*)(Parbankpointer+0x00000004);
	LTC_Config_CH2					= (unsigned*)(Parbankpointer+0x00000008);
	LTC_Config_CH3					= (unsigned*)(Parbankpointer+0x0000000C);
	LTC_Config_CH4					= (unsigned*)(Parbankpointer+0x00000010);
	LTC_Config_CH5					= (unsigned*)(Parbankpointer+0x00000014);
	LTC_Config_CH6					= (unsigned*)(Parbankpointer+0x00000018);
	LTC_Config_CH7					= (unsigned*)(Parbankpointer+0x0000001C);
	LTC_Config_CH8					= (unsigned*)(Parbankpointer+0x00000020);
	LTC_Config_CH9					= (unsigned*)(Parbankpointer+0x00000024);
	LTC_Config_CH10					= (unsigned*)(Parbankpointer+0x00000028);
	LTC_Config_CH11					= (unsigned*)(Parbankpointer+0x0000002C);
	LTC_Config_CH12					= (unsigned*)(Parbankpointer+0x00000030);
	LTC_Config_CH13					= (unsigned*)(Parbankpointer+0x00000034);
	LTC_Config_CH14					= (unsigned*)(Parbankpointer+0x00000038);
	LTC_Config_CH15					= (unsigned*)(Parbankpointer+0x0000003C);
	LTC_Config_CH16					= (unsigned*)(Parbankpointer+0x00000040);
	LTC_Config_CH17					= (unsigned*)(Parbankpointer+0x00000044);
	LTC_Config_CH18					= (unsigned*)(Parbankpointer+0x00000048);
	LTC_Config_CH19					= (unsigned*)(Parbankpointer+0x0000004C);
    
    //Temperaturen
	LTC_Temp_CH0					= (unsigned*)(Parbankpointer+0x00000050);
	LTC_Temp_CH1					= (unsigned*)(Parbankpointer+0x00000054);
	LTC_Temp_CH2					= (unsigned*)(Parbankpointer+0x00000058);
	LTC_Temp_CH3					= (unsigned*)(Parbankpointer+0x0000005C);
	LTC_Temp_CH4					= (unsigned*)(Parbankpointer+0x00000060);
	LTC_Temp_CH5					= (unsigned*)(Parbankpointer+0x00000064);
	LTC_Temp_CH6					= (unsigned*)(Parbankpointer+0x00000068);
	LTC_Temp_CH7					= (unsigned*)(Parbankpointer+0x0000006C);
	LTC_Temp_CH8					= (unsigned*)(Parbankpointer+0x00000070);
	LTC_Temp_CH9					= (unsigned*)(Parbankpointer+0x00000074);
	LTC_Temp_CH10					= (unsigned*)(Parbankpointer+0x00000078);
	LTC_Temp_CH11					= (unsigned*)(Parbankpointer+0x0000007C);
	LTC_Temp_CH12					= (unsigned*)(Parbankpointer+0x00000080);
	LTC_Temp_CH13					= (unsigned*)(Parbankpointer+0x00000084);
	LTC_Temp_CH14					= (unsigned*)(Parbankpointer+0x00000088);
	LTC_Temp_CH15					= (unsigned*)(Parbankpointer+0x0000008C);
	LTC_Temp_CH16					= (unsigned*)(Parbankpointer+0x00000090);
	LTC_Temp_CH17					= (unsigned*)(Parbankpointer+0x00000094);
	LTC_Temp_CH18					= (unsigned*)(Parbankpointer+0x00000098);
	LTC_Temp_CH19					= (unsigned*)(Parbankpointer+0x0000009C);
	*/
}

void LTC_set_config(){
	*Temp_Channel_conf[0] = 0x00000000;// CH1
	*Temp_Channel_conf[1] = 0xE81EDC00;// CH2		-- RSense 1975Ohm
	*Temp_Channel_conf[2] = 0x00000000;// CH3
	*Temp_Channel_conf[3] = 0x6094C000;// CH4		-- (PT100,CH1-2,3-Wire/rotation/internal,25µA,eu-curve,0)
	// Ab hier beginnen die von Außen nutzbaren Kanäle
	*Temp_Channel_conf[4] = 0x00000000;// CH5-T1
	*Temp_Channel_conf[5] = 0xE8A87000;// CH6-T2 	-- Rsense 10780 Ohm
	*Temp_Channel_conf[6] = 0x00000000;// CH7-T3
	*Temp_Channel_conf[7] = 0xB18B8000;// CH8-T4	-- NTC 10k
	*Temp_Channel_conf[8] = 0x00000000;// CH9-T5
	*Temp_Channel_conf[9] = 0x11180000;// CH10-T6
	*Temp_Channel_conf[10] = 0x00000000;// CH11-T7
	*Temp_Channel_conf[11] = 0x11180000;// CH12-T8
	*Temp_Channel_conf[12] = 0x00000000;// CH13-T9
	*Temp_Channel_conf[13] = 0x11180000;// CH14-T10
	*Temp_Channel_conf[14] = 0x00000000;// CH15-T11
	*Temp_Channel_conf[15] = 0x11180000;// CH16-T12
	*Temp_Channel_conf[16] = 0x00000000;// CH17-T13
	*Temp_Channel_conf[17] = 0x11180000;// CH18-T14
	*Temp_Channel_conf[18] = 0x00000000;// CH19-T15
	*Temp_Channel_conf[19] = 0x11180000;// CH20-T16	-- K-Element mit Vergleichstelle auf CH4 11180000
}

void LTC_fetch_values(){
    for(int i = 0; i < CHANNEL_COUNT; i++){
        LTC2983.temperature_raw[i] 	= (*Temp_Channel_Data[i]) & 0x00FFFFFF;
        Kurvenkompbuffer  			= (float)((LTC2983.temperature_raw[i])*TEMP_CONVERSION_FACTOR*100);
        LTC2983.temperature[i]  	= (Kurvenkompensation_m[i]*Kurvenkompbuffer) + Kurvenkompensation_b[i];
    }
}
