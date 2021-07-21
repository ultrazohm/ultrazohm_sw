// system includes
#include <stdbool.h>
#include <stdint.h>

// includes
#include "uz_adcLtc2311.h"
#include "uz_adcLtc2311_hw.h"
#include "../../uz/uz_HAL.h"
#include "uz_adcLtc2311_private.h"

// defines
#define IS_UZ_SUCCESS(ARG) ((ARG) == (UZ_SUCCESS) ? (true) : (false))
#define IS_UZ_FAILURE(ARG) ((ARG) == (UZ_FAILURE) ? (true) : (false))

/*********************
 *
 * private utilities
 *
 *********************/

static void uz_adcLtc2311_setLsbs(uint32_t* value, uint32_t bits) {
	uint32_t mask = 0;

	if (bits > sizeof(value)) {
		bits = sizeof(value);
	}

	for (uint32_t i = 0; i < bits; i++) {
		mask |= (1 << i);
	}

	*value = mask;
}

static int32_t uz_adcLtc2311_allMaskedBitsSetInValue(uint32_t value, uint32_t mask) {
	int32_t return_value = UZ_SUCCESS;

	for (uint32_t i = 0; i < sizeof(value); i++) {

		if (mask & (1 << i)) {

			if ((value & (1 << i)) == 0) {
				return_value = UZ_FAILURE;
				break;
			}
		}
	}

	return (return_value);
}

static int32_t uz_adcLtc2311_spiEnableManualControl(uz_adcLtc2311* self, uz_adcLtc2311_napSleepConfig* configuration) {
	uz_assert_not_NULL(self);
	int32_t return_value = UZ_SUCCESS;
	uint32_t max_attempts = configuration->max_attempts;

	uz_adcLtc2311_hw_write_spi_cr(self->base_address, uz_adcLtc2311_hw_read_spi_cr(self->base_address) | UZ_ADCLTC2311_SPI_CR_CONTROL);

	while ((uz_adcLtc2311_hw_read_spi_cr(self->base_address) & UZ_ADCLTC2311_SPI_CR_CONTROL_STATUS) == 0) {

		if ((configuration->try_infinite == false) && (--max_attempts <= 0)) {
			configuration->error_code |= UZ_ADCLTC2311_NS_TIMEOUT;
			return_value = UZ_FAILURE;
			break;
		}
	}

	return (return_value);
}

static int32_t uz_adcLtc2311_spiDisableManualControl(uz_adcLtc2311* self, uz_adcLtc2311_napSleepConfig* configuration) {
	uz_assert_not_NULL(self);
	uz_adcLtc2311_hw_write_spi_cr(self->base_address, uz_adcLtc2311_hw_read_spi_cr(self->base_address) & ~UZ_ADCLTC2311_SPI_CR_CONTROL);

	int32_t return_value = UZ_SUCCESS;
	uint32_t max_attempts = configuration->max_attempts;

	while (uz_adcLtc2311_hw_read_spi_cr(self->base_address) & UZ_ADCLTC2311_SPI_CR_CONTROL_STATUS) {

		if ((configuration->try_infinite == false) && (--max_attempts <= 0)) {
			configuration->error_code |= UZ_ADCLTC2311_NS_TIMEOUT;
			return_value = UZ_FAILURE;
			break;
		}
	}

	return (return_value);
}

static int32_t uz_adcLtc2311_spiManualControlIsEnabled(uz_adcLtc2311* self) {
	uz_assert_not_NULL(self);

	int32_t return_value = UZ_SUCCESS;

	if (uz_adcLtc2311_hw_read_spi_cr(self->base_address) & UZ_ADCLTC2311_SPI_CR_CONTROL_STATUS)
		return_value = UZ_SUCCESS;
	else
		return_value = UZ_FAILURE;

	return (return_value);

}

static void uz_adcLtc2311_spiSetSsN(uz_adcLtc2311* self, uint32_t spiMasters) {
	uz_assert_not_NULL(self);

	uz_adcLtc2311_hw_write_master_channel(self->base_address, spiMasters);
	uz_adcLtc2311_hw_write_spi_cr(self->base_address, uz_adcLtc2311_hw_read_spi_cr(self->base_address) | UZ_ADCLTC2311_SPI_CR_SS_N);

}

static void uz_adcLtc2311_spiResetSsN(uz_adcLtc2311* self, uint32_t spiMasters) {
	uz_assert_not_NULL(self);

	uz_adcLtc2311_hw_write_master_channel(self->base_address, spiMasters);
	uz_adcLtc2311_hw_write_spi_cr(self->base_address, uz_adcLtc2311_hw_read_spi_cr(self->base_address) & ~UZ_ADCLTC2311_SPI_CR_SS_N);

}

static void uz_adcLtc2311_spiSetSclk(uz_adcLtc2311* self, uint32_t spiMasters) {
	uz_assert_not_NULL(self);

	uz_adcLtc2311_hw_write_master_channel(self->base_address, spiMasters);
	uz_adcLtc2311_hw_write_spi_cr(self->base_address, uz_adcLtc2311_hw_read_spi_cr(self->base_address) | UZ_ADCLTC2311_SPI_CR_SCLK);

}

static void uz_adcLtc2311_spiResetSclk(uz_adcLtc2311* self, uint32_t spiMasters) {
	uz_assert_not_NULL(self);

	uz_adcLtc2311_hw_write_master_channel(self->base_address, spiMasters);
	uz_adcLtc2311_hw_write_spi_cr(self->base_address, uz_adcLtc2311_hw_read_spi_cr(self->base_address) & ~UZ_ADCLTC2311_SPI_CR_SCLK);

}

/*********************
 *
 * ADC functions
 *
 *********************/

uz_adcLtc2311* uz_adcLtc2311_init(uz_adcLtc2311* self) {
	// Check correct initialization
	uz_assert_not_NULL(self);
	uz_assert_false(self->is_ready);
	self->is_ready = true;
	uz_assert_not_zero(self->base_address);
	uz_assert_not_zero(self->ip_clk_frequency_Hz);
	self->napping_spi_masters = 0;
	self->sleeping_spi_masters = 0;
	return (self);
}

void uz_adcLtc2311_init_conversionConfig(uz_adcLtc2311_conversionConfig* configuration) {
	uz_assert_not_NULL(configuration);

	configuration->channel_select = 0;
	configuration->master_select = 0;
	configuration->conversion_factor = 1;
	configuration->offset = 0;
	configuration->set_conversion = false;
	configuration->set_offset = false;
	configuration->error_code = 0;
	configuration->try_infinite = true;
	configuration->max_attempts = 0;
}

int32_t uz_adcLtc2311_configureConversion(uz_adcLtc2311* self, uz_adcLtc2311_conversionConfig* configuration) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(configuration);

	uz_adcLtc2311_hw_write_master_channel(self->base_address, configuration->master_select);
	uz_adcLtc2311_hw_write_channel(self->base_address, configuration->channel_select);
	uint32_t uz_cr;
	int32_t return_value = UZ_SUCCESS;
	configuration->error_code = 0;

	uint32_t max_attempts = configuration->max_attempts;
	if (configuration->set_offset) {
		uz_cr = uz_adcLtc2311_hw_read_cr(self->base_address);
		uz_cr |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID;
		uz_cr &= ~UZ_ADCLTC2311_CR_OFF_CONV;
		uz_adcLtc2311_hw_write_conversion_value(self->base_address, configuration->offset);
		uz_adcLtc2311_hw_write_cr(self->base_address, uz_cr);

		while (uz_adcLtc2311_hw_read_cr(self->base_address) & UZ_ADCLTC2311_CR_CONV_VALUE_VALID) {

			if ((configuration->try_infinite == false) && (--max_attempts <= 0)) {
				configuration->error_code |= UZ_ADCLTC2311_SET_OFFSET_FAILED;
				return_value = UZ_FAILURE;
				break;
			}
		}
	}

	max_attempts = configuration->max_attempts;
	if (configuration->set_conversion) {
		uz_cr = uz_adcLtc2311_hw_read_cr(self->base_address);
		uz_cr |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID | UZ_ADCLTC2311_CR_OFF_CONV;
		uz_adcLtc2311_hw_write_conversion_value(self->base_address, configuration->conversion_factor);
		uz_adcLtc2311_hw_write_cr(self->base_address, uz_cr);

		while (uz_adcLtc2311_hw_read_cr(self->base_address) & UZ_ADCLTC2311_CR_CONV_VALUE_VALID) {

			if ((configuration->try_infinite == false) && (--max_attempts <= 0)) {
				configuration->error_code |= UZ_ADCLTC2311_SET_CONV_FAILED;
				return_value = UZ_FAILURE;
				break;
			}
		}
	}

	return (return_value);
}

int32_t uz_adcLtc2311_configureSpi(uz_adcLtc2311* self, uz_adcLtc2311_spiConfig* configuration) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(configuration);

	int32_t return_value = UZ_SUCCESS;
	configuration->error_code = 0;

	if (configuration->clk_div >> UZ_ADCLTC2311_SPI_CFGR_CLK_DIV_WIDTH) {
		uz_adcLtc2311_setLsbs(&(configuration->clk_div),
		UZ_ADCLTC2311_SPI_CFGR_CLK_DIV_WIDTH);
		uz_printf("CLK_DIV value is too big. Only the use of the lower %u bits is permitted.\n",
		UZ_ADCLTC2311_SPI_CFGR_CLK_DIV_WIDTH);
		uz_printf("New value is %u \n", configuration->clk_div);
		return_value = UZ_FAILURE;
		configuration->error_code |= UZ_ADCLTC2311_CLK_DIV_INVALID;
	}

	if (configuration->pre_delay >> UZ_ADCLTC2311_SPI_CFGR_PRE_DELAY_WIDTH) {
		uz_adcLtc2311_setLsbs(&(configuration->pre_delay),
		UZ_ADCLTC2311_SPI_CFGR_PRE_DELAY_WIDTH);
		uz_printf("PRE_DELAY value is too big. Only the use of the lower %u bits is permitted.\n",
		UZ_ADCLTC2311_SPI_CFGR_PRE_DELAY_WIDTH);
		uz_printf("New value is %u \n", configuration->pre_delay);
		return_value = UZ_FAILURE;
		configuration->error_code |= UZ_ADCLTC2311_PRE_DELAY_INVALID;
	}

	if (configuration->pre_delay >> UZ_ADCLTC2311_SPI_CFGR_POST_DELAY_WIDTH) {
		uz_adcLtc2311_setLsbs(&(configuration->post_delay),
		UZ_ADCLTC2311_SPI_CFGR_POST_DELAY_WIDTH);
		uz_printf("POST_DELAY value is too big. Only the use of the lower %u bits is permitted.\n",
		UZ_ADCLTC2311_SPI_CFGR_POST_DELAY_WIDTH);
		uz_printf("New value is %u \n", configuration->post_delay);
		return_value = UZ_FAILURE;
		configuration->error_code |= UZ_ADCLTC2311_POST_DELAY_INVALID;
	}

	uint32_t uz_spi_cfgr = (configuration->clk_div << UZ_ADCLTC2311_SPI_CFGR_CLK_DIV_LSB) | (configuration->pre_delay << UZ_ADCLTC2311_SPI_CFGR_PRE_DELAY_LSB)
	                | (configuration->post_delay << UZ_ADCLTC2311_SPI_CFGR_POST_DELAY_LSB);

	uz_adcLtc2311_hw_write_spi_cfgr(self->base_address, uz_spi_cfgr);

	uint32_t uz_spi_cr = uz_adcLtc2311_hw_read_spi_cr(self->base_address);

	if (configuration->cpha) {
		uz_spi_cr |= UZ_ADCLTC2311_SPI_CR_CPHA;
	} else {
		uz_spi_cr &= ~UZ_ADCLTC2311_SPI_CR_CPHA;
	}

	if (configuration->cpol) {
		uz_spi_cr |= UZ_ADCLTC2311_SPI_CR_CPOL;
	} else {
		uz_spi_cr &= ~UZ_ADCLTC2311_SPI_CR_CPOL;
	}

	uz_adcLtc2311_hw_write_spi_cr(self->base_address, uz_spi_cr);

	return (return_value);
}

void uz_adcLtc2311_init_spiConfig(uz_adcLtc2311_spiConfig* configuration) {
	uz_assert_not_NULL(configuration);
	configuration->error_code = 0;
	configuration->clk_div = 0;
	configuration->pre_delay = 0;
	configuration->post_delay = 0;
	configuration->cpha = 0;
	configuration->cpol = 1;
}

void uz_adcLtc2311_softwareReset(uz_adcLtc2311* self) {
	uz_assert_not_NULL(self);

	uz_adcLtc2311_hw_write_cr(self->base_address, uz_adcLtc2311_hw_read_cr(self->base_address) | UZ_ADCLTC2311_CR_SW_RESET);

	while (uz_adcLtc2311_hw_read_cr(self->base_address) & UZ_ADCLTC2311_CR_SW_RESET)
		;
}

void uz_adcLtc2311_softwareTrigger(uz_adcLtc2311* self, uint32_t spiMasters) {
	uz_assert_not_NULL(self);

	uz_adcLtc2311_hw_write_master_channel(self->base_address, spiMasters);
	uz_adcLtc2311_hw_write_cr(self->base_address, uz_adcLtc2311_hw_read_cr(self->base_address) | UZ_ADCLTC2311_CR_TRIGGER);
}

void uz_adcLtc2311_setContinuousMode(uz_adcLtc2311* self) {
	uz_assert_not_NULL(self);

	uz_adcLtc2311_hw_write_cr(self->base_address, uz_adcLtc2311_hw_read_cr(self->base_address) | UZ_ADCLTC2311_CR_MODE);
}

void uz_adcLtc2311_setTriggeredMode(uz_adcLtc2311* self) {
	uz_assert_not_NULL(self);

	uz_adcLtc2311_hw_write_cr(self->base_address, uz_adcLtc2311_hw_read_cr(self->base_address) & ~UZ_ADCLTC2311_CR_MODE);
}

void uz_adcLtc2311_init_napSleepConfig(uz_adcLtc2311_napSleepConfig* configuration) {
	uz_assert_not_NULL(configuration);

	configuration->error_code = 0;
	configuration->max_attempts = 0;
	configuration->spi_masters = 0;
	configuration->try_infinite = false;
}

int32_t uz_adcLtc2311_enterNapMode(uz_adcLtc2311* self, uz_adcLtc2311_napSleepConfig* configuration) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(configuration);
	int32_t return_value = UZ_SUCCESS;
	configuration->error_code = 0;

	if (configuration->spi_masters == 0) {
		return_value = UZ_FAILURE;
		configuration->error_code |= UZ_ADCLTC2311_NS_NO_SELECTION;
	}
	if ((self->napping_spi_masters & configuration->spi_masters) || (self->sleeping_spi_masters & configuration->spi_masters)) {
		return_value = UZ_FAILURE;
		configuration->error_code |= UZ_ADCLTC2311_NS_ALREADY_IN_MODE;
	}

	if (IS_UZ_SUCCESS(return_value)) {
		uz_adcLtc2311_hw_write_cr(self->base_address, uz_adcLtc2311_hw_read_cr(self->base_address) & ~UZ_ADCLTC2311_CR_MODE);

		// set default values for SS_N and SCLK
		uz_adcLtc2311_spiSetSsN(self, configuration->spi_masters);

		if (uz_adcLtc2311_hw_read_spi_cr(self->base_address) & UZ_ADCLTC2311_SPI_CR_CPOL)
			uz_adcLtc2311_spiSetSclk(self, configuration->spi_masters);
		else
			uz_adcLtc2311_spiResetSclk(self, configuration->spi_masters);

		return_value = uz_adcLtc2311_spiEnableManualControl(self, configuration);

		if (IS_UZ_FAILURE(return_value))
			configuration->error_code |= UZ_ADCLTC2311_NS_MAN_MODE_EN_FAILED;
		else {

			for (uint32_t i = 0; i < UZ_ADCLTC2311_NAP_PULSES; i++) {
				uz_adcLtc2311_spiSetSsN(self, configuration->spi_masters);
				uz_adcLtc2311_spiResetSsN(self, configuration->spi_masters);
			}

			uz_adcLtc2311_spiSetSsN(self, configuration->spi_masters);

			self->napping_spi_masters |= configuration->spi_masters;
			uz_adcLtc2311_hw_write_adc_available(self->base_address, uz_adcLtc2311_hw_read_adc_available(self->base_address) & ~configuration->spi_masters);
			return_value = uz_adcLtc2311_spiDisableManualControl(self, configuration);

			if (IS_UZ_FAILURE(return_value))
				configuration->error_code |=
				UZ_ADCLTC2311_NS_MAN_MODE_DIS_FAILED;
		}

	}

	return (return_value);
}

int32_t uz_adcLtc2311_leaveNapMode(uz_adcLtc2311* self, uz_adcLtc2311_napSleepConfig* configuration) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(configuration);
	int32_t return_value = UZ_SUCCESS;
	configuration->error_code = 0;

	if (configuration->spi_masters == 0) {
		return_value = UZ_FAILURE;
		configuration->error_code |= UZ_ADCLTC2311_NS_NO_SELECTION;
	}

	// check if all selected masters are in nap mode
	return_value = uz_adcLtc2311_allMaskedBitsSetInValue(self->napping_spi_masters, configuration->spi_masters);

	if (IS_UZ_FAILURE(return_value))
		configuration->error_code |= UZ_ADCLTC2311_NS_NOT_IN_MODE;
	else {
		// check if non of the selected SPI masters is in sleep mode
		if (configuration->spi_masters & self->sleeping_spi_masters) {
			configuration->error_code |= UZ_ADCLTC2311_NS_NOT_IN_MODE;
			return_value = UZ_FAILURE;
		}
	}

	if (IS_UZ_SUCCESS(return_value)) {
		uz_adcLtc2311_hw_write_cr(self->base_address, uz_adcLtc2311_hw_read_cr(self->base_address) & ~UZ_ADCLTC2311_CR_MODE);
		return_value = uz_adcLtc2311_spiEnableManualControl(self, configuration);

		if (IS_UZ_FAILURE(return_value))
			configuration->error_code |= UZ_ADCLTC2311_NS_MAN_MODE_EN_FAILED;
		else {
			uz_adcLtc2311_spiResetSclk(self, configuration->spi_masters);
			uz_adcLtc2311_spiSetSclk(self, configuration->spi_masters);
			self->napping_spi_masters &= ~configuration->spi_masters;
			uz_adcLtc2311_hw_write_adc_available(self->base_address, uz_adcLtc2311_hw_read_adc_available(self->base_address) | configuration->spi_masters);
			return_value = uz_adcLtc2311_spiDisableManualControl(self, configuration);

			if (IS_UZ_FAILURE(return_value))
				configuration->error_code |=
				UZ_ADCLTC2311_NS_MAN_MODE_DIS_FAILED;
		}

	}

	return (return_value);
}

int32_t uz_adcLtc2311_enterSleepMode(uz_adcLtc2311* self, uz_adcLtc2311_napSleepConfig* configuration) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(configuration);
	int32_t return_value = UZ_SUCCESS;
	uint32_t spi_masters = configuration->spi_masters;

	configuration->error_code = 0;

	if (spi_masters == 0) {
		return_value = UZ_FAILURE;
		configuration->error_code |= UZ_ADCLTC2311_NS_NO_SELECTION;
	}
	if (self->sleeping_spi_masters & spi_masters) {
		return_value = UZ_FAILURE;
		configuration->error_code |= UZ_ADCLTC2311_NS_ALREADY_IN_MODE;
	}

	if (IS_UZ_SUCCESS(return_value)) {
		uz_adcLtc2311_hw_write_cr(self->base_address, uz_adcLtc2311_hw_read_cr(self->base_address) & ~UZ_ADCLTC2311_CR_MODE);

		// set default values for SS_N and SCLK
		uz_adcLtc2311_spiSetSsN(self, configuration->spi_masters);

		if (uz_adcLtc2311_hw_read_spi_cr(self->base_address) & UZ_ADCLTC2311_SPI_CR_CPOL)
			uz_adcLtc2311_spiSetSclk(self, configuration->spi_masters);
		else
			uz_adcLtc2311_spiResetSclk(self, configuration->spi_masters);

		return_value = uz_adcLtc2311_spiEnableManualControl(self, configuration);

		if (IS_UZ_FAILURE(return_value))
			configuration->error_code |= UZ_ADCLTC2311_NS_MAN_MODE_EN_FAILED;
		else {
			// check which masters are currently in nap mode
			// with 2 additional pulses the master enters sleep mode from nap mode
			uint32_t nap_to_sleep = spi_masters & self->napping_spi_masters;

			if (nap_to_sleep) {
				// reset the bits for the masters which will enter sleep mode from nap mode
				spi_masters &= ~nap_to_sleep;

				for (uint32_t i = 0; i < UZ_ADCLTC2311_NAP_PULSES; i++) {
					uz_adcLtc2311_spiSetSsN(self, nap_to_sleep);
					uz_adcLtc2311_spiResetSsN(self, nap_to_sleep);
				}

				uz_adcLtc2311_spiSetSsN(self, nap_to_sleep);
				self->napping_spi_masters &= ~nap_to_sleep;
				self->sleeping_spi_masters |= nap_to_sleep;
			}

			if (spi_masters) {

				for (uint32_t i = 0; i < UZ_ADCLTC2311_SLEEP_PULSES; i++) {
					uz_adcLtc2311_spiSetSsN(self, spi_masters);
					uz_adcLtc2311_spiResetSsN(self, spi_masters);
				}

				uz_adcLtc2311_spiSetSsN(self, spi_masters);
				self->sleeping_spi_masters |= spi_masters;
				uz_adcLtc2311_hw_write_adc_available(self->base_address, uz_adcLtc2311_hw_read_adc_available(self->base_address) & ~spi_masters);
			}
			return_value = uz_adcLtc2311_spiDisableManualControl(self, configuration);
			if (IS_UZ_FAILURE(return_value))
				configuration->error_code |=
				UZ_ADCLTC2311_NS_MAN_MODE_DIS_FAILED;
		}

	}

	return (return_value);
}

int32_t uz_adcLtc2311_leaveSleepMode(uz_adcLtc2311* self, uz_adcLtc2311_napSleepConfig* configuration) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(configuration);
	int32_t return_value = UZ_SUCCESS;

	configuration->error_code = 0;

	if (configuration->spi_masters == 0) {
		return_value = UZ_FAILURE;
		configuration->error_code |= UZ_ADCLTC2311_NS_NO_SELECTION;
	}

	// check if all selected masters are in sleep mode
	return_value = uz_adcLtc2311_allMaskedBitsSetInValue(self->sleeping_spi_masters, configuration->spi_masters);

	if (IS_UZ_FAILURE(return_value))
		configuration->error_code |= UZ_ADCLTC2311_NS_NOT_IN_MODE;
	else {
		// check if non of the selected SPI masters is in nap mode
		if (configuration->spi_masters & self->napping_spi_masters) {
			configuration->error_code |= UZ_ADCLTC2311_NS_NOT_IN_MODE;
			return_value = UZ_FAILURE;
		}
	}

	if (IS_UZ_SUCCESS(return_value)) {
		uz_adcLtc2311_hw_write_cr(self->base_address, uz_adcLtc2311_hw_read_cr(self->base_address) & ~UZ_ADCLTC2311_CR_MODE);
		return_value = uz_adcLtc2311_spiEnableManualControl(self, configuration);

		if (IS_UZ_FAILURE(return_value))
			configuration->error_code |= UZ_ADCLTC2311_NS_MAN_MODE_EN_FAILED;
		else {
			uz_adcLtc2311_spiResetSsN(self, configuration->spi_masters);
			uz_adcLtc2311_spiSetSsN(self, configuration->spi_masters);
			self->sleeping_spi_masters &= ~configuration->spi_masters;
			uz_adcLtc2311_hw_write_adc_available(self->base_address, uz_adcLtc2311_hw_read_adc_available(self->base_address) | configuration->spi_masters);
			return_value = uz_adcLtc2311_spiDisableManualControl(self, configuration);

			if (IS_UZ_FAILURE(return_value))
				configuration->error_code |=
				UZ_ADCLTC2311_NS_MAN_MODE_DIS_FAILED;
		}

	}

	return (return_value);
}

