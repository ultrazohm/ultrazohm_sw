#include "uz_vsd_opf_fd_v7.h"

void uz_vsd_opf_fd_v7_init(uz_vsd_opf_fd_v7 *self){

	self->PtrToModelData=&self->modelData;
	self->PtrToModelData->dwork=&self->rtDW;
	self->PtrToModelData->inputs=&self->input;
	self->PtrToModelData->outputs=&self->output;
}

void uz_vsd_opf_fd_v7_step(uz_vsd_opf_fd_v7 *self){
	VSD_FD_6PH_V7_step(self->PtrToModelData);
}

