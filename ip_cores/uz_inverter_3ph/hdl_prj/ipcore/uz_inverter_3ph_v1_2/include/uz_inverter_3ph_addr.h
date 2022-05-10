/*
 * File Name:         C:\Users\valen\Documents\repos\UZ\ultrazohm_sw\ip_cores\uz_inverter_3ph\hdl_prj\ipcore\uz_inverter_3ph_v1_2\include\uz_inverter_3ph_addr.h
 * Description:       C Header File
 * Created:           2022-05-08 18:43:10
*/

#ifndef UZ_INVERTER_3PH_H_
#define UZ_INVERTER_3PH_H_

#define  IPCore_Reset_uz_inverter_3ph            0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_inverter_3ph           0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_inverter_3ph        0x8  //contains unique IP timestamp (yymmddHHMM): 2205081843
#define  switch_pspl_abc_Data_uz_inverter_3ph    0x100  //data register for Inport switch_pspl_abc
#define  switch_pspl_gate_Data_uz_inverter_3ph   0x104  //data register for Inport switch_pspl_gate
#define  i_abc_ps_Data_uz_inverter_3ph           0x140  //data register for Inport i_abc_ps, vector with 3 elements, address ends at 0x148
#define  i_abc_ps_Strobe_uz_inverter_3ph         0x150  //strobe register for port i_abc_ps
#define  gate_ps_Data_uz_inverter_3ph            0x160  //data register for Inport gate_ps, vector with 6 elements, address ends at 0x174
#define  gate_ps_Strobe_uz_inverter_3ph          0x180  //strobe register for port gate_ps
#define  u_abc_ps_Data_uz_inverter_3ph           0x190  //data register for Outport u_abc_ps, vector with 3 elements, address ends at 0x198
#define  u_abc_ps_Strobe_uz_inverter_3ph         0x1A0  //strobe register for port u_abc_ps

#endif /* UZ_INVERTER_3PH_H_ */
