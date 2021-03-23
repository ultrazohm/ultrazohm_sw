#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct uz_MyIp uz_MyIp;
typedef uz_MyIp* uz_MyIp_handle;

uz_MyIp_handle uz_MyIp_init(uint32_t baseAddr);
void uz_MyIp_setVariable(uz_MyIp_handle self,int variable);
int uz_MyIp_getVariable(uz_MyIp_handle self);