#pragma once

#define  IPCore_Reset_uz_JL_pmsmModel         0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_JL_pmsmModel        0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_JL_pmsmModel     0x8  //contains unique IP timestamp (yymmddHHMM): 2605151340: 2605151351
#define  Bremse_Data_uz_JL_pmsmModel          0x100  //data register for Inport Bremse
#define  Last_M_Data_uz_JL_pmsmModel          0x104  //data register for Inport Last_M
#define  Last_J_Data_uz_JL_pmsmModel          0x108  //data register for Inport Last_J
#define  switchUabc_dq_Data_uz_JL_pmsmModel   0x10C  //data register for Inport switchUabc_dq
#define  Ud_Data_uz_JL_pmsmModel              0x110  //data register for Inport Ud
#define  Uq_Data_uz_JL_pmsmModel              0x114  //data register for Inport Uq
#define  rec_mot_Ld_Data_uz_JL_pmsmModel      0x118  //data register for Inport rec_mot_Ld
#define  r1_Data_uz_JL_pmsmModel              0x11C  //data register for Inport r1
#define  psi_pm_Data_uz_JL_pmsmModel          0x120  //data register for Inport psi_pm
#define  Ld_Data_uz_JL_pmsmModel              0x124  //data register for Inport Ld
#define  Lq_Data_uz_JL_pmsmModel              0x128  //data register for Inport Lq
#define  polpaare_Data_uz_JL_pmsmModel        0x12C  //data register for Inport polpaare
#define  mot_J_Data_uz_JL_pmsmModel           0x130  //data register for Inport mot_J
#define  omega_mech_Data_uz_JL_pmsmModel      0x134  //data register for Outport omega_mech
#define  phi_mech_Data_uz_JL_pmsmModel        0x138  //data register for Outport phi_mech
#define  pmsm_M_Mot_Data_uz_JL_pmsmModel      0x13C  //data register for Outport pmsm_M_Mot
#define  rec_mot_Lq_Data_uz_JL_pmsmModel      0x140  //data register for Inport rec_mot_Lq
#define  pmsm_Iu_Data_uz_JL_pmsmModel         0x144  //data register for Outport pmsm_Iu
#define  pmsm_Iv_Data_uz_JL_pmsmModel         0x148  //data register for Outport pmsm_Iv
#define  pmsm_Iw_Data_uz_JL_pmsmModel         0x14C  //data register for Outport pmsm_Iw