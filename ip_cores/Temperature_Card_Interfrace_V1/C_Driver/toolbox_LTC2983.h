#ifndef TOOLBOX_LTC2983_H_INCLUDED
#define TOOLBOX_LTC2983_H_INCLUDED

#define TEMP_CONVERSION_FACTOR 0.000976563
#define CHANNEL_COUNT 20

struct {
	float temperature[CHANNEL_COUNT];
	long temperature_raw[CHANNEL_COUNT];
}LTC2983;

void LTC_initialize_pointer(void * parbankpointer);
void LTC_set_config(void);
void LTC_fetch_values(void);


#endif //TOOLBOX_ADC_H_INCLUDED
