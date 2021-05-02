#include "uz_myIP.h"
#include "uz_myIP_private.h"
#include "xparameters.h"

static uz_myIP uz_myIP_instance1={
    .base_address=XPAR_UZ_AXI_TESTIP_0_BASEADDR,
    .ip_clk_frequency_Hz=100000000U
};

uz_myIP* uz_myIP_allocate_instance_one(void){
    return (uz_myIP_init(&uz_myIP_instance1));
}