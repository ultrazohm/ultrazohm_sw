#pragma once

#define  IPCore_Reset_uz_JL_invModel_ideal       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_JL_invModel_ideal      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_JL_invModel_ideal   0x8  //contains unique IP timestamp (yymmddHHMM): 2605131121
#define  Udc_Data_uz_JL_invModel_ideal           0x100  //data register for Inport Udc
#define  InvOut_PS_Data_uz_JL_invModel_ideal     0x110  //data register for Outport InvOut_PS. Vector with 3 elements. Register is split across a total of 3 addresses, last address is 0x118.
#define  InvOut_PS_Strobe_uz_JL_invModel_ideal   0x120  //strobe register for port InvOut_PS
