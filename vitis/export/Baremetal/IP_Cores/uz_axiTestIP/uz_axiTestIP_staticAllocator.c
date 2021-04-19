#define UZ_AXITESTIP_USE_TESTBENCH 1
#if UZ_AXITESTIP_USE_TESTBENCH

#include "uz_axiTestIP_staticAllocator.h"
#include "uz_axiTestIP_private.h"
#include "xparameters.h"

static uz_axiTestIP axiTestIP_instance1 =
                	{
	                                .base_address = XPAR_UZ_AXI_TESTIP_0_BASEADDR,
	                };

uz_axiTestIP_handle uz_axiTestIP_staticAllocator(void) {
	return (uz_axiTestIP_init(&axiTestIP_instance1));
}

void uz_axiTestIP_testbench() {
	int32_t A = 100;
	int32_t B = 150;
	int32_t C = A * B;
	uz_axiTestIP_handle hardware_multiplication = uz_axiTestIP_staticAllocator();
	uz_axiTestIP_set_A_int32(hardware_multiplication, A);
	uz_axiTestIP_set_B_int32(hardware_multiplication, B);
	int C_readback = uz_axiTestIP_get_C_int32(hardware_multiplication);
	if (C == C_readback) {
		uz_printf("%i times %i = %i\n", A, B, C_readback);
	} else {
		uz_printf("Hardware and Software multiplication is not equal\n Hardware: \n Software \n", C_readback, C);
	}

	float Af=10.5;
	float Bf=9.5;
	float Cf=Af*Bf;
	uz_axiTestIP_set_A_float(hardware_multiplication, Af);
	uz_axiTestIP_set_B_float(hardware_multiplication, Bf);
	int Cf_readback = uz_axiTestIP_get_C_float(hardware_multiplication);
	if (Cf == Cf_readback) {
		uz_printf("Hardware and software multiplication are the same");
	} else {
		uz_printf("Hardware and Software multiplication is not equal");
	}

	while (1) {
		// infinite loop
	}
}
#endif
