#pragma once

#define  IPCore_Reset_uz_JL_Inv_PT1              0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_JL_Inv_PT1             0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_JL_Inv_PT1          0x8  //contains unique IP timestamp (yymmddHHMM): 2605041315
#define  InvConf_SwitchInv_Data_uz_JL_Inv_PT1    0x11C  //data register for Inport InvConf_SwitchInv
#define  InvConf_Udc_Data_uz_JL_Inv_PT1          0x134  //data register for Inport InvConf_Udc
#define  InvConf_PT1_Gain_Data_uz_JL_Inv_PT1     0x138  //data register for Inport InvConf_PT1_Gain
#define  InvConf_PT1_Ts_Data_uz_JL_Inv_PT1       0x13C  //data register for Inport InvConf_PT1_Ts
#define  InvConf_PT1_reset_Data_uz_JL_Inv_PT1    0x140  //data register for Inport InvConf_PT1_reset
#define  InvIn_PWM_H_safe_Data_uz_JL_Inv_PT1     0x100  //data register for Inport InvIn_PWM_H_safe. Vector with 3 elements. Register is split across a total of 3 addresses, last address is 0x108.
#define  InvIn_PWM_H_safe_Strobe_uz_JL_Inv_PT1   0x110  //strobe register for port InvIn_PWM_H_safe
#define  InvIn_Ualpha_Data_uz_JL_Inv_PT1         0x114  //data register for Inport InvIn_Ualpha
#define  InvIn_Ubeta_Data_uz_JL_Inv_PT1          0x118  //data register for Inport InvIn_Ubeta
#define  InvIn_PWM_L_safe_Data_uz_JL_Inv_PT1     0x120  //data register for Inport InvIn_PWM_L_safe. Vector with 3 elements. Register is split across a total of 3 addresses, last address is 0x128.
#define  InvIn_PWM_L_safe_Strobe_uz_JL_Inv_PT1   0x130  //strobe register for port InvIn_PWM_L_safe