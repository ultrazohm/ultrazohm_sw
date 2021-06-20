/*
 * File Name:         hdl_prj/ipcore/uz_pmsm_model_v1_0/include/uz_pmsm_model_addr.h
 * Description:       C Header File
 * Created:           2021-06-17 18:12:47
*/

#ifndef UZ_PMSM_MODEL_H_
#define UZ_PMSM_MODEL_H_

#define  IPCore_Reset_uz_pmsm_model       0x0U  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm_model      0x4U  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm_model   0x8U  //contains unique IP timestamp (yymmddHHMM): 2106171810: 2106171812
#define  u_d_Data_uz_pmsm_model           0x100U  //data register for Inport u_d
#define  u_q_Data_uz_pmsm_model           0x104U  //data register for Inport u_q
#define  omega_mech_Data_uz_pmsm_model    0x108U  //data register for Inport omega_mech
#define  reset_Data_uz_pmsm_model         0x10CU  //data register for Inport reset
#define  i_d_Data_uz_pmsm_model           0x110U  //data register for Outport i_d
#define  i_q_Data_uz_pmsm_model           0x114U  //data register for Outport i_q
#define  torque_Data_uz_pmsm_model        0x118U  //data register for Outport torque

#endif /* UZ_PMSM_MODEL_H_ */
