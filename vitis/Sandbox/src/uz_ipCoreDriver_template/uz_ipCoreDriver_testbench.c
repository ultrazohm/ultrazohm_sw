#include <stdio.h>
#include <assert.h>
#include "uz_ipCore.h"
#include "uz_ipCore_staticAllocator.h"

int main(){
    uz_ipCore* ipCore_handle_instance1=uz_ipCore_allocateAndInit_instance1();
    uz_ipCore* ipCore_handle_instance2=uz_ipCore_allocateAndInit_instance2();
    int var=10;
    uz_ipCore_set_variable(ipCore_handle_instance1,var);
    uz_ipCore_set_variable(ipCore_handle_instance2,var*2);
    int readback=uz_ipCore_get_variable(ipCore_handle_instance1);
    int readback2=uz_ipCore_get_variable(ipCore_handle_instance2);
    assert(readback==var);
    assert(readback2==var*2);
}