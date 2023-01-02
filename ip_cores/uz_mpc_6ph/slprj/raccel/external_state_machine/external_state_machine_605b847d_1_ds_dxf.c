#include "ne_ds.h"
#include "external_state_machine_605b847d_1_ds_dxf.h"
#include "external_state_machine_605b847d_1_ds_sys_struct.h"
#include "external_state_machine_605b847d_1_ds_externals.h"
#include "external_state_machine_605b847d_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T external_state_machine_605b847d_1_ds_dxf ( const NeDynamicSystem *
sys , const NeDynamicSystemInput * t73 , NeDsMethodOutput * t74 ) {
PmRealVector out ; real_T t14 [ 62 ] ; real_T t18 [ 4 ] ; real_T t19 [ 4 ] ;
real_T t20 [ 4 ] ; real_T t21 [ 4 ] ; real_T t22 [ 4 ] ; real_T t23 [ 4 ] ;
real_T t24 [ 4 ] ; real_T t31 [ 4 ] ; real_T t32 [ 4 ] ; real_T t33 [ 4 ] ;
real_T t34 [ 4 ] ; real_T X_idx_1 ; real_T X_idx_11 ; real_T X_idx_12 ;
real_T X_idx_13 ; real_T X_idx_14 ; real_T X_idx_15 ; real_T X_idx_16 ;
real_T X_idx_23 ; real_T X_idx_24 ; real_T X_idx_25 ; real_T X_idx_26 ;
real_T X_idx_3 ; real_T X_idx_4 ; real_T X_idx_7 ; real_T intermediate_der94
; real_T intermediate_der95 ; real_T intermediate_der96 ; real_T
intermediate_der97 ; real_T intermediate_der98 ; real_T intermediate_der99 ;
real_T intrm_sf_mf_13 ; real_T t0 ; real_T t10 ; real_T t11 ; real_T t12 ;
real_T t13 ; real_T t61 ; real_T t62 ; real_T t63 ; real_T t67 ; real_T t68 ;
real_T t69 ; real_T t8 ; real_T t9 ; size_t t54 ; int32_T M_idx_0 ; int32_T
M_idx_1 ; int32_T M_idx_10 ; int32_T M_idx_11 ; int32_T M_idx_2 ; int32_T
M_idx_3 ; int32_T M_idx_4 ; int32_T M_idx_5 ; int32_T M_idx_6 ; int32_T
M_idx_7 ; int32_T M_idx_8 ; int32_T M_idx_9 ; M_idx_0 = t73 -> mM . mX [ 0 ]
; M_idx_1 = t73 -> mM . mX [ 1 ] ; M_idx_2 = t73 -> mM . mX [ 2 ] ; M_idx_3 =
t73 -> mM . mX [ 3 ] ; M_idx_4 = t73 -> mM . mX [ 4 ] ; M_idx_5 = t73 -> mM .
mX [ 5 ] ; M_idx_6 = t73 -> mM . mX [ 6 ] ; M_idx_7 = t73 -> mM . mX [ 7 ] ;
M_idx_8 = t73 -> mM . mX [ 8 ] ; M_idx_9 = t73 -> mM . mX [ 9 ] ; M_idx_10 =
t73 -> mM . mX [ 10 ] ; M_idx_11 = t73 -> mM . mX [ 11 ] ; X_idx_1 = t73 ->
mX . mX [ 1 ] ; X_idx_3 = t73 -> mX . mX [ 3 ] ; X_idx_4 = t73 -> mX . mX [ 4
] ; X_idx_7 = t73 -> mX . mX [ 7 ] ; X_idx_11 = t73 -> mX . mX [ 11 ] ;
X_idx_12 = t73 -> mX . mX [ 12 ] ; X_idx_13 = t73 -> mX . mX [ 13 ] ;
X_idx_14 = t73 -> mX . mX [ 14 ] ; X_idx_15 = t73 -> mX . mX [ 15 ] ;
X_idx_16 = t73 -> mX . mX [ 16 ] ; X_idx_23 = t73 -> mX . mX [ 23 ] ;
X_idx_24 = t73 -> mX . mX [ 24 ] ; X_idx_25 = t73 -> mX . mX [ 25 ] ;
X_idx_26 = t73 -> mX . mX [ 26 ] ; out = t74 -> mDXF ; t61 = ( X_idx_11 *
0.33333333333333331 + X_idx_12 * 0.33333333333333331 ) + X_idx_13 *
0.33333333333333331 ; intrm_sf_mf_13 = ( X_idx_14 * 0.33333333333333331 +
X_idx_15 * 0.33333333333333331 ) + X_idx_16 * 0.33333333333333331 ; t62 = ( (
X_idx_25 * 0.28866666666666663 + X_idx_23 * - 0.5 ) + X_idx_26 * -
0.28866666666666663 ) + X_idx_24 * - 0.5 ; t63 = ( ( X_idx_25 * 0.5 +
X_idx_23 * 0.28866666666666663 ) + X_idx_26 * 0.5 ) + X_idx_24 * -
0.28866666666666663 ; t0 = X_idx_11 - t61 ; X_idx_26 = X_idx_12 - t61 ;
X_idx_25 = X_idx_13 - t61 ; t61 = X_idx_14 - intrm_sf_mf_13 ; X_idx_24 =
X_idx_15 - intrm_sf_mf_13 ; X_idx_23 = X_idx_16 - intrm_sf_mf_13 ;
intrm_sf_mf_13 = X_idx_7 * 5.0 ; t67 = ( ( ( t0 * 0.33333333333333331 +
X_idx_26 * - 0.16666666666666666 ) + X_idx_25 * - 0.16666666666666666 ) + t61
* 0.28866666666666663 ) + X_idx_24 * - 0.28866666666666663 ; t0 = ( ( (
X_idx_26 * 0.28866666666666663 + X_idx_25 * - 0.28866666666666663 ) + t61 *
0.16666666666666666 ) + X_idx_24 * 0.16666666666666666 ) + X_idx_23 * -
0.33333333333333331 ; X_idx_23 = - 0.16666666666666669 ; X_idx_24 = -
0.16666666666666666 ; X_idx_25 = - 0.28866666666666663 ; X_idx_26 =
0.28866666666666663 ; X_idx_11 = 0.33333333333333337 ; X_idx_12 = 0.0 ;
X_idx_13 = - 0.28866666666666663 ; X_idx_14 = 0.28866666666666663 ; X_idx_15
= 0.16666666666666669 ; X_idx_16 = 0.16666666666666669 ; X_idx_7 = 0.0 ; t61
= - 0.33333333333333337 ; t68 = cos ( intrm_sf_mf_13 ) * X_idx_11 + sin (
intrm_sf_mf_13 ) * X_idx_7 ; t69 = cos ( intrm_sf_mf_13 ) * X_idx_23 + sin (
intrm_sf_mf_13 ) * X_idx_13 ; intermediate_der94 = cos ( intrm_sf_mf_13 ) *
X_idx_26 + sin ( intrm_sf_mf_13 ) * X_idx_16 ; intermediate_der95 = cos (
intrm_sf_mf_13 ) * X_idx_24 + sin ( intrm_sf_mf_13 ) * X_idx_14 ;
intermediate_der96 = cos ( intrm_sf_mf_13 ) * X_idx_25 + sin ( intrm_sf_mf_13
) * X_idx_15 ; intermediate_der97 = cos ( intrm_sf_mf_13 ) * X_idx_12 + sin (
intrm_sf_mf_13 ) * t61 ; intermediate_der98 = - sin ( intrm_sf_mf_13 ) * 5.0
* t67 + cos ( intrm_sf_mf_13 ) * 5.0 * t0 ; intermediate_der99 = - sin (
intrm_sf_mf_13 ) * X_idx_11 + cos ( intrm_sf_mf_13 ) * X_idx_7 ; X_idx_11 = -
sin ( intrm_sf_mf_13 ) * X_idx_23 + cos ( intrm_sf_mf_13 ) * X_idx_13 ;
X_idx_23 = - sin ( intrm_sf_mf_13 ) * X_idx_26 + cos ( intrm_sf_mf_13 ) *
X_idx_16 ; X_idx_26 = - sin ( intrm_sf_mf_13 ) * X_idx_24 + cos (
intrm_sf_mf_13 ) * X_idx_14 ; X_idx_24 = - sin ( intrm_sf_mf_13 ) * X_idx_25
+ cos ( intrm_sf_mf_13 ) * X_idx_15 ; X_idx_25 = - sin ( intrm_sf_mf_13 ) *
X_idx_12 + cos ( intrm_sf_mf_13 ) * t61 ; X_idx_12 = - ( cos ( intrm_sf_mf_13
) * 5.0 ) * t67 + - sin ( intrm_sf_mf_13 ) * 5.0 * t0 ; if ( M_idx_0 != 0 ) {
t0 = - 0.01 ; } else { t0 = - 1.0E+6 ; } if ( M_idx_4 != 0 ) { t67 = - 0.01 ;
} else { t67 = - 1.0E+6 ; } if ( M_idx_6 != 0 ) { X_idx_13 = - 0.01 ; } else
{ X_idx_13 = - 1.0E+6 ; } if ( M_idx_8 != 0 ) { X_idx_14 = - 0.01 ; } else {
X_idx_14 = - 1.0E+6 ; } if ( M_idx_10 != 0 ) { X_idx_15 = - 0.01 ; } else {
X_idx_15 = - 1.0E+6 ; } if ( M_idx_2 != 0 ) { X_idx_16 = - 0.01 ; } else {
X_idx_16 = - 1.0E+6 ; } if ( M_idx_0 != 0 ) { X_idx_7 = 0.01 ; } else {
X_idx_7 = 1.0E+6 ; } if ( M_idx_6 != 0 ) { t61 = - 0.01 ; } else { t61 = -
1.0E+6 ; } if ( M_idx_0 != 0 ) { t8 = 0.01 ; } else { t8 = 1.0E+6 ; } if (
M_idx_8 != 0 ) { t9 = - 0.01 ; } else { t9 = - 1.0E+6 ; } if ( M_idx_4 != 0 )
{ t10 = 0.01 ; } else { t10 = 1.0E+6 ; } if ( M_idx_10 != 0 ) { t11 = - 0.01
; } else { t11 = - 1.0E+6 ; } if ( M_idx_4 != 0 ) { t12 = 0.01 ; } else { t12
= 1.0E+6 ; } if ( M_idx_2 != 0 ) { t13 = - 0.01 ; } else { t13 = - 1.0E+6 ; }
t18 [ 0ULL ] = - ( intermediate_der98 * 3.0 ) ; t18 [ 1ULL ] = - ( X_idx_12 *
1.0526315789473684 ) ; t18 [ 2ULL ] = - ( - sin ( intrm_sf_mf_13 ) * t62 *
5.0 + cos ( intrm_sf_mf_13 ) * t63 * 5.0 ) ; t18 [ 3ULL ] = - ( - ( cos (
intrm_sf_mf_13 ) * 5.0 ) * t62 + - sin ( intrm_sf_mf_13 ) * t63 * 5.0 ) ; t19
[ 0ULL ] = - ( t68 * 3.0 ) ; t19 [ 1ULL ] = - ( intermediate_der99 *
1.0526315789473684 ) ; t19 [ 2ULL ] = - 1.0E-6 ; t19 [ 3ULL ] = 1.0E-6 ; t20
[ 0ULL ] = - ( intermediate_der95 * 3.0 ) ; t20 [ 1ULL ] = - ( X_idx_26 *
1.0526315789473684 ) ; t20 [ 2ULL ] = - 1.0E-6 ; t20 [ 3ULL ] = 1.0E-6 ; t21
[ 0ULL ] = - ( t69 * 3.0 ) ; t21 [ 1ULL ] = - ( X_idx_11 * 1.0526315789473684
) ; t21 [ 2ULL ] = - 1.0E-6 ; t21 [ 3ULL ] = 1.0E-6 ; t22 [ 0ULL ] = - (
intermediate_der94 * 3.0 ) ; t22 [ 1ULL ] = - ( X_idx_23 * 1.0526315789473684
) ; t22 [ 2ULL ] = - 1.0E-6 ; t22 [ 3ULL ] = 1.0E-6 ; t23 [ 0ULL ] = - (
intermediate_der96 * 3.0 ) ; t23 [ 1ULL ] = - ( X_idx_24 * 1.0526315789473684
) ; t23 [ 2ULL ] = - 1.0E-6 ; t23 [ 3ULL ] = 1.0E-6 ; t24 [ 0ULL ] = - (
intermediate_der97 * 3.0 ) ; t24 [ 1ULL ] = - ( X_idx_25 * 1.0526315789473684
) ; t24 [ 2ULL ] = - 1.0E-6 ; t24 [ 3ULL ] = 1.0E-6 ; t31 [ 0ULL ] = - ( cos
( intrm_sf_mf_13 ) * - 0.5 + sin ( intrm_sf_mf_13 ) * 0.28866666666666663 ) ;
t31 [ 1ULL ] = - ( - sin ( intrm_sf_mf_13 ) * - 0.5 + cos ( intrm_sf_mf_13 )
* 0.28866666666666663 ) ; t31 [ 2ULL ] = X_idx_7 * 1.0E-6 ; t31 [ 3ULL ] =
t61 * 1.0E-6 ; t32 [ 0ULL ] = - ( cos ( intrm_sf_mf_13 ) * - 0.5 + sin (
intrm_sf_mf_13 ) * - 0.28866666666666663 ) ; t32 [ 1ULL ] = - ( - sin (
intrm_sf_mf_13 ) * - 0.5 + cos ( intrm_sf_mf_13 ) * - 0.28866666666666663 ) ;
t32 [ 2ULL ] = t8 * 1.0E-6 ; t32 [ 3ULL ] = t9 * 1.0E-6 ; t33 [ 0ULL ] = - (
cos ( intrm_sf_mf_13 ) * 0.28866666666666663 + sin ( intrm_sf_mf_13 ) * 0.5 )
; t33 [ 1ULL ] = - ( - sin ( intrm_sf_mf_13 ) * 0.28866666666666663 + cos (
intrm_sf_mf_13 ) * 0.5 ) ; t33 [ 2ULL ] = t10 * 1.0E-6 ; t33 [ 3ULL ] = t11 *
1.0E-6 ; t34 [ 0ULL ] = - ( cos ( intrm_sf_mf_13 ) * - 0.28866666666666663 +
sin ( intrm_sf_mf_13 ) * 0.5 ) ; t34 [ 1ULL ] = - ( - sin ( intrm_sf_mf_13 )
* - 0.28866666666666663 + cos ( intrm_sf_mf_13 ) * 0.5 ) ; t34 [ 2ULL ] = t12
* 1.0E-6 ; t34 [ 3ULL ] = t13 * 1.0E-6 ; t14 [ 0ULL ] = - ( X_idx_4 *
0.90599999999999992 ) ; t14 [ 1ULL ] = - ( - ( X_idx_3 * 0.1 ) *
1.0526315789473684 ) ; t14 [ 2ULL ] = - ( - ( X_idx_1 * 0.1 ) *
1.0526315789473684 ) ; t14 [ 3ULL ] = - ( X_idx_4 * - 0.60600000000000009 ) *
0.35087719298245612 ; t14 [ 4ULL ] = - ( X_idx_1 * 0.90599999999999992 ) ;
t14 [ 5ULL ] = - ( X_idx_3 * - 0.60600000000000009 ) * 0.35087719298245612 ;
for ( t54 = 0ULL ; t54 < 4ULL ; t54 ++ ) { t14 [ t54 + 6ULL ] = t18 [ t54 ] ;
} for ( t54 = 0ULL ; t54 < 4ULL ; t54 ++ ) { t14 [ t54 + 10ULL ] = t19 [ t54
] ; } for ( t54 = 0ULL ; t54 < 4ULL ; t54 ++ ) { t14 [ t54 + 14ULL ] = t20 [
t54 ] ; } for ( t54 = 0ULL ; t54 < 4ULL ; t54 ++ ) { t14 [ t54 + 18ULL ] =
t21 [ t54 ] ; } for ( t54 = 0ULL ; t54 < 4ULL ; t54 ++ ) { t14 [ t54 + 22ULL
] = t22 [ t54 ] ; } for ( t54 = 0ULL ; t54 < 4ULL ; t54 ++ ) { t14 [ t54 +
26ULL ] = t23 [ t54 ] ; } for ( t54 = 0ULL ; t54 < 4ULL ; t54 ++ ) { t14 [
t54 + 30ULL ] = t24 [ t54 ] ; } t14 [ 34ULL ] = t0 * 1.0E-6 ; t14 [ 35ULL ] =
( M_idx_1 != 0 ? - 0.01 : - 1.0E+6 ) * 1.0E-6 ; t14 [ 36ULL ] = t67 * 1.0E-6
; t14 [ 37ULL ] = ( M_idx_5 != 0 ? - 0.01 : - 1.0E+6 ) * 1.0E-6 ; t14 [ 38ULL
] = X_idx_13 * 1.0E-6 ; t14 [ 39ULL ] = ( M_idx_7 != 0 ? - 0.01 : - 1.0E+6 )
* 1.0E-6 ; t14 [ 40ULL ] = X_idx_14 * 1.0E-6 ; t14 [ 41ULL ] = ( M_idx_9 != 0
? - 0.01 : - 1.0E+6 ) * 1.0E-6 ; t14 [ 42ULL ] = X_idx_15 * 1.0E-6 ; t14 [
43ULL ] = ( M_idx_11 != 0 ? - 0.01 : - 1.0E+6 ) * 1.0E-6 ; t14 [ 44ULL ] =
X_idx_16 * 1.0E-6 ; t14 [ 45ULL ] = ( M_idx_3 != 0 ? - 0.01 : - 1.0E+6 ) *
1.0E-6 ; for ( t54 = 0ULL ; t54 < 4ULL ; t54 ++ ) { t14 [ t54 + 46ULL ] = t31
[ t54 ] ; } for ( t54 = 0ULL ; t54 < 4ULL ; t54 ++ ) { t14 [ t54 + 50ULL ] =
t32 [ t54 ] ; } for ( t54 = 0ULL ; t54 < 4ULL ; t54 ++ ) { t14 [ t54 + 54ULL
] = t33 [ t54 ] ; } for ( t54 = 0ULL ; t54 < 4ULL ; t54 ++ ) { t14 [ t54 +
58ULL ] = t34 [ t54 ] ; } out . mX [ 0 ] = t14 [ 0 ] ; out . mX [ 1 ] = t14 [
1 ] ; out . mX [ 2 ] = t14 [ 2 ] ; out . mX [ 3 ] = t14 [ 3 ] ; out . mX [ 4
] = t14 [ 4 ] ; out . mX [ 5 ] = t14 [ 5 ] ; out . mX [ 6 ] = t14 [ 6 ] ; out
. mX [ 7 ] = t14 [ 7 ] ; out . mX [ 8 ] = t14 [ 8 ] ; out . mX [ 9 ] = t14 [
9 ] ; out . mX [ 10 ] = t14 [ 10 ] ; out . mX [ 11 ] = t14 [ 11 ] ; out . mX
[ 12 ] = t14 [ 12 ] ; out . mX [ 13 ] = t14 [ 13 ] ; out . mX [ 14 ] = t14 [
14 ] ; out . mX [ 15 ] = t14 [ 15 ] ; out . mX [ 16 ] = t14 [ 16 ] ; out . mX
[ 17 ] = t14 [ 17 ] ; out . mX [ 18 ] = t14 [ 18 ] ; out . mX [ 19 ] = t14 [
19 ] ; out . mX [ 20 ] = t14 [ 20 ] ; out . mX [ 21 ] = t14 [ 21 ] ; out . mX
[ 22 ] = t14 [ 22 ] ; out . mX [ 23 ] = t14 [ 23 ] ; out . mX [ 24 ] = t14 [
24 ] ; out . mX [ 25 ] = t14 [ 25 ] ; out . mX [ 26 ] = t14 [ 26 ] ; out . mX
[ 27 ] = t14 [ 27 ] ; out . mX [ 28 ] = t14 [ 28 ] ; out . mX [ 29 ] = t14 [
29 ] ; out . mX [ 30 ] = t14 [ 30 ] ; out . mX [ 31 ] = t14 [ 31 ] ; out . mX
[ 32 ] = t14 [ 32 ] ; out . mX [ 33 ] = t14 [ 33 ] ; out . mX [ 34 ] = t14 [
34 ] ; out . mX [ 35 ] = t14 [ 35 ] ; out . mX [ 36 ] = t14 [ 36 ] ; out . mX
[ 37 ] = t14 [ 37 ] ; out . mX [ 38 ] = t14 [ 38 ] ; out . mX [ 39 ] = t14 [
39 ] ; out . mX [ 40 ] = t14 [ 40 ] ; out . mX [ 41 ] = t14 [ 41 ] ; out . mX
[ 42 ] = t14 [ 42 ] ; out . mX [ 43 ] = t14 [ 43 ] ; out . mX [ 44 ] = t14 [
44 ] ; out . mX [ 45 ] = t14 [ 45 ] ; out . mX [ 46 ] = t14 [ 46 ] ; out . mX
[ 47 ] = t14 [ 47 ] ; out . mX [ 48 ] = t14 [ 48 ] ; out . mX [ 49 ] = t14 [
49 ] ; out . mX [ 50 ] = t14 [ 50 ] ; out . mX [ 51 ] = t14 [ 51 ] ; out . mX
[ 52 ] = t14 [ 52 ] ; out . mX [ 53 ] = t14 [ 53 ] ; out . mX [ 54 ] = t14 [
54 ] ; out . mX [ 55 ] = t14 [ 55 ] ; out . mX [ 56 ] = t14 [ 56 ] ; out . mX
[ 57 ] = t14 [ 57 ] ; out . mX [ 58 ] = t14 [ 58 ] ; out . mX [ 59 ] = t14 [
59 ] ; out . mX [ 60 ] = t14 [ 60 ] ; out . mX [ 61 ] = t14 [ 61 ] ; ( void )
sys ; ( void ) t74 ; return 0 ; }
