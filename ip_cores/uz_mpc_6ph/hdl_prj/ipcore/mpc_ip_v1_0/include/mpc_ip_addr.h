/*
 * File Name:         hdl_prj\ipcore\mpc_ip_v1_0\include\mpc_ip_addr.h
 * Description:       C Header File
 * Created:           2022-08-29 16:54:38
*/

#ifndef MPC_IP_H_
#define MPC_IP_H_

#define  IPCore_Reset_mpc_ip       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_mpc_ip      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_mpc_ip   0x8  //contains unique IP timestamp (yymmddHHMM): 2208291654

#endif /* MPC_IP_H_ */
