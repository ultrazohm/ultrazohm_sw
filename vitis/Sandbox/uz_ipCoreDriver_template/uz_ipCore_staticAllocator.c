#include "uz_ipCore_staticAllocator.h"

static uz_ipCore ipCore_instance1={
  .base_address=0,
  .variable=0
};

static uz_ipCore ipCore_instance2={
  .base_address=1,
  .variable=0
};

uz_ipCore_handle uz_ipCore_allocateAndInit_instance1(void){
  return (uz_ipCore_init(&ipCore_instance1) );
}

uz_ipCore_handle uz_ipCore_allocateAndInit_instance2(void){
  return (uz_ipCore_init(&ipCore_instance2) );
}