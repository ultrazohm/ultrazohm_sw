#include "../../uz/uz_global_configuration.h"
#if UZ_RESOLVERIP_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "uz_HAL.h"
#include "uz_resolverIP.h"
#include "uz_resolverIP_hw.h"

/**
 * @brief Data type for object resolverIP
 *
 */
struct uz_resolverIP_t {
    bool is_ready;/**< Boolean that indicates successful initialization */
    struct uz_resolverIP_config_t config;/**< Configuration struct with members seen below */
    uz_resolverIP_mode mode;/**< enum that indicates current mode of AD2S1210 between Configuration Mode, Position Mode and Velocity Mode */
};

static size_t instance_counter = 0U;
static uz_resolverIP_t instances[UZ_RESOLVERIP_MAX_INSTANCES] = { 0 };

static uz_resolverIP_t* uz_resolverIP_allocation(void);

static uz_resolverIP_t* uz_resolverIP_allocation(void){
    uz_assert(instance_counter < UZ_RESOLVERIP_MAX_INSTANCES);
    uz_resolverIP_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_resolverIP_t* uz_resolverIP_init(struct uz_resolverIP_config_t configNew) {
	 uz_assert_not_zero_uint32(configNew.base_address);
	 uz_assert_not_zero_uint32(configNew.ip_clk_frequency_Hz);
     uz_assert(configNew.resolution == 10 || configNew.resolution == 12 || configNew.resolution == 14 || configNew.resolution == 16);
     uz_assert(configNew.freq_clockin > 6000000U && configNew.freq_clockin < 11000000U);

	 uz_resolverIP_t* self = uz_resolverIP_allocation();
	 self->config =configNew;

    uz_resolverIP_hw_write_RESCON(self->config.base_address, RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);

    int32_t rescon;
    do{
        rescon = uz_resolverIP_hw_read_RESCON(self->config.base_address);
    } while (rescon & RESCON_Data_uz_axi_BUSY_bit);

    uz_resolverIP_setConfigMode(self);
    return self;
}

void uz_resolverIP_setConfigMode(uz_resolverIP_t* self){
    uz_assert_not_NULL(self)
    uz_assert(self->is_ready);

    int32_t rescon = uz_resolverIP_hw_read_RESCON(self->config.base_address);
    rescon |= RESCON_Data_uz_axi_CMODE_bit;
    uz_resolverIP_hw_write_RESCON(self->config.base_address, rescon);
    self->mode = CONFIG_MODE;
}


void uz_resolverIP_setDataModeVelocity(uz_resolverIP_t* self){
    uz_assert_not_NULL(self)
    uz_assert(self->is_ready);
    int32_t rescon = uz_resolverIP_hw_read_RESCON(self->config.base_address);
    rescon &= ~(RESCON_Data_uz_axi_CMODE_bit);
    rescon |= (RESCON_Data_uz_axi_DMODE_bit);
    uz_resolverIP_hw_write_RESCON(self->config.base_address, rescon);
    self->mode = VELOCITY_MODE;
}

void uz_resolverIP_setDataModePosition(uz_resolverIP_t* self){
    uz_assert_not_NULL(self)
    uz_assert(self->is_ready);
    int32_t rescon = uz_resolverIP_hw_read_RESCON(self->config.base_address);
    rescon &= ~(RESCON_Data_uz_axi_CMODE_bit);
    rescon &= ~(RESCON_Data_uz_axi_DMODE_bit);
    uz_resolverIP_hw_write_RESCON(self->config.base_address, rescon);
    self->mode = POSITION_MODE;
}

int32_t uz_resolverIP_readData(uz_resolverIP_t* self){
    uz_assert_not_NULL(self)
    uz_assert(self->is_ready);
    int32_t rescon = uz_resolverIP_hw_read_RESCON(self->config.base_address);
    rescon |= RESCON_Data_uz_axi_GO_bit;
    uz_resolverIP_hw_write_RESCON(self->config.base_address, rescon);
    rescon &= ~(RESCON_Data_uz_axi_GO_bit);
    uz_resolverIP_hw_write_RESCON(self->config.base_address, rescon);
    do{
        rescon = uz_resolverIP_hw_read_RESCON(self->config.base_address);
    } while (rescon & RESCON_Data_uz_axi_BUSY_bit);
    
    return uz_resolverIP_hw_read_RESDAT(self->config.base_address);
}

int32_t uz_resolverIP_readRegister(uz_resolverIP_t* self, int32_t addr){
    uz_assert_not_NULL(self)
    uz_assert(self->is_ready);
    uint8_t MSB = 128;
    uz_assert(addr < 2*MSB);
    uz_assert(addr >= 0);
    uz_assert_not_zero((uint8_t)(addr) & MSB); // check for MSB == 1 in address

    uz_resolverIP_setConfigMode(self);

    int32_t rescon = uz_resolverIP_hw_read_RESCON(self->config.base_address);
    rescon &= ~(RESCON_Data_uz_axi_RW_bit);
    uz_resolverIP_hw_write_RESCON(self->config.base_address, rescon);

    uz_resolverIP_hw_write_RESADR(self->config.base_address, addr);

    rescon |= RESCON_Data_uz_axi_GO_bit;
    uz_resolverIP_hw_write_RESCON(self->config.base_address, rescon);
    rescon &= ~(RESCON_Data_uz_axi_GO_bit);
    uz_resolverIP_hw_write_RESCON(self->config.base_address, rescon);

    do{
        rescon = uz_resolverIP_hw_read_RESCON(self->config.base_address);
    } while (rescon & RESCON_Data_uz_axi_BUSY_bit);
    
    return uz_resolverIP_hw_read_RESRDA(self->config.base_address);
}

void uz_resolverIP_writeRegister(uz_resolverIP_t* self, int32_t addr, int32_t val){
    uz_assert_not_NULL(self)
    uz_assert(self->is_ready);
     uint8_t MSB = 128;
    uz_assert(addr < 2*MSB);
    uz_assert(addr >= 0);
    uz_assert_not_zero((uint8_t)(addr) & MSB); // check for MSB == 1 in address
    uz_assert(val <= 0xFF);
    uz_assert(val >= 0);

    uz_resolverIP_setConfigMode(self);

    int32_t rescon = uz_resolverIP_hw_read_RESCON(self->config.base_address);
    rescon |= RESCON_Data_uz_axi_RW_bit;
    uz_resolverIP_hw_write_RESCON(self->config.base_address, rescon);

    uz_resolverIP_hw_write_RESADR(self->config.base_address, addr);
    uz_resolverIP_hw_write_RESDAT(self->config.base_address, val);
    
    rescon |= RESCON_Data_uz_axi_GO_bit;
    uz_resolverIP_hw_write_RESCON(self->config.base_address, rescon);
    rescon &= ~(RESCON_Data_uz_axi_GO_bit);
    uz_resolverIP_hw_write_RESCON(self->config.base_address, rescon);

    do{
        rescon = uz_resolverIP_hw_read_RESCON(self->config.base_address);
    } while (rescon & RESCON_Data_uz_axi_BUSY_bit);
}

void uz_resolverIP_setLOSThresh(uz_resolverIP_t* self, float thresh){
    uz_assert_not_NULL(self);
    
    uz_assert(thresh <= 4.82f);
	uz_assert(thresh >= 0.f);

	int32_t addr = LOS_THRESHOLD_REG_ADR;

	int32_t val = (int) (thresh/0.038f) ;
	uz_assert(val <= 127);
	uz_assert(val >= 0);

	uz_resolverIP_writeRegister(self, addr, val);
}

float uz_resolverIP_getLOSThresh(uz_resolverIP_t* self){
    uz_assert_not_NULL(self);

	int32_t addr = LOS_THRESHOLD_REG_ADR;
	int32_t val = uz_resolverIP_readRegister(self, addr);

	uz_assert(val <= 127);
	uz_assert(val >= 0);

	float val_f = (float) val;
	float thresh = val_f* 0.038f;

	uz_assert(thresh <= 4.82f);
	uz_assert(thresh >= 0.f);

	return thresh;
}


void uz_resolverIP_setDOSOverrangeThresh(uz_resolverIP_t* self, float thresh){
    uz_assert_not_NULL(self);

	uz_assert(thresh <= 4.82f);
	uz_assert(thresh >= 0.f);

	int32_t addr = DOS_OVERRANGE_REG_ADR;

	int32_t val = (int) (thresh/0.038f) ;
	uz_assert(val <= 127);
	uz_assert(val >= 0);

	uz_resolverIP_writeRegister(self, addr, val);
}

float uz_resolverIP_getDOSOverrangeThresh(uz_resolverIP_t* self){
    uz_assert_not_NULL(self);
    
	int32_t addr = DOS_OVERRANGE_REG_ADR;
	int32_t val = uz_resolverIP_readRegister(self, addr);

	uz_assert(val <= 127);
	uz_assert(val >= 0);

	float val_f = (float) val;
	float thresh = val_f* 0.038f;

	uz_assert(thresh <= 4.82f);
	uz_assert(thresh >= 0.f);

	return thresh;
}

void uz_resolverIP_setDOSMismatchThresh(uz_resolverIP_t* self, float thresh){
    uz_assert_not_NULL(self);
	uz_assert(thresh <= 4.82f);
	uz_assert(thresh >= 0.f);

	int32_t addr = DOS_MISMATCH_REG_ADR;

	int32_t val = (int) (thresh/0.038f) ;
	uz_assert(val <= 127);
	uz_assert(val >= 0);

	uz_resolverIP_writeRegister(self, addr, val);
}

float uz_resolverIP_getDOSMismatchThresh(uz_resolverIP_t* self){
    uz_assert_not_NULL(self);
    
	int32_t addr = DOS_MISMATCH_REG_ADR;
	int32_t val = uz_resolverIP_readRegister(self, addr);

	uz_assert(val <= 127);
	uz_assert(val >= 0);

	float val_f = (float) val;
	float thresh = val_f* 0.038f;

	uz_assert(thresh <= 4.82f);
	uz_assert(thresh >= 0.f);

	return thresh;
}


void uz_resolverIP_setDOSResetMin(uz_resolverIP_t* self, float min){
    uz_assert_not_NULL(self);
    
	uz_assert(min <= 4.82f);
	uz_assert(min >= 0.f);


	int32_t addrMin = DOS_RESET_MIN_REG_ADR;

	int32_t valMin = (int) (min/0.038f);
	uz_assert(valMin <= 127);
	uz_assert(valMin >= 0);

	uz_resolverIP_writeRegister(self, addrMin, valMin);
}

float uz_resolverIP_getDOSResetMin(uz_resolverIP_t* self){
    uz_assert_not_NULL(self);
    
	int32_t addrMin = DOS_RESET_MIN_REG_ADR;

	int32_t valMin = uz_resolverIP_readRegister(self, addrMin);

	uz_assert(valMin <= 127);
	uz_assert(valMin >= 0);


	float valMin_f = (float) valMin;
	float threshMin = valMin_f* 0.038f;

	uz_assert(threshMin <= 4.82f);
	uz_assert(threshMin >= 0.f);

	return threshMin;
}


void uz_resolverIP_setDOSResetMax(uz_resolverIP_t* self, float max){
    uz_assert_not_NULL(self);
	uz_assert(max <= 4.82f);
	uz_assert(max >= 0.f);


	int32_t addrMax = DOS_RESET_MAX_REG_ADR;


	int32_t valMax = (int) (max/0.038f) ;
	uz_assert(valMax <= 127);
	uz_assert(valMax >= 0);

	uz_resolverIP_writeRegister(self, addrMax, valMax);
}

float uz_resolverIP_getDOSResetMax(uz_resolverIP_t* self){
    uz_assert_not_NULL(self);
    
	int32_t addrMax = DOS_RESET_MAX_REG_ADR;

	int32_t valMax = uz_resolverIP_readRegister(self, addrMax);

	uz_assert(valMax <= 127);
	uz_assert(valMax >= 0);

	float valMax_f = (float) valMax;
	float threshMax = valMax_f* 0.038f;

	uz_assert(threshMax <= 4.82f);
	uz_assert(threshMax >= 0.f);

	return threshMax;
}


void uz_resolverIP_setLOTHighThresh(uz_resolverIP_t* self, float thresh){
    uz_assert_not_NULL(self);    
    
    float rangeMin = 0.f;
	float rangeMax;
	float LSBsize;
	switch(self->config.resolution){
		case 10U:
			rangeMax = 45.f;
			LSBsize = 0.35f;
			break;

		case 12U:
			rangeMax = 18.f;
			LSBsize = 0.14f;
				break;

		case 14U:
			rangeMax = 9.f;
			LSBsize = 0.09f;
				break;

		case 16U:
			rangeMax = 9.f;
			LSBsize = 0.09f;
				break;
        
        default:
            uz_assert(false);
	}



	uz_assert(thresh <= rangeMax);
	uz_assert(thresh >= rangeMin);

	int32_t addr = LOT_HIGH_THRESH_REG_ADR;

	int32_t val = (int32_t) (thresh/LSBsize) ;
	uz_assert(val <= 127);
	uz_assert(val >= 0);

	uz_resolverIP_writeRegister(self, addr, val);
}

float uz_resolverIP_getLOTHighThresh(uz_resolverIP_t* self){
    uz_assert_not_NULL(self);
    
	float rangeMin = 0.f;
	float rangeMax;
	float LSBsize;
	switch(self->config.resolution){
		case 10U:
			rangeMax = 45.f;
			LSBsize = 0.35f;
			break;

		case 12U:
			rangeMax = 18.f;
			LSBsize = 0.14f;
				break;

		case 14U:
			rangeMax = 9.f;
			LSBsize = 0.09f;
				break;

		case 16U:
			rangeMax = 9.f;
			LSBsize = 0.09f;
				break;

        default:
            uz_assert(false);
	}

	int32_t addr = LOT_HIGH_THRESH_REG_ADR;
	int32_t val = uz_resolverIP_readRegister(self, addr);

	uz_assert(val <= 127);
	uz_assert(val >= 0);

	float val_f = (float) val;
	float thresh = val_f* LSBsize;

	uz_assert(thresh <= rangeMax);
	uz_assert(thresh >= rangeMin);

	return thresh;
}

void uz_resolverIP_setLOTLowThresh(uz_resolverIP_t* self, float thresh){
    uz_assert_not_NULL(self);
    
    float rangeMin = 0.f;
	float rangeMax;
	float LSBsize;
	switch(self->config.resolution){
		case 10U:
			rangeMax = 45.f;
			LSBsize = 0.35f;
			break;

		case 12U:
			rangeMax = 18.f;
			LSBsize = 0.14f;
				break;

		case 14U:
			rangeMax = 9.f;
			LSBsize = 0.09f;
				break;

		case 16U:
			rangeMax = 9.f;
			LSBsize = 0.09f;
				break;

        default:
            uz_assert(false);
	}



	uz_assert(thresh <= rangeMax);
	uz_assert(thresh >= rangeMin);

	int32_t addr = LOT_LOW_THRESH_REG_ADR;

	int32_t val = (int32_t) (thresh/LSBsize) ;
	uz_assert(val <= 127);
	uz_assert(val >= 0);

	uz_resolverIP_writeRegister(self, addr, val);
}

float uz_resolverIP_getLOTLowThresh(uz_resolverIP_t* self){
    uz_assert_not_NULL(self);
    
	float rangeMin = 0.f;
	float rangeMax;
	float LSBsize;
	switch(self->config.resolution){
		case 10U:
			rangeMax = 45.f;
			LSBsize = 0.35f;
			break;

		case 12U:
			rangeMax = 18.f;
			LSBsize = 0.14f;
				break;

		case 14U:
			rangeMax = 9.f;
			LSBsize = 0.09f;
				break;

		case 16U:
			rangeMax = 9.f;
			LSBsize = 0.09f;
				break;

        default:
            uz_assert(false);
	}

	int32_t addr = LOT_LOW_THRESH_REG_ADR;
	int32_t val = uz_resolverIP_readRegister(self, addr);

	uz_assert(val <= 127);
	uz_assert(val >= 0);

	float val_f = (float) val;
	float thresh = val_f* LSBsize;

	uz_assert(thresh <= rangeMax);
	uz_assert(thresh >= rangeMin);

	return thresh;
}

void uz_resolverIP_setExcitationFrequency(uz_resolverIP_t* self, float excFreq){
    uz_assert_not_NULL(self);
    

	uz_assert(excFreq <= 20000.f);
	uz_assert(excFreq >= 2000.f);

	int32_t addr = EXIT_FREQ_REG_ADR;

	int32_t fCW = (int32_t) (excFreq*(1<<15)/self->config.freq_clockin);
	uz_assert(fCW <= 0x50);
	uz_assert(fCW >= 0x4);

	uz_resolverIP_writeRegister(self, addr, fCW);
}

float uz_resolverIP_getExcitationFrequency(uz_resolverIP_t* self){
    uz_assert_not_NULL(self);
    

	int32_t addr = EXIT_FREQ_REG_ADR;
	int32_t val = uz_resolverIP_readRegister(self, addr);

	uz_assert(val <= 0x50);
	uz_assert(val >= 0x4);

	float val_f = (float) val;
	float excFreq = val_f* self->config.freq_clockin / (1<<15);

	uz_assert(excFreq <= 20000.f);
	uz_assert(excFreq >= 2000.f);

	return excFreq;
}


void uz_resolverIP_setCTRLReg(uz_resolverIP_t* self, int32_t register_value){
    uz_assert_not_NULL(self);
    
	uz_assert(register_value <= 0xFF);
	uz_assert(register_value >= 0x00);

	int32_t addr = CONTROL_REG_ADR;

	uz_resolverIP_writeRegister(self, addr, register_value);
}

int32_t uz_resolverIP_getCTRLReg(uz_resolverIP_t* self){
    uz_assert_not_NULL(self);
    
	int32_t addr = CONTROL_REG_ADR;
	int32_t register_value = uz_resolverIP_readRegister(self, addr);

	uz_assert(register_value <= 0xFF);
	uz_assert(register_value >= 0);

	return register_value;
}


void uz_resolverIP_resetSoftware(uz_resolverIP_t* self){
    uz_assert_not_NULL(self);
    
	int32_t addr = SOFTWARE_RST_REG_ADR;

	uz_resolverIP_writeRegister(self, addr, 0x00);

}


int32_t uz_resolverIP_getFLTRegister(uz_resolverIP_t* self){
    uz_assert_not_NULL(self);
    
	int32_t addr = FAULT_REG_ADR;

	int32_t register_value = uz_resolverIP_readRegister(self, addr);

	uz_assert(register_value <= 0xFF);
	uz_assert(register_value >= 0);

	return register_value;

}


#endif