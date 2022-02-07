#pragma once

#ifndef MUX_AXI_IP_H_
#define MUX_AXI_IP_H_

#define  IPCore_Reset_mux_axi_ip                     0x0U  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_mux_axi_ip                    0x4U  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_mux_axi_ip                 0x8U  //contains unique IP timestamp (yymmddHHMM): 2110211105
#define  select_AXI_Data_mux_axi_ip                  0x100U  //data register for Inport select_AXI
#define  select_n_th_adc_interrupt_Data_mux_axi_ip   0x104U  //data register for Inport select_n_th_adc_interrupt

#endif /* MUX_AXI_IP_H_ */