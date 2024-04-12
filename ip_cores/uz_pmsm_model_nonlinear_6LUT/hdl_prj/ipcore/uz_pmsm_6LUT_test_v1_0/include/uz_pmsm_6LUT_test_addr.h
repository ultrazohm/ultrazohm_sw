/*
 * File Name:         C:\Users\Philipp\ultrazohm\ultrazohm_sw\ip_cores\uz_pmsm_model_nonlinear_6LUT\hdl_prj\ipcore\uz_pmsm_6LUT_test_v1_0\include\uz_pmsm_6LUT_test_addr.h
 * Description:       C Header File
 * Created:           2023-10-19 13:38:57
*/

#ifndef UZ_PMSM_6LUT_TEST_H_
#define UZ_PMSM_6LUT_TEST_H_

#define  IPCore_Reset_uz_pmsm_6LUT_test               0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm_6LUT_test              0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm_6LUT_test           0x8  //contains unique IP timestamp (yymmddHHMM): 2310191338
#define  reset_integrators_Data_uz_pmsm_6LUT_test     0x100  //data register for Inport reset_integrators
#define  simulate_mechanical_Data_uz_pmsm_6LUT_test   0x104  //data register for Inport simulate_mechanical
#define  reciprocal_J_Data_uz_pmsm_6LUT_test          0x10C  //data register for Inport reciprocal_J
#define  mu_Data_uz_pmsm_6LUT_test                    0x110  //data register for Inport mu
#define  M_n0_Data_uz_pmsm_6LUT_test                  0x114  //data register for Inport M_n0
#define  R1_Data_uz_pmsm_6LUT_test                    0x120  //data register for Inport R1
#define  polepairs_Data_uz_pmsm_6LUT_test             0x124  //data register for Inport polepairs
#define  inputs_Data_uz_pmsm_6LUT_test                0x130  //data register for Inport inputs. Vector with 4 elements. Register is split across a total of 4 addresses, last address is 0x13C.
#define  inputs_Strobe_uz_pmsm_6LUT_test              0x140  //strobe register for port inputs
#define  outputs_Data_uz_pmsm_6LUT_test               0x150  //data register for Outport outputs. Vector with 4 elements. Register is split across a total of 4 addresses, last address is 0x15C.
#define  outputs_Strobe_uz_pmsm_6LUT_test             0x160  //strobe register for port outputs

#endif /* UZ_PMSM_6LUT_TEST_H_ */
