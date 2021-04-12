#include "uz_AXI_testIP_hw.h"
#include "xparameters.h"
#include "stdio.h"
#include "xil_io.h"
#include <stdint.h>
#include <stddef.h>

void uz_testAxiHalFunctions(void);
inline static void uz_writeMultipleFloatToAxi(volatile const float *SourcePointer,volatile uint32_t writeToAXIAddr, size_t numberOfElements) __attribute__((always_inline));
void test(volatile float *source);
void *mymemcpy(void *dest, const void *src, size_t n);

float A[4]={1,1,1,1};
float B[4]={1,2,3,4};
float C[4]={456,15,418,987};

void uz_testAxiHalFunctions(){



	float x=2;
	float C_read=0;
	float C_readfxd=0;

	uz_AXI_testIP_hw_handle h=uz_AXI_testIP_hw_init(XPAR_AXI_TESTI_IP_0_BASEADDR);

	uz_AXI_testIP_hw_writeAfloat(h,A[0]);
	//uz_AXI_testIP_hw_writeBfloat(h,B[0]);
	//C_read=uz_AXI_testIP_hw_readCfloat(h);
	memcpy( (void *) (XPAR_AXI_TESTI_IP_0_BASEADDR+A_float_Data_AXI_testI_ip), A,4*sizeof(float) ); // without wrapper
	volatile uint32_t addr=(XPAR_AXI_TESTI_IP_0_BASEADDR+B_float_Data_AXI_testI_ip);
	//memcpy( (void *)(XPAR_AXI_TESTI_IP_0_BASEADDR+B_float_Data_AXI_testI_ip), B,4*sizeof(float) );
	//uz_writeMultipleFloatToAxi(B, addr, 4);
	test(&B[0]);

	uz_axi_write_bool(XPAR_AXI_TESTI_IP_0_BASEADDR+A_float_Strobe_AXI_testI_ip, true);
	uz_axi_write_bool(XPAR_AXI_TESTI_IP_0_BASEADDR+B_float_Strobe_AXI_testI_ip, true);
	uz_axi_write_bool(XPAR_AXI_TESTI_IP_0_BASEADDR+A_float_Strobe_AXI_testI_ip, false);
	uz_axi_write_bool(XPAR_AXI_TESTI_IP_0_BASEADDR+B_float_Strobe_AXI_testI_ip, false);

	uz_axi_write_bool(XPAR_AXI_TESTI_IP_0_BASEADDR+C_float_Strobe_AXI_testI_ip, false);
	uz_axi_write_bool(XPAR_AXI_TESTI_IP_0_BASEADDR+C_float_Strobe_AXI_testI_ip, true);
	uz_axi_write_bool(XPAR_AXI_TESTI_IP_0_BASEADDR+C_float_Strobe_AXI_testI_ip, false);
	memcpy( C,(void *) (XPAR_AXI_TESTI_IP_0_BASEADDR+C_float_Data_AXI_testI_ip),4*sizeof(float) ); // without wrapper

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
	uz_printf("%i", C[0]);
	uz_AXI_testIP_hw_writeAfixed(h,A[0]);
	uz_AXI_testIP_hw_writeBfixed(h,B[0]);
	C_readfxd=uz_AXI_testIP_hw_readCfixed(h);
}

inline static void uz_writeMultipleFloatToAxi(volatile const float *SourcePointer,volatile uint32_t writeToAXIAddr, size_t numberOfElements){
    uz_assert_not_NULL(writeToAXIAddr);
    uz_assert_not_NULL(SourcePointer);
    uz_assert(numberOfElements>=1);
    memcpy( (void *)(XPAR_AXI_TESTI_IP_0_BASEADDR+B_float_Data_AXI_testI_ip), B,4*sizeof(float) );
}

void test(volatile float *source){
	memcpy( (void *)(XPAR_AXI_TESTI_IP_0_BASEADDR+B_float_Data_AXI_testI_ip), B,4*sizeof(int) );

	//uz_writeFloatToAxi((void *)(XPAR_AXI_TESTI_IP_0_BASEADDR+B_float_Data_AXI_testI_ip),source[0]);
	//uz_writeFloatToAxi((void *)(XPAR_AXI_TESTI_IP_0_BASEADDR+B_float_Data_AXI_testI_ip+0x4),source[1]);
	//uz_writeFloatToAxi((void *)(XPAR_AXI_TESTI_IP_0_BASEADDR+B_float_Data_AXI_testI_ip+0x8),source[2]);
	//uz_writeFloatToAxi((void *)(XPAR_AXI_TESTI_IP_0_BASEADDR+B_float_Data_AXI_testI_ip+0xC),source[3]);
}


void *mymemcpy(void *dest, const void *src, size_t n)
{
    char *dp = dest;
    const char *sp = src;
    while (n--)
        *dp++ = *sp++;
    return dest;
}

