#ifndef UZ_VSD_OPFFD_ASYM6PH_H
#define UZ_VSD_OPFFD_ASYM6PH_H

#include "VSD_FD_6PH_V4_ert_rtw/VSD_FD_6PH_V4.h"


typedef struct{
	ExtY_VSD_FD_6PH_V4 output;
	ExtU_VSD_FD_6PH_V4 input;
	DW_VSD_FD_6PH_V4 rtDW;
	RT_MODEL_VSD_FD_6PH_V4 modelData;
	RT_MODEL_VSD_FD_6PH_V4 *PtrToModelData;
}uz_vsd_opffd_asym6ph;


void uz_vsd_opffd_asym6ph_init(uz_vsd_opffd_asym6ph *self);
void uz_vsd_opffd_asym6ph_step(uz_vsd_opffd_asym6ph *self);



#endif //UZ_VSD_OPFFD_ASYM6PH_H
