#include "uz_codegen.h"

void uz_codegen_init(uz_codegen *self){
	self->PtrToModelData=&self->modelData;
	self->PtrToModelData->dwork=&self->rtDW;
	self->PtrToModelData->inputs=&self->input;
	self->PtrToModelData->outputs=&self->output;
}

void uz_codegen_step(uz_codegen *self){
	uz_codegen0_step(self->PtrToModelData);
}
