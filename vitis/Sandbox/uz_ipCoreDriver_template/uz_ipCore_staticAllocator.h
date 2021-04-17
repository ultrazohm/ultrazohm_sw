#include "uz_ipCore.h"
#include "uz_ipCore_private.h"

// In a real driver and application, the instances would have meaningful names that are coupled to their function
// e.g., interlockModule_3L and interlockModule_2L for the three and two level interlock module
static uz_ipCore ipCore_instance1={
  .baseAddr=0,
  .variable=0
};

static uz_ipCore ipCore_instance2={
  .baseAddr=1,
  .variable=0
};

uz_ipCore_handle uz_ipCore_allocateAndInit_Instance1(void){
  return (uz_ipCore_init(&ipCore_instance1) );
}

uz_ipCore_handle uz_ipCore_allocateAndInit_Instance2(void){
  return (uz_ipCore_init(&ipCore_instance2) );
}