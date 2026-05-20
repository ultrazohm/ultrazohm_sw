
#ifndef UZ_JL_PMSMMODEL_HW_H
#define UZ_JL_PMSMMODEL_HW_H

#include <stdint.h>
#include <stdbool.h>
void uz_JL_pmsmModel_hw_write_R1(uint32_t base_address, float mot_R1);
void uz_JL_pmsmModel_hw_write_L_d(uint32_t base_address, float L_d);
void uz_JL_pmsmModel_hw_write_L_q(uint32_t base_address, float L_q);
void uz_JL_pmsmModel_hw_write_mot_p(uint32_t base_address, float mot_p);
void uz_JL_pmsmModel_hw_write_psi_pm(uint32_t base_address, float psi_pm);
void uz_JL_pmsmModel_hw_write_mot_J(uint32_t base_address, float mot_J);
// void uz_JL_pmsmModel_hw_write_n_N(uint32_t base_address, float n_n);
// void uz_JL_pmsmModel_hw_write_M_N(uint32_t base_address, float M_n);
// void uz_JL_pmsmModel_hw_write_I_max(uint32_t base_address, float I_max);
void uz_JL_pmsmModel_hw_write_reset(uint32_t base_address, bool reset);
void uz_JL_pmsmModel_hw_write_Reibungskoeffizient(uint32_t base_address, float Reibungskoeffizient);
void uz_JL_pmsmModel_hw_write_Coulomb_Reibung(uint32_t base_address, float Coulomb_Reibung);

void uz_JL_pmsmModel_hw_write_Last_J(uint32_t base_address, float Last_J);
void uz_JL_pmsmModel_hw_write_Last_M(uint32_t base_address, float Last_M);
void uz_JL_pmsmModel_hw_write_bremse(uint32_t base_address, bool bremse);
void uz_JL_pmsmModel_hw_write_Udq(uint32_t base_address, float Udq[2]);
void uz_JL_pmsmModel_hw_write_switchUabc_dq(uint32_t base_address, bool switchUabc_dq);

float uz_JL_pmsmModel_hw_read_omega_mech(uint32_t base_address);
float uz_JL_pmsmModel_hw_read_phi_mech(uint32_t base_address);
float uz_JL_pmsmModel_hw_read_torque(uint32_t base_address);
float uz_JL_pmsmModel_hw_read_I_a(uint32_t base_address);
float uz_JL_pmsmModel_hw_read_I_b(uint32_t base_address);
float uz_JL_pmsmModel_hw_read_I_c(uint32_t base_address);

void uz_JL_pmsmModel_hw_trigger_output_strobe(uint32_t base_address);
// void uz_JL_pmsmModel_hw_trigger_input_strobe(uint32_t base_address);

#endif // UZ_JL_PMSMMODEL_HW_H
