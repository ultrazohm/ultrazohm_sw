#include "uz_codegen.h"


//static RT_MODEL rtM_;
//static RT_MODEL *const rtMPtr = &rtM_; /* Real-time model */
//static 	DW rtDW;                        /* Observable states */
//static 	ExtU rtU;                       /* External inputs */
//static 	ExtY rtY;                       /* External outputs */

//void uz_codegen_init(){
//	rtMPtr->dwork = &rtDW;
//	rtMPtr->inputs = &rtU;
//	rtMPtr->outputs = &rtY;
//	uz_codegen0_initialize(rtMPtr);
//}

//void uz_codegen_updateValues(uz_codegenStruct self){
//	rtMPtr->inputs->time=data.time;
//}

//void uz_codegen_step(){
//	  uz_codegen0_step(rtMPtr);
//}

void uz_codegen_init(uz_codegenStruct *self){
	self->PtrToModelData=&self->modelData;
	self->PtrToModelData->dwork=&self->rtDW;
	self->PtrToModelData->inputs=&self->input;
	self->PtrToModelData->outputs=&self->output;

}

void uz_codegen_step(uz_codegenStruct *self){
	uz_codegen0_step(self->PtrToModelData);
}
