#pragma once

/* One native float32 FSD-MPC instance for the optional A53 timing benchmark. */
#ifdef TEST
#define UZ_FSD_MPC_MAX_INSTANCES 12U
#else
#define UZ_FSD_MPC_MAX_INSTANCES 1U
#endif
