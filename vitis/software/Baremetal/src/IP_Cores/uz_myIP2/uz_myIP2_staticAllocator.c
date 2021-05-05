#include "uz_myIP2.h"
#include "uz_myIP2_private.h"
#include "xparameters.h"

static uz_myIP2 uz_myIP2_instance1={
    .base_address=XPAR_UZ_AXI_TESTIP_0_BASEADDR,
    .ip_clk_frequency_Hz=100000000U
};

uz_myIP2* uz_myIP2_allocate_instance_one(void){
    return (uz_myIP2_init(&uz_myIP2_instance1));
}