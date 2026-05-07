/*
 * File Name:         C:\Users\jonat\Documents\MA_JL_CIL\ip_cores\uz_JL_pmsmModel\hdl_prj\ipcore\uz_JL_pmsmModel_v1_0\include\uz_JL_pmsmModel_addr.h
 * Description:       C Header File
 * Created:           2026-05-04 17:48:02
*/

#ifndef UZ_JL_PMSMMODEL_H_
#define UZ_JL_PMSMMODEL_H_

#define  IPCore_Reset_uz_JL_pmsmModel                    0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_JL_pmsmModel                   0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_JL_pmsmModel                0x8  //contains unique IP timestamp (yymmddHHMM): 2605041742: 2605041747
#define  Last_J_Data_uz_JL_pmsmModel                     0x144  //data register for Inport Last_J
#define  Last_M_Data_uz_JL_pmsmModel                     0x148  //data register for Inport Last_M
#define  Bremse_Data_uz_JL_pmsmModel                     0x14C  //data register for Inport Bremse
#define  PMSM_Out_pmsm_Iuvw_Data_uz_JL_pmsmModel         0x100  //data register for Outport PMSM_Out_pmsm_Iuvw. Vector with 3 elements. Register is split across a total of 3 addresses, last address is 0x108.
#define  PMSM_Out_pmsm_Iuvw_Strobe_uz_JL_pmsmModel       0x110  //strobe register for port PMSM_Out_pmsm_Iuvw
#define  PMSM_Out_pmsm_Omega_mech_Data_uz_JL_pmsmModel   0x114  //data register for Outport PMSM_Out_pmsm_Omega_mech
#define  PMSM_Out_pmsm_phi_mech_Data_uz_JL_pmsmModel     0x118  //data register for Outport PMSM_Out_pmsm_phi_mech
#define  PMSM_Out_pmsm_m_mot_Data_uz_JL_pmsmModel        0x11C  //data register for Outport PMSM_Out_pmsm_m_mot
#define  PMSM_config_mot_R1_Data_uz_JL_pmsmModel         0x120  //data register for Inport PMSM_config_mot_R1
#define  PMSM_config_mot_psi_pm_Data_uz_JL_pmsmModel     0x124  //data register for Inport PMSM_config_mot_psi_pm
#define  PMSM_config_mot_Ld_Data_uz_JL_pmsmModel         0x128  //data register for Inport PMSM_config_mot_Ld
#define  PMSM_config_mot_Lq_Data_uz_JL_pmsmModel         0x12C  //data register for Inport PMSM_config_mot_Lq
#define  PMSM_config_mot_p_Data_uz_JL_pmsmModel          0x130  //data register for Inport PMSM_config_mot_p
#define  PMSM_config_mot_J_Data_uz_JL_pmsmModel          0x134  //data register for Inport PMSM_config_mot_J
#define  PMSM_config_mot_n_N_Data_uz_JL_pmsmModel        0x138  //data register for Inport PMSM_config_mot_n_N
#define  PMSM_config_mot_M_N_Data_uz_JL_pmsmModel        0x13C  //data register for Inport PMSM_config_mot_M_N
#define  PMSM_config_mot_I_max_Data_uz_JL_pmsmModel      0x140  //data register for Inport PMSM_config_mot_I_max

#endif /* UZ_JL_PMSMMODEL_H_ */
