#include "ne_ds.h"
#include "external_state_machine_605b847d_1_ds_m_p.h"
#include "external_state_machine_605b847d_1_ds_sys_struct.h"
#include "external_state_machine_605b847d_1_ds_externals.h"
#include "external_state_machine_605b847d_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T external_state_machine_605b847d_1_ds_m_p ( const NeDynamicSystem *
sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) {
PmSparsityPattern out ; ( void ) t1 ; out = t2 -> mM_P ; out . mNumCol =
27ULL ; out . mNumRow = 27ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 1 ;
out . mJc [ 2 ] = 2 ; out . mJc [ 3 ] = 3 ; out . mJc [ 4 ] = 4 ; out . mJc [
5 ] = 5 ; out . mJc [ 6 ] = 6 ; out . mJc [ 7 ] = 7 ; out . mJc [ 8 ] = 8 ;
out . mJc [ 9 ] = 8 ; out . mJc [ 10 ] = 8 ; out . mJc [ 11 ] = 8 ; out . mJc
[ 12 ] = 8 ; out . mJc [ 13 ] = 8 ; out . mJc [ 14 ] = 8 ; out . mJc [ 15 ] =
8 ; out . mJc [ 16 ] = 8 ; out . mJc [ 17 ] = 8 ; out . mJc [ 18 ] = 8 ; out
. mJc [ 19 ] = 8 ; out . mJc [ 20 ] = 8 ; out . mJc [ 21 ] = 8 ; out . mJc [
22 ] = 8 ; out . mJc [ 23 ] = 8 ; out . mJc [ 24 ] = 8 ; out . mJc [ 25 ] = 8
; out . mJc [ 26 ] = 8 ; out . mJc [ 27 ] = 8 ; out . mIr [ 0 ] = 0 ; out .
mIr [ 1 ] = 2 ; out . mIr [ 2 ] = 1 ; out . mIr [ 3 ] = 4 ; out . mIr [ 4 ] =
5 ; out . mIr [ 5 ] = 6 ; out . mIr [ 6 ] = 7 ; out . mIr [ 7 ] = 3 ; ( void
) sys ; ( void ) t2 ; return 0 ; }
