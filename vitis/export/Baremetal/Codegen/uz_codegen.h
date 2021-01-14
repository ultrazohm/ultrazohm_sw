#include "uz_codegen0_ert_rtw/uz_codegen0.h"

typedef struct{
	ExtY output;
	ExtU input;
	DW rtDW;                        /* Observable states */
	RT_MODEL modelData;
	RT_MODEL *PtrToModelData;
}uz_codegen;

void uz_codegen_init(uz_codegen *self);
void uz_codegen_step(uz_codegen *self);
