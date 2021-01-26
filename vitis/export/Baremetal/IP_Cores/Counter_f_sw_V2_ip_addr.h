#ifndef COUNTER_F_SW_V2_IP_H_
#define COUNTER_F_SW_V2_IP_H_

#define  IPCore_Reset_Counter_f_sw_V2_ip          0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_Counter_f_sw_V2_ip         0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_Counter_f_sw_V2_ip      0x8  //contains unique IP timestamp (yymmddHHMM): 2004271915
#define  bResetAXI_Data_Counter_f_sw_V2_ip        0x100  //data register for Inport bResetAXI
#define  switchNumb_AXI_Data_Counter_f_sw_V2_ip   0x104  //data register for Outport switchNumb_AXI

#endif /* COUNTER_F_SW_V2_IP_H_ */
