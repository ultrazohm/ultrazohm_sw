#include "../include/testbench.h"
#include "../uz/uz_signals/uz_signals.h"
#include "../uz/uz_global_configuration.h"

void uz_duty_cycles_to_rasv(DS_Data* Data, struct uz_DutyCycle_3x3ph_t duty_cycle){
	Data->rasv.halfBridge1DutyCycle = duty_cycle.system1.DutyCycle_A;
	Data->rasv.halfBridge2DutyCycle = duty_cycle.system1.DutyCycle_B;
	Data->rasv.halfBridge3DutyCycle = duty_cycle.system1.DutyCycle_C;
	Data->rasv.halfBridge4DutyCycle = duty_cycle.system2.DutyCycle_A;
	Data->rasv.halfBridge5DutyCycle = duty_cycle.system2.DutyCycle_B;
	Data->rasv.halfBridge6DutyCycle = duty_cycle.system2.DutyCycle_C;
	Data->rasv.halfBridge7DutyCycle = duty_cycle.system3.DutyCycle_A;
	Data->rasv.halfBridge8DutyCycle = duty_cycle.system3.DutyCycle_B;
	Data->rasv.halfBridge9DutyCycle = duty_cycle.system3.DutyCycle_C;
}


void uz_transformations(uz_9ph_abc_t abc_in, uz_9ph_dq_t* full_dq, uz_3ph_dq_t* dq, uz_3ph_alphabeta_t* XY1, uz_3ph_alphabeta_t* XY2, uz_3ph_alphabeta_t* XY3, float theta){
	*full_dq = uz_transformation_9ph_abc_to_dq(abc_in, theta);
	dq->d = full_dq->d;
	dq->q = full_dq->q;
	XY1->alpha = full_dq->x1;
	XY1->beta = full_dq->y1;
	XY2->alpha = full_dq->x2;
	XY2->beta = full_dq->y2;
	XY3->alpha = full_dq->x3;
	XY3->beta = full_dq->y3;
}

void uz_ADC_currents(DS_Data* Data){
	// convert ADC readings to currents in Amps
	Data->av.currents_abc.a1 = (Data->aa.A1.me.ADC_A3 * 12.129f) + 0.10f;
	Data->av.currents_abc.b1 = (Data->aa.A1.me.ADC_A2 * 11.338f) + 0.12f;
	Data->av.currents_abc.c1 = (Data->aa.A1.me.ADC_A1 * 12.051f) - 0.07f;
	Data->av.i_ZK1 = Data->aa.A1.me.ADC_B5 * PHASE_CURRENT_CONV;
	Data->av.currents_abc.a2 = (Data->aa.A2.me.ADC_A3 * 12.038f) - 0.03f;
	Data->av.currents_abc.b2 = (Data->aa.A2.me.ADC_A2 * 12.115f) + 0.00f;
	Data->av.currents_abc.c2 = (Data->aa.A2.me.ADC_A1 * 12.038f) - 0.00f;
	Data->av.i_ZK2 = Data->aa.A2.me.ADC_B5 * PHASE_CURRENT_CONV;
	Data->av.currents_abc.a3 = (Data->aa.A3.me.ADC_A3 * 12.115f) + 0.02f;
	Data->av.currents_abc.b3 = (Data->aa.A3.me.ADC_A2 * 11.923f) - 0.02f;
	Data->av.currents_abc.c3 = (Data->aa.A3.me.ADC_A1 * 11.603f) + 0.12f;
	Data->av.i_ZK3 = Data->aa.A3.me.ADC_B5 * PHASE_CURRENT_CONV;
}

void uz_ADC_voltages(DS_Data* Data){
	// convert ADC readings to voltages
	Data->av.U_ZK1 = (Data->aa.A1.me.ADC_A4 * 100.302f) + 451.30f;
	Data->av.voltages_abc.a1 = (Data->aa.A1.me.ADC_B8 * 101.172f) + 471.60f;
	Data->av.voltages_abc.b1 = (Data->aa.A1.me.ADC_B7 * 102.587f) + 474.84f;
	Data->av.voltages_abc.c1 = (Data->aa.A1.me.ADC_B6 * 100.885f) + 468.39f;
	Data->av.U_ZK2 = (Data->aa.A2.me.ADC_A4 * 99.700f) + 450.30f;
	Data->av.voltages_abc.a2 = (Data->aa.A2.me.ADC_B8 * 100.444f) + 466.19f;
	Data->av.voltages_abc.b2 = (Data->aa.A2.me.ADC_B7 * 100.401f) + 467.20f;
	Data->av.voltages_abc.c2 = (Data->aa.A2.me.ADC_B6 * 100.444f) + 467.00f;
	Data->av.U_ZK3 = (Data->aa.A3.me.ADC_A4 * 99.600f) + 450.20f;
	Data->av.voltages_abc.a3 = (Data->aa.A3.me.ADC_B8 * 100.339f) + 468.32f;
	Data->av.voltages_abc.b3 = (Data->aa.A3.me.ADC_B7 * 100.885f) + 469.95f;
	Data->av.voltages_abc.c3 = (Data->aa.A3.me.ADC_B6 *  99.800f) + 463.05f;
	Data->av.U_ZK = (Data->av.U_ZK1+Data->av.U_ZK2+Data->av.U_ZK3)/3.0f;
}

void uz_PWM_duty_freq_detection(DS_Data* Data){
	struct uz_PWM_duty_freq_detection_outputs_t temp_output;
	// start PWM freq temp measurement
	temp_output = uz_PWM_duty_freq_detection_get_outputs(Data->objects.tempMeasurement1);
	Data->av.temperature_inv_1 = temp_output.TempDegreesCelsius;
	temp_output = uz_PWM_duty_freq_detection_get_outputs(Data->objects.tempMeasurement2);
	Data->av.temperature_inv_2 = temp_output.TempDegreesCelsius;
	temp_output = uz_PWM_duty_freq_detection_get_outputs(Data->objects.tempMeasurement3);
	Data->av.temperature_inv_3 = temp_output.TempDegreesCelsius;
	// end PWM freq temp measurement
}

void uz_TempCard_Measurement(DS_Data* Data){
	// start uz tempcard
	uz_TempCard_IF_MeasureTemps_cyclic(Data->objects.uz_Tempcard);
	uz_temperaturecard_OneGroup channel_A_data = uz_TempCard_IF_get_channel(Data->objects.uz_Tempcard, 'a');
	Data->av.winding_temperature.a1 = channel_A_data.temperature[3]*(channel_A_data.Channels_Valid[3]==1);
	Data->av.winding_temperature.b1 = channel_A_data.temperature[5]*(channel_A_data.Channels_Valid[5]==1);
	Data->av.winding_temperature.c1 = channel_A_data.temperature[7]*(channel_A_data.Channels_Valid[7]==1);
	Data->av.winding_temperature.a2 = channel_A_data.temperature[9]*(channel_A_data.Channels_Valid[9]==1);
	Data->av.winding_temperature.b2 = channel_A_data.temperature[11]*(channel_A_data.Channels_Valid[11]==1);
	Data->av.winding_temperature.c2 = channel_A_data.temperature[13]*(channel_A_data.Channels_Valid[13]==1);
	Data->av.winding_temperature.a3 = channel_A_data.temperature[15]*(channel_A_data.Channels_Valid[15]==1);
	Data->av.winding_temperature.b3 = channel_A_data.temperature[17]*(channel_A_data.Channels_Valid[17]==1);
	Data->av.winding_temperature.c3 = channel_A_data.temperature[19]*(channel_A_data.Channels_Valid[19]==1);
	Data->av.avg_winding_temperature =
			(Data->av.winding_temperature.a1 + Data->av.winding_temperature.b1 + Data->av.winding_temperature.c1 +
			Data->av.winding_temperature.a2 + Data->av.winding_temperature.b2 + Data->av.winding_temperature.c2 +
			Data->av.winding_temperature.a3 + Data->av.winding_temperature.b3 + Data->av.winding_temperature.c3)/
			((channel_A_data.Channels_Valid[3]==1) + (channel_A_data.Channels_Valid[5]==1) + (channel_A_data.Channels_Valid[7]==1) +
			(channel_A_data.Channels_Valid[9]==1) + (channel_A_data.Channels_Valid[11]==1) + (channel_A_data.Channels_Valid[13]==1) +
			(channel_A_data.Channels_Valid[15]==1) + (channel_A_data.Channels_Valid[17]==1) + (channel_A_data.Channels_Valid[19]==1));
	// end uz tempcard
}

void uz_set_DC_zero(DS_Data* Data){
	Data->rasv.halfBridge1DutyCycle = 0.0f;
	Data->rasv.halfBridge2DutyCycle = 0.0f;
	Data->rasv.halfBridge3DutyCycle = 0.0f;
	Data->rasv.halfBridge4DutyCycle = 0.0f;
	Data->rasv.halfBridge5DutyCycle = 0.0f;
	Data->rasv.halfBridge6DutyCycle = 0.0f;
	Data->rasv.halfBridge7DutyCycle = 0.0f;
	Data->rasv.halfBridge8DutyCycle = 0.0f;
	Data->rasv.halfBridge9DutyCycle = 0.0f;
	Data->rasv.halfBridge10DutyCycle = 0.0f;
	Data->rasv.halfBridge11DutyCycle = 0.0f;
	Data->rasv.halfBridge12DutyCycle = 0.0f;
}

void uz_calc_phase_voltage(DS_Data* Data, uint8_t neutral_config){
	// calculates phase (strang) voltages from the phase-Udc- voltages, depending on the neutral config
	float u_n1 = 0.0f;
	float u_n2 = 0.0f;
	float u_n3 = 0.0f;
	switch(neutral_config){
	case 1U:{
		u_n1 = (Data->av.voltages_abc.a1 + Data->av.voltages_abc.b1 + Data->av.voltages_abc.c1 +
				Data->av.voltages_abc.a2 + Data->av.voltages_abc.b2 + Data->av.voltages_abc.c2 +
				Data->av.voltages_abc.a3 + Data->av.voltages_abc.b3 + Data->av.voltages_abc.c3) / 9.0f;
		u_n2 = u_n1;
		u_n3 = u_n1;
		break;
	}
	case 3U:{
		u_n1 = (Data->av.voltages_abc.a1 + Data->av.voltages_abc.b1 + Data->av.voltages_abc.c1) / 3.0f;
		u_n2 = (Data->av.voltages_abc.a2 + Data->av.voltages_abc.b2 + Data->av.voltages_abc.c2) / 3.0f;
		u_n3 = (Data->av.voltages_abc.a3 + Data->av.voltages_abc.b3 + Data->av.voltages_abc.c3) / 3.0f;
		break;
	}
	default: break;
	}
	Data->av.voltages_abc.a1 -= u_n1;
	Data->av.voltages_abc.b1 -= u_n1;
	Data->av.voltages_abc.c1 -= u_n1;
	Data->av.voltages_abc.a2 -= u_n2;
	Data->av.voltages_abc.b2 -= u_n2;
	Data->av.voltages_abc.c2 -= u_n2;
	Data->av.voltages_abc.a3 -= u_n3;
	Data->av.voltages_abc.b3 -= u_n3;
	Data->av.voltages_abc.c3 -= u_n3;
}

void uz_limit_exceed(DS_Data* Data){
	ultrazohm_state_machine_set_enable_control(false);
	Data->rasv.halfBridge1DutyCycle = 0.5f;
	Data->rasv.halfBridge2DutyCycle = 0.5f;
	Data->rasv.halfBridge3DutyCycle = 0.5f;
	Data->rasv.halfBridge4DutyCycle = 0.5f;
	Data->rasv.halfBridge5DutyCycle = 0.5f;
	Data->rasv.halfBridge6DutyCycle = 0.5f;
	Data->rasv.halfBridge7DutyCycle = 0.5f;
	Data->rasv.halfBridge8DutyCycle = 0.5f;
	Data->rasv.halfBridge9DutyCycle = 0.5f;
	Data->rasv.halfBridge10DutyCycle = 0.5f;
	Data->rasv.halfBridge11DutyCycle = 0.5f;
	Data->rasv.halfBridge12DutyCycle = 0.5f;
}

void uz_resolver_read_and_adapt_direction(DS_Data* Data){
    Data->av.rotational_position = uz_resolver_pl_interface_get_outputs(Data->objects.resolver_pl_d2);
    Data->av.rotational_position.position_el_2pi = uz_signals_wrap(2.0f*UZ_PIf-Data->av.rotational_position.position_el_2pi - Data->av.theta_el_offset, 2.0f*UZ_PIf);
    Data->av.omega_el = -1.0f*Data->av.rotational_position.omega_mech_rad_s*UZ_D5_MOTOR_POLE_PAIR_NUMBER;
}
