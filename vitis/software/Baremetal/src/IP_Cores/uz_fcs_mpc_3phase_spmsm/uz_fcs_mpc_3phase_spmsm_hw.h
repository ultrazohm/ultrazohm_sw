#ifndef UZ_FCS_MPC_3PHASE_SPMSM_HW_H
#define UZ_FCS_MPC_3PHASE_SPMSM_HW_H

#include "stdint.h"

void uz_fcs_mpc_3phase_spmsm_hw_set_u_dc_link(uint32_t base_address, float u_dc_link);
void uz_fcs_mpc_3phase_spmsm_hw_set_SampleTime(uint32_t base_address, float SampleTime);
void uz_fcs_mpc_3phase_spmsm_hw_set_Rs(uint32_t base_address, float Rs);
void uz_fcs_mpc_3phase_spmsm_hw_set_Ld(uint32_t base_address, float Ld);
void uz_fcs_mpc_3phase_spmsm_hw_set_Lq(uint32_t base_address, float Lq);
void uz_fcs_mpc_3phase_spmsm_hw_set_psiPM(uint32_t base_address, float psiPM);

#endif // UZ_FCS_MPC_3PHASE_SPMSM_HW_H