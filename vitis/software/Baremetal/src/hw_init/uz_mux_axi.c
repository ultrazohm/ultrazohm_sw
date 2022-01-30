#include "../include/uz_mux_axi.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

static struct uz_mux_axi_config_t uz_mux_axi_config = {
        .base_address= XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR,
        .ip_clk_frequency_Hz=100000000,
		.mux=Interrupt_ISR_source_user_choice,
        .n_th_interrupt=INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE
};

uz_mux_axi_t* initialize_uz_mux_axi(void){
	uz_mux_axi_hw_enable_IP_core(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR);
	uz_mux_axi_hw_set_mux(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR, 1);
	uz_mux_axi_hw_set_n_th_interrupt(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR, 1);
	return (uz_mux_axi_init(uz_mux_axi_config));
}
