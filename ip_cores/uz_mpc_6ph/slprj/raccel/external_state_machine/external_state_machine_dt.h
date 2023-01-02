#include "ext_types.h"
static DataTypeInfo rtDataTypeInfoTable [ ] = { { "real_T" , 0 , 8 } , {
"real32_T" , 1 , 4 } , { "int8_T" , 2 , 1 } , { "uint8_T" , 3 , 1 } , {
"int16_T" , 4 , 2 } , { "uint16_T" , 5 , 2 } , { "int32_T" , 6 , 4 } , {
"uint32_T" , 7 , 4 } , { "boolean_T" , 8 , 1 } , { "fcn_call_T" , 9 , 0 } , {
"int_T" , 10 , 4 } , { "pointer_T" , 11 , 8 } , { "action_T" , 12 , 8 } , {
"timer_uint32_pair_T" , 13 , 8 } , { "uint16_T" , 14 , 2 } , { "int32_T" , 15
, 4 } , { "uint32_T" , 16 , 4 } , { "int32_T" , 17 , 4 } , { "int32_T" , 18 ,
4 } , { "int32_T" , 19 , 4 } , { "int32_T" , 20 , 4 } , { "uint32_T" , 21 , 4
} , { "uint32_T" , 22 , 4 } , { "uint16_T" , 23 , 2 } , { "int16_T" , 24 , 2
} , { "int16_T" , 25 , 2 } , { "uint32_T" , 26 , 4 } , { "uint8_T" , 27 , 1 }
, { "uint64_T" , 28 , 8 } , { "int64_T" , 29 , 8 } , { "int64_T" , 30 , 8 } ,
{ "uint32_T" , 31 , 4 } , { "uint32_T" , 32 , 4 } , { "int32_T" , 33 , 4 } ,
{ "uint16_T" , 34 , 2 } , { "uint32_T" , 35 , 4 } , { "uint16_T" , 36 , 2 } ,
{ "int32_T" , 37 , 4 } , { "int32_T" , 38 , 4 } , { "int32_T" , 39 , 4 } , {
"int32_T" , 40 , 4 } , { "uint8_T" , 41 , 1 } , { "uint8_T" , 42 , 1 } , {
"uint8_T" , 43 , 1 } , { "uint8_T" , 44 , 1 } , { "int32_T" , 45 , 4 } , {
"uint32_T" , 46 , 4 } , { "int64_T" , 47 , 8 } , { "uint64_T" , 48 , 8 } } ;
static uint_T rtDataTypeSizes [ ] = { sizeof ( real_T ) , sizeof ( real32_T )
, sizeof ( int8_T ) , sizeof ( uint8_T ) , sizeof ( int16_T ) , sizeof (
uint16_T ) , sizeof ( int32_T ) , sizeof ( uint32_T ) , sizeof ( boolean_T )
, sizeof ( fcn_call_T ) , sizeof ( int_T ) , sizeof ( void * ) , sizeof (
action_T ) , 2 * sizeof ( uint32_T ) , sizeof ( uint16_T ) , sizeof ( int32_T
) , sizeof ( uint32_T ) , sizeof ( int32_T ) , sizeof ( int32_T ) , sizeof (
int32_T ) , sizeof ( int32_T ) , sizeof ( uint32_T ) , sizeof ( uint32_T ) ,
sizeof ( uint16_T ) , sizeof ( int16_T ) , sizeof ( int16_T ) , sizeof (
uint32_T ) , sizeof ( uint8_T ) , sizeof ( uint64_T ) , sizeof ( int64_T ) ,
sizeof ( int64_T ) , sizeof ( uint32_T ) , sizeof ( uint32_T ) , sizeof (
int32_T ) , sizeof ( uint16_T ) , sizeof ( uint32_T ) , sizeof ( uint16_T ) ,
sizeof ( int32_T ) , sizeof ( int32_T ) , sizeof ( int32_T ) , sizeof (
int32_T ) , sizeof ( uint8_T ) , sizeof ( uint8_T ) , sizeof ( uint8_T ) ,
sizeof ( uint8_T ) , sizeof ( int32_T ) , sizeof ( uint32_T ) , sizeof (
int64_T ) , sizeof ( uint64_T ) } ; static const char_T * rtDataTypeNames [ ]
= { "real_T" , "real32_T" , "int8_T" , "uint8_T" , "int16_T" , "uint16_T" ,
"int32_T" , "uint32_T" , "boolean_T" , "fcn_call_T" , "int_T" , "pointer_T" ,
"action_T" , "timer_uint32_pair_T" , "uint16_T" , "int32_T" , "uint32_T" ,
"int32_T" , "int32_T" , "int32_T" , "int32_T" , "uint32_T" , "uint32_T" ,
"uint16_T" , "int16_T" , "int16_T" , "uint32_T" , "uint8_T" , "uint64_T" ,
"int64_T" , "int64_T" , "uint32_T" , "uint32_T" , "int32_T" , "uint16_T" ,
"uint32_T" , "uint16_T" , "int32_T" , "int32_T" , "int32_T" , "int32_T" ,
"uint8_T" , "uint8_T" , "uint8_T" , "uint8_T" , "int32_T" , "uint32_T" ,
"int64_T" , "uint64_T" } ; static DataTypeTransition rtBTransitions [ ] = { {
( char_T * ) ( & rtB . fcozgxup2r ) , 0 , 0 , 160 } , { ( char_T * ) ( & rtB
. clw5wzlj5g ) , 7 , 0 , 66 } , { ( char_T * ) ( & rtB . ci4qtrfbmi ) , 40 ,
0 , 203 } , { ( char_T * ) ( & rtB . abmmtw4kju [ 0 ] ) , 5 , 0 , 13 } , { (
char_T * ) ( & rtB . du0yxgyaqq ) , 3 , 0 , 4 } , { ( char_T * ) ( & rtB .
dnri1ykhvw ) , 8 , 0 , 862 } , { ( char_T * ) ( & rtDW . eqflivmrhn ) , 0 , 0
, 676 } , { ( char_T * ) ( & rtDW . n5dtdvqf3z . LoggedData [ 0 ] ) , 11 , 0
, 97 } , { ( char_T * ) ( & rtDW . ph0vcv3xx3 ) , 7 , 0 , 29 } , { ( char_T *
) ( & rtDW . kqngwowbti ) , 15 , 0 , 297 } , { ( char_T * ) ( & rtDW .
fbbmy1wbzs ) , 21 , 0 , 39 } , { ( char_T * ) ( & rtDW . n5zmidyqtv ) , 33 ,
0 , 13 } , { ( char_T * ) ( & rtDW . pzvmy2vtfc ) , 7 , 0 , 2 } , { ( char_T
* ) ( & rtDW . krkcguglpr ) , 18 , 0 , 8 } , { ( char_T * ) ( & rtDW .
db5evvqnl4 ) , 32 , 0 , 1 } , { ( char_T * ) ( & rtDW . aysrl0xgu4 [ 0 ] ) ,
10 , 0 , 14 } , { ( char_T * ) ( & rtDW . ndgvh0rhxn [ 0 ] ) , 5 , 0 , 7 } ,
{ ( char_T * ) ( & rtDW . proj4kw2yk ) , 3 , 0 , 3 } , { ( char_T * ) ( &
rtDW . msqdvb1oe3 [ 0 ] ) , 8 , 0 , 108 } } ; static DataTypeTransitionTable
rtBTransTable = { 19U , rtBTransitions } ; static DataTypeTransition
rtPTransitions [ ] = { { ( char_T * ) ( & rtP . IB ) , 0 , 0 , 26 } , { (
char_T * ) ( & rtP . CompareToConstant_const ) , 30 , 0 , 1 } , { ( char_T *
) ( & rtP . CompareToConstant_const_lsb3od3rov ) , 28 , 0 , 1 } , { ( char_T
* ) ( & rtP . CompareToConstant_const_p3naxlyak2 ) , 25 , 0 , 1 } , { (
char_T * ) ( & rtP . CompareToConstant_const_frsa0cp1w5 ) , 23 , 0 , 1 } , {
( char_T * ) ( & rtP . DetectRisePositive_vinit ) , 8 , 0 , 14 } , { ( char_T
* ) ( & rtP . Constant30_Value ) , 0 , 0 , 36 } , { ( char_T * ) ( & rtP .
Switch_wrap_Threshold ) , 30 , 0 , 1 } , { ( char_T * ) ( & rtP .
Mod_value_Value ) , 28 , 0 , 3 } , { ( char_T * ) ( & rtP .
Delay14_InitialCondition ) , 17 , 0 , 216 } , { ( char_T * ) ( & rtP .
LookUpTable_tableData [ 0 ] ) , 16 , 0 , 591 } , { ( char_T * ) ( & rtP .
Switch_wrap_Threshold_izyhb3bebo ) , 25 , 0 , 1 } , { ( char_T * ) ( & rtP .
Saturation_UpperSat ) , 14 , 0 , 13 } , { ( char_T * ) ( & rtP .
Constant_Value_jjvoona122 ) , 8 , 0 , 57 } , { ( char_T * ) ( & rtP .
Saturation_UpperSat_nhlfqmn4x4 ) , 27 , 0 , 19 } } ; static
DataTypeTransitionTable rtPTransTable = { 15U , rtPTransitions } ;
