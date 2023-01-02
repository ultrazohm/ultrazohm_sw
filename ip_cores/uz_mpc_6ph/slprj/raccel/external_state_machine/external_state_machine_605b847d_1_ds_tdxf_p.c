#include "ne_ds.h"
#include "external_state_machine_605b847d_1_ds_tdxf_p.h"
#include "external_state_machine_605b847d_1_ds_sys_struct.h"
#include "external_state_machine_605b847d_1_ds_externals.h"
#include "external_state_machine_605b847d_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T external_state_machine_605b847d_1_ds_tdxf_p ( const NeDynamicSystem *
sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) {
PmSparsityPattern out ; ( void ) t1 ; out = t2 -> mTDXF_P ; out . mNumCol =
27ULL ; out . mNumRow = 27ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 2 ;
out . mJc [ 2 ] = 7 ; out . mJc [ 3 ] = 7 ; out . mJc [ 4 ] = 11 ; out . mJc
[ 5 ] = 15 ; out . mJc [ 6 ] = 17 ; out . mJc [ 7 ] = 19 ; out . mJc [ 8 ] =
23 ; out . mJc [ 9 ] = 25 ; out . mJc [ 10 ] = 26 ; out . mJc [ 11 ] = 27 ;
out . mJc [ 12 ] = 33 ; out . mJc [ 13 ] = 39 ; out . mJc [ 14 ] = 45 ; out .
mJc [ 15 ] = 51 ; out . mJc [ 16 ] = 57 ; out . mJc [ 17 ] = 63 ; out . mJc [
18 ] = 65 ; out . mJc [ 19 ] = 67 ; out . mJc [ 20 ] = 69 ; out . mJc [ 21 ]
= 71 ; out . mJc [ 22 ] = 73 ; out . mJc [ 23 ] = 75 ; out . mJc [ 24 ] = 81
; out . mJc [ 25 ] = 87 ; out . mJc [ 26 ] = 93 ; out . mJc [ 27 ] = 99 ; out
. mIr [ 0 ] = 0 ; out . mIr [ 1 ] = 8 ; out . mIr [ 2 ] = 1 ; out . mIr [ 3 ]
= 3 ; out . mIr [ 4 ] = 4 ; out . mIr [ 5 ] = 5 ; out . mIr [ 6 ] = 9 ; out .
mIr [ 7 ] = 4 ; out . mIr [ 8 ] = 5 ; out . mIr [ 9 ] = 12 ; out . mIr [ 10 ]
= 14 ; out . mIr [ 11 ] = 4 ; out . mIr [ 12 ] = 5 ; out . mIr [ 13 ] = 13 ;
out . mIr [ 14 ] = 14 ; out . mIr [ 15 ] = 6 ; out . mIr [ 16 ] = 10 ; out .
mIr [ 17 ] = 7 ; out . mIr [ 18 ] = 11 ; out . mIr [ 19 ] = 4 ; out . mIr [
20 ] = 5 ; out . mIr [ 21 ] = 12 ; out . mIr [ 22 ] = 13 ; out . mIr [ 23 ] =
0 ; out . mIr [ 24 ] = 8 ; out . mIr [ 25 ] = 2 ; out . mIr [ 26 ] = 14 ; out
. mIr [ 27 ] = 4 ; out . mIr [ 28 ] = 5 ; out . mIr [ 29 ] = 6 ; out . mIr [
30 ] = 7 ; out . mIr [ 31 ] = 15 ; out . mIr [ 32 ] = 16 ; out . mIr [ 33 ] =
4 ; out . mIr [ 34 ] = 5 ; out . mIr [ 35 ] = 6 ; out . mIr [ 36 ] = 7 ; out
. mIr [ 37 ] = 19 ; out . mIr [ 38 ] = 20 ; out . mIr [ 39 ] = 4 ; out . mIr
[ 40 ] = 5 ; out . mIr [ 41 ] = 6 ; out . mIr [ 42 ] = 7 ; out . mIr [ 43 ] =
21 ; out . mIr [ 44 ] = 22 ; out . mIr [ 45 ] = 4 ; out . mIr [ 46 ] = 5 ;
out . mIr [ 47 ] = 6 ; out . mIr [ 48 ] = 7 ; out . mIr [ 49 ] = 23 ; out .
mIr [ 50 ] = 24 ; out . mIr [ 51 ] = 4 ; out . mIr [ 52 ] = 5 ; out . mIr [
53 ] = 6 ; out . mIr [ 54 ] = 7 ; out . mIr [ 55 ] = 25 ; out . mIr [ 56 ] =
26 ; out . mIr [ 57 ] = 4 ; out . mIr [ 58 ] = 5 ; out . mIr [ 59 ] = 6 ; out
. mIr [ 60 ] = 7 ; out . mIr [ 61 ] = 17 ; out . mIr [ 62 ] = 18 ; out . mIr
[ 63 ] = 15 ; out . mIr [ 64 ] = 16 ; out . mIr [ 65 ] = 17 ; out . mIr [ 66
] = 18 ; out . mIr [ 67 ] = 19 ; out . mIr [ 68 ] = 20 ; out . mIr [ 69 ] =
21 ; out . mIr [ 70 ] = 22 ; out . mIr [ 71 ] = 23 ; out . mIr [ 72 ] = 24 ;
out . mIr [ 73 ] = 25 ; out . mIr [ 74 ] = 26 ; out . mIr [ 75 ] = 10 ; out .
mIr [ 76 ] = 11 ; out . mIr [ 77 ] = 12 ; out . mIr [ 78 ] = 13 ; out . mIr [
79 ] = 15 ; out . mIr [ 80 ] = 19 ; out . mIr [ 81 ] = 10 ; out . mIr [ 82 ]
= 11 ; out . mIr [ 83 ] = 12 ; out . mIr [ 84 ] = 13 ; out . mIr [ 85 ] = 15
; out . mIr [ 86 ] = 21 ; out . mIr [ 87 ] = 10 ; out . mIr [ 88 ] = 11 ; out
. mIr [ 89 ] = 12 ; out . mIr [ 90 ] = 13 ; out . mIr [ 91 ] = 17 ; out . mIr
[ 92 ] = 23 ; out . mIr [ 93 ] = 10 ; out . mIr [ 94 ] = 11 ; out . mIr [ 95
] = 12 ; out . mIr [ 96 ] = 13 ; out . mIr [ 97 ] = 17 ; out . mIr [ 98 ] =
25 ; ( void ) sys ; ( void ) t2 ; return 0 ; }
