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
#ifndef UZ_FLUSSSCHAETZER_H
#define UZ_FLUSSSCHAETZER_H

#include "../uz/uz_Transformation/uz_Transformation.h"


typedef struct uz_Flussschaetzer_t uz_Flussschaetzer_t;


struct uz_Flussschaetzer_config
{

};

typedef struct {
  float theta_el_kor;
  float omega_m_est;
  float psi_beta_filt;
  float psi_alpha_filt;
  float theta_el_est;
  float psi_beta;
  float psi_alpha;
  float omega_el_raw;
}Flussschaetzer_output_data ;

uz_Flussschaetzer_t *uz_Flussschaetzer_init(struct uz_Flussschaetzer_config config);


Flussschaetzer_output_data uz_Flussschaetzer_step(uz_Flussschaetzer_t *self,uz_3ph_alphabeta_t u_alphabeta_ref,uz_3ph_alphabeta_t i_alphabeta_meas,float integrator_reset);


void uz_Flussschaetzer_reset(uz_Flussschaetzer_t *self);


Flussschaetzer_output_data uz_Flussschaetzer_get_output(uz_Flussschaetzer_t *self);

void uz_Flussschaetzer_set_config(uz_Flussschaetzer_t *self, struct uz_Flussschaetzer_config config);




#endif // UZ_FLUSSSCHAETZER_H
