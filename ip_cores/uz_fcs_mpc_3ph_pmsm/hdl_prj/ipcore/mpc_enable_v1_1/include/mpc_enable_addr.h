/*
 * File Name:         hdl_prj\ipcore\mpc_enable_v1_1\include\mpc_enable_addr.h
 * Description:       C Header File
 * Created:           2023-10-04 15:59:30
*/

#ifndef MPC_ENABLE_H_
#define MPC_ENABLE_H_

#define  IPCore_Reset_mpc_enable       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_mpc_enable      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_mpc_enable   0x8  //contains unique IP timestamp (yymmddHHMM): 2310041559
#define  AXI_mpc_enb_Data_mpc_enable   0x17C  //data register for Inport AXI_mpc_enb

#endif /* MPC_ENABLE_H_ */
