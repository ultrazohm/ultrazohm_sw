#include "ne_ds.h"
#include "external_state_machine_605b847d_1_ds_mode.h"
#include "external_state_machine_605b847d_1_ds_sys_struct.h"
#include "external_state_machine_605b847d_1_ds_externals.h"
#include "external_state_machine_605b847d_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T external_state_machine_605b847d_1_ds_mode ( const NeDynamicSystem *
sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmIntVector
out ; real_T U_idx_1 ; real_T U_idx_10 ; real_T U_idx_11 ; real_T U_idx_12 ;
real_T U_idx_2 ; real_T U_idx_3 ; real_T U_idx_4 ; real_T U_idx_5 ; real_T
U_idx_6 ; real_T U_idx_7 ; real_T U_idx_8 ; real_T U_idx_9 ; U_idx_1 = t1 ->
mU . mX [ 1 ] ; U_idx_2 = t1 -> mU . mX [ 2 ] ; U_idx_3 = t1 -> mU . mX [ 3 ]
; U_idx_4 = t1 -> mU . mX [ 4 ] ; U_idx_5 = t1 -> mU . mX [ 5 ] ; U_idx_6 =
t1 -> mU . mX [ 6 ] ; U_idx_7 = t1 -> mU . mX [ 7 ] ; U_idx_8 = t1 -> mU . mX
[ 8 ] ; U_idx_9 = t1 -> mU . mX [ 9 ] ; U_idx_10 = t1 -> mU . mX [ 10 ] ;
U_idx_11 = t1 -> mU . mX [ 11 ] ; U_idx_12 = t1 -> mU . mX [ 12 ] ; out = t2
-> mMODE ; out . mX [ 0 ] = ( int32_T ) ( U_idx_7 > 0.7 ) ; out . mX [ 1 ] =
( int32_T ) ( U_idx_9 > 0.7 ) ; out . mX [ 2 ] = ( int32_T ) ( U_idx_6 > 0.7
) ; out . mX [ 3 ] = ( int32_T ) ( U_idx_8 > 0.7 ) ; out . mX [ 4 ] = (
int32_T ) ( U_idx_1 > 0.7 ) ; out . mX [ 5 ] = ( int32_T ) ( U_idx_2 > 0.7 )
; out . mX [ 6 ] = ( int32_T ) ( U_idx_10 > 0.7 ) ; out . mX [ 7 ] = (
int32_T ) ( U_idx_11 > 0.7 ) ; out . mX [ 8 ] = ( int32_T ) ( U_idx_12 > 0.7
) ; out . mX [ 9 ] = ( int32_T ) ( U_idx_3 > 0.7 ) ; out . mX [ 10 ] = (
int32_T ) ( U_idx_4 > 0.7 ) ; out . mX [ 11 ] = ( int32_T ) ( U_idx_5 > 0.7 )
; ( void ) sys ; ( void ) t2 ; return 0 ; }
