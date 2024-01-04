/*
 * File Name:         hdl_prj\ipcore\par_pu_volts_vsd_v1_1\include\par_pu_volts_vsd_addr.h
 * Description:       C Header File
 * Created:           2024-01-04 13:42:13
*/

#ifndef PAR_PU_VOLTS_VSD_H_
#define PAR_PU_VOLTS_VSD_H_

#define  IPCore_Reset_par_pu_volts_vsd              0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_par_pu_volts_vsd             0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_par_pu_volts_vsd          0x8  //contains unique IP timestamp (yymmddHHMM): 2401041342
#define  index_select_AXI_Data_par_pu_volts_vsd     0x100  //data register for Inport index_select_AXI
#define  index_AXI_Data_par_pu_volts_vsd            0x104  //data register for Inport index_AXI
#define  index_offset_AXI_1_Data_par_pu_volts_vsd   0x108  //data register for Inport index_offset_AXI_1
#define  index_offset_AXI_2_Data_par_pu_volts_vsd   0x10C  //data register for Inport index_offset_AXI_2
#define  index_offset_AXI_3_Data_par_pu_volts_vsd   0x110  //data register for Inport index_offset_AXI_3
#define  index_offset_AXI_4_Data_par_pu_volts_vsd   0x114  //data register for Inport index_offset_AXI_4
#define  v_DC_pu_AXI_Data_par_pu_volts_vsd          0x118  //data register for Inport v_DC_pu_AXI
#define  v_dc_select_AXI_Data_par_pu_volts_vsd      0x11C  //data register for Inport v_dc_select_AXI
#define  index_offset_AXI_5_Data_par_pu_volts_vsd   0x120  //data register for Inport index_offset_AXI_5
#define  index_offset_AXI_6_Data_par_pu_volts_vsd   0x124  //data register for Inport index_offset_AXI_6
#define  index_offset_AXI_7_Data_par_pu_volts_vsd   0x128  //data register for Inport index_offset_AXI_7
#define  pu_vd_AXI_Data_par_pu_volts_vsd            0x12C  //data register for Outport pu_vd_AXI
#define  pu_vq_AXI_Data_par_pu_volts_vsd            0x130  //data register for Outport pu_vq_AXI
#define  pu_vx_AXI_Data_par_pu_volts_vsd            0x134  //data register for Outport pu_vx_AXI
#define  pu_vy_AXI_Data_par_pu_volts_vsd            0x138  //data register for Outport pu_vy_AXI

#endif /* PAR_PU_VOLTS_VSD_H_ */
