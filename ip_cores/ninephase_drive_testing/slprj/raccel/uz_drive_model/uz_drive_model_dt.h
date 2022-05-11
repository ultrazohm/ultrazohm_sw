#include "ext_types.h"
static DataTypeInfo rtDataTypeInfoTable [ ] = { { "real_T" , 0 , 8 } , {
"real32_T" , 1 , 4 } , { "int8_T" , 2 , 1 } , { "uint8_T" , 3 , 1 } , {
"int16_T" , 4 , 2 } , { "uint16_T" , 5 , 2 } , { "int32_T" , 6 , 4 } , {
"uint32_T" , 7 , 4 } , { "boolean_T" , 8 , 1 } , { "fcn_call_T" , 9 , 0 } , {
"int_T" , 10 , 4 } , { "pointer_T" , 11 , 8 } , { "action_T" , 12 , 8 } , {
"timer_uint32_pair_T" , 13 , 8 } , { "physical_connection" , 14 , 8 } , {
"struct_HojAm3OvRNpWupjoU8kGuE" , 15 , 48 } , { "uint8_T" , 16 , 1 } , {
"int64_T" , 17 , 8 } , { "int32_T" , 18 , 4 } , {
"struct_GuZC7YYZUOK5mseIsYVPMB" , 19 , 96 } , {
"struct_eLgyfQcxb2WnpXMf1nKTTD" , 20 , 96 } , { "uint8_T" , 21 , 1 } , {
"int32_T" , 22 , 4 } , { "int32_T" , 23 , 4 } , { "int64_T" , 24 , 8 } , {
"uint8_T" , 25 , 1 } , { "uint16_T" , 26 , 2 } , { "uint8_T" , 27 , 1 } , {
"int64_T" , 28 , 8 } , { "uint8_T" , 29 , 1 } , { "uint32_T" , 30 , 4 } , {
"uint8_T" , 31 , 1 } , { "uint64_T" , 32 , 8 } , { "int64_T" , 33 , 8 } , {
"char_T" , 34 , 8 } , { "uchar_T" , 35 , 8 } , { "time_T" , 36 , 8 } } ;
static uint_T rtDataTypeSizes [ ] = { sizeof ( real_T ) , sizeof ( real32_T )
, sizeof ( int8_T ) , sizeof ( uint8_T ) , sizeof ( int16_T ) , sizeof (
uint16_T ) , sizeof ( int32_T ) , sizeof ( uint32_T ) , sizeof ( boolean_T )
, sizeof ( fcn_call_T ) , sizeof ( int_T ) , sizeof ( pointer_T ) , sizeof (
action_T ) , 2 * sizeof ( uint32_T ) , sizeof ( int32_T ) , sizeof (
struct_HojAm3OvRNpWupjoU8kGuE ) , sizeof ( uint8_T ) , sizeof ( int64_T ) ,
sizeof ( int32_T ) , sizeof ( struct_GuZC7YYZUOK5mseIsYVPMB ) , sizeof (
struct_eLgyfQcxb2WnpXMf1nKTTD ) , sizeof ( uint8_T ) , sizeof ( int32_T ) ,
sizeof ( int32_T ) , sizeof ( int64_T ) , sizeof ( uint8_T ) , sizeof (
uint16_T ) , sizeof ( uint8_T ) , sizeof ( int64_T ) , sizeof ( uint8_T ) ,
sizeof ( uint32_T ) , sizeof ( uint8_T ) , sizeof ( uint64_T ) , sizeof (
int64_T ) , sizeof ( char_T ) , sizeof ( uchar_T ) , sizeof ( time_T ) } ;
static const char_T * rtDataTypeNames [ ] = { "real_T" , "real32_T" ,
"int8_T" , "uint8_T" , "int16_T" , "uint16_T" , "int32_T" , "uint32_T" ,
"boolean_T" , "fcn_call_T" , "int_T" , "pointer_T" , "action_T" ,
"timer_uint32_pair_T" , "physical_connection" ,
"struct_HojAm3OvRNpWupjoU8kGuE" , "uint8_T" , "int64_T" , "int32_T" ,
"struct_GuZC7YYZUOK5mseIsYVPMB" , "struct_eLgyfQcxb2WnpXMf1nKTTD" , "uint8_T"
, "int32_T" , "int32_T" , "int64_T" , "uint8_T" , "uint16_T" , "uint8_T" ,
"int64_T" , "uint8_T" , "uint32_T" , "uint8_T" , "uint64_T" , "int64_T" ,
"char_T" , "uchar_T" , "time_T" } ; static DataTypeTransition rtBTransitions
[ ] = { { ( char_T * ) ( & rtB . cqr5wxn5sb ) , 0 , 0 , 216 } , { ( char_T *
) ( & rtB . ozrwjzfnca ) , 1 , 0 , 264 } , { ( char_T * ) ( & rtB .
kqxgd32mvf ) , 18 , 0 , 157 } , { ( char_T * ) ( & rtB . fvfmloctub ) , 5 , 0
, 1 } , { ( char_T * ) ( & rtB . mciby2bhmc ) , 3 , 0 , 7 } , { ( char_T * )
( & rtB . jfzsdgbq5e ) , 2 , 0 , 4 } , { ( char_T * ) ( & rtB . dolerm5nyh )
, 8 , 0 , 37 } , { ( char_T * ) ( & rtB . cx41wglw3j . kehk5h5kaa ) , 24 , 0
, 10 } , { ( char_T * ) ( & rtB . cx41wglw3j . gts4dkakcf [ 0 ] ) , 18 , 0 ,
18 } , { ( char_T * ) ( & rtB . jjob4ur221 . kehk5h5kaa ) , 24 , 0 , 10 } , {
( char_T * ) ( & rtB . jjob4ur221 . gts4dkakcf [ 0 ] ) , 18 , 0 , 18 } , { (
char_T * ) ( & rtB . jogryxdnkz . kehk5h5kaa ) , 24 , 0 , 10 } , { ( char_T *
) ( & rtB . jogryxdnkz . gts4dkakcf [ 0 ] ) , 18 , 0 , 18 } , { ( char_T * )
( & rtB . n4cqr1dkmr . kehk5h5kaa ) , 24 , 0 , 10 } , { ( char_T * ) ( & rtB
. n4cqr1dkmr . gts4dkakcf [ 0 ] ) , 18 , 0 , 18 } , { ( char_T * ) ( & rtB .
a13lr3lsi3 . kehk5h5kaa ) , 24 , 0 , 10 } , { ( char_T * ) ( & rtB .
a13lr3lsi3 . gts4dkakcf [ 0 ] ) , 18 , 0 , 18 } , { ( char_T * ) ( & rtB .
jjajpmoyel . kehk5h5kaa ) , 24 , 0 , 10 } , { ( char_T * ) ( & rtB .
jjajpmoyel . gts4dkakcf [ 0 ] ) , 18 , 0 , 18 } , { ( char_T * ) ( & rtB .
ndmeqad3sm . kehk5h5kaa ) , 24 , 0 , 10 } , { ( char_T * ) ( & rtB .
ndmeqad3sm . gts4dkakcf [ 0 ] ) , 18 , 0 , 18 } , { ( char_T * ) ( & rtB .
o0tbmhvpds . kehk5h5kaa ) , 24 , 0 , 10 } , { ( char_T * ) ( & rtB .
o0tbmhvpds . gts4dkakcf [ 0 ] ) , 18 , 0 , 18 } , { ( char_T * ) ( & rtB .
f5mkygzljka . kehk5h5kaa ) , 24 , 0 , 10 } , { ( char_T * ) ( & rtB .
f5mkygzljka . gts4dkakcf [ 0 ] ) , 18 , 0 , 18 } , { ( char_T * ) ( & rtB .
m432cmsuep . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
mdkybjqwpy . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
gpry1jhtuq . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
dh2sbcx1k5 . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
boikvzokby . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
l1oh3i210b . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
fzihwa5jz0 . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
o0k0yxtimm . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
nzetkmjqj1 . gwunl2xrbh [ 0 ] ) , 8 , 0 , 12 } , { ( char_T * ) ( & rtB .
ndadpcsjlu . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
bvam4ywori . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
fpkdn4t3sg . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
itzps5ovbe . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
nnjygkohqv . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
ijklzzyo04 . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
kfdyhargi1 . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
bbywkhmyky . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
mwi1r4mwtx . gwunl2xrbh [ 0 ] ) , 8 , 0 , 12 } , { ( char_T * ) ( & rtB .
hfxpwwyhz1 . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
epl0ubbsvb . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
imuz2bmqa4 . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
a4jyvx22i5 . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
kmk13inloe . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
liod1hodre . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
f52ctbgs3v . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
p4z2y3oxrmd . f3ngbvxvpa ) , 16 , 0 , 1 } , { ( char_T * ) ( & rtB .
obefemx0qd . gwunl2xrbh [ 0 ] ) , 8 , 0 , 12 } , { ( char_T * ) ( & rtB .
biyhxca30f . getzpyfpzt ) , 0 , 0 , 7 } , { ( char_T * ) ( & rtB . msqwmshj2n
. mua04mpyc1 ) , 0 , 0 , 8 } , { ( char_T * ) ( & rtB . msqwmshj2n .
a4vwthkenj ) , 8 , 0 , 1 } , { ( char_T * ) ( & rtB . mzoe5aiivc . getzpyfpzt
) , 0 , 0 , 7 } , { ( char_T * ) ( & rtB . cstc0v1lpw . mua04mpyc1 ) , 0 , 0
, 8 } , { ( char_T * ) ( & rtB . cstc0v1lpw . a4vwthkenj ) , 8 , 0 , 1 } , {
( char_T * ) ( & rtB . azshdeeeiw3 . getzpyfpzt ) , 0 , 0 , 7 } , { ( char_T
* ) ( & rtB . cqjwvwhkzvh . mua04mpyc1 ) , 0 , 0 , 8 } , { ( char_T * ) ( &
rtB . cqjwvwhkzvh . a4vwthkenj ) , 8 , 0 , 1 } , { ( char_T * ) ( & rtDW .
ituktxufmb [ 0 ] ) , 0 , 0 , 370 } , { ( char_T * ) ( & rtDW . pyihjj0xon .
LoggedData ) , 11 , 0 , 38 } , { ( char_T * ) ( & rtDW . ixrsi3erhf [ 0 ] ) ,
1 , 0 , 1119 } , { ( char_T * ) ( & rtDW . kkklfomjr5 [ 0 ] ) , 18 , 0 , 112
} , { ( char_T * ) ( & rtDW . bqjtw0doyx ) , 1 , 0 , 39 } , { ( char_T * ) (
& rtDW . niztd2zg4p [ 0 ] ) , 18 , 0 , 19 } , { ( char_T * ) ( & rtDW .
bi1fzovgs2 ) , 5 , 0 , 1 } , { ( char_T * ) ( & rtDW . llxyyz4q5x ) , 3 , 0 ,
3 } , { ( char_T * ) ( & rtDW . k44l31otpd [ 0 ] ) , 8 , 0 , 123 } , { (
char_T * ) ( & rtDW . azvnw5pvht ) , 21 , 0 , 3 } , { ( char_T * ) ( & rtDW .
fqvcumyba1 ) , 2 , 0 , 6 } , { ( char_T * ) ( & rtDW . bfyezaoly2 ) , 8 , 0 ,
13 } , { ( char_T * ) ( & rtDW . cx41wglw3j . bineo4prgi [ 0 ] ) , 24 , 0 , 8
} , { ( char_T * ) ( & rtDW . cx41wglw3j . bvutux0ucw ) , 2 , 0 , 1 } , { (
char_T * ) ( & rtDW . jjob4ur221 . bineo4prgi [ 0 ] ) , 24 , 0 , 8 } , { (
char_T * ) ( & rtDW . jjob4ur221 . bvutux0ucw ) , 2 , 0 , 1 } , { ( char_T *
) ( & rtDW . jogryxdnkz . bineo4prgi [ 0 ] ) , 24 , 0 , 8 } , { ( char_T * )
( & rtDW . jogryxdnkz . bvutux0ucw ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW
. n4cqr1dkmr . bineo4prgi [ 0 ] ) , 24 , 0 , 8 } , { ( char_T * ) ( & rtDW .
n4cqr1dkmr . bvutux0ucw ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
a13lr3lsi3 . bineo4prgi [ 0 ] ) , 24 , 0 , 8 } , { ( char_T * ) ( & rtDW .
a13lr3lsi3 . bvutux0ucw ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
jjajpmoyel . bineo4prgi [ 0 ] ) , 24 , 0 , 8 } , { ( char_T * ) ( & rtDW .
jjajpmoyel . bvutux0ucw ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
ndmeqad3sm . bineo4prgi [ 0 ] ) , 24 , 0 , 8 } , { ( char_T * ) ( & rtDW .
ndmeqad3sm . bvutux0ucw ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
o0tbmhvpds . bineo4prgi [ 0 ] ) , 24 , 0 , 8 } , { ( char_T * ) ( & rtDW .
o0tbmhvpds . bvutux0ucw ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
f5mkygzljka . bineo4prgi [ 0 ] ) , 24 , 0 , 8 } , { ( char_T * ) ( & rtDW .
f5mkygzljka . bvutux0ucw ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
biyhxca30f . ftf50xwldj ) , 0 , 0 , 1 } , { ( char_T * ) ( & rtDW .
biyhxca30f . ic4jzsnsgd ) , 7 , 0 , 6 } , { ( char_T * ) ( & rtDW .
biyhxca30f . bnbpcxxvih ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
biyhxca30f . e4ertwjipw ) , 8 , 0 , 1 } , { ( char_T * ) ( & rtDW .
msqwmshj2n . ltyokv5jui ) , 0 , 0 , 1 } , { ( char_T * ) ( & rtDW .
msqwmshj2n . dmqhv1kuog ) , 7 , 0 , 2 } , { ( char_T * ) ( & rtDW .
msqwmshj2n . hlqhpqgl5d ) , 10 , 0 , 1 } , { ( char_T * ) ( & rtDW .
msqwmshj2n . dqmv313jji ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
msqwmshj2n . jaldgiolnb ) , 8 , 0 , 1 } , { ( char_T * ) ( & rtDW .
mzoe5aiivc . ftf50xwldj ) , 0 , 0 , 1 } , { ( char_T * ) ( & rtDW .
mzoe5aiivc . ic4jzsnsgd ) , 7 , 0 , 6 } , { ( char_T * ) ( & rtDW .
mzoe5aiivc . bnbpcxxvih ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
mzoe5aiivc . e4ertwjipw ) , 8 , 0 , 1 } , { ( char_T * ) ( & rtDW .
cstc0v1lpw . ltyokv5jui ) , 0 , 0 , 1 } , { ( char_T * ) ( & rtDW .
cstc0v1lpw . dmqhv1kuog ) , 7 , 0 , 2 } , { ( char_T * ) ( & rtDW .
cstc0v1lpw . hlqhpqgl5d ) , 10 , 0 , 1 } , { ( char_T * ) ( & rtDW .
cstc0v1lpw . dqmv313jji ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
cstc0v1lpw . jaldgiolnb ) , 8 , 0 , 1 } , { ( char_T * ) ( & rtDW .
azshdeeeiw3 . ftf50xwldj ) , 0 , 0 , 1 } , { ( char_T * ) ( & rtDW .
azshdeeeiw3 . ic4jzsnsgd ) , 7 , 0 , 6 } , { ( char_T * ) ( & rtDW .
azshdeeeiw3 . bnbpcxxvih ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
azshdeeeiw3 . e4ertwjipw ) , 8 , 0 , 1 } , { ( char_T * ) ( & rtDW .
cqjwvwhkzvh . ltyokv5jui ) , 0 , 0 , 1 } , { ( char_T * ) ( & rtDW .
cqjwvwhkzvh . dmqhv1kuog ) , 7 , 0 , 2 } , { ( char_T * ) ( & rtDW .
cqjwvwhkzvh . hlqhpqgl5d ) , 10 , 0 , 1 } , { ( char_T * ) ( & rtDW .
cqjwvwhkzvh . dqmv313jji ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
cqjwvwhkzvh . jaldgiolnb ) , 8 , 0 , 1 } } ; static DataTypeTransitionTable
rtBTransTable = { 118U , rtBTransitions } ; static DataTypeTransition
rtPTransitions [ ] = { { ( char_T * ) ( & rtP . L_d ) , 0 , 0 , 116 } , { (
char_T * ) ( & rtP . MultiplyState_constMatrix [ 0 ] ) , 1 , 0 , 2412 } , { (
char_T * ) ( & rtP . enb_counter_ge_51_const ) , 5 , 0 , 3 } , { ( char_T * )
( & rtP . Subsystem8_Index ) , 16 , 0 , 30 } , { ( char_T * ) ( & rtP . dq_Y0
[ 0 ] ) , 0 , 0 , 278 } , { ( char_T * ) ( & rtP . _bias_Value ) , 17 , 0 , 9
} , { ( char_T * ) ( & rtP . Constant1_Value_mfqrhuom3x [ 0 ] ) , 23 , 0 ,
181 } , { ( char_T * ) ( & rtP . StateDelay_InitialCondition [ 0 ] ) , 1 , 0
, 457 } , { ( char_T * ) ( & rtP . Output_InitialCondition ) , 5 , 0 , 3 } ,
{ ( char_T * ) ( & rtP . Delay_InitialCondition_h2511jeak5 ) , 8 , 0 , 320 }
, { ( char_T * ) ( & rtP . Constant_Value_isqfwdnanj ) , 2 , 0 , 4 } , { (
char_T * ) ( & rtP . Delay_InitialCondition_locz5doan2 ) , 21 , 0 , 21 } , {
( char_T * ) ( & rtP . cx41wglw3j . out0_Y0 ) , 24 , 0 , 3 } , { ( char_T * )
( & rtP . jjob4ur221 . out0_Y0 ) , 24 , 0 , 3 } , { ( char_T * ) ( & rtP .
jogryxdnkz . out0_Y0 ) , 24 , 0 , 3 } , { ( char_T * ) ( & rtP . n4cqr1dkmr .
out0_Y0 ) , 24 , 0 , 3 } , { ( char_T * ) ( & rtP . a13lr3lsi3 . out0_Y0 ) ,
24 , 0 , 3 } , { ( char_T * ) ( & rtP . jjajpmoyel . out0_Y0 ) , 24 , 0 , 3 }
, { ( char_T * ) ( & rtP . ndmeqad3sm . out0_Y0 ) , 24 , 0 , 3 } , { ( char_T
* ) ( & rtP . o0tbmhvpds . out0_Y0 ) , 24 , 0 , 3 } , { ( char_T * ) ( & rtP
. f5mkygzljka . out0_Y0 ) , 24 , 0 , 3 } , { ( char_T * ) ( & rtP .
biyhxca30f . Pulses_Y0 ) , 0 , 0 , 77 } , { ( char_T * ) ( & rtP . msqwmshj2n
. Pulses_Y0 ) , 0 , 0 , 159 } , { ( char_T * ) ( & rtP . msqwmshj2n .
DirectLookUpTablenD_DiagnosticForOutOfRangeInput ) , 3 , 0 , 1 } , { ( char_T
* ) ( & rtP . mzoe5aiivc . Pulses_Y0 ) , 0 , 0 , 77 } , { ( char_T * ) ( &
rtP . cstc0v1lpw . Pulses_Y0 ) , 0 , 0 , 159 } , { ( char_T * ) ( & rtP .
cstc0v1lpw . DirectLookUpTablenD_DiagnosticForOutOfRangeInput ) , 3 , 0 , 1 }
, { ( char_T * ) ( & rtP . azshdeeeiw3 . Pulses_Y0 ) , 0 , 0 , 77 } , { (
char_T * ) ( & rtP . cqjwvwhkzvh . Pulses_Y0 ) , 0 , 0 , 159 } , { ( char_T *
) ( & rtP . cqjwvwhkzvh . DirectLookUpTablenD_DiagnosticForOutOfRangeInput )
, 3 , 0 , 1 } } ; static DataTypeTransitionTable rtPTransTable = { 30U ,
rtPTransitions } ;
