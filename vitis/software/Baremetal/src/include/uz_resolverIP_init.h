/******************************************************************************
* Copyright 2021 Eyke Liegmann, Sebastian Wendel
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

#ifndef RESOLVER_H_
#define RESOLVER_H_

#include "../uz/controlToolbox/control_toolbox.h"
#include "../globalData.h"


/**
 * @brief Initializes resolverIP
 *
 */
void initialize_resolverIP(void);

/**
 * @brief Writes the electrical and mechanical position to global data structure, separate trigger neccessary on IPCore sample trigger input
 *
 */
void update_position_of_resolverIP(DS_Data *const data);

/**
 * @brief Writes the mechanical velocity to global data structure, separate trigger neccessary on IPCore sample trigger input
 *
 */
void update_speed_of_resolverIP(DS_Data *const data);					// update speed in global data struct

/**
 * @brief Writes the electrical and mechanical position and mechanical velocity to global data structure, separate trigger neccessary on IPCore sample trigger input
 *
 */
void update_position_and_speed_of_resolverIP(DS_Data* const data);

/**
 * @brief Reads Register
 *
 */
void readRegister_of_resolverIP(DS_Data* const data);

#endif /* RESOLVER_H_ */
