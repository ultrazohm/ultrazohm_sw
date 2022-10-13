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
typedef struct uz_resonantController_t{
	ExtU_Resonant_Controller_T input;	/**< Input struct of the resonant controller*/
	ExtY_Resonant_Controller_T output;	/**< Output struct of the resonant controller*/
	DW_Resonant_Controller_T dwork;
	RT_MODEL_Resonant_Controller_T modelData;
	RT_MODEL_Resonant_Controller_T *PtrToModelData;
}uz_resonantController_t;

/**
 * @brief Configuration struct for PI-Controller. Pass to init function. Accessible by the user
 */
struct uz_resonantController_config {
	float T_sw;			/**< SamplingTime of the PI-Controller in seconds. Must be greater than 0.0f */
	float VR;			/**< Gain of the resonant Controller*/
	float h;			/**< Order of harmonic to be controlled*/
	float omega_el;		/**< Fundamental Frequency in rad/s */
	float lower_limit;	/**< Lower limit for the output limitation */
	float upper_limit;	/**< Upper limit for the output limitation. Must be greater than lower limit */
	float Klim;			/**< Gain of anti-windup feedback*/
	float in_ref;		/**< Input reference value*/
	float in_m;			/**< Input measured value*/
	float Reset;		/**< Reset input*/
};




/**
 * @brief init function for the resonant controller
 * @param uz_resonantController_config config for the resonant controller
 * @return uz_resonant_controller* to the resonant controller
 */
uz_resonantController_t* uz_resonantController_init(struct uz_resonantController_config config);

/**
 * @brief step function of the resonant controller, steps the controller once
 * @param self pointer to uz_resonantController_t* object
 * @return void
 */
void uz_resonantController_step(uz_resonantController_t *self);

/**
 * @brief reset function of the resonant controller
 * @param self pointer to uz_resonantController_t* object
 * @return void
 */
void uz_resonantController_reset(uz_resonantController_t *self);


/**
 * @brief returns output of the resonant controller
 * @param self pointer to uz_resonantController_t* object
 * @return float output value
 */
float uz_resonantController_get_output(uz_resonantController_t *self);


/**
 * @brief sets input of the resonant controller
 * @param self pointer to uz_resonantController_t* object
 * @param float in_ref input reference value for the controller
 * @param float in_m input measured value for the controller
 * @param float omega_el current omega_el for the controller
 * @return void
 */
void uz_resonantController_set_input(uz_resonantController_t *self, float in_ref, float in_m, float omega_el);


/**
 * @brief sets config of resonant controller
 * @param self pointer to uz_resonantController_t* object
 * @param struct uz_resonantController_config config new config for the resonant controller
 * @return void
 */
void uz_resonantController_config(uz_resonantController_t *self, struct uz_resonantController_config config);


#endif //UZ_RESONANTCONTROLLER_H
