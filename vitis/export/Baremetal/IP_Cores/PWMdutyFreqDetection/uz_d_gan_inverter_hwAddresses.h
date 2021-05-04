/*
 * File Name:         hdl_prj\ipcore\UZ_D_GaN_Inverter_v1_0\include\UZ_D_GaN_Inverter_addr.h
 * Description:       C Header File
 * Created:           2021-05-04 10:29:14
*/

#ifndef UZ_D_GAN_INVERTER_H_
#define UZ_D_GAN_INVERTER_H_

#define  IPCore_Reset_UZ_D_GaN_Inverter                   0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_UZ_D_GaN_Inverter                  0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_UZ_D_GaN_Inverter               0x8  //contains unique IP timestamp (yymmddHHMM): 2105041029
#define  AXI_Gan_Temp_1_freq_Data_UZ_D_GaN_Inverter       0x100  //data register for Outport AXI_Gan_Temp_1_freq
#define  AXI_Gan_Temp_1_hightime_Data_UZ_D_GaN_Inverter   0x104  //data register for Outport AXI_Gan_Temp_1_hightime
#define  AXI_Gan_Temp_1_lowtime_Data_UZ_D_GaN_Inverter    0x108  //data register for Outport AXI_Gan_Temp_1_lowtime
#define  AXI_Gan_Temp_1_dutycyc_Data_UZ_D_GaN_Inverter    0x10C  //data register for Outport AXI_Gan_Temp_1_dutycyc
#define  AXI_Gan_Temp_2_freq_Data_UZ_D_GaN_Inverter       0x110  //data register for Outport AXI_Gan_Temp_2_freq
#define  AXI_Gan_Temp_2_hightime_Data_UZ_D_GaN_Inverter   0x114  //data register for Outport AXI_Gan_Temp_2_hightime
#define  AXI_Gan_Temp_2_lowtime_Data_UZ_D_GaN_Inverter    0x118  //data register for Outport AXI_Gan_Temp_2_lowtime
#define  AXI_GaN_FAULT_H1_Data_UZ_D_GaN_Inverter          0x160  //data register for Outport AXI_GaN_FAULT_H1
#define  AXI_GaN_FAULT_L1_Data_UZ_D_GaN_Inverter          0x164  //data register for Outport AXI_GaN_FAULT_L1
#define  AXI_GaN_FAULT_H2_Data_UZ_D_GaN_Inverter          0x168  //data register for Outport AXI_GaN_FAULT_H2
#define  AXI_GaN_FAULT_L2_Data_UZ_D_GaN_Inverter          0x16C  //data register for Outport AXI_GaN_FAULT_L2
#define  AXI_GaN_FAULT_H3_Data_UZ_D_GaN_Inverter          0x170  //data register for Outport AXI_GaN_FAULT_H3
#define  AXI_GaN_FAULT_L3_Data_UZ_D_GaN_Inverter          0x174  //data register for Outport AXI_GaN_FAULT_L3
#define  AXI_GaN_OC_H1_Data_UZ_D_GaN_Inverter             0x178  //data register for Outport AXI_GaN_OC_H1
#define  AXI_GaN_OC_L1_Data_UZ_D_GaN_Inverter             0x17C  //data register for Outport AXI_GaN_OC_L1
#define  AXI_GaN_OC_H2_Data_UZ_D_GaN_Inverter             0x180  //data register for Outport AXI_GaN_OC_H2
#define  AXI_GaN_OC_L2_Data_UZ_D_GaN_Inverter             0x184  //data register for Outport AXI_GaN_OC_L2
#define  AXI_GaN_OC_H3_Data_UZ_D_GaN_Inverter             0x188  //data register for Outport AXI_GaN_OC_H3
#define  AXI_GaN_OC_L3_Data_UZ_D_GaN_Inverter             0x18C  //data register for Outport AXI_GaN_OC_L3
#define  AXI_I_DIAG_Data_UZ_D_GaN_Inverter                0x190  //data register for Outport AXI_I_DIAG
#define  AXI_I1_DIAG_Data_UZ_D_GaN_Inverter               0x194  //data register for Outport AXI_I1_DIAG
#define  AXI_I2_DIAG_Data_UZ_D_GaN_Inverter               0x198  //data register for Outport AXI_I2_DIAG
#define  AXI_I3_DIAG_Data_UZ_D_GaN_Inverter               0x19C  //data register for Outport AXI_I3_DIAG
#define  AXI_PWM_Enable_Data_UZ_D_GaN_Inverter            0x1A0  //data register for Inport AXI_PWM_Enable

#endif /* UZ_D_GAN_INVERTER_H_ */
