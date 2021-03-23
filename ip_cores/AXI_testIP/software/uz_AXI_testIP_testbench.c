#include "uz_AXI_testIP_hw.h"
#include "xparameters.h"
#include "stdio.h"
#include "xil_io.h"
#include <stdint.h>

void uz_testAxiHalFunctions();

void uz_testAxiHalFunctions(){

	float A[4]={1.1,2.2,3.3,4.4};
	float B[4]={1.1,2.2,3.3,4.4};
	float C[4]={456,15,418,987};

	float x=2;
	float C_read=0;
	float C_readfxd=0;

	uz_AXI_testIP_hw_handle h=uz_AXI_testIP_hw_init(XPAR_AXI_TESTI_IP_0_BASEADDR);

	uz_AXI_testIP_hw_writeAfloat(h,A[0]);
	uz_AXI_testIP_hw_writeBfloat(h,B[0]);
	C_read=uz_AXI_testIP_hw_readCfloat(h);

	int A2=2147483646/2;
	int B2=-2;
	uint32_t A3=4294967294/2;
	uint32_t B3=2;

	uz_AXI_testIP_hw_writeAint32(h, A2);
	uz_AXI_testIP_hw_writeBint32(h, B2);
	int res_int=uz_AXI_testIP_hw_readCint32(h);
	uz_AXI_testIP_hw_writeAuint32(h, A3);
	uz_AXI_testIP_hw_writeBuint32(h, B3);
	uint32_t res_uint=uz_AXI_testIP_hw_readCuint32(h);
	uz_printf("2147483646*0.5 times -2 should be -2147483646, is: %i \n", res_int);
	uz_printf("4294967294*0.5 times 2 should be 4294967294, is: %u \n", res_uint);

	uz_AXI_testIP_hw_writeAfixed(h,A[0]);
	uz_AXI_testIP_hw_writeBfixed(h,B[0]);
	C_readfxd=uz_AXI_testIP_hw_readCfixed(h);
}
