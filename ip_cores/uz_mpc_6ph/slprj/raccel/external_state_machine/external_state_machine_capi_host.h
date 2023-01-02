#ifndef RTW_HEADER_external_state_machine_cap_host_h_
#define RTW_HEADER_external_state_machine_cap_host_h_
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap_simtarget.h"
typedef struct { rtwCAPI_ModelMappingInfo mmi ; }
external_state_machine_host_DataMapInfo_T ;
#ifdef __cplusplus
extern "C" {
#endif
void external_state_machine_host_InitializeDataMapInfo (
external_state_machine_host_DataMapInfo_T * dataMap , const char * path ) ;
#ifdef __cplusplus
}
#endif
#endif
#endif
