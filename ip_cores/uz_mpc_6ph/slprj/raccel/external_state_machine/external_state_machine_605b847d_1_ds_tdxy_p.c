#include "ne_ds.h"
#include "external_state_machine_605b847d_1_ds_tdxy_p.h"
#include "external_state_machine_605b847d_1_ds_sys_struct.h"
#include "external_state_machine_605b847d_1_ds_externals.h"
#include "external_state_machine_605b847d_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T external_state_machine_605b847d_1_ds_tdxy_p ( const NeDynamicSystem *
sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) {
PmSparsityPattern out ; ( void ) t1 ; out = t2 -> mTDXY_P ; out . mNumCol =
27ULL ; out . mNumRow = 16ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 0 ;
out . mJc [ 2 ] = 1 ; out . mJc [ 3 ] = 2 ; out . mJc [ 4 ] = 2 ; out . mJc [
5 ] = 2 ; out . mJc [ 6 ] = 2 ; out . mJc [ 7 ] = 2 ; out . mJc [ 8 ] = 2 ;
out . mJc [ 9 ] = 2 ; out . mJc [ 10 ] = 2 ; out . mJc [ 11 ] = 2 ; out . mJc
[ 12 ] = 3 ; out . mJc [ 13 ] = 4 ; out . mJc [ 14 ] = 5 ; out . mJc [ 15 ] =
6 ; out . mJc [ 16 ] = 7 ; out . mJc [ 17 ] = 8 ; out . mJc [ 18 ] = 9 ; out
. mJc [ 19 ] = 10 ; out . mJc [ 20 ] = 11 ; out . mJc [ 21 ] = 12 ; out . mJc
[ 22 ] = 13 ; out . mJc [ 23 ] = 14 ; out . mJc [ 24 ] = 16 ; out . mJc [ 25
] = 18 ; out . mJc [ 26 ] = 20 ; out . mJc [ 27 ] = 22 ; out . mIr [ 0 ] = 2
; out . mIr [ 1 ] = 1 ; out . mIr [ 2 ] = 8 ; out . mIr [ 3 ] = 3 ; out . mIr
[ 4 ] = 4 ; out . mIr [ 5 ] = 5 ; out . mIr [ 6 ] = 6 ; out . mIr [ 7 ] = 7 ;
out . mIr [ 8 ] = 15 ; out . mIr [ 9 ] = 15 ; out . mIr [ 10 ] = 15 ; out .
mIr [ 11 ] = 15 ; out . mIr [ 12 ] = 15 ; out . mIr [ 13 ] = 15 ; out . mIr [
14 ] = 9 ; out . mIr [ 15 ] = 10 ; out . mIr [ 16 ] = 9 ; out . mIr [ 17 ] =
11 ; out . mIr [ 18 ] = 12 ; out . mIr [ 19 ] = 14 ; out . mIr [ 20 ] = 13 ;
out . mIr [ 21 ] = 14 ; ( void ) sys ; ( void ) t2 ; return 0 ; }
