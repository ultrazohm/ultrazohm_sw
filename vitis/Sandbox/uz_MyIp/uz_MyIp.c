   #include "uz_MyIp.h"
   
   struct uz_MyIp{
   uint32_t baseAddr;
   int variable; 
   };

   uz_MyIp_handle uz_MyIp_init(uint32_t baseAddr){
     //uz_assertNotNull(baseAddr);
     uz_MyIp_handle self=malloc(sizeof(uz_MyIp));
     //uz_assertNotNull(self);
     self->baseAddr=baseAddr;
     return self;
    }

    void uz_MyIp_setVariable(uz_MyIp_handle self,int variable){
      //uz_assertNotNull(self);
      self->variable=variable;
    }

    int uz_MyIp_getVariable(uz_MyIp_handle self){
        //uz_assertNotNull(self);
        return (self->variable);
    };