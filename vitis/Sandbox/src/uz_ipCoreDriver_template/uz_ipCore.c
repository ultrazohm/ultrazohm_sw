#include "uz_ipCore.h"
#include "uz_ipCore_private.h"

uz_ipCore* uz_ipCore_init(uz_ipCore* self){
  uz_assert_not_NULL(self); // prevent calls with NULL-pointer
  uz_assert(!self->is_ready); // prevent double initialization
  self->is_ready=true; // module is ready for usage with other functions
  return (self);
}

 void uz_ipCore_set_variable(uz_ipCore* self,int variable){
   self->variable=variable;
}

int uz_ipCore_get_variable(uz_ipCore* self){
     return (self->variable);
}