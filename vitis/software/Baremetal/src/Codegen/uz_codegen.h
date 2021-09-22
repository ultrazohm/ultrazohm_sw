/******************************************************************************
* Copyright 2021 Tobias Schindler
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
******************************************************************************/
#include "Regelung_ert_rtw/Regelung.h"

typedef struct{
	ExtY output;
	ExtU input;
	DW rtDW;                        /* Observable states */
	RT_MODEL modelData;
	RT_MODEL *PtrToModelData;
}uz_codegen;

void uz_codegen_init(uz_codegen *self);
void uz_codegen_step(uz_codegen *self);
