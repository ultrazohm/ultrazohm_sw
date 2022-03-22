#ifndef UZ_RESOLVERIP_HW_H
#define UZ_RESOLVERIP_HW_H

#include <stdint.h>

// Bit Shifts in RESCON Register
#define  RESCON_Data_uz_axi_EN_bit        (1 << 0)
#define  RESCON_Data_uz_axi_GO_bit        (1 << 1)
#define  RESCON_Data_uz_axi_BUSY_bit      (1 << 2)
#define  RESCON_Data_uz_axi_ERROR_bit     (1 << 3)
#define  RESCON_Data_uz_axi_VMODE_bit     (1 << 4)
#define  RESCON_Data_uz_axi_PMODE_bit     (1 << 5)
#define  RESCON_Data_uz_axi_RW_bit        (1 << 6)
#define  RESCON_Data_uz_axi_nRESET_bit    (1 << 7)
#define  RESCON_Data_uz_axi_VALID_bit     (1 << 8)

// AD2S1210 Register Addresses (see datasheet)
#define POS_REG_1_ADR           		0x80U
#define POS_REG_2_ADR           		0x81U
#define VEL_REG_1_ADR           		0x82U
#define VEL_REG_2_ADR           		0x83U
#define LOS_THRESHOLD_REG_ADR           0x88U
#define DOS_OVERRANGE_REG_ADR           0x89U
#define DOS_MISMATCH_REG_ADR            0x8AU
#define DOS_RESET_MIN_REG_ADR           0x8BU
#define DOS_RESET_MAX_REG_ADR           0x8CU
#define LOT_HIGH_THRESH_REG_ADR         0x8DU
#define LOT_LOW_THRESH_REG_ADR          0x8EU
#define EXIT_FREQ_REG_ADR               0x91U
#define CONTROL_REG_ADR                 0x92U
#define SOFTWARE_RST_REG_ADR            0xF0U
#define FAULT_REG_ADR                   0xFFU

void uz_resolverIP_hw_write_RESCON(uint32_t base_address, int32_t val);
void uz_resolverIP_hw_write_RESDAT(uint32_t base_address, int32_t val);
void uz_resolverIP_hw_write_RESADR(uint32_t base_address, int32_t val);

int32_t uz_resolverIP_hw_read_RESCON(uint32_t base_address);
int32_t uz_resolverIP_hw_read_RESDAT(uint32_t base_address);
int32_t uz_resolverIP_hw_read_RESADR(uint32_t base_address);
int32_t uz_resolverIP_hw_read_RESRDA(uint32_t base_address);
int32_t uz_resolverIP_hw_read_RESPOS(uint32_t base_address);
#endif // UZ_RESOLVERIP_HW_H
