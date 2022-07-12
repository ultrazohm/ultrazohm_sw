#ifndef UZ_FCS_MPC_3PHASE_SPMSM_HW_H
#define UZ_FCS_MPC_3PHASE_SPMSM_HW_H

#include "stdint.h"

void uz_fcs_mpc_3phase_spmsm_hw_set_u_dc_link(uint32_t base_address, float u_dc_link);
void uz_fcs_mpc_3phase_spmsm_hw_set_SampleTime(uint32_t base_address, float SampleTime);
void uz_fcs_mpc_3phase_spmsm_hw_set_Rs(uint32_t base_address, float Rs);
void uz_fcs_mpc_3phase_spmsm_hw_set_reciprocal_Ls(uint32_t base_address, float Ld, float Lq);
void uz_fcs_mpc_3phase_spmsm_hw_set_psiPM(uint32_t base_address, float psiPM);
void uz_fcs_mpc_3phase_spmsm_hw_set_pole_pairs(uint32_t base_address, float pole_pairs);

#endif // UZ_FCS_MPC_3PHASE_SPMSM_HW_H
