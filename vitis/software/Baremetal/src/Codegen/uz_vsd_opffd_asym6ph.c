#include "uz_vsd_opffd_asym6ph.h"

void uz_vsd_opffd_asym6ph_init(uz_vsd_opffd_asym6ph *self){

	self->PtrToModelData=&self->modelData;
	self->PtrToModelData->dwork=&self->rtDW;
	self->PtrToModelData->inputs=&self->input;
	self->PtrToModelData->outputs=&self->output;
}

void uz_vsd_opffd_asym6ph_step(uz_vsd_opffd_asym6ph *self){
	VSD_FD_6PH_V4_step(self->PtrToModelData);
}

