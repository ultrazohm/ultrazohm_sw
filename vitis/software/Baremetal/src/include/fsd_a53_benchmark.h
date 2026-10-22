#ifndef FSD_A53_BENCHMARK_H
#define FSD_A53_BENCHMARK_H

#include "APU_RPU_shared.h"
#include <stdbool.h>

#if UZ_FSD_A53_BENCHMARK_ENABLE
bool fsd_a53_benchmark_prepare(volatile struct RPU_to_APU_user_data_t *request);
void fsd_a53_benchmark_complete(
    const volatile struct APU_to_RPU_user_data_t *response,
    int acknowledgment_status);
void fsd_a53_benchmark_report_once(void);
#endif

#endif
