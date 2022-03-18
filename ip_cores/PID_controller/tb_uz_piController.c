#include "uz_piController.h"
#include "uz_signals.h"
#include <stdio.h>
int main(void)
{
	uz_PI_Controller_config config = {0};
	config.Kp = 10.0f;
	config.Ki = 10.0f;
	config.samplingTime_sec = 0.001f;
	config.upper_limit = 10.0f;
	config.lower_limit = -10.0f;
    float referenceValue[4] = {2.54f, 5.0f, -1.45f, -1.23f};
    float actualValue[4] = {1.62f, 6.5f, -3.25f, 2.54f};
    float out;
    printf("testing sample\r\n");
    for(int i=0;i<4;i++){
        uz_PI_Controller_sample(&config,false, referenceValue[i], actualValue[i], false, &out);
        printf("result %f\r\n",out);
    }
}



