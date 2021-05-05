#ifndef STATICALLOCATOR_H
#define STATICALLOCATOR_H

typedef struct allocator allocator;

allocator* allocator_init(int base_address);
int allocator_get_base_addres(allocator* self);
#endif // STATICALLOCATOR_H
