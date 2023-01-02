#include "ne_ds.h"
#include "external_state_machine_605b847d_1_ds_a.h"
#include "external_state_machine_605b847d_1_ds_sys_struct.h"
#include "external_state_machine_605b847d_1_ds_externals.h"
#include "external_state_machine_605b847d_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T external_state_machine_605b847d_1_ds_a ( const NeDynamicSystem * sys
, const NeDynamicSystemInput * t66 , NeDsMethodOutput * t67 ) { PmRealVector
out ; real_T t0 [ 39 ] ; real_T t2 [ 4 ] ; real_T t60 ; real_T t65 ; size_t
t19 ; ( void ) t66 ; out = t67 -> mA ; t2 [ 0ULL ] = 1.0 ; t2 [ 1ULL ] = -
1.0 ; t2 [ 2ULL ] = 0.99999999999999989 ; t2 [ 3ULL ] = - 1.0 ; t60 = 0.5 ;
t65 = - 0.5 ; t0 [ 0ULL ] = - 0.0 ; t0 [ 1ULL ] = - 1.0 ; for ( t19 = 0ULL ;
t19 < 4ULL ; t19 ++ ) { t0 [ t19 + 2ULL ] = t2 [ t19 ] ; } out . mX [ 0 ] =
t0 [ 0 ] ; out . mX [ 1 ] = t0 [ 1 ] ; out . mX [ 2 ] = t0 [ 2 ] ; out . mX [
3 ] = t0 [ 3 ] ; out . mX [ 4 ] = t0 [ 4 ] ; out . mX [ 5 ] = t0 [ 5 ] ; out
. mX [ 6 ] = 0.57000000000000006 ; out . mX [ 7 ] = 1.0 ; out . mX [ 8 ] =
0.19999999999999998 ; out . mX [ 9 ] = 1.0 ; out . mX [ 10 ] = - 1.0 ; out .
mX [ 11 ] = 0.57000000000000006 ; out . mX [ 12 ] = 1.0 ; out . mX [ 13 ] =
0.57000000000000006 ; out . mX [ 14 ] = 1.0 ; out . mX [ 15 ] = - 1.0 ; out .
mX [ 16 ] = - 1.0E-6 ; out . mX [ 17 ] = - 1.0 ; out . mX [ 18 ] =
0.35087719298245612 ; out . mX [ 19 ] = - 1.0 ; out . mX [ 20 ] = - 0.0 ; out
. mX [ 21 ] = 0.5 ; out . mX [ 22 ] = 0.86599999999999988 ; out . mX [ 23 ] =
0.5 ; out . mX [ 24 ] = - 0.86599999999999988 ; out . mX [ 25 ] =
0.86599999999999988 ; out . mX [ 26 ] = - 0.5 ; out . mX [ 27 ] = -
0.86599999999999988 ; out . mX [ 28 ] = - 0.5 ; out . mX [ 29 ] = - 0.0 ; out
. mX [ 30 ] = 1.0 ; out . mX [ 31 ] = t60 ; out . mX [ 32 ] =
0.28866666666666663 ; out . mX [ 33 ] = t60 ; out . mX [ 34 ] = -
0.28866666666666663 ; out . mX [ 35 ] = 0.28866666666666663 ; out . mX [ 36 ]
= t65 ; out . mX [ 37 ] = - 0.28866666666666663 ; out . mX [ 38 ] = t65 ; (
void ) sys ; ( void ) t67 ; return 0 ; }
