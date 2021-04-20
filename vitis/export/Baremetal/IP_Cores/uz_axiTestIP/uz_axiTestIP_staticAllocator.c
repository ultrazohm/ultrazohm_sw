#define UZ_AXITESTIP_USE_TESTBENCH 0
#if UZ_AXITESTIP_USE_TESTBENCH

#include "uz_axiTestIP_staticAllocator.h"
#include "uz_axiTestIP_private.h"
#include "uz_axiTestIP_hwAddresses.h"
#include "xparameters.h"

static uz_axiTestIP axiTestIP_instance1 =
                	{
	                                .base_address = XPAR_UZ_AXI_TESTIP_0_BASEADDR,
	                };

uz_axiTestIP_handle uz_axiTestIP_staticAllocator(void) {
	return (uz_axiTestIP_init(&axiTestIP_instance1));
}

float Aff[4]={1,2,3,4};
float Cff[4]={100,100,100,100};

static void uz_readMultipleFloatFromAxi(float *PointerToDataOnPS, uintptr_t ReadFromAXIAddr, size_t numberOfElements);
static void uz_writeMultipleFloatToAxi(const float *SourcePointer, uintptr_t writeToAXIAddr, size_t numberOfElements);
void uz_axiTestIP_testbench() {
	int32_t A = 100;
	int32_t B = 150;
	int32_t C = A * B;
	uz_axiTestIP_handle hardware_multiplication = uz_axiTestIP_staticAllocator();
	uz_axiTestIP_set_A_int32(hardware_multiplication, A);
	uz_axiTestIP_set_B_int32(hardware_multiplication, B);
	int32_t C_readback = uz_axiTestIP_get_C_int32(hardware_multiplication);
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
	float Cf_readback = uz_axiTestIP_get_C_float(hardware_multiplication);
	if (Cf == Cf_readback) {
		uz_printf("Hardware and software multiplication are the same");
	} else {
		uz_printf("Hardware and Software multiplication is not equal");
	}
	uz_writeMultipleFloatToAxi(Aff,(void *)(XPAR_UZ_AXI_TESTIP_0_BASEADDR+A_float_Data_uz_axi_testIP),4);
	memcpy((void *)(XPAR_UZ_AXI_TESTIP_0_BASEADDR+B_float_Data_uz_axi_testIP),Aff,4*sizeof(float) );
	uz_axi_write_bool(XPAR_UZ_AXI_TESTIP_0_BASEADDR + A_float_Strobe_uz_axi_testIP, false);
	uz_axi_write_bool(XPAR_UZ_AXI_TESTIP_0_BASEADDR + A_float_Strobe_uz_axi_testIP, true);
	uz_axi_write_bool(XPAR_UZ_AXI_TESTIP_0_BASEADDR + A_float_Strobe_uz_axi_testIP, false);
	uz_axi_write_bool(XPAR_UZ_AXI_TESTIP_0_BASEADDR + B_float_Strobe_uz_axi_testIP, false);
	uz_axi_write_bool(XPAR_UZ_AXI_TESTIP_0_BASEADDR + B_float_Strobe_uz_axi_testIP, true);
	uz_axi_write_bool(XPAR_UZ_AXI_TESTIP_0_BASEADDR + B_float_Strobe_uz_axi_testIP, false);
	uz_axi_write_bool(XPAR_UZ_AXI_TESTIP_0_BASEADDR + C_float_Strobe_uz_axi_testIP, false);
	uz_axi_write_bool(XPAR_UZ_AXI_TESTIP_0_BASEADDR + C_float_Strobe_uz_axi_testIP, true);
	uz_axi_write_bool(XPAR_UZ_AXI_TESTIP_0_BASEADDR + C_float_Strobe_uz_axi_testIP, false);
	memcpy(Cff, (void *)(XPAR_UZ_AXI_TESTIP_0_BASEADDR+C_float_Data_uz_axi_testIP),4*sizeof(float) );

	while (1) {
		// infinite loop
	}
}

static void uz_readMultipleFloatFromAxi(float *PointerToDataOnPS, uintptr_t ReadFromAXIAddr, size_t numberOfElements){
    memcpy( PointerToDataOnPS, (void *)ReadFromAXIAddr,numberOfElements*sizeof(float) );
}

static void uz_writeMultipleFloatToAxi(const float *SourcePointer, uintptr_t writeToAXIAddr, size_t numberOfElements){
    memcpy( (void *)writeToAXIAddr, SourcePointer,numberOfElements*sizeof(float) );
}

#endif
