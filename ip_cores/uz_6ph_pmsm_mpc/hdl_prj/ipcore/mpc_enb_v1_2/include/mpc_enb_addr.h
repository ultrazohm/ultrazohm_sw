/*
 * File Name:         hdl_prj\ipcore\mpc_enb_v1_2\include\mpc_enb_addr.h
 * Description:       C Header File
 * Created:           2023-10-18 10:42:56
*/

#ifndef MPC_ENB_H_
#define MPC_ENB_H_

#define  IPCore_Reset_mpc_enb       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_mpc_enb      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_mpc_enb   0x8  //contains unique IP timestamp (yymmddHHMM): 2310181042
#define  AXI_mpc_enb_Data_mpc_enb   0x17C  //data register for Inport AXI_mpc_enb

#endif /* MPC_ENB_H_ */
