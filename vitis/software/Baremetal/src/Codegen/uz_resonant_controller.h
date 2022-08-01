#ifndef UZ_RESONANT_CONTROLLER_H
#define UZ_RESONANT_CONTROLLER_H

#include "Resonanz_Regler_1_ert_rtw/Resonanz_Regler_1.h"


typedef struct{
	ExtU_Resonanz_Regler_1_T input;
	ExtY_Resonanz_Regler_1_T output;
	DW_Resonanz_Regler_1_T dwork;
	RT_MODEL_Resonanz_Regler_1_T modelData;
	RT_MODEL_Resonanz_Regler_1_T *PtrToModelData;
}uz_resonant_controller;


void uz_resonant_controller_init(uz_resonant_controller *self);
void uz_resonant_controller_step(uz_resonant_controller *self);



#endif //UZ_RESONANT_CONTROLLER_H
