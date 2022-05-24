#ifndef UZ_SINGLEINDEX_FAULTDETECTION_H
#define UZ_SINGLEINDEX_FAULTDETECTION_H

#include "Single_Index_Fault_Detection_ert_rtw/Single_Index_Fault_Detection.h"


typedef struct{
	ExtY_Single_Index_Fault_Detecti output;
	ExtU_Single_Index_Fault_Detecti input;
	DW_Single_Index_Fault_Detection rtDW;
	RT_MODEL_Single_Index_Fault_Det modelData;
	RT_MODEL_Single_Index_Fault_Det *PtrToModelData;
}uz_singleindex_faultdetection;




void uz_singleindex_faultdetection_init(uz_singleindex_faultdetection *self);
void uz_singleindex_faultdetection_step(uz_singleindex_faultdetection *self);



#endif //UZ_SINGLEINDEX_FAULTDETECTION_H
