/******************************************************************************
Jonathan Link 2026
******************************************************************************/

#include "../include/JL_SH_Umrichter.h"

conv_status_signals_t conv_status_signals = {
    .pwr_en = false,
    .board_en = false,
    .board_rst = false,
    .board_ready = false,   
    .igbt_desat = false
};
