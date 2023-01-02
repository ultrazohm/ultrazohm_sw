#include "ne_ds.h"
#include "external_state_machine_605b847d_1_ds_a_p.h"
#include "external_state_machine_605b847d_1_ds_sys_struct.h"
#include "external_state_machine_605b847d_1_ds_externals.h"
#include "external_state_machine_605b847d_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T external_state_machine_605b847d_1_ds_a_p ( const NeDynamicSystem *
sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) {
PmSparsityPattern out ; ( void ) t1 ; out = t2 -> mA_P ; out . mNumCol =
27ULL ; out . mNumRow = 27ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 2 ;
out . mJc [ 2 ] = 6 ; out . mJc [ 3 ] = 6 ; out . mJc [ 4 ] = 8 ; out . mJc [
5 ] = 11 ; out . mJc [ 6 ] = 13 ; out . mJc [ 7 ] = 15 ; out . mJc [ 8 ] = 15
; out . mJc [ 9 ] = 17 ; out . mJc [ 10 ] = 18 ; out . mJc [ 11 ] = 19 ; out
. mJc [ 12 ] = 21 ; out . mJc [ 13 ] = 23 ; out . mJc [ 14 ] = 25 ; out . mJc
[ 15 ] = 27 ; out . mJc [ 16 ] = 29 ; out . mJc [ 17 ] = 31 ; out . mJc [ 18
] = 31 ; out . mJc [ 19 ] = 31 ; out . mJc [ 20 ] = 31 ; out . mJc [ 21 ] =
31 ; out . mJc [ 22 ] = 31 ; out . mJc [ 23 ] = 31 ; out . mJc [ 24 ] = 33 ;
out . mJc [ 25 ] = 35 ; out . mJc [ 26 ] = 37 ; out . mJc [ 27 ] = 39 ; out .
mIr [ 0 ] = 0 ; out . mIr [ 1 ] = 8 ; out . mIr [ 2 ] = 1 ; out . mIr [ 3 ] =
3 ; out . mIr [ 4 ] = 5 ; out . mIr [ 5 ] = 9 ; out . mIr [ 6 ] = 4 ; out .
mIr [ 7 ] = 12 ; out . mIr [ 8 ] = 5 ; out . mIr [ 9 ] = 13 ; out . mIr [ 10
] = 14 ; out . mIr [ 11 ] = 6 ; out . mIr [ 12 ] = 10 ; out . mIr [ 13 ] = 7
; out . mIr [ 14 ] = 11 ; out . mIr [ 15 ] = 0 ; out . mIr [ 16 ] = 8 ; out .
mIr [ 17 ] = 2 ; out . mIr [ 18 ] = 14 ; out . mIr [ 19 ] = 6 ; out . mIr [
20 ] = 7 ; out . mIr [ 21 ] = 6 ; out . mIr [ 22 ] = 7 ; out . mIr [ 23 ] = 6
; out . mIr [ 24 ] = 7 ; out . mIr [ 25 ] = 6 ; out . mIr [ 26 ] = 7 ; out .
mIr [ 27 ] = 6 ; out . mIr [ 28 ] = 7 ; out . mIr [ 29 ] = 6 ; out . mIr [ 30
] = 7 ; out . mIr [ 31 ] = 10 ; out . mIr [ 32 ] = 11 ; out . mIr [ 33 ] = 10
; out . mIr [ 34 ] = 11 ; out . mIr [ 35 ] = 10 ; out . mIr [ 36 ] = 11 ; out
. mIr [ 37 ] = 10 ; out . mIr [ 38 ] = 11 ; ( void ) sys ; ( void ) t2 ;
return 0 ; }
