#include "ne_ds.h"
#include "external_state_machine_605b847d_1_ds_y.h"
#include "external_state_machine_605b847d_1_ds_sys_struct.h"
#include "external_state_machine_605b847d_1_ds_externals.h"
#include "external_state_machine_605b847d_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T external_state_machine_605b847d_1_ds_y ( const NeDynamicSystem * sys
, const NeDynamicSystemInput * t8 , NeDsMethodOutput * t9 ) { PmRealVector
out ; real_T U_idx_0 ; real_T X_idx_1 ; real_T X_idx_11 ; real_T X_idx_12 ;
real_T X_idx_13 ; real_T X_idx_14 ; real_T X_idx_15 ; real_T X_idx_16 ;
real_T X_idx_17 ; real_T X_idx_18 ; real_T X_idx_19 ; real_T X_idx_2 ; real_T
X_idx_20 ; real_T X_idx_21 ; real_T X_idx_22 ; real_T X_idx_23 ; real_T
X_idx_24 ; real_T X_idx_25 ; real_T X_idx_26 ; U_idx_0 = t8 -> mU . mX [ 0 ]
; X_idx_1 = t8 -> mX . mX [ 1 ] ; X_idx_2 = t8 -> mX . mX [ 2 ] ; X_idx_11 =
t8 -> mX . mX [ 11 ] ; X_idx_12 = t8 -> mX . mX [ 12 ] ; X_idx_13 = t8 -> mX
. mX [ 13 ] ; X_idx_14 = t8 -> mX . mX [ 14 ] ; X_idx_15 = t8 -> mX . mX [ 15
] ; X_idx_16 = t8 -> mX . mX [ 16 ] ; X_idx_17 = t8 -> mX . mX [ 17 ] ;
X_idx_18 = t8 -> mX . mX [ 18 ] ; X_idx_19 = t8 -> mX . mX [ 19 ] ; X_idx_20
= t8 -> mX . mX [ 20 ] ; X_idx_21 = t8 -> mX . mX [ 21 ] ; X_idx_22 = t8 ->
mX . mX [ 22 ] ; X_idx_23 = t8 -> mX . mX [ 23 ] ; X_idx_24 = t8 -> mX . mX [
24 ] ; X_idx_25 = t8 -> mX . mX [ 25 ] ; X_idx_26 = t8 -> mX . mX [ 26 ] ;
out = t9 -> mY ; out . mX [ 0 ] = - U_idx_0 / - 1.0 ; out . mX [ 1 ] =
X_idx_2 ; out . mX [ 2 ] = X_idx_1 ; out . mX [ 3 ] = - X_idx_12 / - 1.0 ;
out . mX [ 4 ] = - X_idx_13 / - 1.0 ; out . mX [ 5 ] = - X_idx_14 / - 1.0 ;
out . mX [ 6 ] = - X_idx_15 / - 1.0 ; out . mX [ 7 ] = - X_idx_16 / - 1.0 ;
out . mX [ 8 ] = - X_idx_11 / - 1.0 ; out . mX [ 9 ] = - X_idx_23 + -
X_idx_24 ; out . mX [ 10 ] = X_idx_23 ; out . mX [ 11 ] = X_idx_24 ; out . mX
[ 12 ] = X_idx_25 ; out . mX [ 13 ] = X_idx_26 ; out . mX [ 14 ] = - X_idx_25
+ - X_idx_26 ; out . mX [ 15 ] = ( ( ( ( X_idx_17 + X_idx_18 ) + X_idx_19 ) +
X_idx_20 ) + X_idx_21 ) + X_idx_22 ; ( void ) sys ; ( void ) t9 ; return 0 ;
}
