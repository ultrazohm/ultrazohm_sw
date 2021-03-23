#include <stdint.h>
#include <stdlib.h>
#include "../uz_HAL.h"
#include "uz_simEx_addr.h"

typedef struct uz_simEx_hw uz_simEx_hw;
typedef uz_simEx_hw* uz_simEx_hw_handle;

uz_simEx_hw_handle uz_simEx_hw_init(uint32_t baseAddr);
void uz_simEx_hw_writeVin(uz_simEx_hw_handle self, float Vin);
float uz_simEx_hw_readIR(uz_simEx_hw_handle self);
float uz_simEx_hw_readIout(uz_simEx_hw_handle self);
float uz_simEx_hw_readVdiode(uz_simEx_hw_handle self);
