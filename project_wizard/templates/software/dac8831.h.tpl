#include "../IP_Cores/uz_dac_interface/uz_dac_interface.h"
#include "../uz/uz_wavegen/uz_wavegen.h"

struct _DS_Data_;
uz_dac_interface_t* initialize_dac8831_{{ slot_lower }}(void);
void update_dac8831_{{ slot_lower }}_outputs(struct _DS_Data_* data);
