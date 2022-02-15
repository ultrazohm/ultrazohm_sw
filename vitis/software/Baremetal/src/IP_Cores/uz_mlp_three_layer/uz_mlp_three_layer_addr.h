/*
 * File Name:         hdl_prj/ipcore/uz_mlp_three_layer_v2_0/include/uz_mlp_three_layer_addr.h
 * Description:       C Header File
 * Created:           2021-02-12 15:30:37
*/

#ifndef UZ_MLP_THREE_LAYER_H_
#define UZ_MLP_THREE_LAYER_H_

#define  IPCore_Reset_uz_mlp_three_layer                           0x0U  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_mlp_three_layer                          0x4U  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_mlp_three_layer                       0x8U  //contains unique IP timestamp (yymmddHHMM): 2102121530
#define  axi_enable_nn_Data_uz_mlp_three_layer                     0x100U  //data register for Inport axi_enable_nn
#define  enable_nn_Data_uz_mlp_three_layer                         0x104U  //data register for Inport enable_nn
#define  axi_bias_Data_uz_mlp_three_layer                          0x108U  //data register for Inport axi_bias
#define  axi_weight_Data_uz_mlp_three_layer                        0x10CU  //data register for Inport axi_weight
#define  axi_bias_addr_Data_uz_mlp_three_layer                     0x110U  //data register for Inport axi_bias_addr
#define  axi_weight_addr_Data_uz_mlp_three_layer                   0x114U  //data register for Inport axi_weight_addr
#define  axi_wrEnBias_Data_uz_mlp_three_layer                      0x118U  //data register for Inport axi_wrEnBias
#define  axi_wrEnWeights_Data_uz_mlp_three_layer                   0x11CU  //data register for Inport axi_wrEnWeights
#define  axi_layerNr_Data_uz_mlp_three_layer                       0x120U  //data register for Inport axi_layerNr
#define  use_axi_input_Data_uz_mlp_three_layer                     0x124U  //data register for Inport use_axi_input
#define  axi_number_of_inputs_Data_uz_mlp_three_layer              0x128U  //data register for Inport axi_number_of_inputs
#define  axi_output_number_configuration_Data_uz_mlp_three_layer   0x12CU  //data register for Inport axi_output_number_configuration
#define  axi_valid_output_Data_uz_mlp_three_layer                  0x130U  //data register for Outport axi_valid_output
#define  axi_x_input_Data_uz_mlp_three_layer                       0x140U  //data register for Inport axi_x_input, vector with 16 elements, address ends at 0x17C
#define  axi_x_input_Strobe_uz_mlp_three_layer                     0x180U  //strobe register for port axi_x_input
#define  axi_nn_output_Data_uz_mlp_three_layer                     0x1A0U  //data register for Outport axi_nn_output, vector with 8 elements, address ends at 0x1BC
#define  axi_nn_output_Strobe_uz_mlp_three_layer                   0x1C0U  //strobe register for port axi_nn_output

#endif /* UZ_MLP_THREE_LAYER_H_ */
