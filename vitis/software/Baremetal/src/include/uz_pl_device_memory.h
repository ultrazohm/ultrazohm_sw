/******************************************************************************
 * Copyright Contributors to the UltraZohm project.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 ******************************************************************************/

/* uz_pl_device_memory.h - memory type of the PL address range on the R5.
 *
 * The R5 BSP (mpu.c, Init_MPU) maps 0x80000000-0xBFFFFFFF, the AXI registers
 * of all IP cores in the PL, as strongly ordered memory. The R5 completes
 * every strongly ordered access, and all accesses before it, before it goes
 * on: each AXI register write costs the full round trip to the PL and back
 * (about 650 ns).
 *
 * As Device memory a write is posted: the R5 continues while the write
 * travels to the PL. What stays the same (Cortex-R5 TRM, DDI 0460D, D.1):
 * accesses to the PL keep their program order, and a read from the PL waits
 * until every earlier write to the PL is complete - so writing the inputs of
 * an IP core and then reading its output works as before. What changes:
 *  - a write is no longer complete when the next instruction runs; code that
 *    must know a write has arrived (e.g. before it stops or spins) calls
 *    uz_pl_device_memory_complete_writes() (DSB),
 *  - PL writes are not ordered against accesses to Normal memory (TCM, OCM,
 *    DDR) without a barrier,
 *  - an AXI error on a PL write raises an asynchronous (imprecise) abort
 *    instead of a synchronous one (TRM 8.3).
 *
 * Bench 2026-11-24 (HW v3, 40 kHz, CANape-like XCP load, 14.4 M cycles each):
 * ISR_Control p50/p99/max 16.84/18.92/21.80 us -> 9.34/11.56/15.14 us; the
 * duty-cycle writes 9.8 -> 1.8 us. AXI-Lite self-test (uz_axi_testIP,
 * encoder, PWM read-back ports; 10^6 write/read sequences per run): no error.
 */
#ifndef UZ_PL_DEVICE_MEMORY_H
#define UZ_PL_DEVICE_MEMORY_H

/* 0: strongly ordered, as set up by the BSP (default).
 * 1: the PL range 0x80000000-0xBFFFFFFF as shareable Device memory. */
#ifndef UZ_PL_DEVICE_MEMORY
#define UZ_PL_DEVICE_MEMORY 0U
#endif

/* Sets the memory type selected by UZ_PL_DEVICE_MEMORY. Call once at start-up,
 * before the first PL access and with interrupts disabled. Does nothing with
 * UZ_PL_DEVICE_MEMORY 0. */
void uz_pl_device_memory_init(void);

/* Waits until every earlier memory access, PL register writes included, is
 * complete (DSB). */
static inline void uz_pl_device_memory_complete_writes(void)
{
    __asm volatile("dsb" ::: "memory");
}

#endif /* UZ_PL_DEVICE_MEMORY_H */
