/*
 * File Name:         hdl_prj\ipcore\pu_voltages_dq_v1_3\include\pu_voltages_dq_addr.h
 * Description:       C Header File
 * Created:           2023-11-30 09:34:45
*/

#ifndef PU_VOLTAGES_DQ_H_
#define PU_VOLTAGES_DQ_H_

#define  IPCore_Reset_pu_voltages_dq                   0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_pu_voltages_dq                  0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_pu_voltages_dq               0x8  //contains unique IP timestamp (yymmddHHMM): 2311300934
#define  index_select_AXI_Data_pu_voltages_dq          0x100  //data register for Inport index_select_AXI
#define  index_AXI_Data_pu_voltages_dq                 0x104  //data register for Inport index_AXI
#define  pu_vd_AXI_Data_pu_voltages_dq                 0x108  //data register for Outport pu_vd_AXI
#define  pu_vq_AXI_Data_pu_voltages_dq                 0x10C  //data register for Outport pu_vq_AXI
#define  id_ref_pu_AXI_Data_pu_voltages_dq             0x110  //data register for Inport id_ref_pu_AXI
#define  iq_ref_pu_AXI_Data_pu_voltages_dq             0x114  //data register for Inport iq_ref_pu_AXI
#define  v_DC_pu_AXI_Data_pu_voltages_dq               0x118  //data register for Inport v_DC_pu_AXI
#define  v_dc_select_AXI_Data_pu_voltages_dq           0x11C  //data register for Inport v_dc_select_AXI
#define  Ts_minus_Td_over_Ts_AXI_Data_pu_voltages_dq   0x120  //data register for Inport Ts_minus_Td_over_Ts_AXI
#define  Td_over_Ts_AXI_Data_pu_voltages_dq            0x124  //data register for Inport Td_over_Ts_AXI
#define  deadtime_comp_onoff_AXI_Data_pu_voltages_dq   0x128  //data register for Inport deadtime_comp_onoff_AXI

#endif /* PU_VOLTAGES_DQ_H_ */
