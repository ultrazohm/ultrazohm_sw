#include "../include/testbench.h"

extern float offset_temp;
extern float factor_temp;

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
	Data->av.currents_abc.a1 = (Data->aa.A1.me.ADC_A3 - offset_temp) * factor_temp;
	Data->av.currents_abc.b1 = (Data->aa.A1.me.ADC_A2 - offset_temp) * factor_temp;
	Data->av.currents_abc.c1 = (Data->aa.A1.me.ADC_A1 - offset_temp) * factor_temp;
	Data->av.i_ZK1 = Data->aa.A1.me.ADC_B5 * PHASE_CURRENT_CONV;
	Data->av.currents_abc.a2 = (Data->aa.A2.me.ADC_A3 - offset_temp) * factor_temp;
	Data->av.currents_abc.b2 = (Data->aa.A2.me.ADC_A2 - offset_temp) * factor_temp;
	Data->av.currents_abc.c2 = (Data->aa.A2.me.ADC_A1 - offset_temp) * factor_temp;
	Data->av.i_ZK2 = Data->aa.A2.me.ADC_B5 * PHASE_CURRENT_CONV;
	Data->av.currents_abc.a3 = (Data->aa.A3.me.ADC_A3 - offset_temp) * factor_temp;
	Data->av.currents_abc.b3 = (Data->aa.A3.me.ADC_A2 - offset_temp) * factor_temp;
	Data->av.currents_abc.c3 = (Data->aa.A3.me.ADC_A1 - offset_temp) * factor_temp;
	Data->av.i_ZK3 = Data->aa.A3.me.ADC_B5 * PHASE_CURRENT_CONV;
}

void uz_ADC_voltages(DS_Data* Data){
	// convert ADC readings to voltages
	Data->av.U_ZK1 = Data->aa.A1.me.ADC_A4 * DC_VOLT_CONV + 591.3f;
	Data->av.voltages_abc.a1 = Data->aa.A1.me.ADC_B8 * DC_VOLT_CONV + 616.0f;
	Data->av.voltages_abc.b1 = Data->aa.A1.me.ADC_B7 * DC_VOLT_CONV + 614.8f;
	Data->av.voltages_abc.c1 = Data->aa.A1.me.ADC_B6 * DC_VOLT_CONV + 611.5f;
	Data->av.U_ZK2 = Data->aa.A2.me.ADC_A4 * DC_VOLT_CONV;
	Data->av.voltages_abc.a2 = Data->aa.A2.me.ADC_B8 * DC_VOLT_CONV;
	Data->av.voltages_abc.b2 = Data->aa.A2.me.ADC_B7 * DC_VOLT_CONV;
	Data->av.voltages_abc.c2 = Data->aa.A2.me.ADC_B6 * DC_VOLT_CONV;
	Data->av.U_ZK3 = Data->aa.A3.me.ADC_A4 * DC_VOLT_CONV;
	Data->av.voltages_abc.a3 = Data->aa.A3.me.ADC_B8 * DC_VOLT_CONV;
	Data->av.voltages_abc.b3 = Data->aa.A3.me.ADC_B7 * DC_VOLT_CONV;
	Data->av.voltages_abc.c3 = Data->aa.A3.me.ADC_B6 * DC_VOLT_CONV;
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
