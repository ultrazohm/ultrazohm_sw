#ifndef UZ_PMSM_RFE_H
#define UZ_PMSM_RFE_H

typedef struct uz_pmsm_r_fe_t uz_pmsm_r_fe_t;

struct uz_pmsm_r_fe_input_t
{
    float U_d;             /* '<Root>/U_d' */
    float U_q;             /* '<Root>/U_q' */
    float omega_el;        /* '<Root>/omega_el' */
    bool reset_integrator; /* '<Root>/reset_integrator' */
};

/* External outputs (root outports fed by signals with default storage) */
struct uz_pmsm_r_fe_output_t
{
    float Mi_ist;  /* '<Root>/Mi_ist' */
    float Mi_soll; /* '<Root>/Mi_soll' */
    float I_d;     /* '<Root>/I_d' */
    float I_q;     /* '<Root>/I_q' */
};

uz_pmsm_r_fe_t *uz_pmsm_r_fe_init();

#endif // UZ_PMSM_RFE_H
