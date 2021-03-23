#include <stdio.h>
#include "uz_MyIp.h"
#include <assert.h>

int main(){
    printf("test\n");
    uint32_t baseAddr=0;
    uz_MyIp_handle MyIp=uz_MyIp_init(baseAddr);
    int var=10;
    uz_MyIp_setVariable(MyIp,var);
    int readback=0;
    readback=uz_MyIp_getVariable(MyIp);
    assert(readback==var);
    printf("var: %i \nreadback: %i\n",var,readback);
}