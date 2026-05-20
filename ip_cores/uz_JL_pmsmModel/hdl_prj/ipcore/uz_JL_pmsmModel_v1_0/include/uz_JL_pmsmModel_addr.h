/*
 * File Name:         C:\Users\jonat\Documents\MA_JL_CIL\ip_cores\uz_JL_pmsmModel\hdl_prj\ipcore\uz_JL_pmsmModel_v1_0\include\uz_JL_pmsmModel_addr.h
 * Description:       C Header File
 * Created:           2026-05-19 17:18:52
*/

#ifndef UZ_JL_PMSMMODEL_H_
#define UZ_JL_PMSMMODEL_H_

#define  IPCore_Reset_uz_JL_pmsmModel               0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_JL_pmsmModel              0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_JL_pmsmModel           0x8  //contains unique IP timestamp (yymmddHHMM): 2605191718
#define  Bremse_Data_uz_JL_pmsmModel                0x100  //data register for Inport Bremse
#define  Last_M_Data_uz_JL_pmsmModel                0x104  //data register for Inport Last_M
#define  Last_J_Data_uz_JL_pmsmModel                0x108  //data register for Inport Last_J
#define  switchUabc_dq_Data_uz_JL_pmsmModel         0x10C  //data register for Inport switchUabc_dq
#define  Ud_Data_uz_JL_pmsmModel                    0x110  //data register for Inport Ud
#define  Uq_Data_uz_JL_pmsmModel                    0x114  //data register for Inport Uq
#define  rec_mot_Ld_Data_uz_JL_pmsmModel            0x118  //data register for Inport rec_mot_Ld
#define  r1_Data_uz_JL_pmsmModel                    0x11C  //data register for Inport r1
#define  psi_pm_Data_uz_JL_pmsmModel                0x120  //data register for Inport psi_pm
#define  Ld_Data_uz_JL_pmsmModel                    0x124  //data register for Inport Ld
#define  Lq_Data_uz_JL_pmsmModel                    0x128  //data register for Inport Lq
#define  polpaare_Data_uz_JL_pmsmModel              0x12C  //data register for Inport polpaare
#define  mot_J_Data_uz_JL_pmsmModel                 0x130  //data register for Inport mot_J
#define  Reibungskoeffizient_Data_uz_JL_pmsmModel   0x134  //data register for Inport Reibungskoeffizient
#define  Coulomb_Reibung_Data_uz_JL_pmsmModel       0x138  //data register for Inport Coulomb_Reibung
#define  rec_mot_Lq_Data_uz_JL_pmsmModel            0x140  //data register for Inport rec_mot_Lq
#define  pmsm_out_Data_uz_JL_pmsmModel              0x160  //data register for Outport pmsm_out. Vector with 6 elements. Register is split across a total of 6 addresses, last address is 0x174.
#define  pmsm_out_Strobe_uz_JL_pmsmModel            0x180  //strobe register for port pmsm_out

#endif /* UZ_JL_PMSMMODEL_H_ */
