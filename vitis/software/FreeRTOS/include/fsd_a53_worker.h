#ifndef FSD_A53_WORKER_H
#define FSD_A53_WORKER_H

#include "APU_RPU_shared.h"

#if UZ_FSD_A53_BENCHMARK_ENABLE
void fsd_a53_worker_process(
    const volatile struct RPU_to_APU_user_data_t *request,
    volatile struct APU_to_RPU_user_data_t *response);
#endif

#endif
