/*
 * File Name:         /home/ts/Dokumente/ultrazohm_testbench/ultrazohm_test/ultrazohm_sw/ip_cores/simscapeHDL_example_v1_0/ipcore/uz_simscapeExample_v1_0/include/uz_simscapeExample_addr.h
 * Description:       C Header File
 * Created:           2021-04-19 11:33:25
*/

#ifndef UZ_SIMSCAPEEXAMPLE_H_
#define UZ_SIMSCAPEEXAMPLE_H_

#define  IPCore_Reset_uz_simscapeExample       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_simscapeExample      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_simscapeExample   0x8  //contains unique IP timestamp (yymmddHHMM): 2104191133
#define  Vin_Data_uz_simscapeExample           0x100  //data register for Inport Vin
#define  IR_Data_uz_simscapeExample            0x104  //data register for Outport IR
#define  Iout_Data_uz_simscapeExample          0x108  //data register for Outport Iout
#define  Vdiode_Data_uz_simscapeExample        0x10C  //data register for Outport Vdiode

#endif /* UZ_SIMSCAPEEXAMPLE_H_ */
