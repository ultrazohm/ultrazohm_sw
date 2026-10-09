#ifndef FSD_MPC_BENCHMARK_H
#define FSD_MPC_BENCHMARK_H

#include "../uz/uz_fsd_mpc/uz_fsd_mpc.h"
#include "fsd_mpc_benchmark_stats.h"

/* Application-only, default-disabled R5 benchmark. No PWM connection. */
uz_fsd_mpc_t *fsd_mpc_benchmark_init(void);
void fsd_mpc_benchmark_step(uz_fsd_mpc_t *controller);
const struct fsd_mpc_benchmark_stats *fsd_mpc_benchmark_get_stats(void);
void fsd_mpc_benchmark_report_once(void);

#endif
