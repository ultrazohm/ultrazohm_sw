#include "../../uz/uz_global_configuration.h"
#include "../../uz/uz_ParameterID/uz_ParameterID_6ph.h"

#define RESONANT_LIMIT 10.0f
#define RESONANT_ANTIWINDUP_GAIN 10.0f

uz_ParameterID_6ph_t* init_ParaID_6ph_wrapper(void);
struct uz_ParameterID_controller init_ParaID_6ph_controller(void);
void init_ParaID_6ph_misc(void);
