/*
 * File Name:         /home/ts/Dokumente/simscapeHDL/ipcore/simscapeHDL_example_v1_0/include/simscapeHDL_example_addr.h
 * Description:       C Header File
 * Created:           2021-03-18 18:25:27
*/

#ifndef UZ_SIMEXPL_ADDR_H_
#define UZ_SIMEXPL_ADDR_H_

#define  IPCore_Reset_simscapeHDL_example       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_simscapeHDL_example      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_simscapeHDL_example   0x8  //contains unique IP timestamp (yymmddHHMM): 2103181825
#define  Vin_Data_simscapeHDL_example           0x100  //data register for Inport Vin
#define  IR_Data_simscapeHDL_example            0x104  //data register for Outport IR
#define  Iout_Data_simscapeHDL_example          0x108  //data register for Outport Iout
#define  Vdiode_Data_simscapeHDL_example        0x10C  //data register for Outport Vdiode

#endif /* SIMSCAPEHDL_EXAMPLE_H_ */
