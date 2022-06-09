/*
 * File Name:         hdl_prj/ipcore/uz_invert_ip_v1_0/include/uz_invert_ip_addr.h
 * Description:       C Header File
 * Created:           2022-06-09 09:27:33
*/

#ifndef UZ_INVERT_IP_H_
#define UZ_INVERT_IP_H_

#define  IPCore_Reset_uz_invert_ip            0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_invert_ip           0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_invert_ip        0x8  //contains unique IP timestamp (yymmddHHMM): 2206090927
#define  switch_pspl_abc_Data_uz_invert_ip    0x100  //data register for Inport switch_pspl_abc
#define  switch_pspl_gate_Data_uz_invert_ip   0x104  //data register for Inport switch_pspl_gate
#define  u_dc_Data_uz_invert_ip               0x108  //data register for Inport u_dc
#define  i_abc_ps_Data_uz_invert_ip           0x110  //data register for Inport i_abc_ps, vector with 3 elements, address ends at 0x118
#define  i_abc_ps_Strobe_uz_invert_ip         0x120  //strobe register for port i_abc_ps
#define  gate_ps_Data_uz_invert_ip            0x140  //data register for Inport gate_ps, vector with 6 elements, address ends at 0x154
#define  gate_ps_Strobe_uz_invert_ip          0x160  //strobe register for port gate_ps
#define  u_abc_ps_Data_uz_invert_ip           0x170  //data register for Outport u_abc_ps, vector with 3 elements, address ends at 0x178
#define  u_abc_ps_Strobe_uz_invert_ip         0x180  //strobe register for port u_abc_ps

#endif /* UZ_INVERT_IP_H_ */
