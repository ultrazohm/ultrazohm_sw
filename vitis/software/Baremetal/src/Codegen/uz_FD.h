#ifndef UZ_VSD_H
#define UZ_VSD_H

#include "VSD_FD_6PH_V6_ert_rtw/VSD_FD_6PH_V6.h"


typedef struct{
	ExtY_VSD_FD_6PH_V6 output;
	ExtU_VSD_FD_6PH_V6 input;
	DW_VSD_FD_6PH_V6 rtDW;
	RT_MODEL_VSD_FD_6PH_V6 modelData;
	RT_MODEL_VSD_FD_6PH_V6 *PtrToModelData;
}uz_FD;


void uz_FD_init(uz_FD *self);
void uz_FD_step(uz_FD *self);



#endif //UZ_VSD_OPFFD_ASYM6PH_H
