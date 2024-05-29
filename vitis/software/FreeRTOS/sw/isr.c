/******************************************************************************
* Copyright 2021 Sebastian Wendel, Eyke Liegmann
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

#include "xparameters.h"
#include "netif/xadapter.h"

#if LWIP_DHCP==1
#include "lwip/dhcp.h"
#endif

#include "../include/isr.h"
#include "../defines.h"
#include "APU_RPU_shared.h"
#include "xil_cache.h"
#include "../uz/uz_global_configuration.h"

// define the size of the cache to flush
#define CACHE_FLUSH_SIZE_RPU_TO_APU sizeof(*rpu_to_apu_user_data)
#define CACHE_FLUSH_SIZE_APU_TO_RPU sizeof(*apu_to_rpu_user_data)

struct APU_to_RPU_t ControlData;
extern int js_connection_established;

// cf. main.c
extern uint32_t javascope_data_status;

// Javascope Queue parameters
QueueHandle_t js_queue;
int js_queue_full = 0;

int i_LifeCheck_Transfer_ipc;

//Initialize the Interrupt structure
XScuGic INTCipc;	//Interrupt for IPC
XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!
XScuGic_Config *IntcConfig;



//************************************************************
bool control_state_active = false;
bool select_CIL = false;
bool select_CurrentControl = false;
bool select_DDPG_1_64 = false;
bool select_Real = false;
float n_ref_rpm = 0.0f;
#define NUMBER_OF_INPUTS_15N 15U
#define NUMBER_OF_INPUTS_17N 17U
uz_matrix_t* matrix_output_15n;
uz_matrix_t* matrix_output_17n;
uz_6ph_dq_t v_dqxy_limited_volts = {0};
uz_3ph_dq_t v_dq_limited_volts = {0};
uz_3ph_dq_t v_xy_limited_volts = {0};
uz_3ph_dq_t v_dq_non_limited_volts = {0};
uz_3ph_dq_t v_xy_non_limited_volts = {0};
uz_6ph_dq_t v_dqxy_limited_volts_k_old = {0};
uz_6ph_dq_t v_dqxy_non_limited_volts = {0};
uz_6ph_dq_t CIL_i_dqxy_meas = {0};
uz_6ph_abc_t REAL_i_abc_meas = {0};
uz_6ph_abc_t REAL_v_abc_meas = {0};
uz_6ph_abc_t REAL_v_abc_ref = {0};
uz_6ph_dq_t REAL_i_dqxy_meas = {0};
uz_6ph_dq_t REAL_v_dqxy_meas = {0};
uz_6ph_dq_t i_dqxy_integrated_error = {0};
uz_6ph_dq_t i_dqxy_error = {0};
uz_3ph_dq_t CIL_v_dq_reference = {0};
uz_3ph_dq_t CIL_v_xy_reference = {0};
uz_3ph_dq_t CIL_v_z1z2_reference = {0};
uz_3ph_dq_t REAL_v_dq_reference = {0};
uz_3ph_dq_t REAL_v_xy_reference = {0};
uz_3ph_dq_t REAL_v_z1z2_reference = {0};
uz_3ph_dq_t i_dq_reference = {0};
uz_3ph_dq_t i_xy_reference = {0};
uz_3ph_dq_t i_z1z2_reference = {0};
uz_3ph_dq_t CIL_i_dq_meas= {0};
uz_3ph_dq_t CIL_i_xy_meas = {0};
uz_3ph_dq_t CIL_i_z1z2_meas = {0};
uz_3ph_dq_t REAL_i_dq_meas= {0};
uz_3ph_dq_t REAL_i_xy_meas = {0};
uz_3ph_dq_t REAL_i_z1z2_meas = {0};
struct uz_DutyCycle_2x3ph_t DutyCycle_output = {0};
float CIL_omega_mech = 100.0f; //fixed speed for the CIL model
float max_modulation_index = (1.0f / 2.0f) * 0.707106781f;
float ts = 1.0f / UZ_ISR_FREQUENCY;
float V_DC_Volts = 36.0f;
float U_max = (36.0f / 2.0f) * 0.707106781f;
float Voltage_Scaling = 1.0f / (36.0f / 2.0f);
float rated_current = 18.0f;//24.0f;
float polepairs = 5.0f;
float rated_Speed_rpm = 1100.0f;
float speed_weight = 1.0f / 1100.0f;
bool ext_clamping_dq = false;
bool ext_clamping_xy = false;
float i_d_ref = 0.0f;
float i_q_ref = 0.0f;
float i_X_ref = 0.0f;
float i_Y_ref = 0.0f;
float omega_elec = 0.0f;
float v_dc1 = 0.0f;
float theta_elec = 0.0f;
float mechanicalRotorSpeed = 0.0f;
float DutyCycle_A1 = 0.0f;
float DutyCycle_B1 = 0.0f;
float DutyCycle_C1 = 0.0f;
float DutyCycle_A2 = 0.0f;
float DutyCycle_B2 = 0.0f;
float DutyCycle_C2 = 0.0f;
float observation_ip_15n[NUMBER_OF_INPUTS_15N] = {0};
float observation_ip_17n[NUMBER_OF_INPUTS_17N] = {0};
extern uz_CurrentControl_t* CC_dq_instance;
extern uz_CurrentControl_t* CC_xy_instance;
extern uz_matrix_t* matrix_input_17n;
extern uz_nn_t* nn_layer_17n;
extern uz_matrix_t* matrix_input_15n;
extern uz_nn_t* nn_layer_15n;
/**
 * Apu_IpiHandler() - Interrupt handler for IPI
 *
 * @IpiInstPtr		Pointer to the IPI instance
 */
// Standard isr interrupt from BareMetal -> frequency depends on the Software-interrupt from BareMetal
void Transfer_ipc_Intr_Handler(void *data)
{
	// create pointer to javascope_data_t named javascope_data located at MEM_SHARED_START_OCM_BANK_3_JAVASCOPE
	struct javascope_data_t volatile * const javascope_data = (struct javascope_data_t*)MEM_SHARED_START_OCM_BANK_3_JAVASCOPE;
	// create pointers to user data variables located in OCM Bank 1 and 2
	struct RPU_to_APU_user_data_t volatile * const rpu_to_apu_user_data = (struct RPU_to_APU_user_data_t*)MEM_SHARED_START_OCM_BANK_1_RPU_TO_APU;
	struct APU_to_RPU_user_data_t volatile * const apu_to_rpu_user_data = (struct APU_to_RPU_user_data_t*)MEM_SHARED_START_OCM_BANK_2_APU_TO_RPU;
	int status;
	BaseType_t xHigherPriorityTaskWoken;


	// flush cache of shared memory for javascope data
	Xil_DCacheFlushRange( MEM_SHARED_START_OCM_BANK_3_JAVASCOPE, JAVASCOPE_DATA_SIZE_2POW);

	// if javascope connection is established
	if(js_connection_established!=0)
	{
		// append sample to queue
		size_t queue_status = xQueueSendToBackFromISR(js_queue, javascope_data, &xHigherPriorityTaskWoken);

		if (queue_status == errQUEUE_FULL)
		{
			js_queue_full++;
			// uz_printf("OsziData_queue is full\r\n");
		}
	}
	// queue is purged when new connection is established

	// Maintain APU-local copy of status word (cf. main.c)
	javascope_data_status = javascope_data->status;

	u32_t ControlData_length = sizeof(ControlData)/sizeof(float); // XIpiPsu_WriteMessage expects number of 32bit values as message length

#if (USE_A53_AS_ACCELERATOR_FOR_R5_ISR == TRUE)
	// invalidate cache of shared memory before read
	Xil_DCacheInvalidateRange( MEM_SHARED_START_OCM_BANK_1_RPU_TO_APU, CACHE_FLUSH_SIZE_RPU_TO_APU);

	// get data from r5 from shared memory
	control_state_active  = rpu_to_apu_user_data->control_state_active;
	select_CurrentControl = rpu_to_apu_user_data->select_CurrentControl;
	select_CIL = rpu_to_apu_user_data->select_CIL;
	select_Real = rpu_to_apu_user_data->select_Real;
	select_DDPG_1_64 = rpu_to_apu_user_data->select_DDPG_1_64;
	i_dq_reference.d = rpu_to_apu_user_data->i_dq_reference_d;
	i_dq_reference.q = rpu_to_apu_user_data->i_dq_reference_q;
	i_xy_reference.d = rpu_to_apu_user_data->i_xy_reference_x;
	i_xy_reference.q = rpu_to_apu_user_data->i_xy_reference_y;
	CIL_i_dq_meas.d = rpu_to_apu_user_data->CIL_i_dq_meas_d;
	CIL_i_dq_meas.q = rpu_to_apu_user_data->CIL_i_dq_meas_q;
	CIL_i_xy_meas.d = rpu_to_apu_user_data->CIL_i_xy_meas_x;
	CIL_i_xy_meas.q = rpu_to_apu_user_data->CIL_i_xy_meas_y;
	omega_elec = rpu_to_apu_user_data->omega_elec;
	mechanicalRotorSpeed = rpu_to_apu_user_data->mechanicalRotorSpeed;
	REAL_i_dq_meas.d = rpu_to_apu_user_data->REAL_i_dq_meas_d;
	REAL_i_dq_meas.q = rpu_to_apu_user_data->REAL_i_dq_meas_q;
	REAL_i_xy_meas.d = rpu_to_apu_user_data->REAL_i_xy_meas_x;
	REAL_i_xy_meas.q = rpu_to_apu_user_data->REAL_i_xy_meas_y;


	/* do your computations that you want to accelerate here... */
	 if (control_state_active)
	       {
	           if(select_CIL) {

	           	if(select_CurrentControl) {
	           		v_dq_limited_volts = uz_CurrentControl_sample(CC_dq_instance, i_dq_reference, CIL_i_dq_meas, V_DC_Volts, omega_elec);
	           		v_xy_limited_volts = uz_CurrentControl_sample(CC_xy_instance, i_xy_reference, CIL_i_xy_meas, V_DC_Volts, omega_elec);

	           	} else if(select_DDPG_1_64) {
	       			if(ext_clamping_dq == false && ext_clamping_xy == false) {
	       				i_dqxy_integrated_error.d = (i_dqxy_integrated_error.d + (i_dqxy_error.d * ts)); // use Forward-Euler with error of previous timestep for integration
	       				i_dqxy_integrated_error.q = (i_dqxy_integrated_error.q + (i_dqxy_error.q * ts));
	       				i_dqxy_integrated_error.x = (i_dqxy_integrated_error.x + (i_dqxy_error.x * ts));
	       				i_dqxy_integrated_error.y = (i_dqxy_integrated_error.y + (i_dqxy_error.y * ts));
	       			} else {
	       				i_dqxy_integrated_error.d += 0.0f;
	       				i_dqxy_integrated_error.q += 0.0f;
	       				i_dqxy_integrated_error.x += 0.0f;
	       				i_dqxy_integrated_error.y += 0.0f;
	       			}
	       		i_dqxy_error.d = (i_dq_reference.d - CIL_i_dq_meas.d) / rated_current;
	       		i_dqxy_error.q = (i_dq_reference.q - CIL_i_dq_meas.q) / rated_current;
	       		i_dqxy_error.x = (i_xy_reference.d - CIL_i_xy_meas.d) / rated_current;
	       		i_dqxy_error.y = (i_xy_reference.q - CIL_i_xy_meas.q) / rated_current;
	#if NN_15_INPUT_1_64==1
	       		observation_ip_15n[0] = i_dqxy_error.d;
	       		observation_ip_15n[1] = i_dqxy_integrated_error.d * UZ_ISR_FREQUENCY;
	       		observation_ip_15n[2] = i_dqxy_error.q;
	       		observation_ip_15n[3] = i_dqxy_integrated_error.q * UZ_ISR_FREQUENCY;
	       		observation_ip_15n[4] = CIL_i_dq_meas.d / rated_current;
	       		observation_ip_15n[5] = CIL_i_dq_meas.q / rated_current;
	       		observation_ip_15n[6] = Global_Data.av.mechanicalRotorSpeed * speed_weight;
	       		observation_ip_15n[7] = v_dqxy_limited_volts.d * Voltage_Scaling;
	       		observation_ip_15n[8] = v_dqxy_limited_volts.q * Voltage_Scaling;
	       		observation_ip_15n[9] = i_dqxy_error.x;
	       		observation_ip_15n[10] = i_dqxy_integrated_error.x * UZ_ISR_FREQUENCY;
	       		observation_ip_15n[11] = i_dqxy_error.y;
	       		observation_ip_15n[12] = i_dqxy_integrated_error.y * UZ_ISR_FREQUENCY;
	       		observation_ip_15n[13] = v_dqxy_limited_volts.x * Voltage_Scaling;
	       		observation_ip_15n[14] = v_dqxy_limited_volts.y * Voltage_Scaling;
	   	        for (uint32_t i = 0; i < NUMBER_OF_INPUTS_15N; i++) {
	   	        	uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input_15n,observation_ip_15n[i],0U,i);
	   	        }
	   	        uz_nn_ff(Global_Data.objects.nn_layer_15n,Global_Data.objects.matrix_input_15n);
	   	        matrix_output_15n = uz_nn_get_output_data(Global_Data.objects.nn_layer_15n);
	   	        uz_matrix_multiply_by_scalar(matrix_output_15n,U_max); // scaling layer of nn
	   	        v_dq_non_limited_volts.d = uz_matrix_get_element_zero_based(matrix_output_15n,0U,0U);
	   	        v_dq_non_limited_volts.q = uz_matrix_get_element_zero_based(matrix_output_15n,0U,1U);
	   	        v_xy_non_limited_volts.d = uz_matrix_get_element_zero_based(matrix_output_15n,0U,2U);
	   	        v_xy_non_limited_volts.q = uz_matrix_get_element_zero_based(matrix_output_15n,0U,3U);
	#endif
	#if NN_17_INPUT_1_64==1
	       		observation_ip_17n[0] = i_dqxy_error.d;
	       		observation_ip_17n[1] = i_dqxy_integrated_error.d * UZ_ISR_FREQUENCY;
	       		observation_ip_17n[2] = i_dqxy_error.q;
	       		observation_ip_17n[3] = i_dqxy_integrated_error.q * UZ_ISR_FREQUENCY;
	       		observation_ip_17n[4] = CIL_i_dq_meas.d / rated_current;
	       		observation_ip_17n[5] = CIL_i_dq_meas.q / rated_current;
	       		observation_ip_17n[6] = mechanicalRotorSpeed * speed_weight;
	       		observation_ip_17n[7] = v_dqxy_limited_volts.d * Voltage_Scaling;
	       		observation_ip_17n[8] = v_dqxy_limited_volts.q * Voltage_Scaling;
	       		observation_ip_17n[9] = i_dqxy_error.x;
	       		observation_ip_17n[10] = i_dqxy_integrated_error.x * UZ_ISR_FREQUENCY;
	       		observation_ip_17n[11] = i_dqxy_error.y;
	       		observation_ip_17n[12] = i_dqxy_integrated_error.y * UZ_ISR_FREQUENCY;
	       		observation_ip_17n[13] = CIL_i_xy_meas.d / rated_current;
	       		observation_ip_17n[14] = CIL_i_xy_meas.q / rated_current;
	       		observation_ip_17n[15] = v_dqxy_limited_volts.x * Voltage_Scaling;
	       		observation_ip_17n[16] = v_dqxy_limited_volts.y * Voltage_Scaling;
	   	        for (uint32_t i = 0; i < NUMBER_OF_INPUTS_17N; i++) {
	   	        	uz_matrix_set_element_zero_based(matrix_input_17n,observation_ip_17n[i],0U,i);
	   	        }
	   	        uz_nn_ff(nn_layer_17n,matrix_input_17n);
	   	        matrix_output_17n = uz_nn_get_output_data(nn_layer_17n);
	   	        uz_matrix_multiply_by_scalar(matrix_output_17n,U_max); // scaling layer of nn
	   	        v_dq_non_limited_volts.d = uz_matrix_get_element_zero_based(matrix_output_17n,0U,0U);
	   	        v_dq_non_limited_volts.q = uz_matrix_get_element_zero_based(matrix_output_17n,0U,1U);
	   	        v_xy_non_limited_volts.d = uz_matrix_get_element_zero_based(matrix_output_17n,0U,2U);
	   	        v_xy_non_limited_volts.q = uz_matrix_get_element_zero_based(matrix_output_17n,0U,3U);
	#endif

	           	v_dq_limited_volts = uz_CurrentControl_SpaceVector_Limitation(v_dq_non_limited_volts, V_DC_Volts, max_modulation_index, omega_elec, CIL_i_dq_meas, &ext_clamping_dq);
	   			v_xy_limited_volts = uz_CurrentControl_SpaceVector_Limitation(v_xy_non_limited_volts, V_DC_Volts, max_modulation_index, omega_elec, CIL_i_xy_meas, &ext_clamping_xy);

	           	}

	           	v_dqxy_limited_volts.d = v_dq_limited_volts.d;
	           	v_dqxy_limited_volts.q = v_dq_limited_volts.q;
	           	v_dqxy_limited_volts.x = v_xy_limited_volts.d;
	           	v_dqxy_limited_volts.y = v_xy_limited_volts.q;
	           	v_dqxy_limited_volts.z1 = 0.0f;
	           	v_dqxy_limited_volts.z2 = 0.0f;

	           }

	           if(select_Real) {
	           	if(select_CurrentControl) {
	           		v_dq_limited_volts = uz_CurrentControl_sample(CC_dq_instance, i_dq_reference, REAL_i_dq_meas, v_dc1, omega_elec);
	           		v_xy_limited_volts = uz_CurrentControl_sample(CC_xy_instance, i_xy_reference, REAL_i_xy_meas, v_dc1, omega_elec);
	           	} else if(select_DDPG_1_64) {
	       			if(ext_clamping_dq == false && ext_clamping_xy == false) {
	       				i_dqxy_integrated_error.d = (i_dqxy_integrated_error.d + (i_dqxy_error.d * ts)); // use Forward-Euler with error of previous timestep for integration
	       				i_dqxy_integrated_error.q = (i_dqxy_integrated_error.q + (i_dqxy_error.q * ts));
	       				i_dqxy_integrated_error.x = (i_dqxy_integrated_error.x + (i_dqxy_error.x * ts));
	       				i_dqxy_integrated_error.y = (i_dqxy_integrated_error.y + (i_dqxy_error.y * ts));
	       			} else {
	       				i_dqxy_integrated_error.d += 0.0f;
	       				i_dqxy_integrated_error.q += 0.0f;
	       				i_dqxy_integrated_error.x += 0.0f;
	       				i_dqxy_integrated_error.y += 0.0f;
	       			}
	           		i_dqxy_error.d = (i_dq_reference.d - REAL_i_dq_meas.d) / rated_current;
	           		i_dqxy_error.q = (i_dq_reference.q - REAL_i_dq_meas.q) / rated_current;
	           		i_dqxy_error.x = (i_xy_reference.d - REAL_i_xy_meas.d) / rated_current;
	           		i_dqxy_error.y = (i_xy_reference.q - REAL_i_xy_meas.q) / rated_current;
	#if NN_15_INPUT_1_64==1
	           		observation_ip_15n[0] = i_dqxy_error.d;
	           		observation_ip_15n[1] = i_dqxy_integrated_error.d * UZ_ISR_FREQUENCY;
	           		observation_ip_15n[2] = i_dqxy_error.q;
	           		observation_ip_15n[3] = i_dqxy_integrated_error.q * UZ_ISR_FREQUENCY;
	           		observation_ip_15n[4] = REAL_i_dq_meas.d / rated_current;
	           		observation_ip_15n[5] = REAL_i_dq_meas.q / rated_current;
	           		observation_ip_15n[6] = mechanicalRotorSpeed * speed_weight;
	           		observation_ip_15n[7] = v_dqxy_limited_volts.d * Voltage_Scaling;
	           		observation_ip_15n[8] = v_dqxy_limited_volts.q * Voltage_Scaling;
	           		observation_ip_15n[9] = i_dqxy_error.x;
	           		observation_ip_15n[10] = i_dqxy_integrated_error.x * UZ_ISR_FREQUENCY;
	           		observation_ip_15n[11] = i_dqxy_error.y;
	           		observation_ip_15n[12] = i_dqxy_integrated_error.y * UZ_ISR_FREQUENCY;
	           		observation_ip_15n[13] = v_dqxy_limited_volts.x * Voltage_Scaling;
	           		observation_ip_15n[14] = v_dqxy_limited_volts.y * Voltage_Scaling;
	           		for (uint32_t i = 0; i < NUMBER_OF_INPUTS_15N; i++) {
	           			uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input_15n,observation_ip_15n[i],0U,i);
	           		}
	           		uz_nn_ff(Global_Data.objects.nn_layer_15n,Global_Data.objects.matrix_input_15n);
	           		matrix_output_15n = uz_nn_get_output_data(Global_Data.objects.nn_layer_15n);
	           		uz_matrix_multiply_by_scalar(matrix_output_15n,U_max); // scaling layer of nn
	           		v_dq_non_limited_volts.d = uz_matrix_get_element_zero_based(matrix_output_15n,0U,0U);
	           		v_dq_non_limited_volts.q = uz_matrix_get_element_zero_based(matrix_output_15n,0U,1U);
	           		v_xy_non_limited_volts.d = uz_matrix_get_element_zero_based(matrix_output_15n,0U,2U);
	           		v_xy_non_limited_volts.q = uz_matrix_get_element_zero_based(matrix_output_15n,0U,3U);
	#endif

	#if NN_17_INPUT_1_64==1
	           		observation_ip_17n[0] = i_dqxy_error.d;
	           		observation_ip_17n[1] = i_dqxy_integrated_error.d * UZ_ISR_FREQUENCY;
	           		observation_ip_17n[2] = i_dqxy_error.q;
	           		observation_ip_17n[3] = i_dqxy_integrated_error.q * UZ_ISR_FREQUENCY;
	           		observation_ip_17n[4] = REAL_i_dq_meas.d / rated_current;
	           		observation_ip_17n[5] = REAL_i_dq_meas.q / rated_current;
	           		observation_ip_17n[6] = mechanicalRotorSpeed * speed_weight;
	           		observation_ip_17n[7] = v_dqxy_limited_volts.d * Voltage_Scaling;
	           		observation_ip_17n[8] = v_dqxy_limited_volts.q * Voltage_Scaling;
	           		observation_ip_17n[9] = i_dqxy_error.x;
	           		observation_ip_17n[10] = i_dqxy_integrated_error.x * UZ_ISR_FREQUENCY;
	           		observation_ip_17n[11] = i_dqxy_error.y;
	           		observation_ip_17n[12] = i_dqxy_integrated_error.y * UZ_ISR_FREQUENCY;
	           		observation_ip_17n[13] = REAL_i_xy_meas.d / rated_current;
	           		observation_ip_17n[14] = REAL_i_xy_meas.q / rated_current;
	           		observation_ip_17n[15] = v_dqxy_limited_volts.x * Voltage_Scaling;
	           		observation_ip_17n[16] = v_dqxy_limited_volts.y * Voltage_Scaling;
	           		for (uint32_t i = 0; i < NUMBER_OF_INPUTS_17N; i++) {
	           			uz_matrix_set_element_zero_based(matrix_input_17n,observation_ip_17n[i],0U,i);
	           		}
	           		uz_nn_ff(nn_layer_17n,matrix_input_17n);
	           		matrix_output_17n = uz_nn_get_output_data(nn_layer_17n);
	           		uz_matrix_multiply_by_scalar(matrix_output_17n,U_max); // scaling layer of nn
	           		v_dq_non_limited_volts.d = uz_matrix_get_element_zero_based(matrix_output_17n,0U,0U);
	           		v_dq_non_limited_volts.q = uz_matrix_get_element_zero_based(matrix_output_17n,0U,1U);
	           		v_xy_non_limited_volts.d = uz_matrix_get_element_zero_based(matrix_output_17n,0U,2U);
	           		v_xy_non_limited_volts.q = uz_matrix_get_element_zero_based(matrix_output_17n,0U,3U);
	#endif
	           		v_dq_limited_volts = uz_CurrentControl_SpaceVector_Limitation(v_dq_non_limited_volts, V_DC_Volts, max_modulation_index, omega_elec, REAL_i_dq_meas, &ext_clamping_dq);
	           		v_xy_limited_volts = uz_CurrentControl_SpaceVector_Limitation(v_xy_non_limited_volts, V_DC_Volts, max_modulation_index, omega_elec, REAL_i_xy_meas, &ext_clamping_xy);

	           	}

	           	v_dqxy_limited_volts.d = v_dq_limited_volts.d;
	           	v_dqxy_limited_volts.q = v_dq_limited_volts.q;
	           	v_dqxy_limited_volts.x = v_xy_limited_volts.d;
	           	v_dqxy_limited_volts.y = v_xy_limited_volts.q;
	           	v_dqxy_limited_volts.z1 = 0.0f;
	           	v_dqxy_limited_volts.z2 = 0.0f;
	           	REAL_v_abc_ref = uz_transformation_asym30deg_6ph_dq_xy_to_abc(v_dqxy_limited_volts, theta_elec);
	           	DutyCycle_output = uz_spwm_abc_6ph(REAL_v_abc_ref, V_DC_Volts);
	           	DutyCycle_A1 = DutyCycle_output.system1.DutyCycle_A;
	           	DutyCycle_B1 = DutyCycle_output.system1.DutyCycle_B;
	           	DutyCycle_C1 = DutyCycle_output.system1.DutyCycle_C;
	           	DutyCycle_A2 = DutyCycle_output.system2.DutyCycle_A;
	           	DutyCycle_B2 = DutyCycle_output.system2.DutyCycle_B;
	           	DutyCycle_C2 = DutyCycle_output.system2.DutyCycle_C;

	           }

	       } else {
	       	uz_CurrentControl_reset(CC_dq_instance);
	       	uz_CurrentControl_reset(CC_xy_instance);
	       	ext_clamping_dq = false;
	       	ext_clamping_xy = false;
	       	v_dq_limited_volts.d = 0.0f;
	       	v_dq_limited_volts.q = 0.0f;
	       	v_xy_limited_volts.d = 0.0f;
	       	v_xy_limited_volts.q = 0.0f;
	       	i_dqxy_integrated_error.d = 0.0f;
	       	i_dqxy_integrated_error.q = 0.0f;
	       	i_dqxy_integrated_error.x = 0.0f;
	       	i_dqxy_integrated_error.y = 0.0f;
	       	DutyCycle_A1 = 0.0f;
	       	DutyCycle_B1 = 0.0f;
	       	DutyCycle_C1 = 0.0f;
	       	DutyCycle_A2 = 0.0f;
	       	DutyCycle_B2 = 0.0f;
	       	DutyCycle_C2 = 0.0f;

	       }

	// write data to r5 in shared memory and flush cache
	apu_to_rpu_user_data->slowDataCounter  = rpu_to_apu_user_data->slowDataCounter; //just an example
	apu_to_rpu_user_data->DutyCycle_A1 = DutyCycle_A1;
	apu_to_rpu_user_data->DutyCycle_B1 = DutyCycle_B1;
	apu_to_rpu_user_data->DutyCycle_C1 = DutyCycle_C1;
	apu_to_rpu_user_data->DutyCycle_A2 = DutyCycle_A2;
	apu_to_rpu_user_data->DutyCycle_B2 = DutyCycle_B2;
	apu_to_rpu_user_data->DutyCycle_C2 = DutyCycle_C2;
	apu_to_rpu_user_data->v_dqxy_limited_volts_d = v_dqxy_limited_volts.d;
	apu_to_rpu_user_data->v_dqxy_limited_volts_q = v_dqxy_limited_volts.q;
	apu_to_rpu_user_data->v_dqxy_limited_volts_x = v_dqxy_limited_volts.x;
	apu_to_rpu_user_data->v_dqxy_limited_volts_y = v_dqxy_limited_volts.y;

	Xil_DCacheFlushRange( MEM_SHARED_START_OCM_BANK_2_APU_TO_RPU, CACHE_FLUSH_SIZE_APU_TO_RPU);

	/* ...until here */
#endif

	// Write message for acknowledge of the interrupt to RPU
	status = XIpiPsu_WriteMessage(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK, (u32_t*)(&ControlData), ControlData_length, XIPIPSU_BUF_TYPE_RESP);

	// Valid IPI. Clear the appropriate bit in the respective ISR
	XIpiPsu_ClearInterruptStatus(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

	i_LifeCheck_Transfer_ipc++;

	if(i_LifeCheck_Transfer_ipc > 25000){
		i_LifeCheck_Transfer_ipc =0;
	}

	// force context switch after ISR finishes -> switching to ethernet task
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE THE INTERRUPT HAndler (from main)
//----------------------------------------------------
int Initialize_InterruptHandler(){

	int Status = XST_SUCCESS;

	// Interrupt controller configuration
	IntcConfig = XScuGic_LookupConfig(XPAR_SCUGIC_0_DEVICE_ID);
		if(IntcConfig == NULL) {
			uz_printf("APU: Error: GIC Config failed\r\n");
			return XST_FAILURE;
		}

	// Interrupt controller initialization
	Status = XScuGic_CfgInitialize(&INTCipc, IntcConfig, IntcConfig->CpuBaseAddress);
		if(Status != XST_SUCCESS) {
			uz_printf("APU: Error: GIC initialization failed\r\n");
			return XST_FAILURE;
		}

	return Status;
}


//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE & SET THE INTERRUPTs and ISRs
//----------------------------------------------------
int Initialize_ISR(){

	int Status = 0;

	// Initialize RPU GIC and Connect IPI interrupt
	Status = Apu_GicInit(&INTCipc, XPAR_XIPIPSU_0_INT_ID,(Xil_ExceptionHandler)Transfer_ipc_Intr_Handler, &INTCInst_IPI);
	if(Status != XST_SUCCESS) {
		uz_printf("APU: Error: GIC initialization failed\r\n");
		return XST_FAILURE;
	}

	// create queue for buffering R5 interrupt -> ethernet thread
	js_queue = xQueueCreate( JS_QUEUE_SIZE_ELEMENTS, sizeof(struct javascope_data_t) );
	if (js_queue == NULL){
		uz_printf("APU: Error: Queue creation failed\r\n");
		return XST_FAILURE;
	}

	// Initialize interrupt controller for the IPI -> Initialize RPU IPI
	Status = Apu_IpiInit(&INTCInst_IPI, INTERRUPT_ID_IPI);
	if(Status != XST_SUCCESS) {
		uz_printf("APU: Error: IPI initialization failed\r\n");
		return XST_FAILURE;
	}


	return Status;
}

//==============================================================================================================================================================
/**
 * Apu_GicInit() - This function initializes APU GIC and connects
 * 					interrupts with the associated handlers
 * @IntcInstPtr		Pointer to the GIC instance
 * @IntId			Interrupt ID to be connected and enabled
 * @Handler			Associated handler for the Interrupt ID
 * @PeriphInstPtr	Connected interrupt's Peripheral instance pointer
 */
u32 Apu_GicInit(XScuGic *IntcInstPtr, u32 IntId, Xil_ExceptionHandler Handler, void *PeriphInstPtr)
{
	u32 Status = XST_SUCCESS;

	// Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,(Xil_ExceptionHandler)XScuGic_InterruptHandler,IntcInstPtr);
	Xil_ExceptionEnable();										//Enable interrupts in the ARM

	// Make the connection between the IntId of the interrupt source and the
	// associated handler that is to run when the interrupt is recognized.
	Status = XScuGic_Connect(IntcInstPtr, IntId, Handler, PeriphInstPtr);

	XScuGic_Enable(IntcInstPtr, IntId);

	//uz_printf("APU: Apu_GicInit: Done\r\n");
	return Status;
}


//==============================================================================================================================================================
/**
 * Apu_IpiInit() - This function initializes APU IPI and enables IPI interrupts
 *
 * @IpiInstPtr		Pointer to the IPI instance
 */
u32 Apu_IpiInit(XIpiPsu *IntcInst_IPI_Ptr,u16 DeviceId)
{
	XIpiPsu_Config *IntcConfig_IPI;
	int status;

	// Interrupt controller configuration
	IntcConfig_IPI = XIpiPsu_LookupConfig(DeviceId);
		if (IntcConfig_IPI == NULL) {
			uz_printf("APU: Error: Ipi Init failed\r\n");
			return XST_FAILURE;
		}

	// Interrupt controller initialization
	status = XIpiPsu_CfgInitialize(IntcInst_IPI_Ptr, IntcConfig_IPI, IntcConfig_IPI->BaseAddress);
		if (status != XST_SUCCESS) {
			uz_printf("APU: Error: IPI Config failed\r\n");
			return XST_FAILURE;
		}

	XIpiPsu_InterruptEnable(IntcInst_IPI_Ptr, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

	uz_printf("APU: APU_IpiInit: Done\r\n");
	return XST_SUCCESS;
}
