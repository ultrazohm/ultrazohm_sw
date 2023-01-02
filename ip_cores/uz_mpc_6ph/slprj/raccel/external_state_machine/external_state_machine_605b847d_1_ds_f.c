#include "ne_ds.h"
#include "external_state_machine_605b847d_1_ds_f.h"
#include "external_state_machine_605b847d_1_ds_sys_struct.h"
#include "external_state_machine_605b847d_1_ds_externals.h"
#include "external_state_machine_605b847d_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T external_state_machine_605b847d_1_ds_f ( const NeDynamicSystem * sys
, const NeDynamicSystemInput * t23 , NeDsMethodOutput * t24 ) { PmRealVector
out ; real_T Subsystem1_Simscape_Component_i_alpha ; real_T
Subsystem1_Simscape_Component_i_beta ; real_T
Subsystem1_x6ph_Inverter_MOSFET6_mosfet_equation_i ; real_T
Subsystem1_x6ph_Inverter_MOSFET6_mosfet_equation_v ; real_T
Subsystem1_x6ph_Inverter_MOSFET8_mosfet_equation_i ; real_T
Subsystem1_x6ph_Inverter_MOSFET8_mosfet_equation_v ; real_T U_idx_0 ; real_T
X_idx_1 ; real_T X_idx_11 ; real_T X_idx_12 ; real_T X_idx_13 ; real_T
X_idx_14 ; real_T X_idx_15 ; real_T X_idx_16 ; real_T X_idx_17 ; real_T
X_idx_18 ; real_T X_idx_19 ; real_T X_idx_20 ; real_T X_idx_21 ; real_T
X_idx_22 ; real_T X_idx_23 ; real_T X_idx_24 ; real_T X_idx_25 ; real_T
X_idx_26 ; real_T X_idx_3 ; real_T X_idx_4 ; real_T X_idx_7 ; real_T
intrm_sf_mf_13 ; real_T intrm_sf_mf_15 ; real_T t0 ; real_T t1 ; real_T t10 ;
real_T t11 ; real_T t2 ; real_T t22 ; real_T t4 ; real_T t5 ; real_T t7 ;
real_T t8 ; int32_T M_idx_0 ; int32_T M_idx_1 ; int32_T M_idx_10 ; int32_T
M_idx_11 ; int32_T M_idx_2 ; int32_T M_idx_3 ; int32_T M_idx_4 ; int32_T
M_idx_5 ; int32_T M_idx_6 ; int32_T M_idx_7 ; int32_T M_idx_8 ; int32_T
M_idx_9 ; M_idx_0 = t23 -> mM . mX [ 0 ] ; M_idx_1 = t23 -> mM . mX [ 1 ] ;
M_idx_2 = t23 -> mM . mX [ 2 ] ; M_idx_3 = t23 -> mM . mX [ 3 ] ; M_idx_4 =
t23 -> mM . mX [ 4 ] ; M_idx_5 = t23 -> mM . mX [ 5 ] ; M_idx_6 = t23 -> mM .
mX [ 6 ] ; M_idx_7 = t23 -> mM . mX [ 7 ] ; M_idx_8 = t23 -> mM . mX [ 8 ] ;
M_idx_9 = t23 -> mM . mX [ 9 ] ; M_idx_10 = t23 -> mM . mX [ 10 ] ; M_idx_11
= t23 -> mM . mX [ 11 ] ; U_idx_0 = t23 -> mU . mX [ 0 ] ; X_idx_1 = t23 ->
mX . mX [ 1 ] ; X_idx_3 = t23 -> mX . mX [ 3 ] ; X_idx_4 = t23 -> mX . mX [ 4
] ; X_idx_7 = t23 -> mX . mX [ 7 ] ; X_idx_11 = t23 -> mX . mX [ 11 ] ;
X_idx_12 = t23 -> mX . mX [ 12 ] ; X_idx_13 = t23 -> mX . mX [ 13 ] ;
X_idx_14 = t23 -> mX . mX [ 14 ] ; X_idx_15 = t23 -> mX . mX [ 15 ] ;
X_idx_16 = t23 -> mX . mX [ 16 ] ; X_idx_17 = t23 -> mX . mX [ 17 ] ;
X_idx_18 = t23 -> mX . mX [ 18 ] ; X_idx_19 = t23 -> mX . mX [ 19 ] ;
X_idx_20 = t23 -> mX . mX [ 20 ] ; X_idx_21 = t23 -> mX . mX [ 21 ] ;
X_idx_22 = t23 -> mX . mX [ 22 ] ; X_idx_23 = t23 -> mX . mX [ 23 ] ;
X_idx_24 = t23 -> mX . mX [ 24 ] ; X_idx_25 = t23 -> mX . mX [ 25 ] ;
X_idx_26 = t23 -> mX . mX [ 26 ] ; out = t24 -> mF ; t22 = ( X_idx_11 *
0.33333333333333331 + X_idx_12 * 0.33333333333333331 ) + X_idx_13 *
0.33333333333333331 ; intrm_sf_mf_13 = ( X_idx_14 * 0.33333333333333331 +
X_idx_15 * 0.33333333333333331 ) + X_idx_16 * 0.33333333333333331 ;
Subsystem1_Simscape_Component_i_alpha = ( ( X_idx_25 * 0.28866666666666663 +
X_idx_23 * - 0.5 ) + X_idx_26 * - 0.28866666666666663 ) + X_idx_24 * - 0.5 ;
Subsystem1_Simscape_Component_i_beta = ( ( X_idx_25 * 0.5 + X_idx_23 *
0.28866666666666663 ) + X_idx_26 * 0.5 ) + X_idx_24 * - 0.28866666666666663 ;
t1 = ( - X_idx_23 + - X_idx_24 ) + X_idx_17 ; t2 = - X_idx_11 + U_idx_0 ; t4
= ( - X_idx_25 + - X_idx_26 ) + X_idx_18 ; t5 = - X_idx_16 + U_idx_0 ; t7 =
X_idx_19 + X_idx_23 ; t8 = - X_idx_12 + U_idx_0 ; t10 = X_idx_20 + X_idx_24 ;
t11 = - X_idx_13 + U_idx_0 ;
Subsystem1_x6ph_Inverter_MOSFET6_mosfet_equation_i = X_idx_21 + X_idx_25 ;
Subsystem1_x6ph_Inverter_MOSFET6_mosfet_equation_v = - X_idx_14 + U_idx_0 ;
Subsystem1_x6ph_Inverter_MOSFET8_mosfet_equation_i = X_idx_22 + X_idx_26 ;
Subsystem1_x6ph_Inverter_MOSFET8_mosfet_equation_v = - X_idx_15 + U_idx_0 ;
X_idx_24 = X_idx_11 - t22 ; intrm_sf_mf_15 = X_idx_12 - t22 ; t0 = X_idx_13 -
t22 ; t22 = X_idx_14 - intrm_sf_mf_13 ; X_idx_25 = X_idx_15 - intrm_sf_mf_13
; X_idx_26 = X_idx_16 - intrm_sf_mf_13 ; intrm_sf_mf_13 = X_idx_7 * 5.0 ;
X_idx_23 = ( ( ( X_idx_24 * 0.33333333333333331 + intrm_sf_mf_15 * -
0.16666666666666666 ) + t0 * - 0.16666666666666666 ) + t22 *
0.28866666666666663 ) + X_idx_25 * - 0.28866666666666663 ; X_idx_24 = ( ( (
intrm_sf_mf_15 * 0.28866666666666663 + t0 * - 0.28866666666666663 ) + t22 *
0.16666666666666666 ) + X_idx_25 * 0.16666666666666666 ) + X_idx_26 * -
0.33333333333333331 ; t22 = cos ( intrm_sf_mf_13 ) * X_idx_23 + sin (
intrm_sf_mf_13 ) * X_idx_24 ; intrm_sf_mf_15 = - sin ( intrm_sf_mf_13 ) *
X_idx_23 + cos ( intrm_sf_mf_13 ) * X_idx_24 ; if ( M_idx_0 != 0 ) { t0 = t2
- t1 * 0.01 ; } else { t0 = t2 - t1 / 1.0E-6 ; } if ( M_idx_1 != 0 ) { t1 =
X_idx_11 - X_idx_17 * 0.01 ; } else { t1 = X_idx_11 - X_idx_17 / 1.0E-6 ; }
if ( M_idx_4 != 0 ) { t2 = t5 - t4 * 0.01 ; } else { t2 = t5 - t4 / 1.0E-6 ;
} if ( M_idx_5 != 0 ) { U_idx_0 = X_idx_16 - X_idx_18 * 0.01 ; } else {
U_idx_0 = X_idx_16 - X_idx_18 / 1.0E-6 ; } if ( M_idx_6 != 0 ) { t4 = t8 - t7
* 0.01 ; } else { t4 = t8 - t7 / 1.0E-6 ; } if ( M_idx_7 != 0 ) { t5 =
X_idx_12 - X_idx_19 * 0.01 ; } else { t5 = X_idx_12 - X_idx_19 / 1.0E-6 ; }
if ( M_idx_8 != 0 ) { X_idx_26 = t11 - t10 * 0.01 ; } else { X_idx_26 = t11 -
t10 / 1.0E-6 ; } if ( M_idx_9 != 0 ) { t7 = X_idx_13 - X_idx_20 * 0.01 ; }
else { t7 = X_idx_13 - X_idx_20 / 1.0E-6 ; } if ( M_idx_10 != 0 ) { t8 =
Subsystem1_x6ph_Inverter_MOSFET6_mosfet_equation_v -
Subsystem1_x6ph_Inverter_MOSFET6_mosfet_equation_i * 0.01 ; } else { t8 =
Subsystem1_x6ph_Inverter_MOSFET6_mosfet_equation_v -
Subsystem1_x6ph_Inverter_MOSFET6_mosfet_equation_i / 1.0E-6 ; } if ( M_idx_11
!= 0 ) { X_idx_25 = X_idx_14 - X_idx_21 * 0.01 ; } else { X_idx_25 = X_idx_14
- X_idx_21 / 1.0E-6 ; } if ( M_idx_2 != 0 ) { t10 =
Subsystem1_x6ph_Inverter_MOSFET8_mosfet_equation_v -
Subsystem1_x6ph_Inverter_MOSFET8_mosfet_equation_i * 0.01 ; } else { t10 =
Subsystem1_x6ph_Inverter_MOSFET8_mosfet_equation_v -
Subsystem1_x6ph_Inverter_MOSFET8_mosfet_equation_i / 1.0E-6 ; } if ( M_idx_3
!= 0 ) { t11 = X_idx_15 - X_idx_22 * 0.01 ; } else { t11 = X_idx_15 -
X_idx_22 / 1.0E-6 ; } X_idx_24 = - ( cos ( intrm_sf_mf_13 ) *
Subsystem1_Simscape_Component_i_alpha + sin ( intrm_sf_mf_13 ) *
Subsystem1_Simscape_Component_i_beta ) ; X_idx_23 = - ( - sin (
intrm_sf_mf_13 ) * Subsystem1_Simscape_Component_i_alpha + cos (
intrm_sf_mf_13 ) * Subsystem1_Simscape_Component_i_beta ) ; out . mX [ 0 ] =
- 0.0 ; out . mX [ 1 ] = - 0.0 ; out . mX [ 2 ] = - 0.0 ; out . mX [ 3 ] =
0.0 ; out . mX [ 4 ] = - ( ( t22 - ( - ( X_idx_4 * X_idx_1 * 0.302 ) ) ) /
0.33333333333333331 ) ; out . mX [ 5 ] = - ( ( intrm_sf_mf_15 - X_idx_3 *
X_idx_1 * 0.1 ) / 0.95 ) ; out . mX [ 6 ] = - 0.0 ; out . mX [ 7 ] = - 0.0 ;
out . mX [ 8 ] = 0.0 ; out . mX [ 9 ] = 0.0 ; out . mX [ 10 ] = 0.0 ; out .
mX [ 11 ] = 0.0 ; out . mX [ 12 ] = X_idx_24 ; out . mX [ 13 ] = X_idx_23 ;
out . mX [ 14 ] = - ( X_idx_3 * X_idx_4 * - 0.60600000000000009 ) / 2.85 ;
out . mX [ 15 ] = t0 / 1.0E+6 ; out . mX [ 16 ] = t1 / 1.0E+6 ; out . mX [ 17
] = t2 / 1.0E+6 ; out . mX [ 18 ] = U_idx_0 / 1.0E+6 ; out . mX [ 19 ] = t4 /
1.0E+6 ; out . mX [ 20 ] = t5 / 1.0E+6 ; out . mX [ 21 ] = X_idx_26 / 1.0E+6
; out . mX [ 22 ] = t7 / 1.0E+6 ; out . mX [ 23 ] = t8 / 1.0E+6 ; out . mX [
24 ] = X_idx_25 / 1.0E+6 ; out . mX [ 25 ] = t10 / 1.0E+6 ; out . mX [ 26 ] =
t11 / 1.0E+6 ; ( void ) sys ; ( void ) t24 ; return 0 ; }
