/*
 * File Name:         hdl_prj\ipcore\ctrl_stat_ip_v1_0\include\ctrl_stat_ip_addr.h
 * Description:       C Header File
 * Created:           2023-06-15 08:35:46
*/

#ifndef CTRL_STAT_IP_H_
#define CTRL_STAT_IP_H_

#define  IPCore_Reset_ctrl_stat_ip                0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_ctrl_stat_ip               0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_ctrl_stat_ip            0x8  //contains unique IP timestamp (yymmddHHMM): 2306150835
#define  AXI_no_of_iterations_Data_ctrl_stat_ip   0x100  //data register for Inport AXI_no_of_iterations

#endif /* CTRL_STAT_IP_H_ */
