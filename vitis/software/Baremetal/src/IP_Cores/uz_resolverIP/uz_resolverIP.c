/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2022 Felix Kaiser, Thomas Effenberger, Eyke Liegmann
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/

#include "../../uz/uz_global_configuration.h"
#if UZ_RESOLVERIP_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../../uz/uz_HAL.h"
#include "uz_resolverIP.h"
#include "uz_resolverIP_hw.h"
#include "../../uz/uz_math_constants.h"

/**
 * @brief Data type for object resolverIP
 *
 */
struct uz_resolverIP_t {
    bool is_ready;/**< Boolean that indicates successful initialization */
    struct uz_resolverIP_config_t config;/**< Configuration struct with members seen below */
    uz_resolverIP_mode mode;/**< enum that indicates current mode of AD2S1210 between Configuration Mode, Position Mode, Velocity Mode or PositionAndVelocityMode */
    float bitToRpsFactor; /**< Value derived during initialization from resolution; maps raw value to revs per second value*/
	int32_t bit_offset; /**< Value derived during initialization from resolution; maps raw value to revs per second value*/
	union{
 		int32_t registerValue; /** RESDAT Value 32bit*/
  		uint16_t pos_Vel[2]; /** 16bit position value in pos_Vel[0], 16bit velocity value in pos_Vel[1]*/
	}; 
};

static size_t instance_counter = 0U;
static uz_resolverIP_t instances[UZ_RESOLVERIP_MAX_INSTANCES] = { 0 };

static uz_resolverIP_t* uz_resolverIP_allocation(void);
static uz_resolverIP_t* uz_resolverIP_allocation(void){
    uz_assert(instance_counter < UZ_RESOLVERIP_MAX_INSTANCES);
    uz_resolverIP_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    return (self);
}

static float getRangeMax(uint32_t resolution);
static float getLSBSize(uint32_t resolution);


uz_resolverIP_t* uz_resolverIP_init(struct uz_resolverIP_config_t config) {
	 uz_assert_not_zero_uint32(config.base_address);
	 uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
     uz_assert(config.resolution == 10 || config.resolution == 12 || config.resolution == 14 || config.resolution == 16);
     uz_assert(config.freq_clockin >= 6144000U && config.freq_clockin <= 10240000U);
     uz_assert(config.zero_position_mechanical >= 0 && config.zero_position_mechanical < 2*UZ_PIf);
     uz_assert(config.pole_pairs_machine > 0);
     uz_assert(config.pole_pairs_resolver > 0);
	uz_resolverIP_t* self = uz_resolverIP_allocation();
	self->config =config;
    self->is_ready = true;
    self->config.zero_position_mechanical = config.zero_position_mechanical;
    self->config.pole_pairs_machine = config.pole_pairs_machine;
    self->config.pole_pairs_resolver = config.pole_pairs_resolver;
	self->registerValue = 0;

	switch (self->config.resolution){ //Factor is determined by tracking rate defined on p 4 of Datasheet, maps 2-complement value to rps value
	 	 case 16:
	 		self->bitToRpsFactor = uz_convert_sfixed_to_float(125,0) / uz_convert_sfixed_to_float(0x7FFF,0);
	 		self->bit_offset = 0;
	 		 break;
	 	 case 14:
	 		self->bitToRpsFactor = uz_convert_sfixed_to_float(500,0) / uz_convert_sfixed_to_float(0x1FFF,0);
	 		self->bit_offset = 2;
	 		 break;
	 	 case 12:
		 	self->bitToRpsFactor = uz_convert_sfixed_to_float(1000,0) / uz_convert_sfixed_to_float(0x7FF,0);
		 	self->bit_offset = 4;
	 		 break;
	 	 case 10:
		 	self->bitToRpsFactor = uz_convert_sfixed_to_float(2500,0) / uz_convert_sfixed_to_float(0x1FF,0);
		 	self->bit_offset = 6;
	 		 break;
	 	 default:
	 		 uz_assert(false);
	 }

    uz_resolverIP_hw_write_RESCON(self->config.base_address, RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);

    int32_t rescon = 0;
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
    rescon &= ~(RESCON_Data_uz_axi_VMODE_bit);
    rescon &= ~(RESCON_Data_uz_axi_PMODE_bit);
    uz_resolverIP_hw_write_RESCON(self->config.base_address, rescon);
    self->mode = CONFIG_MODE;
}

void uz_resolverIP_setZeroPosition(uz_resolverIP_t* self, float zero_pos){
    uz_assert_not_NULL(self)
    uz_assert(self->is_ready);
    uz_assert(zero_pos >= 0.F);
    uz_assert(zero_pos <= 2.F * UZ_PIf);

    self->config.zero_position_mechanical = zero_pos;
}

void uz_resolverIP_setMachinePolePairs(uz_resolverIP_t* self, float pole_pairs_machine){
    uz_assert_not_NULL(self)
    uz_assert(self->is_ready);
    uz_assert(pole_pairs_machine > 0);

    self->config.pole_pairs_machine = pole_pairs_machine;
}

float uz_resolverIP_getMachinePolePairs(uz_resolverIP_t* self){
    uz_assert_not_NULL(self)
	uz_assert(self->is_ready);
    return self->config.pole_pairs_machine;
}

void uz_resolverIP_setResolverPolePairs(uz_resolverIP_t* self, float pole_pairs_resolver){
    uz_assert_not_NULL(self)
    uz_assert(self->is_ready);
    uz_assert(pole_pairs_resolver > 0);

    self->config.pole_pairs_resolver = pole_pairs_resolver;
}

float uz_resolverIP_getResolverPolePairs(uz_resolverIP_t* self){
    uz_assert_not_NULL(self)
	uz_assert(self->is_ready);
    return self->config.pole_pairs_resolver;
}

void uz_resolverIP_setDataModeVelocity(uz_resolverIP_t* self){
    uz_assert_not_NULL(self)
    uz_assert(self->is_ready);
    int32_t rescon = uz_resolverIP_hw_read_RESCON(self->config.base_address);
    rescon &= ~(RESCON_Data_uz_axi_PMODE_bit);
    rescon |= (RESCON_Data_uz_axi_VMODE_bit);
    uz_resolverIP_hw_write_RESCON(self->config.base_address, rescon);
    self->mode = VELOCITY_MODE;
}

void uz_resolverIP_setDataModePosition(uz_resolverIP_t* self){
    uz_assert_not_NULL(self)
    uz_assert(self->is_ready);
    int32_t rescon = uz_resolverIP_hw_read_RESCON(self->config.base_address);
    rescon &= ~(RESCON_Data_uz_axi_VMODE_bit);
    rescon |= (RESCON_Data_uz_axi_PMODE_bit);
    uz_resolverIP_hw_write_RESCON(self->config.base_address, rescon);
    self->mode = POSITION_MODE;
}

void uz_resolverIP_setDataModePositionVelocity(uz_resolverIP_t* self){
    uz_assert_not_NULL(self)
    uz_assert(self->is_ready);
    int32_t rescon = uz_resolverIP_hw_read_RESCON(self->config.base_address);
    rescon |= (RESCON_Data_uz_axi_VMODE_bit);
    rescon |= (RESCON_Data_uz_axi_PMODE_bit);
    uz_resolverIP_hw_write_RESCON(self->config.base_address, rescon);
    self->mode = POSITION_VELOCITY_MODE;
}
float uz_resolverIP_readElectricalPosition(uz_resolverIP_t* self){
	 uz_assert_not_NULL(self)
	 uz_assert(self->is_ready);
	 float mech_position = uz_resolverIP_readMechanicalPosition(self);
	 float elec_position_wo_overflow = mech_position * self->config.pole_pairs_machine;
	 float overflow = (2.0f * UZ_PIf * floorf(mech_position * self->config.pole_pairs_machine  / (2.0f*UZ_PIf)));
	 return elec_position_wo_overflow - overflow;
}
float uz_resolverIP_readMechanicalPosition(uz_resolverIP_t* self){
	 uz_assert_not_NULL(self)
	 uz_assert(self->is_ready);

	 if (self->mode != POSITION_MODE){
		 uz_resolverIP_setDataModePosition(self);
	 }
	 int32_t rescon = 0;
	 do{
	      rescon = uz_resolverIP_hw_read_RESCON(self->config.base_address);
	  	  } while ((rescon & RESCON_Data_uz_axi_VALID_bit) == 0);

	 	self->registerValue = uz_resolverIP_hw_read_RESDAT(self->config.base_address);

	 	float position = uz_convert_sfixed_to_float(self->pos_Vel[0], (int)(self->config.resolution) - 1) * UZ_PIf;

	 	uz_assert(position >= 0.0f);
	 	uz_assert(position <= 2.0F *UZ_PIf);

	 	if (position - self->config.zero_position_mechanical < 0.0f){
	 		return 2*UZ_PIf + (position - self->config.zero_position_mechanical);
	 	}
	 	else {
	 		return position- self->config.zero_position_mechanical;
	 	}


}

float uz_resolverIP_readElectricalVelocity(uz_resolverIP_t* self){
	 uz_assert_not_NULL(self)
	 uz_assert(self->is_ready);

	 return uz_resolverIP_readMechanicalVelocity(self) * self->config.pole_pairs_machine;
}

float uz_resolverIP_readMechanicalVelocity(uz_resolverIP_t* self){
	 uz_assert_not_NULL(self)
	 uz_assert(self->is_ready);

	 if (self->mode != VELOCITY_MODE){
		 uz_resolverIP_setDataModeVelocity(self);
	 }
	 int32_t rescon = 0;
	 do{
	      rescon = uz_resolverIP_hw_read_RESCON(self->config.base_address);
	  } while ((rescon & RESCON_Data_uz_axi_VALID_bit) == 0);

	self->registerValue = uz_resolverIP_hw_read_RESDAT(self->config.base_address);
	float raw_value =  uz_convert_sfixed_to_float((self->pos_Vel[1]  << (16+self->bit_offset)),16+self->bit_offset); // AD2S1210 Datasheet: The value stored in the velocity register is 16 bits regardless of resolution. At lower resolutions, the LSBs of the 16-bit digital output should be ignored
	return raw_value *self->bitToRpsFactor / self->config.pole_pairs_resolver * 2.0f*UZ_PIf;

}
struct uz_resolverIP_position_velocity_t uz_resolverIP_readElectricalPositionAndVelocity(uz_resolverIP_t* self){
	uz_assert_not_NULL(self)
	uz_assert(self->is_ready);

	struct uz_resolverIP_position_velocity_t mechanical = uz_resolverIP_readMechanicalPositionAndVelocity(self);

	struct uz_resolverIP_position_velocity_t electrical;

	float elec_position_wo_overflow = mechanical.position * self->config.pole_pairs_machine;
	float overflow = (2.0f * UZ_PIf * floorf(mechanical.position * self->config.pole_pairs_machine  / (2.0f*UZ_PIf)));
	electrical.position = elec_position_wo_overflow - overflow;

	electrical.velocity = mechanical.velocity * self->config.pole_pairs_machine;

	return electrical;
}

struct uz_resolverIP_position_velocity_t uz_resolverIP_readMechanicalPositionAndVelocity(uz_resolverIP_t* self){
	 uz_assert_not_NULL(self)
	 uz_assert(self->is_ready);

	 if (self->mode != POSITION_VELOCITY_MODE){
		 uz_resolverIP_setDataModePositionVelocity(self);
	 }
	 int32_t rescon;
	 do{
	      rescon = uz_resolverIP_hw_read_RESCON(self->config.base_address);
	  } while ((rescon & RESCON_Data_uz_axi_VALID_bit) == 0);

	 self->registerValue = uz_resolverIP_hw_read_RESDAT(self->config.base_address);

	 float position = uz_convert_sfixed_to_float(self->pos_Vel[0], (int)(self->config.resolution) - 1)* UZ_PIf;

	 uz_assert(position >= 0.F);
	 uz_assert(position <= 2.F * UZ_PIf);

	 struct uz_resolverIP_position_velocity_t mechanical;

	 if (position - self->config.zero_position_mechanical < 0){
		 mechanical.position = 2*UZ_PIf + (position - self->config.zero_position_mechanical);
	}
	 else {
		 mechanical.position = position- self->config.zero_position_mechanical;
	 }

	float velocity_raw_value =  uz_convert_sfixed_to_float((self->pos_Vel[1]  << (16+self->bit_offset)),16+self->bit_offset); // AD2S1210 Datasheet: The value stored in the velocity register is 16 bits regardless of resolution. At lower resolutions, the LSBs of the 16-bit digital output should be ignored
	mechanical.velocity = velocity_raw_value *self->bitToRpsFactor / self->config.pole_pairs_resolver * 2.0f*UZ_PIf;

	return mechanical;
}

int32_t uz_resolverIP_readRegister(uz_resolverIP_t* self, int32_t addr){

    uz_assert_not_NULL(self)
    uz_assert(self->is_ready);
	uint8_t MSB = 128;
    uz_assert(addr < 2*MSB);
    uz_assert(addr >= 0);
    uz_assert_not_zero((uint8_t)(addr) & MSB); // check for MSB == 1 in address

    uz_resolverIP_setConfigMode(self);

	return uz_resolverIP_hw_readRegister(self->config.base_address, addr);

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

	uz_resolverIP_hw_writeRegister(self->config.base_address, addr, val);

}

void uz_resolverIP_setLOSThresh(uz_resolverIP_t* self, float thresh){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    
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
    uz_assert(self->is_ready);
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
    uz_assert(self->is_ready);
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
    uz_assert(self->is_ready);
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
    uz_assert(self->is_ready);
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
    uz_assert(self->is_ready);
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
    uz_assert(self->is_ready);
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
    uz_assert(self->is_ready);
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
    uz_assert(self->is_ready);
	uz_assert(max <= 4.82f);
	uz_assert(max >= 0.f);


	int32_t addrMax = DOS_RESET_MAX_REG_ADR;


	int32_t valMax = (int32_t) (max/0.038f) ;
	uz_assert(valMax <= 127);
	uz_assert(valMax >= 0);

	uz_resolverIP_writeRegister(self, addrMax, valMax);
}

float uz_resolverIP_getDOSResetMax(uz_resolverIP_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
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
    uz_assert(self->is_ready);
    float rangeMin = 0.f;
	float rangeMax = getRangeMax(self->config.resolution);
	float LSBsize = getLSBSize(self->config.resolution);

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
    uz_assert(self->is_ready);
	float rangeMin = 0.f;
	float rangeMax = getRangeMax(self->config.resolution);
	float LSBsize = getLSBSize(self->config.resolution);

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
    uz_assert(self->is_ready);
    float rangeMin = 0.f;
	float rangeMax = getRangeMax(self->config.resolution);
	float LSBsize = getLSBSize(self->config.resolution);


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
    uz_assert(self->is_ready);
	float rangeMin = 0.f;
	float rangeMax = getRangeMax(self->config.resolution);
	float LSBsize = getLSBSize(self->config.resolution);

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
    uz_assert(self->is_ready);

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
    uz_assert(self->is_ready);

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
    uz_assert(self->is_ready);
	uz_assert(register_value <= 0xFF);
	uz_assert(register_value >= 0x00);

	int32_t addr = CONTROL_REG_ADR;

	uz_resolverIP_writeRegister(self, addr, register_value);
}

int32_t uz_resolverIP_getCTRLReg(uz_resolverIP_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
	int32_t addr = CONTROL_REG_ADR;
	int32_t register_value = uz_resolverIP_readRegister(self, addr);

	uz_assert(register_value <= 0xFF);
	uz_assert(register_value >= 0);

	return register_value;
}


void uz_resolverIP_resetSoftware(uz_resolverIP_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
	int32_t addr = SOFTWARE_RST_REG_ADR;

	uz_resolverIP_writeRegister(self, addr, 0x00);

}


int32_t uz_resolverIP_getFLTRegister(uz_resolverIP_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
	int32_t addr = FAULT_REG_ADR;

	int32_t register_value = uz_resolverIP_readRegister(self, addr);

	uz_assert(register_value <= 0xFF);
	uz_assert(register_value >= 0);

	return register_value;

}

static float getRangeMax(uint32_t resolution)
{
	float rangeMax = 0.0f;

	switch(resolution){
		case 10U:
			rangeMax = 45.f;
			break;

		case 12U:
			rangeMax = 18.f;
				break;

		case 14U:
			rangeMax = 9.f;
				break;

		case 16U:
			rangeMax = 9.f;
				break;
        
        default:
            uz_assert(false);
	}
	return rangeMax;
}

static float getLSBSize(uint32_t resolution)
{
	float LSBSize = 0.0f;

	switch(resolution){
		case 10U:
			LSBSize = 0.35f;
			break;

		case 12U:
			LSBSize = 0.14f;
				break;

		case 14U:
			LSBSize = 0.09f;
				break;

		case 16U:
			LSBSize = 0.09f;
				break;
        
        default:
            uz_assert(false);
	}
	return LSBSize;
}


#endif
