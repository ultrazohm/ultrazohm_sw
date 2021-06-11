

#define UZ_STATIC_ALLOCATOR(objectname,maxinstances)                             \
                                                                                 \
static size_t ##objectname##_counter = 0;                                        \
static objectname ##objectname##_instances[maxinstances] = { 0 };                \
                                                                                 \
objectname * ##objectname##_allocator(void) {                                    \
	uz_assert(##objectname##_counter < UZ_WAVEGEN_THREE_PHASE_MAX_INSTANCES);    \
	objectname * self = &##objectname##_instances[##objectname##_counter];       \
	uz_assert(self->is_ready == false);                                          \
	##objectname##_counter += 1;                                                 \
	self->is_ready = true;                                                       \
	return (self);                                                               \
}                                                                                \