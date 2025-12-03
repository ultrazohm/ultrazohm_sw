/******************************************************************************
 * Copyright 2025 Andreas Geiger
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 ******************************************************************************/

#ifndef __misc_IO_h__
#define __misc_IO_h__

#include "../main.h"

/* public functions */
uint32_t uz_get_misc_inputs(void);
void uz_set_misc_outputs(uint8_t KL15, uint8_t PYRO_TRIGGER, uint8_t RELAY2_CLOSE, uint8_t RELAY3_CLOSE);

#endif /* __misc_IO_h__ */
