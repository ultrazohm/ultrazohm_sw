#include "../include/uz_myIP_testbench.h"
#include "../uz/uz_HAL.h"
#include "../IP_Cores/uz_myIP/uz_myIP.h"
#include "xparameters.h"


void uz_myIP_testbench(void){
    struct uz_myIP_config_t config={
         .base_address= XPAR_UZ_USER_UZ_AXI_TESTIP_0_BASEADDR,
         .ip_clk_frequency_Hz=100000000U
    };
    uz_myIP_t *instance = uz_myIP_init(config);
    int32_t a = -10;
    int32_t b = 200;
    int32_t c = uz_myIP_multiply(instance, a, b);
    uz_printf("Hardware multiply: %i, Software multiply: %i\n", c, a*b);
    if (c==a*b){
      uz_printf("Success: hardware and software multiply are equal! \n");
    }else{
      uz_printf("Fail: hardware and software multiply are NOT equal! \n");
    }

    while(1){
      // do nothing and loop forever
    }
}


