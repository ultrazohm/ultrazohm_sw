#include "../include/uz_endat_interface_init.h"
#include "xparameters.h"

#define ENDAT_D4_IP_CLK_FREQUENCY_HZ 100000000U
#define ENDAT_D4_MACHINE_POLEPAIRS 4U
#define ENDAT_D4_CLK_FREQUENCY_HZ 2500000U
#define ENDAT_D4_POSITION_MECH_OFFSET_RAD (-1.0f)
#define ENDAT_D4_ENCODER_BIT_WIDTH_SINGLE_TURN 25U
#define ENDAT_D4_ENCODER_BIT_WIDTH_MULTI_TURN 12U
#define ENDAT_D4_KP_PLL 628.3185f
#define ENDAT_D4_KI_PLL 98696.0f
#define ENDAT_D4_SAMPLING_INTERVAL_SECONDS 0.0001f
#define ENDAT_D4_DELAY_SAMPLING_CLK_TICKS 0U

static struct uz_endat_interface_config_t endat_d4_1_config = {
    .base_address = XPAR_UZ_USER_ADAPTER_D4_UZ_ENDAT_INTERFACE_0_BASEADDR,
    .ip_clk_frequency_Hz = ENDAT_D4_IP_CLK_FREQUENCY_HZ,
    .machine_polepairs = ENDAT_D4_MACHINE_POLEPAIRS,
    .endat_clk_frequency_Hz = ENDAT_D4_CLK_FREQUENCY_HZ,
    .position_mech_offset_si_single_turn = ENDAT_D4_POSITION_MECH_OFFSET_RAD,
    .endat_encoder_bit_width_single_turn = ENDAT_D4_ENCODER_BIT_WIDTH_SINGLE_TURN,
    .endat_encoder_bit_width_multi_turn = ENDAT_D4_ENCODER_BIT_WIDTH_MULTI_TURN,
    .kp_pll = ENDAT_D4_KP_PLL,
    .ki_pll = ENDAT_D4_KI_PLL,
    .sampling_interval_seconds = ENDAT_D4_SAMPLING_INTERVAL_SECONDS,
    .delay_sampling_in_clk_ticks = ENDAT_D4_DELAY_SAMPLING_CLK_TICKS};

uz_endat_interface_t *endat_encoder_init_endat_d4_1(void)
{
    return (uz_endat_interface_init(endat_d4_1_config));
}

void update_endat_encoder_on_D4(DS_Data *const data)
{
    data->av.endat_machine.theta_mech = uz_endat_interface_get_position_mech_si_single_turn(data->objects.endat_encoder_d4_1);
    data->av.endat_machine.theta_elec = uz_endat_interface_get_position_el_si_single_turn(data->objects.endat_encoder_d4_1);
    data->av.endat_machine.mechanicalRotorSpeed = uz_endat_interface_get_speed_mech_rpm(data->objects.endat_encoder_d4_1);
    data->av.endat_machine.electricalRotorSpeed = uz_endat_interface_get_speed_el_si(data->objects.endat_encoder_d4_1);
}
