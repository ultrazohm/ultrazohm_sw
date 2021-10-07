/*
 * File Name:         hdl_prj\ipcore\mux_axi_ip_v1_1\include\mux_axi_ip_addr.h
 * Description:       C Header File
 * Created:           2021-10-07 11:36:20
*/

#ifndef MUX_AXI_IP_H_
#define MUX_AXI_IP_H_

#define  IPCore_Reset_mux_axi_ip                     0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_mux_axi_ip                    0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_mux_axi_ip                 0x8  //contains unique IP timestamp (yymmddHHMM): 2110071136
#define  select_AXI_Data_mux_axi_ip                  0x100  //data register for Inport select_AXI
#define  select_n_th_adc_interrupt_Data_mux_axi_ip   0x104  //data register for Inport select_n_th_adc_interrupt

#endif /* MUX_AXI_IP_H_ */
