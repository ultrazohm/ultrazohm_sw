/*
 * File Name:         hdl_prj/ipcore/uz_sine_generator_16bit_v1_0/include/uz_sine_generator_16bit_addr.h
 * Description:       C Header File
 * Created:           2024-07-09 16:13:00
 */

#ifndef UZ_SINE_GENERATOR_16BIT_H_
#define UZ_SINE_GENERATOR_16BIT_H_

#define IPCore_Reset_uz_sine_generator_16bit 0x0         // write 0x1 to bit 0 to reset IP core
#define IPCore_Enable_uz_sine_generator_16bit 0x4        // enabled (by default) when bit 0 is 0x1
#define IPCore_Timestamp_uz_sine_generator_16bit 0x8     // contains unique IP timestamp (yymmddHHMM): 2407091605: 2407091609: 2407091612
#define amplitude_1_Data_uz_sine_generator_16bit 0x100   // data register for Inport amplitude_1
#define phase_shift_1_Data_uz_sine_generator_16bit 0x104 // data register for Inport phase_shift_1
#define frequency_1_Data_uz_sine_generator_16bit 0x108   // data register for Inport frequency_1
#define enable_sine_Data_uz_sine_generator_16bit 0x10C   // data register for Inport enable_sine
#define reset_sine_Data_uz_sine_generator_16bit 0x110    // data register for Inport reset_sine
#define amplitude_2_Data_uz_sine_generator_16bit 0x114   // data register for Inport amplitude_2
#define phase_shift_2_Data_uz_sine_generator_16bit 0x118 // data register for Inport phase_shift_2
#define frequency_2_Data_uz_sine_generator_16bit 0x11C   // data register for Inport frequency_2
#define amplitude_3_Data_uz_sine_generator_16bit 0x120   // data register for Inport amplitude_3
#define phase_shift_3_Data_uz_sine_generator_16bit 0x124 // data register for Inport phase_shift_3
#define frequency_3_Data_uz_sine_generator_16bit 0x128   // data register for Inport frequency_3
#define amplitude_4_Data_uz_sine_generator_16bit 0x12C   // data register for Inport amplitude_4
#define phase_shift_4_Data_uz_sine_generator_16bit 0x130 // data register for Inport phase_shift_4
#define frequency_4_Data_uz_sine_generator_16bit 0x134   // data register for Inport frequency_4
#define amplitude_5_Data_uz_sine_generator_16bit 0x138   // data register for Inport amplitude_5
#define phase_shift_5_Data_uz_sine_generator_16bit 0x13C // data register for Inport phase_shift_5
#define frequency_5_Data_uz_sine_generator_16bit 0x140   // data register for Inport frequency_5
#define amplitude_6_Data_uz_sine_generator_16bit 0x144   // data register for Inport amplitude_6
#define phase_shift_6_Data_uz_sine_generator_16bit 0x148 // data register for Inport phase_shift_6
#define amplitude_7_Data_uz_sine_generator_16bit 0x14C   // data register for Inport amplitude_7
#define frequency_6_Data_uz_sine_generator_16bit 0x150   // data register for Inport frequency_6
#define phase_shift_7_Data_uz_sine_generator_16bit 0x154 // data register for Inport phase_shift_7
#define frequency_7_Data_uz_sine_generator_16bit 0x158   // data register for Inport frequency_7
#define amplitude_8_Data_uz_sine_generator_16bit 0x15C   // data register for Inport amplitude_8
#define phase_shift_8_Data_uz_sine_generator_16bit 0x160 // data register for Inport phase_shift_8
#define frequency_8_Data_uz_sine_generator_16bit 0x164   // data register for Inport frequency_8

#endif /* UZ_SINE_GENERATOR_16BIT_H_ */
