/*
 * File Name:         hdl_prj/ipcore/uz_dac_spi_interface_v1_0/include/uz_dac_spi_interface_addr.h
 * Description:       C Header File
 * Created:           2022-05-17 10:01:01
*/

#ifndef UZ_DAC_SPI_INTERFACE_H_
#define UZ_DAC_SPI_INTERFACE_H_

#define  IPCore_Reset_uz_dac_spi_interface         0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_dac_spi_interface        0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_dac_spi_interface     0x8  //contains unique IP timestamp (yymmddHHMM): 2205171000
#define  trigger_write_Data_uz_dac_spi_interface   0x100  //data register for Inport trigger_write
#define  dac_data_1_Data_uz_dac_spi_interface      0x104  //data register for Inport dac_data_1
#define  dac_data_2_Data_uz_dac_spi_interface      0x108  //data register for Inport dac_data_2
#define  dac_data_3_Data_uz_dac_spi_interface      0x10C  //data register for Inport dac_data_3
#define  dac_data_4_Data_uz_dac_spi_interface      0x110  //data register for Inport dac_data_4
#define  dac_data_5_Data_uz_dac_spi_interface      0x114  //data register for Inport dac_data_5
#define  dac_data_6_Data_uz_dac_spi_interface      0x118  //data register for Inport dac_data_6
#define  dac_data_7_Data_uz_dac_spi_interface      0x11C  //data register for Inport dac_data_7
#define  dac_data_8_Data_uz_dac_spi_interface      0x120  //data register for Inport dac_data_8

#endif /* UZ_DAC_SPI_INTERFACE_H_ */
