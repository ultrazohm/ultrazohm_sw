#include "uz_PWM_3L_hw.h"
#include "uz_PWM_3L_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

#include <math.h>
#include "../../uz/uz_math_constants.h"
#include "../../uz/uz_SystemTime/uz_SystemTime.h"

uint32_t carrier_freq_hz = 0;
uint32_t sine_wave_freq_hz = 0;

void uz_PWM_3L_hw_set_carrier_f(uint32_t base_address, uint32_t f_carrier_hz)
{
    uz_assert_not_zero_uint32(base_address);
    if(f_carrier_hz > 100000){
    	f_carrier_hz = 100000;
    }
    if(f_carrier_hz < 100){
    	f_carrier_hz = 100;
    }
    carrier_freq_hz = f_carrier_hz;
    //amount of IPcore clock cycles per carrier cycle
    uint32_t scal_t_carrier = (uint32_t)50000000*(1.0/f_carrier_hz);
    uz_axi_write_uint32(base_address + Scal_T_carrier_AXI_Data_PWM_3Level_control, scal_t_carrier);
}

void uz_PWM_3L_hw_enable_IP_core(uint32_t base_address, bool enable)
{
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_uint32(base_address + PWM_en_AXI_Data_PWM_3Level_control, enable);
}

void uz_PWM_3L_hw_set_u1(uint32_t base_address, float u1){
	uz_assert_not_zero_uint32(base_address);
	bool negative = false;
	if (u1 < -1){
		u1 = -1;
	}
	if (u1 > 1){
		u1 = 1;
	}
	if (u1 < 0){
		negative = true;
	}
	u1 = u1*pow(2,12) + (negative << 14);
	uint32_t u1_cast = (uint32_t)u1;
	uz_axi_write_uint32(base_address + m_u1_norm_AXI_Data_PWM_3Level_control, u1_cast);
}

void uz_PWM_3L_hw_set_u2(uint32_t base_address, float u2){
	uz_assert_not_zero_uint32(base_address);
	bool negative = false;
	if (u2 < -1){
		u2 = -1;
	}
	if (u2 > 1){
		u2 = 1;
	}
	if (u2 < 0){
		negative = true;
	}
	u2 = u2*pow(2,12) + (negative << 14);
	uint32_t u2_cast = (uint32_t)u2;
	uz_axi_write_uint32(base_address + m_u2_norm_AXI_Data_PWM_3Level_control, u2_cast);
}

void uz_PWM_3L_hw_set_u3(uint32_t base_address, float u3){
	uz_assert_not_zero_uint32(base_address);
	bool negative = false;
	if (u3 < -1){
		u3 = -1;
	}
	if (u3 > 1){
		u3 = 1;
	}
	if (u3 < 0){
		negative = true;
	}
	u3 = u3*pow(2,12) + (negative << 14);
	uint32_t u3_cast = (uint32_t)u3;
	uz_axi_write_uint32(base_address + m_u3_norm_AXI_Data_PWM_3Level_control, u3_cast);
}

void uz_PWM_3L_hw_set_mode(uint32_t base_address, uint8_t mode){
	uz_assert_not_zero_uint32(base_address);
	if ((mode < 1) || (mode > 2)){
		mode = 2;
	}
	uz_axi_write_uint32(base_address + Mode_AXI_Data_PWM_3Level_control, mode);
}

void uz_PWM_3L_hw_set_sampligPoint(uint32_t base_address, uint8_t samplingMode){
	uz_assert_not_zero_uint32(base_address);
	if ((samplingMode < 1) || (samplingMode > 4)){
		samplingMode = 4;
	}
	uz_axi_write_uint32(base_address + Sampling_AXI_Data_PWM_3Level_control, samplingMode);
}

void uz_PWM_3L_hw_set_min_PW(uint32_t base_address, uint32_t min_pw_ns){
	uz_assert_not_zero_uint32(base_address);
	// minimum pulse width cant't be greater than width of half a carrier
	if (min_pw_ns > 1e9/(carrier_freq_hz*2)){
		min_pw_ns = 1e9/(carrier_freq_hz*2);
	}
	// to calculate normalised value (between 0-1, representing the min allowed dutycycle)
	// one needs to take the ratio MinPulseWidth (s) / HalfMolationPeriod (s)
	float min_pw_norm;
	min_pw_norm = (float)min_pw_ns*(1e-9)*(float)carrier_freq_hz/2;
	min_pw_norm = min_pw_norm*pow(2,12);
	uint32_t min_pw_norm_cast = (uint32_t)min_pw_norm;
	uz_axi_write_uint32(base_address + min_pwm_norm_Data_PWM_3Level_control, min_pw_norm_cast);
}

void uz_PWM_3L_get_switch_states(uint32_t base_address, uint8_t states[][4]){
	uz_assert_not_zero_uint32(base_address);
	states[0][0] = uz_axi_read_uint32(base_address + AXI_U1_SS0_OUT_Data_PWM_3Level_control);
	states[0][1] = uz_axi_read_uint32(base_address + AXI_U1_SS1_OUT_Data_PWM_3Level_control);
	states[0][2] = uz_axi_read_uint32(base_address + AXI_U1_SS2_OUT_Data_PWM_3Level_control);
	states[0][3] = uz_axi_read_uint32(base_address + AXI_U1_SS3_OUT_Data_PWM_3Level_control);

	states[1][0] = uz_axi_read_uint32(base_address + AXI_U2_SS0_OUT_Data_PWM_3Level_control);
	states[1][1] = uz_axi_read_uint32(base_address + AXI_U2_SS1_OUT_Data_PWM_3Level_control);
	states[1][2] = uz_axi_read_uint32(base_address + AXI_U2_SS2_OUT_Data_PWM_3Level_control);
	states[1][3] = uz_axi_read_uint32(base_address + AXI_U2_SS3_OUT_Data_PWM_3Level_control);

	states[2][0] = uz_axi_read_uint32(base_address + AXI_U3_SS0_OUT_Data_PWM_3Level_control);
	states[2][1] = uz_axi_read_uint32(base_address + AXI_U3_SS1_OUT_Data_PWM_3Level_control);
	states[2][2] = uz_axi_read_uint32(base_address + AXI_U3_SS2_OUT_Data_PWM_3Level_control);
	states[2][3] = uz_axi_read_uint32(base_address + AXI_U3_SS3_OUT_Data_PWM_3Level_control);
}

void uz_PWM_3L_hw_set_test_sin_freq(uint32_t base_address, uint32_t freq_hz, float sin_waves[]){
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_zero_uint32(sin_waves);
	if (freq_hz * 15 > carrier_freq_hz){		// 15 was chosen a bit arbitrarily, just wanted to set some upper limit for the sin wave freq
		freq_hz = carrier_freq_hz/15;
	}
	double time_s = uz_SystemTime_GetInterruptCounter()/(double)carrier_freq_hz; // interrupt_count * interrupt_period
	sin_waves[0] = (float)sin(freq_hz*2*UZ_PId*time_s);
	sin_waves[1] = (float)sin(freq_hz*2*UZ_PId*(time_s+(1.0/3)*(1.0/(float)freq_hz)));
	sin_waves[2] = (float)sin(freq_hz*2*UZ_PId*(time_s+(2.0/3)*(1.0/(float)freq_hz)));
	uz_PWM_3L_hw_set_u1(base_address, sin_waves[0]);
	uz_PWM_3L_hw_set_u2(base_address, sin_waves[1]);
	uz_PWM_3L_hw_set_u3(base_address, sin_waves[2]);
}

uint32_t uz_PWM_3L_hw_enable_IP_core_readback(uint32_t base_address){
	uz_assert_not_zero_uint32(base_address);
	return uz_axi_read_uint32(base_address + PWM_en_AXI_readback_Data_PWM_3Level_control);
}

uint32_t uz_PWM_3L_hw_u1_readback(uint32_t base_address){
	uz_assert_not_zero_uint32(base_address);
	return uz_axi_read_uint32(base_address + m_u1_norm_readback_Data_PWM_3Level_control);
}

uint32_t uz_PWM_3L_hw_get_carrier(uint32_t base_address){
	uz_assert_not_zero_uint32(base_address);
	return uz_axi_read_uint32(base_address + AXI_Carrier_OUT_Data_PWM_3Level_control);
}

uint32_t uz_PWM_3L_hw_carrier_f_readback(uint32_t base_address){
	uz_assert_not_zero_uint32(base_address);
	return uz_axi_read_uint32(base_address + Scal_T_carrier_AXI_readback_Data_PWM_3Level_control);
}
