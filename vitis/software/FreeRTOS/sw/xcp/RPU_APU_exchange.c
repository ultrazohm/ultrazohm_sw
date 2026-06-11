/*
 * Compile stub: the RPU<->APU OCM exchange is a shared protocol between the
 * R5 (Baremetal) and the A53 (FreeRTOS). The single implementation lives in
 * vitis/software/shared/RPU_APU_exchange_impl.c (resolved via the shared/
 * include path, like APU_RPU_shared.h) and is compiled once per application
 * through this stub. Do NOT add code here -- edit the shared implementation.
 */
#include "RPU_APU_exchange_impl.c"
