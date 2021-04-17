#include "uz_ipCore.h"
#include "uz_ipCore_private.h"

uz_ipCore_handle uz_ipCore_init(uz_ipCore_handle self){
  return self;
}

 void uz_ipCore_set_variable(uz_ipCore_handle self,int variable){
   self->variable=variable;
}

int uz_ipCore_get_variable(uz_ipCore_handle self){
     return (self->variable);
}