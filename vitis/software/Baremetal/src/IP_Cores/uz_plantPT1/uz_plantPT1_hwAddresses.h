/*
 * File Name:         hdl_prj/ipcore/uz_plantModel_pt1_v1_0/include/uz_plantModel_pt1_addr.h
 * Description:       C Header File
 * Created:           2021-06-17 10:07:10
*/

#ifndef UZ_PLANTMODEL_PT1_H_
#define UZ_PLANTMODEL_PT1_H_

#define  IPCore_Reset_uz_plantModel_pt1                    0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_plantModel_pt1                   0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_plantModel_pt1                0x8  //contains unique IP timestamp (yymmddHHMM): 2106171007
#define  input_Data_uz_plantModel_pt1                      0x100  //data register for Inport input
#define  gain_Data_uz_plantModel_pt1                       0x104  //data register for Inport gain
#define  reciprocal_time_constant_Data_uz_plantModel_pt1   0x108  //data register for Inport reciprocal_time_constant
#define  reset_Data_uz_plantModel_pt1                      0x10C  //data register for Inport reset
#define  output_Data_uz_plantModel_pt1                     0x110  //data register for Outport output

#endif /* UZ_PLANTMODEL_PT1_H_ */
