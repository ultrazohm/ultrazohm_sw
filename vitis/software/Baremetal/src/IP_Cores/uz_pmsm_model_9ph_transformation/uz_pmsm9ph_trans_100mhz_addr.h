/*
 * File Name:         9phase_trans/ipcore/uz_pmsm9ph_trans_100mhz_v1_0/include/uz_pmsm9ph_trans_100mhz_addr.h
 * Description:       C Header File
 * Created:           2022-06-09 09:43:42
*/

#ifndef UZ_PMSM9PH_TRANS_100MHZ_H_
#define UZ_PMSM9PH_TRANS_100MHZ_H_

#define  IPCore_Reset_uz_pmsm9ph_trans_100mhz           0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm9ph_trans_100mhz          0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm9ph_trans_100mhz       0x8  //contains unique IP timestamp (yymmddHHMM): 2206090943
#define  theta_el_axi_Data_uz_pmsm9ph_trans_100mhz      0x100  //data register for Outport theta_el_axi
#define  i_abc_out_axi_Data_uz_pmsm9ph_trans_100mhz     0x140  //data register for Outport i_abc_out_axi, vector with 9 elements, address ends at 0x160
#define  i_abc_out_axi_Strobe_uz_pmsm9ph_trans_100mhz   0x180  //strobe register for port i_abc_out_axi

#endif /* UZ_PMSM9PH_TRANS_100MHZ_H_ */
