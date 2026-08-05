#include "../include/project_wizard_visualization.h"
#include "../globalData.h"

project_wizard_visualization_data_t project_wizard_visualization_data = {0};

void project_wizard_visualization_update(struct _DS_Data_ *data)
{
    project_wizard_visualization_data.viz_adc_ltc2311_a1_ch0 = data->av.adc_ltc2311_a1_ch0;
    project_wizard_visualization_data.viz_adc_ltc2311_a1_ch1 = data->av.adc_ltc2311_a1_ch1;
    project_wizard_visualization_data.viz_adc_ltc2311_a1_ch2 = data->av.adc_ltc2311_a1_ch2;
    project_wizard_visualization_data.viz_adc_ltc2311_a1_ch3 = data->av.adc_ltc2311_a1_ch3;
    project_wizard_visualization_data.viz_adc_ltc2311_a1_ch4 = data->av.adc_ltc2311_a1_ch4;
    project_wizard_visualization_data.viz_adc_ltc2311_a1_ch5 = data->av.adc_ltc2311_a1_ch5;
    project_wizard_visualization_data.viz_adc_ltc2311_a1_ch6 = data->av.adc_ltc2311_a1_ch6;
    project_wizard_visualization_data.viz_adc_ltc2311_a1_ch7 = data->av.adc_ltc2311_a1_ch7;
}
