#include "uz_resonant_controller.h"

void uz_resonant_controller_init(uz_resonant_controller *self){

	self->PtrToModelData=&self->modelData;
	self->PtrToModelData->dwork=&self->dwork;
	self->PtrToModelData->inputs=&self->input;
	self->PtrToModelData->outputs=&self->output;
}

void uz_resonant_controller_step(uz_resonant_controller *self){
	Resonanz_Regler_1_step(self->PtrToModelData);
}
