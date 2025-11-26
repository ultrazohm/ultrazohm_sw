#pragma once

#include "../IP_Cores/uz_resolverIP/uz_resolverIP.h"
#include "../IP_Cores/uz_resolver_pl_interface/uz_resolver_pl_interface.h"

uz_resolverIP_t* initialize_resolver_left(void);
uz_resolverIP_t* initialize_resolver_right(void);

uz_resolver_pl_interface_t* initialize_resolver_pl_interface_left(void);
uz_resolver_pl_interface_t* initialize_resolver_pl_interface_right(void);
