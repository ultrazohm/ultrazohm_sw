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

#include "../include/uz_pl_device_memory.h"
#include "../uz/uz_HAL.h"

#if UZ_PL_DEVICE_MEMORY != 0U
#include "xil_mpu.h"
#include "xreg_cortexr5.h"
#include "xpseudo_asm.h"

#if UZ_PL_DEVICE_MEMORY != 1U
#error "UZ_PL_DEVICE_MEMORY must be 0 or 1"
#endif

#define UZ_PL_RANGE_BASE 0x80000000U

/* Shareable Device memory: TEX 000, C 0, B 1 in the MPU Region Access Control
 * Register (TRM Table 4-36). xreg_cortexr5.h defines DEVICE_SHARED twice; the
 * Cortex-R5 value is 0x01 (the 0x200 is the one for the Cortex-R52). Access
 * permissions as the BSP sets them for the PL range. */
_Static_assert(DEVICE_SHARED == 0x01U, "DEVICE_SHARED is not the Cortex-R5 encoding (TEX 000, C 0, B 1)");
#define UZ_PL_DEVICE_ATTRIBUTE (DEVICE_SHARED | PRIV_RW_USER_RW)
#define UZ_PL_STRONGLY_ORDERED_ATTRIBUTE (STRONG_ORDERD_SHARED | PRIV_RW_USER_RW)

/* Defined fields of the Region Access Control Register: XN, AP, TEX, S, C, B */
#define UZ_MPU_ACCESS_CONTROL_MASK 0x173FU

/* Selects MPU region `region` for the region registers below. */
static void uz_pl_device_memory_select_region(uint32_t region)
{
    mtcp(XREG_CP15_MPU_MEMORY_REG_NUMBER, region);
    isb();
}

/* Reads the MPU from the hardware: the access control of the region that
 * applies to addr, i.e. the highest-numbered enabled region containing it. */
static uint32_t uz_pl_device_memory_read_attribute(uint32_t addr, uint32_t *region_out)
{
    uint32_t attribute = UINT32_MAX;
    *region_out = MAX_POSSIBLE_MPU_REGS;
    for (uint32_t region = 0U; region < MAX_POSSIBLE_MPU_REGS; region++)
    {
        uz_pl_device_memory_select_region(region);
        const uint32_t size_enable = mfcp(XREG_CP15_MPU_REG_SIZE_EN);
        const uint32_t base = mfcp(XREG_CP15_MPU_REG_BASEADDR);
        const uint32_t access_control = mfcp(XREG_CP15_MPU_REG_ACCESS_CTRL);
        const uint32_t size_log2 = ((size_enable >> 1U) & 0x1FU) + 1U; // region size is 2^(N+1) bytes
        const uint32_t base_mask = (size_log2 >= 32U) ? 0U : ~((1UL << size_log2) - 1UL);
        if (((size_enable & REGION_EN) != 0U) && ((addr & base_mask) == (base & base_mask)))
        {
            attribute = access_control & UZ_MPU_ACCESS_CONTROL_MASK;
            *region_out = region;
        }
    }
    return attribute;
}

/* Changes the memory type of the BSP's MPU region over the PL range in place:
 * only its access control register is rewritten, base and size stay, so the
 * range stays mapped at every moment (the BSP does not enable the background
 * region, and Xil_SetMPURegionByRegNum() refuses an enabled region). No cache
 * maintenance: the range is uncacheable before and after. */
void uz_pl_device_memory_init(void)
{
    // nothing may use the MPU region registers in between
    const uint32_t cpsr = mfcpsr();
    mtcpsr(cpsr | XREG_CPSR_IRQ_ENABLE | XREG_CPSR_FIQ_ENABLE);
    uint32_t region = 0U;
    const uint32_t attribute = uz_pl_device_memory_read_attribute(UZ_PL_RANGE_BASE, &region);
    uz_assert(region < MAX_POSSIBLE_MPU_REGS);
    uz_assert(attribute == UZ_PL_STRONGLY_ORDERED_ATTRIBUTE);
    uz_pl_device_memory_select_region(region);
    const uint32_t size_enable = mfcp(XREG_CP15_MPU_REG_SIZE_EN);
    const uint32_t base = mfcp(XREG_CP15_MPU_REG_BASEADDR);
    uz_assert(base == UZ_PL_RANGE_BASE);
    uz_assert(((size_enable >> 1U) & 0x1FU) == REGION_1G); // 0x80000000-0xBFFFFFFF as set by Init_MPU
    dsb();                                                  // every access before this one under the old attribute
    mtcp(XREG_CP15_MPU_REG_ACCESS_CTRL, UZ_PL_DEVICE_ATTRIBUTE);
    dsb();
    isb(); // the following instructions use the new attribute
    // keep the BSP's copy of the MPU configuration (Xil_GetMPUConfig) in step
    (void)Xil_UpdateMPUConfig(region, (INTPTR)base, size_enable, UZ_PL_DEVICE_ATTRIBUTE);
    mtcpsr(cpsr);

    // read back from the hardware
    const uint32_t now = uz_pl_device_memory_read_attribute(UZ_PL_RANGE_BASE, &region);
    uz_printf("RPU: MPU region %u (PL 0x80000000-0xBFFFFFFF): access control 0x%04x (%s)\r\n", region, now,
              (now == UZ_PL_DEVICE_ATTRIBUTE) ? "Device" : "not Device");
    uz_assert(now == UZ_PL_DEVICE_ATTRIBUTE);
}

#else

void uz_pl_device_memory_init(void)
{
}

#endif
