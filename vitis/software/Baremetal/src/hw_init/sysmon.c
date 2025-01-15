#include "../include/sysmon.h"

uz_sysmon_ps_t* init_sysmon() {
	return uz_sysmon_ps_init(XPAR_XSYSMONPSU_0_DEVICE_ID);
}
