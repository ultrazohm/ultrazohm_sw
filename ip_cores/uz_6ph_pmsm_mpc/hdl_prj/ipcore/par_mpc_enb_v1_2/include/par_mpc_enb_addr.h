/*
 * File Name:         hdl_prj\ipcore\par_mpc_enb_v1_2\include\par_mpc_enb_addr.h
 * Description:       C Header File
 * Created:           2024-01-04 09:07:58
*/

#ifndef PAR_MPC_ENB_H_
#define PAR_MPC_ENB_H_

#define  IPCore_Reset_par_mpc_enb       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_par_mpc_enb      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_par_mpc_enb   0x8  //contains unique IP timestamp (yymmddHHMM): 2401040907
#define  AXI_mpc_enb_Data_par_mpc_enb   0x17C  //data register for Inport AXI_mpc_enb

#endif /* PAR_MPC_ENB_H_ */
