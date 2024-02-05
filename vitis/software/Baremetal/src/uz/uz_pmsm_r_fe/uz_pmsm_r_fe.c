#include "uz_pmsm_r_fe.h"

#include "../uz_global_configuration.h"
#if UZ_PMSM_RFE_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../uz_HAL.h"
#include "uz_pmsm_r_fe.h"
#include "uz_pmsm_rfe_ert_rtw/uz_pmsm_rfe.h"

struct uz_pmsm_r_fe_t
{
    bool is_ready;
    ExtY output;
    ExtU input;
    DW rtDW; /* Observable states */
    RT_MODEL modelData;
    RT_MODEL *PtrToModelData;
};

static uint32_t instance_counter = 0U;
static uz_pmsm_r_fe_t instances[UZ_PMSM_RFE_MAX_INSTANCES] = {0};

static uz_pmsm_r_fe_t* uz_pmsm_r_fe_allocation(void);

static uz_pmsm_r_fe_t* uz_pmsm_r_fe_allocation(void){
    uz_assert(instance_counter < UZ_PMSM_RFE_MAX_INSTANCES);
    uz_pmsm_r_fe_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}


    uz_pmsm_r_fe_t *
    uz_pmsm_r_fe_init()
{
    uz_pmsm_r_fe_t* self = uz_pmsm_r_fe_allocation();
    self->PtrToModelData = &self->modelData;
    self->PtrToModelData->dwork = &self->rtDW;
    self->PtrToModelData->inputs = &self->input;
    self->PtrToModelData->outputs = &self->output;
    uz_pmsm_rfe_initialize(self->PtrToModelData);
    return (self);
}
void uz_pmsm_r_fe_step(uz_pmsm_r_fe_t* self){
    uz_pmsm_rfe_step(self->PtrToModelData);
    self->output.I_d
}



#endif