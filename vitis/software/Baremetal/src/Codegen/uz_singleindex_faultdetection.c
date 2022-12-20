#include "uz_singleindex_faultdetection.h"

void uz_singleindex_faultdetection_init(uz_singleindex_faultdetection *self){

	self->PtrToModelData=&self->modelData;
	self->PtrToModelData->dwork=&self->rtDW;
	self->PtrToModelData->inputs=&self->input;
	self->PtrToModelData->outputs=&self->output;
}

void uz_singleindex_faultdetection_step(uz_singleindex_faultdetection *self){
	Single_Index_Fault_Detection_step(self->PtrToModelData);
}

