/******************************************************************************
 * Copyright 2022 Josef Knoblach
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
#ifndef UZ_RESONANTCONTROLLER_H
#define UZ_RESONANTCONTROLLER_H

#include "Resonant_Controller_ert_rtw/Resonant_Controller.h"

/**
 * @brief Struct definition for uz_resonantController
 *
 */
typedef struct uz_resonantController{
	ExtU_Resonant_Controller_T input;	/**< Input struct of the resonant controller*/
	ExtY_Resonant_Controller_T output;	/**< Output struct of the resonant controller*/
	DW_Resonant_Controller_T dwork;
	RT_MODEL_Resonant_Controller_T modelData;
	RT_MODEL_Resonant_Controller_T *PtrToModelData;
}uz_resonantController;


/**
 * @brief init function for the resonant controller
 * @return uz_resonant_controller* to the resonant controller
 */
uz_resonantController* uz_resonantController_init(void);

/**
 * @brief step function of the resonant controller, steps the controller once
 * @param self pointer to uz_resonantController* object
 * @return void
 */
void uz_resonantController_step(uz_resonantController *self);

/**
 * @brief reset function of the resonant controller
 * @param self pointer to uz_resonantController* object
 * @return void
 */
void uz_resonantController_reset(uz_resonantController *self);


#endif //UZ_RESONANTCONTROLLER_H
