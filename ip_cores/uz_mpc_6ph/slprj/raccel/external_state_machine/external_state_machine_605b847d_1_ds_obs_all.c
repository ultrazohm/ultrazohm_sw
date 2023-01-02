#include "ne_ds.h"
#include "external_state_machine_605b847d_1_ds_obs_all.h"
#include "external_state_machine_605b847d_1_ds_sys_struct.h"
#include "external_state_machine_605b847d_1_ds_externals.h"
#include "external_state_machine_605b847d_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T external_state_machine_605b847d_1_ds_obs_all ( const NeDynamicSystem
* sys , const NeDynamicSystemInput * t32 , NeDsMethodOutput * t33 ) {
PmRealVector out ; real_T t0 [ 278 ] ; real_T
Subsystem1_DC_link_Voltage_Sensor_V ; real_T Subsystem1_Open_Circuit1_V_v ;
real_T Subsystem1_Open_Circuit_V_v ; real_T
Subsystem1_Simscape_Component_i_a1 ; real_T
Subsystem1_Simscape_Component_i_c2 ; real_T
Subsystem1_x6ph_Inverter_MOSFET_mosfet_equation_i ; real_T U_idx_0 ; real_T
U_idx_1 ; real_T U_idx_10 ; real_T U_idx_11 ; real_T U_idx_12 ; real_T
U_idx_13 ; real_T U_idx_2 ; real_T U_idx_3 ; real_T U_idx_4 ; real_T U_idx_5
; real_T U_idx_6 ; real_T U_idx_7 ; real_T U_idx_8 ; real_T U_idx_9 ; real_T
X_idx_0 ; real_T X_idx_1 ; real_T X_idx_10 ; real_T X_idx_11 ; real_T
X_idx_12 ; real_T X_idx_13 ; real_T X_idx_14 ; real_T X_idx_15 ; real_T
X_idx_16 ; real_T X_idx_17 ; real_T X_idx_18 ; real_T X_idx_19 ; real_T
X_idx_2 ; real_T X_idx_20 ; real_T X_idx_21 ; real_T X_idx_22 ; real_T
X_idx_23 ; real_T X_idx_24 ; real_T X_idx_25 ; real_T X_idx_26 ; real_T
X_idx_3 ; real_T X_idx_4 ; real_T X_idx_5 ; real_T X_idx_6 ; real_T X_idx_7 ;
real_T X_idx_8 ; real_T X_idx_9 ; real_T t10 ; real_T t13 ; real_T t14 ;
real_T t17 ; real_T t18 ; real_T t2 ; real_T t21 ; real_T t22 ; real_T t25 ;
real_T t26 ; real_T t27 ; real_T t28 ; real_T t29 ; real_T t30 ; real_T t31 ;
real_T t5 ; real_T t6 ; real_T t9 ; int32_T b ; U_idx_0 = t32 -> mU . mX [ 0
] ; U_idx_1 = t32 -> mU . mX [ 1 ] ; U_idx_2 = t32 -> mU . mX [ 2 ] ; U_idx_3
= t32 -> mU . mX [ 3 ] ; U_idx_4 = t32 -> mU . mX [ 4 ] ; U_idx_5 = t32 -> mU
. mX [ 5 ] ; U_idx_6 = t32 -> mU . mX [ 6 ] ; U_idx_7 = t32 -> mU . mX [ 7 ]
; U_idx_8 = t32 -> mU . mX [ 8 ] ; U_idx_9 = t32 -> mU . mX [ 9 ] ; U_idx_10
= t32 -> mU . mX [ 10 ] ; U_idx_11 = t32 -> mU . mX [ 11 ] ; U_idx_12 = t32
-> mU . mX [ 12 ] ; U_idx_13 = t32 -> mU . mX [ 13 ] ; X_idx_0 = t32 -> mX .
mX [ 0 ] ; X_idx_1 = t32 -> mX . mX [ 1 ] ; X_idx_2 = t32 -> mX . mX [ 2 ] ;
X_idx_3 = t32 -> mX . mX [ 3 ] ; X_idx_4 = t32 -> mX . mX [ 4 ] ; X_idx_5 =
t32 -> mX . mX [ 5 ] ; X_idx_6 = t32 -> mX . mX [ 6 ] ; X_idx_7 = t32 -> mX .
mX [ 7 ] ; X_idx_8 = t32 -> mX . mX [ 8 ] ; X_idx_9 = t32 -> mX . mX [ 9 ] ;
X_idx_10 = t32 -> mX . mX [ 10 ] ; X_idx_11 = t32 -> mX . mX [ 11 ] ;
X_idx_12 = t32 -> mX . mX [ 12 ] ; X_idx_13 = t32 -> mX . mX [ 13 ] ;
X_idx_14 = t32 -> mX . mX [ 14 ] ; X_idx_15 = t32 -> mX . mX [ 15 ] ;
X_idx_16 = t32 -> mX . mX [ 16 ] ; X_idx_17 = t32 -> mX . mX [ 17 ] ;
X_idx_18 = t32 -> mX . mX [ 18 ] ; X_idx_19 = t32 -> mX . mX [ 19 ] ;
X_idx_20 = t32 -> mX . mX [ 20 ] ; X_idx_21 = t32 -> mX . mX [ 21 ] ;
X_idx_22 = t32 -> mX . mX [ 22 ] ; X_idx_23 = t32 -> mX . mX [ 23 ] ;
X_idx_24 = t32 -> mX . mX [ 24 ] ; X_idx_25 = t32 -> mX . mX [ 25 ] ;
X_idx_26 = t32 -> mX . mX [ 26 ] ; out = t33 -> mOBS_ALL ;
Subsystem1_DC_link_Voltage_Sensor_V = - U_idx_0 / - 1.0 ;
Subsystem1_Open_Circuit_V_v = ( X_idx_11 * 0.33333333333333331 + X_idx_12 *
0.33333333333333331 ) + X_idx_13 * 0.33333333333333331 ;
Subsystem1_Open_Circuit1_V_v = ( X_idx_14 * 0.33333333333333331 + X_idx_15 *
0.33333333333333331 ) + X_idx_16 * 0.33333333333333331 ;
Subsystem1_Simscape_Component_i_a1 = - X_idx_23 + - X_idx_24 ;
Subsystem1_Simscape_Component_i_c2 = - X_idx_25 + - X_idx_26 ;
Subsystem1_x6ph_Inverter_MOSFET_mosfet_equation_i = ( - X_idx_23 + - X_idx_24
) + X_idx_17 ; t2 = - X_idx_11 + U_idx_0 ; t5 = ( - X_idx_25 + - X_idx_26 ) +
X_idx_18 ; t6 = - X_idx_16 + U_idx_0 ; t9 = X_idx_19 + X_idx_23 ; t10 = -
X_idx_12 + U_idx_0 ; t13 = X_idx_20 + X_idx_24 ; t14 = - X_idx_13 + U_idx_0 ;
t17 = X_idx_21 + X_idx_25 ; t18 = - X_idx_14 + U_idx_0 ; t21 = X_idx_22 +
X_idx_26 ; t22 = - X_idx_15 + U_idx_0 ; t25 = - X_idx_11 / - 1.0 ; t26 = -
X_idx_12 / - 1.0 ; t27 = - X_idx_13 / - 1.0 ; t28 = - X_idx_14 / - 1.0 ; t29
= - X_idx_15 / - 1.0 ; t30 = - X_idx_16 / - 1.0 ; t31 = ( ( ( ( X_idx_17 +
X_idx_18 ) + X_idx_19 ) + X_idx_20 ) + X_idx_21 ) + X_idx_22 ; t0 [ 0ULL ] =
X_idx_8 ; t0 [ 1ULL ] = 0.0 ; t0 [ 2ULL ] = U_idx_0 ; t0 [ 3ULL ] = U_idx_0 ;
t0 [ 4ULL ] = X_idx_0 ; t0 [ 5ULL ] = U_idx_0 ; t0 [ 6ULL ] = 0.0 ; t0 [ 7ULL
] = Subsystem1_DC_link_Voltage_Sensor_V ; t0 [ 8ULL ] = 0.0 ; t0 [ 9ULL ] =
U_idx_0 ; t0 [ 10ULL ] = Subsystem1_DC_link_Voltage_Sensor_V ; t0 [ 11ULL ] =
0.0 ; t0 [ 12ULL ] = 0.0 ; t0 [ 13ULL ] = X_idx_1 ; t0 [ 14ULL ] = U_idx_13 ;
t0 [ 15ULL ] = - X_idx_9 + X_idx_10 ; t0 [ 16ULL ] = U_idx_13 ; t0 [ 17ULL ]
= X_idx_2 ; t0 [ 18ULL ] = 0.0 ; t0 [ 19ULL ] = X_idx_1 ; t0 [ 20ULL ] =
X_idx_1 ; t0 [ 21ULL ] = X_idx_2 * 57.295779513082323 ; t0 [ 22ULL ] =
X_idx_2 ; t0 [ 23ULL ] = X_idx_1 ; t0 [ 24ULL ] = X_idx_1 ; t0 [ 25ULL ] =
X_idx_1 ; t0 [ 26ULL ] = X_idx_9 ; t0 [ 27ULL ] = X_idx_1 ; t0 [ 28ULL ] =
0.0 ; t0 [ 29ULL ] = Subsystem1_Open_Circuit_V_v ; t0 [ 30ULL ] =
Subsystem1_Open_Circuit_V_v ; t0 [ 31ULL ] = Subsystem1_Open_Circuit1_V_v ;
t0 [ 32ULL ] = Subsystem1_Open_Circuit1_V_v ; t0 [ 33ULL ] = ( ( ( ( ( -
X_idx_8 + - X_idx_17 ) + - X_idx_18 ) + - X_idx_19 ) + - X_idx_20 ) + -
X_idx_21 ) + - X_idx_22 ; t0 [ 34ULL ] = 0.0 ; t0 [ 35ULL ] = U_idx_0 ; t0 [
36ULL ] = U_idx_0 ; t0 [ 37ULL ] = U_idx_0 ; t0 [ 38ULL ] = U_idx_0 ; t0 [
39ULL ] = U_idx_0 ; t0 [ 40ULL ] = 0.0 ; t0 [ 41ULL ] = U_idx_0 ; t0 [ 42ULL
] = 0.0 ; t0 [ 43ULL ] = X_idx_1 ; t0 [ 44ULL ] = X_idx_11 ; t0 [ 45ULL ] =
X_idx_14 ; t0 [ 46ULL ] = X_idx_12 ; t0 [ 47ULL ] = X_idx_15 ; t0 [ 48ULL ] =
X_idx_13 ; t0 [ 49ULL ] = X_idx_16 ; t0 [ 50ULL ] =
Subsystem1_Simscape_Component_i_a1 ; t0 [ 51ULL ] = X_idx_25 ; t0 [ 52ULL ] =
( ( X_idx_25 * 0.28866666666666663 + X_idx_23 * - 0.5 ) + X_idx_26 * -
0.28866666666666663 ) + X_idx_24 * - 0.5 ; t0 [ 53ULL ] = X_idx_23 ; t0 [
54ULL ] = X_idx_26 ; t0 [ 55ULL ] = ( ( X_idx_25 * 0.5 + X_idx_23 *
0.28866666666666663 ) + X_idx_26 * 0.5 ) + X_idx_24 * - 0.28866666666666663 ;
t0 [ 56ULL ] = X_idx_24 ; t0 [ 57ULL ] = Subsystem1_Simscape_Component_i_c2 ;
t0 [ 58ULL ] = X_idx_3 ; t0 [ 59ULL ] = X_idx_4 ; t0 [ 60ULL ] = X_idx_5 ; t0
[ 61ULL ] = X_idx_6 ; t0 [ 62ULL ] = X_idx_10 ; t0 [ 63ULL ] =
Subsystem1_Open_Circuit_V_v ; t0 [ 64ULL ] = Subsystem1_Open_Circuit1_V_v ;
t0 [ 65ULL ] = X_idx_7 ; t0 [ 66ULL ] = U_idx_1 ; t0 [ 67ULL ] = U_idx_2 ; t0
[ 68ULL ] = U_idx_3 ; t0 [ 69ULL ] = U_idx_4 ; t0 [ 70ULL ] = U_idx_5 ; t0 [
71ULL ] = U_idx_6 ; t0 [ 72ULL ] = U_idx_7 ; t0 [ 73ULL ] = U_idx_8 ; t0 [
74ULL ] = U_idx_9 ; t0 [ 75ULL ] = U_idx_10 ; t0 [ 76ULL ] = U_idx_11 ; t0 [
77ULL ] = U_idx_12 ; t0 [ 78ULL ] = U_idx_13 ; t0 [ 79ULL ] = U_idx_9 ; t0 [
80ULL ] = U_idx_7 ; t0 [ 81ULL ] = U_idx_11 ; t0 [ 82ULL ] = U_idx_10 ; t0 [
83ULL ] = U_idx_3 ; t0 [ 84ULL ] = U_idx_12 ; t0 [ 85ULL ] = U_idx_5 ; t0 [
86ULL ] = U_idx_4 ; t0 [ 87ULL ] = U_idx_8 ; t0 [ 88ULL ] = U_idx_6 ; t0 [
89ULL ] = U_idx_2 ; t0 [ 90ULL ] = U_idx_1 ; t0 [ 91ULL ] = U_idx_0 ; t0 [
92ULL ] = U_idx_7 ; t0 [ 93ULL ] = X_idx_11 ; t0 [ 94ULL ] = U_idx_7 ; t0 [
95ULL ] = Subsystem1_x6ph_Inverter_MOSFET_mosfet_equation_i ; t0 [ 96ULL ] =
( - U_idx_7 + 0.7 ) / - 1.0 ; t0 [ 97ULL ] = X_idx_11 ; t0 [ 98ULL ] =
U_idx_0 ; t0 [ 99ULL ] = t2 ; t0 [ 100ULL ] = - (
Subsystem1_x6ph_Inverter_MOSFET_mosfet_equation_i * t2 * 0.001 ) / - 1.0 *
1000.0 ; t0 [ 101ULL ] = X_idx_11 ; t0 [ 102ULL ] = U_idx_9 ; t0 [ 103ULL ] =
0.0 ; t0 [ 104ULL ] = U_idx_9 ; t0 [ 105ULL ] = X_idx_17 ; t0 [ 106ULL ] = (
- U_idx_9 + 0.7 ) / - 1.0 ; t0 [ 107ULL ] = 0.0 ; t0 [ 108ULL ] = X_idx_11 ;
t0 [ 109ULL ] = X_idx_11 ; t0 [ 110ULL ] = - ( X_idx_17 * X_idx_11 * 0.001 )
/ - 1.0 * 1000.0 ; t0 [ 111ULL ] = U_idx_0 ; t0 [ 112ULL ] = U_idx_1 ; t0 [
113ULL ] = X_idx_16 ; t0 [ 114ULL ] = U_idx_1 ; t0 [ 115ULL ] = t5 ; t0 [
116ULL ] = ( - U_idx_1 + 0.7 ) / - 1.0 ; t0 [ 117ULL ] = X_idx_16 ; t0 [
118ULL ] = U_idx_0 ; t0 [ 119ULL ] = t6 ; t0 [ 120ULL ] = - ( t5 * t6 * 0.001
) / - 1.0 * 1000.0 ; t0 [ 121ULL ] = X_idx_16 ; t0 [ 122ULL ] = U_idx_2 ; t0
[ 123ULL ] = 0.0 ; t0 [ 124ULL ] = U_idx_2 ; t0 [ 125ULL ] = X_idx_18 ; t0 [
126ULL ] = ( - U_idx_2 + 0.7 ) / - 1.0 ; t0 [ 127ULL ] = 0.0 ; t0 [ 128ULL ]
= X_idx_16 ; t0 [ 129ULL ] = X_idx_16 ; t0 [ 130ULL ] = - ( X_idx_18 *
X_idx_16 * 0.001 ) / - 1.0 * 1000.0 ; t0 [ 131ULL ] = U_idx_0 ; t0 [ 132ULL ]
= U_idx_10 ; t0 [ 133ULL ] = X_idx_12 ; t0 [ 134ULL ] = U_idx_10 ; t0 [
135ULL ] = t9 ; t0 [ 136ULL ] = ( - U_idx_10 + 0.7 ) / - 1.0 ; t0 [ 137ULL ]
= X_idx_12 ; t0 [ 138ULL ] = U_idx_0 ; t0 [ 139ULL ] = t10 ; t0 [ 140ULL ] =
- ( t9 * t10 * 0.001 ) / - 1.0 * 1000.0 ; t0 [ 141ULL ] = X_idx_12 ; t0 [
142ULL ] = U_idx_11 ; t0 [ 143ULL ] = 0.0 ; t0 [ 144ULL ] = U_idx_11 ; t0 [
145ULL ] = X_idx_19 ; t0 [ 146ULL ] = ( - U_idx_11 + 0.7 ) / - 1.0 ; t0 [
147ULL ] = 0.0 ; t0 [ 148ULL ] = X_idx_12 ; t0 [ 149ULL ] = X_idx_12 ; t0 [
150ULL ] = - ( X_idx_19 * X_idx_12 * 0.001 ) / - 1.0 * 1000.0 ; t0 [ 151ULL ]
= U_idx_0 ; t0 [ 152ULL ] = U_idx_12 ; t0 [ 153ULL ] = X_idx_13 ; t0 [ 154ULL
] = U_idx_12 ; t0 [ 155ULL ] = t13 ; t0 [ 156ULL ] = ( - U_idx_12 + 0.7 ) / -
1.0 ; t0 [ 157ULL ] = X_idx_13 ; t0 [ 158ULL ] = U_idx_0 ; t0 [ 159ULL ] =
t14 ; t0 [ 160ULL ] = - ( t13 * t14 * 0.001 ) / - 1.0 * 1000.0 ; t0 [ 161ULL
] = X_idx_13 ; t0 [ 162ULL ] = U_idx_3 ; t0 [ 163ULL ] = 0.0 ; t0 [ 164ULL ]
= U_idx_3 ; t0 [ 165ULL ] = X_idx_20 ; t0 [ 166ULL ] = ( - U_idx_3 + 0.7 ) /
- 1.0 ; t0 [ 167ULL ] = 0.0 ; t0 [ 168ULL ] = X_idx_13 ; t0 [ 169ULL ] =
X_idx_13 ; t0 [ 170ULL ] = - ( X_idx_20 * X_idx_13 * 0.001 ) / - 1.0 * 1000.0
; t0 [ 171ULL ] = U_idx_0 ; t0 [ 172ULL ] = U_idx_4 ; t0 [ 173ULL ] =
X_idx_14 ; t0 [ 174ULL ] = U_idx_4 ; t0 [ 175ULL ] = t17 ; t0 [ 176ULL ] = (
- U_idx_4 + 0.7 ) / - 1.0 ; t0 [ 177ULL ] = X_idx_14 ; t0 [ 178ULL ] =
U_idx_0 ; t0 [ 179ULL ] = t18 ; t0 [ 180ULL ] = - ( t17 * t18 * 0.001 ) / -
1.0 * 1000.0 ; t0 [ 181ULL ] = X_idx_14 ; t0 [ 182ULL ] = U_idx_5 ; t0 [
183ULL ] = 0.0 ; t0 [ 184ULL ] = U_idx_5 ; t0 [ 185ULL ] = X_idx_21 ; t0 [
186ULL ] = ( - U_idx_5 + 0.7 ) / - 1.0 ; t0 [ 187ULL ] = 0.0 ; t0 [ 188ULL ]
= X_idx_14 ; t0 [ 189ULL ] = X_idx_14 ; t0 [ 190ULL ] = - ( X_idx_21 *
X_idx_14 * 0.001 ) / - 1.0 * 1000.0 ; t0 [ 191ULL ] = U_idx_0 ; t0 [ 192ULL ]
= U_idx_6 ; t0 [ 193ULL ] = X_idx_15 ; t0 [ 194ULL ] = U_idx_6 ; t0 [ 195ULL
] = t21 ; t0 [ 196ULL ] = ( - U_idx_6 + 0.7 ) / - 1.0 ; t0 [ 197ULL ] =
X_idx_15 ; t0 [ 198ULL ] = U_idx_0 ; t0 [ 199ULL ] = t22 ; t0 [ 200ULL ] = -
( t21 * t22 * 0.001 ) / - 1.0 * 1000.0 ; t0 [ 201ULL ] = X_idx_15 ; t0 [
202ULL ] = U_idx_8 ; t0 [ 203ULL ] = 0.0 ; t0 [ 204ULL ] = U_idx_8 ; t0 [
205ULL ] = X_idx_22 ; t0 [ 206ULL ] = ( - U_idx_8 + 0.7 ) / - 1.0 ; t0 [
207ULL ] = 0.0 ; t0 [ 208ULL ] = X_idx_15 ; t0 [ 209ULL ] = X_idx_15 ; t0 [
210ULL ] = - ( X_idx_22 * X_idx_15 * 0.001 ) / - 1.0 * 1000.0 ; t0 [ 211ULL ]
= U_idx_0 ; t0 [ 212ULL ] = 0.0 ; t0 [ 213ULL ] = t25 ; t0 [ 214ULL ] = 0.0 ;
t0 [ 215ULL ] = X_idx_11 ; t0 [ 216ULL ] = t26 ; t0 [ 217ULL ] = 0.0 ; t0 [
218ULL ] = X_idx_12 ; t0 [ 219ULL ] = t26 ; t0 [ 220ULL ] = t27 ; t0 [ 221ULL
] = 0.0 ; t0 [ 222ULL ] = X_idx_13 ; t0 [ 223ULL ] = t27 ; t0 [ 224ULL ] =
t28 ; t0 [ 225ULL ] = 0.0 ; t0 [ 226ULL ] = X_idx_14 ; t0 [ 227ULL ] = t28 ;
t0 [ 228ULL ] = t29 ; t0 [ 229ULL ] = 0.0 ; t0 [ 230ULL ] = X_idx_15 ; t0 [
231ULL ] = t29 ; t0 [ 232ULL ] = t30 ; t0 [ 233ULL ] = 0.0 ; t0 [ 234ULL ] =
X_idx_16 ; t0 [ 235ULL ] = t30 ; t0 [ 236ULL ] = t25 ; t0 [ 237ULL ] =
Subsystem1_Simscape_Component_i_a1 ; t0 [ 238ULL ] =
Subsystem1_Simscape_Component_i_a1 ; t0 [ 239ULL ] = X_idx_11 ; t0 [ 240ULL ]
= X_idx_11 ; t0 [ 241ULL ] = Subsystem1_Simscape_Component_i_a1 ; t0 [ 242ULL
] = X_idx_23 ; t0 [ 243ULL ] = X_idx_23 ; t0 [ 244ULL ] = X_idx_12 ; t0 [
245ULL ] = X_idx_12 ; t0 [ 246ULL ] = X_idx_23 ; t0 [ 247ULL ] = X_idx_24 ;
t0 [ 248ULL ] = X_idx_24 ; t0 [ 249ULL ] = X_idx_13 ; t0 [ 250ULL ] =
X_idx_13 ; t0 [ 251ULL ] = X_idx_24 ; t0 [ 252ULL ] = X_idx_25 ; t0 [ 253ULL
] = X_idx_25 ; t0 [ 254ULL ] = X_idx_14 ; t0 [ 255ULL ] = X_idx_14 ; t0 [
256ULL ] = X_idx_25 ; t0 [ 257ULL ] = X_idx_26 ; t0 [ 258ULL ] = X_idx_26 ;
t0 [ 259ULL ] = X_idx_15 ; t0 [ 260ULL ] = X_idx_15 ; t0 [ 261ULL ] =
X_idx_26 ; t0 [ 262ULL ] = Subsystem1_Simscape_Component_i_c2 ; t0 [ 263ULL ]
= Subsystem1_Simscape_Component_i_c2 ; t0 [ 264ULL ] = X_idx_16 ; t0 [ 265ULL
] = X_idx_16 ; t0 [ 266ULL ] = Subsystem1_Simscape_Component_i_c2 ; t0 [
267ULL ] = t31 ; t0 [ 268ULL ] = t31 ; t0 [ 269ULL ] = 0.0 ; t0 [ 270ULL ] =
0.0 ; t0 [ 271ULL ] = t31 ; t0 [ 272ULL ] = X_idx_11 ; t0 [ 273ULL ] =
X_idx_12 ; t0 [ 274ULL ] = X_idx_13 ; t0 [ 275ULL ] = X_idx_14 ; t0 [ 276ULL
] = X_idx_15 ; t0 [ 277ULL ] = X_idx_16 ; for ( b = 0 ; b < 278 ; b ++ ) {
out . mX [ b ] = t0 [ b ] ; } ( void ) sys ; ( void ) t33 ; return 0 ; }
