#include "ne_ds.h"
#include "external_state_machine_605b847d_1_ds_tduf_p.h"
#include "external_state_machine_605b847d_1_ds_sys_struct.h"
#include "external_state_machine_605b847d_1_ds_externals.h"
#include "external_state_machine_605b847d_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T external_state_machine_605b847d_1_ds_tduf_p ( const NeDynamicSystem *
sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) {
PmSparsityPattern out ; ( void ) t1 ; out = t2 -> mTDUF_P ; out . mNumCol =
14ULL ; out . mNumRow = 27ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 7 ;
out . mJc [ 2 ] = 8 ; out . mJc [ 3 ] = 9 ; out . mJc [ 4 ] = 10 ; out . mJc
[ 5 ] = 11 ; out . mJc [ 6 ] = 12 ; out . mJc [ 7 ] = 13 ; out . mJc [ 8 ] =
14 ; out . mJc [ 9 ] = 15 ; out . mJc [ 10 ] = 16 ; out . mJc [ 11 ] = 17 ;
out . mJc [ 12 ] = 18 ; out . mJc [ 13 ] = 19 ; out . mJc [ 14 ] = 20 ; out .
mIr [ 0 ] = 8 ; out . mIr [ 1 ] = 15 ; out . mIr [ 2 ] = 17 ; out . mIr [ 3 ]
= 19 ; out . mIr [ 4 ] = 21 ; out . mIr [ 5 ] = 23 ; out . mIr [ 6 ] = 25 ;
out . mIr [ 7 ] = 17 ; out . mIr [ 8 ] = 18 ; out . mIr [ 9 ] = 22 ; out .
mIr [ 10 ] = 23 ; out . mIr [ 11 ] = 24 ; out . mIr [ 12 ] = 25 ; out . mIr [
13 ] = 15 ; out . mIr [ 14 ] = 26 ; out . mIr [ 15 ] = 16 ; out . mIr [ 16 ]
= 19 ; out . mIr [ 17 ] = 20 ; out . mIr [ 18 ] = 21 ; out . mIr [ 19 ] = 9 ;
( void ) sys ; ( void ) t2 ; return 0 ; }
