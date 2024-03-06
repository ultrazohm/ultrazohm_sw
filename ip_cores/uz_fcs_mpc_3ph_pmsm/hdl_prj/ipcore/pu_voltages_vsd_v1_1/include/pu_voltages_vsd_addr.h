/*
 * File Name:         hdl_prj\ipcore\pu_voltages_vsd_v1_1\include\pu_voltages_vsd_addr.h
 * Description:       C Header File
 * Created:           2023-10-04 15:50:02
*/

#ifndef PU_VOLTAGES_VSD_H_
#define PU_VOLTAGES_VSD_H_

#define  IPCore_Reset_pu_voltages_vsd            0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_pu_voltages_vsd           0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_pu_voltages_vsd        0x8  //contains unique IP timestamp (yymmddHHMM): 2310041550
#define  index_select_AXI_Data_pu_voltages_vsd   0x100  //data register for Inport index_select_AXI
#define  index_AXI_Data_pu_voltages_vsd          0x104  //data register for Inport index_AXI
#define  pu_vd_AXI_Data_pu_voltages_vsd          0x108  //data register for Outport pu_vd_AXI
#define  pu_vq_AXI_Data_pu_voltages_vsd          0x10C  //data register for Outport pu_vq_AXI
#define  v_DC_pu_AXI_Data_pu_voltages_vsd        0x118  //data register for Inport v_DC_pu_AXI
#define  v_dc_select_AXI_Data_pu_voltages_vsd    0x11C  //data register for Inport v_dc_select_AXI

#endif /* PU_VOLTAGES_VSD_H_ */
