#include <stdint.h>
#include <stdlib.h>
#include "uz_AXI_testIP_hwAddr.h"
#include "../../uz/uz_HAL.h"

typedef struct uz_AXI_testIP_hw uz_AXI_testIP_hw;
typedef uz_AXI_testIP_hw* uz_AXI_testIP_hw_handle;

uz_AXI_testIP_hw_handle uz_AXI_testIP_hw_init(uint32_t baseAddr);

// Float matrix multiplication
float uz_AXI_testIP_hw_readCfloat(uz_AXI_testIP_hw_handle self);
void uz_AXI_testIP_hw_writeBfloat(uz_AXI_testIP_hw_handle self, float data);
void uz_AXI_testIP_hw_writeAfloat(uz_AXI_testIP_hw_handle self, float data);

// int32 multiplication
void uz_AXI_testIP_hw_writeAint32(uz_AXI_testIP_hw_handle self, int32_t data);
void uz_AXI_testIP_hw_writeBint32(uz_AXI_testIP_hw_handle self, int32_t data);
int32_t uz_AXI_testIP_hw_readCint32(uz_AXI_testIP_hw_handle self);

// uint32 multiplication
void uz_AXI_testIP_hw_writeAuint32(uz_AXI_testIP_hw_handle self, uint32_t data);
void uz_AXI_testIP_hw_writeBuint32(uz_AXI_testIP_hw_handle self, uint32_t data);
uint32_t uz_AXI_testIP_hw_readCuint32(uz_AXI_testIP_hw_handle self);

// fi(1,16,6) multiplication
void uz_AXI_testIP_hw_writeAfixed(uz_AXI_testIP_hw_handle self, float data);
void uz_AXI_testIP_hw_writeBfixed(uz_AXI_testIP_hw_handle self, float data);
float uz_AXI_testIP_hw_readCfixed(uz_AXI_testIP_hw_handle self);
