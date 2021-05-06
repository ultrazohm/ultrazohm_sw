#include "staticAllocator.h"
#include "../../../software/Baremetal/src/uz/uz_HAL.h"
#define MAX_INSTANCES 2

struct allocator{
    int base_address;
    int is_ready;
};

static allocator instances[MAX_INSTANCES]={0};
static int instance_number=0;

allocator* allocator_init(int base_address){
    uz_assert(instance_number<MAX_INSTANCES);
    instance_number+=1;
    allocator* self = &instances[instance_number-1];
    self->base_address=base_address;
    return self;
}

int allocator_get_base_addres(allocator* self){
    return (self->base_address);
}