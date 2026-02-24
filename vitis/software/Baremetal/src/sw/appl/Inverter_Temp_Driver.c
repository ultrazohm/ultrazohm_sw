#include "Inverter_Temp_Driver.h"
#include "../../main.h"
#include "../../IP_Cores/uz_DutyCycleMeas/uz_DutyCycleMeas_hw.h"
#include "NTC_LookUp_Inverter.h"

Inv_SiC_Temp_t Inv_SiC_Temp;

void inverter_temp_update_values(void){
    
	uint8_t tmp_PWM_hightimeTicks[9] = {0};

	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *  INVERTER 1
	 */
	/* Phase 1 */
	tmp_PWM_hightimeTicks[0] = uz_DutyCycleMeas_hw_get_PWMhightimeTicks(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_INV_TEMP_UZ_DUTYCYCLEMEAS_IP_0_BASEADDR);
	if(tmp_PWM_hightimeTicks[0] <= 250)	// proof if Duty Cycle high-time ticks value is in range of NTC array (250 is array length)
		Inv_SiC_Temp.T_Sys1_Ph1 = (float) T_NTC_LookUp_Inverter[tmp_PWM_hightimeTicks[0]];
	else
		Inv_SiC_Temp.T_Sys1_Ph1 = (float) T_NTC_LookUp_Inverter[0];

	/* Phase 2 */
	tmp_PWM_hightimeTicks[1] = uz_DutyCycleMeas_hw_get_PWMhightimeTicks(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_INV_TEMP_UZ_DUTYCYCLEMEAS_IP_1_BASEADDR);
	if(tmp_PWM_hightimeTicks[1] <= 250)	// proof if Duty Cycle high-time ticks value is in range of NTC array (250 is array length)
		Inv_SiC_Temp.T_Sys1_Ph2 = (float) T_NTC_LookUp_Inverter[tmp_PWM_hightimeTicks[1]];
	else
		Inv_SiC_Temp.T_Sys1_Ph2 = (float) T_NTC_LookUp_Inverter[0];

	/* Phase 3 */
	tmp_PWM_hightimeTicks[2] = uz_DutyCycleMeas_hw_get_PWMhightimeTicks(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_INV_TEMP_UZ_DUTYCYCLEMEAS_IP_2_BASEADDR);
	if(tmp_PWM_hightimeTicks[2] <= 250)	// proof if Duty Cycle high-time ticks value is in range of NTC array (250 is array length)
		Inv_SiC_Temp.T_Sys1_Ph3 = (float) T_NTC_LookUp_Inverter[tmp_PWM_hightimeTicks[2]];
	else
		Inv_SiC_Temp.T_Sys1_Ph3 = (float) T_NTC_LookUp_Inverter[0];


	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *  INVERTER 2
	 */
	/* Phase 1 */
	tmp_PWM_hightimeTicks[3] = uz_DutyCycleMeas_hw_get_PWMhightimeTicks(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_INV_TEMP_UZ_DUTYCYCLEMEAS_IP_3_BASEADDR);
	if(tmp_PWM_hightimeTicks[0] <= 250)	// proof if Duty Cycle high-time ticks value is in range of NTC array (250 is array length)
		Inv_SiC_Temp.T_Sys2_Ph1 = (float) T_NTC_LookUp_Inverter[tmp_PWM_hightimeTicks[3]];
	else
		Inv_SiC_Temp.T_Sys2_Ph1 = (float) T_NTC_LookUp_Inverter[0];

	/* Phase 2 */
	tmp_PWM_hightimeTicks[4] = uz_DutyCycleMeas_hw_get_PWMhightimeTicks(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_INV_TEMP_UZ_DUTYCYCLEMEAS_IP_4_BASEADDR);
	if(tmp_PWM_hightimeTicks[1] <= 250)	// proof if Duty Cycle high-time ticks value is in range of NTC array (250 is array length)
		Inv_SiC_Temp.T_Sys2_Ph2 = (float) T_NTC_LookUp_Inverter[tmp_PWM_hightimeTicks[4]];
	else
		Inv_SiC_Temp.T_Sys2_Ph2 = (float) T_NTC_LookUp_Inverter[0];

	/* Phase 3 */
	tmp_PWM_hightimeTicks[5] = uz_DutyCycleMeas_hw_get_PWMhightimeTicks(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_INV_TEMP_UZ_DUTYCYCLEMEAS_IP_5_BASEADDR);
	if(tmp_PWM_hightimeTicks[2] <= 250)	// proof if Duty Cycle high-time ticks value is in range of NTC array (250 is array length)
		Inv_SiC_Temp.T_Sys2_Ph3 = (float) T_NTC_LookUp_Inverter[tmp_PWM_hightimeTicks[5]];
	else
		Inv_SiC_Temp.T_Sys2_Ph3 = (float) T_NTC_LookUp_Inverter[0];


	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *  INVERTER 3
	 */
	/* Phase 1 */
	tmp_PWM_hightimeTicks[6] = uz_DutyCycleMeas_hw_get_PWMhightimeTicks(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_INV_TEMP_UZ_DUTYCYCLEMEAS_IP_6_BASEADDR);
	if(tmp_PWM_hightimeTicks[0] <= 250)	// proof if Duty Cycle high-time ticks value is in range of NTC array (250 is array length)
		Inv_SiC_Temp.T_Sys3_Ph1 = (float) T_NTC_LookUp_Inverter[tmp_PWM_hightimeTicks[6]];
	else
		Inv_SiC_Temp.T_Sys3_Ph1 = (float) T_NTC_LookUp_Inverter[0];

	/* Phase 2 */
	tmp_PWM_hightimeTicks[7] = uz_DutyCycleMeas_hw_get_PWMhightimeTicks(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_INV_TEMP_UZ_DUTYCYCLEMEAS_IP_7_BASEADDR);
	if(tmp_PWM_hightimeTicks[1] <= 250)	// proof if Duty Cycle high-time ticks value is in range of NTC array (250 is array length)
		Inv_SiC_Temp.T_Sys3_Ph2 = (float) T_NTC_LookUp_Inverter[tmp_PWM_hightimeTicks[7]];
	else
		Inv_SiC_Temp.T_Sys3_Ph2 = (float) T_NTC_LookUp_Inverter[0];

	/* Phase 3 */
	tmp_PWM_hightimeTicks[8] = uz_DutyCycleMeas_hw_get_PWMhightimeTicks(XPAR_UZ_DIGITAL_ADAPTER_INVERTER_INTERFACE_INV_TEMP_UZ_DUTYCYCLEMEAS_IP_8_BASEADDR);
	if(tmp_PWM_hightimeTicks[2] <= 250)	// proof if Duty Cycle high-time ticks value is in range of NTC array (250 is array length)
		Inv_SiC_Temp.T_Sys3_Ph3 = (float) T_NTC_LookUp_Inverter[tmp_PWM_hightimeTicks[8]];
	else
		Inv_SiC_Temp.T_Sys3_Ph3 = (float) T_NTC_LookUp_Inverter[0];


}

