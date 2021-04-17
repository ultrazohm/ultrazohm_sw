#include <stdio.h>
#include <assert.h>

#include "uz_ipCore.h"
#include "uz_ipCore_staticAllocator.h"

int main(){
    printf("test\n");
    uz_ipCore_handle ipCore_handle_instance1=uz_ipCore_allocateAndInit_Instance1();
    uz_ipCore_handle ipCore_handle_instance2=uz_ipCore_allocateAndInit_Instance2();
    int var=10;
    uz_ipCore_setVariable(ipCore_handle_instance1,var);
    uz_ipCore_setVariable(ipCore_handle_instance2,var*2);
    int readback=uz_ipCore_getVariable(ipCore_handle_instance1);
    int readback2=uz_ipCore_getVariable(ipCore_handle_instance2);
    assert(readback==var);
    assert(readback2==var*2);
    printf("var: %i \n readback: %i\n",var,readback);
    printf("var: %i \n readback: %i\n",var*2,readback2);
}