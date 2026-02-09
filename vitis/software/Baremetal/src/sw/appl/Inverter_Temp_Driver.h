#ifndef INVERTER_TEMP_DRIVER_H
#define INVERTER_TEMP_DRIVER_H
/*********************
 *
 * Includes
 *
 *********************/
#include <stdint.h>
#include <stdbool.h>


/*********************
 *
 * TypeDefs
 *
 *********************/
//typedef struct Inv_SiC_Temp_t Inv_SiC_Temp_t;
typedef struct {
	float T_Sys1_Ph1;
	float T_Sys1_Ph2;
	float T_Sys1_Ph3;
	float T_Sys2_Ph1;
	float T_Sys2_Ph2;
	float T_Sys2_Ph3;
	float T_Sys3_Ph1;
	float T_Sys3_Ph2;
	float T_Sys3_Ph3;
} Inv_SiC_Temp_t;

extern Inv_SiC_Temp_t Inv_SiC_Temp;



/*********************
 *
 * Functions
 *
 *********************/
void inverter_temp_update_values(void);

#endif // INVERTER_TEMP_DRIVER_H
