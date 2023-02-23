#include "../uz_global_configuration.h"
#if UZ_PARAMETERID_6PH_MAX_INSTANCES > 0U

#include <stdbool.h>
#include "../../uz_HAL.h"
#include "uz_ParaID_FluxMapID_6ph.h"
#include "FluxMapID_6ph_codegen.h"

struct uz_ParaID_FluxMapID_6ph_t {
    bool is_ready;
    ExtY_FluxMapID_6ph_codegen_t output;
    ExtU_FluxMapID_6ph_codegen_t input;
    DW_FluxMapID_6ph_codegen_t rtDW;
    RT_MODEL_FluxMapID_6ph_codege_t modelData;
    RT_MODEL_FluxMapID_6ph_codege_t *PtrToModelData;
};

static uint32_t instance_counter = 0U;
static uz_ParaID_FluxMapID_6ph_t instances[UZ_PARAMETERID_6PH_MAX_INSTANCES] = { 0 };

static uz_ParaID_FluxMapID_6ph_t* uz_FluxMapID_6ph_allocation(void);

static uz_ParaID_FluxMapID_6ph_t* uz_FluxMapID_6ph_allocation(void){
    uz_assert(instance_counter < UZ_PARAMETERID_6PH_MAX_INSTANCES);
    uz_ParaID_FluxMapID_6ph_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_ParaID_FluxMapID_6ph_t* uz_FluxMapID_6ph_init(void) {
    uz_ParaID_FluxMapID_6ph_t* self = uz_FluxMapID_6ph_allocation();
    self->PtrToModelData=&self->modelData;
    self->PtrToModelData->dwork=&self->rtDW;
    self->PtrToModelData->inputs=&self->input;
    self->PtrToModelData->outputs=&self->output;
    FluxMapID_6ph_codegen_initialize(self->PtrToModelData);
    return (self);
    return (self);
}

void uz_FluxMapID_6ph_step(uz_ParaID_FluxMapID_6ph_t* self, uz_ParaID_FluxMapIDConfig_t ID_config, uz_ParaID_ActualValues_t actual, uz_ParaID_GlobalConfig_t global_config, uz_ParaID_ControlFlags_t flags){
    self->input.FluxMapIDConfig=ID_config;
    self->input.ActualValues=actual;
    self->input.GlobalConfig_out=global_config;
    self->input.ControlFlags=flags;
    FluxMapID_6ph_codegen_step(self->PtrToModelData);
}

bool uz_get_FluxMapID_6ph_entered(uz_ParaID_FluxMapID_6ph_t* self)
{
    return self->output.enteredFluxMapID;
}

bool uz_get_FluxMapID_6ph_finished(uz_ParaID_FluxMapID_6ph_t* self)
{
    return self->output.finishedFluxMapID;
}

uz_ParaID_Controller_Parameters_output_t uz_get_FluxMapID_6ph_FOCoutput(uz_ParaID_FluxMapID_6ph_t* self)
{
    return self->output.FluxMapID_FOC_output;
}

uz_ParaID_FluxMapID_output_t uz_get_FluxMapID_6ph_output(uz_ParaID_FluxMapID_6ph_t* self)
{
    return self->output.FluxMapID_output;
}

#endif