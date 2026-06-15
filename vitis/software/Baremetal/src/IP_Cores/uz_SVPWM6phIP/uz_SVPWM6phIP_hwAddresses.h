#pragma once

#define  IPCore_Reset_SVPWM_6ph_ip                      0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_SVPWM_6ph_ip                     0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_SVPWM_6ph_ip                  0x8  //contains unique IP timestamp (yymmddHHMM): 2606131525
#define  PWM_en_AXI_Data_SVPWM_6ph_ip                   0x100  //data register for Inport PWM_en_AXI
#define  Mode_AXI_Data_SVPWM_6ph_ip                     0x104  //data register for Inport Mode_AXI
#define  Scal_f_carrier_AXI_Data_SVPWM_6ph_ip           0x108  //data register for Inport Scal_f_carrier_AXI
#define  Scal_T_carrier_AXI_Data_SVPWM_6ph_ip           0x10C  //data register for Inport Scal_T_carrier_AXI
#define  PWM_min_SV_time_AXI_Data_SVPWM_6ph_ip          0x110  //data register for Inport PWM_min_SV_time_AXI
#define  in_T1_AXI_Data_SVPWM_6ph_ip                    0x114  //data register for Inport in_T1_AXI
#define  in_T2_AXI_Data_SVPWM_6ph_ip                    0x118  //data register for Inport in_T2_AXI
#define  in_T3_AXI_Data_SVPWM_6ph_ip                    0x11C  //data register for Inport in_T3_AXI
#define  in_T4_AXI_Data_SVPWM_6ph_ip                    0x120  //data register for Inport in_T4_AXI
#define  in_T5_AXI_Data_SVPWM_6ph_ip                    0x124  //data register for Inport in_T5_AXI
#define  in_SV1_AXI_Data_SVPWM_6ph_ip                   0x128  //data register for Inport in_SV1_AXI
#define  in_SV2_AXI_Data_SVPWM_6ph_ip                   0x12C  //data register for Inport in_SV2_AXI
#define  in_SV3_AXI_Data_SVPWM_6ph_ip                   0x130  //data register for Inport in_SV3_AXI
#define  in_SV4_AXI_Data_SVPWM_6ph_ip                   0x134  //data register for Inport in_SV4_AXI
#define  in_SV5_AXI_Data_SVPWM_6ph_ip                   0x138  //data register for Inport in_SV5_AXI
#define  count_src_ext_AXI_Data_SVPWM_6ph_ip            0x13C  //data register for Inport count_src_ext_AXI
#define  PWM_trigger_source_AXI_Data_SVPWM_6ph_ip       0x140  //data register for Inport PWM_trigger_source_AXI
#define  TriState_HB1_AXI_Data_SVPWM_6ph_ip             0x144  //data register for Inport TriState_HB1_AXI
#define  TriState_HB2_AXI_Data_SVPWM_6ph_ip             0x148  //data register for Inport TriState_HB2_AXI
#define  TriState_HB3_AXI_Data_SVPWM_6ph_ip             0x14C  //data register for Inport TriState_HB3_AXI
#define  TriState_HB4_AXI1_Data_SVPWM_6ph_ip            0x150  //data register for Inport TriState_HB4_AXI1
#define  TriState_HB5_AXI1_Data_SVPWM_6ph_ip            0x154  //data register for Inport TriState_HB5_AXI1
#define  TriState_HB6_AXI1_Data_SVPWM_6ph_ip            0x158  //data register for Inport TriState_HB6_AXI1
#define  PWM_en_rd_AXI_Data_SVPWM_6ph_ip                0x15C  //data register for Outport PWM_en_rd_AXI
#define  PWM_f_carrier_kHz_rd_AXI_Data_SVPWM_6ph_ip     0x160  //data register for Outport PWM_f_carrier_kHz_rd_AXI
#define  PWM_T_carrier_us_rd_AXI_Data_SVPWM_6ph_ip      0x164  //data register for Outport PWM_T_carrier_us_rd_AXI
#define  PWM_min_pulse_width_rd_AXI_Data_SVPWM_6ph_ip   0x168  //data register for Outport PWM_min_pulse_width_rd_AXI
#define  Mode_rd_AXI_Data_SVPWM_6ph_ip                  0x16C  //data register for Outport Mode_rd_AXI