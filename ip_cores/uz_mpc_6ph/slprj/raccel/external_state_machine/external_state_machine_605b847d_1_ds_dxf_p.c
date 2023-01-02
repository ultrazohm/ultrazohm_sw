#include "ne_ds.h"
#include "external_state_machine_605b847d_1_ds_dxf_p.h"
#include "external_state_machine_605b847d_1_ds_sys_struct.h"
#include "external_state_machine_605b847d_1_ds_externals.h"
#include "external_state_machine_605b847d_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T external_state_machine_605b847d_1_ds_dxf_p ( const NeDynamicSystem *
sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) {
PmSparsityPattern out ; ( void ) t1 ; out = t2 -> mDXF_P ; out . mNumCol =
27ULL ; out . mNumRow = 27ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 0 ;
out . mJc [ 2 ] = 2 ; out . mJc [ 3 ] = 2 ; out . mJc [ 4 ] = 4 ; out . mJc [
5 ] = 6 ; out . mJc [ 6 ] = 6 ; out . mJc [ 7 ] = 6 ; out . mJc [ 8 ] = 10 ;
out . mJc [ 9 ] = 10 ; out . mJc [ 10 ] = 10 ; out . mJc [ 11 ] = 10 ; out .
mJc [ 12 ] = 14 ; out . mJc [ 13 ] = 18 ; out . mJc [ 14 ] = 22 ; out . mJc [
15 ] = 26 ; out . mJc [ 16 ] = 30 ; out . mJc [ 17 ] = 34 ; out . mJc [ 18 ]
= 36 ; out . mJc [ 19 ] = 38 ; out . mJc [ 20 ] = 40 ; out . mJc [ 21 ] = 42
; out . mJc [ 22 ] = 44 ; out . mJc [ 23 ] = 46 ; out . mJc [ 24 ] = 50 ; out
. mJc [ 25 ] = 54 ; out . mJc [ 26 ] = 58 ; out . mJc [ 27 ] = 62 ; out . mIr
[ 0 ] = 4 ; out . mIr [ 1 ] = 5 ; out . mIr [ 2 ] = 5 ; out . mIr [ 3 ] = 14
; out . mIr [ 4 ] = 4 ; out . mIr [ 5 ] = 14 ; out . mIr [ 6 ] = 4 ; out .
mIr [ 7 ] = 5 ; out . mIr [ 8 ] = 12 ; out . mIr [ 9 ] = 13 ; out . mIr [ 10
] = 4 ; out . mIr [ 11 ] = 5 ; out . mIr [ 12 ] = 15 ; out . mIr [ 13 ] = 16
; out . mIr [ 14 ] = 4 ; out . mIr [ 15 ] = 5 ; out . mIr [ 16 ] = 19 ; out .
mIr [ 17 ] = 20 ; out . mIr [ 18 ] = 4 ; out . mIr [ 19 ] = 5 ; out . mIr [
20 ] = 21 ; out . mIr [ 21 ] = 22 ; out . mIr [ 22 ] = 4 ; out . mIr [ 23 ] =
5 ; out . mIr [ 24 ] = 23 ; out . mIr [ 25 ] = 24 ; out . mIr [ 26 ] = 4 ;
out . mIr [ 27 ] = 5 ; out . mIr [ 28 ] = 25 ; out . mIr [ 29 ] = 26 ; out .
mIr [ 30 ] = 4 ; out . mIr [ 31 ] = 5 ; out . mIr [ 32 ] = 17 ; out . mIr [
33 ] = 18 ; out . mIr [ 34 ] = 15 ; out . mIr [ 35 ] = 16 ; out . mIr [ 36 ]
= 17 ; out . mIr [ 37 ] = 18 ; out . mIr [ 38 ] = 19 ; out . mIr [ 39 ] = 20
; out . mIr [ 40 ] = 21 ; out . mIr [ 41 ] = 22 ; out . mIr [ 42 ] = 23 ; out
. mIr [ 43 ] = 24 ; out . mIr [ 44 ] = 25 ; out . mIr [ 45 ] = 26 ; out . mIr
[ 46 ] = 12 ; out . mIr [ 47 ] = 13 ; out . mIr [ 48 ] = 15 ; out . mIr [ 49
] = 19 ; out . mIr [ 50 ] = 12 ; out . mIr [ 51 ] = 13 ; out . mIr [ 52 ] =
15 ; out . mIr [ 53 ] = 21 ; out . mIr [ 54 ] = 12 ; out . mIr [ 55 ] = 13 ;
out . mIr [ 56 ] = 17 ; out . mIr [ 57 ] = 23 ; out . mIr [ 58 ] = 12 ; out .
mIr [ 59 ] = 13 ; out . mIr [ 60 ] = 17 ; out . mIr [ 61 ] = 25 ; ( void )
sys ; ( void ) t2 ; return 0 ; }
