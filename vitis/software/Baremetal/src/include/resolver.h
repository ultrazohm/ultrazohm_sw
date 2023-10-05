#ifndef _HW_INIT_RESOLVER_H_
#define _HW_INIT_RESOLVER_H_

#include "../IP_Cores/uz_resolverIP/uz_resolverIP.h"
#include "../IP_Cores/uz_resolver_pl_interface/uz_resolver_pl_interface.h"

uz_resolverIP_t* init_resolver_d4(void);

uz_resolver_pl_interface_t* initialize_resolver_pl_d4(void);

#endif
