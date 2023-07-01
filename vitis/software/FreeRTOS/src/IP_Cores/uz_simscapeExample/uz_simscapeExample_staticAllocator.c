#define UZ_SIMSCAPEEXAMPLE_USE_IP 0
#if UZ_SIMSCAPEEXAMPLE_USE_IP

#include "uz_simscapeExample_staticAllocator.h"
#include "uz_simscapeExample.h"
#include "uz_simscapeExample_private.h"
#include "xparameters.h"

static uz_simscapeExample simscapeModel_instance1 = { .base_address = XPAR_UZ_SIMSCAPEEXAMPLE_0_BASEADDR, .amp = 10.0f, .freq_Hz = 1.0f };

uz_simscapeExample_handle uz_simscapeExample_staticAllocator(void) {
	return (uz_simscapeExample_init(&simscapeModel_instance1));
}

#endif
