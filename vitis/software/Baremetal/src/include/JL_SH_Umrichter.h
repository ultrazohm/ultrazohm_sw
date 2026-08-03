/******************************************************************************
Jonathan Link 2026
******************************************************************************/

#ifndef INCLUDE_JL_SH_UMRICHTER_H_
#define INCLUDE_JL_SH_UMRICHTER_H_

// Regelungsart im control_state der Zustandsmaschine (Global_Data.rasv.ctrl_state)
typedef enum _ctrl_state_t_ {
	ctrl_state_none = 0, // Anfangszustand: keiner der folgenden Zustaende aktiv
	current_control,
	rpm_control,
	test_sine
} ctrl_state_t;

#endif /* INCLUDE_JL_SH_UMRICHTER_H_ */
