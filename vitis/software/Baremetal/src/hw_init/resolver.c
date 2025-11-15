#include "../include/resolver.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

struct uz_resolverIP_config_t resolver_config_left={
        .base_address=XPAR_UZ_USER_RESOLVER_INTERFACE_V_0_BASEADDR,
        .ip_clk_frequency_Hz=100000000U,
        .resolution = 16,
        .freq_clockin = 8192000,
        .pole_pairs_machine = 4.0f,
        .pole_pairs_resolver = 1.0f,
        .zero_position_mechanical = 0.3959959f, //0.3923f <- was the rough estimate
        .mode_after_init = POSITION_VELOCITY_MODE,
     };

struct uz_resolverIP_config_t resolver_config_right={
        .base_address=XPAR_UZ_USER_RESOLVER_INTERFACE_V_1_BASEADDR,
        .ip_clk_frequency_Hz=100000000U,
        .resolution = 16,
        .freq_clockin = 8192000,
        .pole_pairs_machine = 4.0f,
        .pole_pairs_resolver = 1.0f,
        .zero_position_mechanical =  0.4008981f, //0.3964f <- was the rough estimate
        .mode_after_init = POSITION_VELOCITY_MODE,
     };

//void update_position_of_resolverIP(DS_Data* const data){
//     data->av.theta_mech = uz_resolverIP_readMechanicalPosition(data->objects.resolver_IP);
//     data->av.theta_elec = (data->av.theta_mech * uz_resolverIP_getMachinePolePairs(data->objects.resolver_IP)) - 2 * UZ_PIf * floor(data->av.theta_mech * uz_resolverIP_getMachinePolePairs(data->objects.resolver_IP)  / (2* UZ_PIf));
//}
//
//void update_speed_of_resolverIP(DS_Data* const data){
//     data->av.mechanicalRotorSpeed = uz_resolverIP_readMechanicalVelocity(data->objects.resolver_IP) * 60.f; //in rpm
//}
//
//void update_position_and_speed_of_resolverIP(DS_Data* const data){
//     uz_resolverIP_position_velocity_t  mechanical = uz_resolverIP_readMechanicalPositionAndVelocity(data->objects.resolver_IP);
//     data->av.theta_mech = mechanical.position;
//     data->av.mechanicalRotorSpeed = mechanical.velocity * 60.F; //rpm
//     data->av.theta_elec = (data->av.theta_mech * uz_resolverIP_getMachinePolePairs(data->objects.resolver_IP)) - 2.0f * UZ_PIf * floorf(data->av.theta_mech * uz_resolverIP_getMachinePolePairs(data->objects.resolver_IP)  / (2.0f * UZ_PIf));
//}

uz_resolverIP_t* initialize_resolver_left(void) {
	return (uz_resolverIP_init(resolver_config_left));
}

uz_resolverIP_t* initialize_resolver_right(void) {
	return (uz_resolverIP_init(resolver_config_right));
}

