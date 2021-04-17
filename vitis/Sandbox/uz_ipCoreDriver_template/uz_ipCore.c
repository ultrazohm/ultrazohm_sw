#include "uz_ipCore.h"
#include "uz_ipCore_private.h"

uz_ipCore_handle uz_ipCore_init(uz_ipCore_handle self){
  //uz_assertNotNull(baseAddr);
  return self;
}

 void uz_ipCore_setVariable(uz_ipCore_handle self,int variable){
   //uz_assertNotNull(self);
   self->variable=variable;
}

int uz_ipCore_getVariable(uz_ipCore_handle self){
     //uz_assertNotNull(self);
     return (self->variable);
};