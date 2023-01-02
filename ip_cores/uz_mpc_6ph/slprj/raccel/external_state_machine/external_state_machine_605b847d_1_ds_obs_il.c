#include "ne_ds.h"
#include "external_state_machine_605b847d_1_ds_obs_il.h"
#include "external_state_machine_605b847d_1_ds_sys_struct.h"
#include "external_state_machine_605b847d_1_ds_externals.h"
#include "external_state_machine_605b847d_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T external_state_machine_605b847d_1_ds_obs_il ( const NeDynamicSystem *
sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { static
boolean_T _cg_const_1 [ 278 ] = { true , true , false , false , true , false
, true , false , true , false , false , true , true , true , false , true ,
false , true , true , true , true , true , true , true , true , true , true ,
true , true , true , true , true , true , true , true , false , false , false
, false , false , true , false , true , true , true , true , true , true ,
true , true , true , true , true , true , true , true , true , true , true ,
true , true , true , true , true , true , true , false , false , false ,
false , false , false , false , false , false , false , false , false , false
, false , false , false , false , false , false , false , false , false ,
false , false , false , false , false , true , false , true , false , true ,
false , false , false , true , false , true , false , true , false , true ,
true , true , false , false , false , true , false , true , false , true ,
false , false , false , true , false , true , false , true , false , true ,
true , true , false , false , false , true , false , true , false , true ,
false , false , false , true , false , true , false , true , false , true ,
true , true , false , false , false , true , false , true , false , true ,
false , false , false , true , false , true , false , true , false , true ,
true , true , false , false , false , true , false , true , false , true ,
false , false , false , true , false , true , false , true , false , true ,
true , true , false , false , false , true , false , true , false , true ,
false , false , false , true , false , true , false , true , false , true ,
true , true , false , false , true , true , true , true , true , true , true
, true , true , true , true , true , true , true , true , true , true , true
, true , true , true , true , true , true , true , true , true , true , true
, true , true , true , true , true , true , true , true , true , true , true
, true , true , true , true , true , true , true , true , true , true , true
, true , true , true , true , true , true , true , true , true , true , true
, true , true , true , true } ; PmBoolVector out ; int32_T b ; boolean_T t0 [
278 ] ; ( void ) t1 ; out = t2 -> mOBS_IL ; for ( b = 0 ; b < 278 ; b ++ ) {
t0 [ b ] = _cg_const_1 [ b ] ; } for ( b = 0 ; b < 278 ; b ++ ) { out . mX [
b ] = t0 [ b ] ; } ( void ) sys ; ( void ) t2 ; return 0 ; }
