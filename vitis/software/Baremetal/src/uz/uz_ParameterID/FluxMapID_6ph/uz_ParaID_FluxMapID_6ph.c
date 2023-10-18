#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_6PH_MAX_INSTANCES > 0U

#include <stdbool.h>
#include "../../uz_HAL.h"
#include "uz_ParaID_FluxMapID_6ph.h"
#include "FluxMapID_6ph_codegen.h"

#include "../../uz_SystemTime/uz_SystemTime.h"


#define PARAMETERID6PH_FLUXMAP_RES_ORDER_AB 2.0f
#define PARAMETERID6PH_FLUXMAP_RES_ORDER_XY 6.0f
#define PARAMETERID6PH_FLUXMAP_ISR_FREQUENCY (UZ_PWM_FREQUENCY/INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE)
#define PARAMETERID6PH_FLUXMAP_AC_SQUARED ((0.1f*2.0f*UZ_PIf*PARAMETERID6PH_FLUXMAP_ISR_FREQUENCY)*(0.1f*2.0f*UZ_PIf*PARAMETERID6PH_FLUXMAP_ISR_FREQUENCY))

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
static void uz_FluxMapID_6ph_set_controller_parameter(uz_ParameterID_Data_t* Data, uz_CurrentControl_t* CC_instance_1, uz_CurrentControl_t* CC_instance_2, uz_resonantController_t* resonant_1, uz_resonantController_t* resonant_2);

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

bool uz_get_FluxMapID_6ph_entered(uz_ParaID_FluxMapID_6ph_t* self){
    return self->output.enteredFluxMapID;
}

bool uz_get_FluxMapID_6ph_finished(uz_ParaID_FluxMapID_6ph_t* self){
    return self->output.finishedFluxMapID;
}

uz_ParaID_Controller_Parameters_output_t* uz_get_FluxMapID_6ph_FOCoutput(uz_ParaID_FluxMapID_6ph_t* self){
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.FluxMapID_FOC_output);
}

uz_ParaID_FluxMapID_output_t* uz_get_FluxMapID_6ph_output(uz_ParaID_FluxMapID_6ph_t* self){
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.FluxMapID_output);
}

#endif
