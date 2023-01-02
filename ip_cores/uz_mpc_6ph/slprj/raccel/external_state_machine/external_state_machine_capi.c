#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "external_state_machine_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)    
#ifndef SS_INT64
#define SS_INT64  47
#endif
#ifndef SS_UINT64
#define SS_UINT64  48
#endif
#else
#include "builtin_typeid_types.h"
#include "external_state_machine.h"
#include "external_state_machine_capi.h"
#include "external_state_machine_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST                  
#define TARGET_STRING(s)               (NULL)                    
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization" ) , TARGET_STRING
( "result" ) , 0 , 0 , 0 , 0 , 0 } , { 1 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization" ) , TARGET_STRING
( "" ) , 1 , 1 , 0 , 0 , 0 } , { 2 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization" ) , TARGET_STRING
( "" ) , 3 , 1 , 0 , 0 , 0 } , { 3 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization" ) , TARGET_STRING
( "" ) , 5 , 1 , 0 , 0 , 0 } , { 4 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization" ) , TARGET_STRING
( "" ) , 7 , 1 , 0 , 0 , 0 } , { 5 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization" ) , TARGET_STRING
( "" ) , 9 , 1 , 0 , 0 , 0 } , { 6 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization" ) , TARGET_STRING
( "" ) , 11 , 1 , 0 , 0 , 0 } , { 7 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp" ) , TARGET_STRING ( "id_delay"
) , 0 , 2 , 0 , 1 , 0 } , { 8 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp" ) , TARGET_STRING ( "" ) , 1 ,
2 , 0 , 1 , 0 } , { 9 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp" ) , TARGET_STRING ( "" ) , 2 ,
2 , 0 , 1 , 0 } , { 10 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp" ) , TARGET_STRING ( "" ) , 3 ,
2 , 0 , 1 , 0 } , { 11 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp" ) , TARGET_STRING ( "" ) , 8 ,
1 , 0 , 0 , 0 } , { 12 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction" ) , TARGET_STRING ( "" ) , 0 ,
2 , 0 , 1 , 0 } , { 13 , 10 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd" ) , TARGET_STRING ( "" )
, 0 , 2 , 0 , 1 , 0 } , { 14 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation" ) , TARGET_STRING ( "id_pu" )
, 0 , 2 , 0 , 2 , 0 } , { 15 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation" ) , TARGET_STRING ( "iq_pu" )
, 1 , 2 , 0 , 2 , 0 } , { 16 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation" ) , TARGET_STRING ( "" ) , 4
, 2 , 0 , 3 , 0 } , { 17 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation" ) , TARGET_STRING ( "" ) , 5
, 2 , 0 , 3 , 0 } , { 18 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation" ) , TARGET_STRING (
"calc_done" ) , 6 , 1 , 0 , 0 , 0 } , { 19 , 13 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 4 , 0 } , { 20 , 13 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg" ) , TARGET_STRING ( "" ) , 1 , 2 ,
0 , 4 , 0 } , { 21 , 13 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg" ) , TARGET_STRING ( "" ) , 2 , 2 ,
0 , 4 , 0 } , { 22 , 13 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg" ) , TARGET_STRING ( "" ) , 3 , 2 ,
0 , 4 , 0 } , { 23 , 13 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg" ) , TARGET_STRING ( "" ) , 6 , 1 ,
0 , 0 , 0 } , { 24 , 1 , TARGET_STRING (
"external_state_machine/MATLAB Function" ) , TARGET_STRING ( "" ) , 0 , 3 , 1
, 0 , 1 } , { 25 , 1 , TARGET_STRING (
"external_state_machine/MATLAB Function" ) , TARGET_STRING ( "" ) , 1 , 3 , 0
, 0 , 1 } , { 26 , 0 , TARGET_STRING ( "external_state_machine/Constant30" )
, TARGET_STRING ( "" ) , 0 , 3 , 0 , 0 , 0 } , { 27 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion1" ) , TARGET_STRING ( "" ) , 0 ,
1 , 0 , 0 , 1 } , { 28 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion11" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 2 } , { 29 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion12" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 2 } , { 30 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion13" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 2 } , { 31 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion14" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 2 } , { 32 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion15" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 2 } , { 33 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion16" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 2 } , { 34 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion17" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 2 } , { 35 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion18" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 2 } , { 36 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion19" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 2 } , { 37 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion2" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 2 } , { 38 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion20" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 2 } , { 39 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion21" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 2 } , { 40 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion22" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 2 } , { 41 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion23" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 2 } , { 42 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion24" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 2 } , { 43 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion25" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 2 } , { 44 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion26" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 2 } , { 45 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion27" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 2 } , { 46 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion28" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 2 } , { 47 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion29" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 3 } , { 48 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion30" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 3 } , { 49 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion32" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 3 } , { 50 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion33" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 3 } , { 51 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion34" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 3 } , { 52 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion35" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 3 } , { 53 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion36" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 3 } , { 54 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion38" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 3 } , { 55 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion39" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 6 , 0 } , { 56 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion40" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 2 } , { 57 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion54" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 7 , 2 } , { 58 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion55" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 4 , 2 } , { 59 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion56" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 4 , 2 } , { 60 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion57" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 4 , 2 } , { 61 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion58" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 4 , 2 } , { 62 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion59" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 6 , 0 } , { 63 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion60" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 8 , 2 } , { 64 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion61" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 8 , 2 } , { 65 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion62" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 8 , 2 } , { 66 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion63" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 8 , 2 } , { 67 , 0 , TARGET_STRING (
"external_state_machine/Data Type Conversion9" ) , TARGET_STRING ( "" ) , 0 ,
2 , 0 , 6 , 0 } , { 68 , 0 , TARGET_STRING ( "external_state_machine/Gain19"
) , TARGET_STRING ( "" ) , 0 , 3 , 0 , 0 , 4 } , { 69 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition" ) , TARGET_STRING ( "" ) , 0 , 3 , 1
, 0 , 0 } , { 70 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition1" ) , TARGET_STRING ( "volts_done" )
, 0 , 1 , 0 , 0 , 0 } , { 71 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition10" ) , TARGET_STRING ( "" ) , 0 , 1 ,
0 , 0 , 0 } , { 72 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition11" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 0 } , { 73 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition12" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 0 } , { 74 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition13" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 75 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition14" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 76 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition15" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 0 } , { 77 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition16" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 78 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition17" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 79 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition18" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 80 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition19" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 81 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition2" ) , TARGET_STRING ( "delay_done" )
, 0 , 1 , 0 , 0 , 0 } , { 82 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition20" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 83 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition21" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 84 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition22" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 4 , 0 } , { 85 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition23" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 86 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition24" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 1 , 0 } , { 87 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition25" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 88 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition26" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 89 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition27" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 90 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition28" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 1 , 0 } , { 91 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition29" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 92 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition3" ) , TARGET_STRING ( "pred_done" ) ,
0 , 1 , 0 , 0 , 0 } , { 93 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition30" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 94 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition31" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 95 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition32" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 96 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition33" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 97 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition34" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 98 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition35" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 99 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition36" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 100 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition37" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 101 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition38" ) , TARGET_STRING ( "" ) , 0 , 3 ,
0 , 0 , 0 } , { 102 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition39" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 103 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition4" ) , TARGET_STRING ( "opt_done" ) ,
0 , 1 , 0 , 0 , 0 } , { 104 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition40" ) , TARGET_STRING ( "" ) , 0 , 3 ,
0 , 0 , 0 } , { 105 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition41" ) , TARGET_STRING ( "id_measured"
) , 0 , 2 , 0 , 1 , 0 } , { 106 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition42" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 107 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition43" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 108 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition44" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 4 , 0 } , { 109 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition45" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 1 , 0 } , { 110 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition46" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 5 , 0 } , { 111 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition47" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 1 , 0 } , { 112 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition48" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 1 , 0 } , { 113 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition49" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 1 , 0 } , { 114 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition5" ) , TARGET_STRING ( "" ) , 0 , 3 ,
0 , 0 , 0 } , { 115 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition50" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 1 , 0 } , { 116 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition51" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 1 , 0 } , { 117 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition52" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 1 , 0 } , { 118 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition53" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 1 , 0 } , { 119 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition54" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 1 , 0 } , { 120 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition55" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 0 } , { 121 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition56" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 1 , 0 } , { 122 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition57" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 1 , 0 } , { 123 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition58" ) , TARGET_STRING ( "park_done" )
, 0 , 1 , 0 , 0 , 0 } , { 124 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition59" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 1 , 0 } , { 125 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition6" ) , TARGET_STRING ( "" ) , 0 , 1 ,
0 , 0 , 0 } , { 126 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition60" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 1 , 0 } , { 127 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition61" ) , TARGET_STRING ( "" ) , 0 , 3 ,
0 , 0 , 0 } , { 128 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition62" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 7 , 0 } , { 129 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition63" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 4 , 0 } , { 130 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition64" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 4 , 0 } , { 131 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition65" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 4 , 0 } , { 132 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition66" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 4 , 0 } , { 133 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition67" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 1 , 0 } , { 134 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition68" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 0 } , { 135 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition69" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 8 , 0 } , { 136 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition7" ) , TARGET_STRING ( "" ) , 0 , 1 ,
0 , 0 , 0 } , { 137 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition70" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 8 , 0 } , { 138 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition71" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 8 , 0 } , { 139 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition72" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 8 , 0 } , { 140 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition73" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 8 , 0 } , { 141 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition74" ) , TARGET_STRING ( "" ) , 0 , 2 ,
0 , 1 , 0 } , { 142 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition75" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 0 } , { 143 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition76" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 0 } , { 144 , 0 , TARGET_STRING (
"external_state_machine/Rate Transition9" ) , TARGET_STRING ( "opt_done" ) ,
0 , 0 , 0 , 0 , 0 } , { 145 , 0 , TARGET_STRING (
"external_state_machine/Delay1" ) , TARGET_STRING ( "" ) , 0 , 3 , 1 , 0 , 0
} , { 146 , 0 , TARGET_STRING ( "external_state_machine/Delay2" ) ,
TARGET_STRING ( "" ) , 0 , 3 , 0 , 0 , 0 } , { 147 , 0 , TARGET_STRING (
"external_state_machine/Delay3" ) , TARGET_STRING ( "" ) , 0 , 2 , 0 , 4 , 0
} , { 148 , 0 , TARGET_STRING ( "external_state_machine/Delay4" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 4 , 0 } , { 149 , 0 , TARGET_STRING (
"external_state_machine/HDL Counter/Switch_reset" ) , TARGET_STRING ( "" ) ,
0 , 4 , 0 , 0 , 1 } , { 150 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Data Type Conversion66" ) , TARGET_STRING
( "" ) , 0 , 3 , 2 , 0 , 3 } , { 151 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Gain2" ) , TARGET_STRING ( "" ) , 0 , 3 ,
0 , 0 , 3 } , { 152 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Mod" ) , TARGET_STRING ( "" ) , 0 , 3 , 0
, 0 , 3 } , { 153 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Rate Transition67" ) , TARGET_STRING ( ""
) , 0 , 3 , 3 , 0 , 5 } , { 154 , 2 , TARGET_STRING (
"external_state_machine/Subsystem2/Count_f_sw" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 9 , 0 } , { 155 , 0 , TARGET_STRING (
"external_state_machine/Subsystem2/Saturation" ) , TARGET_STRING ( "" ) , 0 ,
4 , 0 , 10 , 0 } , { 156 , 0 , TARGET_STRING (
"external_state_machine/Subsystem2/reset_old_switch1" ) , TARGET_STRING ( ""
) , 0 , 3 , 0 , 0 , 0 } , { 157 , 0 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/AND1" ) , TARGET_STRING ( "" ) , 0
, 1 , 0 , 0 , 0 } , { 158 , 0 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/OR" ) , TARGET_STRING ( "" ) , 0 ,
1 , 0 , 0 , 0 } , { 159 , 0 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Switch1" ) , TARGET_STRING ( "" )
, 0 , 1 , 0 , 0 , 0 } , { 160 , 0 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Switch2" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 0 } , { 161 , 0 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Switch3" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 0 } , { 162 , 0 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Switch4" ) , TARGET_STRING (
"delay_done" ) , 0 , 1 , 0 , 0 , 0 } , { 163 , 0 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Switch5" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 0 } , { 164 , 0 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Switch9" ) , TARGET_STRING ( "" )
, 0 , 1 , 0 , 0 , 0 } , { 165 , 0 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Delay4" ) , TARGET_STRING ( "" ) ,
0 , 1 , 0 , 0 , 0 } , { 166 , 0 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Delay9" ) , TARGET_STRING ( "" ) ,
0 , 1 , 0 , 0 , 0 } , { 167 , 3 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_costs_and_optimization/FiniteControlSetSwitchingTable"
) , TARGET_STRING ( "" ) , 0 , 1 , 4 , 0 , 0 } , { 168 , 4 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/MATLAB Function" )
, TARGET_STRING ( "" ) , 0 , 1 , 5 , 0 , 4 } , { 169 , 4 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/MATLAB Function" )
, TARGET_STRING ( "" ) , 1 , 1 , 5 , 0 , 4 } , { 170 , 5 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/iterativesearch" )
, TARGET_STRING ( "opt_idx" ) , 0 , 0 , 0 , 0 , 0 } , { 171 , 5 ,
TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/iterativesearch" )
, TARGET_STRING ( "" ) , 1 , 0 , 0 , 11 , 0 } , { 172 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Product" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 12 , 0 } , { 173 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Product1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 12 , 0 } , { 174 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Product10" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 12 , 0 } , { 175 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Product11" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 12 , 0 } , { 176 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Product12" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 12 , 0 } , { 177 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Product13" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 11 , 0 } , { 178 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Product14" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 12 , 0 } , { 179 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Product2" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 12 , 0 } , { 180 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Product3" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 12 , 0 } , { 181 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Product4" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 12 , 0 } , { 182 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Product5" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 12 , 0 } , { 183 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Product6" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 12 , 0 } , { 184 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Product7" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 12 , 0 } , { 185 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Product8" ) ,
TARGET_STRING ( "" ) , 0 , 5 , 5 , 0 , 4 } , { 186 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Product9" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 12 , 0 } , { 187 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Relational Operator1"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 188 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Add" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 13 , 0 } , { 189 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Add1" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 13 , 0 } , { 190 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Add2" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 13 , 0 } , { 191 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Add3" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 13 , 0 } , { 192 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Add6" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 11 , 0 } , { 193 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Sum of Elements" )
, TARGET_STRING ( "" ) , 0 , 5 , 0 , 0 , 0 } , { 194 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 12 , 0 } , { 195 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch1" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 1 , 0 } , { 196 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch11" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 197 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch12" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 12 , 0 } , { 198 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch13" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 12 , 0 } , { 199 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch14" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 12 , 0 } , { 200 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch15" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 8 , 0 } , { 201 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch16" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 8 , 0 } , { 202 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch17" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 8 , 0 } , { 203 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch18" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 8 , 0 } , { 204 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch19" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 8 , 0 } , { 205 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch2" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 1 , 0 } , { 206 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch20" ) ,
TARGET_STRING ( "last_opt_idx" ) , 0 , 0 , 0 , 0 , 0 } , { 207 , 6 ,
TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch21" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 3 , 0 , 4 } , { 208 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch3" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 1 , 0 } , { 209 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch4" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 1 , 0 } , { 210 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch5" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 7 , 0 } , { 211 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch6" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 4 , 0 } , { 212 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch7" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 4 , 0 } , { 213 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch8" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 4 , 0 } , { 214 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Switch9" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 4 , 0 } , { 215 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay37" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 3 , 0 , 0 } , { 216 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay38" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 3 , 0 , 0 } , { 217 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay4" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 218 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay50" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 219 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay57" ) ,
TARGET_STRING ( "dU" ) , 0 , 0 , 0 , 11 , 0 } , { 220 , 6 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay58" ) ,
TARGET_STRING ( "" ) , 0 , 5 , 5 , 0 , 0 } , { 221 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Product1" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 222 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Product10" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 223 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Product12" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 224 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Product14" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 225 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Product2" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 226 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Product3" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 2 , 0 } , { 227 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Product4" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 228 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Product6" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 229 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Product7" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 230 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Product8" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 2 , 0 } , { 231 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Product9" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 232 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 1 , 0 } , { 233 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch1" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 1 , 0 } , { 234 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch12" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 235 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch13" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 236 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch14" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 237 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch15" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 238 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch16" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 239 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch17" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 240 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch18" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 241 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch19" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 242 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch2" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 4 , 0 } , { 243 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch21" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 244 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch28" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 1 , 0 } , { 245 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch29" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 1 , 0 } , { 246 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch3" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 4 , 0 } , { 247 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch30" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 1 , 0 } , { 248 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch31" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 1 , 0 } , { 249 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch4" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 1 , 0 } , { 250 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch5" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 5 , 0 } , { 251 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch6" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 1 , 0 } , { 252 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch7" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 1 , 0 } , { 253 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Switch8" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 1 , 0 } , { 254 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay11" ) , TARGET_STRING ( ""
) , 0 , 1 , 0 , 0 , 0 } , { 255 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay14" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 1 , 0 } , { 256 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay15" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 1 , 0 } , { 257 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay16" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 1 , 0 } , { 258 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay17" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 1 , 0 } , { 259 , 7 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay49" ) , TARGET_STRING ( ""
) , 0 , 1 , 0 , 0 , 0 } , { 260 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Product1" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 261 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Product10" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 262 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Product12" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 263 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Product14" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 264 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Product2" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 265 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Product3" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 2 , 0 } , { 266 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Product4" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 267 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Product6" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 268 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Product7" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 269 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Product8" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 2 , 0 } , { 270 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Product9" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 271 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Add1" ) , TARGET_STRING ( "" )
, 0 , 2 , 0 , 1 , 0 } , { 272 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Add3" ) , TARGET_STRING ( "" )
, 0 , 2 , 0 , 1 , 0 } , { 273 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Add5" ) , TARGET_STRING ( "" )
, 0 , 2 , 0 , 1 , 0 } , { 274 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Add7" ) , TARGET_STRING ( "" )
, 0 , 2 , 0 , 1 , 0 } , { 275 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Switch" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 1 , 0 } , { 276 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Switch1" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 1 , 0 } , { 277 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Switch12" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 278 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Switch13" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 279 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Switch14" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 280 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Switch15" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 281 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Switch16" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 282 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Switch17" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 283 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Switch18" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 284 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Switch19" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 5 , 0 } , { 285 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Switch2" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 1 , 0 } , { 286 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Switch21" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 287 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Switch28" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 1 , 0 } , { 288 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Switch29" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 1 , 0 } , { 289 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Switch3" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 1 , 0 } , { 290 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Switch30" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 1 , 0 } , { 291 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Switch31" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 1 , 0 } , { 292 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Switch5" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 5 , 0 } , { 293 , 8 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay14" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 1 , 0 } , { 294 , 9 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/finite_control_set" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 1 , 0 } , { 295 , 9 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/finite_control_set" ) ,
TARGET_STRING ( "" ) , 1 , 2 , 0 , 1 , 0 } , { 296 , 9 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/finite_control_set" ) ,
TARGET_STRING ( "" ) , 2 , 2 , 0 , 1 , 0 } , { 297 , 9 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/finite_control_set" ) ,
TARGET_STRING ( "" ) , 3 , 2 , 0 , 1 , 0 } , { 298 , 10 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Switch" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 0 } , { 299 , 10 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Switch1" ) , TARGET_STRING
( "" ) , 0 , 2 , 0 , 3 , 0 } , { 300 , 10 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Switch2" ) , TARGET_STRING
( "" ) , 0 , 2 , 0 , 3 , 0 } , { 301 , 10 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Switch27" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 5 , 0 } , { 302 , 10 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Switch3" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 0 } , { 303 , 10 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Switch4" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 0 } , { 304 , 10 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Switch5" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 0 } , { 305 , 10 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay7" ) , TARGET_STRING
( "" ) , 0 , 2 , 0 , 1 , 0 } , { 306 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Gain" ) , TARGET_STRING ( "" )
, 0 , 2 , 0 , 3 , 0 } , { 307 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Product" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 6 , 0 } , { 308 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Add" ) , TARGET_STRING ( "" )
, 0 , 2 , 0 , 2 , 0 } , { 309 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Add1" ) , TARGET_STRING ( "" )
, 0 , 2 , 0 , 2 , 0 } , { 310 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Switch" ) , TARGET_STRING (
"u1" ) , 0 , 2 , 0 , 4 , 0 } , { 311 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Switch1" ) , TARGET_STRING (
"u2" ) , 0 , 2 , 0 , 4 , 0 } , { 312 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Switch2" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 6 , 0 } , { 313 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Switch3" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 6 , 0 } , { 314 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Switch4" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 6 , 0 } , { 315 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay13" ) , TARGET_STRING (
"" ) , 0 , 1 , 0 , 0 , 0 } , { 316 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay18" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 3 , 0 } , { 317 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay19" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 3 , 0 } , { 318 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay26" ) , TARGET_STRING (
"" ) , 0 , 1 , 0 , 0 , 0 } , { 319 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay7" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 2 , 0 } , { 320 , 11 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay8" ) , TARGET_STRING ( ""
) , 0 , 2 , 0 , 2 , 0 } , { 321 , 12 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/VSD_6ph_30deg" ) , TARGET_STRING (
"" ) , 0 , 2 , 0 , 4 , 0 } , { 322 , 12 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/VSD_6ph_30deg" ) , TARGET_STRING (
"" ) , 1 , 2 , 0 , 4 , 0 } , { 323 , 12 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/VSD_6ph_30deg" ) , TARGET_STRING (
"" ) , 2 , 2 , 0 , 4 , 0 } , { 324 , 12 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/VSD_6ph_30deg" ) , TARGET_STRING (
"" ) , 3 , 2 , 0 , 4 , 0 } , { 325 , 12 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/VSD_6ph_30deg" ) , TARGET_STRING (
"" ) , 4 , 2 , 0 , 4 , 0 } , { 326 , 12 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/VSD_6ph_30deg" ) , TARGET_STRING (
"" ) , 5 , 2 , 0 , 4 , 0 } , { 327 , 13 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Switch" ) , TARGET_STRING ( "" ) , 0
, 2 , 0 , 5 , 0 } , { 328 , 13 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Switch1" ) , TARGET_STRING ( "" ) ,
0 , 2 , 0 , 5 , 0 } , { 329 , 13 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Switch2" ) , TARGET_STRING ( "" ) ,
0 , 2 , 0 , 5 , 0 } , { 330 , 13 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Switch3" ) , TARGET_STRING ( "" ) ,
0 , 2 , 0 , 5 , 0 } , { 331 , 13 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Switch4" ) , TARGET_STRING ( "" ) ,
0 , 2 , 0 , 5 , 0 } , { 332 , 13 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Switch5" ) , TARGET_STRING ( "" ) ,
0 , 2 , 0 , 5 , 0 } , { 333 , 13 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay13" ) , TARGET_STRING ( "" ) ,
0 , 1 , 0 , 0 , 0 } , { 334 , 13 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay14" ) , TARGET_STRING ( "" ) ,
0 , 2 , 0 , 4 , 0 } , { 335 , 13 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay15" ) , TARGET_STRING ( "" ) ,
0 , 2 , 0 , 4 , 0 } , { 336 , 13 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay16" ) , TARGET_STRING ( "" ) ,
0 , 2 , 0 , 4 , 0 } , { 337 , 13 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay17" ) , TARGET_STRING ( "" ) ,
0 , 2 , 0 , 4 , 0 } , { 338 , 0 , TARGET_STRING (
 "external_state_machine/ctrl_state_machine/Detect Rise Positive/FixPt Relational Operator"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 339 , 0 , TARGET_STRING (
 "external_state_machine/ctrl_state_machine/Detect Rise Positive1/FixPt Relational Operator"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 340 , 0 , TARGET_STRING (
 "external_state_machine/ctrl_state_machine/Detect Rise Positive3/FixPt Relational Operator"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 341 , 0 , TARGET_STRING (
 "external_state_machine/ctrl_state_machine/Detect Rise Positive4/FixPt Relational Operator"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 342 , 0 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/HDL Counter/DT_convert" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 343 , 0 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/HDL Counter/Switch_reset" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 344 , 0 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Subsystem/Switch1" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 345 , 0 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Subsystem2/Switch1" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 346 , 0 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Subsystem4/Switch1" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 347 , 0 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Subsystem7/Switch1" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 348 , 0 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/limited_counter/Add" ) ,
TARGET_STRING ( "" ) , 0 , 4 , 0 , 0 , 0 } , { 349 , 0 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/resetable_counter/Add" ) ,
TARGET_STRING ( "" ) , 0 , 4 , 0 , 0 , 0 } , { 350 , 6 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_costs_and_optimization/Detect Rise Positive/FixPt Relational Operator"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 351 , 7 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_delay_comp/Detect Rise Positive/FixPt Relational Operator"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 352 , 7 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_delay_comp/Detect Rise Positive1/FixPt Relational Operator"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 353 , 8 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_prediction/Detect Rise Positive/FixPt Relational Operator"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 354 , 8 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_prediction/Detect Rise Positive1/FixPt Relational Operator"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 355 , 10 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Detect Rise Positive1/FixPt Relational Operator"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 356 , 11 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Detect Rise Positive/FixPt Relational Operator"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 357 , 13 , TARGET_STRING (
 "external_state_machine/uz_vsd_6ph_30deg/Detect Rise Positive/FixPt Relational Operator"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 358 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Solver Configuration1/EVAL_KEY/INPUT_10_1_1"
) , TARGET_STRING ( "" ) , 0 , 3 , 6 , 0 , 3 } , { 359 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Solver Configuration1/EVAL_KEY/INPUT_11_1_1"
) , TARGET_STRING ( "" ) , 0 , 3 , 6 , 0 , 3 } , { 360 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Solver Configuration1/EVAL_KEY/INPUT_12_1_1"
) , TARGET_STRING ( "" ) , 0 , 3 , 6 , 0 , 3 } , { 361 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Solver Configuration1/EVAL_KEY/INPUT_13_1_1"
) , TARGET_STRING ( "" ) , 0 , 3 , 6 , 0 , 3 } , { 362 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Solver Configuration1/EVAL_KEY/INPUT_14_1_1"
) , TARGET_STRING ( "" ) , 0 , 3 , 6 , 0 , 3 } , { 363 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Solver Configuration1/EVAL_KEY/INPUT_1_1_1"
) , TARGET_STRING ( "" ) , 0 , 3 , 6 , 0 , 3 } , { 364 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Solver Configuration1/EVAL_KEY/INPUT_2_1_1"
) , TARGET_STRING ( "" ) , 0 , 3 , 6 , 0 , 3 } , { 365 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Solver Configuration1/EVAL_KEY/INPUT_3_1_1"
) , TARGET_STRING ( "" ) , 0 , 3 , 6 , 0 , 3 } , { 366 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Solver Configuration1/EVAL_KEY/INPUT_4_1_1"
) , TARGET_STRING ( "" ) , 0 , 3 , 6 , 0 , 3 } , { 367 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Solver Configuration1/EVAL_KEY/INPUT_5_1_1"
) , TARGET_STRING ( "" ) , 0 , 3 , 6 , 0 , 3 } , { 368 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Solver Configuration1/EVAL_KEY/INPUT_6_1_1"
) , TARGET_STRING ( "" ) , 0 , 3 , 6 , 0 , 3 } , { 369 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Solver Configuration1/EVAL_KEY/INPUT_7_1_1"
) , TARGET_STRING ( "" ) , 0 , 3 , 6 , 0 , 3 } , { 370 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Solver Configuration1/EVAL_KEY/INPUT_8_1_1"
) , TARGET_STRING ( "" ) , 0 , 3 , 6 , 0 , 3 } , { 371 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Solver Configuration1/EVAL_KEY/INPUT_9_1_1"
) , TARGET_STRING ( "" ) , 0 , 3 , 6 , 0 , 3 } , { 372 , 0 , TARGET_STRING (
"external_state_machine/Subsystem1/Solver Configuration1/EVAL_KEY/STATE_1" )
, TARGET_STRING ( "" ) , 0 , 3 , 7 , 0 , 3 } , { 373 , 0 , TARGET_STRING (
 "external_state_machine/ctrl_state_machine/Detect Rise Positive/Positive/Compare"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 374 , 0 , TARGET_STRING (
 "external_state_machine/ctrl_state_machine/Detect Rise Positive1/Positive/Compare"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 375 , 0 , TARGET_STRING (
 "external_state_machine/ctrl_state_machine/Detect Rise Positive2/Positive/Compare"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 376 , 0 , TARGET_STRING (
 "external_state_machine/ctrl_state_machine/Detect Rise Positive3/Positive/Compare"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 377 , 0 , TARGET_STRING (
 "external_state_machine/ctrl_state_machine/Detect Rise Positive4/Positive/Compare"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 378 , 6 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_costs_and_optimization/Detect Rise Positive/Positive/Compare"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 379 , 7 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_delay_comp/Detect Rise Positive/Positive/Compare"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 380 , 7 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_delay_comp/Detect Rise Positive1/Positive/Compare"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 381 , 8 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_prediction/Detect Rise Positive/Positive/Compare"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 382 , 8 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_prediction/Detect Rise Positive1/Positive/Compare"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 383 , 10 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Detect Rise Positive/Positive/Compare"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 384 , 10 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Detect Rise Positive1/Positive/Compare"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 385 , 11 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Detect Rise Positive/Positive/Compare"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 386 , 13 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Detect Rise Positive/Positive/Compare"
) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 387 , 11 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/cos_hdl/SignCorrected"
) , TARGET_STRING ( "Cosine" ) , 0 , 2 , 0 , 3 , 0 } , { 388 , 11 ,
TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/sin_hdl/SignCorrected"
) , TARGET_STRING ( "Sine" ) , 0 , 2 , 0 , 3 , 0 } , { 0 , 0 , ( NULL ) , (
NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_BlockParameters
rtBlockParameters [ ] = { { 389 , TARGET_STRING (
"external_state_machine/HDL Counter" ) , TARGET_STRING ( "CountStep" ) , 3 ,
0 , 0 } , { 390 , TARGET_STRING ( "external_state_machine/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 391 , TARGET_STRING (
"external_state_machine/Constant1" ) , TARGET_STRING ( "Value" ) , 3 , 0 , 0
} , { 392 , TARGET_STRING ( "external_state_machine/Constant11" ) ,
TARGET_STRING ( "Value" ) , 3 , 0 , 0 } , { 393 , TARGET_STRING (
"external_state_machine/Constant12" ) , TARGET_STRING ( "Value" ) , 3 , 0 , 0
} , { 394 , TARGET_STRING ( "external_state_machine/Constant13" ) ,
TARGET_STRING ( "Value" ) , 3 , 0 , 0 } , { 395 , TARGET_STRING (
"external_state_machine/Constant2" ) , TARGET_STRING ( "Value" ) , 3 , 0 , 0
} , { 396 , TARGET_STRING ( "external_state_machine/Constant25" ) ,
TARGET_STRING ( "Value" ) , 3 , 0 , 0 } , { 397 , TARGET_STRING (
"external_state_machine/Constant30" ) , TARGET_STRING ( "Value" ) , 3 , 0 , 0
} , { 398 , TARGET_STRING ( "external_state_machine/Constant36" ) ,
TARGET_STRING ( "Value" ) , 3 , 0 , 0 } , { 399 , TARGET_STRING (
"external_state_machine/Constant37" ) , TARGET_STRING ( "Value" ) , 3 , 0 , 0
} , { 400 , TARGET_STRING ( "external_state_machine/Constant38" ) ,
TARGET_STRING ( "Value" ) , 3 , 0 , 0 } , { 401 , TARGET_STRING (
"external_state_machine/Constant39" ) , TARGET_STRING ( "Value" ) , 3 , 0 , 0
} , { 402 , TARGET_STRING ( "external_state_machine/Constant40" ) ,
TARGET_STRING ( "Value" ) , 3 , 0 , 0 } , { 403 , TARGET_STRING (
"external_state_machine/Constant41" ) , TARGET_STRING ( "Value" ) , 3 , 0 , 0
} , { 404 , TARGET_STRING ( "external_state_machine/Constant43" ) ,
TARGET_STRING ( "Value" ) , 3 , 0 , 0 } , { 405 , TARGET_STRING (
"external_state_machine/Constant44" ) , TARGET_STRING ( "Value" ) , 3 , 0 , 0
} , { 406 , TARGET_STRING ( "external_state_machine/Constant45" ) ,
TARGET_STRING ( "Value" ) , 3 , 0 , 0 } , { 407 , TARGET_STRING (
"external_state_machine/Constant46" ) , TARGET_STRING ( "Value" ) , 3 , 0 , 0
} , { 408 , TARGET_STRING ( "external_state_machine/Constant47" ) ,
TARGET_STRING ( "Value" ) , 3 , 0 , 0 } , { 409 , TARGET_STRING (
"external_state_machine/Constant48" ) , TARGET_STRING ( "Value" ) , 3 , 0 , 0
} , { 410 , TARGET_STRING ( "external_state_machine/Constant49" ) ,
TARGET_STRING ( "Value" ) , 3 , 0 , 0 } , { 411 , TARGET_STRING (
"external_state_machine/Constant50" ) , TARGET_STRING ( "Value" ) , 3 , 0 , 0
} , { 412 , TARGET_STRING ( "external_state_machine/Pulse Generator2" ) ,
TARGET_STRING ( "Amplitude" ) , 3 , 0 , 0 } , { 413 , TARGET_STRING (
"external_state_machine/Pulse Generator2" ) , TARGET_STRING ( "Period" ) , 3
, 0 , 0 } , { 414 , TARGET_STRING ( "external_state_machine/Pulse Generator2"
) , TARGET_STRING ( "PulseWidth" ) , 3 , 0 , 0 } , { 415 , TARGET_STRING (
"external_state_machine/Pulse Generator2" ) , TARGET_STRING ( "PhaseDelay" )
, 3 , 0 , 0 } , { 416 , TARGET_STRING ( "external_state_machine/Gain19" ) ,
TARGET_STRING ( "Gain" ) , 3 , 0 , 0 } , { 417 , TARGET_STRING (
"external_state_machine/Rate Transition" ) , TARGET_STRING (
"InitialCondition" ) , 3 , 0 , 0 } , { 418 , TARGET_STRING (
"external_state_machine/Rate Transition10" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 419 , TARGET_STRING (
"external_state_machine/Rate Transition23" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 420 , TARGET_STRING (
"external_state_machine/Rate Transition32" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 421 , TARGET_STRING (
"external_state_machine/Rate Transition33" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 422 , TARGET_STRING (
"external_state_machine/Rate Transition34" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 423 , TARGET_STRING (
"external_state_machine/Rate Transition35" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 424 , TARGET_STRING (
"external_state_machine/Rate Transition36" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 425 , TARGET_STRING (
"external_state_machine/Rate Transition37" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 426 , TARGET_STRING (
"external_state_machine/Rate Transition38" ) , TARGET_STRING (
"InitialCondition" ) , 3 , 0 , 0 } , { 427 , TARGET_STRING (
"external_state_machine/Rate Transition43" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 428 , TARGET_STRING (
"external_state_machine/Rate Transition5" ) , TARGET_STRING (
"InitialCondition" ) , 3 , 0 , 0 } , { 429 , TARGET_STRING (
"external_state_machine/Switch" ) , TARGET_STRING ( "Threshold" ) , 3 , 0 , 0
} , { 430 , TARGET_STRING ( "external_state_machine/Delay" ) , TARGET_STRING
( "InitialCondition" ) , 1 , 0 , 0 } , { 431 , TARGET_STRING (
"external_state_machine/Delay1" ) , TARGET_STRING ( "InitialCondition" ) , 3
, 0 , 0 } , { 432 , TARGET_STRING ( "external_state_machine/Delay2" ) ,
TARGET_STRING ( "InitialCondition" ) , 3 , 0 , 0 } , { 433 , TARGET_STRING (
"external_state_machine/Delay3" ) , TARGET_STRING ( "InitialCondition" ) , 2
, 0 , 4 } , { 434 , TARGET_STRING ( "external_state_machine/Delay4" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 4 } , { 435 , TARGET_STRING (
"external_state_machine/HDL Counter/Constant" ) , TARGET_STRING ( "Value" ) ,
4 , 0 , 0 } , { 436 , TARGET_STRING (
"external_state_machine/HDL Counter/Free_running_or_modulo" ) , TARGET_STRING
( "Value" ) , 1 , 0 , 0 } , { 437 , TARGET_STRING (
"external_state_machine/HDL Counter/From_value" ) , TARGET_STRING ( "Value" )
, 4 , 0 , 0 } , { 438 , TARGET_STRING (
"external_state_machine/HDL Counter/Init_value" ) , TARGET_STRING ( "Value" )
, 4 , 0 , 0 } , { 439 , TARGET_STRING (
"external_state_machine/HDL Counter/Step_value" ) , TARGET_STRING ( "Value" )
, 4 , 0 , 0 } , { 440 , TARGET_STRING (
"external_state_machine/HDL Counter/const_dir" ) , TARGET_STRING ( "Value" )
, 1 , 0 , 0 } , { 441 , TARGET_STRING (
"external_state_machine/HDL Counter/const_load" ) , TARGET_STRING ( "Value" )
, 1 , 0 , 0 } , { 442 , TARGET_STRING (
"external_state_machine/HDL Counter/const_load_val" ) , TARGET_STRING (
"Value" ) , 4 , 0 , 0 } , { 443 , TARGET_STRING (
"external_state_machine/HDL Counter/const_rst" ) , TARGET_STRING ( "Value" )
, 1 , 0 , 0 } , { 444 , TARGET_STRING (
"external_state_machine/HDL Counter/Count_reg" ) , TARGET_STRING (
"InitialCondition" ) , 4 , 0 , 0 } , { 445 , TARGET_STRING (
"external_state_machine/Subsystem1/Constant30" ) , TARGET_STRING ( "Value" )
, 3 , 0 , 0 } , { 446 , TARGET_STRING (
"external_state_machine/Subsystem1/Gain1" ) , TARGET_STRING ( "Gain" ) , 3 ,
0 , 0 } , { 447 , TARGET_STRING ( "external_state_machine/Subsystem1/Gain2" )
, TARGET_STRING ( "Gain" ) , 3 , 0 , 0 } , { 448 , TARGET_STRING (
"external_state_machine/Subsystem2/Saturation" ) , TARGET_STRING (
"UpperLimit" ) , 4 , 0 , 10 } , { 449 , TARGET_STRING (
"external_state_machine/Subsystem2/Saturation" ) , TARGET_STRING (
"LowerLimit" ) , 4 , 0 , 10 } , { 450 , TARGET_STRING (
"external_state_machine/Subsystem2/SS_Old" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 451 , TARGET_STRING (
"external_state_machine/Subsystem2/delay" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 9 } , { 452 , TARGET_STRING (
"external_state_machine/Subsystem2/reset_old2" ) , TARGET_STRING (
"InitialCondition" ) , 3 , 0 , 0 } , { 453 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Detect Rise Positive" ) ,
TARGET_STRING ( "vinit" ) , 1 , 0 , 0 } , { 454 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Detect Rise Positive1" ) ,
TARGET_STRING ( "vinit" ) , 1 , 0 , 0 } , { 455 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Detect Rise Positive2" ) ,
TARGET_STRING ( "vinit" ) , 1 , 0 , 0 } , { 456 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Detect Rise Positive3" ) ,
TARGET_STRING ( "vinit" ) , 1 , 0 , 0 } , { 457 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Detect Rise Positive4" ) ,
TARGET_STRING ( "vinit" ) , 1 , 0 , 0 } , { 458 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/HDL Counter" ) , TARGET_STRING (
"CountStep" ) , 3 , 0 , 0 } , { 459 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Constant4" ) , TARGET_STRING (
"Value" ) , 4 , 0 , 0 } , { 460 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Delay" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 461 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Delay1" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 462 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Delay2" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 463 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Delay21" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 464 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Delay3" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 465 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Delay4" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 466 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Delay5" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 467 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Delay6" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 468 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Delay7" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 469 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Delay8" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 470 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Delay9" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 471 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Detect Rise Positive"
) , TARGET_STRING ( "vinit" ) , 1 , 0 , 0 } , { 472 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/sfix18_En15 max value"
) , TARGET_STRING ( "Value" ) , 2 , 0 , 5 } , { 473 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay" ) ,
TARGET_STRING ( "InitialCondition" ) , 1 , 0 , 0 } , { 474 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay1" ) ,
TARGET_STRING ( "InitialCondition" ) , 1 , 0 , 0 } , { 475 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay10" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 1 } , { 476 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay11" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 7 } , { 477 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay12" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 7 } , { 478 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay14" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 4 } , { 479 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay15" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 4 } , { 480 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay16" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 4 } , { 481 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay17" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 4 } , { 482 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay18" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 4 } , { 483 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay19" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 4 } , { 484 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay2" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 1 } , { 485 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay20" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 4 } , { 486 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay21" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 4 } , { 487 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay23" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 488 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay24" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 489 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay25" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 8 } , { 490 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay26" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 8 } , { 491 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay27" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 8 } , { 492 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay28" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 8 } , { 493 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay29" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 8 } , { 494 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay3" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 1 } , { 495 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay30" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 8 } , { 496 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay31" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 8 } , { 497 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay32" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 8 } , { 498 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay33" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 8 } , { 499 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay34" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 8 } , { 500 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay35" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 11 } , { 501 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay36" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 1 } , { 502 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay37" ) ,
TARGET_STRING ( "InitialCondition" ) , 1 , 0 , 0 } , { 503 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay38" ) ,
TARGET_STRING ( "InitialCondition" ) , 1 , 0 , 0 } , { 504 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay39" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 1 } , { 505 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay4" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 506 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay40" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 1 } , { 507 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay41" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 1 } , { 508 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay42" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 12 } , { 509 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay43" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 12 } , { 510 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay44" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 12 } , { 511 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay45" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 12 } , { 512 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay46" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 13 } , { 513 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay47" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 13 } , { 514 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay48" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 13 } , { 515 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay49" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 13 } , { 516 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay5" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 1 } , { 517 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay50" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 518 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay51" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 7 } , { 519 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay52" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 12 } , { 520 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay53" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 12 } , { 521 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay54" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 12 } , { 522 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay55" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 12 } , { 523 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay56" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 12 } , { 524 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay57" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 11 } , { 525 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay58" ) ,
TARGET_STRING ( "InitialCondition" ) , 5 , 0 , 0 } , { 526 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay59" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 12 } , { 527 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay6" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 1 } , { 528 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay60" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 12 } , { 529 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay61" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 12 } , { 530 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay62" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 12 } , { 531 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay63" ) ,
TARGET_STRING ( "InitialCondition" ) , 5 , 0 , 0 } , { 532 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay64" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 8 } , { 533 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay65" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 8 } , { 534 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay66" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 8 } , { 535 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay67" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 8 } , { 536 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay68" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 8 } , { 537 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay69" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 12 } , { 538 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay7" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 1 } , { 539 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay70" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 12 } , { 540 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay71" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 12 } , { 541 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay72" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 12 } , { 542 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay73" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 543 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay8" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 1 } , { 544 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay9" ) ,
TARGET_STRING ( "InitialCondition" ) , 2 , 0 , 1 } , { 545 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_costs_and_optimization/Delay94" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 11 } , { 546 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Detect Rise Positive" ) ,
TARGET_STRING ( "vinit" ) , 1 , 0 , 0 } , { 547 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Detect Rise Positive1" ) ,
TARGET_STRING ( "vinit" ) , 1 , 0 , 0 } , { 548 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 549 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay1" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 550 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay10" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 551 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay11" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 552 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay12" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 553 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay13" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 554 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay14" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 555 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay15" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 556 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay16" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 557 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay17" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 558 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay18" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 559 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay19" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 560 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay2" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 561 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay20" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 562 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay21" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 563 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay22" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 564 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay23" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 565 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay24" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 566 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay25" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 567 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay26" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 568 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay27" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 569 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay28" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 570 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay29" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 571 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay3" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 572 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay30" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 573 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay31" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 574 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay32" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 575 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay33" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 576 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay34" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 577 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay35" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 578 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay36" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 579 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay37" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 580 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay38" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 581 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay39" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 582 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay4" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 583 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay40" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 584 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay41" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 585 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay42" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 586 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay43" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 587 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay44" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 588 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay45" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 589 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay46" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 2 } , { 590 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay47" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 591 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay48" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 2 } , { 592 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay49" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 593 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay5" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 594 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay50" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 595 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay51" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 596 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay52" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 597 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay53" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 598 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay54" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 599 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay57" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 600 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay58" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 601 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay59" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 602 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay6" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 603 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay60" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 604 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay62" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 605 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay63" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 606 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay64" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 607 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay65" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 608 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay7" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 609 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay70" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 610 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay71" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 611 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay72" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 612 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay73" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 613 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay8" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 614 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_delay_comp/Delay9" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 615 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Detect Rise Positive" ) ,
TARGET_STRING ( "vinit" ) , 1 , 0 , 0 } , { 616 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Detect Rise Positive1" ) ,
TARGET_STRING ( "vinit" ) , 1 , 0 , 0 } , { 617 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 618 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay1" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 619 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay10" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 620 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay11" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 621 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay12" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 622 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay13" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 623 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay14" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 624 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay15" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 625 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay16" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 626 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay17" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 627 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay18" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 628 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay19" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 629 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay2" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 630 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay20" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 631 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay21" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 632 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay22" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 633 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay23" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 634 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay24" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 635 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay25" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 636 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay26" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 637 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay27" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 638 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay28" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 639 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay29" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 640 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay3" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 641 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay30" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 642 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay31" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 643 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay32" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 644 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay33" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 645 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay34" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 646 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay35" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 647 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay36" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 648 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay37" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 649 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay38" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 650 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay39" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 651 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay4" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 652 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay40" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 653 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay41" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 654 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay42" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 655 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay43" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 656 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay44" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 657 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay45" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 658 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay46" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 2 } , { 659 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay47" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 660 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay48" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 2 } , { 661 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay5" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 662 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay50" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 663 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay57" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 664 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay58" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 665 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay59" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 666 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay6" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 667 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay60" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 668 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay62" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 669 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay63" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 670 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay64" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 671 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay65" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 672 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay7" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 673 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay70" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 674 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay71" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 675 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay72" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 676 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay73" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 677 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay8" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 678 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_prediction/Delay9" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 1 } , { 679 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Detect Rise Positive" ) ,
TARGET_STRING ( "vinit" ) , 1 , 0 , 0 } , { 680 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Detect Rise Positive1" ) ,
TARGET_STRING ( "vinit" ) , 1 , 0 , 0 } , { 681 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Switch" ) , TARGET_STRING
( "Threshold" ) , 0 , 0 , 0 } , { 682 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 683 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay1" ) , TARGET_STRING
( "InitialCondition" ) , 1 , 0 , 0 } , { 684 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay10" ) , TARGET_STRING
( "InitialCondition" ) , 2 , 0 , 3 } , { 685 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay11" ) , TARGET_STRING
( "InitialCondition" ) , 2 , 0 , 3 } , { 686 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay12" ) , TARGET_STRING
( "InitialCondition" ) , 0 , 0 , 0 } , { 687 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay13" ) , TARGET_STRING
( "InitialCondition" ) , 0 , 0 , 0 } , { 688 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay14" ) , TARGET_STRING
( "InitialCondition" ) , 0 , 0 , 0 } , { 689 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay15" ) , TARGET_STRING
( "InitialCondition" ) , 0 , 0 , 0 } , { 690 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay16" ) , TARGET_STRING
( "InitialCondition" ) , 0 , 0 , 0 } , { 691 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay17" ) , TARGET_STRING
( "InitialCondition" ) , 2 , 0 , 1 } , { 692 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay18" ) , TARGET_STRING
( "InitialCondition" ) , 2 , 0 , 1 } , { 693 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay19" ) , TARGET_STRING
( "InitialCondition" ) , 2 , 0 , 1 } , { 694 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay2" ) , TARGET_STRING
( "InitialCondition" ) , 2 , 0 , 3 } , { 695 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay20" ) , TARGET_STRING
( "InitialCondition" ) , 2 , 0 , 1 } , { 696 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay21" ) , TARGET_STRING
( "InitialCondition" ) , 1 , 0 , 0 } , { 697 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay3" ) , TARGET_STRING
( "InitialCondition" ) , 2 , 0 , 3 } , { 698 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay4" ) , TARGET_STRING
( "InitialCondition" ) , 2 , 0 , 1 } , { 699 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay5" ) , TARGET_STRING
( "InitialCondition" ) , 2 , 0 , 1 } , { 700 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay56" ) , TARGET_STRING
( "InitialCondition" ) , 2 , 0 , 5 } , { 701 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay6" ) , TARGET_STRING
( "InitialCondition" ) , 2 , 0 , 1 } , { 702 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay7" ) , TARGET_STRING
( "InitialCondition" ) , 2 , 0 , 1 } , { 703 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay8" ) , TARGET_STRING
( "InitialCondition" ) , 0 , 0 , 0 } , { 704 , TARGET_STRING (
"external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Delay9" ) , TARGET_STRING
( "InitialCondition" ) , 2 , 0 , 5 } , { 705 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Detect Rise Positive" ) ,
TARGET_STRING ( "vinit" ) , 1 , 0 , 0 } , { 706 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Gain" ) , TARGET_STRING (
"Gain" ) , 2 , 0 , 14 } , { 707 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 708 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay1" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 709 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay10" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 2 } , { 710 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay11" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 6 } , { 711 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay12" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 6 } , { 712 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay13" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 713 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay14" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 3 } , { 714 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay15" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 6 } , { 715 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay16" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 3 } , { 716 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay17" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 3 } , { 717 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay18" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 3 } , { 718 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay19" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 3 } , { 719 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay2" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 6 } , { 720 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay20" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 6 } , { 721 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay21" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 6 } , { 722 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay22" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 723 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay23" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 724 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay24" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 725 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay25" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 726 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay26" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 727 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay3" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 728 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay4" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 729 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay5" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 730 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay6" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 6 } , { 731 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay7" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 2 } , { 732 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay8" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 2 } , { 733 , TARGET_STRING (
"external_state_machine/uz_park_transformation/Delay9" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 2 } , { 734 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Detect Rise Positive" ) ,
TARGET_STRING ( "vinit" ) , 1 , 0 , 0 } , { 735 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 736 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay1" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 737 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay10" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 738 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay11" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 739 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay12" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 740 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay13" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 741 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay14" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 742 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay15" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 743 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay16" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 744 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay17" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 745 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay18" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 746 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay19" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 747 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay2" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 748 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay20" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 749 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay21" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 750 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay22" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 751 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay23" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 752 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay24" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 753 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay25" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 4 } , { 754 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay3" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 755 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay4" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 756 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay5" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 757 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay6" ) , TARGET_STRING (
"InitialCondition" ) , 1 , 0 , 0 } , { 758 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay7" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 759 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay8" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 760 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Delay9" ) , TARGET_STRING (
"InitialCondition" ) , 2 , 0 , 5 } , { 761 , TARGET_STRING (
"external_state_machine/HDL Counter/Add_wrap/Compare To Constant" ) ,
TARGET_STRING ( "const" ) , 5 , 0 , 15 } , { 762 , TARGET_STRING (
"external_state_machine/HDL Counter/Add_wrap/Mod_value" ) , TARGET_STRING (
"Value" ) , 5 , 0 , 15 } , { 763 , TARGET_STRING (
"external_state_machine/HDL Counter/Add_wrap/Switch_wrap" ) , TARGET_STRING (
"Threshold" ) , 5 , 0 , 15 } , { 764 , TARGET_STRING (
"external_state_machine/HDL Counter/Sub_wrap/Compare To Constant" ) ,
TARGET_STRING ( "const" ) , 6 , 0 , 16 } , { 765 , TARGET_STRING (
"external_state_machine/HDL Counter/Sub_wrap/Mod_value" ) , TARGET_STRING (
"Value" ) , 5 , 0 , 15 } , { 766 , TARGET_STRING (
"external_state_machine/HDL Counter/Sub_wrap/Switch_wrap" ) , TARGET_STRING (
"Threshold" ) , 6 , 0 , 16 } , { 767 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/HDL Counter/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 768 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/HDL Counter/Free_running_or_modulo"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 769 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/HDL Counter/From_value" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 770 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/HDL Counter/Init_value" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 771 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/HDL Counter/Step_value" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 772 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/HDL Counter/const_dir" ) ,
TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 773 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/HDL Counter/const_load" ) ,
TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 774 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/HDL Counter/const_load_val" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 775 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/HDL Counter/Count_reg" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 776 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Subsystem/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 777 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Subsystem/Switch1" ) ,
TARGET_STRING ( "Threshold" ) , 0 , 0 , 0 } , { 778 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Subsystem/Unit Delay" ) ,
TARGET_STRING ( "InitialCondition" ) , 1 , 0 , 0 } , { 779 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Subsystem2/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 780 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Subsystem2/Switch1" ) ,
TARGET_STRING ( "Threshold" ) , 0 , 0 , 0 } , { 781 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Subsystem2/Unit Delay" ) ,
TARGET_STRING ( "InitialCondition" ) , 1 , 0 , 0 } , { 782 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Subsystem4/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 783 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Subsystem4/Switch1" ) ,
TARGET_STRING ( "Threshold" ) , 0 , 0 , 0 } , { 784 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Subsystem4/Unit Delay" ) ,
TARGET_STRING ( "InitialCondition" ) , 1 , 0 , 0 } , { 785 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Subsystem7/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 786 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Subsystem7/Switch1" ) ,
TARGET_STRING ( "Threshold" ) , 0 , 0 , 0 } , { 787 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/Subsystem7/Unit Delay" ) ,
TARGET_STRING ( "InitialCondition" ) , 1 , 0 , 0 } , { 788 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/limited_counter/Constant3" ) ,
TARGET_STRING ( "Value" ) , 4 , 0 , 0 } , { 789 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/limited_counter/Constant5" ) ,
TARGET_STRING ( "Value" ) , 4 , 0 , 0 } , { 790 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/limited_counter/Constant6" ) ,
TARGET_STRING ( "Value" ) , 4 , 0 , 0 } , { 791 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/limited_counter/Delay4" ) ,
TARGET_STRING ( "InitialCondition" ) , 4 , 0 , 0 } , { 792 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/resetable_counter/Constant1" ) ,
TARGET_STRING ( "Value" ) , 4 , 0 , 0 } , { 793 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/resetable_counter/Constant3" ) ,
TARGET_STRING ( "Value" ) , 4 , 0 , 0 } , { 794 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/resetable_counter/Constant5" ) ,
TARGET_STRING ( "Value" ) , 4 , 0 , 0 } , { 795 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/resetable_counter/Constant6" ) ,
TARGET_STRING ( "Value" ) , 4 , 0 , 0 } , { 796 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/resetable_counter/Delay4" ) ,
TARGET_STRING ( "InitialCondition" ) , 4 , 0 , 0 } , { 797 , TARGET_STRING (
 "external_state_machine/ctrl_state_machine/Detect Rise Positive/Positive/Constant"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 798 , TARGET_STRING (
 "external_state_machine/ctrl_state_machine/Detect Rise Positive1/Positive/Constant"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 799 , TARGET_STRING (
 "external_state_machine/ctrl_state_machine/Detect Rise Positive2/Positive/Constant"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 800 , TARGET_STRING (
 "external_state_machine/ctrl_state_machine/Detect Rise Positive3/Positive/Constant"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 801 , TARGET_STRING (
 "external_state_machine/ctrl_state_machine/Detect Rise Positive4/Positive/Constant"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 802 , TARGET_STRING (
 "external_state_machine/ctrl_state_machine/HDL Counter/Add_wrap/Compare To Constant"
) , TARGET_STRING ( "const" ) , 7 , 0 , 17 } , { 803 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/HDL Counter/Add_wrap/Mod_value" )
, TARGET_STRING ( "Value" ) , 7 , 0 , 17 } , { 804 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/HDL Counter/Add_wrap/Switch_wrap"
) , TARGET_STRING ( "Threshold" ) , 7 , 0 , 17 } , { 805 , TARGET_STRING (
 "external_state_machine/ctrl_state_machine/HDL Counter/Sub_wrap/Compare To Constant"
) , TARGET_STRING ( "const" ) , 8 , 0 , 18 } , { 806 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/HDL Counter/Sub_wrap/Mod_value" )
, TARGET_STRING ( "Value" ) , 7 , 0 , 17 } , { 807 , TARGET_STRING (
"external_state_machine/ctrl_state_machine/HDL Counter/Sub_wrap/Switch_wrap"
) , TARGET_STRING ( "Threshold" ) , 8 , 0 , 18 } , { 808 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_costs_and_optimization/Detect Rise Positive/Positive/Constant"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 809 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_delay_comp/Detect Rise Positive/Positive/Constant"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 810 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_delay_comp/Detect Rise Positive1/Positive/Constant"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 811 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_prediction/Detect Rise Positive/Positive/Constant"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 812 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_prediction/Detect Rise Positive1/Positive/Constant"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 813 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Detect Rise Positive/Positive/Constant"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 814 , TARGET_STRING (
 "external_state_machine/uz_6ph_mpc_pu_voltages_vsd/Detect Rise Positive1/Positive/Constant"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 815 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Detect Rise Positive/Positive/Constant"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 816 , TARGET_STRING (
"external_state_machine/uz_vsd_6ph_30deg/Detect Rise Positive/Positive/Constant"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 817 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/cos_hdl/Point25"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 19 } , { 818 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/cos_hdl/Point50"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 19 } , { 819 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/cos_hdl/Point75"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 19 } , { 820 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/cos_hdl/pow2switch"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 821 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/cos_hdl/Look-Up Table"
) , TARGET_STRING ( "Table" ) , 0 , 8 , 20 } , { 822 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/cos_hdl/Look-Up Table"
) , TARGET_STRING ( "BreakpointsForDimension1FirstPoint" ) , 5 , 0 , 21 } , {
823 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/cos_hdl/Look-Up Table"
) , TARGET_STRING ( "BreakpointsForDimension1Spacing" ) , 5 , 0 , 21 } , {
824 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/cos_hdl/Saturation"
) , TARGET_STRING ( "UpperLimit" ) , 5 , 0 , 21 } , { 825 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/cos_hdl/Saturation"
) , TARGET_STRING ( "LowerLimit" ) , 5 , 0 , 21 } , { 826 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/cos_hdl/RAMDelayBalance"
) , TARGET_STRING ( "InitialCondition" ) , 4 , 0 , 0 } , { 827 ,
TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/sin_hdl/Point25"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 19 } , { 828 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/sin_hdl/Point50"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 19 } , { 829 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/sin_hdl/pow2switch"
) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 830 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/sin_hdl/Look-Up Table"
) , TARGET_STRING ( "Table" ) , 0 , 8 , 20 } , { 831 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/sin_hdl/Look-Up Table"
) , TARGET_STRING ( "BreakpointsForDimension1FirstPoint" ) , 5 , 0 , 21 } , {
832 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/sin_hdl/Look-Up Table"
) , TARGET_STRING ( "BreakpointsForDimension1Spacing" ) , 5 , 0 , 21 } , {
833 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/sin_hdl/Saturation"
) , TARGET_STRING ( "UpperLimit" ) , 5 , 0 , 21 } , { 834 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/sin_hdl/Saturation"
) , TARGET_STRING ( "LowerLimit" ) , 5 , 0 , 21 } , { 835 , TARGET_STRING (
 "external_state_machine/uz_park_transformation/Sine HDL Optimized/sincos hdl/sin_hdl/RAMDelayBalance"
) , TARGET_STRING ( "InitialCondition" ) , 1 , 0 , 0 } , { 0 , ( NULL ) , (
NULL ) , 0 , 0 , 0 } } ; static int_T rt_LoggedStateIdxList [ ] = { - 1 } ;
static const rtwCAPI_Signals rtRootInputs [ ] = { { 0 , 0 , ( NULL ) , ( NULL
) , 0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_Signals rtRootOutputs [ ] =
{ { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const
rtwCAPI_ModelParameters rtModelParameters [ ] = { { 836 , TARGET_STRING (
"IB" ) , 3 , 0 , 0 } , { 837 , TARGET_STRING ( "Ld_over_LB" ) , 3 , 0 , 0 } ,
{ 838 , TARGET_STRING ( "Lq_over_LB" ) , 3 , 0 , 0 } , { 839 , TARGET_STRING
( "Rs_over_ZB" ) , 3 , 0 , 0 } , { 840 , TARGET_STRING (
"Ts_times_ZB_over_Ld" ) , 3 , 0 , 0 } , { 841 , TARGET_STRING (
"Ts_times_ZB_over_Lq" ) , 3 , 0 , 0 } , { 842 , TARGET_STRING (
"Ts_times_ZB_over_Lx" ) , 3 , 0 , 0 } , { 843 , TARGET_STRING (
"Ts_times_ZB_over_Ly" ) , 3 , 0 , 0 } , { 844 , TARGET_STRING ( "VB" ) , 3 ,
0 , 0 } , { 845 , TARGET_STRING ( "id_ref" ) , 3 , 0 , 0 } , { 846 ,
TARGET_STRING ( "iq_ref" ) , 3 , 0 , 0 } , { 847 , TARGET_STRING ( "ix_ref" )
, 3 , 0 , 0 } , { 848 , TARGET_STRING ( "iy_ref" ) , 3 , 0 , 0 } , { 849 ,
TARGET_STRING ( "lambda_d" ) , 3 , 0 , 0 } , { 850 , TARGET_STRING (
"lambda_q" ) , 3 , 0 , 0 } , { 851 , TARGET_STRING ( "lambda_u" ) , 3 , 0 , 0
} , { 852 , TARGET_STRING ( "lambda_x" ) , 3 , 0 , 0 } , { 853 ,
TARGET_STRING ( "lambda_y" ) , 3 , 0 , 0 } , { 854 , TARGET_STRING ( "n_rpm"
) , 3 , 0 , 0 } , { 855 , TARGET_STRING ( "omegaB" ) , 3 , 0 , 0 } , { 856 ,
TARGET_STRING ( "omega_m" ) , 3 , 0 , 0 } , { 857 , TARGET_STRING ( "p" ) , 3
, 0 , 0 } , { 858 , TARGET_STRING ( "psi_pm_over_psiB" ) , 3 , 0 , 0 } , {
859 , TARGET_STRING ( "v_dc" ) , 3 , 0 , 0 } , { 0 , ( NULL ) , 0 , 0 , 0 } }
;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . ovneqytvb3 , & rtB . gtwmnrkwjh [
0 ] , ( & rtB . gtwmnrkwjh [ 0 ] + 1 ) , ( & rtB . gtwmnrkwjh [ 0 ] + 2 ) , (
& rtB . gtwmnrkwjh [ 0 ] + 3 ) , ( & rtB . gtwmnrkwjh [ 0 ] + 4 ) , ( & rtB .
gtwmnrkwjh [ 0 ] + 5 ) , & rtB . mb1dausxob , & rtB . m02jkz3erl , & rtB .
b2wveawkxh , & rtB . lbnydus2mk , & rtB . ah2bxq3tfk , & rtB . bptsg3neq1 , &
rtB . gdeqi52c3t , & rtB . nrwwbchbrw , & rtB . gssmxnvfua , & rtB .
am4ducelp3 , & rtB . lhxfwcched , & rtB . o52zy5et4p , & rtB . jralpmdrls , &
rtB . iykbyydmon , & rtB . nporvgpwl5 , & rtB . bd2h1p1dwd , & rtB .
c1qtgfuqip , & rtB . mnewdly4rk [ 0 ] , & rtB . ikiwxh3pr0 , & rtB .
fcozgxup2r , & rtB . mljf2qmgrn , & rtB . jfmanze4hz , & rtB . j1jikgvsbe , &
rtB . kxdt20352r , & rtB . ctvejegmmg , & rtB . loi2dpkdmq , & rtB .
icibs2siak , & rtB . iga5ruvk1d , & rtB . kwcdebbbzm , & rtB . d2ue2amye1 , &
rtB . aqyozdfrvn , & rtB . ogw0jlrsav , & rtB . fgekdgytcl , & rtB .
js1jw0gwoh , & rtB . ow0lbcm3nw , & rtB . g4tjr4rodb , & rtB . ecbinphpys , &
rtB . ark4jw0ol1 , & rtB . j0zjiyvk0f , & rtB . ktdz5w4hac , & rtB .
pkt0kcmmwy , & rtB . i1cv5s0qez , & rtB . b3k1jc2spd , & rtB . oc1bhsd51n , &
rtB . mbfvpiofjh , & rtB . obrkszk0cv , & rtB . dy41bixjgm , & rtB .
d3q00brn3g , & rtB . nbwy3kxczg , & rtB . oomqbqsxdx , & rtB . ntdmohlrsu , &
rtB . iaykrjeium , & rtB . jitz2wpx1e , & rtB . hlquagpjg5 , & rtB .
ezujvliyy2 , & rtB . mtqsyo3cre , & rtB . nt0shde4ft , & rtB . hec3bzzryy , &
rtB . ca0aodvq2z , & rtB . fmsyx2mkyl , & rtB . dkdzjfwmsv , & rtB .
dqp13zkjbj , & rtB . c1dsvyiwhm [ 0 ] , & rtB . moankq0vrm , & rtB .
olsapwr1z4 , & rtB . p4xxqflaz5 , & rtB . m2w3iz3aee , & rtB . csksiawycx , &
rtB . catclpkjvb , & rtB . b04dlpqzmt , & rtB . df5a40typz , & rtB .
biilum20bi , & rtB . es1xmwhqgi , & rtB . kzgxqag1v5 , & rtB . p2yxu3rxuj , &
rtB . n5nlogcsom , & rtB . agynjzlh54 , & rtB . mtzx4xvlax , & rtB .
nmkdcrt0qx , & rtB . ptih1c04wn , & rtB . ih5jd5n4ln , & rtB . jqgatvc5ch , &
rtB . dds5fk25sg , & rtB . n1grg5qbak , & rtB . dastx34d4p , & rtB .
ojitybxqj0 , & rtB . cvmrh4mo4a , & rtB . nursxirg3t , & rtB . bnkb2z4ycm , &
rtB . oxqakuykpz , & rtB . c4z2wnbs4r , & rtB . if42drdoar , & rtB .
ldbpssyze0 , & rtB . bwcpigp5ap , & rtB . bghjerrr0e , & rtB . pr325ipqz2 , &
rtB . bt2grerp03 , & rtB . dp4jpvrmv3 , & rtB . n2vhiuxqrd , & rtB .
a45zgfroe3 , & rtB . imof4oqoms , & rtB . pslktcu2l4 , & rtB . bcnxdxqltu , &
rtB . b5jzoasf2i , & rtB . bb5t3ibe0p , & rtB . mxlokkcfhc , & rtB .
dyj5bgbcuc , & rtB . ihxw3fzoje , & rtB . nwjbxd5r0c , & rtB . iiaud3znpo , &
rtB . nysw21g0bp , & rtB . i2hx5d4jqp , & rtB . bpxzqnm4l3 , & rtB .
e1seijo30z , & rtB . brzsggcuou , & rtB . awb2jvsx2b , & rtB . lo0tdpg4mu , &
rtB . fuouordfgu , & rtB . nmc2xljzas , & rtB . djnlln1rt3 , & rtB .
lp2l32tgao , & rtB . pql34arxv5 , & rtB . cshwcojbkl , & rtB . bz5z1h3w5l , &
rtB . avqujsxhbp , & rtB . emojjx24as , & rtB . i2mvlkkrve , & rtB .
k3rwb1nqzz , & rtB . lffhrtss2z , & rtB . dzkyf1yhey , & rtB . aef0nmtmyw , &
rtB . bwt2ta3y4t , & rtB . ijz2qzhhuv , & rtB . ebml2kyo2g , & rtB .
h5u0rntcrt , & rtB . iqah1i2pca , & rtB . cvltirj1q3 , & rtB . cpaefdqklz , &
rtB . lmkwkw2lhs [ 0 ] , & rtB . kgu2nomxi3 , & rtB . mjaavthri3 , & rtB .
lgs4fxnwq4 , & rtB . dybu4alcby , & rtB . hs3rg4x4ij [ 0 ] , & rtB .
coilnsyskm , & rtB . fydkgnnnmt , & rtB . p3mop3zcfx [ 0 ] , & rtB .
h0sxejbfrf , & rtB . cqzet413xp , & rtB . hrkx0npxpj , & rtB . icer2di2hv , &
rtB . a4e5d4dld3 , & rtB . lnykytlnzs , & rtB . kgid2mdewr , & rtB .
ifqle4ujtr , & rtB . eqmn14zfna , & rtB . ggywohjzma , & rtB . jgei5mlpwd , &
rtB . jwzsfkd1v0 , & rtB . od0dkd0ufc , & rtB . figchqmbtq [ 0 ] , & rtB .
j0okylvykn [ 0 ] , & rtB . a0h3ocewhn [ 0 ] , & rtB . lyfo12bhlu , & rtB .
cposlljum2 , & rtB . lxudeufh1d , & rtB . akztohrenr , & rtB . cgb3qjmnm1 , &
rtB . m3fqdyqaq0 , & rtB . dcv0qoidsm , & rtB . jijwjr1aep , & rtB .
plsxbe2rwl , & rtB . brxbx3aefy , & rtB . jrwqq01e0j , & rtB . kvgqqefxxk , &
rtB . jfag3ljpz2 , & rtB . m4sshnlbnd , & rtB . f5vvqvlmdf , & rtB .
mh05k33kvh [ 0 ] , & rtB . cxwqwlgqc4 , & rtB . cwxbyautnv , & rtB .
ci4qtrfbmi , & rtB . askifyoshw , & rtB . cg2pnptrpr , & rtB . aajgiijj3s , &
rtB . lckc244i1e , & rtB . mhzb0kyqbm , & rtB . e2cucg45wx , & rtB .
otw0xeijil , & rtB . fsht3xlhlm , & rtB . avpwddkess , & rtB . hwynjfgmpa , &
rtB . j53pgmxfiw , & rtB . gwflnfyd3y , & rtB . l0ihtrjlj1 , & rtB .
aioy1sakev , & rtB . gg3t0vmeel , & rtB . gdwi5f1bbu , & rtB . crbyngd1fp , &
rtB . f4vkxxvqv1 , & rtB . jmghpd1ccq [ 0 ] , & rtB . erx2bhl3a2 , & rtB .
fs5cilycmk , & rtB . aiyagoteaz , & rtB . cjk0kj5ilh , & rtB . d1yvyet12z , &
rtB . fbuev32gxu , & rtB . kvqdejhsfd , & rtB . ju33m4cdrm [ 0 ] , & rtB .
gtwmnrkwjh [ 0 ] , & rtB . ovneqytvb3 , & rtB . k5oalu5yu0 , & rtB .
lqon1cuusl , & rtB . abmmtw4kju [ 0 ] , & rtB . ilhom1roft , & rtB .
o1nheal4dl , & rtB . ldtzknqryt , & rtB . l40jsbi33q , & rtB . gkbeex3aov , &
rtB . fgyfte5o4r , & rtB . pxism14cfu , & rtB . otjtab4rn1 , & rtB .
g1idrksute , & rtB . kokmmzmj5h , & rtB . djtjkyc3yb , & rtB . atmzkwoefg , &
rtB . pdklgdrtks , & rtB . cqnfwarygo , & rtB . erfdu1ogpt , & rtB .
dxhgfbvkpv , & rtB . ae3nlgfi0l , & rtB . g4sstpqgr1 , & rtB . lb2a0b0xi1 , &
rtB . egxt2dwnsf , & rtB . ank1auk353 , & rtB . lcy00sgc1j , & rtB .
pycin0ogk2 , & rtB . a1mkbd21bt , & rtB . eozaupyiiy , & rtB . lrabwpf3mg , &
rtB . dxma5mr1lx , & rtB . ladqh1l1ay , & rtB . cym20fugcb , & rtB .
as3hkfei2t , & rtB . nthdrri3s0 , & rtB . a2351vndi4 , & rtB . kvgxa5awww , &
rtB . ah2bxq3tfk , & rtB . mb1dausxob , & rtB . m02jkz3erl , & rtB .
b2wveawkxh , & rtB . lbnydus2mk , & rtB . cilyi3ulpf , & rtB . kjitpnmckx , &
rtB . jfynefzxod , & rtB . klau3bhcok , & rtB . iw2bemw1sc , & rtB .
ecqkpipjds , & rtB . ji4elq5u20 , & rtB . dugaktvjly , & rtB . gcovqfjvjy , &
rtB . chqj5hplsb , & rtB . cf2gbuvld4 , & rtB . mrc40d2oaq , & rtB .
dzpm51udig , & rtB . b3a00fi0lk , & rtB . kpt5p5oivq , & rtB . ezwccynacw , &
rtB . mucr14b03d , & rtB . gu53noaj33 , & rtB . gw4aeghx5n , & rtB .
k2w1rqjksr , & rtB . f3x3ayd3vh , & rtB . a1csjnflft , & rtB . lcnsuqiqav , &
rtB . eqsz3uj5cb , & rtB . ai05mevrg4 , & rtB . cfzlg02rpx , & rtB .
iv3zvpc4hj , & rtB . hc43hyjorn , & rtB . g1xkscgfyp , & rtB . nwlyfnjpph , &
rtB . ltkwgay4se , & rtB . by5z1sdg50 , & rtB . pvifqhny22 , & rtB .
mm5qjw1ml3 , & rtB . bptsg3neq1 , & rtB . jdjvvy4qkx , & rtB . nt5gslipee , &
rtB . fj24gr35mh , & rtB . drn44sdqme , & rtB . ae4vubc5b1 , & rtB .
n44tlwb0da , & rtB . nxoknrq2e3 , & rtB . nqmjim4gch , & rtB . aazbfhr2ut , &
rtB . dz3wnztbfs , & rtB . ff5hmeglkf , & rtB . gdeqi52c3t , & rtB .
dddfdi4ui2 , & rtB . gmmx5idrtv , & rtB . jmpbc3xkzj , & rtB . aox4zs4akc , &
rtB . kvkl30wy5k , & rtB . b42v5ih2op , & rtB . a2yzlhimua , & rtB .
fbvmghhwrb , & rtB . enzloc2m4v , & rtB . o52zy5et4p , & rtB . am4ducelp3 , &
rtB . lhxfwcched , & rtB . oidxdtv5az , & rtB . nrwwbchbrw , & rtB .
gssmxnvfua , & rtB . blfvxdt1an , & rtB . m2gcavesop , & rtB . nkpmpn3xav , &
rtB . ohixx01idi , & rtB . hp4mdxny0h , & rtB . l2ps0onw3e , & rtB .
b51fi2l4e5 , & rtB . eymox4nbbw , & rtB . ogo4agvx4m , & rtB . dmllkyn2lu , &
rtB . dsob5gptyg , & rtB . ikf05abn4x , & rtB . c1qtgfuqip , & rtB .
jralpmdrls , & rtB . iykbyydmon , & rtB . nporvgpwl5 , & rtB . bd2h1p1dwd , &
rtB . kpjhx4ulbx , & rtB . hzvrhcluwq , & rtB . dhfjsgln1r , & rtB .
pbs13vjlcq , & rtB . clw5wzlj5g , & rtB . he2mr2rcnd , & rtB . d4ao3nqx04 , &
rtB . nazisikh4e , & rtB . l1y4ubxzp4 , & rtB . aod5ud5rjm , & rtB .
ie4ievmzf2 , & rtB . du0yxgyaqq , & rtB . n5zujmxxlk , & rtB . enr0e4zgln , &
rtB . bfl4myxuyy , & rtB . nsawlq2dr0 , & rtB . nfdfoxbx1p , & rtB .
aifqhbnefh , & rtB . k2mr5pqns3 , & rtB . mzofnr1feg , & rtB . hchz4qh53z [ 0
] , & rtB . pmg1smq0gc [ 0 ] , & rtB . dp1kyta3vn [ 0 ] , & rtB . jugjyagxhv
[ 0 ] , & rtB . jykmlqtkrp [ 0 ] , & rtB . kkvwllx1gm [ 0 ] , & rtB .
lvlyzea3mc [ 0 ] , & rtB . pjjqylgrq1 [ 0 ] , & rtB . dcri1qgabh [ 0 ] , &
rtB . iui5f4c211 [ 0 ] , & rtB . ofh24d2eaz [ 0 ] , & rtB . obyantfxn4 [ 0 ]
, & rtB . moi15iwh0h [ 0 ] , & rtB . p25clet1cn [ 0 ] , & rtB . dqinqamfi1 [
0 ] , & rtB . b3b4mzzxo5 , & rtB . hgpvoewzdj , & rtB . dnri1ykhvw , & rtB .
ltwz301alb , & rtB . lncdbextut , & rtB . mtim2c0h5d , & rtB . piyxjz1ppc , &
rtB . gkgzqppshb , & rtB . gzgid3ewbc , & rtB . jr4adxnn11 , & rtB .
plgbvxdc4e , & rtB . c2nvlokfal , & rtB . cwpwdtuvmh , & rtB . eg2janikev , &
rtB . eggdor1wld , & rtB . iczjnwpnj2 , & rtP . HDLCounter_CountStep , & rtP
. Constant_Value , & rtP . Constant1_Value , & rtP . Constant11_Value , & rtP
. Constant12_Value , & rtP . Constant13_Value , & rtP . Constant2_Value , &
rtP . Constant25_Value , & rtP . Constant30_Value , & rtP . Constant36_Value
, & rtP . Constant37_Value , & rtP . Constant38_Value , & rtP .
Constant39_Value , & rtP . Constant40_Value , & rtP . Constant41_Value , &
rtP . Constant43_Value , & rtP . Constant44_Value , & rtP . Constant45_Value
, & rtP . Constant46_Value , & rtP . Constant47_Value , & rtP .
Constant48_Value , & rtP . Constant49_Value , & rtP . Constant50_Value , &
rtP . PulseGenerator2_Amp , & rtP . PulseGenerator2_Period , & rtP .
PulseGenerator2_Duty , & rtP . PulseGenerator2_PhaseDelay , & rtP .
Gain19_Gain , & rtP . RateTransition_InitialCondition , & rtP .
RateTransition10_InitialCondition , & rtP . RateTransition23_InitialCondition
, & rtP . RateTransition32_InitialCondition , & rtP .
RateTransition33_InitialCondition , & rtP . RateTransition34_InitialCondition
, & rtP . RateTransition35_InitialCondition , & rtP .
RateTransition36_InitialCondition , & rtP . RateTransition37_InitialCondition
, & rtP . RateTransition38_InitialCondition , & rtP .
RateTransition43_InitialCondition , & rtP . RateTransition5_InitialCondition
, & rtP . Switch_Threshold , & rtP . Delay_InitialCondition_mgy5b5rjgy , &
rtP . Delay1_InitialCondition , & rtP . Delay2_InitialCondition , & rtP .
Delay3_InitialCondition , & rtP . Delay4_InitialCondition_j0mtraynb2 , & rtP
. Constant_Value_krezwpdugr , & rtP . Free_running_or_modulo_Value , & rtP .
From_value_Value_mqtm0fsuxq , & rtP . Init_value_Value_dhwjsos3in , & rtP .
Step_value_Value_bryryaclem , & rtP . const_dir_Value , & rtP .
const_load_Value , & rtP . const_load_val_Value_b0tcqrjnzj , & rtP .
const_rst_Value , & rtP . Count_reg_InitialCondition_asueyru4ot , & rtP .
Constant30_Value_prnuyl4z0d , & rtP . Gain1_Gain , & rtP . Gain2_Gain , & rtP
. Saturation_UpperSat_nhlfqmn4x4 , & rtP . Saturation_LowerSat_cyyxxqbhoa , &
rtP . SS_Old_InitialCondition , & rtP . delay_InitialCondition , & rtP .
reset_old2_InitialCondition , & rtP . DetectRisePositive_vinit_ib22cc4q3r , &
rtP . DetectRisePositive1_vinit_gbiji02hsl , & rtP .
DetectRisePositive2_vinit , & rtP . DetectRisePositive3_vinit , & rtP .
DetectRisePositive4_vinit , & rtP . HDLCounter_CountStep_jkdercy3f0 , & rtP .
Constant4_Value , & rtP . Delay_InitialCondition_arimfvovwm , & rtP .
Delay1_InitialCondition_dpy3sexlsr , & rtP .
Delay2_InitialCondition_mqwne0yfzv , & rtP .
Delay21_InitialCondition_pzx2rrfnsh , & rtP .
Delay3_InitialCondition_kt0ior3g52 , & rtP .
Delay4_InitialCondition_ehuroqp43u , & rtP .
Delay5_InitialCondition_iro1ml0o4b , & rtP .
Delay6_InitialCondition_c31jqcw5pd , & rtP .
Delay7_InitialCondition_dqlbrwosli , & rtP .
Delay8_InitialCondition_hbbfrekxgi , & rtP .
Delay9_InitialCondition_ff0n2wb02d , & rtP . DetectRisePositive_vinit , & rtP
. sfix18_En15maxvalue_Value , & rtP . Delay_InitialCondition_ayrfgyd5vh , &
rtP . Delay1_InitialCondition_acststv1xc , & rtP .
Delay10_InitialCondition_fncm3u0aqk , & rtP .
Delay11_InitialCondition_aefe120qnx , & rtP .
Delay12_InitialCondition_iyuzeo4mp3 , & rtP . Delay14_InitialCondition , &
rtP . Delay15_InitialCondition , & rtP . Delay16_InitialCondition , & rtP .
Delay17_InitialCondition , & rtP . Delay18_InitialCondition , & rtP .
Delay19_InitialCondition , & rtP . Delay2_InitialCondition_lcgjnepw1h , & rtP
. Delay20_InitialCondition , & rtP . Delay21_InitialCondition , & rtP .
Delay23_InitialCondition_op2l2kezcw , & rtP .
Delay24_InitialCondition_p14sgx14xm , & rtP .
Delay25_InitialCondition_f02epsp2gx , & rtP .
Delay26_InitialCondition_io0pemxg3l , & rtP .
Delay27_InitialCondition_eimdrnj4fl , & rtP .
Delay28_InitialCondition_px5icuhcg5 , & rtP .
Delay29_InitialCondition_glmi4lltd2 , & rtP .
Delay3_InitialCondition_pugikzolzj , & rtP .
Delay30_InitialCondition_ofnmyt0tby , & rtP .
Delay31_InitialCondition_pmkvgjaz2l , & rtP .
Delay32_InitialCondition_f5wtxt21ad , & rtP .
Delay33_InitialCondition_oi2vbhmnab , & rtP .
Delay34_InitialCondition_bhvxb4sani , & rtP .
Delay35_InitialCondition_g0vgtma3kl , & rtP .
Delay36_InitialCondition_pw5b5tbf3k , & rtP .
Delay37_InitialCondition_o4l3n4g21g , & rtP .
Delay38_InitialCondition_fjlfddcmxf , & rtP .
Delay39_InitialCondition_pla21bbxiw , & rtP .
Delay4_InitialCondition_bnp5uh2nbr , & rtP .
Delay40_InitialCondition_muusj1w2jz , & rtP . Delay41_InitialCondition , &
rtP . Delay42_InitialCondition_moexjyifg4 , & rtP . Delay43_InitialCondition
, & rtP . Delay44_InitialCondition , & rtP .
Delay45_InitialCondition_aaata0dpq2 , & rtP .
Delay46_InitialCondition_hp1tgavvdq , & rtP .
Delay47_InitialCondition_ij0jcy2nr2 , & rtP .
Delay48_InitialCondition_f1f5dsuuw2 , & rtP . Delay49_InitialCondition , &
rtP . Delay5_InitialCondition_earayqbybk , & rtP . Delay50_InitialCondition ,
& rtP . Delay51_InitialCondition_myx3xoza4z , & rtP .
Delay52_InitialCondition_hccf1x1wju , & rtP .
Delay53_InitialCondition_ejnujgvjuc , & rtP .
Delay54_InitialCondition_gsztafuagp , & rtP . Delay55_InitialCondition , &
rtP . Delay56_InitialCondition_bt1dah4zxx , & rtP .
Delay57_InitialCondition_l0nrhq2swb , & rtP .
Delay58_InitialCondition_luxfkrhdi3 , & rtP .
Delay59_InitialCondition_aefql4ojpq , & rtP .
Delay6_InitialCondition_kamhzwpi4u , & rtP .
Delay60_InitialCondition_mlmhnwovs5 , & rtP . Delay61_InitialCondition , &
rtP . Delay62_InitialCondition_guxfhxoq5j , & rtP .
Delay63_InitialCondition_e4x3dh2sou , & rtP .
Delay64_InitialCondition_miacangvo0 , & rtP .
Delay65_InitialCondition_kjdhdv3njw , & rtP . Delay66_InitialCondition , &
rtP . Delay67_InitialCondition , & rtP . Delay68_InitialCondition , & rtP .
Delay69_InitialCondition , & rtP . Delay7_InitialCondition_cmnkpdmjvh , & rtP
. Delay70_InitialCondition_fvi5gvi3z2 , & rtP .
Delay71_InitialCondition_dp0cjzqycn , & rtP .
Delay72_InitialCondition_exjymra1sd , & rtP .
Delay73_InitialCondition_cbbkdwlw5h , & rtP .
Delay8_InitialCondition_a21yi54nej , & rtP .
Delay9_InitialCondition_i5y5manjyq , & rtP . Delay94_InitialCondition , & rtP
. DetectRisePositive_vinit_fo4xnhoygk , & rtP . DetectRisePositive1_vinit , &
rtP . Delay_InitialCondition_eem2mixovl , & rtP .
Delay1_InitialCondition_dat0r241xb , & rtP . Delay10_InitialCondition , & rtP
. Delay11_InitialCondition_ehofyfh5ho , & rtP .
Delay12_InitialCondition_dhy1cxosgt , & rtP . Delay13_InitialCondition , &
rtP . Delay14_InitialCondition_bati1r4y0o , & rtP .
Delay15_InitialCondition_noxola40gw , & rtP .
Delay16_InitialCondition_il3shhgxsb , & rtP .
Delay17_InitialCondition_p4m3kzesyj , & rtP .
Delay18_InitialCondition_jntt4dfp5k , & rtP .
Delay19_InitialCondition_mrc5koktnp , & rtP .
Delay2_InitialCondition_mnfmscojm5 , & rtP .
Delay20_InitialCondition_aectgnkorn , & rtP .
Delay21_InitialCondition_mklmlykc1g , & rtP .
Delay22_InitialCondition_pybkr3xzaa , & rtP .
Delay23_InitialCondition_nqh0wedxsh , & rtP .
Delay24_InitialCondition_gf5unztfp3 , & rtP .
Delay25_InitialCondition_ld1wgcfanj , & rtP . Delay26_InitialCondition , &
rtP . Delay27_InitialCondition , & rtP . Delay28_InitialCondition , & rtP .
Delay29_InitialCondition , & rtP . Delay3_InitialCondition_h5j03igjqv , & rtP
. Delay30_InitialCondition , & rtP . Delay31_InitialCondition , & rtP .
Delay32_InitialCondition , & rtP . Delay33_InitialCondition , & rtP .
Delay34_InitialCondition , & rtP . Delay35_InitialCondition , & rtP .
Delay36_InitialCondition , & rtP . Delay37_InitialCondition , & rtP .
Delay38_InitialCondition , & rtP . Delay39_InitialCondition , & rtP .
Delay4_InitialCondition_chzqhro0zz , & rtP . Delay40_InitialCondition , & rtP
. Delay41_InitialCondition_ky0pjf1mvz , & rtP . Delay42_InitialCondition , &
rtP . Delay43_InitialCondition_h2okxsmbyb , & rtP .
Delay44_InitialCondition_hnfu4d5knp , & rtP . Delay45_InitialCondition , &
rtP . Delay46_InitialCondition , & rtP . Delay47_InitialCondition , & rtP .
Delay48_InitialCondition , & rtP . Delay49_InitialCondition_mzyf012msw , &
rtP . Delay5_InitialCondition_o3nqpbca5j , & rtP .
Delay50_InitialCondition_mfmxuzil5a , & rtP . Delay51_InitialCondition , &
rtP . Delay52_InitialCondition , & rtP . Delay53_InitialCondition , & rtP .
Delay54_InitialCondition , & rtP . Delay57_InitialCondition , & rtP .
Delay58_InitialCondition , & rtP . Delay59_InitialCondition , & rtP .
Delay6_InitialCondition , & rtP . Delay60_InitialCondition , & rtP .
Delay62_InitialCondition , & rtP . Delay63_InitialCondition , & rtP .
Delay64_InitialCondition , & rtP . Delay65_InitialCondition , & rtP .
Delay7_InitialCondition , & rtP . Delay70_InitialCondition , & rtP .
Delay71_InitialCondition , & rtP . Delay72_InitialCondition , & rtP .
Delay73_InitialCondition , & rtP . Delay8_InitialCondition , & rtP .
Delay9_InitialCondition , & rtP . DetectRisePositive_vinit_f1y4obgego , & rtP
. DetectRisePositive1_vinit_ivletkhlft , & rtP .
Delay_InitialCondition_mguhinw1z3 , & rtP .
Delay1_InitialCondition_igcycvhe02 , & rtP .
Delay10_InitialCondition_l0q4djyeoi , & rtP .
Delay11_InitialCondition_dpsigb2nh3 , & rtP .
Delay12_InitialCondition_ouc2nmxdsk , & rtP .
Delay13_InitialCondition_kimcfr4gze , & rtP .
Delay14_InitialCondition_jf44sqesxi , & rtP .
Delay15_InitialCondition_lb41cd340o , & rtP .
Delay16_InitialCondition_kxh1ifbnkm , & rtP .
Delay17_InitialCondition_lnkr0kpdkt , & rtP .
Delay18_InitialCondition_pngf4p1bou , & rtP .
Delay19_InitialCondition_indohfis2p , & rtP .
Delay2_InitialCondition_h1aqdsgg2a , & rtP .
Delay20_InitialCondition_o35q2txese , & rtP .
Delay21_InitialCondition_glizedcvzk , & rtP .
Delay22_InitialCondition_oo0fxo4ts3 , & rtP .
Delay23_InitialCondition_puaz0elee4 , & rtP .
Delay24_InitialCondition_mohdww4zbp , & rtP .
Delay25_InitialCondition_gsczwe1i1u , & rtP .
Delay26_InitialCondition_mgka52oerp , & rtP .
Delay27_InitialCondition_m4iln3awwi , & rtP .
Delay28_InitialCondition_cb32osnq0d , & rtP .
Delay29_InitialCondition_mm0khohit1 , & rtP .
Delay3_InitialCondition_ezgpfjbzr1 , & rtP .
Delay30_InitialCondition_ggwlqp3ayv , & rtP .
Delay31_InitialCondition_ekfi3stwf2 , & rtP .
Delay32_InitialCondition_cs5kutlccj , & rtP .
Delay33_InitialCondition_ppr11dhhgn , & rtP .
Delay34_InitialCondition_dpua2hw2gm , & rtP .
Delay35_InitialCondition_dysk2sqtpr , & rtP .
Delay36_InitialCondition_nmclzfgmgt , & rtP .
Delay37_InitialCondition_pvv3oz1agd , & rtP .
Delay38_InitialCondition_hyqujaeun2 , & rtP .
Delay39_InitialCondition_mceniyldyc , & rtP .
Delay4_InitialCondition_mshy1btqrq , & rtP .
Delay40_InitialCondition_ehtobfeh4e , & rtP .
Delay41_InitialCondition_e2e5nal5lm , & rtP .
Delay42_InitialCondition_gru3zset4s , & rtP .
Delay43_InitialCondition_fk3jz0t30i , & rtP .
Delay44_InitialCondition_otecsnu01f , & rtP .
Delay45_InitialCondition_ncb3hew20x , & rtP .
Delay46_InitialCondition_c3h254v0m5 , & rtP .
Delay47_InitialCondition_pbr1n1noet , & rtP .
Delay48_InitialCondition_p4le5tsnjt , & rtP .
Delay5_InitialCondition_lbpw0wn4yz , & rtP .
Delay50_InitialCondition_f4xnk4oved , & rtP .
Delay57_InitialCondition_d0pinoubfq , & rtP .
Delay58_InitialCondition_fqi0cwobbv , & rtP .
Delay59_InitialCondition_bxg5ajl2cg , & rtP .
Delay6_InitialCondition_i4uwjjxy40 , & rtP .
Delay60_InitialCondition_pxiemqggyu , & rtP .
Delay62_InitialCondition_p1wk5q0cdt , & rtP .
Delay63_InitialCondition_beo3flwsuv , & rtP .
Delay64_InitialCondition_ka3tfhhj1f , & rtP .
Delay65_InitialCondition_bmbct3hq2d , & rtP .
Delay7_InitialCondition_duzxicgcbl , & rtP .
Delay70_InitialCondition_p0mpocu54t , & rtP .
Delay71_InitialCondition_cf3uyr12b4 , & rtP .
Delay72_InitialCondition_fhvujjzjmp , & rtP .
Delay73_InitialCondition_obxslsutcn , & rtP .
Delay8_InitialCondition_dwwg2yfgol , & rtP .
Delay9_InitialCondition_nrucrycygo , & rtP .
DetectRisePositive_vinit_dm4ai0zmth , & rtP .
DetectRisePositive1_vinit_bpoqq0kqip , & rtP . Switch_Threshold_lbu3enyq0g ,
& rtP . Delay_InitialCondition_f5wa0qe2ex , & rtP .
Delay1_InitialCondition_kwcvbd3x3q , & rtP .
Delay10_InitialCondition_izlyzkvwk0 , & rtP .
Delay11_InitialCondition_gmmvu1fbcm , & rtP .
Delay12_InitialCondition_gmkk1why2d , & rtP .
Delay13_InitialCondition_m0jqhjefa3 , & rtP .
Delay14_InitialCondition_iptsnmiqcc , & rtP .
Delay15_InitialCondition_nk02qrs4ya , & rtP .
Delay16_InitialCondition_mr40dl0mot , & rtP .
Delay17_InitialCondition_nxouw4fmzy , & rtP .
Delay18_InitialCondition_bxgh5q1rnv , & rtP .
Delay19_InitialCondition_dskcubxram , & rtP .
Delay2_InitialCondition_p3vzpccrzz , & rtP .
Delay20_InitialCondition_a3mgvgzkkd , & rtP .
Delay21_InitialCondition_apznhxher1 , & rtP .
Delay3_InitialCondition_cdk4mpryb2 , & rtP .
Delay4_InitialCondition_fb1eurtbw1 , & rtP .
Delay5_InitialCondition_nuntj3gqhg , & rtP . Delay56_InitialCondition , & rtP
. Delay6_InitialCondition_ajvsfi0dp2 , & rtP .
Delay7_InitialCondition_coynyzjcg4 , & rtP .
Delay8_InitialCondition_h4ihxe4npk , & rtP .
Delay9_InitialCondition_prno1bxsxa , & rtP .
DetectRisePositive_vinit_kkghatpupi , & rtP . Gain_Gain , & rtP .
Delay_InitialCondition , & rtP . Delay1_InitialCondition_ly22xqd5qq , & rtP .
Delay10_InitialCondition_iotuu4egg5 , & rtP . Delay11_InitialCondition , &
rtP . Delay12_InitialCondition , & rtP . Delay13_InitialCondition_etk5iarzoa
, & rtP . Delay14_InitialCondition_bylgo2mpoi , & rtP .
Delay15_InitialCondition_mfiibw15yv , & rtP .
Delay16_InitialCondition_b4fkcf5yn4 , & rtP .
Delay17_InitialCondition_kt3xokvvuu , & rtP .
Delay18_InitialCondition_eqkpnac3um , & rtP .
Delay19_InitialCondition_fkv3s3dp5d , & rtP .
Delay2_InitialCondition_fsrhxdibbo , & rtP .
Delay20_InitialCondition_mbo0wh3jll , & rtP .
Delay21_InitialCondition_ptwc2dagcm , & rtP . Delay22_InitialCondition , &
rtP . Delay23_InitialCondition , & rtP . Delay24_InitialCondition , & rtP .
Delay25_InitialCondition , & rtP . Delay26_InitialCondition_pllnymf2r1 , &
rtP . Delay3_InitialCondition_ezcydfdbof , & rtP . Delay4_InitialCondition ,
& rtP . Delay5_InitialCondition , & rtP . Delay6_InitialCondition_j5vpi3mg4q
, & rtP . Delay7_InitialCondition_pn01ygnqgy , & rtP .
Delay8_InitialCondition_owtbs5ubep , & rtP .
Delay9_InitialCondition_o4ddfnrtdp , & rtP .
DetectRisePositive_vinit_al1piibe1i , & rtP .
Delay_InitialCondition_dnv0ifrubu , & rtP .
Delay1_InitialCondition_c52q2mr0yt , & rtP .
Delay10_InitialCondition_g0wldcu40f , & rtP .
Delay11_InitialCondition_o15pinrfzn , & rtP .
Delay12_InitialCondition_ck3j1elvfp , & rtP .
Delay13_InitialCondition_chiigtws5y , & rtP .
Delay14_InitialCondition_aykb0m4uaj , & rtP .
Delay15_InitialCondition_lijhdzhcao , & rtP .
Delay16_InitialCondition_ea4j2itlpr , & rtP .
Delay17_InitialCondition_eshmddcula , & rtP .
Delay18_InitialCondition_mvcbk0lpqx , & rtP .
Delay19_InitialCondition_ltjalipc0r , & rtP .
Delay2_InitialCondition_euoswkcs5n , & rtP .
Delay20_InitialCondition_ieha2k4so3 , & rtP .
Delay21_InitialCondition_dnukglu4wl , & rtP .
Delay22_InitialCondition_fiqqx4xn4m , & rtP .
Delay23_InitialCondition_mivupfqcav , & rtP .
Delay24_InitialCondition_hptjdovnd3 , & rtP .
Delay25_InitialCondition_jp1hnwtuv1 , & rtP .
Delay3_InitialCondition_pi0tmw14b4 , & rtP .
Delay4_InitialCondition_jeioq1ufui , & rtP .
Delay5_InitialCondition_emgr2bsszy , & rtP .
Delay6_InitialCondition_ombiorxymx , & rtP .
Delay7_InitialCondition_gh5vhp5qht , & rtP .
Delay8_InitialCondition_pmfdfw522x , & rtP .
Delay9_InitialCondition_cyyr0jpkpb , & rtP .
CompareToConstant_const_frsa0cp1w5 , & rtP . Mod_value_Value_l21scu10m2 , &
rtP . Switch_wrap_Threshold_nhu5pffepr , & rtP .
CompareToConstant_const_p3naxlyak2 , & rtP . Mod_value_Value_pbng05kqkk , &
rtP . Switch_wrap_Threshold_izyhb3bebo , & rtP . Constant_Value_lwusvgbjut ,
& rtP . Free_running_or_modulo_Value_la3s00hfhs , & rtP . From_value_Value ,
& rtP . Init_value_Value , & rtP . Step_value_Value , & rtP .
const_dir_Value_i0caynohtg , & rtP . const_load_Value_anfy5khxl2 , & rtP .
const_load_val_Value , & rtP . Count_reg_InitialCondition , & rtP .
Constant1_Value_az5chewn2m , & rtP . Switch1_Threshold_bszl3a5ngz , & rtP .
UnitDelay_InitialCondition_h2pwusbzsi , & rtP . Constant1_Value_ialq4qchdp ,
& rtP . Switch1_Threshold_cmgitpnmj4 , & rtP .
UnitDelay_InitialCondition_lapzeesnb2 , & rtP . Constant1_Value_ehsaxh0cmq ,
& rtP . Switch1_Threshold , & rtP . UnitDelay_InitialCondition , & rtP .
Constant1_Value_ej4utqpdhu , & rtP . Switch1_Threshold_bsiyvpmeeg , & rtP .
UnitDelay_InitialCondition_mm1y0ejde0 , & rtP . Constant3_Value_ivo13icu2r ,
& rtP . Constant5_Value_fqzhn0hxkr , & rtP . Constant6_Value_gdnteqbjb4 , &
rtP . Delay4_InitialCondition_ftztsa1ilo , & rtP . Constant1_Value_oayr5juvkv
, & rtP . Constant3_Value , & rtP . Constant5_Value , & rtP . Constant6_Value
, & rtP . Delay4_InitialCondition_fmraqiik34 , & rtP .
Constant_Value_fe2tuwwksa , & rtP . Constant_Value_kquk2qjynt , & rtP .
Constant_Value_lspkkwit3o , & rtP . Constant_Value_pjgiu3aaeo , & rtP .
Constant_Value_aeu2zpibv2 , & rtP . CompareToConstant_const_lsb3od3rov , &
rtP . Mod_value_Value , & rtP . Switch_wrap_Threshold_er4cjhkfze , & rtP .
CompareToConstant_const , & rtP . Mod_value_Value_grlkw0lqhe , & rtP .
Switch_wrap_Threshold , & rtP . Constant_Value_jjvoona122 , & rtP .
Constant_Value_nwkotzyoei , & rtP . Constant_Value_fxz04fjufv , & rtP .
Constant_Value_p2ftaoinvh , & rtP . Constant_Value_hdyf3gawar , & rtP .
Constant_Value_dmcqaaps25 , & rtP . Constant_Value_pm1sdpisrb , & rtP .
Constant_Value_orbhgrq4vm , & rtP . Constant_Value_aifiy50g10 , & rtP .
Point25_Value , & rtP . Point50_Value , & rtP . Point75_Value , & rtP .
pow2switch_Value , & rtP . LookUpTable_tableData [ 0 ] , & rtP .
LookUpTable_bpFirstPoint01Data , & rtP . LookUpTable_bpSpace01Data , & rtP .
Saturation_UpperSat , & rtP . Saturation_LowerSat , & rtP .
RAMDelayBalance_InitialCondition_bi3be0mmud , & rtP .
Point25_Value_ae3byy1qfp , & rtP . Point50_Value_bq4x5ihc1z , & rtP .
pow2switch_Value_pcaa04qou3 , & rtP . LookUpTable_tableData_l4xsx4sjok [ 0 ]
, & rtP . LookUpTable_bpFirstPoint01Data_bm0k1ty0wi , & rtP .
LookUpTable_bpSpace01Data_jpds1epk12 , & rtP . Saturation_UpperSat_h5014v3u1p
, & rtP . Saturation_LowerSat_otvbogra21 , & rtP .
RAMDelayBalance_InitialCondition , & rtP . IB , & rtP . Ld_over_LB , & rtP .
Lq_over_LB , & rtP . Rs_over_ZB , & rtP . Ts_times_ZB_over_Ld , & rtP .
Ts_times_ZB_over_Lq , & rtP . Ts_times_ZB_over_Lx , & rtP .
Ts_times_ZB_over_Ly , & rtP . VB , & rtP . id_ref , & rtP . iq_ref , & rtP .
ix_ref , & rtP . iy_ref , & rtP . lambda_d , & rtP . lambda_q , & rtP .
lambda_u , & rtP . lambda_x , & rtP . lambda_y , & rtP . n_rpm , & rtP .
omegaB , & rtP . omega_m , & rtP . p , & rtP . psi_pm_over_psiB , & rtP .
v_dc , } ; static int32_T * rtVarDimsAddrMap [ ] = { ( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { {
"unsigned int" , "uint32_T" , 0 , 0 , sizeof ( uint32_T ) , SS_UINT32 , 0 , 0
, 0 } , { "unsigned char" , "boolean_T" , 0 , 0 , sizeof ( boolean_T ) ,
SS_BOOLEAN , 0 , 0 , 0 } , { "int" , "int32_T" , 0 , 0 , sizeof ( int32_T ) ,
SS_INT32 , 0 , 0 , 0 } , { "double" , "real_T" , 0 , 0 , sizeof ( real_T ) ,
SS_DOUBLE , 0 , 0 , 0 } , { "unsigned char" , "uint8_T" , 0 , 0 , sizeof (
uint8_T ) , SS_UINT8 , 0 , 0 , 0 } , { "unsigned short" , "uint16_T" , 0 , 0
, sizeof ( uint16_T ) , SS_UINT16 , 0 , 0 , 0 } , { "short" , "int16_T" , 0 ,
0 , sizeof ( int16_T ) , SS_INT16 , 0 , 0 , 0 } , { "numeric" , "uint64_T" ,
0 , 0 , sizeof ( uint64_T ) , SS_UINT64 , 0 , 0 , 0 } , { "numeric" ,
"int64_T" , 0 , 0 , sizeof ( int64_T ) , SS_INT64 , 0 , 0 , 0 } } ;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 2 , 2 , 0 } , {
rtwCAPI_VECTOR , 4 , 2 , 0 } , { rtwCAPI_VECTOR , 6 , 2 , 0 } , {
rtwCAPI_MATRIX_COL_MAJOR , 8 , 2 , 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 10 , 2
, 0 } , { rtwCAPI_VECTOR , 12 , 2 , 0 } , { rtwCAPI_VECTOR , 14 , 2 , 0 } , {
rtwCAPI_VECTOR , 16 , 2 , 0 } } ; static const uint_T rtDimensionArray [ ] =
{ 1 , 1 , 1 , 12 , 12 , 1 , 6 , 1 , 64 , 12 , 1 , 6 , 4 , 1 , 39 , 1 , 1 ,
256 } ; static const real_T rtcapiStoredFloats [ ] = { 1.0E-8 , 0.0 , 1.0 ,
5.0E-7 , 1.0E-6 , 0.0001 } ; static const rtwCAPI_FixPtMap rtFixPtMap [ ] = {
{ ( NULL ) , ( NULL ) , rtwCAPI_FIX_RESERVED , 0 , 0 , 0 } , { ( const void *
) & rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 27 , - 24 , 1 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 27 , - 16 , 1 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 18 , - 16 , 1 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 18 , - 11 , 1 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 18 , - 15 , 1 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 18 , - 14 , 1 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 18 , - 15 , 0 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 18 , - 17 , 0 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 25 , 0 , 0 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 1 , 0 , 0 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 27 , - 24 , 0 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 27 , - 22 , 0 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 32 , - 24 , 1 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 18 , - 19 , 1 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 9 , 0 , 0 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 9 , 0 , 1 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 33 , 0 , 0 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 33 , 0 , 1 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 18 , - 18 , 0 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 17 , - 16 , 0 } , { ( const void * ) &
rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
rtwCAPI_FIX_UNIFORM_SCALING , 10 , 0 , 0 } } ; static const
rtwCAPI_SampleTimeMap rtSampleTimeMap [ ] = { { ( const void * ) &
rtcapiStoredFloats [ 0 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] , 1 ,
0 } , { ( const void * ) & rtcapiStoredFloats [ 3 ] , ( const void * ) &
rtcapiStoredFloats [ 1 ] , 2 , 0 } , { ( NULL ) , ( NULL ) , 5 , 0 } , { (
const void * ) & rtcapiStoredFloats [ 4 ] , ( const void * ) &
rtcapiStoredFloats [ 1 ] , 3 , 0 } , { ( const void * ) & rtcapiStoredFloats
[ 1 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] , 0 , 0 } , { ( const
void * ) & rtcapiStoredFloats [ 5 ] , ( const void * ) & rtcapiStoredFloats [
1 ] , 4 , 0 } } ; static rtwCAPI_ModelMappingStaticInfo mmiStatic = { {
rtBlockSignals , 389 , rtRootInputs , 0 , rtRootOutputs , 0 } , {
rtBlockParameters , 447 , rtModelParameters , 24 } , { ( NULL ) , 0 } , {
rtDataTypeMap , rtDimensionMap , rtFixPtMap , rtElementMap , rtSampleTimeMap
, rtDimensionArray } , "float" , { 2114018602U , 2314162676U , 1313601420U ,
1160228812U } , ( NULL ) , 0 , 0 , rt_LoggedStateIdxList } ; const
rtwCAPI_ModelMappingStaticInfo * external_state_machine_GetCAPIStaticMap (
void ) { return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void external_state_machine_InitializeDataMapInfo ( void ) {
rtwCAPI_SetVersion ( ( * rt_dataMapInfoPtr ) . mmi , 1 ) ;
rtwCAPI_SetStaticMap ( ( * rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ;
rtwCAPI_SetLoggingStaticMap ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetDataAddressMap ( ( * rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ;
rtwCAPI_SetVarDimsAddressMap ( ( * rt_dataMapInfoPtr ) . mmi ,
rtVarDimsAddrMap ) ; rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr )
. mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi
, ( NULL ) ) ; rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi ,
0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void external_state_machine_host_InitializeDataMapInfo (
external_state_machine_host_DataMapInfo_T * dataMap , const char * path ) {
rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ; rtwCAPI_SetStaticMap ( dataMap ->
mmi , & mmiStatic ) ; rtwCAPI_SetDataAddressMap ( dataMap -> mmi , NULL ) ;
rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , NULL ) ; rtwCAPI_SetPath (
dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap -> mmi , NULL ) ;
rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
