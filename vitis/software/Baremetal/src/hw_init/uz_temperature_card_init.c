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
  .Configdata_A = {0U},
  .Configdata_A[0]  = 0U,
  .Configdata_A[1]  = SENSOR_TYPE__SENSE_RESISTOR | SENSE_RESISTOR_VALUE_1k,
  .Configdata_A[2]  = 0U,
  .Configdata_A[3]  = 0U,
  .Configdata_A[4]  = 0U,
  .Configdata_A[5]  = 0U,
  .Configdata_A[6]  = 0U,
  .Configdata_A[7]  = 0U,
  .Configdata_A[8]  = 0U,
  .Configdata_A[9]  = 0U,
  .Configdata_A[10]  = 0U,
  .Configdata_A[11] = 0U,
  .Configdata_A[12]  = 0U,
  .Configdata_A[13] = 0U,
  .Configdata_A[14]  = 0U,
  .Configdata_A[15] = 0U,
  .Configdata_A[16]  = 0U,
  .Configdata_A[17] = 0U,
  .Configdata_A[18]  = 0U,
  .Configdata_A[19] = SENSOR_TYPE__RTD_PT_1000 | RTD_RSENSE_CHANNEL__2 | RTD_NUM_WIRES__2_WIRE | RTD_EXCITATION_MODE__NO_ROTATION_SHARING | RTD_EXCITATION_CURRENT__500UA | RTD_STANDARD__EUROPEAN,
  // channelgroup B
  .Configdata_B = {0U},
  // channelgroup C
  .Configdata_C = {0U}
  };

uz_temperaturecard_t* initialize_temperature_card_d3(void){
       return (uz_temperaturecard_init(config_temperature_card));
}
