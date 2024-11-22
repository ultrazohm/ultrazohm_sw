	uint32_t kernel_dim = (kp_setup & ((1<<HSA_KERNEL_DISPATCH_PACKET_SETUP_WIDTH_DIMENSIONS)-1)) >> HSA_KERNEL_DISPATCH_PACKET_SETUP_DIMENSIONS;
	uint32_t kernel_meta = (unit_fences << 4) | kernel_dim;
	// write kernel configuration

	// pack kernel arguemts to use less AXI transfers
	uint32_t transfer1 = ((uint32_t)kp_wg_size_x << 16) | kernel_meta;
	uint32_t transfer2 = ((uint32_t)kp_wg_size_z   << 16) | ((uint32_t)kp_wg_size_y);
	uint32_t transfer3 = kp_grid_size_x;
	uint32_t transfer4 = ((uint32_t)kp_grid_size_y);
	uint32_t transfer5 = kp_grid_size_z;
	uint32_t transfer6 = ((uint32_t)pasid);
	uint32_t transfer7 = ((uint32_t)0);
	uint32_t transfer8 = ((uint32_t)0);

	uint32_t arg_transfer1 = ;
	uint32_t arg_transfer2 = ;
	uint32_t arg_transfer3 = ;
	uint32_t arg_transfer4 = ;
	uint32_t arg_transfer5 = ;
	uint32_t arg_transfer6 = ;


	*((volatile uint32_t*)(core_base_addr+DIM_OFFSET))       = transfer1;
	*((volatile uint32_t*)(core_base_addr+GRIDSIZEX_OFFSET)) = transfer2;
	*((volatile uint32_t*)(core_base_addr+GRIDSIZEZ_OFFSET)) = transfer3;
	*((volatile uint32_t*)(core_base_addr+GRIDSIZEZ_OFFSET)) = transfer4;
	*((volatile uint32_t*)(core_base_addr+GRIDSIZEZ_OFFSET)) = transfer5;
	*((volatile uint32_t*)(core_base_addr+GRIDSIZEZ_OFFSET)) = transfer6;
	*((volatile uint32_t*)(core_base_addr+GRIDSIZEZ_OFFSET)) = transfer7;
	*((volatile uint32_t*)(core_base_addr+GRIDSIZEZ_OFFSET)) = transfer8;
	
	*((volatile uint32_t*)(core_base_addr+GRIDSIZEZ_OFFSET)) = arg_transfer1;
	*((volatile uint32_t*)(core_base_addr+GRIDSIZEZ_OFFSET)) = arg_transfer2;
	*((volatile uint32_t*)(core_base_addr+GRIDSIZEZ_OFFSET)) = arg_transfer3;
	*((volatile uint32_t*)(core_base_addr+GRIDSIZEZ_OFFSET)) = arg_transfer4;
	*((volatile uint32_t*)(core_base_addr+GRIDSIZEZ_OFFSET)) = arg_transfer5;
	*((volatile uint32_t*)(core_base_addr+GRIDSIZEZ_OFFSET)) = arg_transfer6;

	// setup kernarg address and AXI config
	volatile uint8_t *kernarg_ptr = (volatile uint8_t*)kp_kernarg_addr;
	unsigned int kernarg_size = (volatile uint64_t)(kp_kobj->kernarg_length);

	// only execute kernel if kernel argument size is in the allowed range
	if(kernarg_size <= ACCEL_ADDR_SPACE_LEN-KERNARG_OFFSET){
		unsigned int num_8byte_writes = kernarg_size >> 3;
		unsigned int num_1byte_writes = kernarg_size - (num_8byte_writes << 3);

		// write all kernel arguments to the accelerator core configuration space
		uint32_t bytes_written = 0;
		for(unsigned int i=0; i<num_8byte_writes; ++i){
			*((volatile uint64_t*)(core_base_addr+KERNARG_OFFSET+bytes_written)) = *((volatile uint64_t*)kernarg_ptr);
			kernarg_ptr += 8;
			bytes_written += 8;
		}
	}
