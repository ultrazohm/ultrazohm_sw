#include "uz_resonant_controller.h"

void uz_resonantController_init(uz_resonantController *self){

	self->PtrToModelData=&self->modelData;
	self->PtrToModelData->dwork=&self->dwork;
	self->PtrToModelData->inputs=&self->input;
	self->PtrToModelData->outputs=&self->output;
}

void uz_resonantController_step(uz_resonantController *self){
	Resonant_Controller_step(self->PtrToModelData);
}

void uz_resonantController_reset(uz_resonantController *self){
	self->PtrToModelData->inputs->Reset = 1.0;
	self->PtrToModelData->inputs->in_m = 0.0;
	self->PtrToModelData->inputs->in_ref = 0.0;
	Resonant_Controller_step(self->PtrToModelData);
	self->PtrToModelData->inputs->Reset = 0.0;
}
