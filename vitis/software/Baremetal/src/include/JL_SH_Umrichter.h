/******************************************************************************
Jonathan Link 2026
******************************************************************************/

#ifndef INCLUDE_JL_SH_UMRICHTER_H_
#define INCLUDE_JL_SH_UMRICHTER_H_

#include <stdbool.h>

#define PWR_EN_BIT 6
#define BOARD_EN_BIT 8
#define BOARD_RST_BIT 10
#define BOARD_READY_BIT 1
#define IGBT_Desat_BIT 3

// Regelungsart im control_state der Zustandsmaschine (Global_Data.rasv.ctrl_state)
typedef enum _ctrl_state_t_ {
	ctrl_state_none = 0, // Anfangszustand: keiner der folgenden Zustaende aktiv
	current_control,
	rpm_control,
	test_sine,
	test_square,
	DPT // Doppelpulstest, siehe uz_dpt.h
} ctrl_state_t;

typedef struct Conv_status_signals_t_ {
	bool pwr_en;
	bool board_en;
	bool board_rst;
	bool board_ready;
	bool igbt_desat;
} conv_status_signals_t;

#endif /* INCLUDE_JL_SH_UMRICHTER_H_ */
