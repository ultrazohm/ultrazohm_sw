#include "../include/uz_temperature_card_init.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

  struct uz_temperaturecard_config_t config_temperature_card = {
  // general config
  .base_address = XPAR_UZ_USER_TEMPERATURE_CARD_INT_0_BASEADDR,
  .ip_clk_frequency_Hz = 100000000U,
  .Sample_Freq_Hz = 5U, // we are fine with 5 Hz since the LTC2983 itself isn't that fast with updating the results
  // channelgroup A
  .Configdata_A = {0U}, // for proper configuration we will come back later
  // channelgroup B
  .Configdata_B = {0U},
  // channelgroup C
  .Configdata_C = {0U}
  };

uz_temperaturecard_t* initialize_temperature_card_d4(void){
       return (uz_temperaturecard_init(config_temperature_card));
}
