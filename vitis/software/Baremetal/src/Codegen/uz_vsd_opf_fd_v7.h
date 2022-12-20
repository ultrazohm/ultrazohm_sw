#ifndef UZ_VSD_OPF_FD_H
#define UZ_VSD_OPF_FD_H

#include "VSD_FD_6PH_V7_ert_rtw/VSD_FD_6PH_V7.h"


typedef struct{
	ExtY_VSD_FD_6PH_V7 output;
	ExtU_VSD_FD_6PH_V7 input;
	DW_VSD_FD_6PH_V7 rtDW;
	RT_MODEL_VSD_FD_6PH_V7 modelData;
	RT_MODEL_VSD_FD_6PH_V7 *PtrToModelData;
}uz_vsd_opf_fd_v7;


void uz_vsd_opf_fd_v7_init(uz_vsd_opf_fd_v7 *self);
void uz_vsd_opf_fd_v7_step(uz_vsd_opf_fd_v7 *self);



#endif //UZ_VSD_OPF_FD_H
