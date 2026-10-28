#include "../include/resolver.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "../uz/uz_math_constants.h"
#include "xparameters.h"
#include <math.h>



struct uz_resolverIP_config_t resolver_config={
        .base_address=XPAR_UZ_DIGITAL_ADAPTER_D4_ADAPTER_RESOLVER_INTERFACE_V_0_BASEADDR,
        .ip_clk_frequency_Hz=100000000U,
        .resolution = 16,
        .freq_clockin = 8192000,
        .pole_pairs_machine = 4.0f,
        .pole_pairs_resolver = 1.0f,
        .zero_position_mechanical = 0.0f, //0.3923f <- was the rough estimate
        .mode_after_init = POSITION_VELOCITY_MODE,
     };


struct uz_resolver_pl_interface_config_t resolver_pl_config = {
               .base_address = XPAR_UZ_DIGITAL_ADAPTER_D4_ADAPTER_UZ_RESOLVER_PL_INTER_0_BASEADDR,
               .bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT,
               .ip_clk_frequency_Hz = 100000000U,
               .machine_polepairs = 4,
               .position_intmax = 65535,
               .resolver_polepairs = 1,
               .theta_m_offset_rad = -0.3841f //-0.3959959
};

struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs = {
               .n_mech_rpm = 0.0f,
               .omega_mech_rad_s = 0.0f,
               .position_el_2pi = 0.0f,
               .position_mech_2pi = 0.0f,
               .revolution_counter = 0
};


uz_resolverIP_t* initialize_resolver(void) {
	return (uz_resolverIP_init(resolver_config));
}

uz_resolver_pl_interface_t* initialize_resolver_pl_interface(void) {
	return (uz_resolver_pl_interface_init(resolver_pl_config,
			resolver_pl_outputs));
}


struct uz_resolver_pos_mt_config_t resolver_pos_mt_config = {
		.base_address = XPAR_UZ_RESOLVER_POS_MT_0_BASEADDR,
		.ip_clk_frequency_Hz = 100000000U,
};

uz_resolver_pos_mt_t* initialize_resolver_pos_mt(void) {
	return (uz_resolver_pos_mt_init(resolver_pos_mt_config));
}

// Counts per mechanical revolution derived from the resolver_pl_interface configuration.
// position_intmax is the largest representable value (2^16 - 1 = 65535); one full revolution
// spans position_intmax + 1 = 65536 counts (wrap at 2^16, cf. bitshift(.,16) in multiturn_counter.m).
static double counts_per_rev(void) {
	return ((double)(resolver_pl_config.position_intmax + 1));
}

static double counts_to_rad(int64_t counts) {
	return (((double)counts) * (2.0 * UZ_PId) / counts_per_rev());
}

static double counts_to_deg(int64_t counts) {
	return (((double)counts) * 360.0 / counts_per_rev());
}

static int64_t rad_to_counts(double rad) {
	return ((int64_t)llround(rad * counts_per_rev() / (2.0 * UZ_PId)));
}

static int64_t deg_to_counts(double deg) {
	return ((int64_t)llround(deg * counts_per_rev() / 360.0));
}

struct resolver_pos_mt_reading_t resolver_pos_mt_read_position(uz_resolver_pos_mt_t *self) {
	struct uz_resolver_pos_mt_outputs_t outputs = uz_resolver_pos_mt_get_outputs(self);
	struct resolver_pos_mt_reading_t reading = { 0 };
	reading.multiturn_position_counts = outputs.multiturn_position;
	reading.multiturn_position_rad = counts_to_rad(outputs.multiturn_position);
	reading.multiturn_position_deg = counts_to_deg(outputs.multiturn_position);
	reading.turns = outputs.turns;
	reading.singleturn_counts = outputs.singleturn_raw;
	reading.valid = outputs.pos_mt_valid;
	return (reading);
}

void resolver_pos_mt_write_preset_counts(uz_resolver_pos_mt_t *self, int64_t counts) {
	uz_resolver_pos_mt_load_preset(self, counts);
}

void resolver_pos_mt_write_preset_rad(uz_resolver_pos_mt_t *self, double rad) {
	uz_resolver_pos_mt_load_preset(self, rad_to_counts(rad));
}

void resolver_pos_mt_write_preset_deg(uz_resolver_pos_mt_t *self, double deg) {
	uz_resolver_pos_mt_load_preset(self, deg_to_counts(deg));
}
