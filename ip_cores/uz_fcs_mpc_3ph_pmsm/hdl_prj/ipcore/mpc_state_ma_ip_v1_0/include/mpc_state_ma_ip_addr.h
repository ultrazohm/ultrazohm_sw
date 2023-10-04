/*
 * File Name:         hdl_prj\ipcore\mpc_state_ma_ip_v1_0\include\mpc_state_ma_ip_addr.h
 * Description:       C Header File
 * Created:           2023-10-04 15:41:23
*/

#ifndef MPC_STATE_MA_IP_H_
#define MPC_STATE_MA_IP_H_

#define  IPCore_Reset_mpc_state_ma_ip                0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_mpc_state_ma_ip               0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_mpc_state_ma_ip            0x8  //contains unique IP timestamp (yymmddHHMM): 2310041541
#define  AXI_no_of_iterations_Data_mpc_state_ma_ip   0x100  //data register for Inport AXI_no_of_iterations

#endif /* MPC_STATE_MA_IP_H_ */
