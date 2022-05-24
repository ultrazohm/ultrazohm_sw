#include "uz_FD.h"

void uz_FD_init(uz_FD *self){

	self->PtrToModelData=&self->modelData;
	self->PtrToModelData->dwork=&self->rtDW;
	self->PtrToModelData->inputs=&self->input;
	self->PtrToModelData->outputs=&self->output;
}

void uz_FD_step(uz_FD *self){
	VSD_FD_6PH_V6_step(self->PtrToModelData);
}

