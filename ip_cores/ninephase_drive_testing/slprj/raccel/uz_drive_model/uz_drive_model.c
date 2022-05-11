#include "rt_logging_mmi.h"
#include "uz_drive_model_capi.h"
#include <math.h>
#include "uz_drive_model.h"
#include "uz_drive_model_private.h"
#include "uz_drive_model_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; RTWExtModeInfo * gblRTWExtModeInfo = NULL ; void
raccelForceExtModeShutdown ( boolean_T extModeStartPktReceived ) { if ( !
extModeStartPktReceived ) { boolean_T stopRequested = false ;
rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 6 , & stopRequested ) ; }
rtExtModeShutdown ( 6 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
#include "slsa_sim_engine.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 0 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 1 ; int_T gbl_raccel_NumST = 7 ; const char_T
* gbl_raccel_Version = "10.4 (R2021b) 14-May-2021" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#else
UNUSED_PARAMETER ( S ) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; const int_T gblNumRootInportBlks = 0 ; const int_T
gblNumModelInputs = 0 ; extern const char * gblInportFileName ; extern
rtInportTUtable * gblInportTUtables ; const int_T gblInportDataTypeIdx [ ] =
{ - 1 } ; const int_T gblInportDims [ ] = { - 1 } ; const int_T
gblInportComplex [ ] = { - 1 } ; const int_T gblInportInterpoFlag [ ] = { - 1
} ; const int_T gblInportContinuous [ ] = { - 1 } ; int_T enableFcnCallFlag [
] = { 1 , 1 , 1 , 1 , 1 , 1 , 1 } ; const char *
raccelLoadInputsAndAperiodicHitTimes ( SimStruct * S , const char *
inportFileName , int * matFileFormat ) { return rt_RAccelReadInportsMatFile (
S , inportFileName , matFileFormat ) ; }
#include "simstruc.h"
#include "fixedpoint.h"
#include "slsa_sim_engine.h"
#include "simtarget/slSimTgtSLExecSimBridge.h"
B rtB ; X rtX ; DW rtDW ; PrevZCX rtPrevZCX ; static SimStruct model_S ;
SimStruct * const rtS = & model_S ; real_T look1_pbinlxpw ( real_T u0 , const
real_T bp0 [ ] , const real_T table [ ] , uint32_T prevIndex [ ] , uint32_T
maxIndex ) { real_T frac ; real_T yL_0d0 ; uint32_T bpIdx ; uint32_T found ;
uint32_T iLeft ; uint32_T iRght ; if ( u0 <= bp0 [ 0U ] ) { bpIdx = 0U ; frac
= ( u0 - bp0 [ 0U ] ) / ( bp0 [ 1U ] - bp0 [ 0U ] ) ; } else if ( u0 < bp0 [
maxIndex ] ) { bpIdx = prevIndex [ 0U ] ; iLeft = 0U ; iRght = maxIndex ;
found = 0U ; while ( found == 0U ) { if ( u0 < bp0 [ bpIdx ] ) { iRght =
bpIdx - 1U ; bpIdx = ( ( bpIdx + iLeft ) - 1U ) >> 1U ; } else if ( u0 < bp0
[ bpIdx + 1U ] ) { found = 1U ; } else { iLeft = bpIdx + 1U ; bpIdx = ( (
bpIdx + iRght ) + 1U ) >> 1U ; } } frac = ( u0 - bp0 [ bpIdx ] ) / ( bp0 [
bpIdx + 1U ] - bp0 [ bpIdx ] ) ; } else { bpIdx = maxIndex - 1U ; frac = ( u0
- bp0 [ maxIndex - 1U ] ) / ( bp0 [ maxIndex ] - bp0 [ maxIndex - 1U ] ) ; }
prevIndex [ 0U ] = bpIdx ; yL_0d0 = table [ bpIdx ] ; return ( table [ bpIdx
+ 1U ] - yL_0d0 ) * frac + yL_0d0 ; } void fdvdj1poit ( cz235gejcz * localB ,
gqx2bugedg * localDW , bnof3krbot * localP ) { localDW -> ltyokv5jui = localP
-> UnitDelay_InitialCondition ; localB -> hqezd5t15w [ 0 ] = localP ->
Pulses_Y0 ; localB -> d1n40oandv [ 0 ] = localP -> Pulses_Y0 ; localB ->
hqezd5t15w [ 1 ] = localP -> Pulses_Y0 ; localB -> d1n40oandv [ 1 ] = localP
-> Pulses_Y0 ; localB -> hqezd5t15w [ 2 ] = localP -> Pulses_Y0 ; localB ->
d1n40oandv [ 2 ] = localP -> Pulses_Y0 ; } void pqmhjlfkxs ( gqx2bugedg *
localDW ) { localDW -> jaldgiolnb = false ; } void fndh4y3t0v ( SimStruct *
rtS_p , gqx2bugedg * localDW ) { localDW -> jaldgiolnb = false ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS_p ) ; localDW -> grzcmycdpb
= 0U ; } void cqjwvwhkzv ( SimStruct * rtS_i , boolean_T dy3dvniwgq , real_T
djs0afef4t , real_T hnq1e5wf11 , real_T rtp_Fc , cz235gejcz * localB ,
gqx2bugedg * localDW , bnof3krbot * localP , nrs5bzunb3 * localZCE ) { real_T
azpttdu4al ; real_T cgu2vl4rat_idx_0 ; real_T cgu2vl4rat_idx_1 ; real_T
ecnmtf20lj_idx_0 ; real_T gs1mrj2mat ; real_T hoz5lcpv5e ; real_T iagba4tszh
; real_T izyiioml5y_idx_2 ; int32_T tableOffset ; void * diag ; ZCEventType
zcEvent ; if ( ssIsSampleHit ( rtS_i , 1 , 0 ) && ssIsMajorTimeStep ( rtS_i )
) { if ( dy3dvniwgq ) { if ( ! localDW -> jaldgiolnb ) { if ( ssGetTaskTime (
rtS_i , 1 ) != ssGetTStart ( rtS_i ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS_i ) ; } localDW ->
jaldgiolnb = true ; } } else if ( localDW -> jaldgiolnb ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS_i ) ; pqmhjlfkxs ( localDW )
; } } if ( localDW -> jaldgiolnb ) { azpttdu4al = look1_pbinlxpw ( hnq1e5wf11
, localP -> uDLookupTable_bp01Data , localP -> uDLookupTable_tableData , &
localDW -> dmqhv1kuog , 5U ) ; azpttdu4al = muDoubleScalarFloor ( azpttdu4al
) ; gs1mrj2mat = hnq1e5wf11 - ( azpttdu4al - localP ->
Constant2_Value_g14jlw05vl ) * localP -> Constant1_Value ; ecnmtf20lj_idx_0 =
muDoubleScalarCos ( gs1mrj2mat + localP -> Constant_Value ) * djs0afef4t ;
gs1mrj2mat = djs0afef4t * muDoubleScalarSin ( gs1mrj2mat ) ; hoz5lcpv5e = 1.0
/ rtp_Fc ; izyiioml5y_idx_2 = ( localP -> Constant8_Value - (
ecnmtf20lj_idx_0 + gs1mrj2mat ) ) * hoz5lcpv5e ; if ( muDoubleScalarMod (
azpttdu4al , localP -> Constant1_Value_kmpgskj54q ) >= localP ->
Switch1_Threshold ) { cgu2vl4rat_idx_0 = hoz5lcpv5e * ecnmtf20lj_idx_0 ;
cgu2vl4rat_idx_1 = hoz5lcpv5e * gs1mrj2mat ; } else { cgu2vl4rat_idx_0 =
hoz5lcpv5e * gs1mrj2mat ; cgu2vl4rat_idx_1 = hoz5lcpv5e * ecnmtf20lj_idx_0 ;
} localB -> mua04mpyc1 = muDoubleScalarRem ( ssGetT ( rtS_i ) + localP ->
Constant4_Value , localP -> Constant2_Value ) * localP -> uib2_Gain ;
hoz5lcpv5e = ( ( 2.0 * localB -> mua04mpyc1 - 1.0 ) + 1.0 ) * 0.5 * ( 1.0 /
rtp_Fc ) ; gs1mrj2mat = localP -> u4_Gain * izyiioml5y_idx_2 ;
cgu2vl4rat_idx_0 *= localP -> u2_Gain ; ecnmtf20lj_idx_0 = gs1mrj2mat +
cgu2vl4rat_idx_0 ; cgu2vl4rat_idx_1 *= localP -> u2_Gain_ci0stxvb1g ;
iagba4tszh = ecnmtf20lj_idx_0 + cgu2vl4rat_idx_1 ; izyiioml5y_idx_2 = localP
-> u2_Gain_bktdt40nlr * izyiioml5y_idx_2 + iagba4tszh ; cgu2vl4rat_idx_1 +=
izyiioml5y_idx_2 ; if ( ssIsSampleHit ( rtS_i , 1 , 0 ) ) { zcEvent =
rt_ZCFcn ( ANY_ZERO_CROSSING , & localZCE -> cowinqfkuy , ( localB ->
mua04mpyc1 - localP -> HitCrossing_Offset ) ) ; if ( localDW -> hlqhpqgl5d ==
0 ) { if ( zcEvent != NO_ZCEVENT ) { localB -> a4vwthkenj = ! localB ->
a4vwthkenj ; localDW -> hlqhpqgl5d = 1 ; } else if ( localB -> a4vwthkenj ) {
localB -> a4vwthkenj = ( ( ! ( localB -> mua04mpyc1 != localP ->
HitCrossing_Offset ) ) && localB -> a4vwthkenj ) ; } else { localB ->
a4vwthkenj = ( ( localB -> mua04mpyc1 == localP -> HitCrossing_Offset ) ||
localB -> a4vwthkenj ) ; } } else { localB -> a4vwthkenj = ( ( ! ( localB ->
mua04mpyc1 != localP -> HitCrossing_Offset ) ) && localB -> a4vwthkenj ) ;
localDW -> hlqhpqgl5d = 0 ; } } if ( ssIsSampleHit ( rtS_i , 5 , 0 ) ) {
localB -> ffroit3bl4 = localDW -> ltyokv5jui ; } gs1mrj2mat = ( ( ( ( ( ( (
real_T ) ( hoz5lcpv5e >= gs1mrj2mat ) + localP -> Constant7_Value ) + (
real_T ) ( hoz5lcpv5e >= ecnmtf20lj_idx_0 ) ) + ( real_T ) ( hoz5lcpv5e >=
iagba4tszh ) ) + ( real_T ) ( hoz5lcpv5e >= izyiioml5y_idx_2 ) ) + ( real_T )
( hoz5lcpv5e >= cgu2vl4rat_idx_1 ) ) + ( real_T ) ( hoz5lcpv5e >=
cgu2vl4rat_idx_1 + cgu2vl4rat_idx_0 ) ) - localP ->
Constant2_Value_h0opffki0s ; azpttdu4al -= localP -> Constant3_Value ; if (
azpttdu4al > localP -> Saturation_UpperSat ) { azpttdu4al = localP ->
Saturation_UpperSat ; } else if ( azpttdu4al < localP -> Saturation_LowerSat
) { azpttdu4al = localP -> Saturation_LowerSat ; } hoz5lcpv5e =
muDoubleScalarFloor ( gs1mrj2mat ) ; if ( ( localP ->
DirectLookUpTablenD_DiagnosticForOutOfRangeInput != 0 ) && ( ( ! ( hoz5lcpv5e
>= 0.0 ) ) || ( ! ( hoz5lcpv5e <= 6.0 ) ) ) ) { if ( localP ->
DirectLookUpTablenD_DiagnosticForOutOfRangeInput == 1 ) { if ( localDW ->
grzcmycdpb == 0U ) { diag = CreateDiagnosticAsVoidPtr (
"Simulink:blocks:DirectLookupNdBlockIndexOutOfRangeWarnMsg" , 1 , 5 ,
 "uz_drive_model/Subsystem/SVPWM Generator (2-Level)/Model/SV Modulator Pattern #1/Generate  pulse pattern/Direct Look-Up Table (n-D)"
) ; rt_ssReportDiagnosticAsWarning ( rtS_i , diag ) ; } if ( localDW ->
grzcmycdpb < MAX_uint32_T ) { localDW -> grzcmycdpb ++ ; } } else { diag =
CreateDiagnosticAsVoidPtr (
"Simulink:blocks:DirectLookupNdBlockIndexOutOfRangeErrorMsg" , 1 , 5 ,
 "uz_drive_model/Subsystem/SVPWM Generator (2-Level)/Model/SV Modulator Pattern #1/Generate  pulse pattern/Direct Look-Up Table (n-D)"
) ; rt_ssSet_slErrMsg ( rtS_i , diag ) ; } } hoz5lcpv5e = muDoubleScalarFloor
( azpttdu4al ) ; if ( ( localP ->
DirectLookUpTablenD_DiagnosticForOutOfRangeInput != 0 ) && ( ( ! ( hoz5lcpv5e
>= 0.0 ) ) || ( ! ( hoz5lcpv5e <= 5.0 ) ) ) ) { if ( localP ->
DirectLookUpTablenD_DiagnosticForOutOfRangeInput == 1 ) { if ( localDW ->
grzcmycdpb == 0U ) { diag = CreateDiagnosticAsVoidPtr (
"Simulink:blocks:DirectLookupNdBlockIndexOutOfRangeWarnMsg" , 1 , 5 ,
 "uz_drive_model/Subsystem/SVPWM Generator (2-Level)/Model/SV Modulator Pattern #1/Generate  pulse pattern/Direct Look-Up Table (n-D)"
) ; rt_ssReportDiagnosticAsWarning ( rtS_i , diag ) ; } if ( localDW ->
grzcmycdpb < MAX_uint32_T ) { localDW -> grzcmycdpb ++ ; } } else { diag =
CreateDiagnosticAsVoidPtr (
"Simulink:blocks:DirectLookupNdBlockIndexOutOfRangeErrorMsg" , 1 , 5 ,
 "uz_drive_model/Subsystem/SVPWM Generator (2-Level)/Model/SV Modulator Pattern #1/Generate  pulse pattern/Direct Look-Up Table (n-D)"
) ; rt_ssSet_slErrMsg ( rtS_i , diag ) ; } } if ( muDoubleScalarIsNaN (
azpttdu4al ) ) { hoz5lcpv5e = 0.0 ; } else { hoz5lcpv5e = azpttdu4al ; } if (
muDoubleScalarIsNaN ( gs1mrj2mat ) ) { azpttdu4al = 0.0 ; } else { azpttdu4al
= gs1mrj2mat ; } if ( hoz5lcpv5e > 5.0 ) { hoz5lcpv5e = 5.0 ; } else if (
hoz5lcpv5e < 0.0 ) { hoz5lcpv5e = 0.0 ; } if ( azpttdu4al > 6.0 ) {
azpttdu4al = 6.0 ; } else if ( azpttdu4al < 0.0 ) { azpttdu4al = 0.0 ; }
tableOffset = ( int32_T ) hoz5lcpv5e * 21 + ( int32_T ) azpttdu4al * 3 ;
localB -> hqezd5t15w [ 0 ] = localP -> DirectLookUpTablenD_table [
tableOffset ] ; localB -> hqezd5t15w [ 1 ] = localP ->
DirectLookUpTablenD_table [ tableOffset + 1 ] ; localB -> hqezd5t15w [ 2 ] =
localP -> DirectLookUpTablenD_table [ tableOffset + 2 ] ; localB ->
d1n40oandv [ 0 ] = ! ( localB -> hqezd5t15w [ 0 ] != 0.0 ) ; localB ->
d1n40oandv [ 1 ] = ! ( localB -> hqezd5t15w [ 1 ] != 0.0 ) ; localB ->
d1n40oandv [ 2 ] = ! ( localB -> hqezd5t15w [ 2 ] != 0.0 ) ; if (
ssIsMajorTimeStep ( rtS_i ) ) { srUpdateBC ( localDW -> dqmv313jji ) ; } } }
void cqjwvwhkzvTID6 ( SimStruct * rtS_m , gqx2bugedg * localDW ) { if (
ssIsMajorTimeStep ( rtS_m ) ) { srUpdateBC ( localDW -> dqmv313jji ) ; } }
void px4gj3w5ct ( SimStruct * rtS_i , cz235gejcz * localB , gqx2bugedg *
localDW ) { if ( localDW -> jaldgiolnb && ssIsSampleHit ( rtS_i , 5 , 0 ) ) {
localDW -> ltyokv5jui = localB -> ffroit3bl4 ; } } void nn0sefi01r (
SimStruct * rtS_g , gqx2bugedg * localDW ) { void * diag ; if ( localDW ->
grzcmycdpb != 0U ) { diag = CreateDiagnosticAsVoidPtr (
"Simulink:blocks:DirectLookupNdBlockNumOfIndexOutOfRangeWarnMsg" , 2 , 5 ,
 "uz_drive_model/Subsystem/SVPWM Generator (2-Level)/Model/SV Modulator Pattern #1/Generate  pulse pattern/Direct Look-Up Table (n-D)"
, 1 , localDW -> grzcmycdpb ) ; rt_ssReportDiagnosticAsWarning ( rtS_g , diag
) ; } } void jya45nfjbt ( cog2itxiqj * localB , dqnc2mdlgm * localDW ,
nygobnlzkj * localP ) { localDW -> ftf50xwldj = localP ->
UnitDelay_InitialCondition ; localB -> getzpyfpzt = localP -> Pulses_Y0 ;
localB -> gexcbgcs0i = localP -> Pulses_Y0 ; localB -> da1hylhljz = localP ->
Pulses_Y0 ; localB -> hhdeynni3k = localP -> Pulses_Y0 ; localB -> hx1dswidvn
= localP -> Pulses_Y0 ; localB -> ann0jcq1uk = localP -> Pulses_Y0 ; } void
k0i1quatwd ( dqnc2mdlgm * localDW ) { localDW -> e4ertwjipw = false ; } void
psbttp2yxj ( SimStruct * rtS_p , dqnc2mdlgm * localDW ) { localDW ->
e4ertwjipw = false ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS_p ) ; }
void azshdeeeiw ( SimStruct * rtS_f , boolean_T c3yka0vm44 , real_T
flq35icr02 , real_T g4md3o4lvx , cog2itxiqj * localB , dqnc2mdlgm * localDW ,
nygobnlzkj * localP ) { real_T ks1ivw4lgu ; real_T cw20idgdej ; real_T
fseo0wnstx ; real_T gdky1r5cig ; real_T giwjahjgeb ; real_T jwj21belu2 ;
real_T mng1jitt1w ; real_T oezk3hwccy ; real_T oikf13m5nu ; real_T omsc1p2h0a
; if ( ssIsSampleHit ( rtS_f , 1 , 0 ) && ssIsMajorTimeStep ( rtS_f ) ) { if
( c3yka0vm44 ) { if ( ! localDW -> e4ertwjipw ) { if ( ssGetTaskTime ( rtS_f
, 1 ) != ssGetTStart ( rtS_f ) ) { ssSetBlockStateForSolverChangedAtMajorStep
( rtS_f ) ; } localDW -> e4ertwjipw = true ; } } else if ( localDW ->
e4ertwjipw ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS_f ) ;
k0i1quatwd ( localDW ) ; } } if ( localDW -> e4ertwjipw ) { oezk3hwccy =
look1_pbinlxpw ( g4md3o4lvx , localP ->
LookUpTableDeterminethesectorofUbasedonalpharad_bp01Data , localP ->
LookUpTableDeterminethesectorofUbasedonalpharad_tableData , & localDW ->
ic4jzsnsgd , 5U ) ; oezk3hwccy = muDoubleScalarFloor ( oezk3hwccy ) ;
cw20idgdej = look1_pbinlxpw ( oezk3hwccy , localP -> uDLookupTable_bp01Data ,
localP -> uDLookupTable_tableData , & localDW -> j5itaoriq1 , 5U ) ;
gdky1r5cig = look1_pbinlxpw ( oezk3hwccy , localP -> uDLookupTable1_bp01Data
, localP -> uDLookupTable1_tableData , & localDW -> bjona3wx3v , 5U ) ;
oikf13m5nu = look1_pbinlxpw ( oezk3hwccy , localP -> uDLookupTable2_bp01Data
, localP -> uDLookupTable2_tableData , & localDW -> bldvjsjmit , 5U ) ;
fseo0wnstx = look1_pbinlxpw ( oezk3hwccy , localP -> uDLookupTable3_bp01Data
, localP -> uDLookupTable3_tableData , & localDW -> opg33homib , 5U ) ;
ks1ivw4lgu = localP -> gain_Gain * flq35icr02 ; jwj21belu2 = ks1ivw4lgu *
muDoubleScalarCos ( g4md3o4lvx ) ; giwjahjgeb = ks1ivw4lgu *
muDoubleScalarSin ( g4md3o4lvx ) ; mng1jitt1w = jwj21belu2 * cw20idgdej +
giwjahjgeb * gdky1r5cig ; cw20idgdej = look1_pbinlxpw ( muDoubleScalarRem (
ssGetT ( rtS_f ) + localP -> Constant3_Value , localP -> Constant4_Value ) *
localP -> uib1_Gain , localP -> uDLookupTable_bp01Data_dlxdluyycg , localP ->
uDLookupTable_tableData_jf0tl0zi2n , & localDW -> n4jsnmm3dp , 2U ) ;
omsc1p2h0a = ( ( cw20idgdej - localP -> Constant2_Value ) + 1.0 ) * 0.5 ;
cw20idgdej = ( omsc1p2h0a >= mng1jitt1w ) ; gdky1r5cig = ! ( cw20idgdej !=
0.0 ) ; oikf13m5nu = ( omsc1p2h0a >= ( jwj21belu2 * oikf13m5nu + giwjahjgeb *
fseo0wnstx ) + mng1jitt1w ) ; fseo0wnstx = ! ( oikf13m5nu != 0.0 ) ; if (
oezk3hwccy > localP -> Saturation_UpperSat ) { oezk3hwccy = localP ->
Saturation_UpperSat ; } else if ( oezk3hwccy < localP -> Saturation_LowerSat
) { oezk3hwccy = localP -> Saturation_LowerSat ; } switch ( ( int32_T )
oezk3hwccy ) { case 1 : localB -> getzpyfpzt = localP -> Constant1_Value ;
break ; case 2 : localB -> getzpyfpzt = gdky1r5cig ; break ; case 3 : localB
-> getzpyfpzt = oikf13m5nu ; break ; case 4 : localB -> getzpyfpzt = localP
-> Constant2_Value_kj0t41nl1x ; break ; case 5 : localB -> getzpyfpzt =
cw20idgdej ; break ; default : localB -> getzpyfpzt = fseo0wnstx ; break ; }
localB -> gexcbgcs0i = ! ( localB -> getzpyfpzt != 0.0 ) ; switch ( ( int32_T
) oezk3hwccy ) { case 1 : localB -> da1hylhljz = cw20idgdej ; break ; case 2
: localB -> da1hylhljz = fseo0wnstx ; break ; case 3 : localB -> da1hylhljz =
localP -> Constant1_Value ; break ; case 4 : localB -> da1hylhljz =
gdky1r5cig ; break ; case 5 : localB -> da1hylhljz = oikf13m5nu ; break ;
default : localB -> da1hylhljz = localP -> Constant2_Value_kj0t41nl1x ; break
; } localB -> hhdeynni3k = ! ( localB -> da1hylhljz != 0.0 ) ; switch ( (
int32_T ) oezk3hwccy ) { case 1 : localB -> hx1dswidvn = oikf13m5nu ; break ;
case 2 : localB -> hx1dswidvn = localP -> Constant2_Value_kj0t41nl1x ; break
; case 3 : localB -> hx1dswidvn = cw20idgdej ; break ; case 4 : localB ->
hx1dswidvn = fseo0wnstx ; break ; case 5 : localB -> hx1dswidvn = localP ->
Constant1_Value ; break ; default : localB -> hx1dswidvn = gdky1r5cig ; break
; } localB -> ann0jcq1uk = ! ( localB -> hx1dswidvn != 0.0 ) ; if (
ssIsSampleHit ( rtS_f , 5 , 0 ) ) { localB -> l5rfzkfj5k = localDW ->
ftf50xwldj ; } if ( ssIsMajorTimeStep ( rtS_f ) ) { srUpdateBC ( localDW ->
bnbpcxxvih ) ; } } } void azshdeeeiwTID6 ( SimStruct * rtS_m , dqnc2mdlgm *
localDW ) { if ( ssIsMajorTimeStep ( rtS_m ) ) { srUpdateBC ( localDW ->
bnbpcxxvih ) ; } } void l1bndan4eb ( SimStruct * rtS_c , cog2itxiqj * localB
, dqnc2mdlgm * localDW ) { if ( localDW -> e4ertwjipw && ssIsSampleHit (
rtS_c , 5 , 0 ) ) { localDW -> ftf50xwldj = localB -> l5rfzkfj5k ; } } void
gy5wd21nmz ( const real32_T dcl5qalq3t [ 12 ] , const real32_T md2lseqy24 [ 8
] , kavyiqnma5 * localB ) { localB -> gwunl2xrbh [ 0 ] = ( dcl5qalq3t [ 0 ] +
- 12.0F > 0.8 ) ; localB -> gwunl2xrbh [ 1 ] = ( md2lseqy24 [ 0 ] > 0.5F ) ;
localB -> gwunl2xrbh [ 2 ] = ( - dcl5qalq3t [ 1 ] + - 12.0F > 0.8 ) ; localB
-> gwunl2xrbh [ 3 ] = ( md2lseqy24 [ 1 ] > 0.5F ) ; localB -> gwunl2xrbh [ 4
] = ( - dcl5qalq3t [ 2 ] + - 12.0F > 0.8 ) ; localB -> gwunl2xrbh [ 5 ] = (
md2lseqy24 [ 2 ] > 0.5F ) ; localB -> gwunl2xrbh [ 6 ] = ( dcl5qalq3t [ 1 ] +
- 12.0F > 0.8 ) ; localB -> gwunl2xrbh [ 7 ] = ( md2lseqy24 [ 3 ] > 0.05 ) ;
localB -> gwunl2xrbh [ 8 ] = ( - dcl5qalq3t [ 0 ] + - 12.0F > 0.8 ) ; localB
-> gwunl2xrbh [ 9 ] = ( md2lseqy24 [ 4 ] > 0.5F ) ; localB -> gwunl2xrbh [ 10
] = ( dcl5qalq3t [ 2 ] + - 12.0F > 0.8 ) ; localB -> gwunl2xrbh [ 11 ] = (
md2lseqy24 [ 5 ] > 0.05 ) ; } void p4z2y3oxrm ( const boolean_T oy0pxpnzml [
12 ] , uint8_T enwomtisuj , const boolean_T mprhu3voft [ 12 ] , uint8_T
rtp_Index , c43be0leba * localB ) { int32_T i ; boolean_T iklbauzwio [ 12 ] ;
for ( i = 0 ; i < 12 ; i ++ ) { iklbauzwio [ i ] = oy0pxpnzml [ i ] ^
mprhu3voft [ i ] ; } if ( ( boolean_T ) ( ( boolean_T ) ( ( boolean_T ) ( (
boolean_T ) ( ( boolean_T ) ( ( boolean_T ) ( ( boolean_T ) ( ( boolean_T ) (
( boolean_T ) ( ( boolean_T ) ( ( boolean_T ) ( ( boolean_T ) ( iklbauzwio [
0 ] ^ 1 ) & ( boolean_T ) ( iklbauzwio [ 1 ] ^ 1 ) ) & ( boolean_T ) (
iklbauzwio [ 2 ] ^ 1 ) ) & ( boolean_T ) ( iklbauzwio [ 3 ] ^ 1 ) ) & (
boolean_T ) ( iklbauzwio [ 4 ] ^ 1 ) ) & ( boolean_T ) ( iklbauzwio [ 5 ] ^ 1
) ) & ( boolean_T ) ( iklbauzwio [ 6 ] ^ 1 ) ) & ( boolean_T ) ( iklbauzwio [
7 ] ^ 1 ) ) & ( boolean_T ) ( iklbauzwio [ 8 ] ^ 1 ) ) & ( boolean_T ) (
iklbauzwio [ 9 ] ^ 1 ) ) & ( boolean_T ) ( iklbauzwio [ 10 ] ^ 1 ) ) & (
boolean_T ) ( iklbauzwio [ 11 ] ^ 1 ) ) ) { localB -> f3ngbvxvpa = rtp_Index
; } else { localB -> f3ngbvxvpa = enwomtisuj ; } } void amrcdbjbbq (
ch3csirfgx * localB , f5d5p32bfp * localDW , nytscbbkkv * localP ) { int32_T
i ; for ( i = 0 ; i < 8 ; i ++ ) { localDW -> bineo4prgi [ i ] = localP ->
PipelineRegister_InitialCondition ; } localB -> kehk5h5kaa = localP ->
out0_Y0 ; } void f5mkygzljk ( boolean_T pbf43v0ydb , ch3csirfgx * localB ,
f5d5p32bfp * localDW , nytscbbkkv * localP ) { int64_T lahmjghec3 ; if (
pbf43v0ydb ) { localB -> kehk5h5kaa = localDW -> bineo4prgi [ 0 ] ;
lahmjghec3 = localP -> Constant_Value ; srUpdateBC ( localDW -> bvutux0ucw )
; } } void ipssuqc5xa ( boolean_T pbf43v0ydb , const int32_T go3yyxmtm4 [ 9 ]
, const int32_T mk3rn1uuk1 [ 9 ] , ch3csirfgx * localB , f5d5p32bfp * localDW
) { int64_T tmp ; int32_T i ; if ( pbf43v0ydb ) { tmp = 0LL ; for ( i = 0 ; i
< 9 ; i ++ ) { localB -> pejblvhpwh [ i ] = go3yyxmtm4 [ i ] ; localB ->
gts4dkakcf [ i ] = mk3rn1uuk1 [ i ] ; localB -> jvi14dsw1h [ i ] = ( int64_T
) localB -> pejblvhpwh [ i ] * localB -> gts4dkakcf [ i ] ; tmp += localB ->
jvi14dsw1h [ i ] ; tmp = ( tmp & 4398046511104ULL ) != 0ULL ? tmp | -
4398046511104LL : tmp & 4398046511103LL ; } for ( i = 0 ; i < 7 ; i ++ ) {
localDW -> bineo4prgi [ ( uint32_T ) i ] = localDW -> bineo4prgi [ i + 1U ] ;
} localDW -> bineo4prgi [ 7 ] = tmp ; } } void MdlInitialize ( void ) {
int32_T i ; rtDW . inffcupvx2 = rtP . TmpRTBAtSumInport1_InitialCondition ;
rtX . ptze3ue0cm = rtP . PIDController2_InitialConditionForIntegrator ; rtDW
. p21lrpi51b = rtP . TmpRTBAtSumInport1_InitialCondition_i0245o1ytv ; rtX .
flellzbl1y = rtP . PIDController2_InitialConditionForIntegrator_fepqme2wel ;
rtDW . mpvdclcsce = rtP . TmpRTBAtSubsystem1Inport2_InitialCondition ; rtDW .
hma0f53x5s = rtP . TmpRTBAtSubsystempi2delayInport2_InitialCondition ; rtDW .
fe3ipxqiw5 = rtP . TmpRTBAtuz_inverter_3phInport2_InitialCondition ; rtDW .
kkklfomjr5 [ 0 ] = rtP . Delay_InitialCondition_doutal3110 ; rtDW .
kkklfomjr5 [ 1 ] = rtP . Delay_InitialCondition_doutal3110 ; rtDW .
fqvcumyba1 = rtP . TmpRTBAtEqual1Inport2_InitialCondition ; rtDW . py4iuvrbea
= rtP . Memory_InitialCondition ; rtDW . cgg3v13mlz = rtP .
TmpRTBAtSwitchInport3_InitialCondition ; rtDW . njfpshnpni = rtP .
TmpRTBAtEqual1Inport2_InitialCondition_elqjaja3n4 ; rtDW . a43rt5p5qk = rtP .
Memory_InitialCondition_h50fp4oqpu ; rtDW . ffjft2t0pj = rtP .
TmpRTBAtSwitchInport3_InitialCondition_i4lr0xcxgv ; rtDW . e5cexk5tsa = rtP .
TmpRTBAtuz_inverter_3ph1Inport2_InitialCondition ; rtDW . d2ne5d41vh = rtP .
TmpRTBAtuz_inverter_3ph2Inport2_InitialCondition ; rtDW . ituktxufmb [ 0 ] =
rtP . UnitDelay_InitialCondition ; rtDW . epsbkv53pu [ 0 ] = rtP .
UnitDelay1_InitialCondition ; rtDW . cmh2vel5ym [ 0 ] = rtP .
UnitDelay3_InitialCondition ; rtDW . miazophk3q [ 0 ] = rtP .
DataTypeConversion3_pd1_InitialCondition ; rtDW . ituktxufmb [ 1 ] = rtP .
UnitDelay_InitialCondition ; rtDW . epsbkv53pu [ 1 ] = rtP .
UnitDelay1_InitialCondition ; rtDW . cmh2vel5ym [ 1 ] = rtP .
UnitDelay3_InitialCondition ; rtDW . miazophk3q [ 1 ] = rtP .
DataTypeConversion3_pd1_InitialCondition ; rtDW . ituktxufmb [ 2 ] = rtP .
UnitDelay_InitialCondition ; rtDW . epsbkv53pu [ 2 ] = rtP .
UnitDelay1_InitialCondition ; rtDW . cmh2vel5ym [ 2 ] = rtP .
UnitDelay3_InitialCondition ; rtDW . miazophk3q [ 2 ] = rtP .
DataTypeConversion3_pd1_InitialCondition ; for ( i = 0 ; i < 6 ; i ++ ) {
rtDW . ixrsi3erhf [ i ] = rtP . Add_pd1_InitialCondition ; rtDW . jis1uepreo
[ i ] = rtP . Add1_pd1_InitialCondition ; } for ( i = 0 ; i < 54 ; i ++ ) {
rtDW . fwkxey5epo [ i ] = rtP . DataTypeConversion39_pd1_InitialCondition ; }
rtDW . f4tcd4udur = rtP . delayMatch2_InitialCondition ; rtDW . aoxcwu3qll =
rtP . crp_out_delay1_InitialCondition ; rtDW . cnrqogla5d [ 0 ] = rtP .
DataTypeConversion11_pd1_InitialCondition ; rtDW . aanjcgvfa0 [ 0 ] = rtP .
DataTypeConversion12_pd1_InitialCondition ; rtDW . ctbynjdwij [ 0 ] = rtP .
DataTypeConversion13_pd1_InitialCondition ; rtDW . cnrqogla5d [ 1 ] = rtP .
DataTypeConversion11_pd1_InitialCondition ; rtDW . aanjcgvfa0 [ 1 ] = rtP .
DataTypeConversion12_pd1_InitialCondition ; rtDW . ctbynjdwij [ 1 ] = rtP .
DataTypeConversion13_pd1_InitialCondition ; rtDW . cnrqogla5d [ 2 ] = rtP .
DataTypeConversion11_pd1_InitialCondition ; rtDW . aanjcgvfa0 [ 2 ] = rtP .
DataTypeConversion12_pd1_InitialCondition ; rtDW . ctbynjdwij [ 2 ] = rtP .
DataTypeConversion13_pd1_InitialCondition ; rtDW . ihfcziqcgk = rtP .
crp_out_delay5_InitialCondition ; rtDW . eahq4k0qba = rtP .
crp_out_delay6_InitialCondition ; rtDW . oo31woulsl = rtP .
crp_out_delay7_InitialCondition ; rtDW . blhgrykwvp = rtP .
crp_out_delay8_InitialCondition ; rtDW . osqohvejno = rtP .
crp_out_delay9_InitialCondition ; rtDW . cvcfermial = rtP .
crp_out_delay10_InitialCondition ; rtDW . ocn3tuy1mq = rtP .
crp_out_delay11_InitialCondition ; rtDW . jfrl3cqm1n = rtP .
crp_out_delay3_InitialCondition ; rtDW . gnh32qpzkl [ 0 ] = rtP .
DataTypeConversion14_pd1_InitialCondition ; rtDW . afo0nwhxua [ 0 ] = rtP .
DataTypeConversion141_pd1_InitialCondition ; rtDW . jdtstycpmg [ 0 ] = rtP .
DataTypeConversion15_pd1_InitialCondition ; rtDW . g2ry4vjsj1 [ 0 ] = rtP .
DataTypeConversion16_pd1_InitialCondition ; rtDW . iehvrkddj2 [ 0 ] = rtP .
DataTypeConversion17_pd1_InitialCondition ; rtDW . nbavx35izv [ 0 ] = rtP .
DataTypeConversion18_pd1_InitialCondition ; rtDW . cl1vsftpzn [ 0 ] = rtP .
DataTypeConversion19_pd1_InitialCondition ; rtDW . lhojsnn24m [ 0 ] = rtP .
DataTypeConversion20_pd1_InitialCondition ; rtDW . lzrfskvb50 [ 0 ] = rtP .
DataTypeConversion21_pd1_InitialCondition ; rtDW . kxzyyq15r0 [ 0 ] = rtP .
DataTypeConversion22_pd1_InitialCondition ; rtDW . d42pvxfz0g [ 0 ] = rtP .
DataTypeConversion23_pd1_InitialCondition ; rtDW . ayahx5voca [ 0 ] = rtP .
DataTypeConversion24_pd1_InitialCondition ; rtDW . l2zkdqsp2y [ 0 ] = rtP .
DataTypeConversion25_pd1_InitialCondition ; rtDW . lxk5izw00o [ 0 ] = rtP .
DataTypeConversion26_pd1_InitialCondition ; rtDW . cqp1dau03w [ 0 ] = rtP .
DataTypeConversion27_pd1_InitialCondition ; rtDW . gfiovjo3e2 [ 0 ] = rtP .
DataTypeConversion28_pd1_InitialCondition ; rtDW . p2iwsajmfp [ 0 ] = rtP .
DataTypeConversion29_pd1_InitialCondition ; rtDW . b4auxd1lsk [ 0 ] = rtP .
DataTypeConversion30_pd1_InitialCondition ; rtDW . gnh32qpzkl [ 1 ] = rtP .
DataTypeConversion14_pd1_InitialCondition ; rtDW . afo0nwhxua [ 1 ] = rtP .
DataTypeConversion141_pd1_InitialCondition ; rtDW . jdtstycpmg [ 1 ] = rtP .
DataTypeConversion15_pd1_InitialCondition ; rtDW . g2ry4vjsj1 [ 1 ] = rtP .
DataTypeConversion16_pd1_InitialCondition ; rtDW . iehvrkddj2 [ 1 ] = rtP .
DataTypeConversion17_pd1_InitialCondition ; rtDW . nbavx35izv [ 1 ] = rtP .
DataTypeConversion18_pd1_InitialCondition ; rtDW . cl1vsftpzn [ 1 ] = rtP .
DataTypeConversion19_pd1_InitialCondition ; rtDW . lhojsnn24m [ 1 ] = rtP .
DataTypeConversion20_pd1_InitialCondition ; rtDW . lzrfskvb50 [ 1 ] = rtP .
DataTypeConversion21_pd1_InitialCondition ; rtDW . kxzyyq15r0 [ 1 ] = rtP .
DataTypeConversion22_pd1_InitialCondition ; rtDW . d42pvxfz0g [ 1 ] = rtP .
DataTypeConversion23_pd1_InitialCondition ; rtDW . ayahx5voca [ 1 ] = rtP .
DataTypeConversion24_pd1_InitialCondition ; rtDW . l2zkdqsp2y [ 1 ] = rtP .
DataTypeConversion25_pd1_InitialCondition ; rtDW . lxk5izw00o [ 1 ] = rtP .
DataTypeConversion26_pd1_InitialCondition ; rtDW . cqp1dau03w [ 1 ] = rtP .
DataTypeConversion27_pd1_InitialCondition ; rtDW . gfiovjo3e2 [ 1 ] = rtP .
DataTypeConversion28_pd1_InitialCondition ; rtDW . p2iwsajmfp [ 1 ] = rtP .
DataTypeConversion29_pd1_InitialCondition ; rtDW . b4auxd1lsk [ 1 ] = rtP .
DataTypeConversion30_pd1_InitialCondition ; rtDW . gnh32qpzkl [ 2 ] = rtP .
DataTypeConversion14_pd1_InitialCondition ; rtDW . afo0nwhxua [ 2 ] = rtP .
DataTypeConversion141_pd1_InitialCondition ; rtDW . jdtstycpmg [ 2 ] = rtP .
DataTypeConversion15_pd1_InitialCondition ; rtDW . g2ry4vjsj1 [ 2 ] = rtP .
DataTypeConversion16_pd1_InitialCondition ; rtDW . iehvrkddj2 [ 2 ] = rtP .
DataTypeConversion17_pd1_InitialCondition ; rtDW . nbavx35izv [ 2 ] = rtP .
DataTypeConversion18_pd1_InitialCondition ; rtDW . cl1vsftpzn [ 2 ] = rtP .
DataTypeConversion19_pd1_InitialCondition ; rtDW . lhojsnn24m [ 2 ] = rtP .
DataTypeConversion20_pd1_InitialCondition ; rtDW . lzrfskvb50 [ 2 ] = rtP .
DataTypeConversion21_pd1_InitialCondition ; rtDW . kxzyyq15r0 [ 2 ] = rtP .
DataTypeConversion22_pd1_InitialCondition ; rtDW . d42pvxfz0g [ 2 ] = rtP .
DataTypeConversion23_pd1_InitialCondition ; rtDW . ayahx5voca [ 2 ] = rtP .
DataTypeConversion24_pd1_InitialCondition ; rtDW . l2zkdqsp2y [ 2 ] = rtP .
DataTypeConversion25_pd1_InitialCondition ; rtDW . lxk5izw00o [ 2 ] = rtP .
DataTypeConversion26_pd1_InitialCondition ; rtDW . cqp1dau03w [ 2 ] = rtP .
DataTypeConversion27_pd1_InitialCondition ; rtDW . gfiovjo3e2 [ 2 ] = rtP .
DataTypeConversion28_pd1_InitialCondition ; rtDW . p2iwsajmfp [ 2 ] = rtP .
DataTypeConversion29_pd1_InitialCondition ; rtDW . b4auxd1lsk [ 2 ] = rtP .
DataTypeConversion30_pd1_InitialCondition ; rtDW . kovzbujdnb [ 0 ] = rtP .
DataTypeConversion31_pd1_InitialCondition ; rtDW . kovzbujdnb [ 1 ] = rtP .
DataTypeConversion31_pd1_InitialCondition ; rtDW . kovzbujdnb [ 2 ] = rtP .
DataTypeConversion31_pd1_InitialCondition ; rtDW . dttn4xmcnk [ 0 ] = rtP .
DataTypeConversion32_pd1_InitialCondition ; rtDW . erukb0glgz [ 0 ] = rtP .
DataTypeConversion33_pd1_InitialCondition ; rtDW . n1ap5w5rdi [ 0 ] = rtP .
DataTypeConversion8_pd1_InitialCondition ; rtDW . k44l31otpd [ 0 ] = rtP .
delayMatch14_InitialCondition ; rtDW . ndb122ek3u [ 0 ] = rtP .
delayMatch15_InitialCondition ; rtDW . pdjkbbbzjq [ 0 ] = rtP .
DataTypeConversion331_pd1_InitialCondition ; rtDW . dttn4xmcnk [ 1 ] = rtP .
DataTypeConversion32_pd1_InitialCondition ; rtDW . erukb0glgz [ 1 ] = rtP .
DataTypeConversion33_pd1_InitialCondition ; rtDW . n1ap5w5rdi [ 1 ] = rtP .
DataTypeConversion8_pd1_InitialCondition ; rtDW . k44l31otpd [ 1 ] = rtP .
delayMatch14_InitialCondition ; rtDW . ndb122ek3u [ 1 ] = rtP .
delayMatch15_InitialCondition ; rtDW . pdjkbbbzjq [ 1 ] = rtP .
DataTypeConversion331_pd1_InitialCondition ; rtDW . dttn4xmcnk [ 2 ] = rtP .
DataTypeConversion32_pd1_InitialCondition ; rtDW . erukb0glgz [ 2 ] = rtP .
DataTypeConversion33_pd1_InitialCondition ; rtDW . n1ap5w5rdi [ 2 ] = rtP .
DataTypeConversion8_pd1_InitialCondition ; rtDW . k44l31otpd [ 2 ] = rtP .
delayMatch14_InitialCondition ; rtDW . ndb122ek3u [ 2 ] = rtP .
delayMatch15_InitialCondition ; rtDW . pdjkbbbzjq [ 2 ] = rtP .
DataTypeConversion331_pd1_InitialCondition ; rtDW . bi1fzovgs2 = rtP .
Output_InitialCondition ; rtDW . dzr2rntvvo [ 0 ] = rtP .
Delay1_InitialCondition ; rtDW . dzr2rntvvo [ 1 ] = rtP .
Delay1_InitialCondition ; rtDW . pml0yl52te [ 0 ] = rtP .
DataTypeConversion5_pd1_InitialCondition ; rtDW . pml0yl52te [ 1 ] = rtP .
DataTypeConversion5_pd1_InitialCondition ; rtDW . pml0yl52te [ 2 ] = rtP .
DataTypeConversion5_pd1_InitialCondition ; rtDW . eswvf4pz4v = rtP .
crp_out_delay2_InitialCondition ; rtDW . miwm3apiea [ 0 ] = rtP .
Delay4_InitialCondition ; rtDW . otborblus0 [ 0 ] = rtP .
crp_out_delay12_InitialCondition ; rtDW . jcievkrvvv [ 0 ] = rtP .
Delay5_InitialCondition ; rtDW . ovlbtlz2z5 [ 0 ] = rtP .
crp_out_delay13_InitialCondition ; rtDW . mx1dy0gdum [ 0 ] = rtP .
Delay6_InitialCondition ; rtDW . iygynuhhiw [ 0 ] = rtP .
crp_out_delay14_InitialCondition ; rtDW . miwm3apiea [ 1 ] = rtP .
Delay4_InitialCondition ; rtDW . otborblus0 [ 1 ] = rtP .
crp_out_delay12_InitialCondition ; rtDW . jcievkrvvv [ 1 ] = rtP .
Delay5_InitialCondition ; rtDW . ovlbtlz2z5 [ 1 ] = rtP .
crp_out_delay13_InitialCondition ; rtDW . mx1dy0gdum [ 1 ] = rtP .
Delay6_InitialCondition ; rtDW . iygynuhhiw [ 1 ] = rtP .
crp_out_delay14_InitialCondition ; rtDW . miwm3apiea [ 2 ] = rtP .
Delay4_InitialCondition ; rtDW . otborblus0 [ 2 ] = rtP .
crp_out_delay12_InitialCondition ; rtDW . jcievkrvvv [ 2 ] = rtP .
Delay5_InitialCondition ; rtDW . ovlbtlz2z5 [ 2 ] = rtP .
crp_out_delay13_InitialCondition ; rtDW . mx1dy0gdum [ 2 ] = rtP .
Delay6_InitialCondition ; rtDW . iygynuhhiw [ 2 ] = rtP .
crp_out_delay14_InitialCondition ; rtDW . oamcwpfckc = rtP .
crp_out_delay_InitialCondition_j0kceq3s5o ; rtDW . ifur0qjdev = rtP .
crp_out_delay4_InitialCondition ; for ( i = 0 ; i < 6 ; i ++ ) { rtDW .
pnsuou2020 [ i ] = rtP . Divide_pd1_InitialCondition ; rtDW . opg1thx2qw [ i
] = rtP . Add_pd1_InitialCondition_n1tl5wbe5f ; rtDW . amalc3ffil [ i ] = rtP
. Divide2_pd1_InitialCondition ; rtDW . mwenvz0tar [ i ] = rtP .
Add1_pd1_InitialCondition_jad155jnqy ; rtDW . de3otshxus [ i ] = rtP .
Divide4_pd1_InitialCondition ; rtDW . i2ctd1awel [ i ] = rtP .
Add2_pd1_InitialCondition ; rtDW . ccf5juo5ya [ i ] = rtP .
Divide6_pd1_InitialCondition ; rtDW . i4lkkodfyj [ i ] = rtP .
Add3_pd1_InitialCondition ; rtDW . mdvclm3wpb [ i ] = rtP .
Divide8_pd1_InitialCondition ; rtDW . gai5nv42oe [ i ] = rtP .
Add4_pd1_InitialCondition ; rtDW . imfxseqvvv [ i ] = rtP .
Divide10_pd1_InitialCondition ; rtDW . cxatkad2jz [ i ] = rtP .
Add5_pd1_InitialCondition ; rtDW . ikxzuowx1v [ i ] = rtP .
Divide12_pd1_InitialCondition ; rtDW . bg2vv1po0e [ i ] = rtP .
Add6_pd1_InitialCondition ; rtDW . dmmot30jq4 [ i ] = rtP .
DataTypeConversion1_pd1_InitialCondition ; rtDW . anfxf0zt2u [ i ] = rtP .
Product11_pd1_InitialCondition ; rtDW . al5aajfx21 [ i ] = rtP .
Product6_pd1_InitialCondition ; rtDW . gt3chc0tga [ i ] = rtP .
Product5_pd1_InitialCondition ; rtDW . hoesofthyy [ i ] = rtP .
DataTypeConversion37_pd1_InitialCondition ; rtDW . aw0bxhrzal [ i ] = rtP .
Delay_InitialCondition ; rtDW . estezyunas [ i ] = rtP .
Delay2_InitialCondition ; rtDW . olzifhaukx [ i ] = rtP .
Delay3_InitialCondition ; rtDW . h2z1m5wxiy [ i ] = rtP .
Divide1_pd1_InitialCondition ; rtDW . dviol1u0jv [ i ] = rtP .
Divide11_pd1_InitialCondition ; rtDW . df5ibuzfvl [ i ] = rtP .
Divide13_pd1_InitialCondition ; rtDW . ikv4gqtanm [ i ] = rtP .
Divide3_pd1_InitialCondition ; rtDW . hru10ym4o1 [ i ] = rtP .
Divide5_pd1_InitialCondition ; rtDW . erp5nno2ec [ i ] = rtP .
Divide7_pd1_InitialCondition ; rtDW . ima1cclrzn [ i ] = rtP .
Divide9_pd1_InitialCondition ; rtDW . hm24hbgcg1 [ i ] = rtP .
Sum33_pd1_InitialCondition ; rtDW . ob20xueupt [ i ] = rtP .
Factor_pd1_InitialCondition ; rtDW . phidvr4lhk [ i ] = rtP .
Sum1_stage3_pd1_InitialCondition ; rtDW . atdfcebxbc [ i ] = rtP .
Gain_pd1_InitialCondition ; rtDW . o3sgmp4aev [ i ] = rtP .
Gain1_pd1_InitialCondition ; rtDW . nld3uzo5io [ i ] = rtP .
Sum_stage3_pd1_InitialCondition ; rtDW . fi4wuwmktb [ i ] = rtP .
Gain2_pd1_InitialCondition ; rtDW . gm4ivysliu [ i ] = rtP .
Gain3_pd1_InitialCondition ; rtDW . pyurk4he1k [ i ] = rtP .
Gain4_pd1_InitialCondition ; rtDW . ocff1ayzzn [ i ] = rtP .
Gain5_pd1_InitialCondition ; rtDW . l0rzviqodi [ i ] = rtP .
Gain6_pd1_InitialCondition ; rtDW . o0qik01ouq [ i ] = rtP .
Gain7_pd1_InitialCondition ; rtDW . jci52usrwf [ i ] = rtP .
Gain8_pd1_InitialCondition ; rtDW . n0ifswwd21 [ i ] = rtP .
Gain9_pd1_InitialCondition ; } for ( i = 0 ; i < 9 ; i ++ ) { rtDW .
emh5kwkq0f [ i ] = rtP . Mux_out1_InitialCondition ; } for ( i = 0 ; i < 6 ;
i ++ ) { rtDW . enqlcsixk2 [ i ] = rtP . Product10_pd1_InitialCondition ;
rtDW . bq4gap0f1m [ i ] = rtP . Product_pd1_InitialCondition ; rtDW .
lfuv5ipyfs [ i ] = rtP . Product1_pd1_InitialCondition ; rtDW . f3zvxiekpj [
i ] = rtP . Sum1_pd1_InitialCondition ; } for ( i = 0 ; i < 15 ; i ++ ) {
rtDW . dspkd5mdvs [ i ] = rtP . delayMatch20_InitialCondition ; } for ( i = 0
; i < 6 ; i ++ ) { rtDW . gmymeboquk [ i ] = rtP .
Product2_pd1_InitialCondition ; } for ( i = 0 ; i < 9 ; i ++ ) { rtDW .
bs1nmm0jpl [ i ] = rtP . delayMatch19_InitialCondition ; } rtDW . f0lbp4tqqn
[ 0 ] = rtP . delayMatch16_InitialCondition ; rtDW . f0lbp4tqqn [ 1 ] = rtP .
delayMatch16_InitialCondition ; rtDW . f0lbp4tqqn [ 2 ] = rtP .
delayMatch16_InitialCondition ; for ( i = 0 ; i < 6 ; i ++ ) { rtDW .
bx5vsdt4mt [ i ] = rtP . Product3_pd1_InitialCondition ; rtDW . hjbvl0tg45 [
i ] = rtP . delayMatch18_InitialCondition ; rtDW . nyxm5sdvcd [ i ] = rtP .
Sum2_pd1_InitialCondition ; rtDW . fva2rmvmh4 [ i ] = rtP .
Product7_pd1_InitialCondition ; rtDW . hdlc0qsc4w [ i ] = rtP .
Product8_pd1_InitialCondition ; } for ( i = 0 ; i < 36 ; i ++ ) { rtDW .
ciaqlqmyyx [ i ] = rtP . delayMatch22_InitialCondition ; } for ( i = 0 ; i <
6 ; i ++ ) { rtDW . e1kih03oaj [ i ] = rtP . Product9_pd1_InitialCondition ;
} for ( i = 0 ; i < 27 ; i ++ ) { rtDW . m5gzgpvijm [ i ] = rtP .
Sin_to_sincos_pd1_InitialCondition ; rtDW . o3kxgyy1fj [ i ] = rtP .
Sin_to_sincos_pd2_InitialCondition ; } rtDW . mxawq0evig [ 0 ] = rtP .
delayMatch17_InitialCondition ; rtDW . mxawq0evig [ 1 ] = rtP .
delayMatch17_InitialCondition ; rtDW . mxawq0evig [ 2 ] = rtP .
delayMatch17_InitialCondition ; rtDW . ocwqpyvhqo = rtP .
delayMatch32_InitialCondition ; rtDW . loh1yczrtr = rtP .
delayMatch1_InitialCondition ; rtDW . h5lg5oz5ks [ 0 ] = rtP .
DataTypeConversion1_pd1_InitialCondition_mvexewp4sm ; rtDW . h5lg5oz5ks [ 1 ]
= rtP . DataTypeConversion1_pd1_InitialCondition_mvexewp4sm ; rtDW .
h5lg5oz5ks [ 2 ] = rtP . DataTypeConversion1_pd1_InitialCondition_mvexewp4sm
; for ( i = 0 ; i < 6 ; i ++ ) { rtDW . fl4tijqsrl [ i ] = rtP .
Sum1_stage2_pd1_InitialCondition ; rtDW . e1vdezejb0 [ i ] = rtP .
Sum3_pd1_InitialCondition ; rtDW . nrq4usubsl [ i ] = rtP .
Sum31_pd1_InitialCondition ; rtDW . omuzgpsf1f [ i ] = rtP .
Sum310_pd1_InitialCondition ; rtDW . hys0om0qbu [ i ] = rtP .
Sum32_pd1_InitialCondition ; rtDW . nkf0blmwkl [ i ] = rtP .
delayMatch21_InitialCondition ; rtDW . nr5d4vqt4t [ i ] = rtP .
Sum34_pd1_InitialCondition ; rtDW . cnk414y00k [ i ] = rtP .
Sum35_pd1_InitialCondition ; rtDW . fnpjhtoie0 [ i ] = rtP .
Sum36_pd1_InitialCondition ; rtDW . frvvvscadt [ i ] = rtP .
Sum37_pd1_InitialCondition ; rtDW . pfwwityzhm [ i ] = rtP .
Sum38_pd1_InitialCondition ; rtDW . awvvdj3gzy [ i ] = rtP .
Sum39_pd1_InitialCondition ; rtDW . esrssadyy0 [ i ] = rtP .
Sum_stage2_pd1_InitialCondition ; rtDW . hggmceleiv [ i ] = rtP .
Divide_pd1_InitialCondition_iqg20l45y4 ; } rtDW . cayw42bvqq [ 0 ] = rtP .
DataTypeConversion2_pd1_InitialCondition ; rtDW . cayw42bvqq [ 1 ] = rtP .
DataTypeConversion2_pd1_InitialCondition ; rtDW . cayw42bvqq [ 2 ] = rtP .
DataTypeConversion2_pd1_InitialCondition ; rtDW . fmhxej54hb = rtP .
crp_out_delay_InitialCondition ; for ( i = 0 ; i < 36 ; i ++ ) { rtDW .
pdhtdmqeof [ i ] = rtP . delayMatch23_InitialCondition ; } for ( i = 0 ; i <
39 ; i ++ ) { rtDW . i3xwoxj5zy [ i ] = rtP . delayMatch26_InitialCondition ;
} for ( i = 0 ; i < 6 ; i ++ ) { rtDW . fzberuaezs [ i ] = rtP .
Gain_pd1_InitialCondition_cts3ldlqmt ; rtDW . oiurtflkiv [ i ] = rtP .
Sum3_pd1_InitialCondition_peozyuudyd ; } for ( i = 0 ; i < 18 ; i ++ ) { rtDW
. lth0p1kskk [ i ] = rtP . delayMatch_InitialCondition ; } for ( i = 0 ; i <
6 ; i ++ ) { rtDW . ko0pv0nfnn [ i ] = rtP .
Divide_pd1_InitialCondition_on1tgmlnc5 ; rtDW . kr1btzpdxw [ i ] = rtP .
Divide1_pd1_InitialCondition_nynh3rh5wh ; rtDW . axidhoghf0 [ i ] = rtP .
Divide3_pd1_InitialCondition_mlowt02ilw ; rtDW . pqgou55kzx [ i ] = rtP .
Divide2_pd1_InitialCondition_kdu4cy0gyz ; rtDW . fuh3bn4ezo [ i ] = rtP .
Divide_pd1_InitialCondition_pjuin1ba3m ; rtDW . kzefheif0g [ i ] = rtP .
Divide1_pd1_InitialCondition_jtfnqzsn4k ; rtDW . aa2p00mqis [ i ] = rtP .
Add_pd1_InitialCondition_asnecikhmg ; rtDW . pasm0mbp1y [ i ] = rtP .
Divide2_pd1_InitialCondition_kxizquldvw ; rtDW . jqvl3ulori [ i ] = rtP .
Divide3_pd1_InitialCondition_bk22v0hz40 ; rtDW . jez5q1v2di [ i ] = rtP .
Add1_pd1_InitialCondition_foyb4xrhux ; } for ( i = 0 ; i < 54 ; i ++ ) { rtDW
. az4aq4f2to [ i ] = rtP .
DataTypeConversion28_pd1_InitialCondition_enouvozbat ; } rtDW . hv1tfq2dkg =
rtP . delay_InitialCondition ; for ( i = 0 ; i < 8 ; i ++ ) { rtDW .
lr1nlrmqch [ i ] = rtP . delayMatch_InitialCondition_gw555m4rpr ; rtDW .
a44d5qyg12 [ i ] = rtP . delayMatch1_InitialCondition_pf2zcfdqdf ; } for ( i
= 0 ; i < 18 ; i ++ ) { rtDW . bwkcfpuwid [ i ] = rtP .
delayMatch10_InitialCondition ; rtDW . bb0v2ld5vf [ i ] = rtP .
delayMatch11_InitialCondition ; rtDW . cno1ak0c3c [ i ] = rtP .
delayMatch12_InitialCondition ; rtDW . nxk0ojgi44 [ i ] = rtP .
delayMatch13_InitialCondition ; } for ( i = 0 ; i < 8 ; i ++ ) { rtDW .
bubytbfjvq [ i ] = rtP . delayMatch2_InitialCondition_gxmnquuszr ; } for ( i
= 0 ; i < 18 ; i ++ ) { rtDW . glikpzp24u [ i ] = rtP .
delayMatch24_InitialCondition ; } for ( i = 0 ; i < 57 ; i ++ ) { rtDW .
hskq4vr1qs [ i ] = rtP . delayMatch25_InitialCondition ; } for ( i = 0 ; i <
60 ; i ++ ) { rtDW . htr1ntw0w0 [ i ] = rtP . delayMatch27_InitialCondition ;
rtDW . hljbnnt3zw [ i ] = rtP . delayMatch28_InitialCondition ; rtDW .
d2cg15qgjf [ i ] = rtP . delayMatch29_InitialCondition ; } rtDW . kebzxgfy5a
= rtP . delayMatch30_InitialCondition ; rtDW . pmncprwmz4 = rtP .
delayMatch31_InitialCondition ; rtDW . g05suawwrk = rtP .
delayMatch33_InitialCondition ; rtDW . ore24n4522 = rtP .
delayMatch34_InitialCondition ; rtDW . ckuddxo2v5 [ 0 ] = rtP .
delayMatch35_InitialCondition ; rtDW . hoqlzb3yrr [ 0 ] = rtP .
delayMatch36_InitialCondition ; rtDW . d2yav1jvrg [ 0 ] = rtP .
delayMatch37_InitialCondition ; rtDW . ckuddxo2v5 [ 1 ] = rtP .
delayMatch35_InitialCondition ; rtDW . hoqlzb3yrr [ 1 ] = rtP .
delayMatch36_InitialCondition ; rtDW . d2yav1jvrg [ 1 ] = rtP .
delayMatch37_InitialCondition ; rtDW . ckuddxo2v5 [ 2 ] = rtP .
delayMatch35_InitialCondition ; rtDW . hoqlzb3yrr [ 2 ] = rtP .
delayMatch36_InitialCondition ; rtDW . d2yav1jvrg [ 2 ] = rtP .
delayMatch37_InitialCondition ; rtDW . pdli3lyef1 = rtP .
delayMatch38_InitialCondition ; for ( i = 0 ; i < 8 ; i ++ ) { rtDW .
ir1mqsar5f [ i ] = rtP . delayMatch3_InitialCondition ; rtDW . f1sl003e30 [ i
] = rtP . delayMatch4_InitialCondition ; rtDW . mz1lyyodga [ i ] = rtP .
delayMatch5_InitialCondition ; rtDW . i22hackosr [ i ] = rtP .
delayMatch6_InitialCondition ; } for ( i = 0 ; i < 18 ; i ++ ) { rtDW .
hrf0r3epza [ i ] = rtP . delayMatch7_InitialCondition ; rtDW . l4gldy0ied [ i
] = rtP . delayMatch8_InitialCondition ; rtDW . jcgd4tqv41 [ i ] = rtP .
delayMatch9_InitialCondition ; } amrcdbjbbq ( & rtB . f5mkygzljka , & rtDW .
f5mkygzljka , & rtP . f5mkygzljka ) ; amrcdbjbbq ( & rtB . o0tbmhvpds , &
rtDW . o0tbmhvpds , & rtP . o0tbmhvpds ) ; amrcdbjbbq ( & rtB . jjajpmoyel ,
& rtDW . jjajpmoyel , & rtP . jjajpmoyel ) ; amrcdbjbbq ( & rtB . ndmeqad3sm
, & rtDW . ndmeqad3sm , & rtP . ndmeqad3sm ) ; amrcdbjbbq ( & rtB .
a13lr3lsi3 , & rtDW . a13lr3lsi3 , & rtP . a13lr3lsi3 ) ; amrcdbjbbq ( & rtB
. jogryxdnkz , & rtDW . jogryxdnkz , & rtP . jogryxdnkz ) ; amrcdbjbbq ( &
rtB . jjob4ur221 , & rtDW . jjob4ur221 , & rtP . jjob4ur221 ) ; amrcdbjbbq (
& rtB . n4cqr1dkmr , & rtDW . n4cqr1dkmr , & rtP . n4cqr1dkmr ) ; amrcdbjbbq
( & rtB . cx41wglw3j , & rtDW . cx41wglw3j , & rtP . cx41wglw3j ) ; rtB .
js3yk5ooqs = rtP . alpha_beta_Y0_ops5pd5nfl [ 0 ] ; rtB . b2ae2knt0i = rtP .
alpha_beta_Y0_ops5pd5nfl [ 1 ] ; rtB . pnc3vys3n0 = rtP . alpha_beta_Y0 [ 0 ]
; rtB . mxbllj53re = rtP . alpha_beta_Y0 [ 1 ] ; fdvdj1poit ( & rtB .
cqjwvwhkzvh , & rtDW . cqjwvwhkzvh , & rtP . cqjwvwhkzvh ) ; jya45nfjbt ( &
rtB . azshdeeeiw3 , & rtDW . azshdeeeiw3 , & rtP . azshdeeeiw3 ) ; for ( i =
0 ; i < 6 ; i ++ ) { rtDW . jsu3fijte22m [ i ] = rtP . G_InitialCondition ; }
rtDW . mofgw1cji2 = rtP . Delay_InitialCondition_h2511jeak5 ; rtDW .
npqdzcpz4k = rtP . Output_InitialCondition_k1eifxwcol ; for ( i = 0 ; i < 12
; i ++ ) { rtDW . nz3xkbxksp [ i ] = rtP . StateDelay_InitialCondition [ i ]
; rtDW . cmxd2uv3ip [ i ] = rtP . Delay3_InitialCondition_pz0l4fynfp ; } for
( i = 0 ; i < 5 ; i ++ ) { rtDW . hbtp4braxp [ i ] = rtP .
Delay2_InitialCondition_bawdou0zon ; } rtDW . dq0pmdxppu = rtP .
RateTransition2_InitialCondition ; rtDW . gvxq4lgohv = rtP .
RateTransition1_InitialCondition ; rtDW . hyopdoshjp = rtP .
Delay_InitialCondition_locz5doan2 ; for ( i = 0 ; i < 40 ; i ++ ) { rtDW .
hbomutgs5x [ i ] = rtP . Delay1_InitialCondition_gatgxvvxab ; } for ( i = 0 ;
i < 5 ; i ++ ) { rtDW . ifa1aifv0v [ i ] = rtP .
Delay1_InitialCondition_phnxqmqpfv ; } fdvdj1poit ( & rtB . cstc0v1lpw , &
rtDW . cstc0v1lpw , & rtP . cstc0v1lpw ) ; jya45nfjbt ( & rtB . mzoe5aiivc ,
& rtDW . mzoe5aiivc , & rtP . mzoe5aiivc ) ; fdvdj1poit ( & rtB . msqwmshj2n
, & rtDW . msqwmshj2n , & rtP . msqwmshj2n ) ; jya45nfjbt ( & rtB .
biyhxca30f , & rtDW . biyhxca30f , & rtP . biyhxca30f ) ; rtB . pmyyd40jng =
rtP . dq_Y0_o3qdmlalvk [ 0 ] ; rtB . muhro1pthm = rtP . dq_Y0_o3qdmlalvk [ 1
] ; rtB . hfsnjuqzrn = rtP . dq_Y0 [ 0 ] ; rtB . kt0x35emh1 = rtP . dq_Y0 [ 1
] ; for ( i = 0 ; i < 6 ; i ++ ) { rtDW . jsu3fijte22 [ i ] = rtP .
G_InitialCondition_jxkxj0lwzg ; } rtDW . fmvtpht2wc = rtP .
Delay_InitialCondition_hsyswncslp ; rtDW . bjzrd2jgh1 = rtP .
Output_InitialCondition_p4phx04cq3 ; for ( i = 0 ; i < 12 ; i ++ ) { rtDW .
etncgat1qk [ i ] = rtP . StateDelay_InitialCondition_mi2yczlxa3 [ i ] ; rtDW
. j0pfyx5sl0 [ i ] = rtP . Delay3_InitialCondition_g5eqpjibmj ; } for ( i = 0
; i < 5 ; i ++ ) { rtDW . jlwpaqqpol [ i ] = rtP .
Delay2_InitialCondition_l1s0ro1fve ; } rtDW . anqq4l0npb = rtP .
RateTransition2_InitialCondition_koo3fszowf ; rtDW . mam5vcqfvx = rtP .
RateTransition1_InitialCondition_fmb14y3cnw ; rtDW . avqcisj0g1 = rtP .
Delay_InitialCondition_gboil2iboz ; for ( i = 0 ; i < 40 ; i ++ ) { rtDW .
otdqomronl [ i ] = rtP . Delay1_InitialCondition_opon0r3npu ; } for ( i = 0 ;
i < 5 ; i ++ ) { rtDW . o2nyvbjxnw [ i ] = rtP .
Delay1_InitialCondition_lhskk4uacg ; } for ( i = 0 ; i < 6 ; i ++ ) { rtDW .
jsu3fijte2 [ i ] = rtP . G_InitialCondition_jxkxj0lwzg4 ; } rtDW . lbwbhxgeac
= rtP . Delay_InitialCondition_lwyrt2xv4d ; rtDW . llxyyz4q5x = rtP .
Output_InitialCondition_fsvrv3myjb ; for ( i = 0 ; i < 12 ; i ++ ) { rtDW .
oyxqmd0f4v [ i ] = rtP . StateDelay_InitialCondition_guggx4cua1 [ i ] ; rtDW
. cdd1gh0rmi [ i ] = rtP . Delay3_InitialCondition_ixg4h4ehk2 ; } for ( i = 0
; i < 5 ; i ++ ) { rtDW . lgjrfdubva [ i ] = rtP .
Delay2_InitialCondition_fjvh01tibv ; } rtDW . on2kbwtd1i = rtP .
RateTransition2_InitialCondition_aqmfututeg ; rtDW . myfhgr2zam = rtP .
RateTransition1_InitialCondition_pdphulocq1 ; rtDW . azvnw5pvht = rtP .
Delay_InitialCondition_hk250tgmls ; for ( i = 0 ; i < 40 ; i ++ ) { rtDW .
ayjsmpf3pd [ i ] = rtP . Delay1_InitialCondition_fmarmststv ; } for ( i = 0 ;
i < 5 ; i ++ ) { rtDW . il1i11vhya [ i ] = rtP .
Delay1_InitialCondition_jfqjorsshb ; } } void MdlStart ( void ) { int32_T i ;
{ bool externalInputIsInDatasetFormat = false ; void * pISigstreamManager =
rt_GetISigstreamManager ( rtS ) ;
rtwISigstreamManagerGetInputIsInDatasetFormat ( pISigstreamManager , &
externalInputIsInDatasetFormat ) ; if ( externalInputIsInDatasetFormat ) { }
} { { { bool isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "setp_iq" ) ;
sdiLabelU origSigName = sdiGetLabelFromChars ( "setp_iq" ) ; sdiLabelU
propName = sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath =
sdiGetLabelFromChars ( "uz_drive_model/Subsystem8/Switch" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "setp_iq" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE
; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims .
dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ; srcInfo .
fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. gwqsbwh5jo . AQHandles = sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"0015111f-6101-4fdb-a560-f53bd0be2fb0" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW . gwqsbwh5jo . AQHandles )
{ sdiSetSignalSampleTimeString ( rtDW . gwqsbwh5jo . AQHandles , "Parameter"
, 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime ( rtDW . gwqsbwh5jo .
AQHandles , ssGetTaskTime ( rtS , 6 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . gwqsbwh5jo . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . gwqsbwh5jo . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "" ) ; sdiLabelU origSigName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU propName = sdiGetLabelFromChars ( ""
) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion3" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE
; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims .
dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ; srcInfo .
fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. p3pqosjddk . AQHandles = sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"88f7a20f-e213-4ab5-9268-dfd1944a751d" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW . p3pqosjddk . AQHandles )
{ sdiSetSignalSampleTimeString ( rtDW . p3pqosjddk . AQHandles , "2e-09" ,
2.0E-9 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime ( rtDW . p3pqosjddk .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . p3pqosjddk . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . p3pqosjddk . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "G" ) ; sdiLabelU origSigName =
sdiGetLabelFromChars ( "G" ) ; sdiLabelU propName = sdiGetLabelFromChars ( ""
) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"uz_drive_model/uz_inverter_3ph/Switch1" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "G" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray
[ 1 ] = { 6 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . e0liuhgquprw . AQHandles =
sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "8d45750f-f6df-47d0-83a9-639363872925" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW
. e0liuhgquprw . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW .
e0liuhgquprw . AQHandles , "2e-09" , 2.0E-9 , ssGetTFinal ( rtS ) ) ;
sdiSetRunStartTime ( rtDW . e0liuhgquprw . AQHandles , ssGetTaskTime ( rtS ,
1 ) ) ; sdiAsyncRepoSetSignalExportSettings ( rtDW . e0liuhgquprw . AQHandles
, 1 , 0 ) ; sdiAsyncRepoSetSignalExportName ( rtDW . e0liuhgquprw . AQHandles
, loggedName , origSigName , propName ) ; } sdiFreeLabel ( sigName ) ;
sdiFreeLabel ( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel (
propName ) ; sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ;
sdiFreeLabel ( subPath ) ; } } if ( ! isStreamoutAlreadyRegistered ) { } } }
} { { { bool isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "load_torque" ) ;
sdiLabelU origSigName = sdiGetLabelFromChars ( "load_torque" ) ; sdiLabelU
propName = sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath =
sdiGetLabelFromChars ( "uz_drive_model/Data Type Conversion9" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "load_torque" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_SINGLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE
; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims .
dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ; srcInfo .
fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. ityuo0nupl . AQHandles = sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"f1404354-d105-4eb0-9d2b-c6841f066dd9" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW . ityuo0nupl . AQHandles )
{ sdiSetSignalSampleTimeString ( rtDW . ityuo0nupl . AQHandles , "1e-06" ,
1.0E-6 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime ( rtDW . ityuo0nupl .
AQHandles , ssGetTaskTime ( rtS , 4 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . ityuo0nupl . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . ityuo0nupl . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "outputs" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "outputs" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"uz_drive_model/uz_pmsm_model_9ph" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "outputs" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_SINGLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE ; int_T sigDimsArray [
1 ] = { 5 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . lrdg4xmzak . AQHandles =
sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "50503de7-3661-4d59-8481-4021fdd57db2" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW
. lrdg4xmzak . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . lrdg4xmzak
. AQHandles , "1e-06" , 1.0E-6 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime (
rtDW . lrdg4xmzak . AQHandles , ssGetTaskTime ( rtS , 4 ) ) ;
sdiAsyncRepoSetSignalExportSettings ( rtDW . lrdg4xmzak . AQHandles , 1 , 0 )
; sdiAsyncRepoSetSignalExportName ( rtDW . lrdg4xmzak . AQHandles ,
loggedName , origSigName , propName ) ; } sdiFreeLabel ( sigName ) ;
sdiFreeLabel ( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel (
propName ) ; sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ;
sdiFreeLabel ( subPath ) ; } } if ( ! isStreamoutAlreadyRegistered ) { } } }
} { { { bool isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "output_current" ) ;
sdiLabelU origSigName = sdiGetLabelFromChars ( "output_current" ) ; sdiLabelU
propName = sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath =
sdiGetLabelFromChars ( "uz_drive_model/uz_pmsm_model_9ph" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "output_current" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_SINGLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE
; int_T sigDimsArray [ 1 ] = { 9 } ; sigDims . nDims = 1 ; sigDims .
dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ; srcInfo .
fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 1 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. fkpb3hpobh . AQHandles = sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"2445ee1b-3e66-47c6-a2bc-51f4620ce16a" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW . fkpb3hpobh . AQHandles )
{ sdiSetSignalSampleTimeString ( rtDW . fkpb3hpobh . AQHandles , "1e-06" ,
1.0E-6 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime ( rtDW . fkpb3hpobh .
AQHandles , ssGetTaskTime ( rtS , 4 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . fkpb3hpobh . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . fkpb3hpobh . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "i_abc1" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "i_abc1" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"uz_drive_model/uz_pmsm_model_9ph" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "i_abc1" ) ;
sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoCreateFixedPointDataType_BinaryPointScaling ( 0 , 1 , 25 , 12 ) ;
{ sdiComplexity sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_DISCRETE ; int_T sigDimsArray [ 1 ] = { 3 } ; sigDims . nDims = 1
; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 2 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. euzuyivlcf . AQHandles = sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"585695b0-e8a8-45da-bcdf-a8c0799ea65d" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW . euzuyivlcf . AQHandles )
{ sdiSetSignalSampleTimeString ( rtDW . euzuyivlcf . AQHandles , "1e-06" ,
1.0E-6 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime ( rtDW . euzuyivlcf .
AQHandles , ssGetTaskTime ( rtS , 4 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . euzuyivlcf . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . euzuyivlcf . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "i_abc2" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "i_abc2" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"uz_drive_model/uz_pmsm_model_9ph" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "i_abc2" ) ;
sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoCreateFixedPointDataType_BinaryPointScaling ( 0 , 1 , 25 , 12 ) ;
{ sdiComplexity sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_DISCRETE ; int_T sigDimsArray [ 1 ] = { 3 } ; sigDims . nDims = 1
; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 3 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. hzgoj3w1ci . AQHandles = sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"e163994d-2779-4ed9-a584-4ee84bc7c0bf" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW . hzgoj3w1ci . AQHandles )
{ sdiSetSignalSampleTimeString ( rtDW . hzgoj3w1ci . AQHandles , "1e-06" ,
1.0E-6 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime ( rtDW . hzgoj3w1ci .
AQHandles , ssGetTaskTime ( rtS , 4 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . hzgoj3w1ci . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . hzgoj3w1ci . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "i_abc3" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "i_abc3" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"uz_drive_model/uz_pmsm_model_9ph" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "i_abc3" ) ;
sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoCreateFixedPointDataType_BinaryPointScaling ( 0 , 1 , 25 , 12 ) ;
{ sdiComplexity sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_DISCRETE ; int_T sigDimsArray [ 1 ] = { 3 } ; sigDims . nDims = 1
; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 4 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. k2wlyn1paf . AQHandles = sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"8b59b5ae-9ae0-4d5e-93bc-dd9787fd0b0f" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW . k2wlyn1paf . AQHandles )
{ sdiSetSignalSampleTimeString ( rtDW . k2wlyn1paf . AQHandles , "1e-06" ,
1.0E-6 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime ( rtDW . k2wlyn1paf .
AQHandles , ssGetTaskTime ( rtS , 4 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . k2wlyn1paf . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . k2wlyn1paf . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "out_theta" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "out_theta" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"uz_drive_model/uz_pmsm_model_9ph" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "out_theta" )
; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoCreateFixedPointDataType_BinaryPointScaling ( 0 , 1 , 25 , 12 ) ;
{ sdiComplexity sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_DISCRETE ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims = 1
; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 5 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. f4ugnmm3af . AQHandles = sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"14f8a689-dff5-4d3a-97bb-5fae02309ae7" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW . f4ugnmm3af . AQHandles )
{ sdiSetSignalSampleTimeString ( rtDW . f4ugnmm3af . AQHandles , "1e-06" ,
1.0E-6 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime ( rtDW . f4ugnmm3af .
AQHandles , ssGetTaskTime ( rtS , 4 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . f4ugnmm3af . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . f4ugnmm3af . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "setp_abc2" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "setp_abc2" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"uz_drive_model/Subsystem8/Mux1" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "setp_abc2" )
; sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray
[ 1 ] = { 3 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . lnwwdousnr . AQHandles =
sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "732e1f2b-d601-403d-a0be-9c5f92c20f14" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW
. lnwwdousnr . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . lnwwdousnr
. AQHandles , "2e-09" , 2.0E-9 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime (
rtDW . lnwwdousnr . AQHandles , ssGetTaskTime ( rtS , 1 ) ) ;
sdiAsyncRepoSetSignalExportSettings ( rtDW . lnwwdousnr . AQHandles , 1 , 0 )
; sdiAsyncRepoSetSignalExportName ( rtDW . lnwwdousnr . AQHandles ,
loggedName , origSigName , propName ) ; } sdiFreeLabel ( sigName ) ;
sdiFreeLabel ( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel (
propName ) ; sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ;
sdiFreeLabel ( subPath ) ; } } if ( ! isStreamoutAlreadyRegistered ) { } } }
} { { { bool isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "setp_abc3" ) ;
sdiLabelU origSigName = sdiGetLabelFromChars ( "setp_abc3" ) ; sdiLabelU
propName = sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath =
sdiGetLabelFromChars ( "uz_drive_model/Subsystem8/Mux4" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "setp_abc3" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 3 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. b3y2ruf2y2 . AQHandles = sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"f60ca53e-9132-4f4e-9629-49dc84c752b4" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW . b3y2ruf2y2 . AQHandles )
{ sdiSetSignalSampleTimeString ( rtDW . b3y2ruf2y2 . AQHandles , "2e-09" ,
2.0E-9 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime ( rtDW . b3y2ruf2y2 .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . b3y2ruf2y2 . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . b3y2ruf2y2 . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "setp_abc1" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "setp_abc1" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"uz_drive_model/Subsystem8/Mux" ) ; sdiLabelU blockSID = sdiGetLabelFromChars
( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ;
sdiLabelU sigName = sdiGetLabelFromChars ( "setp_abc1" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray
[ 1 ] = { 3 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . f0zxs3dlyt . AQHandles =
sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "8c4a62e0-960f-4daf-9f73-32571f1e74e2" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW
. f0zxs3dlyt . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . f0zxs3dlyt
. AQHandles , "2e-09" , 2.0E-9 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime (
rtDW . f0zxs3dlyt . AQHandles , ssGetTaskTime ( rtS , 1 ) ) ;
sdiAsyncRepoSetSignalExportSettings ( rtDW . f0zxs3dlyt . AQHandles , 1 , 0 )
; sdiAsyncRepoSetSignalExportName ( rtDW . f0zxs3dlyt . AQHandles ,
loggedName , origSigName , propName ) ; } sdiFreeLabel ( sigName ) ;
sdiFreeLabel ( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel (
propName ) ; sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ;
sdiFreeLabel ( subPath ) ; } } if ( ! isStreamoutAlreadyRegistered ) { } } }
} { { { bool isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "setp_u_d" ) ;
sdiLabelU origSigName = sdiGetLabelFromChars ( "setp_u_d" ) ; sdiLabelU
propName = sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath =
sdiGetLabelFromChars ( "uz_drive_model/Subsystem8/Subsystem2" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "setp_u_d" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. hdsszfpsby . AQHandles = sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"a97bf528-aaff-4bcf-b9d6-dd708fe71df4" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW . hdsszfpsby . AQHandles )
{ sdiSetSignalSampleTimeString ( rtDW . hdsszfpsby . AQHandles , "2e-09" ,
2.0E-9 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime ( rtDW . hdsszfpsby .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . hdsszfpsby . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . hdsszfpsby . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "setp_u_q" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "setp_u_q" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"uz_drive_model/Subsystem8/Subsystem3" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "setp_u_q" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray
[ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . exqvxbdaup . AQHandles =
sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "28aaeb62-3861-4110-bc97-62b107b0af8e" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW
. exqvxbdaup . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . exqvxbdaup
. AQHandles , "2e-09" , 2.0E-9 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime (
rtDW . exqvxbdaup . AQHandles , ssGetTaskTime ( rtS , 1 ) ) ;
sdiAsyncRepoSetSignalExportSettings ( rtDW . exqvxbdaup . AQHandles , 1 , 0 )
; sdiAsyncRepoSetSignalExportName ( rtDW . exqvxbdaup . AQHandles ,
loggedName , origSigName , propName ) ; } sdiFreeLabel ( sigName ) ;
sdiFreeLabel ( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel (
propName ) ; sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ;
sdiFreeLabel ( subPath ) ; } } if ( ! isStreamoutAlreadyRegistered ) { } } }
} { { { bool isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "actual_i_d" ) ;
sdiLabelU origSigName = sdiGetLabelFromChars ( "actual_i_d" ) ; sdiLabelU
propName = sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath =
sdiGetLabelFromChars ( "uz_drive_model/Subsystem8/Subsystem" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "actual_i_d" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE
; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims .
dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ; srcInfo .
fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. ettcurcs0e . AQHandles = sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"dca11233-0a64-44d1-bd74-ae65da1a1b81" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW . ettcurcs0e . AQHandles )
{ sdiSetSignalSampleTimeString ( rtDW . ettcurcs0e . AQHandles , "1e-06" ,
1.0E-6 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime ( rtDW . ettcurcs0e .
AQHandles , ssGetTaskTime ( rtS , 4 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . ettcurcs0e . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . ettcurcs0e . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "actual_i_q" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "actual_i_q" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"uz_drive_model/Subsystem8/Subsystem" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "actual_i_q" )
; sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE ; int_T sigDimsArray [
1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 1 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . c0e12yj12u . AQHandles =
sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "99b6d9cc-3225-4f2f-a39a-664f05568af9" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW
. c0e12yj12u . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . c0e12yj12u
. AQHandles , "1e-06" , 1.0E-6 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime (
rtDW . c0e12yj12u . AQHandles , ssGetTaskTime ( rtS , 4 ) ) ;
sdiAsyncRepoSetSignalExportSettings ( rtDW . c0e12yj12u . AQHandles , 1 , 0 )
; sdiAsyncRepoSetSignalExportName ( rtDW . c0e12yj12u . AQHandles ,
loggedName , origSigName , propName ) ; } sdiFreeLabel ( sigName ) ;
sdiFreeLabel ( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel (
propName ) ; sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ;
sdiFreeLabel ( subPath ) ; } } if ( ! isStreamoutAlreadyRegistered ) { } } }
} { { { bool isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "G" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "G" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"uz_drive_model/uz_inverter_3ph1/Switch1" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "G" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray
[ 1 ] = { 6 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . e0liuhgqupr . AQHandles =
sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "adb56122-053e-4f8b-9caf-470e75c517f8" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW
. e0liuhgqupr . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW .
e0liuhgqupr . AQHandles , "2e-09" , 2.0E-9 , ssGetTFinal ( rtS ) ) ;
sdiSetRunStartTime ( rtDW . e0liuhgqupr . AQHandles , ssGetTaskTime ( rtS , 1
) ) ; sdiAsyncRepoSetSignalExportSettings ( rtDW . e0liuhgqupr . AQHandles ,
1 , 0 ) ; sdiAsyncRepoSetSignalExportName ( rtDW . e0liuhgqupr . AQHandles ,
loggedName , origSigName , propName ) ; } sdiFreeLabel ( sigName ) ;
sdiFreeLabel ( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel (
propName ) ; sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ;
sdiFreeLabel ( subPath ) ; } } if ( ! isStreamoutAlreadyRegistered ) { } } }
} { { { bool isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "G" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "G" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"uz_drive_model/uz_inverter_3ph2/Switch1" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "G" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray
[ 1 ] = { 6 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . e0liuhgqup . AQHandles =
sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "3eff77e2-193d-41ba-8fee-06ef787a0329" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW
. e0liuhgqup . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . e0liuhgqup
. AQHandles , "2e-09" , 2.0E-9 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime (
rtDW . e0liuhgqup . AQHandles , ssGetTaskTime ( rtS , 1 ) ) ;
sdiAsyncRepoSetSignalExportSettings ( rtDW . e0liuhgqup . AQHandles , 1 , 0 )
; sdiAsyncRepoSetSignalExportName ( rtDW . e0liuhgqup . AQHandles ,
loggedName , origSigName , propName ) ; } sdiFreeLabel ( sigName ) ;
sdiFreeLabel ( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel (
propName ) ; sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ;
sdiFreeLabel ( subPath ) ; } } if ( ! isStreamoutAlreadyRegistered ) { } } }
} fndh4y3t0v ( rtS , & rtDW . cqjwvwhkzvh ) ; psbttp2yxj ( rtS , & rtDW .
azshdeeeiw3 ) ; fndh4y3t0v ( rtS , & rtDW . cstc0v1lpw ) ; psbttp2yxj ( rtS ,
& rtDW . mzoe5aiivc ) ; fndh4y3t0v ( rtS , & rtDW . msqwmshj2n ) ; psbttp2yxj
( rtS , & rtDW . biyhxca30f ) ; rtB . d2xswmz51j = rtP .
TmpRTBAtSumInport1_InitialCondition ; rtB . mrvvmxjbsp = rtP .
TmpRTBAtSumInport1_InitialCondition_i0245o1ytv ; rtB . k0tjdml5mw = rtP .
TmpRTBAtSubsystem1Inport2_InitialCondition ; rtDW . gdbbfmmgdg = false ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtB . ei1bavxqil = rtP .
TmpRTBAtSubsystempi2delayInport2_InitialCondition ; rtDW . jd2ppumcjt = false
; ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtB . fmskolgwcb = rtP
. TmpRTBAtuz_inverter_3phInport2_InitialCondition ; for ( i = 0 ; i < 6 ; i
++ ) { rtB . pro0t00oqzlp [ i ] = rtP . G_InitialCondition ; } rtB .
aotbj02q5j = rtP . RateTransition2_InitialCondition ; rtB . fsoxlkgk5l = rtP
. RateTransition1_InitialCondition ; rtB . jfzsdgbq5e = rtP .
TmpRTBAtEqual1Inport2_InitialCondition ; rtB . gqp4loxl10 = rtP .
TmpRTBAtSwitchInport3_InitialCondition ; rtB . myemztkk1m = rtP .
TmpRTBAtEqual1Inport2_InitialCondition_elqjaja3n4 ; rtB . i3srfw2hbe = rtP .
TmpRTBAtSwitchInport3_InitialCondition_i4lr0xcxgv ; rtB . mt1ygms2s1 = rtP .
TmpRTBAtuz_inverter_3ph1Inport2_InitialCondition ; for ( i = 0 ; i < 6 ; i ++
) { rtB . pro0t00oqzl [ i ] = rtP . G_InitialCondition_jxkxj0lwzg ; } rtB .
f1keoylfm3 = rtP . RateTransition2_InitialCondition_koo3fszowf ; rtB .
a1el3w34yn = rtP . RateTransition1_InitialCondition_fmb14y3cnw ; rtB .
aondhpk131 = rtP . TmpRTBAtuz_inverter_3ph2Inport2_InitialCondition ; for ( i
= 0 ; i < 6 ; i ++ ) { rtB . pro0t00oqz [ i ] = rtP .
G_InitialCondition_jxkxj0lwzg4 ; } rtB . kvtifit3ew = rtP .
RateTransition2_InitialCondition_aqmfututeg ; rtB . a3lvlw3afz = rtP .
RateTransition1_InitialCondition_pdphulocq1 ; MdlInitialize ( ) ; } void
MdlOutputs ( int_T tid ) { real_T pywmjctoq0 ; real_T eaqfmjcnca ; real_T
cj0ekrls2n ; real_T j1bjtqkfke ; real_T dmvqitgjzr ; real_T c3nzicj2l0 ;
uint32_T nyh00w3mbc ; uint32_T kc2bmjruge ; uint32_T eem3j5utmn ; real32_T
cq5xhl1pln ; real32_T mbuj01azxx ; real32_T hxx1o3o0xn [ 12 ] ; real32_T
a23umb45gk [ 3 ] ; real32_T dvf40ry3hk [ 8 ] ; real32_T nzdhboavpu [ 12 ] ;
real32_T gbmbic5vi1 [ 3 ] ; real32_T anmq1qibli [ 8 ] ; real32_T oifnvc511t [
12 ] ; real32_T ngicsoxznd [ 3 ] ; real32_T bekkbqozei [ 8 ] ; uint16_T
mmn0zxocgd ; uint16_T okdii0prpb ; uint8_T jyxstc4ejt ; uint8_T enasz1anlw ;
uint8_T kxqrijm5xr ; uint8_T drgpwpv0fx ; uint8_T e4fsbsehu2 ; uint8_T
p5cn5ntxmp ; boolean_T hynlasc1nw ; boolean_T epl2f04eoj [ 12 ] ; boolean_T
dnrpkzm5vi [ 12 ] ; boolean_T dupe3kwjvt [ 12 ] ; int64_T tmp_c ; int64_T
tmp_e ; int64_T tmp_f ; int64_T tmp_g ; int64_T tmp_i ; int64_T tmp_j ;
int64_T tmp_m ; int64_T tmp_p ; real_T ck1wijicgc [ 9 ] ; real_T cv3amtzpeo_p
[ 9 ] ; real_T ksrnub5xfk [ 6 ] ; real_T n5mry0ynam [ 6 ] ; real_T tmp [ 3 ]
; real_T k50sau3xmx [ 2 ] ; real_T baegv5utn3 ; real_T bxdgvixlrj ; real_T
c3e3zs0dtp ; real_T d1rmwt0esq ; real_T dkjmpmrmx0 ; real_T dmsofgutmy ;
real_T dycq312gzw ; real_T e01vrhb3hu ; real_T eeij1wcm5a ; real_T elmssggsl2
; real_T eqwgwo0chw ; real_T fjvdpbi13s ; real_T ftrre2olna ; real_T
fzopdc1y3h ; real_T hfopv1ilcb ; real_T hs3cpomagx ; real_T hsi51z2fza ;
real_T idif3mgiwd ; real_T idv0agripi ; real_T j2bjtltjrv ; real_T jdebb5lusi
; real_T jg31sslk3y ; real_T jjijeib3g5 ; real_T jqy22ktepi ; real_T
jvzpawhyvp ; real_T k1dmmkojfr ; real_T kbjxlva2lq ; real_T kkrhy3nd01 ;
real_T mfxncopstb ; real_T mpbkrymds0 ; real_T n4bzfamly2 ; real_T nskntf0qgz
; real_T nvszulfdmh ; real_T ogbmffm3fg ; real_T okapx5kozs ; real_T
ppdeyph1iv ; real_T pz3ma13zn2 ; int32_T cyymg1pfyn [ 81 ] ; int32_T
nnuffjzjqz [ 3 ] ; int32_T pbrhssinnq [ 3 ] ; int32_T ev43vw1xil_idx_0 ;
int32_T ev43vw1xil_idx_1 ; int32_T ev43vw1xil_idx_2 ; int32_T
gj2rpmenje_idx_0 ; int32_T gj2rpmenje_idx_1 ; int32_T gj2rpmenje_idx_2 ;
int32_T gj2rpmenje_idx_3 ; int32_T gj2rpmenje_idx_4 ; int32_T
gj2rpmenje_idx_5 ; int32_T gj2rpmenje_idx_6 ; int32_T gj2rpmenje_idx_7 ;
int32_T gj2rpmenje_idx_8 ; int32_T grxhuiwehd_idx_0 ; int32_T
grxhuiwehd_idx_1 ; int32_T grxhuiwehd_idx_2 ; int32_T i ; int32_T
l1bmi31zy3_idx_0 ; int32_T l1bmi31zy3_idx_1 ; int32_T l1bmi31zy3_idx_2 ;
real32_T echj2jj5d3 [ 12 ] ; real32_T bdny0r0qld [ 9 ] ; real32_T gn5gtgcxz0
[ 9 ] ; real32_T hixndcwga0 [ 5 ] ; real32_T af42yonrt3 [ 3 ] ; real32_T
dapu0byl3k [ 3 ] ; real32_T mc34jx2fmw [ 3 ] ; real32_T afzdvlkvaw ; real32_T
b0nmwzpz3k ; real32_T bcptyhlhxz ; real32_T bhia010lzv ; real32_T bmq2atwrs0
; real32_T bumwatdafh ; real32_T c10u5tt5g5 ; real32_T cjdf0ewrkr ; real32_T
cpgtcy5yeq ; real32_T cui5hlvqn2 ; real32_T d0hyrjbvrp ; real32_T d0wxlnjlsb
; real32_T d1i4jxgfoj ; real32_T dagdwu0ljw ; real32_T fhbhifl4ec ; real32_T
fwbhsjbvgy ; real32_T hgizml3qp1 ; real32_T iiszzjm1xe_idx_0 ; real32_T
iiszzjm1xe_idx_1 ; real32_T iiszzjm1xe_idx_2 ; real32_T j31e1nzsdd ; real32_T
jbohufsqub ; real32_T jm4jb5nop1 ; real32_T k0k32irma1 ; real32_T
kgqoy5nldi_idx_0 ; real32_T kgqoy5nldi_idx_1 ; real32_T kgqoy5nldi_idx_2 ;
real32_T m0cdt1tutw ; real32_T mkv3qbkou5 ; real32_T mrsi213w3g_idx_0 ;
real32_T mrsi213w3g_idx_1 ; real32_T mrsi213w3g_idx_2 ; real32_T mvfiiz1q5d ;
real32_T nod352cw4v ; real32_T nsgl3oipuf ; real32_T oanngtfv3o ; real32_T u
; real32_T v ; uint8_T av2veoeel0 ; boolean_T cuudaoj10x [ 6 ] ; boolean_T
gj0vg0h2tb [ 6 ] ; boolean_T ltcu0ov5fb [ 6 ] ; boolean_T ehrn3b0ham ;
boolean_T ew0ut03d54 ; boolean_T gl2pknaref ; boolean_T iry4obo3mj ;
srClearBC ( rtDW . cqjwvwhkzvh . dqmv313jji ) ; srClearBC ( rtDW .
azshdeeeiw3 . bnbpcxxvih ) ; srClearBC ( rtDW . i1c4xekdhn ) ; srClearBC (
rtDW . ip0d0t1043 ) ; srClearBC ( rtDW . jitieevvno ) ; srClearBC ( rtDW .
k0efqstpz0 ) ; srClearBC ( rtDW . f5mkygzljka . bvutux0ucw ) ; if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW
. cedwdfuxlq = rtP . Constant3_Value ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) )
{ rtDW . bfyezaoly2 = rtP . simulate_mechanical1_Value ; } } if (
ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . dolerm5nyh = ( rtDW . cedwdfuxlq !=
0.0 ) ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 4 , 0 )
) { rtDW . bqjtw0doyx = rtB . n01lcmfhax ; } if ( ssIsSampleHit ( rtS , 4 , 0
) ) { rtB . bjkenl5zqo = rtDW . bfyezaoly2 ; } if ( ssIsSampleHit ( rtS , 1 ,
0 ) && ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . cc421u2f3f = rtB . klks1betwn
; } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . ozrwjzfnca = rtDW .
bqjtw0doyx ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 4
, 0 ) ) { rtDW . pdjafikrtl = rtB . apfmql0sei ; } if ( ssIsSampleHit ( rtS ,
4 , 0 ) ) { rtB . hv5ezjmgeo = rtDW . cc421u2f3f ; } if ( ssIsSampleHit ( rtS
, 1 , 0 ) && ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . pojlxrwx0d = rtB .
axfg3xmtsw ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . fqxsmb4jyk = rtDW
. pdjafikrtl ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS ,
4 , 0 ) ) { rtDW . m4fnnxykzj = rtB . ezj0gynpe2 ; } if ( ssIsSampleHit ( rtS
, 4 , 0 ) ) { rtB . nftvdrrocl = rtDW . pojlxrwx0d ; } if ( ssIsSampleHit (
rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . k40ux0ctpf = rtB .
c5qcb5u3xz ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . pqtimdb5j0 = rtDW
. m4fnnxykzj ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS ,
4 , 0 ) ) { rtDW . kvknfbkwvk = rtB . dmg5kd4tx3 ; } if ( ssIsSampleHit ( rtS
, 4 , 0 ) ) { rtB . bmvpiaropc = rtDW . k40ux0ctpf ; } if ( ssIsSampleHit (
rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . by04uer2xp = rtB .
kh313ui5yr ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . msybf1i1ih = rtDW
. kvknfbkwvk ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS ,
4 , 0 ) ) { rtDW . n1vlvivlrx = rtB . hvql1wzp1l ; } if ( ssIsSampleHit ( rtS
, 4 , 0 ) ) { rtB . ctfswtdkgy = rtDW . by04uer2xp ; } if ( ssIsSampleHit (
rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . ib3g0mc4j4 = rtB .
ibyskbyf12 ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . famzz0eg5w = rtDW
. n1vlvivlrx ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS ,
4 , 0 ) ) { rtDW . c3coe5r3z1 = rtB . fxv4zcsfc1 ; } if ( ssIsSampleHit ( rtS
, 4 , 0 ) ) { rtB . lt1czm1uxp = rtDW . ib3g0mc4j4 ; } if ( ssIsSampleHit (
rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . gopfnpfdpo = rtB .
bvmuyedlcu ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . o4hoccuzjr = rtDW
. c3coe5r3z1 ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS ,
4 , 0 ) ) { rtDW . fhefxq1ozn = rtB . op5yeerppz ; } if ( ssIsSampleHit ( rtS
, 4 , 0 ) ) { rtB . bnaxt4mwdx = rtDW . gopfnpfdpo ; rtB . du0uth4oge = rtDW
. fhefxq1ozn ; } if ( ssGetTaskTime ( rtS , 0 ) < rtP . Step1_Time ) { rtB .
cqr5wxn5sb = rtP . Step1_Y0 ; } else { rtB . cqr5wxn5sb = rtP . Step1_YFinal
; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( ssIsSampleHit ( rtS , 4 , 0 )
) { rtDW . ny5tmca5u1 = rtB . cqr5wxn5sb ; } if ( ssIsSampleHit ( rtS , 4 , 0
) ) { rtDW . k3sz0zxcz4 = rtP . omega_mech1_Value ; } } if ( ssIsSampleHit (
rtS , 4 , 0 ) ) { rtB . iuri1z2qfy = ( real32_T ) rtDW . ny5tmca5u1 ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW .
hafwy3njkc = rtP . ud_Value ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB .
cgssfsafy3 = ( real32_T ) rtDW . k3sz0zxcz4 ; } if ( ssIsSampleHit ( rtS , 1
, 0 ) && ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . gqa5jm0r2v = rtP . uq_Value
; } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . bfmnddev3o = ( real32_T )
rtDW . hafwy3njkc ; rtB . fwt504l0fp = ( real32_T ) rtDW . gqa5jm0r2v ; } if
( ssIsSampleHit ( rtS , 1 , 0 ) ) { k1dmmkojfr = rtDW . miazophk3q [ 0 ] ; {
if ( rtDW . p3pqosjddk . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . p3pqosjddk . AQHandles , ssGetTaskTime ( rtS , 1 ) ,
( char * ) & k1dmmkojfr + 0 ) ; } } rtB . haranx30a5 [ 0 ] = rtB . iuri1z2qfy
; rtB . haranx30a5 [ 1 ] = rtB . cgssfsafy3 ; rtB . haranx30a5 [ 2 ] = rtB .
bfmnddev3o ; rtB . haranx30a5 [ 3 ] = rtB . fwt504l0fp ; for ( i = 0 ; i < 9
; i ++ ) { bdny0r0qld [ i ] = rtDW . fwkxey5epo [ i ] ; } if ( rtB .
bjkenl5zqo ) { gn5gtgcxz0 [ 0 ] = rtB . haranx30a5 [ 2 ] ; gn5gtgcxz0 [ 1 ] =
rtB . haranx30a5 [ 3 ] ; gn5gtgcxz0 [ 2 ] = rtP . Constant_Value_hlt3aiqgcy ;
gn5gtgcxz0 [ 3 ] = rtP . Constant_Value_hlt3aiqgcy ; gn5gtgcxz0 [ 4 ] = rtP .
Constant_Value_hlt3aiqgcy ; gn5gtgcxz0 [ 5 ] = rtP .
Constant_Value_hlt3aiqgcy ; gn5gtgcxz0 [ 6 ] = rtP .
Constant_Value_hlt3aiqgcy ; gn5gtgcxz0 [ 7 ] = rtP .
Constant_Value_hlt3aiqgcy ; gn5gtgcxz0 [ 8 ] = rtP .
Constant_Value_hlt3aiqgcy ; } else { gn5gtgcxz0 [ 0 ] = rtDW . ixrsi3erhf [ 0
] ; gn5gtgcxz0 [ 1 ] = rtDW . jis1uepreo [ 0 ] ; for ( i = 0 ; i < 7 ; i ++ )
{ gn5gtgcxz0 [ i + 2 ] = bdny0r0qld [ i + 2 ] ; } } rtB . ardjnl10dt =
gn5gtgcxz0 [ 2 ] - rtDW . pnsuou2020 [ 0 ] ; oanngtfv3o = rtDW . opg1thx2qw [
0 ] ; rtB . jf1dkqak4i = gn5gtgcxz0 [ 3 ] - rtDW . amalc3ffil [ 0 ] ;
cui5hlvqn2 = rtDW . mwenvz0tar [ 0 ] ; rtB . lvqyun4ml4 = gn5gtgcxz0 [ 4 ] -
rtDW . de3otshxus [ 0 ] ; bmq2atwrs0 = rtDW . i2ctd1awel [ 0 ] ; rtB .
mr5jvkeea4 = gn5gtgcxz0 [ 5 ] - rtDW . ccf5juo5ya [ 0 ] ; jbohufsqub = rtDW .
i4lkkodfyj [ 0 ] ; rtB . glnkapw4oj = gn5gtgcxz0 [ 6 ] - rtDW . mdvclm3wpb [
0 ] ; mvfiiz1q5d = rtDW . gai5nv42oe [ 0 ] ; rtB . fclle0plbx = gn5gtgcxz0 [
7 ] - rtDW . imfxseqvvv [ 0 ] ; afzdvlkvaw = rtDW . cxatkad2jz [ 0 ] ; rtB .
nlrhqopjdv = gn5gtgcxz0 [ 8 ] - rtDW . ikxzuowx1v [ 0 ] ; cjdf0ewrkr = rtDW .
bg2vv1po0e [ 0 ] ; bcptyhlhxz = rtDW . f4tcd4udur ; u = rtDW . f4tcd4udur *
4096.0F ; v = muSingleScalarAbs ( u ) ; if ( v < 8.388608E+6F ) { if ( v >=
0.5F ) { u = muSingleScalarFloor ( u + 0.5F ) ; } else { u *= 0.0F ; } } if (
muSingleScalarIsNaN ( u ) || muSingleScalarIsInf ( u ) ) { u = 0.0F ; } else
{ u = muSingleScalarRem ( u , 3.3554432E+7F ) ; } i = ( int32_T )
muSingleScalarFloor ( u ) ; rtB . ljbz13eall = ( i & 16777216U ) != 0U ? i |
- 16777216 : i & 16777215 ; rtB . bi5qzktbi4 = rtDW . dmmot30jq4 [ 0 ] ; rtB
. nahffw1fqn = rtB . hv5ezjmgeo ; rtB . pgp2ddnfdk = rtDW . cnrqogla5d [ 0 ]
; rtB . lup5lr2jvb = rtB . fqxsmb4jyk ; d1rmwt0esq = rtDW . aanjcgvfa0 [ 0 ]
; if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . jayew5vh20 = rtDW .
aoxcwu3qll ; } } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . jnpfxzq53a =
rtDW . jayew5vh20 ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( rtB .
dolerm5nyh ) { rtB . jqoi3hd2f5 = rtP . Initial_Val2_Value ; } else { rtB .
jqoi3hd2f5 = rtB . jnpfxzq53a ; } rtB . bqib1cp1cj = ( real32_T ) rtB .
jqoi3hd2f5 ; rtB . oj1n41111k = rtDW . ctbynjdwij [ 0 ] ; rtB . olgy0iynok =
rtDW . anfxf0zt2u [ 0 ] ; bxdgvixlrj = rtDW . gnh32qpzkl [ 0 ] ; if (
ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . gtl5stszrm = rtDW . ihfcziqcgk ; } }
if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . eztey41xwv = rtDW . gtl5stszrm ;
} if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( rtB . dolerm5nyh ) { kbjxlva2lq
= rtP . Initial_Val3_Value ; } else { kbjxlva2lq = rtB . eztey41xwv ; } rtB .
gxiz1fefsk = ( real32_T ) kbjxlva2lq ; k0k32irma1 = rtDW . afo0nwhxua [ 0 ] ;
if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . pacgla51lq = rtDW . eahq4k0qba
; } } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . lkk5omnvvt = rtDW .
pacgla51lq ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( rtB . dolerm5nyh )
{ c3e3zs0dtp = rtP . Initial_Val4_Value ; } else { c3e3zs0dtp = rtB .
lkk5omnvvt ; } rtB . ozq3nsiak4 = ( real32_T ) c3e3zs0dtp ; cpgtcy5yeq = rtDW
. jdtstycpmg [ 0 ] ; if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . jntfw1jmxj
= rtDW . oo31woulsl ; } } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB .
fevhynkzve = rtDW . jntfw1jmxj ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if
( rtB . dolerm5nyh ) { dkjmpmrmx0 = rtP . Initial_Val5_Value ; } else {
dkjmpmrmx0 = rtB . fevhynkzve ; } rtB . fxar2syvnw = ( real32_T ) dkjmpmrmx0
; j31e1nzsdd = rtDW . g2ry4vjsj1 [ 0 ] ; if ( ssIsSampleHit ( rtS , 4 , 0 ) )
{ rtDW . ml1vr0zmzd = rtDW . blhgrykwvp ; } } if ( ssIsSampleHit ( rtS , 4 ,
0 ) ) { rtB . k2u5abxvdm = rtDW . ml1vr0zmzd ; } if ( ssIsSampleHit ( rtS , 1
, 0 ) ) { if ( rtB . dolerm5nyh ) { fjvdpbi13s = rtP . Initial_Val6_Value ; }
else { fjvdpbi13s = rtB . k2u5abxvdm ; } rtB . igl4agsvph = ( real32_T )
fjvdpbi13s ; b0nmwzpz3k = rtDW . iehvrkddj2 [ 0 ] ; if ( ssIsSampleHit ( rtS
, 4 , 0 ) ) { rtDW . ietukijfm5 = rtDW . osqohvejno ; } } if ( ssIsSampleHit
( rtS , 4 , 0 ) ) { rtB . fmww04dhk3 = rtDW . ietukijfm5 ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( rtB . dolerm5nyh ) { elmssggsl2 = rtP
. Initial_Val7_Value ; } else { elmssggsl2 = rtB . fmww04dhk3 ; } rtB .
kkpufmifuj = ( real32_T ) elmssggsl2 ; fwbhsjbvgy = rtDW . nbavx35izv [ 0 ] ;
if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . hcvygsausk = rtDW . cvcfermial
; } } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . lsypufcvtj = rtDW .
hcvygsausk ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( rtB . dolerm5nyh )
{ jg31sslk3y = rtP . Initial_Val8_Value ; } else { jg31sslk3y = rtB .
lsypufcvtj ; } rtB . lx40xm1u3s = ( real32_T ) jg31sslk3y ; m0cdt1tutw = rtDW
. cl1vsftpzn [ 0 ] ; if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . osj02yjrnn
= rtDW . ocn3tuy1mq ; } } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB .
crebamanmt = rtDW . osj02yjrnn ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if
( rtB . dolerm5nyh ) { baegv5utn3 = rtP . Initial_Val9_Value ; } else {
baegv5utn3 = rtB . crebamanmt ; } rtB . fyoaaccrru = ( real32_T ) baegv5utn3
; fhbhifl4ec = rtDW . lhojsnn24m [ 0 ] ; rtB . ac1d3qgxbp = gn5gtgcxz0 [ 0 ]
; eeij1wcm5a = rtDW . lzrfskvb50 [ 0 ] ; rtB . dxuigsm1g2 = gn5gtgcxz0 [ 1 ]
; ppdeyph1iv = rtDW . kxzyyq15r0 [ 0 ] ; if ( ssIsSampleHit ( rtS , 4 , 0 ) )
{ rtDW . o3dbqj4xyk = rtDW . jfrl3cqm1n ; } } if ( ssIsSampleHit ( rtS , 4 ,
0 ) ) { rtB . dzx3p1gp32 = rtDW . o3dbqj4xyk ; } if ( ssIsSampleHit ( rtS , 1
, 0 ) ) { if ( rtB . dolerm5nyh ) { rtB . g1mrrh2azp = rtP .
Initial_Val_Value ; } else { rtB . g1mrrh2azp = rtB . dzx3p1gp32 ; } rtB .
a00j4is05h = ( real32_T ) rtB . g1mrrh2azp ; rtB . a1lifabcqz = rtDW .
d42pvxfz0g [ 0 ] ; rtB . bft2jjoec5 = oanngtfv3o ; hfopv1ilcb = rtDW .
ayahx5voca [ 0 ] ; rtB . cmhi33mwre = cui5hlvqn2 ; ogbmffm3fg = rtDW .
l2zkdqsp2y [ 0 ] ; rtB . jml1bsjxtz = bmq2atwrs0 ; nskntf0qgz = rtDW .
lxk5izw00o [ 0 ] ; rtB . mkhgcxbdbc = jbohufsqub ; idv0agripi = rtDW .
cqp1dau03w [ 0 ] ; rtB . mmaiq4q51j = mvfiiz1q5d ; jqy22ktepi = rtDW .
gfiovjo3e2 [ 0 ] ; rtB . ejp2ouo0yj = afzdvlkvaw ; okapx5kozs = rtDW .
p2iwsajmfp [ 0 ] ; rtB . dxm0qgspl5 = rtB . pqtimdb5j0 ; rtB . j4ghcw5gtk =
cjdf0ewrkr ; kkrhy3nd01 = rtDW . b4auxd1lsk [ 0 ] ; pz3ma13zn2 = rtDW .
al5aajfx21 [ 0 ] ; rtB . oq4k1jl1j1 = ( real32_T ) rtDW . al5aajfx21 [ 0 ] ;
nsgl3oipuf = rtDW . kovzbujdnb [ 0 ] ; n4bzfamly2 = rtDW . gt3chc0tga [ 0 ] ;
rtB . lzb32orqgb = ( real32_T ) rtDW . gt3chc0tga [ 0 ] ; bhia010lzv = rtDW .
dttn4xmcnk [ 0 ] ; rtB . n3tpootby4 = rtB . nftvdrrocl ; dycq312gzw = rtDW .
erukb0glgz [ 0 ] ; if ( rtDW . k44l31otpd [ 0 ] ) { rtB . fme5wp01hh = rtDW .
n1ap5w5rdi [ 0 ] ; } else { rtB . fme5wp01hh = rtDW . ndb122ek3u [ 0 ] ; }
rtB . nyfnpu0nol = rtB . fme5wp01hh ; hsi51z2fza = rtDW . pdjkbbbzjq [ 0 ] ;
mmn0zxocgd = rtDW . bi1fzovgs2 ; rtB . ayauqzczgu = ( ( mmn0zxocgd >= rtP .
enb_counter_ge_51_const ) && ( mmn0zxocgd <= rtP . enb_counter_le_59_const )
) ; f5mkygzljk ( rtB . ayauqzczgu , & rtB . f5mkygzljka , & rtDW .
f5mkygzljka , & rtP . f5mkygzljka ) ; f5mkygzljk ( rtB . ayauqzczgu , & rtB .
o0tbmhvpds , & rtDW . o0tbmhvpds , & rtP . o0tbmhvpds ) ; f5mkygzljk ( rtB .
ayauqzczgu , & rtB . jjajpmoyel , & rtDW . jjajpmoyel , & rtP . jjajpmoyel )
; f5mkygzljk ( rtB . ayauqzczgu , & rtB . ndmeqad3sm , & rtDW . ndmeqad3sm ,
& rtP . ndmeqad3sm ) ; f5mkygzljk ( rtB . ayauqzczgu , & rtB . a13lr3lsi3 , &
rtDW . a13lr3lsi3 , & rtP . a13lr3lsi3 ) ; f5mkygzljk ( rtB . ayauqzczgu , &
rtB . jogryxdnkz , & rtDW . jogryxdnkz , & rtP . jogryxdnkz ) ; f5mkygzljk (
rtB . ayauqzczgu , & rtB . jjob4ur221 , & rtDW . jjob4ur221 , & rtP .
jjob4ur221 ) ; f5mkygzljk ( rtB . ayauqzczgu , & rtB . n4cqr1dkmr , & rtDW .
n4cqr1dkmr , & rtP . n4cqr1dkmr ) ; f5mkygzljk ( rtB . ayauqzczgu , & rtB .
cx41wglw3j , & rtDW . cx41wglw3j , & rtP . cx41wglw3j ) ; i = ( int32_T ) ( (
( rtB . f5mkygzljka . kehk5h5kaa & 32768ULL ) != 0ULL ) + ( rtB . f5mkygzljka
. kehk5h5kaa >> 16 ) ) ; rtB . faduibn1mq [ 0 ] = ( i & 16777216U ) != 0U ? i
| - 16777216 : i & 16777215 ; i = ( int32_T ) ( ( ( rtB . o0tbmhvpds .
kehk5h5kaa & 32768ULL ) != 0ULL ) + ( rtB . o0tbmhvpds . kehk5h5kaa >> 16 ) )
; rtB . faduibn1mq [ 1 ] = ( i & 16777216U ) != 0U ? i | - 16777216 : i &
16777215 ; i = ( int32_T ) ( ( ( rtB . jjajpmoyel . kehk5h5kaa & 32768ULL )
!= 0ULL ) + ( rtB . jjajpmoyel . kehk5h5kaa >> 16 ) ) ; rtB . faduibn1mq [ 2
] = ( i & 16777216U ) != 0U ? i | - 16777216 : i & 16777215 ; i = ( int32_T )
( ( ( rtB . ndmeqad3sm . kehk5h5kaa & 32768ULL ) != 0ULL ) + ( rtB .
ndmeqad3sm . kehk5h5kaa >> 16 ) ) ; rtB . faduibn1mq [ 3 ] = ( i & 16777216U
) != 0U ? i | - 16777216 : i & 16777215 ; i = ( int32_T ) ( ( ( rtB .
a13lr3lsi3 . kehk5h5kaa & 32768ULL ) != 0ULL ) + ( rtB . a13lr3lsi3 .
kehk5h5kaa >> 16 ) ) ; rtB . faduibn1mq [ 4 ] = ( i & 16777216U ) != 0U ? i |
- 16777216 : i & 16777215 ; i = ( int32_T ) ( ( ( rtB . jogryxdnkz .
kehk5h5kaa & 32768ULL ) != 0ULL ) + ( rtB . jogryxdnkz . kehk5h5kaa >> 16 ) )
; rtB . faduibn1mq [ 5 ] = ( i & 16777216U ) != 0U ? i | - 16777216 : i &
16777215 ; i = ( int32_T ) ( ( ( rtB . jjob4ur221 . kehk5h5kaa & 32768ULL )
!= 0ULL ) + ( rtB . jjob4ur221 . kehk5h5kaa >> 16 ) ) ; rtB . faduibn1mq [ 6
] = ( i & 16777216U ) != 0U ? i | - 16777216 : i & 16777215 ; i = ( int32_T )
( ( ( rtB . n4cqr1dkmr . kehk5h5kaa & 32768ULL ) != 0ULL ) + ( rtB .
n4cqr1dkmr . kehk5h5kaa >> 16 ) ) ; rtB . faduibn1mq [ 7 ] = ( i & 16777216U
) != 0U ? i | - 16777216 : i & 16777215 ; i = ( int32_T ) ( ( ( rtB .
cx41wglw3j . kehk5h5kaa & 32768ULL ) != 0ULL ) + ( rtB . cx41wglw3j .
kehk5h5kaa >> 16 ) ) ; rtB . faduibn1mq [ 8 ] = ( i & 16777216U ) != 0U ? i |
- 16777216 : i & 16777215 ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB .
ld0qtnhxv2 = rtDW . dzr2rntvvo [ 0 ] ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) )
{ rtB . ialnb1yw5e = ( real32_T ) rtB . ld0qtnhxv2 * 0.000244140625F ;
d0wxlnjlsb = rtDW . hoesofthyy [ 0 ] ; rtB . b4ty1phbhk = rtB . bmvpiaropc ;
dmsofgutmy = rtDW . pml0yl52te [ 0 ] ; if ( ssIsSampleHit ( rtS , 4 , 0 ) ) {
rtDW . ghxlzewxqv = rtDW . eswvf4pz4v ; } } if ( ssIsSampleHit ( rtS , 4 , 0
) ) { rtB . p0dldf2akj = rtDW . ghxlzewxqv ; rtB . ghazr1rloj [ 0 ] = rtDW .
aw0bxhrzal [ 0 ] ; rtB . ghazr1rloj [ 1 ] = rtDW . aw0bxhrzal [ 1 ] ; rtB .
ghazr1rloj [ 2 ] = rtDW . aw0bxhrzal [ 2 ] ; } if ( ssIsSampleHit ( rtS , 1 ,
0 ) ) { if ( rtB . dolerm5nyh ) { idif3mgiwd = rtP . Initial_Val1_Value ; }
else { idif3mgiwd = rtB . p0dldf2akj ; } rtB . cqo5mybcym = ( real32_T )
idif3mgiwd ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . kxltf1cq42 [ 0 ]
= rtDW . estezyunas [ 0 ] ; rtB . kxltf1cq42 [ 1 ] = rtDW . estezyunas [ 1 ]
; rtB . kxltf1cq42 [ 2 ] = rtDW . estezyunas [ 2 ] ; } if ( ssIsSampleHit (
rtS , 1 , 0 ) ) { grxhuiwehd_idx_0 = rtB . ghazr1rloj [ 0 ] ;
grxhuiwehd_idx_1 = rtB . ghazr1rloj [ 1 ] ; grxhuiwehd_idx_2 = rtB .
ghazr1rloj [ 2 ] ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . coti0iqh4j
[ 0 ] = rtDW . olzifhaukx [ 0 ] ; rtB . coti0iqh4j [ 1 ] = rtDW . olzifhaukx
[ 1 ] ; rtB . coti0iqh4j [ 2 ] = rtDW . olzifhaukx [ 2 ] ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { gj2rpmenje_idx_0 = grxhuiwehd_idx_0 ;
gj2rpmenje_idx_3 = rtB . kxltf1cq42 [ 0 ] ; gj2rpmenje_idx_6 = rtB .
coti0iqh4j [ 0 ] ; gj2rpmenje_idx_1 = grxhuiwehd_idx_1 ; gj2rpmenje_idx_4 =
rtB . kxltf1cq42 [ 1 ] ; gj2rpmenje_idx_7 = rtB . coti0iqh4j [ 1 ] ;
gj2rpmenje_idx_2 = grxhuiwehd_idx_2 ; gj2rpmenje_idx_5 = rtB . kxltf1cq42 [ 2
] ; gj2rpmenje_idx_8 = rtB . coti0iqh4j [ 2 ] ; if ( ssIsSampleHit ( rtS , 4
, 0 ) ) { rtDW . gpf5tclqta [ 0 ] = rtDW . otborblus0 [ 0 ] ; rtDW .
gpf5tclqta [ 1 ] = rtDW . otborblus0 [ 1 ] ; rtDW . gpf5tclqta [ 2 ] = rtDW .
otborblus0 [ 2 ] ; } } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB .
njb5q03jbz [ 0 ] = rtDW . miwm3apiea [ 0 ] ; rtB . njb5q03jbz [ 1 ] = rtDW .
miwm3apiea [ 1 ] ; rtB . njb5q03jbz [ 2 ] = rtDW . miwm3apiea [ 2 ] ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW .
mvfamndgj4 [ 0 ] = rtDW . ovlbtlz2z5 [ 0 ] ; rtDW . mvfamndgj4 [ 1 ] = rtDW .
ovlbtlz2z5 [ 1 ] ; rtDW . mvfamndgj4 [ 2 ] = rtDW . ovlbtlz2z5 [ 2 ] ; } if (
ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . piz1xhutnj [ 0 ] = rtDW . gpf5tclqta
[ 0 ] ; rtB . grirtgo1wo [ 0 ] = rtDW . jcievkrvvv [ 0 ] ; rtB . piz1xhutnj [
1 ] = rtDW . gpf5tclqta [ 1 ] ; rtB . grirtgo1wo [ 1 ] = rtDW . jcievkrvvv [
1 ] ; rtB . piz1xhutnj [ 2 ] = rtDW . gpf5tclqta [ 2 ] ; rtB . grirtgo1wo [ 2
] = rtDW . jcievkrvvv [ 2 ] ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) &&
ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . kcaj1yegtz [ 0 ] = rtDW . iygynuhhiw
[ 0 ] ; rtDW . kcaj1yegtz [ 1 ] = rtDW . iygynuhhiw [ 1 ] ; rtDW . kcaj1yegtz
[ 2 ] = rtDW . iygynuhhiw [ 2 ] ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) {
rtB . p30scmuimh [ 0 ] = rtDW . mvfamndgj4 [ 0 ] ; rtB . edxyvtrnw3 [ 0 ] =
rtDW . mx1dy0gdum [ 0 ] ; rtB . p30scmuimh [ 1 ] = rtDW . mvfamndgj4 [ 1 ] ;
rtB . edxyvtrnw3 [ 1 ] = rtDW . mx1dy0gdum [ 1 ] ; rtB . p30scmuimh [ 2 ] =
rtDW . mvfamndgj4 [ 2 ] ; rtB . edxyvtrnw3 [ 2 ] = rtDW . mx1dy0gdum [ 2 ] ;
} if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 4 , 0 ) ) {
rtDW . guhdmzy0n4 = rtDW . oamcwpfckc ; } if ( ssIsSampleHit ( rtS , 4 , 0 )
) { rtB . ckmlti53ey [ 0 ] = rtDW . kcaj1yegtz [ 0 ] ; rtB . ckmlti53ey [ 1 ]
= rtDW . kcaj1yegtz [ 1 ] ; rtB . ckmlti53ey [ 2 ] = rtDW . kcaj1yegtz [ 2 ]
; } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 4 , 0 ) ) {
rtDW . pbpmgsmorm = rtDW . ifur0qjdev ; } if ( ssIsSampleHit ( rtS , 4 , 0 )
) { rtB . i11z0ig3jm = rtDW . guhdmzy0n4 ; rtB . fwwwwnm0xy = rtDW .
pbpmgsmorm ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { hgizml3qp1 = rtDW .
h2z1m5wxiy [ 0 ] ; rtB . iskolztlai = rtB . nftvdrrocl * rtDW . h2z1m5wxiy [
0 ] ; rtB . odetrknlzz = k0k32irma1 * rtB . msybf1i1ih ; d0hyrjbvrp = rtDW .
dviol1u0jv [ 0 ] ; rtB . murauiwsvw = rtB . nftvdrrocl * rtDW . dviol1u0jv [
0 ] ; rtB . lugsvs2nsp = m0cdt1tutw * rtB . bnaxt4mwdx ; c10u5tt5g5 = rtDW .
df5ibuzfvl [ 0 ] ; rtB . gydjzs1bdb = rtB . nftvdrrocl * rtDW . df5ibuzfvl [
0 ] ; rtB . im5yymuath = fhbhifl4ec * rtB . du0uth4oge ; d1i4jxgfoj = rtDW .
ikv4gqtanm [ 0 ] ; rtB . bs3jd3qjqw = rtB . nftvdrrocl * rtDW . ikv4gqtanm [
0 ] ; rtB . iiqlz25ibz = cpgtcy5yeq * rtB . ctfswtdkgy ; dagdwu0ljw = rtDW .
hru10ym4o1 [ 0 ] ; rtB . m3i5omzuvm = rtB . nftvdrrocl * rtDW . hru10ym4o1 [
0 ] ; rtB . opdam4elco = j31e1nzsdd * rtB . famzz0eg5w ; nod352cw4v = rtDW .
erp5nno2ec [ 0 ] ; rtB . bpvldt4nml = rtB . nftvdrrocl * rtDW . erp5nno2ec [
0 ] ; rtB . b5q02ypjjz = b0nmwzpz3k * rtB . lt1czm1uxp ; bumwatdafh = rtDW .
ima1cclrzn [ 0 ] ; rtB . bzop13ab3h = rtB . nftvdrrocl * rtDW . ima1cclrzn [
0 ] ; rtB . ohmrbovmfa = fwbhsjbvgy * rtB . o4hoccuzjr ; rtB . jc2xb5555z =
rtP . Factor_const_Value * rtDW . hm24hbgcg1 [ 0 ] ; rtB . ncbythljam = rtP .
Gain_const_Value * rtDW . phidvr4lhk [ 0 ] ; rtB . ab2h2zhgij = rtP .
Gain_const1_Value * bxdgvixlrj ; rtB . gztw3fbv31 = rtP . Gain_const2_Value *
rtDW . nld3uzo5io [ 0 ] ; rtB . hwcg2de5ln = rtP . Gain_const3_Value *
hfopv1ilcb ; rtB . cw25rqhbhe = rtP . Gain_const4_Value * ogbmffm3fg ; rtB .
bohbdh5pos = rtP . Gain_const5_Value * nskntf0qgz ; rtB . mg4hzao3ac = rtP .
Gain_const6_Value * idv0agripi ; rtB . k3devdomyi = rtP . Gain_const7_Value *
jqy22ktepi ; rtB . l2ecs4m1wq = rtP . Gain_const8_Value * okapx5kozs ; rtB .
lphdmpzics = rtP . Gain_const9_Value * kkrhy3nd01 ; for ( i = 0 ; i < 9 ; i
++ ) { gn5gtgcxz0 [ i ] = rtDW . emh5kwkq0f [ i ] ; } rtB . bg5sagtx2f = rtDW
. enqlcsixk2 [ 0 ] * rtB . jqoi3hd2f5 ; rtB . o42245qd4a = rtDW . enqlcsixk2
[ 0 ] * rtB . g1mrrh2azp ; rtB . lofmmfuim4 = hsi51z2fza * k1dmmkojfr ; rtB .
ku3t5edtlg = rtB . ozrwjzfnca * rtDW . f3zvxiekpj [ 0 ] ; rtB . eqti4hemyn =
bhia010lzv * rtDW . dspkd5mdvs [ 0 ] ; rtB . n4gmeaqzp4 = rtDW . bs1nmm0jpl [
0 ] * nsgl3oipuf ; rtB . gti1gti2ss = rtDW . bx5vsdt4mt [ 0 ] ; rtB .
cajcokate4 = rtDW . hjbvl0tg45 [ 0 ] * rtDW . nyxm5sdvcd [ 0 ] ; rtB .
mxgu50ynet = rtDW . f0lbp4tqqn [ 0 ] * d1rmwt0esq ; rtB . m4ynyxpbu2 =
pz3ma13zn2 * dycq312gzw ; rtB . ik02utyxan = n4bzfamly2 * dycq312gzw ; rtB .
f00exjvhy5 = rtDW . ob20xueupt [ 0 ] * rtDW . ciaqlqmyyx [ 0 ] ; rtB .
ijrdbn05so = rtDW . e1kih03oaj [ 0 ] ; muSingleScalarSinCos ( d0wxlnjlsb , &
rtB . mk1wynbhp2 , & rtB . gjoeyfmk32 ) ; jm4jb5nop1 = rtDW . m5gzgpvijm [ 0
] ; mkv3qbkou5 = rtDW . o3kxgyy1fj [ 0 ] ; rtB . e4wgz1h5dw = rtB .
fwwwwnm0xy + rtB . haranx30a5 [ 0 ] ; rtB . lie0qvypkt = ppdeyph1iv - rtDW .
lfuv5ipyfs [ 0 ] ; rtB . ghwcctc4hl = rtDW . fl4tijqsrl [ 0 ] - rtDW .
fva2rmvmh4 [ 0 ] ; rtB . pzyy3abz13 = rtDW . mxawq0evig [ 0 ] - dmsofgutmy ;
rtB . jjunnmldtx = rtDW . atdfcebxbc [ 0 ] + rtB . jqoi3hd2f5 ; mfxncopstb =
rtDW . e1vdezejb0 [ 0 ] ; rtB . ewkvxp0tx3 = rtDW . o3sgmp4aev [ 0 ] +
idif3mgiwd ; mpbkrymds0 = rtDW . nrq4usubsl [ 0 ] ; rtB . pxpefqknkg = rtDW .
n0ifswwd21 [ 0 ] + baegv5utn3 ; jvzpawhyvp = rtDW . omuzgpsf1f [ 0 ] ; rtB .
pmnldr5rgz = rtDW . fi4wuwmktb [ 0 ] + rtB . g1mrrh2azp ; jdebb5lusi = rtDW .
hys0om0qbu [ 0 ] ; rtB . cssbez0qdp = rtDW . nkf0blmwkl [ 0 ] - rtDW .
gmymeboquk [ 0 ] ; rtB . jorthzrtqn = rtDW . gm4ivysliu [ 0 ] + kbjxlva2lq ;
fzopdc1y3h = rtDW . nr5d4vqt4t [ 0 ] ; rtB . kkydc41wz4 = rtDW . pyurk4he1k [
0 ] + c3e3zs0dtp ; j2bjtltjrv = rtDW . cnk414y00k [ 0 ] ; rtB . pls0pucbim =
rtDW . ocff1ayzzn [ 0 ] + dkjmpmrmx0 ; jjijeib3g5 = rtDW . fnpjhtoie0 [ 0 ] ;
rtB . c4jaly0gxz = rtDW . l0rzviqodi [ 0 ] + fjvdpbi13s ; ftrre2olna = rtDW .
frvvvscadt [ 0 ] ; rtB . kmjcmuq4sa = rtDW . o0qik01ouq [ 0 ] + elmssggsl2 ;
eqwgwo0chw = rtDW . pfwwityzhm [ 0 ] ; rtB . j4shds0cgp = rtDW . jci52usrwf [
0 ] + jg31sslk3y ; nvszulfdmh = rtDW . awvvdj3gzy [ 0 ] ; rtB . crlo0ykadd =
eeij1wcm5a - rtDW . hdlc0qsc4w [ 0 ] ; rtB . a3nmhcj3ac = rtDW . esrssadyy0 [
0 ] + rtDW . bq4gap0f1m [ 0 ] ; gl2pknaref = rtDW . ocwqpyvhqo ; if ( rtDW .
ocwqpyvhqo ) { e01vrhb3hu = rtP . Initial_Val_Value_pik4yifivl ; } else {
e01vrhb3hu = rtDW . loh1yczrtr ; } rtB . krcsx2cqzw = ( real32_T ) e01vrhb3hu
; rtB . krzkvwtyr5 = rtDW . h5lg5oz5ks [ 0 ] ; rtB . ekqsqfqm5z = rtDW .
hggmceleiv [ 0 ] ; hs3cpomagx = rtDW . cayw42bvqq [ 0 ] ; if ( ssIsSampleHit
( rtS , 4 , 0 ) ) { rtDW . jw4znmasof = rtDW . fmhxej54hb ; } } if (
ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . nvrrli0mdp = rtDW . jw4znmasof ; rtB
. jakdxomnmi = rtDW . hv1tfq2dkg ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) {
rtB . lkfyl1qpfg = rtDW . pdhtdmqeof [ 0 ] * rtDW . i3xwoxj5zy [ 0 ] ; rtB .
k2epoclkhf = rtP . Gain_const_Value_kf5wnphskk * hs3cpomagx ; rtB .
o3isut3xe2 = rtDW . fzberuaezs [ 0 ] + e01vrhb3hu ; rtB . drcj52wpue = rtDW .
lth0p1kskk [ 0 ] ; rtB . frhtoi20is = rtB . nvrrli0mdp ; if ( gl2pknaref ) {
rtB . pdwhfw3xoj = rtP . Initial_Val_Value_pik4yifivl ; } else { rtB .
pdwhfw3xoj = rtDW . oiurtflkiv [ 0 ] ; } rtB . mfqi5bmnfc [ 0 ] = bhia010lzv
; rtB . mfqi5bmnfc [ 1 ] = nsgl3oipuf ; rtB . mfqi5bmnfc [ 2 ] = hgizml3qp1 ;
rtB . mfqi5bmnfc [ 3 ] = d1i4jxgfoj ; rtB . mfqi5bmnfc [ 4 ] = dagdwu0ljw ;
rtB . mfqi5bmnfc [ 5 ] = nod352cw4v ; rtB . mfqi5bmnfc [ 6 ] = bumwatdafh ;
rtB . mfqi5bmnfc [ 7 ] = d0hyrjbvrp ; rtB . mfqi5bmnfc [ 8 ] = c10u5tt5g5 ;
rtB . n01cwk51y2 = rtDW . ko0pv0nfnn [ 0 ] + rtDW . kr1btzpdxw [ 0 ] ; rtB .
p3g0p13atl = rtDW . axidhoghf0 [ 0 ] - rtDW . pqgou55kzx [ 0 ] ; for ( i = 0
; i < 9 ; i ++ ) { for ( grxhuiwehd_idx_0 = 0 ; grxhuiwehd_idx_0 < 9 ;
grxhuiwehd_idx_0 ++ ) { cyymg1pfyn [ grxhuiwehd_idx_0 + 9 * i ] = rtP .
Constant1_Value_jytosolkko [ 9 * grxhuiwehd_idx_0 + i ] ; } } tmp_c = (
int64_T ) cyymg1pfyn [ 0 ] * gj2rpmenje_idx_0 + rtP . _bias_Value ; tmp_c = (
tmp_c & 8796093022208ULL ) != 0ULL ? tmp_c | - 8796093022208LL : tmp_c &
8796093022207LL ; tmp_c = ( ( tmp_c & 4398046511104ULL ) != 0ULL ? tmp_c | -
4398046511104LL : tmp_c & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 1 ] *
gj2rpmenje_idx_1 ; tmp_c = ( tmp_c & 8796093022208ULL ) != 0ULL ? tmp_c | -
8796093022208LL : tmp_c & 8796093022207LL ; tmp_c = ( ( tmp_c &
4398046511104ULL ) != 0ULL ? tmp_c | - 4398046511104LL : tmp_c &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 2 ] * gj2rpmenje_idx_2 ; tmp_c =
( tmp_c & 8796093022208ULL ) != 0ULL ? tmp_c | - 8796093022208LL : tmp_c &
8796093022207LL ; tmp_c = ( ( tmp_c & 4398046511104ULL ) != 0ULL ? tmp_c | -
4398046511104LL : tmp_c & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 3 ] *
gj2rpmenje_idx_3 ; tmp_c = ( tmp_c & 8796093022208ULL ) != 0ULL ? tmp_c | -
8796093022208LL : tmp_c & 8796093022207LL ; tmp_c = ( ( tmp_c &
4398046511104ULL ) != 0ULL ? tmp_c | - 4398046511104LL : tmp_c &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 4 ] * gj2rpmenje_idx_4 ; tmp_c =
( tmp_c & 8796093022208ULL ) != 0ULL ? tmp_c | - 8796093022208LL : tmp_c &
8796093022207LL ; tmp_c = ( ( tmp_c & 4398046511104ULL ) != 0ULL ? tmp_c | -
4398046511104LL : tmp_c & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 5 ] *
gj2rpmenje_idx_5 ; tmp_c = ( tmp_c & 8796093022208ULL ) != 0ULL ? tmp_c | -
8796093022208LL : tmp_c & 8796093022207LL ; tmp_c = ( ( tmp_c &
4398046511104ULL ) != 0ULL ? tmp_c | - 4398046511104LL : tmp_c &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 6 ] * gj2rpmenje_idx_6 ; tmp_c =
( tmp_c & 8796093022208ULL ) != 0ULL ? tmp_c | - 8796093022208LL : tmp_c &
8796093022207LL ; tmp_c = ( ( tmp_c & 4398046511104ULL ) != 0ULL ? tmp_c | -
4398046511104LL : tmp_c & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 7 ] *
gj2rpmenje_idx_7 ; tmp_c = ( tmp_c & 8796093022208ULL ) != 0ULL ? tmp_c | -
8796093022208LL : tmp_c & 8796093022207LL ; tmp_c = ( ( tmp_c &
4398046511104ULL ) != 0ULL ? tmp_c | - 4398046511104LL : tmp_c &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 8 ] * gj2rpmenje_idx_8 ; tmp_c =
( tmp_c & 8796093022208ULL ) != 0ULL ? tmp_c | - 8796093022208LL : tmp_c &
8796093022207LL ; tmp_f = ( int64_T ) cyymg1pfyn [ 9 ] * gj2rpmenje_idx_0 +
rtP . _bias1_Value ; tmp_f = ( tmp_f & 8796093022208ULL ) != 0ULL ? tmp_f | -
8796093022208LL : tmp_f & 8796093022207LL ; tmp_f = ( ( tmp_f &
4398046511104ULL ) != 0ULL ? tmp_f | - 4398046511104LL : tmp_f &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 10 ] * gj2rpmenje_idx_1 ; tmp_f
= ( tmp_f & 8796093022208ULL ) != 0ULL ? tmp_f | - 8796093022208LL : tmp_f &
8796093022207LL ; tmp_f = ( ( tmp_f & 4398046511104ULL ) != 0ULL ? tmp_f | -
4398046511104LL : tmp_f & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 11 ] *
gj2rpmenje_idx_2 ; tmp_f = ( tmp_f & 8796093022208ULL ) != 0ULL ? tmp_f | -
8796093022208LL : tmp_f & 8796093022207LL ; tmp_f = ( ( tmp_f &
4398046511104ULL ) != 0ULL ? tmp_f | - 4398046511104LL : tmp_f &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 12 ] * gj2rpmenje_idx_3 ; tmp_f
= ( tmp_f & 8796093022208ULL ) != 0ULL ? tmp_f | - 8796093022208LL : tmp_f &
8796093022207LL ; tmp_f = ( ( tmp_f & 4398046511104ULL ) != 0ULL ? tmp_f | -
4398046511104LL : tmp_f & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 13 ] *
gj2rpmenje_idx_4 ; tmp_f = ( tmp_f & 8796093022208ULL ) != 0ULL ? tmp_f | -
8796093022208LL : tmp_f & 8796093022207LL ; tmp_f = ( ( tmp_f &
4398046511104ULL ) != 0ULL ? tmp_f | - 4398046511104LL : tmp_f &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 14 ] * gj2rpmenje_idx_5 ; tmp_f
= ( tmp_f & 8796093022208ULL ) != 0ULL ? tmp_f | - 8796093022208LL : tmp_f &
8796093022207LL ; tmp_f = ( ( tmp_f & 4398046511104ULL ) != 0ULL ? tmp_f | -
4398046511104LL : tmp_f & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 15 ] *
gj2rpmenje_idx_6 ; tmp_f = ( tmp_f & 8796093022208ULL ) != 0ULL ? tmp_f | -
8796093022208LL : tmp_f & 8796093022207LL ; tmp_f = ( ( tmp_f &
4398046511104ULL ) != 0ULL ? tmp_f | - 4398046511104LL : tmp_f &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 16 ] * gj2rpmenje_idx_7 ; tmp_f
= ( tmp_f & 8796093022208ULL ) != 0ULL ? tmp_f | - 8796093022208LL : tmp_f &
8796093022207LL ; tmp_f = ( ( tmp_f & 4398046511104ULL ) != 0ULL ? tmp_f | -
4398046511104LL : tmp_f & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 17 ] *
gj2rpmenje_idx_8 ; tmp_f = ( tmp_f & 8796093022208ULL ) != 0ULL ? tmp_f | -
8796093022208LL : tmp_f & 8796093022207LL ; tmp_j = ( int64_T ) cyymg1pfyn [
18 ] * gj2rpmenje_idx_0 + rtP . _bias2_Value ; tmp_j = ( tmp_j &
8796093022208ULL ) != 0ULL ? tmp_j | - 8796093022208LL : tmp_j &
8796093022207LL ; tmp_j = ( ( tmp_j & 4398046511104ULL ) != 0ULL ? tmp_j | -
4398046511104LL : tmp_j & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 19 ] *
gj2rpmenje_idx_1 ; tmp_j = ( tmp_j & 8796093022208ULL ) != 0ULL ? tmp_j | -
8796093022208LL : tmp_j & 8796093022207LL ; tmp_j = ( ( tmp_j &
4398046511104ULL ) != 0ULL ? tmp_j | - 4398046511104LL : tmp_j &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 20 ] * gj2rpmenje_idx_2 ; tmp_j
= ( tmp_j & 8796093022208ULL ) != 0ULL ? tmp_j | - 8796093022208LL : tmp_j &
8796093022207LL ; tmp_j = ( ( tmp_j & 4398046511104ULL ) != 0ULL ? tmp_j | -
4398046511104LL : tmp_j & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 21 ] *
gj2rpmenje_idx_3 ; tmp_j = ( tmp_j & 8796093022208ULL ) != 0ULL ? tmp_j | -
8796093022208LL : tmp_j & 8796093022207LL ; tmp_j = ( ( tmp_j &
4398046511104ULL ) != 0ULL ? tmp_j | - 4398046511104LL : tmp_j &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 22 ] * gj2rpmenje_idx_4 ; tmp_j
= ( tmp_j & 8796093022208ULL ) != 0ULL ? tmp_j | - 8796093022208LL : tmp_j &
8796093022207LL ; tmp_j = ( ( tmp_j & 4398046511104ULL ) != 0ULL ? tmp_j | -
4398046511104LL : tmp_j & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 23 ] *
gj2rpmenje_idx_5 ; tmp_j = ( tmp_j & 8796093022208ULL ) != 0ULL ? tmp_j | -
8796093022208LL : tmp_j & 8796093022207LL ; tmp_j = ( ( tmp_j &
4398046511104ULL ) != 0ULL ? tmp_j | - 4398046511104LL : tmp_j &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 24 ] * gj2rpmenje_idx_6 ; tmp_j
= ( tmp_j & 8796093022208ULL ) != 0ULL ? tmp_j | - 8796093022208LL : tmp_j &
8796093022207LL ; tmp_j = ( ( tmp_j & 4398046511104ULL ) != 0ULL ? tmp_j | -
4398046511104LL : tmp_j & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 25 ] *
gj2rpmenje_idx_7 ; tmp_j = ( tmp_j & 8796093022208ULL ) != 0ULL ? tmp_j | -
8796093022208LL : tmp_j & 8796093022207LL ; tmp_j = ( ( tmp_j &
4398046511104ULL ) != 0ULL ? tmp_j | - 4398046511104LL : tmp_j &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 26 ] * gj2rpmenje_idx_8 ; tmp_j
= ( tmp_j & 8796093022208ULL ) != 0ULL ? tmp_j | - 8796093022208LL : tmp_j &
8796093022207LL ; tmp_g = ( int64_T ) cyymg1pfyn [ 27 ] * gj2rpmenje_idx_0 +
rtP . _bias3_Value ; tmp_g = ( tmp_g & 8796093022208ULL ) != 0ULL ? tmp_g | -
8796093022208LL : tmp_g & 8796093022207LL ; tmp_g = ( ( tmp_g &
4398046511104ULL ) != 0ULL ? tmp_g | - 4398046511104LL : tmp_g &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 28 ] * gj2rpmenje_idx_1 ; tmp_g
= ( tmp_g & 8796093022208ULL ) != 0ULL ? tmp_g | - 8796093022208LL : tmp_g &
8796093022207LL ; tmp_g = ( ( tmp_g & 4398046511104ULL ) != 0ULL ? tmp_g | -
4398046511104LL : tmp_g & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 29 ] *
gj2rpmenje_idx_2 ; tmp_g = ( tmp_g & 8796093022208ULL ) != 0ULL ? tmp_g | -
8796093022208LL : tmp_g & 8796093022207LL ; tmp_g = ( ( tmp_g &
4398046511104ULL ) != 0ULL ? tmp_g | - 4398046511104LL : tmp_g &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 30 ] * gj2rpmenje_idx_3 ; tmp_g
= ( tmp_g & 8796093022208ULL ) != 0ULL ? tmp_g | - 8796093022208LL : tmp_g &
8796093022207LL ; tmp_g = ( ( tmp_g & 4398046511104ULL ) != 0ULL ? tmp_g | -
4398046511104LL : tmp_g & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 31 ] *
gj2rpmenje_idx_4 ; tmp_g = ( tmp_g & 8796093022208ULL ) != 0ULL ? tmp_g | -
8796093022208LL : tmp_g & 8796093022207LL ; tmp_g = ( ( tmp_g &
4398046511104ULL ) != 0ULL ? tmp_g | - 4398046511104LL : tmp_g &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 32 ] * gj2rpmenje_idx_5 ; tmp_g
= ( tmp_g & 8796093022208ULL ) != 0ULL ? tmp_g | - 8796093022208LL : tmp_g &
8796093022207LL ; tmp_g = ( ( tmp_g & 4398046511104ULL ) != 0ULL ? tmp_g | -
4398046511104LL : tmp_g & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 33 ] *
gj2rpmenje_idx_6 ; tmp_g = ( tmp_g & 8796093022208ULL ) != 0ULL ? tmp_g | -
8796093022208LL : tmp_g & 8796093022207LL ; tmp_g = ( ( tmp_g &
4398046511104ULL ) != 0ULL ? tmp_g | - 4398046511104LL : tmp_g &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 34 ] * gj2rpmenje_idx_7 ; tmp_g
= ( tmp_g & 8796093022208ULL ) != 0ULL ? tmp_g | - 8796093022208LL : tmp_g &
8796093022207LL ; tmp_g = ( ( tmp_g & 4398046511104ULL ) != 0ULL ? tmp_g | -
4398046511104LL : tmp_g & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 35 ] *
gj2rpmenje_idx_8 ; tmp_g = ( tmp_g & 8796093022208ULL ) != 0ULL ? tmp_g | -
8796093022208LL : tmp_g & 8796093022207LL ; tmp_m = ( int64_T ) cyymg1pfyn [
36 ] * gj2rpmenje_idx_0 + rtP . _bias4_Value ; tmp_m = ( tmp_m &
8796093022208ULL ) != 0ULL ? tmp_m | - 8796093022208LL : tmp_m &
8796093022207LL ; tmp_m = ( ( tmp_m & 4398046511104ULL ) != 0ULL ? tmp_m | -
4398046511104LL : tmp_m & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 37 ] *
gj2rpmenje_idx_1 ; tmp_m = ( tmp_m & 8796093022208ULL ) != 0ULL ? tmp_m | -
8796093022208LL : tmp_m & 8796093022207LL ; tmp_m = ( ( tmp_m &
4398046511104ULL ) != 0ULL ? tmp_m | - 4398046511104LL : tmp_m &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 38 ] * gj2rpmenje_idx_2 ; tmp_m
= ( tmp_m & 8796093022208ULL ) != 0ULL ? tmp_m | - 8796093022208LL : tmp_m &
8796093022207LL ; tmp_m = ( ( tmp_m & 4398046511104ULL ) != 0ULL ? tmp_m | -
4398046511104LL : tmp_m & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 39 ] *
gj2rpmenje_idx_3 ; tmp_m = ( tmp_m & 8796093022208ULL ) != 0ULL ? tmp_m | -
8796093022208LL : tmp_m & 8796093022207LL ; tmp_m = ( ( tmp_m &
4398046511104ULL ) != 0ULL ? tmp_m | - 4398046511104LL : tmp_m &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 40 ] * gj2rpmenje_idx_4 ; tmp_m
= ( tmp_m & 8796093022208ULL ) != 0ULL ? tmp_m | - 8796093022208LL : tmp_m &
8796093022207LL ; tmp_m = ( ( tmp_m & 4398046511104ULL ) != 0ULL ? tmp_m | -
4398046511104LL : tmp_m & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 41 ] *
gj2rpmenje_idx_5 ; tmp_m = ( tmp_m & 8796093022208ULL ) != 0ULL ? tmp_m | -
8796093022208LL : tmp_m & 8796093022207LL ; tmp_m = ( ( tmp_m &
4398046511104ULL ) != 0ULL ? tmp_m | - 4398046511104LL : tmp_m &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 42 ] * gj2rpmenje_idx_6 ; tmp_m
= ( tmp_m & 8796093022208ULL ) != 0ULL ? tmp_m | - 8796093022208LL : tmp_m &
8796093022207LL ; tmp_m = ( ( tmp_m & 4398046511104ULL ) != 0ULL ? tmp_m | -
4398046511104LL : tmp_m & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 43 ] *
gj2rpmenje_idx_7 ; tmp_m = ( tmp_m & 8796093022208ULL ) != 0ULL ? tmp_m | -
8796093022208LL : tmp_m & 8796093022207LL ; tmp_m = ( ( tmp_m &
4398046511104ULL ) != 0ULL ? tmp_m | - 4398046511104LL : tmp_m &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 44 ] * gj2rpmenje_idx_8 ; tmp_m
= ( tmp_m & 8796093022208ULL ) != 0ULL ? tmp_m | - 8796093022208LL : tmp_m &
8796093022207LL ; tmp_i = ( int64_T ) cyymg1pfyn [ 45 ] * gj2rpmenje_idx_0 +
rtP . _bias5_Value ; tmp_i = ( tmp_i & 8796093022208ULL ) != 0ULL ? tmp_i | -
8796093022208LL : tmp_i & 8796093022207LL ; tmp_i = ( ( tmp_i &
4398046511104ULL ) != 0ULL ? tmp_i | - 4398046511104LL : tmp_i &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 46 ] * gj2rpmenje_idx_1 ; tmp_i
= ( tmp_i & 8796093022208ULL ) != 0ULL ? tmp_i | - 8796093022208LL : tmp_i &
8796093022207LL ; tmp_i = ( ( tmp_i & 4398046511104ULL ) != 0ULL ? tmp_i | -
4398046511104LL : tmp_i & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 47 ] *
gj2rpmenje_idx_2 ; tmp_i = ( tmp_i & 8796093022208ULL ) != 0ULL ? tmp_i | -
8796093022208LL : tmp_i & 8796093022207LL ; tmp_i = ( ( tmp_i &
4398046511104ULL ) != 0ULL ? tmp_i | - 4398046511104LL : tmp_i &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 48 ] * gj2rpmenje_idx_3 ; tmp_i
= ( tmp_i & 8796093022208ULL ) != 0ULL ? tmp_i | - 8796093022208LL : tmp_i &
8796093022207LL ; tmp_i = ( ( tmp_i & 4398046511104ULL ) != 0ULL ? tmp_i | -
4398046511104LL : tmp_i & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 49 ] *
gj2rpmenje_idx_4 ; tmp_i = ( tmp_i & 8796093022208ULL ) != 0ULL ? tmp_i | -
8796093022208LL : tmp_i & 8796093022207LL ; tmp_i = ( ( tmp_i &
4398046511104ULL ) != 0ULL ? tmp_i | - 4398046511104LL : tmp_i &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 50 ] * gj2rpmenje_idx_5 ; tmp_i
= ( tmp_i & 8796093022208ULL ) != 0ULL ? tmp_i | - 8796093022208LL : tmp_i &
8796093022207LL ; tmp_i = ( ( tmp_i & 4398046511104ULL ) != 0ULL ? tmp_i | -
4398046511104LL : tmp_i & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 51 ] *
gj2rpmenje_idx_6 ; tmp_i = ( tmp_i & 8796093022208ULL ) != 0ULL ? tmp_i | -
8796093022208LL : tmp_i & 8796093022207LL ; tmp_i = ( ( tmp_i &
4398046511104ULL ) != 0ULL ? tmp_i | - 4398046511104LL : tmp_i &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 52 ] * gj2rpmenje_idx_7 ; tmp_i
= ( tmp_i & 8796093022208ULL ) != 0ULL ? tmp_i | - 8796093022208LL : tmp_i &
8796093022207LL ; tmp_i = ( ( tmp_i & 4398046511104ULL ) != 0ULL ? tmp_i | -
4398046511104LL : tmp_i & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 53 ] *
gj2rpmenje_idx_8 ; tmp_i = ( tmp_i & 8796093022208ULL ) != 0ULL ? tmp_i | -
8796093022208LL : tmp_i & 8796093022207LL ; tmp_e = ( int64_T ) cyymg1pfyn [
54 ] * gj2rpmenje_idx_0 + rtP . _bias6_Value ; tmp_e = ( tmp_e &
8796093022208ULL ) != 0ULL ? tmp_e | - 8796093022208LL : tmp_e &
8796093022207LL ; tmp_e = ( ( tmp_e & 4398046511104ULL ) != 0ULL ? tmp_e | -
4398046511104LL : tmp_e & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 55 ] *
gj2rpmenje_idx_1 ; tmp_e = ( tmp_e & 8796093022208ULL ) != 0ULL ? tmp_e | -
8796093022208LL : tmp_e & 8796093022207LL ; tmp_e = ( ( tmp_e &
4398046511104ULL ) != 0ULL ? tmp_e | - 4398046511104LL : tmp_e &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 56 ] * gj2rpmenje_idx_2 ; tmp_e
= ( tmp_e & 8796093022208ULL ) != 0ULL ? tmp_e | - 8796093022208LL : tmp_e &
8796093022207LL ; tmp_e = ( ( tmp_e & 4398046511104ULL ) != 0ULL ? tmp_e | -
4398046511104LL : tmp_e & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 57 ] *
gj2rpmenje_idx_3 ; tmp_e = ( tmp_e & 8796093022208ULL ) != 0ULL ? tmp_e | -
8796093022208LL : tmp_e & 8796093022207LL ; tmp_e = ( ( tmp_e &
4398046511104ULL ) != 0ULL ? tmp_e | - 4398046511104LL : tmp_e &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 58 ] * gj2rpmenje_idx_4 ; tmp_e
= ( tmp_e & 8796093022208ULL ) != 0ULL ? tmp_e | - 8796093022208LL : tmp_e &
8796093022207LL ; tmp_e = ( ( tmp_e & 4398046511104ULL ) != 0ULL ? tmp_e | -
4398046511104LL : tmp_e & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 59 ] *
gj2rpmenje_idx_5 ; tmp_e = ( tmp_e & 8796093022208ULL ) != 0ULL ? tmp_e | -
8796093022208LL : tmp_e & 8796093022207LL ; tmp_e = ( ( tmp_e &
4398046511104ULL ) != 0ULL ? tmp_e | - 4398046511104LL : tmp_e &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 60 ] * gj2rpmenje_idx_6 ; tmp_e
= ( tmp_e & 8796093022208ULL ) != 0ULL ? tmp_e | - 8796093022208LL : tmp_e &
8796093022207LL ; tmp_e = ( ( tmp_e & 4398046511104ULL ) != 0ULL ? tmp_e | -
4398046511104LL : tmp_e & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 61 ] *
gj2rpmenje_idx_7 ; tmp_e = ( tmp_e & 8796093022208ULL ) != 0ULL ? tmp_e | -
8796093022208LL : tmp_e & 8796093022207LL ; tmp_e = ( ( tmp_e &
4398046511104ULL ) != 0ULL ? tmp_e | - 4398046511104LL : tmp_e &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 62 ] * gj2rpmenje_idx_8 ; tmp_e
= ( tmp_e & 8796093022208ULL ) != 0ULL ? tmp_e | - 8796093022208LL : tmp_e &
8796093022207LL ; tmp_p = ( int64_T ) cyymg1pfyn [ 63 ] * gj2rpmenje_idx_0 +
rtP . _bias7_Value ; tmp_p = ( tmp_p & 8796093022208ULL ) != 0ULL ? tmp_p | -
8796093022208LL : tmp_p & 8796093022207LL ; tmp_p = ( ( tmp_p &
4398046511104ULL ) != 0ULL ? tmp_p | - 4398046511104LL : tmp_p &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 64 ] * gj2rpmenje_idx_1 ; tmp_p
= ( tmp_p & 8796093022208ULL ) != 0ULL ? tmp_p | - 8796093022208LL : tmp_p &
8796093022207LL ; tmp_p = ( ( tmp_p & 4398046511104ULL ) != 0ULL ? tmp_p | -
4398046511104LL : tmp_p & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 65 ] *
gj2rpmenje_idx_2 ; tmp_p = ( tmp_p & 8796093022208ULL ) != 0ULL ? tmp_p | -
8796093022208LL : tmp_p & 8796093022207LL ; tmp_p = ( ( tmp_p &
4398046511104ULL ) != 0ULL ? tmp_p | - 4398046511104LL : tmp_p &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 66 ] * gj2rpmenje_idx_3 ; tmp_p
= ( tmp_p & 8796093022208ULL ) != 0ULL ? tmp_p | - 8796093022208LL : tmp_p &
8796093022207LL ; tmp_p = ( ( tmp_p & 4398046511104ULL ) != 0ULL ? tmp_p | -
4398046511104LL : tmp_p & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 67 ] *
gj2rpmenje_idx_4 ; tmp_p = ( tmp_p & 8796093022208ULL ) != 0ULL ? tmp_p | -
8796093022208LL : tmp_p & 8796093022207LL ; tmp_p = ( ( tmp_p &
4398046511104ULL ) != 0ULL ? tmp_p | - 4398046511104LL : tmp_p &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 68 ] * gj2rpmenje_idx_5 ; tmp_p
= ( tmp_p & 8796093022208ULL ) != 0ULL ? tmp_p | - 8796093022208LL : tmp_p &
8796093022207LL ; tmp_p = ( ( tmp_p & 4398046511104ULL ) != 0ULL ? tmp_p | -
4398046511104LL : tmp_p & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 69 ] *
gj2rpmenje_idx_6 ; tmp_p = ( tmp_p & 8796093022208ULL ) != 0ULL ? tmp_p | -
8796093022208LL : tmp_p & 8796093022207LL ; tmp_p = ( ( tmp_p &
4398046511104ULL ) != 0ULL ? tmp_p | - 4398046511104LL : tmp_p &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 70 ] * gj2rpmenje_idx_7 ; tmp_p
= ( tmp_p & 8796093022208ULL ) != 0ULL ? tmp_p | - 8796093022208LL : tmp_p &
8796093022207LL ; tmp_p = ( ( tmp_p & 4398046511104ULL ) != 0ULL ? tmp_p | -
4398046511104LL : tmp_p & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 71 ] *
gj2rpmenje_idx_8 ; tmp_p = ( tmp_p & 8796093022208ULL ) != 0ULL ? tmp_p | -
8796093022208LL : tmp_p & 8796093022207LL ; rtB . jgteqxearg [ 0 ] = (
real32_T ) ( ( tmp_c & 4398046511104ULL ) != 0ULL ? tmp_c | - 4398046511104LL
: tmp_c & 4398046511103LL ) * 4.65661287E-10F ; rtB . jgteqxearg [ 1 ] = (
real32_T ) ( ( tmp_f & 4398046511104ULL ) != 0ULL ? tmp_f | - 4398046511104LL
: tmp_f & 4398046511103LL ) * 4.65661287E-10F ; rtB . jgteqxearg [ 2 ] = (
real32_T ) ( ( tmp_j & 4398046511104ULL ) != 0ULL ? tmp_j | - 4398046511104LL
: tmp_j & 4398046511103LL ) * 4.65661287E-10F ; rtB . jgteqxearg [ 3 ] = (
real32_T ) ( ( tmp_g & 4398046511104ULL ) != 0ULL ? tmp_g | - 4398046511104LL
: tmp_g & 4398046511103LL ) * 4.65661287E-10F ; rtB . jgteqxearg [ 4 ] = (
real32_T ) ( ( tmp_m & 4398046511104ULL ) != 0ULL ? tmp_m | - 4398046511104LL
: tmp_m & 4398046511103LL ) * 4.65661287E-10F ; rtB . jgteqxearg [ 5 ] = (
real32_T ) ( ( tmp_i & 4398046511104ULL ) != 0ULL ? tmp_i | - 4398046511104LL
: tmp_i & 4398046511103LL ) * 4.65661287E-10F ; rtB . jgteqxearg [ 6 ] = (
real32_T ) ( ( tmp_e & 4398046511104ULL ) != 0ULL ? tmp_e | - 4398046511104LL
: tmp_e & 4398046511103LL ) * 4.65661287E-10F ; rtB . jgteqxearg [ 7 ] = (
real32_T ) ( ( tmp_p & 4398046511104ULL ) != 0ULL ? tmp_p | - 4398046511104LL
: tmp_p & 4398046511103LL ) * 4.65661287E-10F ; tmp_c = ( int64_T )
cyymg1pfyn [ 72 ] * gj2rpmenje_idx_0 + rtP . _bias8_Value ; tmp_c = ( tmp_c &
8796093022208ULL ) != 0ULL ? tmp_c | - 8796093022208LL : tmp_c &
8796093022207LL ; tmp_c = ( ( tmp_c & 4398046511104ULL ) != 0ULL ? tmp_c | -
4398046511104LL : tmp_c & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 73 ] *
gj2rpmenje_idx_1 ; tmp_c = ( tmp_c & 8796093022208ULL ) != 0ULL ? tmp_c | -
8796093022208LL : tmp_c & 8796093022207LL ; tmp_c = ( ( tmp_c &
4398046511104ULL ) != 0ULL ? tmp_c | - 4398046511104LL : tmp_c &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 74 ] * gj2rpmenje_idx_2 ; tmp_c
= ( tmp_c & 8796093022208ULL ) != 0ULL ? tmp_c | - 8796093022208LL : tmp_c &
8796093022207LL ; tmp_c = ( ( tmp_c & 4398046511104ULL ) != 0ULL ? tmp_c | -
4398046511104LL : tmp_c & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 75 ] *
gj2rpmenje_idx_3 ; tmp_c = ( tmp_c & 8796093022208ULL ) != 0ULL ? tmp_c | -
8796093022208LL : tmp_c & 8796093022207LL ; tmp_c = ( ( tmp_c &
4398046511104ULL ) != 0ULL ? tmp_c | - 4398046511104LL : tmp_c &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 76 ] * gj2rpmenje_idx_4 ; tmp_c
= ( tmp_c & 8796093022208ULL ) != 0ULL ? tmp_c | - 8796093022208LL : tmp_c &
8796093022207LL ; tmp_c = ( ( tmp_c & 4398046511104ULL ) != 0ULL ? tmp_c | -
4398046511104LL : tmp_c & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 77 ] *
gj2rpmenje_idx_5 ; tmp_c = ( tmp_c & 8796093022208ULL ) != 0ULL ? tmp_c | -
8796093022208LL : tmp_c & 8796093022207LL ; tmp_c = ( ( tmp_c &
4398046511104ULL ) != 0ULL ? tmp_c | - 4398046511104LL : tmp_c &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 78 ] * gj2rpmenje_idx_6 ; tmp_c
= ( tmp_c & 8796093022208ULL ) != 0ULL ? tmp_c | - 8796093022208LL : tmp_c &
8796093022207LL ; tmp_c = ( ( tmp_c & 4398046511104ULL ) != 0ULL ? tmp_c | -
4398046511104LL : tmp_c & 4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 79 ] *
gj2rpmenje_idx_7 ; tmp_c = ( tmp_c & 8796093022208ULL ) != 0ULL ? tmp_c | -
8796093022208LL : tmp_c & 8796093022207LL ; tmp_c = ( ( tmp_c &
4398046511104ULL ) != 0ULL ? tmp_c | - 4398046511104LL : tmp_c &
4398046511103LL ) + ( int64_T ) cyymg1pfyn [ 80 ] * gj2rpmenje_idx_8 ; tmp_c
= ( tmp_c & 8796093022208ULL ) != 0ULL ? tmp_c | - 8796093022208LL : tmp_c &
8796093022207LL ; rtB . jgteqxearg [ 8 ] = ( real32_T ) ( ( tmp_c &
4398046511104ULL ) != 0ULL ? tmp_c | - 4398046511104LL : tmp_c &
4398046511103LL ) * 4.65661287E-10F ; rtB . fonmaxluk5 = mkv3qbkou5 *
bdny0r0qld [ 0 ] ; rtB . ly2e1zoduv = jm4jb5nop1 * bdny0r0qld [ 1 ] ; rtB .
hz5f5wlyee = jm4jb5nop1 * bdny0r0qld [ 0 ] ; rtB . mel3kf0new = mkv3qbkou5 *
bdny0r0qld [ 1 ] ; rtB . htuhckhws0 = rtDW . fuh3bn4ezo [ 0 ] - rtDW .
kzefheif0g [ 0 ] ; rtB . e5k1nos5fp = rtDW . pasm0mbp1y [ 0 ] + rtDW .
jqvl3ulori [ 0 ] ; u = rtDW . aa2p00mqis [ 0 ] * 4096.0F ; v =
muSingleScalarAbs ( u ) ; if ( v < 8.388608E+6F ) { if ( v >= 0.5F ) { u =
muSingleScalarFloor ( u + 0.5F ) ; } else { u *= 0.0F ; } } if (
muSingleScalarIsNaN ( u ) || muSingleScalarIsInf ( u ) ) { u = 0.0F ; } else
{ u = muSingleScalarRem ( u , 3.3554432E+7F ) ; } i = ( int32_T )
muSingleScalarFloor ( u ) ; rtB . ke0zqpublh [ 0 ] = ( i & 16777216U ) != 0U
? i | - 16777216 : i & 16777215 ; u = rtDW . jez5q1v2di [ 0 ] * 4096.0F ; v =
muSingleScalarAbs ( u ) ; if ( v < 8.388608E+6F ) { if ( v >= 0.5F ) { u =
muSingleScalarFloor ( u + 0.5F ) ; } else { u *= 0.0F ; } } if (
muSingleScalarIsNaN ( u ) || muSingleScalarIsInf ( u ) ) { u = 0.0F ; } else
{ u = muSingleScalarRem ( u , 3.3554432E+7F ) ; } i = ( int32_T )
muSingleScalarFloor ( u ) ; rtB . ke0zqpublh [ 1 ] = ( i & 16777216U ) != 0U
? i | - 16777216 : i & 16777215 ; u = hgizml3qp1 * 4096.0F ; v =
muSingleScalarAbs ( u ) ; if ( v < 8.388608E+6F ) { if ( v >= 0.5F ) { u =
muSingleScalarFloor ( u + 0.5F ) ; } else { u *= 0.0F ; } } if (
muSingleScalarIsNaN ( u ) || muSingleScalarIsInf ( u ) ) { u = 0.0F ; } else
{ u = muSingleScalarRem ( u , 3.3554432E+7F ) ; } i = ( int32_T )
muSingleScalarFloor ( u ) ; rtB . ke0zqpublh [ 2 ] = ( i & 16777216U ) != 0U
? i | - 16777216 : i & 16777215 ; u = d1i4jxgfoj * 4096.0F ; v =
muSingleScalarAbs ( u ) ; if ( v < 8.388608E+6F ) { if ( v >= 0.5F ) { u =
muSingleScalarFloor ( u + 0.5F ) ; } else { u *= 0.0F ; } } if (
muSingleScalarIsNaN ( u ) || muSingleScalarIsInf ( u ) ) { u = 0.0F ; } else
{ u = muSingleScalarRem ( u , 3.3554432E+7F ) ; } i = ( int32_T )
muSingleScalarFloor ( u ) ; rtB . ke0zqpublh [ 3 ] = ( i & 16777216U ) != 0U
? i | - 16777216 : i & 16777215 ; u = dagdwu0ljw * 4096.0F ; v =
muSingleScalarAbs ( u ) ; if ( v < 8.388608E+6F ) { if ( v >= 0.5F ) { u =
muSingleScalarFloor ( u + 0.5F ) ; } else { u *= 0.0F ; } } if (
muSingleScalarIsNaN ( u ) || muSingleScalarIsInf ( u ) ) { u = 0.0F ; } else
{ u = muSingleScalarRem ( u , 3.3554432E+7F ) ; } i = ( int32_T )
muSingleScalarFloor ( u ) ; rtB . ke0zqpublh [ 4 ] = ( i & 16777216U ) != 0U
? i | - 16777216 : i & 16777215 ; u = nod352cw4v * 4096.0F ; v =
muSingleScalarAbs ( u ) ; if ( v < 8.388608E+6F ) { if ( v >= 0.5F ) { u =
muSingleScalarFloor ( u + 0.5F ) ; } else { u *= 0.0F ; } } if (
muSingleScalarIsNaN ( u ) || muSingleScalarIsInf ( u ) ) { u = 0.0F ; } else
{ u = muSingleScalarRem ( u , 3.3554432E+7F ) ; } i = ( int32_T )
muSingleScalarFloor ( u ) ; rtB . ke0zqpublh [ 5 ] = ( i & 16777216U ) != 0U
? i | - 16777216 : i & 16777215 ; u = bumwatdafh * 4096.0F ; v =
muSingleScalarAbs ( u ) ; if ( v < 8.388608E+6F ) { if ( v >= 0.5F ) { u =
muSingleScalarFloor ( u + 0.5F ) ; } else { u *= 0.0F ; } } if (
muSingleScalarIsNaN ( u ) || muSingleScalarIsInf ( u ) ) { u = 0.0F ; } else
{ u = muSingleScalarRem ( u , 3.3554432E+7F ) ; } i = ( int32_T )
muSingleScalarFloor ( u ) ; rtB . ke0zqpublh [ 6 ] = ( i & 16777216U ) != 0U
? i | - 16777216 : i & 16777215 ; u = d0hyrjbvrp * 4096.0F ; v =
muSingleScalarAbs ( u ) ; if ( v < 8.388608E+6F ) { if ( v >= 0.5F ) { u =
muSingleScalarFloor ( u + 0.5F ) ; } else { u *= 0.0F ; } } if (
muSingleScalarIsNaN ( u ) || muSingleScalarIsInf ( u ) ) { u = 0.0F ; } else
{ u = muSingleScalarRem ( u , 3.3554432E+7F ) ; } i = ( int32_T )
muSingleScalarFloor ( u ) ; rtB . ke0zqpublh [ 7 ] = ( i & 16777216U ) != 0U
? i | - 16777216 : i & 16777215 ; u = c10u5tt5g5 * 4096.0F ; v =
muSingleScalarAbs ( u ) ; if ( v < 8.388608E+6F ) { if ( v >= 0.5F ) { u =
muSingleScalarFloor ( u + 0.5F ) ; } else { u *= 0.0F ; } } if (
muSingleScalarIsNaN ( u ) || muSingleScalarIsInf ( u ) ) { u = 0.0F ; } else
{ u = muSingleScalarRem ( u , 3.3554432E+7F ) ; } i = ( int32_T )
muSingleScalarFloor ( u ) ; rtB . ke0zqpublh [ 8 ] = ( i & 16777216U ) != 0U
? i | - 16777216 : i & 16777215 ; for ( i = 0 ; i < 9 ; i ++ ) { rtB .
enz5ww01sg [ i ] = rtDW . az4aq4f2to [ i ] ; } rtB . ggxspydiyp = mkv3qbkou5
* bhia010lzv ; rtB . ntn5swsdwf = jm4jb5nop1 * nsgl3oipuf ; rtB . bgjebmhgfv
= jm4jb5nop1 * bhia010lzv ; rtB . j4uzb05eqs = mkv3qbkou5 * nsgl3oipuf ; for
( i = 0 ; i < 9 ; i ++ ) { for ( grxhuiwehd_idx_0 = 0 ; grxhuiwehd_idx_0 < 9
; grxhuiwehd_idx_0 ++ ) { cyymg1pfyn [ grxhuiwehd_idx_0 + 9 * i ] = rtP .
Constant1_Value_mfqrhuom3x [ 9 * grxhuiwehd_idx_0 + i ] ; } } for ( i = 0 ; i
< 9 ; i ++ ) { rtB . i0e4upsk2d [ i ] = cyymg1pfyn [ i ] ; } for ( i = 0 ; i
< 9 ; i ++ ) { rtB . io0z1g0pje [ i ] = cyymg1pfyn [ i + 9 ] ; } for ( i = 0
; i < 9 ; i ++ ) { rtB . gihxrchecp [ i ] = cyymg1pfyn [ i + 18 ] ; } for ( i
= 0 ; i < 9 ; i ++ ) { rtB . hemavelcim [ i ] = cyymg1pfyn [ i + 27 ] ; } for
( i = 0 ; i < 9 ; i ++ ) { rtB . h1tpfgxf3b [ i ] = cyymg1pfyn [ i + 36 ] ; }
for ( i = 0 ; i < 9 ; i ++ ) { rtB . jszybsysr2 [ i ] = cyymg1pfyn [ i + 45 ]
; } for ( i = 0 ; i < 9 ; i ++ ) { rtB . ioigeufkrg [ i ] = cyymg1pfyn [ i +
54 ] ; } for ( i = 0 ; i < 9 ; i ++ ) { rtB . ngwwugiho4 [ i ] = cyymg1pfyn [
i + 63 ] ; } for ( i = 0 ; i < 9 ; i ++ ) { rtB . nd1jlmty5o [ i ] =
cyymg1pfyn [ i + 72 ] ; } okdii0prpb = ( uint16_T ) ( ( uint32_T ) mmn0zxocgd
+ rtP . FixPtConstant_Value ) ; if ( okdii0prpb > rtP . ctr_499_uplimit ) {
rtB . fvfmloctub = rtP . Constant_Value_nxgby3d43k ; } else { rtB .
fvfmloctub = okdii0prpb ; } rtB . loraops0qq = rtDW . lr1nlrmqch [ 0 ] ; rtB
. cxh2bze2aw = rtDW . a44d5qyg12 [ 0 ] ; rtB . m4jtd010un = rtDW . bwkcfpuwid
[ 0 ] ; rtB . fsyrkzjyrx = rtDW . bb0v2ld5vf [ 0 ] ; rtB . klvorwbawb = rtDW
. cno1ak0c3c [ 0 ] ; rtB . oafknyqwix = rtDW . nxk0ojgi44 [ 0 ] ; rtB .
iuqrgdsyyu = rtDW . bubytbfjvq [ 0 ] ; rtB . kffkzglrlg = rtDW . glikpzp24u [
0 ] ; rtB . fmeg1ss5bt = rtDW . hskq4vr1qs [ 0 ] ; rtB . j1vdqdq20c = rtDW .
htr1ntw0w0 [ 0 ] ; rtB . oirs5ucrzg = rtDW . hljbnnt3zw [ 0 ] ; rtB .
g5f1cmb3g1 = rtDW . d2cg15qgjf [ 0 ] ; rtB . lme3ejskfc = rtDW . ir1mqsar5f [
0 ] ; rtB . jvvqwef1jr = rtDW . f1sl003e30 [ 0 ] ; rtB . en2i3j4iug = rtDW .
mz1lyyodga [ 0 ] ; rtB . dwjldlpqwz = rtDW . i22hackosr [ 0 ] ; rtB .
avfxnnnygf = rtDW . hrf0r3epza [ 0 ] ; rtB . bqjbue4zrx = rtDW . l4gldy0ied [
0 ] ; rtB . axkfxspns0 = rtDW . jcgd4tqv41 [ 0 ] ; if ( rtB . dolerm5nyh ) {
rtB . h2h3aoif55 = rtP . Initial_Val2_Value ; rtB . atculhoes1 = rtP .
Initial_Val1_Value ; rtB . ba4ycbfbms = rtP . Initial_Val_Value ; rtB .
d5bxbfmv3h = rtP . Initial_Val3_Value ; rtB . jmg21szmcd = rtP .
Initial_Val4_Value ; rtB . nvio0y23qb = rtP . Initial_Val5_Value ; rtB .
o5rpzk02ux = rtP . Initial_Val6_Value ; rtB . o44jebcpbs = rtP .
Initial_Val7_Value ; rtB . fhua05yaow = rtP . Initial_Val8_Value ; rtB .
ekqxh0o2yy = rtP . Initial_Val9_Value ; } else { rtB . h2h3aoif55 =
mfxncopstb ; rtB . atculhoes1 = mpbkrymds0 ; rtB . ba4ycbfbms = jdebb5lusi ;
rtB . d5bxbfmv3h = fzopdc1y3h ; rtB . jmg21szmcd = j2bjtltjrv ; rtB .
nvio0y23qb = jjijeib3g5 ; rtB . o5rpzk02ux = ftrre2olna ; rtB . o44jebcpbs =
eqwgwo0chw ; rtB . fhua05yaow = nvszulfdmh ; rtB . ekqxh0o2yy = jvzpawhyvp ;
} if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . axle03m4av [ 0 ] = rtDW .
kebzxgfy5a ; rtDW . axle03m4av [ 1 ] = rtDW . pmncprwmz4 ; rtDW . axle03m4av
[ 2 ] = bcptyhlhxz ; rtDW . axle03m4av [ 3 ] = rtDW . g05suawwrk ; rtDW .
axle03m4av [ 4 ] = rtDW . ore24n4522 ; } } if ( ssIsSampleHit ( rtS , 4 , 0 )
) { rtB . nd2ifd1axi [ 0 ] = rtDW . ckuddxo2v5 [ 0 ] ; rtB . nd2ifd1axi [ 1 ]
= rtDW . ckuddxo2v5 [ 1 ] ; rtB . nd2ifd1axi [ 2 ] = rtDW . ckuddxo2v5 [ 2 ]
; pbrhssinnq [ 0 ] = rtDW . hoqlzb3yrr [ 0 ] ; nnuffjzjqz [ 0 ] = rtDW .
d2yav1jvrg [ 0 ] ; pbrhssinnq [ 1 ] = rtDW . hoqlzb3yrr [ 1 ] ; nnuffjzjqz [
1 ] = rtDW . d2yav1jvrg [ 1 ] ; pbrhssinnq [ 2 ] = rtDW . hoqlzb3yrr [ 2 ] ;
nnuffjzjqz [ 2 ] = rtDW . d2yav1jvrg [ 2 ] ; rtB . llye522vj1 = rtDW .
pdli3lyef1 ; for ( i = 0 ; i < 5 ; i ++ ) { hixndcwga0 [ i ] = rtDW .
axle03m4av [ i ] ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit (
rtS , 4 , 0 ) ) { for ( i = 0 ; i < 9 ; i ++ ) { rtDW . evcuev5sfd [ i ] =
gn5gtgcxz0 [ i ] ; } } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { for ( i = 0 ; i
< 9 ; i ++ ) { rtB . ntfnjg0jqj [ i ] = rtDW . evcuev5sfd [ i ] ; } } if (
ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB .
d2xswmz51j = rtDW . inffcupvx2 ; } d1rmwt0esq = ( rtB . d2xswmz51j + rtX .
ptze3ue0cm ) * rtP . k_p_d ; if ( d1rmwt0esq > rtP . lim_pi ) { rtB .
ejyqailfrk = rtP . lim_pi ; } else if ( d1rmwt0esq < - rtP . lim_pi ) { rtB .
ejyqailfrk = - rtP . lim_pi ; } else { rtB . ejyqailfrk = d1rmwt0esq ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB .
mrvvmxjbsp = rtDW . p21lrpi51b ; } k1dmmkojfr = ( rtB . mrvvmxjbsp + rtX .
flellzbl1y ) * rtP . k_p_q ; if ( k1dmmkojfr > rtP . lim_pi ) { rtB .
ghi2pz21ut = rtP . lim_pi ; } else if ( k1dmmkojfr < - rtP . lim_pi ) { rtB .
ghi2pz21ut = - rtP . lim_pi ; } else { rtB . ghi2pz21ut = k1dmmkojfr ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB
. k0tjdml5mw = rtDW . mpvdclcsce ; } if ( ssIsMajorTimeStep ( rtS ) ) { if (
rtB . d5mmalu5vx > 0 ) { if ( ! rtDW . gdbbfmmgdg ) { if ( ssGetTaskTime (
rtS , 1 ) != ssGetTStart ( rtS ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . gdbbfmmgdg =
true ; } } else if ( rtDW . gdbbfmmgdg ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . gdbbfmmgdg =
false ; } } } if ( rtDW . gdbbfmmgdg ) { rtB . js3yk5ooqs = rtB . ejyqailfrk
* muDoubleScalarCos ( rtB . k0tjdml5mw ) - rtB . ghi2pz21ut *
muDoubleScalarSin ( rtB . k0tjdml5mw ) ; rtB . b2ae2knt0i = rtB . ejyqailfrk
* muDoubleScalarSin ( rtB . k0tjdml5mw ) + rtB . ghi2pz21ut *
muDoubleScalarCos ( rtB . k0tjdml5mw ) ; if ( ssIsMajorTimeStep ( rtS ) ) {
srUpdateBC ( rtDW . k0efqstpz0 ) ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) {
if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . ei1bavxqil = rtDW . hma0f53x5s ;
} if ( ssIsMajorTimeStep ( rtS ) ) { if ( rtB . n3swfpwaok > 0 ) { if ( !
rtDW . jd2ppumcjt ) { if ( ssGetTaskTime ( rtS , 1 ) != ssGetTStart ( rtS ) )
{ ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . jd2ppumcjt =
true ; } } else if ( rtDW . jd2ppumcjt ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . jd2ppumcjt =
false ; } } } if ( rtDW . jd2ppumcjt ) { rtB . pnc3vys3n0 = rtB . ejyqailfrk
* muDoubleScalarSin ( rtB . ei1bavxqil ) + rtB . ghi2pz21ut *
muDoubleScalarCos ( rtB . ei1bavxqil ) ; rtB . mxbllj53re = - rtB .
ejyqailfrk * muDoubleScalarCos ( rtB . ei1bavxqil ) + rtB . ghi2pz21ut *
muDoubleScalarSin ( rtB . ei1bavxqil ) ; if ( ssIsMajorTimeStep ( rtS ) ) {
srUpdateBC ( rtDW . jitieevvno ) ; } } if ( rtB . d5mmalu5vx != 0 ) {
cv3amtzpeo_p [ 0 ] = rtB . js3yk5ooqs ; cv3amtzpeo_p [ 1 ] = rtB . b2ae2knt0i
; } else { cv3amtzpeo_p [ 0 ] = rtB . pnc3vys3n0 ; cv3amtzpeo_p [ 1 ] = rtB .
mxbllj53re ; } cv3amtzpeo_p [ 2 ] = rtP . Constant2_Value_c1xcu1ly3c ;
cv3amtzpeo_p [ 3 ] = rtP . Constant2_Value_c1xcu1ly3c ; cv3amtzpeo_p [ 4 ] =
rtP . Constant2_Value_c1xcu1ly3c ; cv3amtzpeo_p [ 5 ] = rtP .
Constant2_Value_c1xcu1ly3c ; cv3amtzpeo_p [ 6 ] = rtP .
Constant2_Value_c1xcu1ly3c ; cv3amtzpeo_p [ 7 ] = rtP .
Constant2_Value_c1xcu1ly3c ; cv3amtzpeo_p [ 8 ] = rtP .
Constant2_Value_c1xcu1ly3c ; memset ( & rtB . agqqnkjpc4 [ 0 ] , 0 , 9U *
sizeof ( real_T ) ) ; for ( i = 0 ; i < 9 ; i ++ ) { for ( grxhuiwehd_idx_0 =
0 ; grxhuiwehd_idx_0 < 9 ; grxhuiwehd_idx_0 ++ ) { rtB . agqqnkjpc4 [ i ] +=
rtP . Constant1_Value_grwerjwqox [ 9 * grxhuiwehd_idx_0 + i ] * cv3amtzpeo_p
[ grxhuiwehd_idx_0 ] ; } } for ( i = 0 ; i < 3 ; i ++ ) { tmp [ i ] = ( rtP .
Gain3_Gain [ i + 3 ] * rtB . agqqnkjpc4 [ 1 ] + rtP . Gain3_Gain [ i ] * rtB
. agqqnkjpc4 [ 0 ] ) + rtP . Gain3_Gain [ i + 6 ] * rtB . agqqnkjpc4 [ 2 ] ;
} kbjxlva2lq = rtP . Gain1_Gain * tmp [ 0 ] ; c3e3zs0dtp = rtP . Gain1_Gain *
tmp [ 1 ] ; if ( rtB . cwnrh0a0wn ) { bxdgvixlrj = kbjxlva2lq ; } else {
bxdgvixlrj = muDoubleScalarHypot ( kbjxlva2lq , c3e3zs0dtp ) ; } if ( rtB .
epstor1a22 ) { bxdgvixlrj = rtP . Constant2_Value ; } if ( bxdgvixlrj > rtP .
um1_UpperSat ) { pywmjctoq0 = rtP . um1_UpperSat ; } else if ( bxdgvixlrj <
rtP . um1_LowerSat ) { pywmjctoq0 = rtP . um1_LowerSat ; } else { pywmjctoq0
= bxdgvixlrj ; } if ( rtB . cwnrh0a0wn ) { bxdgvixlrj = c3e3zs0dtp ; } else {
bxdgvixlrj = muDoubleScalarAtan2 ( c3e3zs0dtp , kbjxlva2lq ) ; } if ( rtB .
epstor1a22 ) { bxdgvixlrj = rtP . Constant1_Value_pc5hbderw4 * ssGetT ( rtS )
* rtP . Freq2_Value + rtB . g4t0xlro5r ; } eaqfmjcnca = muDoubleScalarMod (
bxdgvixlrj , rtP . Constant2_Value_ouhzm4n00j ) ; cqjwvwhkzv ( rtS , rtB .
h3tkzgo55v , pywmjctoq0 , eaqfmjcnca , rtP . f_pwm , & rtB . cqjwvwhkzvh , &
rtDW . cqjwvwhkzvh , & rtP . cqjwvwhkzvh , & rtPrevZCX . cqjwvwhkzvh ) ;
azshdeeeiw ( rtS , rtB . jeqz1ilrpj , pywmjctoq0 , eaqfmjcnca , & rtB .
azshdeeeiw3 , & rtDW . azshdeeeiw3 , & rtP . azshdeeeiw3 ) ; if ( ( int32_T )
rtP . SVPWMGenerator2Level_SwitchingPattern == 1 ) { rtB . flx3sokx1j [ 0 ] =
rtB . cqjwvwhkzvh . hqezd5t15w [ 0 ] ; rtB . flx3sokx1j [ 1 ] = rtB .
cqjwvwhkzvh . d1n40oandv [ 0 ] ; rtB . flx3sokx1j [ 2 ] = rtB . cqjwvwhkzvh .
hqezd5t15w [ 1 ] ; rtB . flx3sokx1j [ 3 ] = rtB . cqjwvwhkzvh . d1n40oandv [
1 ] ; rtB . flx3sokx1j [ 4 ] = rtB . cqjwvwhkzvh . hqezd5t15w [ 2 ] ; rtB .
flx3sokx1j [ 5 ] = rtB . cqjwvwhkzvh . d1n40oandv [ 2 ] ; } else { rtB .
flx3sokx1j [ 0 ] = rtB . azshdeeeiw3 . getzpyfpzt ; rtB . flx3sokx1j [ 1 ] =
rtB . azshdeeeiw3 . gexcbgcs0i ; rtB . flx3sokx1j [ 2 ] = rtB . azshdeeeiw3 .
da1hylhljz ; rtB . flx3sokx1j [ 3 ] = rtB . azshdeeeiw3 . hhdeynni3k ; rtB .
flx3sokx1j [ 4 ] = rtB . azshdeeeiw3 . hx1dswidvn ; rtB . flx3sokx1j [ 5 ] =
rtB . azshdeeeiw3 . ann0jcq1uk ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if
( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . idcpojjs11 = rtB . idhzvwwmxp ; }
if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . fmskolgwcb = rtDW . fe3ipxqiw5 ;
} } if ( ssIsSampleHit ( rtS , 3 , 0 ) && ssIsSampleHit ( rtS , 4 , 0 ) ) {
rtDW . fbadxescvd [ 0 ] = rtP . Constant_Value ; rtDW . fbadxescvd [ 1 ] =
rtP . Constant_Value ; rtDW . fbadxescvd [ 2 ] = rtP . Constant_Value ; } if
( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . inbt3za1lf = rtDW . idcpojjs11 ;
iiszzjm1xe_idx_0 = ( real32_T ) rtDW . fbadxescvd [ 0 ] ; iiszzjm1xe_idx_1 =
( real32_T ) rtDW . fbadxescvd [ 1 ] ; iiszzjm1xe_idx_2 = ( real32_T ) rtDW .
fbadxescvd [ 2 ] ; } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { ltcu0ov5fb [ 0 ]
= ( rtP . Constant_Value != 0.0 ) ; ltcu0ov5fb [ 1 ] = ( rtP . Constant_Value
!= 0.0 ) ; ltcu0ov5fb [ 2 ] = ( rtP . Constant_Value != 0.0 ) ; ltcu0ov5fb [
3 ] = ( rtP . Constant_Value != 0.0 ) ; ltcu0ov5fb [ 4 ] = ( rtP .
Constant_Value != 0.0 ) ; ltcu0ov5fb [ 5 ] = ( rtP . Constant_Value != 0.0 )
; } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 3 , 0 ) ) {
for ( i = 0 ; i < 6 ; i ++ ) { rtB . pro0t00oqzlp [ i ] = rtDW . jsu3fijte22m
[ i ] ; } } for ( i = 0 ; i < 6 ; i ++ ) { if ( rtB . fmskolgwcb ) { rtB .
atklik5qqa [ i ] = rtB . pro0t00oqzlp [ i ] ; } else { rtB . atklik5qqa [ i ]
= rtB . flx3sokx1j [ i ] ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { } if (
ssIsSampleHit ( rtS , 4 , 0 ) ) { if ( rtB . inbt3za1lf ) { rtB . nimpzzl3rt
[ 0 ] = iiszzjm1xe_idx_0 ; rtB . nimpzzl3rt [ 1 ] = iiszzjm1xe_idx_1 ; rtB .
nimpzzl3rt [ 2 ] = iiszzjm1xe_idx_2 ; } else { rtB . nimpzzl3rt [ 0 ] = (
real_T ) rtB . nd2ifd1axi [ 0 ] * 0.000244140625 ; rtB . nimpzzl3rt [ 1 ] = (
real_T ) rtB . nd2ifd1axi [ 1 ] * 0.000244140625 ; rtB . nimpzzl3rt [ 2 ] = (
real_T ) rtB . nd2ifd1axi [ 2 ] * 0.000244140625 ; } } if ( ssIsSampleHit (
rtS , 1 , 0 ) ) { { if ( rtDW . e0liuhgquprw . AQHandles && ssGetLogOutput (
rtS ) ) { sdiWriteSignal ( rtDW . e0liuhgquprw . AQHandles , ssGetTaskTime (
rtS , 1 ) , ( char * ) & rtB . atklik5qqa [ 0 ] + 0 ) ; } } } if (
ssIsSampleHit ( rtS , 2 , 0 ) ) { for ( i = 0 ; i < 12 ; i ++ ) { oifnvc511t
[ i ] = rtDW . nz3xkbxksp [ i ] ; } iry4obo3mj = rtDW . mofgw1cji2 ;
e4fsbsehu2 = rtDW . npqdzcpz4k ; gl2pknaref = ( e4fsbsehu2 == rtP .
CompareToConstant_const_cnyrwuombr ) & rtDW . mofgw1cji2 ; for ( i = 0 ; i <
12 ; i ++ ) { if ( gl2pknaref ) { rtB . jryifpteuq [ i ] = oifnvc511t [ i ] ;
} else { rtB . jryifpteuq [ i ] = rtDW . cmxd2uv3ip [ i ] ; } } for ( i = 0 ;
i < 12 ; i ++ ) { if ( rtDW . hbtp4braxp [ 0 ] ) { echj2jj5d3 [ i ] = rtB .
jryifpteuq [ i ] ; } else { echj2jj5d3 [ i ] = rtP . X0_Value [ i ] ; } } for
( i = 0 ; i < 3 ; i ++ ) { af42yonrt3 [ i ] = 0.0F ; for ( grxhuiwehd_idx_0 =
0 ; grxhuiwehd_idx_0 < 12 ; grxhuiwehd_idx_0 ++ ) { af42yonrt3 [ i ] += rtP .
MultiplyState_constMatrix [ 3 * grxhuiwehd_idx_0 + i ] * echj2jj5d3 [
grxhuiwehd_idx_0 ] ; } } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { rtDW .
lafrvsvgf0 = af42yonrt3 [ 0 ] ; } } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) {
rtB . oi0f1dpmvz = rtDW . lafrvsvgf0 ; if ( ssIsSampleHit ( rtS , 4 , 0 ) ) {
rtDW . my5afrzgkdfq = rtB . oi0f1dpmvz ; } } if ( ssIsSampleHit ( rtS , 4 , 0
) ) { rtB . a4skgo2zdk4r = rtDW . my5afrzgkdfq ; } if ( ssIsSampleHit ( rtS ,
2 , 0 ) && ssIsSampleHit ( rtS , 3 , 0 ) ) { rtDW . og3lno4rre = af42yonrt3 [
1 ] ; } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { rtB . o1jq12suxm = rtDW .
og3lno4rre ; if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . edo3dr0fru5x = rtB
. o1jq12suxm ; } } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . aqrztu4ociaz
= rtDW . edo3dr0fru5x ; } if ( ssIsSampleHit ( rtS , 2 , 0 ) && ssIsSampleHit
( rtS , 3 , 0 ) ) { rtDW . ld5g5vrgmj = af42yonrt3 [ 2 ] ; } if (
ssIsSampleHit ( rtS , 3 , 0 ) ) { rtB . ile2cuirmz = rtDW . ld5g5vrgmj ; if (
ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . hyaxdywynlcl = rtB . ile2cuirmz ; }
} if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . klaa1rzh3fay = rtDW .
hyaxdywynlcl ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS ,
3 , 0 ) ) { rtDW . jpqfmeeeto = rtB . atklik5qqa [ 0 ] ; } if ( ssIsSampleHit
( rtS , 3 , 0 ) ) { ngicsoxznd [ 0 ] = ( real32_T ) rtB . oi0f1dpmvz ;
ngicsoxznd [ 1 ] = ( real32_T ) rtB . o1jq12suxm ; ngicsoxznd [ 2 ] = (
real32_T ) rtB . ile2cuirmz ; bxdgvixlrj = rtB . oi0f1dpmvz * 4096.0 ;
kbjxlva2lq = muDoubleScalarAbs ( bxdgvixlrj ) ; if ( kbjxlva2lq <
4.503599627370496E+15 ) { if ( kbjxlva2lq >= 0.5 ) { bxdgvixlrj =
muDoubleScalarFloor ( bxdgvixlrj + 0.5 ) ; } else { bxdgvixlrj *= 0.0 ; } }
if ( muDoubleScalarIsNaN ( bxdgvixlrj ) || muDoubleScalarIsInf ( bxdgvixlrj )
) { kbjxlva2lq = 0.0 ; } else { kbjxlva2lq = muDoubleScalarRem ( bxdgvixlrj ,
3.3554432E+7 ) ; } i = ( int32_T ) muDoubleScalarFloor ( kbjxlva2lq ) ; rtB .
iaytspuvc2 [ 0 ] = ( i & 16777216U ) != 0U ? i | - 16777216 : i & 16777215 ;
bxdgvixlrj = rtB . o1jq12suxm * 4096.0 ; kbjxlva2lq = muDoubleScalarAbs (
bxdgvixlrj ) ; if ( kbjxlva2lq < 4.503599627370496E+15 ) { if ( kbjxlva2lq >=
0.5 ) { bxdgvixlrj = muDoubleScalarFloor ( bxdgvixlrj + 0.5 ) ; } else {
bxdgvixlrj *= 0.0 ; } } if ( muDoubleScalarIsNaN ( bxdgvixlrj ) ||
muDoubleScalarIsInf ( bxdgvixlrj ) ) { kbjxlva2lq = 0.0 ; } else { kbjxlva2lq
= muDoubleScalarRem ( bxdgvixlrj , 3.3554432E+7 ) ; } i = ( int32_T )
muDoubleScalarFloor ( kbjxlva2lq ) ; rtB . iaytspuvc2 [ 1 ] = ( i & 16777216U
) != 0U ? i | - 16777216 : i & 16777215 ; bxdgvixlrj = rtB . ile2cuirmz *
4096.0 ; kbjxlva2lq = muDoubleScalarAbs ( bxdgvixlrj ) ; if ( kbjxlva2lq <
4.503599627370496E+15 ) { if ( kbjxlva2lq >= 0.5 ) { bxdgvixlrj =
muDoubleScalarFloor ( bxdgvixlrj + 0.5 ) ; } else { bxdgvixlrj *= 0.0 ; } }
if ( muDoubleScalarIsNaN ( bxdgvixlrj ) || muDoubleScalarIsInf ( bxdgvixlrj )
) { kbjxlva2lq = 0.0 ; } else { kbjxlva2lq = muDoubleScalarRem ( bxdgvixlrj ,
3.3554432E+7 ) ; } i = ( int32_T ) muDoubleScalarFloor ( kbjxlva2lq ) ; rtB .
iaytspuvc2 [ 2 ] = ( i & 16777216U ) != 0U ? i | - 16777216 : i & 16777215 ;
if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . aotbj02q5j = rtDW . dq0pmdxppu ;
} rtB . emtc4xb3jh = ( real32_T ) rtB . aotbj02q5j ; } if ( ssIsSampleHit (
rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 3 , 0 ) ) { rtDW . p25vgyovxo = rtB .
atklik5qqa [ 1 ] ; } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { rtB . a0cgfepyxf
= ( real32_T ) rtDW . jpqfmeeeto ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) &&
ssIsSampleHit ( rtS , 3 , 0 ) ) { rtDW . fgxsmumrmw = rtB . atklik5qqa [ 2 ]
; } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { rtB . dakqt0dgf2 = ( real32_T )
rtDW . p25vgyovxo ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit (
rtS , 3 , 0 ) ) { rtDW . p3km4baqfe = rtB . atklik5qqa [ 3 ] ; } if (
ssIsSampleHit ( rtS , 3 , 0 ) ) { rtB . ctjk3zl0rw = ( real32_T ) rtDW .
fgxsmumrmw ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 3
, 0 ) ) { rtDW . agchj4uiph = rtB . atklik5qqa [ 4 ] ; } if ( ssIsSampleHit (
rtS , 3 , 0 ) ) { rtB . jqmsjhg33r = ( real32_T ) rtDW . p3km4baqfe ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 3 , 0 ) ) { rtDW .
fd5nlfaj2u = rtB . atklik5qqa [ 5 ] ; } if ( ssIsSampleHit ( rtS , 3 , 0 ) )
{ rtB . j10c3it1oh = ( real32_T ) rtDW . agchj4uiph ; rtB . nxi2wmkwov = (
real32_T ) rtDW . fd5nlfaj2u ; for ( i = 0 ; i < 6 ; i ++ ) { rtB .
arkmcvldut [ i ] = ltcu0ov5fb [ i ] ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) )
{ rtB . fsoxlkgk5l = rtDW . gvxq4lgohv ; } rtB . ib5sxshjan = ( real32_T )
rtB . fsoxlkgk5l ; } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { for ( i = 0 ; i <
8 ; i ++ ) { bekkbqozei [ i ] = rtDW . hbomutgs5x [ i ] ; } p5cn5ntxmp = (
uint8_T ) ( ( uint32_T ) e4fsbsehu2 + rtP . FixPtConstant_Value_opnmhasca3 )
; if ( p5cn5ntxmp > rtP . CounterLimited_uplimit ) { rtB . aw0y5alaor = rtP .
Constant_Value_lcohz4siwn ; } else { rtB . aw0y5alaor = p5cn5ntxmp ; } rtB .
f0w0cum5km = rtDW . ifa1aifv0v [ 0 ] ; rtB . eprprovalw [ 0 ] = rtB .
a0cgfepyxf ; rtB . eprprovalw [ 1 ] = rtB . jqmsjhg33r ; rtB . eprprovalw [ 2
] = rtB . nxi2wmkwov ; rtB . eprprovalw [ 3 ] = rtB . ctjk3zl0rw ; rtB .
eprprovalw [ 4 ] = rtB . dakqt0dgf2 ; rtB . eprprovalw [ 5 ] = rtB .
j10c3it1oh ; rtB . eprprovalw [ 6 ] = rtB . ib5sxshjan ; rtB . eprprovalw [ 7
] = rtB . emtc4xb3jh ; gy5wd21nmz ( oifnvc511t , rtB . eprprovalw , & rtB .
obefemx0qd ) ; for ( i = 0 ; i < 12 ; i ++ ) { dupe3kwjvt [ i ] = rtB .
obefemx0qd . gwunl2xrbh [ i ] ; } p4z2y3oxrm ( dupe3kwjvt , rtP .
DefaultIndex_Value , rtP . ModeVector8_Value , rtP . Subsystem8_Index , & rtB
. hfxpwwyhz1 ) ; p4z2y3oxrm ( dupe3kwjvt , rtB . hfxpwwyhz1 . f3ngbvxvpa ,
rtP . ModeVector7_Value , rtP . Subsystem7_Index , & rtB . epl0ubbsvb ) ;
p4z2y3oxrm ( dupe3kwjvt , rtB . epl0ubbsvb . f3ngbvxvpa , rtP .
ModeVector6_Value , rtP . Subsystem6_Index , & rtB . imuz2bmqa4 ) ;
p4z2y3oxrm ( dupe3kwjvt , rtB . imuz2bmqa4 . f3ngbvxvpa , rtP .
ModeVector5_Value , rtP . Subsystem5_Index , & rtB . a4jyvx22i5 ) ;
p4z2y3oxrm ( dupe3kwjvt , rtB . a4jyvx22i5 . f3ngbvxvpa , rtP .
ModeVector4_Value , rtP . Subsystem4_Index , & rtB . kmk13inloe ) ;
p4z2y3oxrm ( dupe3kwjvt , rtB . kmk13inloe . f3ngbvxvpa , rtP .
ModeVector3_Value , rtP . Subsystem3_Index , & rtB . liod1hodre ) ;
p4z2y3oxrm ( dupe3kwjvt , rtB . liod1hodre . f3ngbvxvpa , rtP .
ModeVector2_Value , rtP . Subsystem2_Index , & rtB . f52ctbgs3v ) ;
p4z2y3oxrm ( dupe3kwjvt , rtB . f52ctbgs3v . f3ngbvxvpa , rtP .
ModeVector1_Value , rtP . Subsystem1_Index , & rtB . p4z2y3oxrmd ) ; if (
iry4obo3mj ) { av2veoeel0 = rtB . p4z2y3oxrmd . f3ngbvxvpa ; } else {
av2veoeel0 = rtP . Constant_Value_ebjb3omr24 ; } eem3j5utmn = rtDW .
hyopdoshjp ; for ( i = 0 ; i < 12 ; i ++ ) { echj2jj5d3 [ i ] = 0.0F ; } for
( i = 0 ; i < 12 ; i ++ ) { for ( grxhuiwehd_idx_0 = 0 ; grxhuiwehd_idx_0 < 8
; grxhuiwehd_idx_0 ++ ) { echj2jj5d3 [ i ] += rtP . MultiplyInput_constMatrix
[ ( 12 * grxhuiwehd_idx_0 + i ) + 96 * av2veoeel0 ] * rtB . eprprovalw [
grxhuiwehd_idx_0 ] ; } } for ( i = 0 ; i < 12 ; i ++ ) { rtB . dl4p452e1n [ i
] = rtP . Bias_Value [ 12 * av2veoeel0 + i ] + echj2jj5d3 [ i ] ; } } if (
ssIsSampleHit ( rtS , 3 , 0 ) ) { } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { {
if ( rtDW . ityuo0nupl . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . ityuo0nupl . AQHandles , ssGetTaskTime ( rtS , 4 ) ,
( char * ) & rtB . iuri1z2qfy + 0 ) ; } } { if ( rtDW . lrdg4xmzak .
AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . lrdg4xmzak .
AQHandles , ssGetTaskTime ( rtS , 4 ) , ( char * ) & hixndcwga0 [ 0 ] + 0 ) ;
} } { if ( rtDW . fkpb3hpobh . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . fkpb3hpobh . AQHandles , ssGetTaskTime ( rtS , 4 ) ,
( char * ) & rtB . ntfnjg0jqj [ 0 ] + 0 ) ; } } { if ( rtDW . euzuyivlcf .
AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . euzuyivlcf .
AQHandles , ssGetTaskTime ( rtS , 4 ) , ( char * ) & rtB . nd2ifd1axi [ 0 ] +
0 ) ; } } { if ( rtDW . hzgoj3w1ci . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . hzgoj3w1ci . AQHandles , ssGetTaskTime ( rtS , 4 ) ,
( char * ) & pbrhssinnq [ 0 ] + 0 ) ; } } { if ( rtDW . k2wlyn1paf .
AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . k2wlyn1paf .
AQHandles , ssGetTaskTime ( rtS , 4 ) , ( char * ) & nnuffjzjqz [ 0 ] + 0 ) ;
} } { if ( rtDW . f4ugnmm3af . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . f4ugnmm3af . AQHandles , ssGetTaskTime ( rtS , 4 ) ,
( char * ) & rtB . llye522vj1 + 0 ) ; } } rtB . i2luwb2xg3 = ( real_T ) rtB .
llye522vj1 * 0.000244140625 ; rtB . iztliysr2c [ 0 ] = ( real_T ) pbrhssinnq
[ 0 ] * 0.000244140625 ; rtB . iztliysr2c [ 1 ] = ( real_T ) pbrhssinnq [ 1 ]
* 0.000244140625 ; rtB . iztliysr2c [ 2 ] = ( real_T ) pbrhssinnq [ 2 ] *
0.000244140625 ; rtB . dcyymdlgr3 [ 0 ] = ( real_T ) rtB . nd2ifd1axi [ 0 ] *
0.000244140625 ; rtB . dcyymdlgr3 [ 1 ] = ( real_T ) rtB . nd2ifd1axi [ 1 ] *
0.000244140625 ; rtB . dcyymdlgr3 [ 2 ] = ( real_T ) rtB . nd2ifd1axi [ 2 ] *
0.000244140625 ; rtB . gjirmvlhql [ 0 ] = ( real_T ) nnuffjzjqz [ 0 ] *
0.000244140625 ; rtB . gjirmvlhql [ 1 ] = ( real_T ) nnuffjzjqz [ 1 ] *
0.000244140625 ; rtB . gjirmvlhql [ 2 ] = ( real_T ) nnuffjzjqz [ 2 ] *
0.000244140625 ; rtB . kqxgd32mvf = rtDW . kkklfomjr5 [ 0 ] ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW .
hw1g0wvqpq = rtB . j20cbeet2a ; } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) {
cuudaoj10x [ 0 ] = ( rtP . Constant_Value_nf3bb0tq45 != 0.0 ) ; cuudaoj10x [
1 ] = ( rtP . Constant_Value_nf3bb0tq45 != 0.0 ) ; cuudaoj10x [ 2 ] = ( rtP .
Constant_Value_nf3bb0tq45 != 0.0 ) ; cuudaoj10x [ 3 ] = ( rtP .
Constant_Value_nf3bb0tq45 != 0.0 ) ; cuudaoj10x [ 4 ] = ( rtP .
Constant_Value_nf3bb0tq45 != 0.0 ) ; cuudaoj10x [ 5 ] = ( rtP .
Constant_Value_nf3bb0tq45 != 0.0 ) ; if ( ssIsSampleHit ( rtS , 4 , 0 ) ) {
rtDW . neqcp2rk0x [ 0 ] = rtP . Constant_Value_nf3bb0tq45 ; rtDW . neqcp2rk0x
[ 1 ] = rtP . Constant_Value_nf3bb0tq45 ; rtDW . neqcp2rk0x [ 2 ] = rtP .
Constant_Value_nf3bb0tq45 ; } } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB .
bttgnayvtn = rtDW . hw1g0wvqpq ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) &&
ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . iw5qsles1z = rtB . fjlr1apiaj ; } if
( ssIsSampleHit ( rtS , 4 , 0 ) ) { mrsi213w3g_idx_0 = ( real32_T ) rtDW .
neqcp2rk0x [ 0 ] ; mrsi213w3g_idx_1 = ( real32_T ) rtDW . neqcp2rk0x [ 1 ] ;
mrsi213w3g_idx_2 = ( real32_T ) rtDW . neqcp2rk0x [ 2 ] ; } if (
ssIsSampleHit ( rtS , 3 , 0 ) ) { gj0vg0h2tb [ 0 ] = ( rtP .
Constant_Value_mwigsjn0on != 0.0 ) ; gj0vg0h2tb [ 1 ] = ( rtP .
Constant_Value_mwigsjn0on != 0.0 ) ; gj0vg0h2tb [ 2 ] = ( rtP .
Constant_Value_mwigsjn0on != 0.0 ) ; gj0vg0h2tb [ 3 ] = ( rtP .
Constant_Value_mwigsjn0on != 0.0 ) ; gj0vg0h2tb [ 4 ] = ( rtP .
Constant_Value_mwigsjn0on != 0.0 ) ; gj0vg0h2tb [ 5 ] = ( rtP .
Constant_Value_mwigsjn0on != 0.0 ) ; if ( ssIsSampleHit ( rtS , 4 , 0 ) ) {
rtDW . injrnpzipy [ 0 ] = rtP . Constant_Value_mwigsjn0on ; rtDW . injrnpzipy
[ 1 ] = rtP . Constant_Value_mwigsjn0on ; rtDW . injrnpzipy [ 2 ] = rtP .
Constant_Value_mwigsjn0on ; } } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB .
a4s3xvlbex = rtDW . iw5qsles1z ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) &&
ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . gomqyfi1fi = rtP .
simulate_mechanical2_Value ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) {
kgqoy5nldi_idx_0 = ( real32_T ) rtDW . injrnpzipy [ 0 ] ; kgqoy5nldi_idx_1 =
( real32_T ) rtDW . injrnpzipy [ 1 ] ; kgqoy5nldi_idx_2 = ( real32_T ) rtDW .
injrnpzipy [ 2 ] ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit (
rtS , 4 , 0 ) ) { rtDW . dczrefoerg = rtP . simulate_mechanical_Value ; } if
( ssIsSampleHit ( rtS , 4 , 0 ) ) { hynlasc1nw = rtDW . gomqyfi1fi ; rtB .
fbqqxnvweh = rtDW . dczrefoerg ; } for ( i = 0 ; i < 3 ; i ++ ) { tmp [ i ] =
( rtP . Gain3_Gain_gkm2xguh4p [ i + 3 ] * rtB . agqqnkjpc4 [ 4 ] + rtP .
Gain3_Gain_gkm2xguh4p [ i ] * rtB . agqqnkjpc4 [ 3 ] ) + rtP .
Gain3_Gain_gkm2xguh4p [ i + 6 ] * rtB . agqqnkjpc4 [ 5 ] ; } kbjxlva2lq = rtP
. Gain1_Gain_nutmkm45g1 * tmp [ 0 ] ; c3e3zs0dtp = rtP .
Gain1_Gain_nutmkm45g1 * tmp [ 1 ] ; if ( rtB . hxnqngtyf1 ) { bxdgvixlrj =
kbjxlva2lq ; } else { bxdgvixlrj = muDoubleScalarHypot ( kbjxlva2lq ,
c3e3zs0dtp ) ; } if ( rtB . ghxuospbjl ) { bxdgvixlrj = rtP .
Constant2_Value_ayggr1hr00 ; } if ( bxdgvixlrj > rtP .
um1_UpperSat_lvqel1uo0o ) { cj0ekrls2n = rtP . um1_UpperSat_lvqel1uo0o ; }
else if ( bxdgvixlrj < rtP . um1_LowerSat_necuzvpcee ) { cj0ekrls2n = rtP .
um1_LowerSat_necuzvpcee ; } else { cj0ekrls2n = bxdgvixlrj ; } if ( rtB .
hxnqngtyf1 ) { bxdgvixlrj = c3e3zs0dtp ; } else { bxdgvixlrj =
muDoubleScalarAtan2 ( c3e3zs0dtp , kbjxlva2lq ) ; } if ( rtB . ghxuospbjl ) {
bxdgvixlrj = rtP . Constant1_Value_are0ior3pl * ssGetT ( rtS ) * rtP .
Freq2_Value_hfy2fcbazp + rtB . lxu2tizwog ; } j1bjtqkfke = muDoubleScalarMod
( bxdgvixlrj , rtP . Constant2_Value_jrika1x30d ) ; cqjwvwhkzv ( rtS , rtB .
a1jnu0tnvv , cj0ekrls2n , j1bjtqkfke , rtP . f_pwm , & rtB . cstc0v1lpw , &
rtDW . cstc0v1lpw , & rtP . cstc0v1lpw , & rtPrevZCX . cstc0v1lpw ) ;
azshdeeeiw ( rtS , rtB . jt0dbfa543 , cj0ekrls2n , j1bjtqkfke , & rtB .
mzoe5aiivc , & rtDW . mzoe5aiivc , & rtP . mzoe5aiivc ) ; if ( ( int32_T )
rtP . SVPWMGenerator2Level_SwitchingPattern_kmqtzirjjx == 1 ) { n5mry0ynam [
0 ] = rtB . cstc0v1lpw . hqezd5t15w [ 0 ] ; n5mry0ynam [ 1 ] = rtB .
cstc0v1lpw . d1n40oandv [ 0 ] ; n5mry0ynam [ 2 ] = rtB . cstc0v1lpw .
hqezd5t15w [ 1 ] ; n5mry0ynam [ 3 ] = rtB . cstc0v1lpw . d1n40oandv [ 1 ] ;
n5mry0ynam [ 4 ] = rtB . cstc0v1lpw . hqezd5t15w [ 2 ] ; n5mry0ynam [ 5 ] =
rtB . cstc0v1lpw . d1n40oandv [ 2 ] ; } else { n5mry0ynam [ 0 ] = rtB .
mzoe5aiivc . getzpyfpzt ; n5mry0ynam [ 1 ] = rtB . mzoe5aiivc . gexcbgcs0i ;
n5mry0ynam [ 2 ] = rtB . mzoe5aiivc . da1hylhljz ; n5mry0ynam [ 3 ] = rtB .
mzoe5aiivc . hhdeynni3k ; n5mry0ynam [ 4 ] = rtB . mzoe5aiivc . hx1dswidvn ;
n5mry0ynam [ 5 ] = rtB . mzoe5aiivc . ann0jcq1uk ; } for ( i = 0 ; i < 3 ; i
++ ) { tmp [ i ] = ( rtP . Gain3_Gain_bttof010vd [ i + 3 ] * rtB . agqqnkjpc4
[ 7 ] + rtP . Gain3_Gain_bttof010vd [ i ] * rtB . agqqnkjpc4 [ 6 ] ) + rtP .
Gain3_Gain_bttof010vd [ i + 6 ] * rtB . agqqnkjpc4 [ 8 ] ; } kbjxlva2lq = rtP
. Gain1_Gain_bejkcmwgji * tmp [ 0 ] ; c3e3zs0dtp = rtP .
Gain1_Gain_bejkcmwgji * tmp [ 1 ] ; if ( rtB . grg2qcew0n ) { bxdgvixlrj =
kbjxlva2lq ; } else { bxdgvixlrj = muDoubleScalarHypot ( kbjxlva2lq ,
c3e3zs0dtp ) ; } if ( rtB . mp2miztasv ) { bxdgvixlrj = rtP .
Constant2_Value_nvluxn40nk ; } if ( bxdgvixlrj > rtP .
um1_UpperSat_l35ktjv2oo ) { dmvqitgjzr = rtP . um1_UpperSat_l35ktjv2oo ; }
else if ( bxdgvixlrj < rtP . um1_LowerSat_d3qp0zvp4b ) { dmvqitgjzr = rtP .
um1_LowerSat_d3qp0zvp4b ; } else { dmvqitgjzr = bxdgvixlrj ; } if ( rtB .
grg2qcew0n ) { bxdgvixlrj = c3e3zs0dtp ; } else { bxdgvixlrj =
muDoubleScalarAtan2 ( c3e3zs0dtp , kbjxlva2lq ) ; } if ( rtB . mp2miztasv ) {
bxdgvixlrj = rtP . Constant1_Value_eembvftqvk * ssGetT ( rtS ) * rtP .
Freq2_Value_nqc1qew4zf + rtB . imc322aww5 ; } c3nzicj2l0 = muDoubleScalarMod
( bxdgvixlrj , rtP . Constant2_Value_aq5b3qckdj ) ; cqjwvwhkzv ( rtS , rtB .
mdhyl1ygwf , dmvqitgjzr , c3nzicj2l0 , rtP . f_pwm , & rtB . msqwmshj2n , &
rtDW . msqwmshj2n , & rtP . msqwmshj2n , & rtPrevZCX . msqwmshj2n ) ;
azshdeeeiw ( rtS , rtB . p50ijigx25 , dmvqitgjzr , c3nzicj2l0 , & rtB .
biyhxca30f , & rtDW . biyhxca30f , & rtP . biyhxca30f ) ; if ( ( int32_T )
rtP . SVPWMGenerator2Level_SwitchingPattern_b5rdju1jqc == 1 ) { ksrnub5xfk [
0 ] = rtB . msqwmshj2n . hqezd5t15w [ 0 ] ; ksrnub5xfk [ 1 ] = rtB .
msqwmshj2n . d1n40oandv [ 0 ] ; ksrnub5xfk [ 2 ] = rtB . msqwmshj2n .
hqezd5t15w [ 1 ] ; ksrnub5xfk [ 3 ] = rtB . msqwmshj2n . d1n40oandv [ 1 ] ;
ksrnub5xfk [ 4 ] = rtB . msqwmshj2n . hqezd5t15w [ 2 ] ; ksrnub5xfk [ 5 ] =
rtB . msqwmshj2n . d1n40oandv [ 2 ] ; } else { ksrnub5xfk [ 0 ] = rtB .
biyhxca30f . getzpyfpzt ; ksrnub5xfk [ 1 ] = rtB . biyhxca30f . gexcbgcs0i ;
ksrnub5xfk [ 2 ] = rtB . biyhxca30f . da1hylhljz ; ksrnub5xfk [ 3 ] = rtB .
biyhxca30f . hhdeynni3k ; ksrnub5xfk [ 4 ] = rtB . biyhxca30f . hx1dswidvn ;
ksrnub5xfk [ 5 ] = rtB . biyhxca30f . ann0jcq1uk ; } if ( ssIsSampleHit ( rtS
, 1 , 0 ) ) { { if ( rtDW . lnwwdousnr . AQHandles && ssGetLogOutput ( rtS )
) { sdiWriteSignal ( rtDW . lnwwdousnr . AQHandles , ssGetTaskTime ( rtS , 1
) , ( char * ) & rtB . agqqnkjpc4 [ 3 ] + 0 ) ; } } { if ( rtDW . b3y2ruf2y2
. AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . b3y2ruf2y2
. AQHandles , ssGetTaskTime ( rtS , 1 ) , ( char * ) & rtB . agqqnkjpc4 [ 6 ]
+ 0 ) ; } } { if ( rtDW . f0zxs3dlyt . AQHandles && ssGetLogOutput ( rtS ) )
{ sdiWriteSignal ( rtDW . f0zxs3dlyt . AQHandles , ssGetTaskTime ( rtS , 1 )
, ( char * ) & rtB . agqqnkjpc4 [ 0 ] + 0 ) ; } } { if ( rtDW . hdsszfpsby .
AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . hdsszfpsby .
AQHandles , ssGetTaskTime ( rtS , 1 ) , ( char * ) & rtB . ejyqailfrk + 0 ) ;
} } { if ( rtDW . exqvxbdaup . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . exqvxbdaup . AQHandles , ssGetTaskTime ( rtS , 1 ) ,
( char * ) & rtB . ghi2pz21ut + 0 ) ; } } } if ( ssIsSampleHit ( rtS , 4 , 0
) ) { cv3amtzpeo_p [ 0 ] = rtDW . ituktxufmb [ 0 ] ; cv3amtzpeo_p [ 3 ] =
rtDW . epsbkv53pu [ 0 ] ; cv3amtzpeo_p [ 6 ] = rtDW . cmh2vel5ym [ 0 ] ;
cv3amtzpeo_p [ 1 ] = rtDW . ituktxufmb [ 1 ] ; cv3amtzpeo_p [ 4 ] = rtDW .
epsbkv53pu [ 1 ] ; cv3amtzpeo_p [ 7 ] = rtDW . cmh2vel5ym [ 1 ] ;
cv3amtzpeo_p [ 2 ] = rtDW . ituktxufmb [ 2 ] ; cv3amtzpeo_p [ 5 ] = rtDW .
epsbkv53pu [ 2 ] ; cv3amtzpeo_p [ 8 ] = rtDW . cmh2vel5ym [ 2 ] ; for ( i = 0
; i < 9 ; i ++ ) { ck1wijicgc [ i ] = 0.0 ; for ( grxhuiwehd_idx_0 = 0 ;
grxhuiwehd_idx_0 < 9 ; grxhuiwehd_idx_0 ++ ) { ck1wijicgc [ i ] += rtP . c [
9 * grxhuiwehd_idx_0 + i ] * cv3amtzpeo_p [ grxhuiwehd_idx_0 ] ; } } if ( rtB
. mciby2bhmc > 0 ) { rtB . pmyyd40jng = ck1wijicgc [ 0 ] * muDoubleScalarCos
( rtB . i2luwb2xg3 ) + ck1wijicgc [ 1 ] * muDoubleScalarSin ( rtB .
i2luwb2xg3 ) ; rtB . muhro1pthm = - ck1wijicgc [ 0 ] * muDoubleScalarSin (
rtB . i2luwb2xg3 ) + ck1wijicgc [ 1 ] * muDoubleScalarCos ( rtB . i2luwb2xg3
) ; if ( ssIsMajorTimeStep ( rtS ) ) { srUpdateBC ( rtDW . ip0d0t1043 ) ; } }
if ( rtB . oksi514ex4 > 0 ) { rtB . hfsnjuqzrn = ck1wijicgc [ 0 ] *
muDoubleScalarSin ( rtB . i2luwb2xg3 ) - ck1wijicgc [ 1 ] * muDoubleScalarCos
( rtB . i2luwb2xg3 ) ; rtB . kt0x35emh1 = ck1wijicgc [ 0 ] *
muDoubleScalarCos ( rtB . i2luwb2xg3 ) + ck1wijicgc [ 1 ] * muDoubleScalarSin
( rtB . i2luwb2xg3 ) ; if ( ssIsMajorTimeStep ( rtS ) ) { srUpdateBC ( rtDW .
i1c4xekdhn ) ; } } if ( rtB . mciby2bhmc != 0 ) { k50sau3xmx [ 0 ] = rtB .
pmyyd40jng ; k50sau3xmx [ 1 ] = rtB . muhro1pthm ; } else { k50sau3xmx [ 0 ]
= rtB . hfsnjuqzrn ; k50sau3xmx [ 1 ] = rtB . kt0x35emh1 ; } { if ( rtDW .
ettcurcs0e . AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW .
ettcurcs0e . AQHandles , ssGetTaskTime ( rtS , 4 ) , ( char * ) & k50sau3xmx
[ 0 ] + 0 ) ; } } { if ( rtDW . c0e12yj12u . AQHandles && ssGetLogOutput (
rtS ) ) { sdiWriteSignal ( rtDW . c0e12yj12u . AQHandles , ssGetTaskTime (
rtS , 4 ) , ( char * ) & k50sau3xmx [ 1 ] + 0 ) ; } } rtB . forvj4qm2y = rtP
. Constant_Value_k0oeb5ytii - k50sau3xmx [ 0 ] ; } if ( d1rmwt0esq > rtP .
lim_pi ) { bxdgvixlrj = d1rmwt0esq - rtP . lim_pi ; } else if ( d1rmwt0esq >=
- rtP . lim_pi ) { bxdgvixlrj = 0.0 ; } else { bxdgvixlrj = d1rmwt0esq - ( -
rtP . lim_pi ) ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS
, 4 , 0 ) ) { rtB . jfzsdgbq5e = rtDW . fqvcumyba1 ; } kbjxlva2lq =
muDoubleScalarSign ( bxdgvixlrj ) ; if ( muDoubleScalarIsNaN ( kbjxlva2lq ) )
{ kbjxlva2lq = 0.0 ; } else { kbjxlva2lq = muDoubleScalarRem ( kbjxlva2lq ,
256.0 ) ; } iry4obo3mj = ( ( kbjxlva2lq < 0.0 ? ( int32_T ) ( int8_T ) - (
int8_T ) ( uint8_T ) - kbjxlva2lq : ( int32_T ) ( int8_T ) ( uint8_T )
kbjxlva2lq ) == rtB . jfzsdgbq5e ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) {
kbjxlva2lq = muDoubleScalarSign ( rtP . k_p_d ) ; if ( muDoubleScalarIsNaN (
kbjxlva2lq ) ) { kbjxlva2lq = 0.0 ; } else { kbjxlva2lq = muDoubleScalarRem (
kbjxlva2lq , 256.0 ) ; } rtB . a1ijhl4wri = ( ( kbjxlva2lq < 0.0 ? ( int32_T
) ( int8_T ) - ( int8_T ) ( uint8_T ) - kbjxlva2lq : ( int32_T ) ( int8_T ) (
uint8_T ) kbjxlva2lq ) == rtP . Constant_Value_isqfwdnanj ) ; rtB .
fjcgdlcjwe = ! rtB . a1ijhl4wri ; } rtB . nh3gjjgpvk = ( ( rtP .
ZeroGain_Gain * d1rmwt0esq != bxdgvixlrj ) && ( ( iry4obo3mj && rtB .
a1ijhl4wri ) || ( ( ! iry4obo3mj ) && rtB . fjcgdlcjwe ) ) ) ; if (
ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . k2ndgrxbvv = rtP . k_i_d * rtB .
forvj4qm2y ; kbjxlva2lq = muDoubleScalarSign ( rtB . k2ndgrxbvv ) ; if (
muDoubleScalarIsNaN ( kbjxlva2lq ) ) { kbjxlva2lq = 0.0 ; } else { kbjxlva2lq
= muDoubleScalarRem ( kbjxlva2lq , 256.0 ) ; } rtB . hbkhdg0qsb = ( int8_T )
( kbjxlva2lq < 0.0 ? ( int32_T ) ( int8_T ) - ( int8_T ) ( uint8_T ) -
kbjxlva2lq : ( int32_T ) ( int8_T ) ( uint8_T ) kbjxlva2lq ) ; rtB .
jmtjax2f4t = rtB . amb4v03txh - k50sau3xmx [ 1 ] ; } if ( ssIsSampleHit ( rtS
, 1 , 0 ) ) { if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . gqp4loxl10 = rtDW
. cgg3v13mlz ; } if ( rtDW . py4iuvrbea ) { rtB . cqqwj4hgbc = rtP .
Constant1_Value ; } else { rtB . cqqwj4hgbc = rtB . gqp4loxl10 ; } if (
ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . myemztkk1m = rtDW . njfpshnpni ; } }
if ( k1dmmkojfr > rtP . lim_pi ) { d1rmwt0esq = k1dmmkojfr - rtP . lim_pi ; }
else if ( k1dmmkojfr >= - rtP . lim_pi ) { d1rmwt0esq = 0.0 ; } else {
d1rmwt0esq = k1dmmkojfr - ( - rtP . lim_pi ) ; } kbjxlva2lq =
muDoubleScalarSign ( d1rmwt0esq ) ; if ( muDoubleScalarIsNaN ( kbjxlva2lq ) )
{ kbjxlva2lq = 0.0 ; } else { kbjxlva2lq = muDoubleScalarRem ( kbjxlva2lq ,
256.0 ) ; } iry4obo3mj = ( ( kbjxlva2lq < 0.0 ? ( int32_T ) ( int8_T ) - (
int8_T ) ( uint8_T ) - kbjxlva2lq : ( int32_T ) ( int8_T ) ( uint8_T )
kbjxlva2lq ) == rtB . myemztkk1m ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) {
kbjxlva2lq = muDoubleScalarSign ( rtP . k_p_q ) ; if ( muDoubleScalarIsNaN (
kbjxlva2lq ) ) { kbjxlva2lq = 0.0 ; } else { kbjxlva2lq = muDoubleScalarRem (
kbjxlva2lq , 256.0 ) ; } rtB . od5ai22z2l = ( ( kbjxlva2lq < 0.0 ? ( int32_T
) ( int8_T ) - ( int8_T ) ( uint8_T ) - kbjxlva2lq : ( int32_T ) ( int8_T ) (
uint8_T ) kbjxlva2lq ) == rtP . Constant_Value_fbzm1lgfms ) ; rtB .
ksgsqnb2ei = ! rtB . od5ai22z2l ; } rtB . oru1rzybc2 = ( ( rtP .
ZeroGain_Gain_b4r1gxoc4f * k1dmmkojfr != d1rmwt0esq ) && ( ( iry4obo3mj &&
rtB . od5ai22z2l ) || ( ( ! iry4obo3mj ) && rtB . ksgsqnb2ei ) ) ) ; if (
ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . bohcvczirh = rtP . k_i_q * rtB .
jmtjax2f4t ; kbjxlva2lq = muDoubleScalarSign ( rtB . bohcvczirh ) ; if (
muDoubleScalarIsNaN ( kbjxlva2lq ) ) { kbjxlva2lq = 0.0 ; } else { kbjxlva2lq
= muDoubleScalarRem ( kbjxlva2lq , 256.0 ) ; } rtB . j3et02wxql = ( int8_T )
( kbjxlva2lq < 0.0 ? ( int32_T ) ( int8_T ) - ( int8_T ) ( uint8_T ) -
kbjxlva2lq : ( int32_T ) ( int8_T ) ( uint8_T ) kbjxlva2lq ) ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB
. i3srfw2hbe = rtDW . ffjft2t0pj ; rtB . mt1ygms2s1 = rtDW . e5cexk5tsa ; }
if ( rtDW . a43rt5p5qk ) { rtB . nwpl41ljbn = rtP .
Constant1_Value_ldif3tdbbp ; } else { rtB . nwpl41ljbn = rtB . i3srfw2hbe ; }
if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { for ( i = 0 ; i < 6 ; i ++ ) { rtB .
pro0t00oqzl [ i ] = rtDW . jsu3fijte22 [ i ] ; } } } for ( i = 0 ; i < 6 ; i
++ ) { if ( rtB . mt1ygms2s1 ) { rtB . dkskqk5nay [ i ] = rtB . pro0t00oqzl [
i ] ; } else { rtB . dkskqk5nay [ i ] = n5mry0ynam [ i ] ; } } if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { if
( rtB . bttgnayvtn ) { rtB . kdtkapks5q [ 0 ] = mrsi213w3g_idx_0 ; rtB .
kdtkapks5q [ 1 ] = mrsi213w3g_idx_1 ; rtB . kdtkapks5q [ 2 ] =
mrsi213w3g_idx_2 ; } else { rtB . kdtkapks5q [ 0 ] = ( real_T ) pbrhssinnq [
0 ] * 0.000244140625 ; rtB . kdtkapks5q [ 1 ] = ( real_T ) pbrhssinnq [ 1 ] *
0.000244140625 ; rtB . kdtkapks5q [ 2 ] = ( real_T ) pbrhssinnq [ 2 ] *
0.000244140625 ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { { if ( rtDW .
e0liuhgqupr . AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW .
e0liuhgqupr . AQHandles , ssGetTaskTime ( rtS , 1 ) , ( char * ) & rtB .
dkskqk5nay [ 0 ] + 0 ) ; } } } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { for ( i
= 0 ; i < 12 ; i ++ ) { nzdhboavpu [ i ] = rtDW . etncgat1qk [ i ] ; }
ehrn3b0ham = rtDW . fmvtpht2wc ; kxqrijm5xr = rtDW . bjzrd2jgh1 ; iry4obo3mj
= ( kxqrijm5xr == rtP . CompareToConstant_const_fvoxtyn5vv ) & rtDW .
fmvtpht2wc ; for ( i = 0 ; i < 12 ; i ++ ) { if ( iry4obo3mj ) { rtB .
brenn0ae3u [ i ] = nzdhboavpu [ i ] ; } else { rtB . brenn0ae3u [ i ] = rtDW
. j0pfyx5sl0 [ i ] ; } } for ( i = 0 ; i < 12 ; i ++ ) { if ( rtDW .
jlwpaqqpol [ 0 ] ) { echj2jj5d3 [ i ] = rtB . brenn0ae3u [ i ] ; } else {
echj2jj5d3 [ i ] = rtP . X0_Value_osgqfzom1r [ i ] ; } } for ( i = 0 ; i < 3
; i ++ ) { dapu0byl3k [ i ] = 0.0F ; for ( grxhuiwehd_idx_0 = 0 ;
grxhuiwehd_idx_0 < 12 ; grxhuiwehd_idx_0 ++ ) { dapu0byl3k [ i ] += rtP .
MultiplyState_constMatrix_eohiapchpm [ 3 * grxhuiwehd_idx_0 + i ] *
echj2jj5d3 [ grxhuiwehd_idx_0 ] ; } } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) {
rtDW . bjkklesnma = dapu0byl3k [ 0 ] ; } } if ( ssIsSampleHit ( rtS , 3 , 0 )
) { rtB . mj20pqbu5g = rtDW . bjkklesnma ; if ( ssIsSampleHit ( rtS , 4 , 0 )
) { rtDW . my5afrzgkdf = rtB . mj20pqbu5g ; } } if ( ssIsSampleHit ( rtS , 4
, 0 ) ) { rtB . a4skgo2zdk4 = rtDW . my5afrzgkdf ; } if ( ssIsSampleHit ( rtS
, 2 , 0 ) && ssIsSampleHit ( rtS , 3 , 0 ) ) { rtDW . nsaa1gti0b = dapu0byl3k
[ 1 ] ; } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { rtB . oed0sm4hyv = rtDW .
nsaa1gti0b ; if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . edo3dr0fru5 = rtB
. oed0sm4hyv ; } } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . aqrztu4ocia =
rtDW . edo3dr0fru5 ; } if ( ssIsSampleHit ( rtS , 2 , 0 ) && ssIsSampleHit (
rtS , 3 , 0 ) ) { rtDW . ghx0ts2zzs = dapu0byl3k [ 2 ] ; } if ( ssIsSampleHit
( rtS , 3 , 0 ) ) { rtB . aspz402pif = rtDW . ghx0ts2zzs ; if ( ssIsSampleHit
( rtS , 4 , 0 ) ) { rtDW . hyaxdywynlc = rtB . aspz402pif ; } } if (
ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . klaa1rzh3fa = rtDW . hyaxdywynlc ; }
if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 3 , 0 ) ) { rtDW
. o13fmizguv = rtB . dkskqk5nay [ 0 ] ; } if ( ssIsSampleHit ( rtS , 3 , 0 )
) { gbmbic5vi1 [ 0 ] = ( real32_T ) rtB . mj20pqbu5g ; gbmbic5vi1 [ 1 ] = (
real32_T ) rtB . oed0sm4hyv ; gbmbic5vi1 [ 2 ] = ( real32_T ) rtB .
aspz402pif ; bxdgvixlrj = rtB . mj20pqbu5g * 4096.0 ; kbjxlva2lq =
muDoubleScalarAbs ( bxdgvixlrj ) ; if ( kbjxlva2lq < 4.503599627370496E+15 )
{ if ( kbjxlva2lq >= 0.5 ) { bxdgvixlrj = muDoubleScalarFloor ( bxdgvixlrj +
0.5 ) ; } else { bxdgvixlrj *= 0.0 ; } } if ( muDoubleScalarIsNaN (
bxdgvixlrj ) || muDoubleScalarIsInf ( bxdgvixlrj ) ) { kbjxlva2lq = 0.0 ; }
else { kbjxlva2lq = muDoubleScalarRem ( bxdgvixlrj , 3.3554432E+7 ) ; } i = (
int32_T ) muDoubleScalarFloor ( kbjxlva2lq ) ; l1bmi31zy3_idx_0 = ( i &
16777216U ) != 0U ? i | - 16777216 : i & 16777215 ; bxdgvixlrj = rtB .
oed0sm4hyv * 4096.0 ; kbjxlva2lq = muDoubleScalarAbs ( bxdgvixlrj ) ; if (
kbjxlva2lq < 4.503599627370496E+15 ) { if ( kbjxlva2lq >= 0.5 ) { bxdgvixlrj
= muDoubleScalarFloor ( bxdgvixlrj + 0.5 ) ; } else { bxdgvixlrj *= 0.0 ; } }
if ( muDoubleScalarIsNaN ( bxdgvixlrj ) || muDoubleScalarIsInf ( bxdgvixlrj )
) { kbjxlva2lq = 0.0 ; } else { kbjxlva2lq = muDoubleScalarRem ( bxdgvixlrj ,
3.3554432E+7 ) ; } i = ( int32_T ) muDoubleScalarFloor ( kbjxlva2lq ) ;
l1bmi31zy3_idx_1 = ( i & 16777216U ) != 0U ? i | - 16777216 : i & 16777215 ;
bxdgvixlrj = rtB . aspz402pif * 4096.0 ; kbjxlva2lq = muDoubleScalarAbs (
bxdgvixlrj ) ; if ( kbjxlva2lq < 4.503599627370496E+15 ) { if ( kbjxlva2lq >=
0.5 ) { bxdgvixlrj = muDoubleScalarFloor ( bxdgvixlrj + 0.5 ) ; } else {
bxdgvixlrj *= 0.0 ; } } if ( muDoubleScalarIsNaN ( bxdgvixlrj ) ||
muDoubleScalarIsInf ( bxdgvixlrj ) ) { kbjxlva2lq = 0.0 ; } else { kbjxlva2lq
= muDoubleScalarRem ( bxdgvixlrj , 3.3554432E+7 ) ; } i = ( int32_T )
muDoubleScalarFloor ( kbjxlva2lq ) ; l1bmi31zy3_idx_2 = ( i & 16777216U ) !=
0U ? i | - 16777216 : i & 16777215 ; if ( ssIsSampleHit ( rtS , 4 , 0 ) ) {
rtB . f1keoylfm3 = rtDW . anqq4l0npb ; } rtB . ifeyoqsf33 = ( real32_T ) rtB
. f1keoylfm3 ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS ,
3 , 0 ) ) { rtDW . hdglqralt5 = rtB . dkskqk5nay [ 1 ] ; } if ( ssIsSampleHit
( rtS , 3 , 0 ) ) { rtB . kcblg0vlib = ( real32_T ) rtDW . o13fmizguv ; } if
( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 3 , 0 ) ) { rtDW .
ptnxk4g0lc = rtB . dkskqk5nay [ 2 ] ; } if ( ssIsSampleHit ( rtS , 3 , 0 ) )
{ rtB . otf010jouj = ( real32_T ) rtDW . hdglqralt5 ; } if ( ssIsSampleHit (
rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 3 , 0 ) ) { rtDW . pjnb2ek2e3 = rtB .
dkskqk5nay [ 3 ] ; } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { rtB . i5wwklu4fv
= ( real32_T ) rtDW . ptnxk4g0lc ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) &&
ssIsSampleHit ( rtS , 3 , 0 ) ) { rtDW . m0rv3vqddv = rtB . dkskqk5nay [ 4 ]
; } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { rtB . i5kvikzb3h = ( real32_T )
rtDW . pjnb2ek2e3 ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit (
rtS , 3 , 0 ) ) { rtDW . o10ebbt22e = rtB . dkskqk5nay [ 5 ] ; } if (
ssIsSampleHit ( rtS , 3 , 0 ) ) { rtB . evlbtuq3cx = ( real32_T ) rtDW .
m0rv3vqddv ; rtB . in3lhsbtco = ( real32_T ) rtDW . o10ebbt22e ; for ( i = 0
; i < 6 ; i ++ ) { rtB . lvxw1arzhe [ i ] = cuudaoj10x [ i ] ; } if (
ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . a1el3w34yn = rtDW . mam5vcqfvx ; }
rtB . fsedjavxts = ( real32_T ) rtB . a1el3w34yn ; } if ( ssIsSampleHit ( rtS
, 2 , 0 ) ) { for ( i = 0 ; i < 8 ; i ++ ) { anmq1qibli [ i ] = rtDW .
otdqomronl [ i ] ; } drgpwpv0fx = ( uint8_T ) ( ( uint32_T ) kxqrijm5xr + rtP
. FixPtConstant_Value_ixzugyupnp ) ; if ( drgpwpv0fx > rtP .
CounterLimited_uplimit_fvgmipctvh ) { rtB . e2ntsret2e = rtP .
Constant_Value_fm1213sgjm ; } else { rtB . e2ntsret2e = drgpwpv0fx ; } rtB .
brsz4ajf4x = rtDW . o2nyvbjxnw [ 0 ] ; rtB . asxknbd3q5 [ 0 ] = rtB .
kcblg0vlib ; rtB . asxknbd3q5 [ 1 ] = rtB . i5kvikzb3h ; rtB . asxknbd3q5 [ 2
] = rtB . in3lhsbtco ; rtB . asxknbd3q5 [ 3 ] = rtB . i5wwklu4fv ; rtB .
asxknbd3q5 [ 4 ] = rtB . otf010jouj ; rtB . asxknbd3q5 [ 5 ] = rtB .
evlbtuq3cx ; rtB . asxknbd3q5 [ 6 ] = rtB . fsedjavxts ; rtB . asxknbd3q5 [ 7
] = rtB . ifeyoqsf33 ; gy5wd21nmz ( nzdhboavpu , rtB . asxknbd3q5 , & rtB .
mwi1r4mwtx ) ; for ( i = 0 ; i < 12 ; i ++ ) { dnrpkzm5vi [ i ] = rtB .
mwi1r4mwtx . gwunl2xrbh [ i ] ; } p4z2y3oxrm ( dnrpkzm5vi , rtP .
DefaultIndex_Value_dlqxo25nwp , rtP . ModeVector8_Value_pe5qwse0zo , rtP .
Subsystem8_Index_fzlqi5zbx5 , & rtB . ndadpcsjlu ) ; p4z2y3oxrm ( dnrpkzm5vi
, rtB . ndadpcsjlu . f3ngbvxvpa , rtP . ModeVector7_Value_exy1mfuwew , rtP .
Subsystem7_Index_hzi3xwpiyv , & rtB . bvam4ywori ) ; p4z2y3oxrm ( dnrpkzm5vi
, rtB . bvam4ywori . f3ngbvxvpa , rtP . ModeVector6_Value_be5qaduvq0 , rtP .
Subsystem6_Index_g31i2fthbw , & rtB . fpkdn4t3sg ) ; p4z2y3oxrm ( dnrpkzm5vi
, rtB . fpkdn4t3sg . f3ngbvxvpa , rtP . ModeVector5_Value_mcfamzdv4h , rtP .
Subsystem5_Index_glcvjbpr4j , & rtB . itzps5ovbe ) ; p4z2y3oxrm ( dnrpkzm5vi
, rtB . itzps5ovbe . f3ngbvxvpa , rtP . ModeVector4_Value_bvzbygmfek , rtP .
Subsystem4_Index_gjtpscjc3t , & rtB . nnjygkohqv ) ; p4z2y3oxrm ( dnrpkzm5vi
, rtB . nnjygkohqv . f3ngbvxvpa , rtP . ModeVector3_Value_dpbdjp1pks , rtP .
Subsystem3_Index_jyh2hyuoat , & rtB . ijklzzyo04 ) ; p4z2y3oxrm ( dnrpkzm5vi
, rtB . ijklzzyo04 . f3ngbvxvpa , rtP . ModeVector2_Value_pbdosmlzxp , rtP .
Subsystem2_Index_o2hydk3gbe , & rtB . kfdyhargi1 ) ; p4z2y3oxrm ( dnrpkzm5vi
, rtB . kfdyhargi1 . f3ngbvxvpa , rtP . ModeVector1_Value_lzg1v22s1n , rtP .
Subsystem1_Index_gamunef4go , & rtB . bbywkhmyky ) ; if ( ehrn3b0ham ) {
av2veoeel0 = rtB . bbywkhmyky . f3ngbvxvpa ; } else { av2veoeel0 = rtP .
Constant_Value_h33j5qc3ne ; } kc2bmjruge = rtDW . avqcisj0g1 ; for ( i = 0 ;
i < 12 ; i ++ ) { echj2jj5d3 [ i ] = 0.0F ; } for ( i = 0 ; i < 12 ; i ++ ) {
for ( grxhuiwehd_idx_0 = 0 ; grxhuiwehd_idx_0 < 8 ; grxhuiwehd_idx_0 ++ ) {
echj2jj5d3 [ i ] += rtP . MultiplyInput_constMatrix_ny0mxowoiz [ ( 12 *
grxhuiwehd_idx_0 + i ) + 96 * av2veoeel0 ] * rtB . asxknbd3q5 [
grxhuiwehd_idx_0 ] ; } } for ( i = 0 ; i < 12 ; i ++ ) { rtB . fld2qyvslw [ i
] = rtP . Bias_Value_aaxy53sl5x [ 12 * av2veoeel0 + i ] + echj2jj5d3 [ i ] ;
} } if ( ssIsSampleHit ( rtS , 3 , 0 ) && ssIsSampleHit ( rtS , 4 , 0 ) ) {
rtDW . niztd2zg4p [ 0 ] = l1bmi31zy3_idx_0 ; rtDW . niztd2zg4p [ 1 ] =
l1bmi31zy3_idx_1 ; rtDW . niztd2zg4p [ 2 ] = l1bmi31zy3_idx_2 ; } if (
ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . p1wjqkompn [ 0 ] = rtDW . niztd2zg4p
[ 0 ] ; rtB . p1wjqkompn [ 1 ] = rtDW . niztd2zg4p [ 1 ] ; rtB . p1wjqkompn [
2 ] = rtDW . niztd2zg4p [ 2 ] ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if (
ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . aondhpk131 = rtDW . d2ne5d41vh ; } if
( ssIsSampleHit ( rtS , 3 , 0 ) ) { for ( i = 0 ; i < 6 ; i ++ ) { rtB .
pro0t00oqz [ i ] = rtDW . jsu3fijte2 [ i ] ; } } } for ( i = 0 ; i < 6 ; i ++
) { if ( rtB . aondhpk131 ) { rtB . cf5pwifjmr [ i ] = rtB . pro0t00oqz [ i ]
; } else { rtB . cf5pwifjmr [ i ] = ksrnub5xfk [ i ] ; } } if ( ssIsSampleHit
( rtS , 1 , 0 ) ) { } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { if ( rtB .
a4s3xvlbex ) { rtB . kwpowwsiez [ 0 ] = kgqoy5nldi_idx_0 ; rtB . kwpowwsiez [
1 ] = kgqoy5nldi_idx_1 ; rtB . kwpowwsiez [ 2 ] = kgqoy5nldi_idx_2 ; } else {
rtB . kwpowwsiez [ 0 ] = ( real_T ) nnuffjzjqz [ 0 ] * 0.000244140625 ; rtB .
kwpowwsiez [ 1 ] = ( real_T ) nnuffjzjqz [ 1 ] * 0.000244140625 ; rtB .
kwpowwsiez [ 2 ] = ( real_T ) nnuffjzjqz [ 2 ] * 0.000244140625 ; } } if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { { if ( rtDW . e0liuhgqup . AQHandles &&
ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . e0liuhgqup . AQHandles ,
ssGetTaskTime ( rtS , 1 ) , ( char * ) & rtB . cf5pwifjmr [ 0 ] + 0 ) ; } } }
if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { for ( i = 0 ; i < 12 ; i ++ ) {
hxx1o3o0xn [ i ] = rtDW . oyxqmd0f4v [ i ] ; } ew0ut03d54 = rtDW . lbwbhxgeac
; jyxstc4ejt = rtDW . llxyyz4q5x ; ehrn3b0ham = ( jyxstc4ejt == rtP .
CompareToConstant_const_kipk51db13 ) & rtDW . lbwbhxgeac ; for ( i = 0 ; i <
12 ; i ++ ) { if ( ehrn3b0ham ) { rtB . jiuomirfvx [ i ] = hxx1o3o0xn [ i ] ;
} else { rtB . jiuomirfvx [ i ] = rtDW . cdd1gh0rmi [ i ] ; } } for ( i = 0 ;
i < 12 ; i ++ ) { if ( rtDW . lgjrfdubva [ 0 ] ) { echj2jj5d3 [ i ] = rtB .
jiuomirfvx [ i ] ; } else { echj2jj5d3 [ i ] = rtP . X0_Value_dgtnjkgayi [ i
] ; } } for ( i = 0 ; i < 3 ; i ++ ) { mc34jx2fmw [ i ] = 0.0F ; for (
grxhuiwehd_idx_0 = 0 ; grxhuiwehd_idx_0 < 12 ; grxhuiwehd_idx_0 ++ ) {
mc34jx2fmw [ i ] += rtP . MultiplyState_constMatrix_d53rujt10a [ 3 *
grxhuiwehd_idx_0 + i ] * echj2jj5d3 [ grxhuiwehd_idx_0 ] ; } } if (
ssIsSampleHit ( rtS , 3 , 0 ) ) { rtDW . cblzsrog5u = mc34jx2fmw [ 0 ] ; } }
if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { rtB . jpqnsdsvax = rtDW . cblzsrog5u ;
if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . my5afrzgkd = rtB . jpqnsdsvax ;
} } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . a4skgo2zdk = rtDW .
my5afrzgkd ; } if ( ssIsSampleHit ( rtS , 2 , 0 ) && ssIsSampleHit ( rtS , 3
, 0 ) ) { rtDW . nqfbacpvcp = mc34jx2fmw [ 1 ] ; } if ( ssIsSampleHit ( rtS ,
3 , 0 ) ) { rtB . a3hcsd5djm = rtDW . nqfbacpvcp ; if ( ssIsSampleHit ( rtS ,
4 , 0 ) ) { rtDW . edo3dr0fru = rtB . a3hcsd5djm ; } } if ( ssIsSampleHit (
rtS , 4 , 0 ) ) { rtB . aqrztu4oci = rtDW . edo3dr0fru ; } if ( ssIsSampleHit
( rtS , 2 , 0 ) && ssIsSampleHit ( rtS , 3 , 0 ) ) { rtDW . fdktvwm3kd =
mc34jx2fmw [ 2 ] ; } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { rtB . ftks2e35i3
= rtDW . fdktvwm3kd ; if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW .
hyaxdywynl = rtB . ftks2e35i3 ; } } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) {
rtB . klaa1rzh3f = rtDW . hyaxdywynl ; } if ( ssIsSampleHit ( rtS , 1 , 0 )
&& ssIsSampleHit ( rtS , 3 , 0 ) ) { rtDW . lfzkcubuyh = rtB . cf5pwifjmr [ 0
] ; } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { a23umb45gk [ 0 ] = ( real32_T )
rtB . jpqnsdsvax ; a23umb45gk [ 1 ] = ( real32_T ) rtB . a3hcsd5djm ;
a23umb45gk [ 2 ] = ( real32_T ) rtB . ftks2e35i3 ; bxdgvixlrj = rtB .
jpqnsdsvax * 4096.0 ; kbjxlva2lq = muDoubleScalarAbs ( bxdgvixlrj ) ; if (
kbjxlva2lq < 4.503599627370496E+15 ) { if ( kbjxlva2lq >= 0.5 ) { bxdgvixlrj
= muDoubleScalarFloor ( bxdgvixlrj + 0.5 ) ; } else { bxdgvixlrj *= 0.0 ; } }
if ( muDoubleScalarIsNaN ( bxdgvixlrj ) || muDoubleScalarIsInf ( bxdgvixlrj )
) { kbjxlva2lq = 0.0 ; } else { kbjxlva2lq = muDoubleScalarRem ( bxdgvixlrj ,
3.3554432E+7 ) ; } i = ( int32_T ) muDoubleScalarFloor ( kbjxlva2lq ) ;
ev43vw1xil_idx_0 = ( i & 16777216U ) != 0U ? i | - 16777216 : i & 16777215 ;
bxdgvixlrj = rtB . a3hcsd5djm * 4096.0 ; kbjxlva2lq = muDoubleScalarAbs (
bxdgvixlrj ) ; if ( kbjxlva2lq < 4.503599627370496E+15 ) { if ( kbjxlva2lq >=
0.5 ) { bxdgvixlrj = muDoubleScalarFloor ( bxdgvixlrj + 0.5 ) ; } else {
bxdgvixlrj *= 0.0 ; } } if ( muDoubleScalarIsNaN ( bxdgvixlrj ) ||
muDoubleScalarIsInf ( bxdgvixlrj ) ) { kbjxlva2lq = 0.0 ; } else { kbjxlva2lq
= muDoubleScalarRem ( bxdgvixlrj , 3.3554432E+7 ) ; } i = ( int32_T )
muDoubleScalarFloor ( kbjxlva2lq ) ; ev43vw1xil_idx_1 = ( i & 16777216U ) !=
0U ? i | - 16777216 : i & 16777215 ; bxdgvixlrj = rtB . ftks2e35i3 * 4096.0 ;
kbjxlva2lq = muDoubleScalarAbs ( bxdgvixlrj ) ; if ( kbjxlva2lq <
4.503599627370496E+15 ) { if ( kbjxlva2lq >= 0.5 ) { bxdgvixlrj =
muDoubleScalarFloor ( bxdgvixlrj + 0.5 ) ; } else { bxdgvixlrj *= 0.0 ; } }
if ( muDoubleScalarIsNaN ( bxdgvixlrj ) || muDoubleScalarIsInf ( bxdgvixlrj )
) { kbjxlva2lq = 0.0 ; } else { kbjxlva2lq = muDoubleScalarRem ( bxdgvixlrj ,
3.3554432E+7 ) ; } i = ( int32_T ) muDoubleScalarFloor ( kbjxlva2lq ) ;
ev43vw1xil_idx_2 = ( i & 16777216U ) != 0U ? i | - 16777216 : i & 16777215 ;
if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . kvtifit3ew = rtDW . on2kbwtd1i ;
} rtB . gxf5v3fekk = ( real32_T ) rtB . kvtifit3ew ; } if ( ssIsSampleHit (
rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 3 , 0 ) ) { rtDW . bt2kw45n5u = rtB .
cf5pwifjmr [ 1 ] ; } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { rtB . ljvsb0m4tf
= ( real32_T ) rtDW . lfzkcubuyh ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) &&
ssIsSampleHit ( rtS , 3 , 0 ) ) { rtDW . eqzj0rxvun = rtB . cf5pwifjmr [ 2 ]
; } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { rtB . hcl2mherxb = ( real32_T )
rtDW . bt2kw45n5u ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit (
rtS , 3 , 0 ) ) { rtDW . ilnpea2zjg = rtB . cf5pwifjmr [ 3 ] ; } if (
ssIsSampleHit ( rtS , 3 , 0 ) ) { rtB . jqrr1set1f = ( real32_T ) rtDW .
eqzj0rxvun ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 3
, 0 ) ) { rtDW . ddhgjj4slr = rtB . cf5pwifjmr [ 4 ] ; } if ( ssIsSampleHit (
rtS , 3 , 0 ) ) { rtB . klznlbui1b = ( real32_T ) rtDW . ilnpea2zjg ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) && ssIsSampleHit ( rtS , 3 , 0 ) ) { rtDW .
cguk3rlz2c = rtB . cf5pwifjmr [ 5 ] ; } if ( ssIsSampleHit ( rtS , 3 , 0 ) )
{ rtB . lk3th3p1al = ( real32_T ) rtDW . ddhgjj4slr ; rtB . kqqvdbnzy3 = (
real32_T ) rtDW . cguk3rlz2c ; for ( i = 0 ; i < 6 ; i ++ ) { rtB .
ilatryxyc3 [ i ] = gj0vg0h2tb [ i ] ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) )
{ rtB . a3lvlw3afz = rtDW . myfhgr2zam ; } rtB . i5uxa5wsug = ( real32_T )
rtB . a3lvlw3afz ; } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { for ( i = 0 ; i <
8 ; i ++ ) { dvf40ry3hk [ i ] = rtDW . ayjsmpf3pd [ i ] ; } enasz1anlw = (
uint8_T ) ( ( uint32_T ) jyxstc4ejt + rtP . FixPtConstant_Value_mariintfbp )
; if ( enasz1anlw > rtP . CounterLimited_uplimit_np4zdwmb1e ) { rtB .
kycn2fuam4 = rtP . Constant_Value_eorisuadz3 ; } else { rtB . kycn2fuam4 =
enasz1anlw ; } rtB . c25uz5tds5 = rtDW . il1i11vhya [ 0 ] ; rtB . amtihtn1an
[ 0 ] = rtB . ljvsb0m4tf ; rtB . amtihtn1an [ 1 ] = rtB . klznlbui1b ; rtB .
amtihtn1an [ 2 ] = rtB . kqqvdbnzy3 ; rtB . amtihtn1an [ 3 ] = rtB .
jqrr1set1f ; rtB . amtihtn1an [ 4 ] = rtB . hcl2mherxb ; rtB . amtihtn1an [ 5
] = rtB . lk3th3p1al ; rtB . amtihtn1an [ 6 ] = rtB . i5uxa5wsug ; rtB .
amtihtn1an [ 7 ] = rtB . gxf5v3fekk ; gy5wd21nmz ( hxx1o3o0xn , rtB .
amtihtn1an , & rtB . nzetkmjqj1 ) ; for ( i = 0 ; i < 12 ; i ++ ) {
epl2f04eoj [ i ] = rtB . nzetkmjqj1 . gwunl2xrbh [ i ] ; } p4z2y3oxrm (
epl2f04eoj , rtP . DefaultIndex_Value_a00bbokt5z , rtP .
ModeVector8_Value_ndjrz30mn4 , rtP . Subsystem8_Index_g1r4pfdd11 , & rtB .
m432cmsuep ) ; p4z2y3oxrm ( epl2f04eoj , rtB . m432cmsuep . f3ngbvxvpa , rtP
. ModeVector7_Value_kfcbsv4wr0 , rtP . Subsystem7_Index_n4h55mccm4 , & rtB .
mdkybjqwpy ) ; p4z2y3oxrm ( epl2f04eoj , rtB . mdkybjqwpy . f3ngbvxvpa , rtP
. ModeVector6_Value_jxzmvcin1w , rtP . Subsystem6_Index_kjr4ynilvy , & rtB .
gpry1jhtuq ) ; p4z2y3oxrm ( epl2f04eoj , rtB . gpry1jhtuq . f3ngbvxvpa , rtP
. ModeVector5_Value_pdt0z4g5rr , rtP . Subsystem5_Index_kc5dwsgpkh , & rtB .
dh2sbcx1k5 ) ; p4z2y3oxrm ( epl2f04eoj , rtB . dh2sbcx1k5 . f3ngbvxvpa , rtP
. ModeVector4_Value_cebv2o0h2i , rtP . Subsystem4_Index_k4wyew5d14 , & rtB .
boikvzokby ) ; p4z2y3oxrm ( epl2f04eoj , rtB . boikvzokby . f3ngbvxvpa , rtP
. ModeVector3_Value_ct3wsuvwjv , rtP . Subsystem3_Index_cao32uglvg , & rtB .
l1oh3i210b ) ; p4z2y3oxrm ( epl2f04eoj , rtB . l1oh3i210b . f3ngbvxvpa , rtP
. ModeVector2_Value_ksothw4zp0 , rtP . Subsystem2_Index_cwbdy5b3nk , & rtB .
fzihwa5jz0 ) ; p4z2y3oxrm ( epl2f04eoj , rtB . fzihwa5jz0 . f3ngbvxvpa , rtP
. ModeVector1_Value_jwc0rjoavh , rtP . Subsystem1_Index_onoalnmieu , & rtB .
o0k0yxtimm ) ; if ( ew0ut03d54 ) { av2veoeel0 = rtB . o0k0yxtimm . f3ngbvxvpa
; } else { av2veoeel0 = rtP . Constant_Value_a2fgb02dpi ; } nyh00w3mbc = rtDW
. azvnw5pvht ; for ( i = 0 ; i < 12 ; i ++ ) { echj2jj5d3 [ i ] = 0.0F ; }
for ( i = 0 ; i < 12 ; i ++ ) { for ( grxhuiwehd_idx_0 = 0 ; grxhuiwehd_idx_0
< 8 ; grxhuiwehd_idx_0 ++ ) { echj2jj5d3 [ i ] += rtP .
MultiplyInput_constMatrix_dt0y2fteom [ ( 12 * grxhuiwehd_idx_0 + i ) + 96 *
av2veoeel0 ] * rtB . amtihtn1an [ grxhuiwehd_idx_0 ] ; } } for ( i = 0 ; i <
12 ; i ++ ) { rtB . b5hsoldwxb [ i ] = rtP . Bias_Value_egvhuyhyzm [ 12 *
av2veoeel0 + i ] + echj2jj5d3 [ i ] ; } } if ( ssIsSampleHit ( rtS , 3 , 0 )
) { if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . faadh0wdog [ 0 ] =
ev43vw1xil_idx_0 ; rtDW . faadh0wdog [ 1 ] = ev43vw1xil_idx_1 ; rtDW .
faadh0wdog [ 2 ] = ev43vw1xil_idx_2 ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) )
{ rtDW . jgx0xkzgjo [ 0 ] = rtB . iaytspuvc2 [ 0 ] ; rtDW . jgx0xkzgjo [ 1 ]
= rtB . iaytspuvc2 [ 1 ] ; rtDW . jgx0xkzgjo [ 2 ] = rtB . iaytspuvc2 [ 2 ] ;
} } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . bc4jkovamz [ 0 ] = rtDW .
faadh0wdog [ 0 ] ; rtB . bc4jkovamz [ 1 ] = rtDW . faadh0wdog [ 1 ] ; rtB .
bc4jkovamz [ 2 ] = rtDW . faadh0wdog [ 2 ] ; } if ( ssIsSampleHit ( rtS , 1 ,
0 ) && ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . bfidcyeanb = rtB . g5udhujwag
; } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtB . ct50xdrbpe [ 0 ] = rtDW .
jgx0xkzgjo [ 0 ] ; rtB . ct50xdrbpe [ 1 ] = rtDW . jgx0xkzgjo [ 1 ] ; rtB .
ct50xdrbpe [ 2 ] = rtDW . jgx0xkzgjo [ 2 ] ; } if ( ssIsSampleHit ( rtS , 1 ,
0 ) && ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . fi31qowovj = rtB . ill1vghh4b
; } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { cq5xhl1pln = rtDW . bfidcyeanb ;
mbuj01azxx = rtDW . fi31qowovj ; } UNUSED_PARAMETER ( tid ) ; } void
MdlOutputsTID6 ( int_T tid ) { real_T munlv45duu ; real_T j3p5k4shp3 ; real_T
ph3uzcqjm1 ; rtB . idhzvwwmxp = rtP . Constant9_Value ; rtB . j20cbeet2a =
rtP . Constant9_Value_gdn1knb3nq ; rtB . fjlr1apiaj = rtP .
Constant9_Value_fgokpme3bd ; rtB . g4t0xlro5r = rtP . DegRad_Gain * rtP .
Constant3_Value_asrfyaoivf ; rtB . epstor1a22 = ( rtP .
SVPWMGenerator2Level_InputType == rtP . Constant_Value_ep3zz2rhlg ) ; rtB .
cwnrh0a0wn = ( rtP . SVPWMGenerator2Level_InputType == rtP .
Constant1_Value_gihsyq2jvw ) ; rtB . h3tkzgo55v = ( rtP .
SVPWMGenerator2Level_SwitchingPattern == rtP . Constant_Value_a3tiqve2ba ) ;
rtB . jeqz1ilrpj = ! rtB . h3tkzgo55v ; cqjwvwhkzvTID6 ( rtS , & rtDW .
cqjwvwhkzvh ) ; azshdeeeiwTID6 ( rtS , & rtDW . azshdeeeiw3 ) ; rtB .
lxu2tizwog = rtP . DegRad_Gain_hsvtiaadnd * rtP . Constant3_Value_fsonf21ozn
; rtB . ghxuospbjl = ( rtP . SVPWMGenerator2Level_InputType_p5gp2uzlhc == rtP
. Constant_Value_n5xgxhep3k ) ; rtB . hxnqngtyf1 = ( rtP .
SVPWMGenerator2Level_InputType_p5gp2uzlhc == rtP . Constant1_Value_fc5w4veyse
) ; rtB . a1jnu0tnvv = ( rtP .
SVPWMGenerator2Level_SwitchingPattern_kmqtzirjjx == rtP .
Constant_Value_hrxltwm4pv ) ; rtB . jt0dbfa543 = ! rtB . a1jnu0tnvv ;
cqjwvwhkzvTID6 ( rtS , & rtDW . cstc0v1lpw ) ; azshdeeeiwTID6 ( rtS , & rtDW
. mzoe5aiivc ) ; rtB . imc322aww5 = rtP . DegRad_Gain_lpbikznakf * rtP .
Constant3_Value_mwaqmz2fbl ; rtB . mp2miztasv = ( rtP .
SVPWMGenerator2Level_InputType_eeovqphbmi == rtP . Constant_Value_dl3vzsgqc3
) ; rtB . grg2qcew0n = ( rtP . SVPWMGenerator2Level_InputType_eeovqphbmi ==
rtP . Constant1_Value_id2q2llyug ) ; rtB . mdhyl1ygwf = ( rtP .
SVPWMGenerator2Level_SwitchingPattern_b5rdju1jqc == rtP .
Constant_Value_hnyucebqyk ) ; rtB . p50ijigx25 = ! rtB . mdhyl1ygwf ;
cqjwvwhkzvTID6 ( rtS , & rtDW . msqwmshj2n ) ; azshdeeeiwTID6 ( rtS , & rtDW
. biyhxca30f ) ; if ( rtP . Constant1_Value_mkyn4cvwnf ) { rtB . amb4v03txh =
0.0 ; } else { rtB . amb4v03txh = rtP . setp_iq_Value ; } { if ( rtDW .
gwqsbwh5jo . AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW .
gwqsbwh5jo . AQHandles , ssGetTaskTime ( rtS , 6 ) , ( char * ) & rtB .
amb4v03txh + 0 ) ; } } rtB . mciby2bhmc = ( uint8_T ) ( rtP .
AlphaBetaZerotodq0_Alignment == rtP . CompareToConstant_const ) ; rtB .
oksi514ex4 = ( uint8_T ) ( rtP . AlphaBetaZerotodq0_Alignment == rtP .
CompareToConstant1_const ) ; munlv45duu = rtP . Constant_Value_ak1tppnn4h ;
j3p5k4shp3 = rtP . Constant_Value_pzbpxmwupt ; rtB . d5mmalu5vx = ( uint8_T )
( rtP . dq0toAlphaBetaZero_Alignment == rtP .
CompareToConstant_const_i2rz2duvtn ) ; rtB . n3swfpwaok = ( uint8_T ) ( rtP .
dq0toAlphaBetaZero_Alignment == rtP . CompareToConstant1_const_icp5urwmrl ) ;
ph3uzcqjm1 = rtP . Constant3_Value_lglm3qv24g ; rtB . dmg5kd4tx3 = ( real32_T
) ( 1.0 / rtP . L_o1 ) ; rtB . ezj0gynpe2 = ( real32_T ) rtP . polepair ; rtB
. c5qcb5u3xz = ( real32_T ) rtP . psi_pm ; rtB . n01lcmfhax = ( real32_T ) (
1.0 / rtP . inertia ) ; rtB . ill1vghh4b = ( real32_T ) rtP .
friction_coefficient ; rtB . g5udhujwag = ( real32_T ) rtP .
static_friction_torque ; rtB . op5yeerppz = ( real32_T ) ( 1.0 / rtP . L_zero
) ; rtB . kh313ui5yr = ( real32_T ) ( 1.0 / rtP . L_o2 ) ; rtB . hvql1wzp1l =
( real32_T ) ( 1.0 / rtP . L_x1 ) ; rtB . ibyskbyf12 = ( real32_T ) ( 1.0 /
rtP . L_y1 ) ; rtB . fxv4zcsfc1 = ( real32_T ) ( 1.0 / rtP . L_x2 ) ; rtB .
bvmuyedlcu = ( real32_T ) ( 1.0 / rtP . L_y2 ) ; rtB . klks1betwn = (
real32_T ) ( 1.0 / rtP . L_d ) ; rtB . apfmql0sei = ( real32_T ) ( 1.0 / rtP
. L_q ) ; rtB . axfg3xmtsw = ( real32_T ) rtP . R_1 ; UNUSED_PARAMETER ( tid
) ; } void MdlUpdate ( int_T tid ) { int32_T i ; int32_T idxWidth ; if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { rtDW . miazophk3q [ 0U ] = rtDW .
miazophk3q [ 1U ] ; rtDW . miazophk3q [ 1U ] = rtDW . miazophk3q [ 2U ] ;
rtDW . miazophk3q [ 2 ] = rtB . dxm0qgspl5 ; for ( i = 0 ; i < 5 ; i ++ ) {
rtDW . ixrsi3erhf [ ( uint32_T ) i ] = rtDW . ixrsi3erhf [ i + 1U ] ; rtDW .
jis1uepreo [ ( uint32_T ) i ] = rtDW . jis1uepreo [ i + 1U ] ; for ( idxWidth
= 0 ; idxWidth < 9 ; idxWidth ++ ) { rtDW . fwkxey5epo [ i * 9U + idxWidth ]
= rtDW . fwkxey5epo [ ( i + 1U ) * 9U + idxWidth ] ; } } rtDW . ixrsi3erhf [
5 ] = rtB . n01cwk51y2 ; rtDW . jis1uepreo [ 5 ] = rtB . p3g0p13atl ; for ( i
= 0 ; i < 9 ; i ++ ) { rtDW . fwkxey5epo [ i + 45 ] = rtB . jgteqxearg [ i ]
; } rtDW . f4tcd4udur = rtB . drcj52wpue ; rtDW . cnrqogla5d [ 0U ] = rtDW .
cnrqogla5d [ 1U ] ; rtDW . cnrqogla5d [ 1U ] = rtDW . cnrqogla5d [ 2U ] ;
rtDW . cnrqogla5d [ 2 ] = rtB . nahffw1fqn ; rtDW . aanjcgvfa0 [ 0U ] = rtDW
. aanjcgvfa0 [ 1U ] ; rtDW . aanjcgvfa0 [ 1U ] = rtDW . aanjcgvfa0 [ 2U ] ;
rtDW . aanjcgvfa0 [ 2 ] = rtB . lup5lr2jvb ; rtDW . aoxcwu3qll = rtB .
h2h3aoif55 ; rtDW . ctbynjdwij [ 0U ] = rtDW . ctbynjdwij [ 1U ] ; rtDW .
ctbynjdwij [ 1U ] = rtDW . ctbynjdwij [ 2U ] ; rtDW . ctbynjdwij [ 2 ] = rtB
. bqib1cp1cj ; rtDW . gnh32qpzkl [ 0U ] = rtDW . gnh32qpzkl [ 1U ] ; rtDW .
gnh32qpzkl [ 1U ] = rtDW . gnh32qpzkl [ 2U ] ; rtDW . gnh32qpzkl [ 2 ] = rtB
. olgy0iynok ; rtDW . ihfcziqcgk = rtB . d5bxbfmv3h ; rtDW . afo0nwhxua [ 0U
] = rtDW . afo0nwhxua [ 1U ] ; rtDW . afo0nwhxua [ 1U ] = rtDW . afo0nwhxua [
2U ] ; rtDW . afo0nwhxua [ 2 ] = rtB . gxiz1fefsk ; rtDW . eahq4k0qba = rtB .
jmg21szmcd ; rtDW . jdtstycpmg [ 0U ] = rtDW . jdtstycpmg [ 1U ] ; rtDW .
jdtstycpmg [ 1U ] = rtDW . jdtstycpmg [ 2U ] ; rtDW . jdtstycpmg [ 2 ] = rtB
. ozq3nsiak4 ; rtDW . oo31woulsl = rtB . nvio0y23qb ; rtDW . g2ry4vjsj1 [ 0U
] = rtDW . g2ry4vjsj1 [ 1U ] ; rtDW . g2ry4vjsj1 [ 1U ] = rtDW . g2ry4vjsj1 [
2U ] ; rtDW . g2ry4vjsj1 [ 2 ] = rtB . fxar2syvnw ; rtDW . blhgrykwvp = rtB .
o5rpzk02ux ; rtDW . iehvrkddj2 [ 0U ] = rtDW . iehvrkddj2 [ 1U ] ; rtDW .
iehvrkddj2 [ 1U ] = rtDW . iehvrkddj2 [ 2U ] ; rtDW . iehvrkddj2 [ 2 ] = rtB
. igl4agsvph ; rtDW . osqohvejno = rtB . o44jebcpbs ; rtDW . nbavx35izv [ 0U
] = rtDW . nbavx35izv [ 1U ] ; rtDW . nbavx35izv [ 1U ] = rtDW . nbavx35izv [
2U ] ; rtDW . nbavx35izv [ 2 ] = rtB . kkpufmifuj ; rtDW . cvcfermial = rtB .
fhua05yaow ; rtDW . cl1vsftpzn [ 0U ] = rtDW . cl1vsftpzn [ 1U ] ; rtDW .
cl1vsftpzn [ 1U ] = rtDW . cl1vsftpzn [ 2U ] ; rtDW . cl1vsftpzn [ 2 ] = rtB
. lx40xm1u3s ; rtDW . ocn3tuy1mq = rtB . ekqxh0o2yy ; rtDW . lhojsnn24m [ 0U
] = rtDW . lhojsnn24m [ 1U ] ; rtDW . lhojsnn24m [ 1U ] = rtDW . lhojsnn24m [
2U ] ; rtDW . lhojsnn24m [ 2 ] = rtB . fyoaaccrru ; rtDW . lzrfskvb50 [ 0U ]
= rtDW . lzrfskvb50 [ 1U ] ; rtDW . lzrfskvb50 [ 1U ] = rtDW . lzrfskvb50 [
2U ] ; rtDW . lzrfskvb50 [ 2 ] = rtB . ac1d3qgxbp ; rtDW . kxzyyq15r0 [ 0U ]
= rtDW . kxzyyq15r0 [ 1U ] ; rtDW . kxzyyq15r0 [ 1U ] = rtDW . kxzyyq15r0 [
2U ] ; rtDW . kxzyyq15r0 [ 2 ] = rtB . dxuigsm1g2 ; rtDW . jfrl3cqm1n = rtB .
ba4ycbfbms ; rtDW . d42pvxfz0g [ 0U ] = rtDW . d42pvxfz0g [ 1U ] ; rtDW .
d42pvxfz0g [ 1U ] = rtDW . d42pvxfz0g [ 2U ] ; rtDW . d42pvxfz0g [ 2 ] = rtB
. a00j4is05h ; rtDW . ayahx5voca [ 0U ] = rtDW . ayahx5voca [ 1U ] ; rtDW .
ayahx5voca [ 1U ] = rtDW . ayahx5voca [ 2U ] ; rtDW . ayahx5voca [ 2 ] = rtB
. bft2jjoec5 ; rtDW . l2zkdqsp2y [ 0U ] = rtDW . l2zkdqsp2y [ 1U ] ; rtDW .
l2zkdqsp2y [ 1U ] = rtDW . l2zkdqsp2y [ 2U ] ; rtDW . l2zkdqsp2y [ 2 ] = rtB
. cmhi33mwre ; rtDW . lxk5izw00o [ 0U ] = rtDW . lxk5izw00o [ 1U ] ; rtDW .
lxk5izw00o [ 1U ] = rtDW . lxk5izw00o [ 2U ] ; rtDW . lxk5izw00o [ 2 ] = rtB
. jml1bsjxtz ; rtDW . cqp1dau03w [ 0U ] = rtDW . cqp1dau03w [ 1U ] ; rtDW .
cqp1dau03w [ 1U ] = rtDW . cqp1dau03w [ 2U ] ; rtDW . cqp1dau03w [ 2 ] = rtB
. mkhgcxbdbc ; rtDW . gfiovjo3e2 [ 0U ] = rtDW . gfiovjo3e2 [ 1U ] ; rtDW .
gfiovjo3e2 [ 1U ] = rtDW . gfiovjo3e2 [ 2U ] ; rtDW . gfiovjo3e2 [ 2 ] = rtB
. mmaiq4q51j ; rtDW . p2iwsajmfp [ 0U ] = rtDW . p2iwsajmfp [ 1U ] ; rtDW .
p2iwsajmfp [ 1U ] = rtDW . p2iwsajmfp [ 2U ] ; rtDW . p2iwsajmfp [ 2 ] = rtB
. ejp2ouo0yj ; rtDW . b4auxd1lsk [ 0U ] = rtDW . b4auxd1lsk [ 1U ] ; rtDW .
b4auxd1lsk [ 1U ] = rtDW . b4auxd1lsk [ 2U ] ; rtDW . b4auxd1lsk [ 2 ] = rtB
. j4ghcw5gtk ; rtDW . kovzbujdnb [ 0U ] = rtDW . kovzbujdnb [ 1U ] ; rtDW .
kovzbujdnb [ 1U ] = rtDW . kovzbujdnb [ 2U ] ; rtDW . kovzbujdnb [ 2 ] = rtB
. oq4k1jl1j1 ; for ( i = 0 ; i < 5 ; i ++ ) { rtDW . pnsuou2020 [ ( uint32_T
) i ] = rtDW . pnsuou2020 [ i + 1U ] ; rtDW . opg1thx2qw [ ( uint32_T ) i ] =
rtDW . opg1thx2qw [ i + 1U ] ; rtDW . amalc3ffil [ ( uint32_T ) i ] = rtDW .
amalc3ffil [ i + 1U ] ; rtDW . mwenvz0tar [ ( uint32_T ) i ] = rtDW .
mwenvz0tar [ i + 1U ] ; rtDW . de3otshxus [ ( uint32_T ) i ] = rtDW .
de3otshxus [ i + 1U ] ; rtDW . i2ctd1awel [ ( uint32_T ) i ] = rtDW .
i2ctd1awel [ i + 1U ] ; rtDW . ccf5juo5ya [ ( uint32_T ) i ] = rtDW .
ccf5juo5ya [ i + 1U ] ; rtDW . i4lkkodfyj [ ( uint32_T ) i ] = rtDW .
i4lkkodfyj [ i + 1U ] ; rtDW . mdvclm3wpb [ ( uint32_T ) i ] = rtDW .
mdvclm3wpb [ i + 1U ] ; rtDW . gai5nv42oe [ ( uint32_T ) i ] = rtDW .
gai5nv42oe [ i + 1U ] ; rtDW . imfxseqvvv [ ( uint32_T ) i ] = rtDW .
imfxseqvvv [ i + 1U ] ; rtDW . cxatkad2jz [ ( uint32_T ) i ] = rtDW .
cxatkad2jz [ i + 1U ] ; rtDW . ikxzuowx1v [ ( uint32_T ) i ] = rtDW .
ikxzuowx1v [ i + 1U ] ; rtDW . bg2vv1po0e [ ( uint32_T ) i ] = rtDW .
bg2vv1po0e [ i + 1U ] ; rtDW . dmmot30jq4 [ ( uint32_T ) i ] = rtDW .
dmmot30jq4 [ i + 1U ] ; rtDW . anfxf0zt2u [ ( uint32_T ) i ] = rtDW .
anfxf0zt2u [ i + 1U ] ; rtDW . al5aajfx21 [ ( uint32_T ) i ] = rtDW .
al5aajfx21 [ i + 1U ] ; rtDW . gt3chc0tga [ ( uint32_T ) i ] = rtDW .
gt3chc0tga [ i + 1U ] ; } rtDW . pnsuou2020 [ 5 ] = rtB . iskolztlai ; rtDW .
opg1thx2qw [ 5 ] = rtB . ardjnl10dt ; rtDW . amalc3ffil [ 5 ] = rtB .
bs3jd3qjqw ; rtDW . mwenvz0tar [ 5 ] = rtB . jf1dkqak4i ; rtDW . de3otshxus [
5 ] = rtB . m3i5omzuvm ; rtDW . i2ctd1awel [ 5 ] = rtB . lvqyun4ml4 ; rtDW .
ccf5juo5ya [ 5 ] = rtB . bpvldt4nml ; rtDW . i4lkkodfyj [ 5 ] = rtB .
mr5jvkeea4 ; rtDW . mdvclm3wpb [ 5 ] = rtB . bzop13ab3h ; rtDW . gai5nv42oe [
5 ] = rtB . glnkapw4oj ; rtDW . imfxseqvvv [ 5 ] = rtB . murauiwsvw ; rtDW .
cxatkad2jz [ 5 ] = rtB . fclle0plbx ; rtDW . ikxzuowx1v [ 5 ] = rtB .
gydjzs1bdb ; rtDW . bg2vv1po0e [ 5 ] = rtB . nlrhqopjdv ; rtDW . dmmot30jq4 [
5 ] = rtB . ljbz13eall ; rtDW . anfxf0zt2u [ 5 ] = rtB . ku3t5edtlg ; rtDW .
al5aajfx21 [ 5 ] = rtB . mxgu50ynet ; rtDW . gt3chc0tga [ 5 ] = rtB .
cajcokate4 ; rtDW . dttn4xmcnk [ 0U ] = rtDW . dttn4xmcnk [ 1U ] ; rtDW .
dttn4xmcnk [ 1U ] = rtDW . dttn4xmcnk [ 2U ] ; rtDW . dttn4xmcnk [ 2 ] = rtB
. lzb32orqgb ; rtDW . erukb0glgz [ 0U ] = rtDW . erukb0glgz [ 1U ] ; rtDW .
erukb0glgz [ 1U ] = rtDW . erukb0glgz [ 2U ] ; rtDW . erukb0glgz [ 2 ] = rtB
. n3tpootby4 ; rtDW . n1ap5w5rdi [ 0U ] = rtDW . n1ap5w5rdi [ 1U ] ; rtDW .
n1ap5w5rdi [ 1U ] = rtDW . n1ap5w5rdi [ 2U ] ; rtDW . n1ap5w5rdi [ 2 ] = rtB
. cqo5mybcym ; rtDW . k44l31otpd [ 0U ] = rtDW . k44l31otpd [ 1U ] ; rtDW .
k44l31otpd [ 1U ] = rtDW . k44l31otpd [ 2U ] ; rtDW . k44l31otpd [ 2 ] = rtB
. fbqqxnvweh ; rtDW . ndb122ek3u [ 0U ] = rtDW . ndb122ek3u [ 1U ] ; rtDW .
ndb122ek3u [ 1U ] = rtDW . ndb122ek3u [ 2U ] ; rtDW . ndb122ek3u [ 2 ] = rtB
. haranx30a5 [ 1 ] ; rtDW . pdjkbbbzjq [ 0U ] = rtDW . pdjkbbbzjq [ 1U ] ;
rtDW . pdjkbbbzjq [ 1U ] = rtDW . pdjkbbbzjq [ 2U ] ; rtDW . pdjkbbbzjq [ 2 ]
= rtB . nyfnpu0nol ; rtDW . bi1fzovgs2 = rtB . fvfmloctub ; ipssuqc5xa ( rtB
. ayauqzczgu , rtB . i0e4upsk2d , rtB . enz5ww01sg , & rtB . f5mkygzljka , &
rtDW . f5mkygzljka ) ; ipssuqc5xa ( rtB . ayauqzczgu , rtB . io0z1g0pje , rtB
. enz5ww01sg , & rtB . o0tbmhvpds , & rtDW . o0tbmhvpds ) ; ipssuqc5xa ( rtB
. ayauqzczgu , rtB . gihxrchecp , rtB . enz5ww01sg , & rtB . jjajpmoyel , &
rtDW . jjajpmoyel ) ; ipssuqc5xa ( rtB . ayauqzczgu , rtB . hemavelcim , rtB
. enz5ww01sg , & rtB . ndmeqad3sm , & rtDW . ndmeqad3sm ) ; ipssuqc5xa ( rtB
. ayauqzczgu , rtB . h1tpfgxf3b , rtB . enz5ww01sg , & rtB . a13lr3lsi3 , &
rtDW . a13lr3lsi3 ) ; ipssuqc5xa ( rtB . ayauqzczgu , rtB . jszybsysr2 , rtB
. enz5ww01sg , & rtB . jogryxdnkz , & rtDW . jogryxdnkz ) ; ipssuqc5xa ( rtB
. ayauqzczgu , rtB . ioigeufkrg , rtB . enz5ww01sg , & rtB . jjob4ur221 , &
rtDW . jjob4ur221 ) ; ipssuqc5xa ( rtB . ayauqzczgu , rtB . ngwwugiho4 , rtB
. enz5ww01sg , & rtB . n4cqr1dkmr , & rtDW . n4cqr1dkmr ) ; ipssuqc5xa ( rtB
. ayauqzczgu , rtB . nd1jlmty5o , rtB . enz5ww01sg , & rtB . cx41wglw3j , &
rtDW . cx41wglw3j ) ; for ( i = 0 ; i < 5 ; i ++ ) { rtDW . hoesofthyy [ (
uint32_T ) i ] = rtDW . hoesofthyy [ i + 1U ] ; } rtDW . hoesofthyy [ 5 ] =
rtB . ialnb1yw5e ; rtDW . pml0yl52te [ 0U ] = rtDW . pml0yl52te [ 1U ] ; rtDW
. pml0yl52te [ 1U ] = rtDW . pml0yl52te [ 2U ] ; rtDW . pml0yl52te [ 2 ] =
rtB . b4ty1phbhk ; rtDW . eswvf4pz4v = rtB . atculhoes1 ; } if (
ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . dzr2rntvvo [ 0U ] = rtDW .
dzr2rntvvo [ 1U ] ; rtDW . dzr2rntvvo [ 1 ] = rtB . kqxgd32mvf ; rtDW .
aw0bxhrzal [ 0U ] = rtDW . aw0bxhrzal [ 3U ] ; rtDW . aw0bxhrzal [ 1U ] =
rtDW . aw0bxhrzal [ 4U ] ; rtDW . aw0bxhrzal [ 2U ] = rtDW . aw0bxhrzal [ 5U
] ; rtDW . aw0bxhrzal [ 3 ] = rtB . ct50xdrbpe [ 0 ] ; rtDW . aw0bxhrzal [ 4
] = rtB . ct50xdrbpe [ 1 ] ; rtDW . aw0bxhrzal [ 5 ] = rtB . ct50xdrbpe [ 2 ]
; rtDW . estezyunas [ 0U ] = rtDW . estezyunas [ 3U ] ; rtDW . estezyunas [
1U ] = rtDW . estezyunas [ 4U ] ; rtDW . estezyunas [ 2U ] = rtDW .
estezyunas [ 5U ] ; rtDW . estezyunas [ 3 ] = rtB . p1wjqkompn [ 0 ] ; rtDW .
estezyunas [ 4 ] = rtB . p1wjqkompn [ 1 ] ; rtDW . estezyunas [ 5 ] = rtB .
p1wjqkompn [ 2 ] ; rtDW . olzifhaukx [ 0U ] = rtDW . olzifhaukx [ 3U ] ; rtDW
. olzifhaukx [ 1U ] = rtDW . olzifhaukx [ 4U ] ; rtDW . olzifhaukx [ 2U ] =
rtDW . olzifhaukx [ 5U ] ; rtDW . olzifhaukx [ 3 ] = rtB . bc4jkovamz [ 0 ] ;
rtDW . miwm3apiea [ 0 ] = rtB . piz1xhutnj [ 0 ] ; rtDW . olzifhaukx [ 4 ] =
rtB . bc4jkovamz [ 1 ] ; rtDW . miwm3apiea [ 1 ] = rtB . piz1xhutnj [ 1 ] ;
rtDW . olzifhaukx [ 5 ] = rtB . bc4jkovamz [ 2 ] ; rtDW . miwm3apiea [ 2 ] =
rtB . piz1xhutnj [ 2 ] ; rtDW . jcievkrvvv [ 0 ] = rtB . p30scmuimh [ 0 ] ;
rtDW . jcievkrvvv [ 1 ] = rtB . p30scmuimh [ 1 ] ; rtDW . jcievkrvvv [ 2 ] =
rtB . p30scmuimh [ 2 ] ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtDW .
otborblus0 [ 0 ] = rtB . faduibn1mq [ 0 ] ; rtDW . otborblus0 [ 1 ] = rtB .
faduibn1mq [ 1 ] ; rtDW . otborblus0 [ 2 ] = rtB . faduibn1mq [ 2 ] ; rtDW .
ovlbtlz2z5 [ 0 ] = rtB . faduibn1mq [ 3 ] ; rtDW . ovlbtlz2z5 [ 1 ] = rtB .
faduibn1mq [ 4 ] ; rtDW . ovlbtlz2z5 [ 2 ] = rtB . faduibn1mq [ 5 ] ; rtDW .
iygynuhhiw [ 0 ] = rtB . faduibn1mq [ 6 ] ; rtDW . iygynuhhiw [ 1 ] = rtB .
faduibn1mq [ 7 ] ; rtDW . iygynuhhiw [ 2 ] = rtB . faduibn1mq [ 8 ] ; rtDW .
oamcwpfckc = rtB . bi5qzktbi4 ; rtDW . ifur0qjdev = rtB . ijrdbn05so ; for (
i = 0 ; i < 5 ; i ++ ) { rtDW . h2z1m5wxiy [ ( uint32_T ) i ] = rtDW .
h2z1m5wxiy [ i + 1U ] ; rtDW . dviol1u0jv [ ( uint32_T ) i ] = rtDW .
dviol1u0jv [ i + 1U ] ; rtDW . df5ibuzfvl [ ( uint32_T ) i ] = rtDW .
df5ibuzfvl [ i + 1U ] ; rtDW . ikv4gqtanm [ ( uint32_T ) i ] = rtDW .
ikv4gqtanm [ i + 1U ] ; rtDW . hru10ym4o1 [ ( uint32_T ) i ] = rtDW .
hru10ym4o1 [ i + 1U ] ; rtDW . erp5nno2ec [ ( uint32_T ) i ] = rtDW .
erp5nno2ec [ i + 1U ] ; rtDW . ima1cclrzn [ ( uint32_T ) i ] = rtDW .
ima1cclrzn [ i + 1U ] ; rtDW . hm24hbgcg1 [ ( uint32_T ) i ] = rtDW .
hm24hbgcg1 [ i + 1U ] ; rtDW . ob20xueupt [ ( uint32_T ) i ] = rtDW .
ob20xueupt [ i + 1U ] ; rtDW . phidvr4lhk [ ( uint32_T ) i ] = rtDW .
phidvr4lhk [ i + 1U ] ; rtDW . atdfcebxbc [ ( uint32_T ) i ] = rtDW .
atdfcebxbc [ i + 1U ] ; rtDW . o3sgmp4aev [ ( uint32_T ) i ] = rtDW .
o3sgmp4aev [ i + 1U ] ; rtDW . nld3uzo5io [ ( uint32_T ) i ] = rtDW .
nld3uzo5io [ i + 1U ] ; rtDW . fi4wuwmktb [ ( uint32_T ) i ] = rtDW .
fi4wuwmktb [ i + 1U ] ; rtDW . gm4ivysliu [ ( uint32_T ) i ] = rtDW .
gm4ivysliu [ i + 1U ] ; rtDW . pyurk4he1k [ ( uint32_T ) i ] = rtDW .
pyurk4he1k [ i + 1U ] ; rtDW . ocff1ayzzn [ ( uint32_T ) i ] = rtDW .
ocff1ayzzn [ i + 1U ] ; rtDW . l0rzviqodi [ ( uint32_T ) i ] = rtDW .
l0rzviqodi [ i + 1U ] ; rtDW . o0qik01ouq [ ( uint32_T ) i ] = rtDW .
o0qik01ouq [ i + 1U ] ; rtDW . jci52usrwf [ ( uint32_T ) i ] = rtDW .
jci52usrwf [ i + 1U ] ; rtDW . n0ifswwd21 [ ( uint32_T ) i ] = rtDW .
n0ifswwd21 [ i + 1U ] ; } rtDW . h2z1m5wxiy [ 5 ] = rtB . odetrknlzz ; rtDW .
dviol1u0jv [ 5 ] = rtB . lugsvs2nsp ; rtDW . df5ibuzfvl [ 5 ] = rtB .
im5yymuath ; rtDW . ikv4gqtanm [ 5 ] = rtB . iiqlz25ibz ; rtDW . hru10ym4o1 [
5 ] = rtB . opdam4elco ; rtDW . erp5nno2ec [ 5 ] = rtB . b5q02ypjjz ; rtDW .
ima1cclrzn [ 5 ] = rtB . ohmrbovmfa ; rtDW . hm24hbgcg1 [ 5 ] = rtB .
cssbez0qdp ; rtDW . ob20xueupt [ 5 ] = rtB . jc2xb5555z ; rtDW . phidvr4lhk [
5 ] = rtB . ghwcctc4hl ; rtDW . atdfcebxbc [ 5 ] = rtB . ncbythljam ; rtDW .
o3sgmp4aev [ 5 ] = rtB . ab2h2zhgij ; rtDW . nld3uzo5io [ 5 ] = rtB .
a3nmhcj3ac ; rtDW . fi4wuwmktb [ 5 ] = rtB . gztw3fbv31 ; rtDW . gm4ivysliu [
5 ] = rtB . hwcg2de5ln ; rtDW . pyurk4he1k [ 5 ] = rtB . cw25rqhbhe ; rtDW .
ocff1ayzzn [ 5 ] = rtB . bohbdh5pos ; rtDW . l0rzviqodi [ 5 ] = rtB .
mg4hzao3ac ; rtDW . o0qik01ouq [ 5 ] = rtB . k3devdomyi ; rtDW . jci52usrwf [
5 ] = rtB . l2ecs4m1wq ; rtDW . n0ifswwd21 [ 5 ] = rtB . lphdmpzics ; for ( i
= 0 ; i < 9 ; i ++ ) { rtDW . emh5kwkq0f [ i ] = rtB . mfqi5bmnfc [ i ] ; }
for ( i = 0 ; i < 5 ; i ++ ) { rtDW . enqlcsixk2 [ ( uint32_T ) i ] = rtDW .
enqlcsixk2 [ i + 1U ] ; rtDW . bq4gap0f1m [ ( uint32_T ) i ] = rtDW .
bq4gap0f1m [ i + 1U ] ; rtDW . lfuv5ipyfs [ ( uint32_T ) i ] = rtDW .
lfuv5ipyfs [ i + 1U ] ; rtDW . f3zvxiekpj [ ( uint32_T ) i ] = rtDW .
f3zvxiekpj [ i + 1U ] ; } rtDW . enqlcsixk2 [ 5 ] = rtB . lofmmfuim4 ; rtDW .
bq4gap0f1m [ 5 ] = rtB . bg5sagtx2f ; rtDW . lfuv5ipyfs [ 5 ] = rtB .
o42245qd4a ; rtDW . f3zvxiekpj [ 5 ] = rtB . e4wgz1h5dw ; for ( i = 0 ; i <
14 ; i ++ ) { rtDW . dspkd5mdvs [ ( uint32_T ) i ] = rtDW . dspkd5mdvs [ i +
1U ] ; } rtDW . dspkd5mdvs [ 14 ] = rtB . oj1n41111k ; for ( i = 0 ; i < 5 ;
i ++ ) { rtDW . gmymeboquk [ ( uint32_T ) i ] = rtDW . gmymeboquk [ i + 1U ]
; } rtDW . gmymeboquk [ 5 ] = rtB . eqti4hemyn ; for ( i = 0 ; i < 8 ; i ++ )
{ rtDW . bs1nmm0jpl [ ( uint32_T ) i ] = rtDW . bs1nmm0jpl [ i + 1U ] ; }
rtDW . bs1nmm0jpl [ 8 ] = rtB . a1lifabcqz ; rtDW . f0lbp4tqqn [ 0U ] = rtDW
. f0lbp4tqqn [ 1U ] ; rtDW . f0lbp4tqqn [ 1U ] = rtDW . f0lbp4tqqn [ 2U ] ;
rtDW . f0lbp4tqqn [ 2 ] = rtB . jqoi3hd2f5 ; for ( i = 0 ; i < 5 ; i ++ ) {
rtDW . bx5vsdt4mt [ ( uint32_T ) i ] = rtDW . bx5vsdt4mt [ i + 1U ] ; rtDW .
hjbvl0tg45 [ ( uint32_T ) i ] = rtDW . hjbvl0tg45 [ i + 1U ] ; rtDW .
nyxm5sdvcd [ ( uint32_T ) i ] = rtDW . nyxm5sdvcd [ i + 1U ] ; rtDW .
fva2rmvmh4 [ ( uint32_T ) i ] = rtDW . fva2rmvmh4 [ i + 1U ] ; rtDW .
hdlc0qsc4w [ ( uint32_T ) i ] = rtDW . hdlc0qsc4w [ i + 1U ] ; } rtDW .
bx5vsdt4mt [ 5 ] = rtB . n4gmeaqzp4 ; rtDW . hjbvl0tg45 [ 5 ] = rtB .
pgp2ddnfdk ; rtDW . nyxm5sdvcd [ 5 ] = rtB . pzyy3abz13 ; rtDW . fva2rmvmh4 [
5 ] = rtB . m4ynyxpbu2 ; rtDW . hdlc0qsc4w [ 5 ] = rtB . ik02utyxan ; for ( i
= 0 ; i < 35 ; i ++ ) { rtDW . ciaqlqmyyx [ ( uint32_T ) i ] = rtDW .
ciaqlqmyyx [ i + 1U ] ; } rtDW . ciaqlqmyyx [ 35 ] = rtB . pqtimdb5j0 ; for (
i = 0 ; i < 5 ; i ++ ) { rtDW . e1kih03oaj [ ( uint32_T ) i ] = rtDW .
e1kih03oaj [ i + 1U ] ; } rtDW . e1kih03oaj [ 5 ] = rtB . f00exjvhy5 ; for (
i = 0 ; i < 26 ; i ++ ) { rtDW . m5gzgpvijm [ ( uint32_T ) i ] = rtDW .
m5gzgpvijm [ i + 1U ] ; rtDW . o3kxgyy1fj [ ( uint32_T ) i ] = rtDW .
o3kxgyy1fj [ i + 1U ] ; } rtDW . m5gzgpvijm [ 26 ] = rtB . mk1wynbhp2 ; rtDW
. o3kxgyy1fj [ 26 ] = rtB . gjoeyfmk32 ; rtDW . mxawq0evig [ 0U ] = rtDW .
mxawq0evig [ 1U ] ; rtDW . mxawq0evig [ 1U ] = rtDW . mxawq0evig [ 2U ] ;
rtDW . mxawq0evig [ 2 ] = rtB . g1mrrh2azp ; rtDW . ocwqpyvhqo = rtB .
j1vdqdq20c ; rtDW . loh1yczrtr = rtB . frhtoi20is ; rtDW . h5lg5oz5ks [ 0U ]
= rtDW . h5lg5oz5ks [ 1U ] ; rtDW . h5lg5oz5ks [ 1U ] = rtDW . h5lg5oz5ks [
2U ] ; rtDW . h5lg5oz5ks [ 2 ] = rtB . krcsx2cqzw ; for ( i = 0 ; i < 5 ; i
++ ) { rtDW . fl4tijqsrl [ ( uint32_T ) i ] = rtDW . fl4tijqsrl [ i + 1U ] ;
rtDW . e1vdezejb0 [ ( uint32_T ) i ] = rtDW . e1vdezejb0 [ i + 1U ] ; rtDW .
nrq4usubsl [ ( uint32_T ) i ] = rtDW . nrq4usubsl [ i + 1U ] ; rtDW .
omuzgpsf1f [ ( uint32_T ) i ] = rtDW . omuzgpsf1f [ i + 1U ] ; rtDW .
hys0om0qbu [ ( uint32_T ) i ] = rtDW . hys0om0qbu [ i + 1U ] ; rtDW .
nkf0blmwkl [ ( uint32_T ) i ] = rtDW . nkf0blmwkl [ i + 1U ] ; rtDW .
nr5d4vqt4t [ ( uint32_T ) i ] = rtDW . nr5d4vqt4t [ i + 1U ] ; rtDW .
cnk414y00k [ ( uint32_T ) i ] = rtDW . cnk414y00k [ i + 1U ] ; rtDW .
fnpjhtoie0 [ ( uint32_T ) i ] = rtDW . fnpjhtoie0 [ i + 1U ] ; rtDW .
frvvvscadt [ ( uint32_T ) i ] = rtDW . frvvvscadt [ i + 1U ] ; rtDW .
pfwwityzhm [ ( uint32_T ) i ] = rtDW . pfwwityzhm [ i + 1U ] ; rtDW .
awvvdj3gzy [ ( uint32_T ) i ] = rtDW . awvvdj3gzy [ i + 1U ] ; rtDW .
esrssadyy0 [ ( uint32_T ) i ] = rtDW . esrssadyy0 [ i + 1U ] ; rtDW .
hggmceleiv [ ( uint32_T ) i ] = rtDW . hggmceleiv [ i + 1U ] ; } rtDW .
fl4tijqsrl [ 5 ] = rtB . lie0qvypkt ; rtDW . e1vdezejb0 [ 5 ] = rtB .
jjunnmldtx ; rtDW . nrq4usubsl [ 5 ] = rtB . ewkvxp0tx3 ; rtDW . omuzgpsf1f [
5 ] = rtB . pxpefqknkg ; rtDW . hys0om0qbu [ 5 ] = rtB . pmnldr5rgz ; rtDW .
nkf0blmwkl [ 5 ] = rtB . gti1gti2ss ; rtDW . nr5d4vqt4t [ 5 ] = rtB .
jorthzrtqn ; rtDW . cnk414y00k [ 5 ] = rtB . kkydc41wz4 ; rtDW . fnpjhtoie0 [
5 ] = rtB . pls0pucbim ; rtDW . frvvvscadt [ 5 ] = rtB . c4jaly0gxz ; rtDW .
pfwwityzhm [ 5 ] = rtB . kmjcmuq4sa ; rtDW . awvvdj3gzy [ 5 ] = rtB .
j4shds0cgp ; rtDW . esrssadyy0 [ 5 ] = rtB . crlo0ykadd ; rtDW . hggmceleiv [
5 ] = rtB . lkfyl1qpfg ; rtDW . cayw42bvqq [ 0U ] = rtDW . cayw42bvqq [ 1U ]
; rtDW . cayw42bvqq [ 1U ] = rtDW . cayw42bvqq [ 2U ] ; rtDW . cayw42bvqq [ 2
] = rtB . ekqsqfqm5z ; rtDW . fmhxej54hb = rtB . pdwhfw3xoj ; for ( i = 0 ; i
< 35 ; i ++ ) { rtDW . pdhtdmqeof [ ( uint32_T ) i ] = rtDW . pdhtdmqeof [ i
+ 1U ] ; } rtDW . pdhtdmqeof [ 35 ] = rtB . avfxnnnygf ; for ( i = 0 ; i < 38
; i ++ ) { rtDW . i3xwoxj5zy [ ( uint32_T ) i ] = rtDW . i3xwoxj5zy [ i + 1U
] ; } rtDW . i3xwoxj5zy [ 38 ] = rtB . m4jtd010un ; for ( i = 0 ; i < 5 ; i
++ ) { rtDW . fzberuaezs [ ( uint32_T ) i ] = rtDW . fzberuaezs [ i + 1U ] ;
rtDW . oiurtflkiv [ ( uint32_T ) i ] = rtDW . oiurtflkiv [ i + 1U ] ; } rtDW
. fzberuaezs [ 5 ] = rtB . k2epoclkhf ; rtDW . oiurtflkiv [ 5 ] = rtB .
o3isut3xe2 ; for ( i = 0 ; i < 17 ; i ++ ) { rtDW . lth0p1kskk [ ( uint32_T )
i ] = rtDW . lth0p1kskk [ i + 1U ] ; } rtDW . lth0p1kskk [ 17 ] = rtB .
krzkvwtyr5 ; for ( i = 0 ; i < 5 ; i ++ ) { rtDW . ko0pv0nfnn [ ( uint32_T )
i ] = rtDW . ko0pv0nfnn [ i + 1U ] ; rtDW . kr1btzpdxw [ ( uint32_T ) i ] =
rtDW . kr1btzpdxw [ i + 1U ] ; rtDW . axidhoghf0 [ ( uint32_T ) i ] = rtDW .
axidhoghf0 [ i + 1U ] ; rtDW . pqgou55kzx [ ( uint32_T ) i ] = rtDW .
pqgou55kzx [ i + 1U ] ; rtDW . fuh3bn4ezo [ ( uint32_T ) i ] = rtDW .
fuh3bn4ezo [ i + 1U ] ; rtDW . kzefheif0g [ ( uint32_T ) i ] = rtDW .
kzefheif0g [ i + 1U ] ; rtDW . aa2p00mqis [ ( uint32_T ) i ] = rtDW .
aa2p00mqis [ i + 1U ] ; rtDW . pasm0mbp1y [ ( uint32_T ) i ] = rtDW .
pasm0mbp1y [ i + 1U ] ; rtDW . jqvl3ulori [ ( uint32_T ) i ] = rtDW .
jqvl3ulori [ i + 1U ] ; rtDW . jez5q1v2di [ ( uint32_T ) i ] = rtDW .
jez5q1v2di [ i + 1U ] ; for ( idxWidth = 0 ; idxWidth < 9 ; idxWidth ++ ) {
rtDW . az4aq4f2to [ i * 9U + idxWidth ] = rtDW . az4aq4f2to [ ( i + 1U ) * 9U
+ idxWidth ] ; } } rtDW . ko0pv0nfnn [ 5 ] = rtB . fonmaxluk5 ; rtDW .
kr1btzpdxw [ 5 ] = rtB . ly2e1zoduv ; rtDW . axidhoghf0 [ 5 ] = rtB .
mel3kf0new ; rtDW . pqgou55kzx [ 5 ] = rtB . hz5f5wlyee ; rtDW . fuh3bn4ezo [
5 ] = rtB . ggxspydiyp ; rtDW . kzefheif0g [ 5 ] = rtB . ntn5swsdwf ; rtDW .
aa2p00mqis [ 5 ] = rtB . htuhckhws0 ; rtDW . pasm0mbp1y [ 5 ] = rtB .
bgjebmhgfv ; rtDW . jqvl3ulori [ 5 ] = rtB . j4uzb05eqs ; rtDW . jez5q1v2di [
5 ] = rtB . e5k1nos5fp ; for ( i = 0 ; i < 9 ; i ++ ) { rtDW . az4aq4f2to [ i
+ 45 ] = rtB . ke0zqpublh [ i ] ; } } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) {
rtDW . mx1dy0gdum [ 0 ] = rtB . ckmlti53ey [ 0 ] ; rtDW . mx1dy0gdum [ 1 ] =
rtB . ckmlti53ey [ 1 ] ; rtDW . mx1dy0gdum [ 2 ] = rtB . ckmlti53ey [ 2 ] ;
rtDW . hv1tfq2dkg = rtB . i11z0ig3jm ; rtDW . ckuddxo2v5 [ 0 ] = rtB .
njb5q03jbz [ 0 ] ; rtDW . hoqlzb3yrr [ 0 ] = rtB . grirtgo1wo [ 0 ] ; rtDW .
d2yav1jvrg [ 0 ] = rtB . edxyvtrnw3 [ 0 ] ; rtDW . ckuddxo2v5 [ 1 ] = rtB .
njb5q03jbz [ 1 ] ; rtDW . hoqlzb3yrr [ 1 ] = rtB . grirtgo1wo [ 1 ] ; rtDW .
d2yav1jvrg [ 1 ] = rtB . edxyvtrnw3 [ 1 ] ; rtDW . ckuddxo2v5 [ 2 ] = rtB .
njb5q03jbz [ 2 ] ; rtDW . hoqlzb3yrr [ 2 ] = rtB . grirtgo1wo [ 2 ] ; rtDW .
d2yav1jvrg [ 2 ] = rtB . edxyvtrnw3 [ 2 ] ; rtDW . pdli3lyef1 = rtB .
jakdxomnmi ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { for ( i = 0 ; i < 7 ; i
++ ) { rtDW . lr1nlrmqch [ ( uint32_T ) i ] = rtDW . lr1nlrmqch [ i + 1U ] ;
rtDW . a44d5qyg12 [ ( uint32_T ) i ] = rtDW . a44d5qyg12 [ i + 1U ] ; } rtDW
. lr1nlrmqch [ 7 ] = rtB . fme5wp01hh ; rtDW . a44d5qyg12 [ 7 ] = rtB .
ijrdbn05so ; for ( i = 0 ; i < 17 ; i ++ ) { rtDW . bwkcfpuwid [ ( uint32_T )
i ] = rtDW . bwkcfpuwid [ i + 1U ] ; rtDW . bb0v2ld5vf [ ( uint32_T ) i ] =
rtDW . bb0v2ld5vf [ i + 1U ] ; rtDW . cno1ak0c3c [ ( uint32_T ) i ] = rtDW .
cno1ak0c3c [ i + 1U ] ; rtDW . nxk0ojgi44 [ ( uint32_T ) i ] = rtDW .
nxk0ojgi44 [ i + 1U ] ; } rtDW . bwkcfpuwid [ 17 ] = rtB . lme3ejskfc ; rtDW
. bb0v2ld5vf [ 17 ] = rtB . jvvqwef1jr ; rtDW . cno1ak0c3c [ 17 ] = rtB .
en2i3j4iug ; rtDW . nxk0ojgi44 [ 17 ] = rtB . dwjldlpqwz ; for ( i = 0 ; i <
7 ; i ++ ) { rtDW . bubytbfjvq [ ( uint32_T ) i ] = rtDW . bubytbfjvq [ i +
1U ] ; } rtDW . bubytbfjvq [ 7 ] = rtB . fme5wp01hh ; for ( i = 0 ; i < 17 ;
i ++ ) { rtDW . glikpzp24u [ ( uint32_T ) i ] = rtDW . glikpzp24u [ i + 1U ]
; } rtDW . glikpzp24u [ 17 ] = rtB . bqjbue4zrx ; for ( i = 0 ; i < 56 ; i ++
) { rtDW . hskq4vr1qs [ ( uint32_T ) i ] = rtDW . hskq4vr1qs [ i + 1U ] ; }
rtDW . hskq4vr1qs [ 56 ] = rtB . axkfxspns0 ; for ( i = 0 ; i < 59 ; i ++ ) {
rtDW . htr1ntw0w0 [ ( uint32_T ) i ] = rtDW . htr1ntw0w0 [ i + 1U ] ; rtDW .
hljbnnt3zw [ ( uint32_T ) i ] = rtDW . hljbnnt3zw [ i + 1U ] ; rtDW .
d2cg15qgjf [ ( uint32_T ) i ] = rtDW . d2cg15qgjf [ i + 1U ] ; } rtDW .
htr1ntw0w0 [ 59 ] = rtB . fsyrkzjyrx ; rtDW . hljbnnt3zw [ 59 ] = rtB .
klvorwbawb ; rtDW . d2cg15qgjf [ 59 ] = rtB . oafknyqwix ; for ( i = 0 ; i <
7 ; i ++ ) { rtDW . ir1mqsar5f [ ( uint32_T ) i ] = rtDW . ir1mqsar5f [ i +
1U ] ; } rtDW . ir1mqsar5f [ 7 ] = rtB . pqtimdb5j0 ; rtDW . kebzxgfy5a = rtB
. kffkzglrlg ; rtDW . pmncprwmz4 = rtB . fmeg1ss5bt ; rtDW . g05suawwrk = rtB
. oirs5ucrzg ; rtDW . ore24n4522 = rtB . g5f1cmb3g1 ; for ( i = 0 ; i < 7 ; i
++ ) { rtDW . f1sl003e30 [ ( uint32_T ) i ] = rtDW . f1sl003e30 [ i + 1U ] ;
} rtDW . f1sl003e30 [ 7 ] = rtB . dolerm5nyh ; for ( i = 0 ; i < 7 ; i ++ ) {
rtDW . mz1lyyodga [ ( uint32_T ) i ] = rtDW . mz1lyyodga [ i + 1U ] ; rtDW .
i22hackosr [ ( uint32_T ) i ] = rtDW . i22hackosr [ i + 1U ] ; } rtDW .
mz1lyyodga [ 7 ] = rtB . haranx30a5 [ 2 ] ; rtDW . i22hackosr [ 7 ] = rtB .
haranx30a5 [ 3 ] ; for ( i = 0 ; i < 17 ; i ++ ) { rtDW . hrf0r3epza [ (
uint32_T ) i ] = rtDW . hrf0r3epza [ i + 1U ] ; rtDW . l4gldy0ied [ (
uint32_T ) i ] = rtDW . l4gldy0ied [ i + 1U ] ; rtDW . jcgd4tqv41 [ (
uint32_T ) i ] = rtDW . jcgd4tqv41 [ i + 1U ] ; } rtDW . hrf0r3epza [ 17 ] =
rtB . loraops0qq ; rtDW . l4gldy0ied [ 17 ] = rtB . cxh2bze2aw ; rtDW .
jcgd4tqv41 [ 17 ] = rtB . iuqrgdsyyu ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) )
{ rtDW . inffcupvx2 = rtB . forvj4qm2y ; rtDW . p21lrpi51b = rtB . jmtjax2f4t
; rtDW . mpvdclcsce = rtB . i2luwb2xg3 ; rtDW . hma0f53x5s = rtB . i2luwb2xg3
; } px4gj3w5ct ( rtS , & rtB . cqjwvwhkzvh , & rtDW . cqjwvwhkzvh ) ;
l1bndan4eb ( rtS , & rtB . azshdeeeiw3 , & rtDW . azshdeeeiw3 ) ; if (
ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . fe3ipxqiw5 = rtB . inbt3za1lf ; } if
( ssIsSampleHit ( rtS , 3 , 0 ) ) { for ( i = 0 ; i < 6 ; i ++ ) { rtDW .
jsu3fijte22m [ i ] = rtB . arkmcvldut [ i ] ; } } if ( ssIsSampleHit ( rtS ,
2 , 0 ) ) { rtDW . mofgw1cji2 = rtB . f0w0cum5km ; rtDW . npqdzcpz4k = rtB .
aw0y5alaor ; for ( i = 0 ; i < 12 ; i ++ ) { rtDW . nz3xkbxksp [ i ] = rtB .
dl4p452e1n [ i ] ; rtDW . cmxd2uv3ip [ i ] = rtB . jryifpteuq [ i ] ; } rtDW
. hbtp4braxp [ 0U ] = rtDW . hbtp4braxp [ 1U ] ; rtDW . hbtp4braxp [ 1U ] =
rtDW . hbtp4braxp [ 2U ] ; rtDW . hbtp4braxp [ 2U ] = rtDW . hbtp4braxp [ 3U
] ; rtDW . hbtp4braxp [ 3U ] = rtDW . hbtp4braxp [ 4U ] ; rtDW . hbtp4braxp [
4 ] = rtB . f0w0cum5km ; rtDW . hyopdoshjp = rtP . Index_Value ; for ( i = 0
; i < 4 ; i ++ ) { for ( idxWidth = 0 ; idxWidth < 8 ; idxWidth ++ ) { rtDW .
hbomutgs5x [ ( ( uint32_T ) i << 3 ) + idxWidth ] = rtDW . hbomutgs5x [ ( ( i
+ 1U ) << 3 ) + idxWidth ] ; } } for ( i = 0 ; i < 8 ; i ++ ) { rtDW .
hbomutgs5x [ i + 32 ] = rtB . eprprovalw [ i ] ; } rtDW . ifa1aifv0v [ 0U ] =
rtDW . ifa1aifv0v [ 1U ] ; rtDW . ifa1aifv0v [ 1U ] = rtDW . ifa1aifv0v [ 2U
] ; rtDW . ifa1aifv0v [ 2U ] = rtDW . ifa1aifv0v [ 3U ] ; rtDW . ifa1aifv0v [
3U ] = rtDW . ifa1aifv0v [ 4U ] ; rtDW . ifa1aifv0v [ 4 ] = rtP .
ValidOut1_Value ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . dq0pmdxppu
= rtB . nimpzzl3rt [ 1 ] ; rtDW . gvxq4lgohv = rtB . nimpzzl3rt [ 0 ] ; } if
( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . kkklfomjr5 [ 0U ] = rtDW .
kkklfomjr5 [ 1U ] ; rtDW . kkklfomjr5 [ 1 ] = rtB . llye522vj1 ; } px4gj3w5ct
( rtS , & rtB . cstc0v1lpw , & rtDW . cstc0v1lpw ) ; l1bndan4eb ( rtS , & rtB
. mzoe5aiivc , & rtDW . mzoe5aiivc ) ; px4gj3w5ct ( rtS , & rtB . msqwmshj2n
, & rtDW . msqwmshj2n ) ; l1bndan4eb ( rtS , & rtB . biyhxca30f , & rtDW .
biyhxca30f ) ; if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . ituktxufmb [ 0 ]
= rtB . dcyymdlgr3 [ 0 ] ; rtDW . epsbkv53pu [ 0 ] = rtB . iztliysr2c [ 0 ] ;
rtDW . cmh2vel5ym [ 0 ] = rtB . gjirmvlhql [ 0 ] ; rtDW . ituktxufmb [ 1 ] =
rtB . dcyymdlgr3 [ 1 ] ; rtDW . epsbkv53pu [ 1 ] = rtB . iztliysr2c [ 1 ] ;
rtDW . cmh2vel5ym [ 1 ] = rtB . gjirmvlhql [ 1 ] ; rtDW . ituktxufmb [ 2 ] =
rtB . dcyymdlgr3 [ 2 ] ; rtDW . epsbkv53pu [ 2 ] = rtB . iztliysr2c [ 2 ] ;
rtDW . cmh2vel5ym [ 2 ] = rtB . gjirmvlhql [ 2 ] ; rtDW . fqvcumyba1 = rtB .
hbkhdg0qsb ; rtDW . cgg3v13mlz = rtB . k2ndgrxbvv ; rtDW . njfpshnpni = rtB .
j3et02wxql ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtDW . py4iuvrbea = rtB
. nh3gjjgpvk ; rtDW . a43rt5p5qk = rtB . oru1rzybc2 ; } if ( ssIsSampleHit (
rtS , 4 , 0 ) ) { rtDW . ffjft2t0pj = rtB . bohcvczirh ; rtDW . e5cexk5tsa =
rtB . bttgnayvtn ; } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { for ( i = 0 ; i <
6 ; i ++ ) { rtDW . jsu3fijte22 [ i ] = rtB . lvxw1arzhe [ i ] ; } } if (
ssIsSampleHit ( rtS , 2 , 0 ) ) { rtDW . fmvtpht2wc = rtB . brsz4ajf4x ; rtDW
. bjzrd2jgh1 = rtB . e2ntsret2e ; for ( i = 0 ; i < 12 ; i ++ ) { rtDW .
etncgat1qk [ i ] = rtB . fld2qyvslw [ i ] ; rtDW . j0pfyx5sl0 [ i ] = rtB .
brenn0ae3u [ i ] ; } rtDW . jlwpaqqpol [ 0U ] = rtDW . jlwpaqqpol [ 1U ] ;
rtDW . jlwpaqqpol [ 1U ] = rtDW . jlwpaqqpol [ 2U ] ; rtDW . jlwpaqqpol [ 2U
] = rtDW . jlwpaqqpol [ 3U ] ; rtDW . jlwpaqqpol [ 3U ] = rtDW . jlwpaqqpol [
4U ] ; rtDW . jlwpaqqpol [ 4 ] = rtB . brsz4ajf4x ; rtDW . avqcisj0g1 = rtP .
Index_Value_fzocaavlvm ; for ( i = 0 ; i < 4 ; i ++ ) { for ( idxWidth = 0 ;
idxWidth < 8 ; idxWidth ++ ) { rtDW . otdqomronl [ ( ( uint32_T ) i << 3 ) +
idxWidth ] = rtDW . otdqomronl [ ( ( i + 1U ) << 3 ) + idxWidth ] ; } } for (
i = 0 ; i < 8 ; i ++ ) { rtDW . otdqomronl [ i + 32 ] = rtB . asxknbd3q5 [ i
] ; } rtDW . o2nyvbjxnw [ 0U ] = rtDW . o2nyvbjxnw [ 1U ] ; rtDW . o2nyvbjxnw
[ 1U ] = rtDW . o2nyvbjxnw [ 2U ] ; rtDW . o2nyvbjxnw [ 2U ] = rtDW .
o2nyvbjxnw [ 3U ] ; rtDW . o2nyvbjxnw [ 3U ] = rtDW . o2nyvbjxnw [ 4U ] ;
rtDW . o2nyvbjxnw [ 4 ] = rtP . ValidOut1_Value_fddponpq1g ; } if (
ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW . anqq4l0npb = rtB . kdtkapks5q [ 1 ]
; rtDW . mam5vcqfvx = rtB . kdtkapks5q [ 0 ] ; } if ( ssIsSampleHit ( rtS , 4
, 0 ) ) { rtDW . d2ne5d41vh = rtB . a4s3xvlbex ; } if ( ssIsSampleHit ( rtS ,
3 , 0 ) ) { for ( i = 0 ; i < 6 ; i ++ ) { rtDW . jsu3fijte2 [ i ] = rtB .
ilatryxyc3 [ i ] ; } } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { rtDW .
lbwbhxgeac = rtB . c25uz5tds5 ; rtDW . llxyyz4q5x = rtB . kycn2fuam4 ; for (
i = 0 ; i < 12 ; i ++ ) { rtDW . oyxqmd0f4v [ i ] = rtB . b5hsoldwxb [ i ] ;
rtDW . cdd1gh0rmi [ i ] = rtB . jiuomirfvx [ i ] ; } rtDW . lgjrfdubva [ 0U ]
= rtDW . lgjrfdubva [ 1U ] ; rtDW . lgjrfdubva [ 1U ] = rtDW . lgjrfdubva [
2U ] ; rtDW . lgjrfdubva [ 2U ] = rtDW . lgjrfdubva [ 3U ] ; rtDW .
lgjrfdubva [ 3U ] = rtDW . lgjrfdubva [ 4U ] ; rtDW . lgjrfdubva [ 4 ] = rtB
. c25uz5tds5 ; rtDW . azvnw5pvht = rtP . Index_Value_co5ixudaqi ; for ( i = 0
; i < 4 ; i ++ ) { for ( idxWidth = 0 ; idxWidth < 8 ; idxWidth ++ ) { rtDW .
ayjsmpf3pd [ ( ( uint32_T ) i << 3 ) + idxWidth ] = rtDW . ayjsmpf3pd [ ( ( i
+ 1U ) << 3 ) + idxWidth ] ; } } for ( i = 0 ; i < 8 ; i ++ ) { rtDW .
ayjsmpf3pd [ i + 32 ] = rtB . amtihtn1an [ i ] ; } rtDW . il1i11vhya [ 0U ] =
rtDW . il1i11vhya [ 1U ] ; rtDW . il1i11vhya [ 1U ] = rtDW . il1i11vhya [ 2U
] ; rtDW . il1i11vhya [ 2U ] = rtDW . il1i11vhya [ 3U ] ; rtDW . il1i11vhya [
3U ] = rtDW . il1i11vhya [ 4U ] ; rtDW . il1i11vhya [ 4 ] = rtP .
ValidOut1_Value_lbhou0b3dw ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { rtDW .
on2kbwtd1i = rtB . kwpowwsiez [ 1 ] ; rtDW . myfhgr2zam = rtB . kwpowwsiez [
0 ] ; } UNUSED_PARAMETER ( tid ) ; } void MdlUpdateTID6 ( int_T tid ) {
UNUSED_PARAMETER ( tid ) ; } void MdlDerivatives ( void ) { XDot * _rtXdot ;
_rtXdot = ( ( XDot * ) ssGetdX ( rtS ) ) ; _rtXdot -> ptze3ue0cm = rtB .
cqqwj4hgbc ; _rtXdot -> flellzbl1y = rtB . nwpl41ljbn ; } void MdlProjection
( void ) { } void MdlTerminate ( void ) { nn0sefi01r ( rtS , & rtDW .
cqjwvwhkzvh ) ; nn0sefi01r ( rtS , & rtDW . cstc0v1lpw ) ; nn0sefi01r ( rtS ,
& rtDW . msqwmshj2n ) ; { if ( rtDW . gwqsbwh5jo . AQHandles ) {
sdiTerminateStreaming ( & rtDW . gwqsbwh5jo . AQHandles ) ; } } { if ( rtDW .
p3pqosjddk . AQHandles ) { sdiTerminateStreaming ( & rtDW . p3pqosjddk .
AQHandles ) ; } } { if ( rtDW . e0liuhgquprw . AQHandles ) {
sdiTerminateStreaming ( & rtDW . e0liuhgquprw . AQHandles ) ; } } { if ( rtDW
. ityuo0nupl . AQHandles ) { sdiTerminateStreaming ( & rtDW . ityuo0nupl .
AQHandles ) ; } } { if ( rtDW . lrdg4xmzak . AQHandles ) {
sdiTerminateStreaming ( & rtDW . lrdg4xmzak . AQHandles ) ; } } { if ( rtDW .
fkpb3hpobh . AQHandles ) { sdiTerminateStreaming ( & rtDW . fkpb3hpobh .
AQHandles ) ; } } { if ( rtDW . euzuyivlcf . AQHandles ) {
sdiTerminateStreaming ( & rtDW . euzuyivlcf . AQHandles ) ; } } { if ( rtDW .
hzgoj3w1ci . AQHandles ) { sdiTerminateStreaming ( & rtDW . hzgoj3w1ci .
AQHandles ) ; } } { if ( rtDW . k2wlyn1paf . AQHandles ) {
sdiTerminateStreaming ( & rtDW . k2wlyn1paf . AQHandles ) ; } } { if ( rtDW .
f4ugnmm3af . AQHandles ) { sdiTerminateStreaming ( & rtDW . f4ugnmm3af .
AQHandles ) ; } } { if ( rtDW . lnwwdousnr . AQHandles ) {
sdiTerminateStreaming ( & rtDW . lnwwdousnr . AQHandles ) ; } } { if ( rtDW .
b3y2ruf2y2 . AQHandles ) { sdiTerminateStreaming ( & rtDW . b3y2ruf2y2 .
AQHandles ) ; } } { if ( rtDW . f0zxs3dlyt . AQHandles ) {
sdiTerminateStreaming ( & rtDW . f0zxs3dlyt . AQHandles ) ; } } { if ( rtDW .
hdsszfpsby . AQHandles ) { sdiTerminateStreaming ( & rtDW . hdsszfpsby .
AQHandles ) ; } } { if ( rtDW . exqvxbdaup . AQHandles ) {
sdiTerminateStreaming ( & rtDW . exqvxbdaup . AQHandles ) ; } } { if ( rtDW .
ettcurcs0e . AQHandles ) { sdiTerminateStreaming ( & rtDW . ettcurcs0e .
AQHandles ) ; } } { if ( rtDW . c0e12yj12u . AQHandles ) {
sdiTerminateStreaming ( & rtDW . c0e12yj12u . AQHandles ) ; } } { if ( rtDW .
e0liuhgqupr . AQHandles ) { sdiTerminateStreaming ( & rtDW . e0liuhgqupr .
AQHandles ) ; } } { if ( rtDW . e0liuhgqup . AQHandles ) {
sdiTerminateStreaming ( & rtDW . e0liuhgqup . AQHandles ) ; } } } static void
mr_uz_drive_model_cacheDataAsMxArray ( mxArray * destArray , mwIndex i , int
j , const void * srcData , size_t numBytes ) ; static void
mr_uz_drive_model_cacheDataAsMxArray ( mxArray * destArray , mwIndex i , int
j , const void * srcData , size_t numBytes ) { mxArray * newArray =
mxCreateUninitNumericMatrix ( ( size_t ) 1 , numBytes , mxUINT8_CLASS ,
mxREAL ) ; memcpy ( ( uint8_T * ) mxGetData ( newArray ) , ( const uint8_T *
) srcData , numBytes ) ; mxSetFieldByNumber ( destArray , i , j , newArray )
; } static void mr_uz_drive_model_restoreDataFromMxArray ( void * destData ,
const mxArray * srcArray , mwIndex i , int j , size_t numBytes ) ; static
void mr_uz_drive_model_restoreDataFromMxArray ( void * destData , const
mxArray * srcArray , mwIndex i , int j , size_t numBytes ) { memcpy ( (
uint8_T * ) destData , ( const uint8_T * ) mxGetData ( mxGetFieldByNumber (
srcArray , i , j ) ) , numBytes ) ; } static void
mr_uz_drive_model_cacheBitFieldToMxArray ( mxArray * destArray , mwIndex i ,
int j , uint_T bitVal ) ; static void
mr_uz_drive_model_cacheBitFieldToMxArray ( mxArray * destArray , mwIndex i ,
int j , uint_T bitVal ) { mxSetFieldByNumber ( destArray , i , j ,
mxCreateDoubleScalar ( ( double ) bitVal ) ) ; } static uint_T
mr_uz_drive_model_extractBitFieldFromMxArray ( const mxArray * srcArray ,
mwIndex i , int j , uint_T numBits ) ; static uint_T
mr_uz_drive_model_extractBitFieldFromMxArray ( const mxArray * srcArray ,
mwIndex i , int j , uint_T numBits ) { const uint_T varVal = ( uint_T )
mxGetScalar ( mxGetFieldByNumber ( srcArray , i , j ) ) ; return varVal & ( (
1u << numBits ) - 1u ) ; } static void
mr_uz_drive_model_cacheDataToMxArrayWithOffset ( mxArray * destArray ,
mwIndex i , int j , mwIndex offset , const void * srcData , size_t numBytes )
; static void mr_uz_drive_model_cacheDataToMxArrayWithOffset ( mxArray *
destArray , mwIndex i , int j , mwIndex offset , const void * srcData ,
size_t numBytes ) { uint8_T * varData = ( uint8_T * ) mxGetData (
mxGetFieldByNumber ( destArray , i , j ) ) ; memcpy ( ( uint8_T * ) & varData
[ offset * numBytes ] , ( const uint8_T * ) srcData , numBytes ) ; } static
void mr_uz_drive_model_restoreDataFromMxArrayWithOffset ( void * destData ,
const mxArray * srcArray , mwIndex i , int j , mwIndex offset , size_t
numBytes ) ; static void mr_uz_drive_model_restoreDataFromMxArrayWithOffset (
void * destData , const mxArray * srcArray , mwIndex i , int j , mwIndex
offset , size_t numBytes ) { const uint8_T * varData = ( const uint8_T * )
mxGetData ( mxGetFieldByNumber ( srcArray , i , j ) ) ; memcpy ( ( uint8_T *
) destData , ( const uint8_T * ) & varData [ offset * numBytes ] , numBytes )
; } static void mr_uz_drive_model_cacheBitFieldToCellArrayWithOffset (
mxArray * destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal )
; static void mr_uz_drive_model_cacheBitFieldToCellArrayWithOffset ( mxArray
* destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal ) {
mxSetCell ( mxGetFieldByNumber ( destArray , i , j ) , offset ,
mxCreateDoubleScalar ( ( double ) fieldVal ) ) ; } static uint_T
mr_uz_drive_model_extractBitFieldFromCellArrayWithOffset ( const mxArray *
srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) ; static
uint_T mr_uz_drive_model_extractBitFieldFromCellArrayWithOffset ( const
mxArray * srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) {
const uint_T fieldVal = ( uint_T ) mxGetScalar ( mxGetCell (
mxGetFieldByNumber ( srcArray , i , j ) , offset ) ) ; return fieldVal & ( (
1u << numBits ) - 1u ) ; } mxArray * mr_uz_drive_model_GetDWork ( ) { static
const char * ssDWFieldNames [ 3 ] = { "rtB" , "rtDW" , "rtPrevZCX" , } ;
mxArray * ssDW = mxCreateStructMatrix ( 1 , 1 , 3 , ssDWFieldNames ) ;
mr_uz_drive_model_cacheDataAsMxArray ( ssDW , 0 , 0 , ( const void * ) & (
rtB ) , sizeof ( rtB ) ) ; { static const char * rtdwDataFieldNames [ 384 ] =
{ "rtDW.ituktxufmb" , "rtDW.epsbkv53pu" , "rtDW.cmh2vel5ym" ,
"rtDW.miazophk3q" , "rtDW.cnrqogla5d" , "rtDW.aanjcgvfa0" , "rtDW.aoxcwu3qll"
, "rtDW.gnh32qpzkl" , "rtDW.ihfcziqcgk" , "rtDW.eahq4k0qba" ,
"rtDW.oo31woulsl" , "rtDW.blhgrykwvp" , "rtDW.osqohvejno" , "rtDW.cvcfermial"
, "rtDW.ocn3tuy1mq" , "rtDW.lzrfskvb50" , "rtDW.kxzyyq15r0" ,
"rtDW.jfrl3cqm1n" , "rtDW.ayahx5voca" , "rtDW.l2zkdqsp2y" , "rtDW.lxk5izw00o"
, "rtDW.cqp1dau03w" , "rtDW.gfiovjo3e2" , "rtDW.p2iwsajmfp" ,
"rtDW.b4auxd1lsk" , "rtDW.al5aajfx21" , "rtDW.gt3chc0tga" , "rtDW.erukb0glgz"
, "rtDW.pdjkbbbzjq" , "rtDW.pml0yl52te" , "rtDW.eswvf4pz4v" ,
"rtDW.phidvr4lhk" , "rtDW.atdfcebxbc" , "rtDW.o3sgmp4aev" , "rtDW.nld3uzo5io"
, "rtDW.fi4wuwmktb" , "rtDW.gm4ivysliu" , "rtDW.pyurk4he1k" ,
"rtDW.ocff1ayzzn" , "rtDW.l0rzviqodi" , "rtDW.o0qik01ouq" , "rtDW.jci52usrwf"
, "rtDW.n0ifswwd21" , "rtDW.enqlcsixk2" , "rtDW.bq4gap0f1m" ,
"rtDW.lfuv5ipyfs" , "rtDW.hjbvl0tg45" , "rtDW.nyxm5sdvcd" , "rtDW.f0lbp4tqqn"
, "rtDW.fva2rmvmh4" , "rtDW.hdlc0qsc4w" , "rtDW.fl4tijqsrl" ,
"rtDW.mxawq0evig" , "rtDW.e1vdezejb0" , "rtDW.nrq4usubsl" , "rtDW.omuzgpsf1f"
, "rtDW.hys0om0qbu" , "rtDW.nr5d4vqt4t" , "rtDW.cnk414y00k" ,
"rtDW.fnpjhtoie0" , "rtDW.frvvvscadt" , "rtDW.pfwwityzhm" , "rtDW.awvvdj3gzy"
, "rtDW.esrssadyy0" , "rtDW.loh1yczrtr" , "rtDW.cayw42bvqq" ,
"rtDW.fmhxej54hb" , "rtDW.fzberuaezs" , "rtDW.oiurtflkiv" , "rtDW.cedwdfuxlq"
, "rtDW.ny5tmca5u1" , "rtDW.k3sz0zxcz4" , "rtDW.hafwy3njkc" ,
"rtDW.gqa5jm0r2v" , "rtDW.inffcupvx2" , "rtDW.p21lrpi51b" , "rtDW.mpvdclcsce"
, "rtDW.hma0f53x5s" , "rtDW.fbadxescvd" , "rtDW.neqcp2rk0x" ,
"rtDW.injrnpzipy" , "rtDW.cgg3v13mlz" , "rtDW.ffjft2t0pj" , "rtDW.jayew5vh20"
, "rtDW.gtl5stszrm" , "rtDW.pacgla51lq" , "rtDW.jntfw1jmxj" ,
"rtDW.ml1vr0zmzd" , "rtDW.ietukijfm5" , "rtDW.hcvygsausk" , "rtDW.osj02yjrnn"
, "rtDW.o3dbqj4xyk" , "rtDW.ghxlzewxqv" , "rtDW.jw4znmasof" ,
"rtDW.jsu3fijte2" , "rtDW.my5afrzgkd" , "rtDW.edo3dr0fru" , "rtDW.hyaxdywynl"
, "rtDW.on2kbwtd1i" , "rtDW.lfzkcubuyh" , "rtDW.bt2kw45n5u" ,
"rtDW.eqzj0rxvun" , "rtDW.ilnpea2zjg" , "rtDW.ddhgjj4slr" , "rtDW.cguk3rlz2c"
, "rtDW.myfhgr2zam" , "rtDW.jsu3fijte22" , "rtDW.my5afrzgkdf" ,
"rtDW.edo3dr0fru5" , "rtDW.hyaxdywynlc" , "rtDW.anqq4l0npb" ,
"rtDW.o13fmizguv" , "rtDW.hdglqralt5" , "rtDW.ptnxk4g0lc" , "rtDW.pjnb2ek2e3"
, "rtDW.m0rv3vqddv" , "rtDW.o10ebbt22e" , "rtDW.mam5vcqfvx" ,
"rtDW.jsu3fijte22m" , "rtDW.my5afrzgkdfq" , "rtDW.edo3dr0fru5x" ,
"rtDW.hyaxdywynlcl" , "rtDW.dq0pmdxppu" , "rtDW.jpqfmeeeto" ,
"rtDW.p25vgyovxo" , "rtDW.fgxsmumrmw" , "rtDW.p3km4baqfe" , "rtDW.agchj4uiph"
, "rtDW.fd5nlfaj2u" , "rtDW.gvxq4lgohv" , "rtDW.ixrsi3erhf" ,
"rtDW.jis1uepreo" , "rtDW.fwkxey5epo" , "rtDW.pnsuou2020" , "rtDW.opg1thx2qw"
, "rtDW.amalc3ffil" , "rtDW.mwenvz0tar" , "rtDW.de3otshxus" ,
"rtDW.i2ctd1awel" , "rtDW.ccf5juo5ya" , "rtDW.i4lkkodfyj" , "rtDW.mdvclm3wpb"
, "rtDW.gai5nv42oe" , "rtDW.imfxseqvvv" , "rtDW.cxatkad2jz" ,
"rtDW.ikxzuowx1v" , "rtDW.bg2vv1po0e" , "rtDW.f4tcd4udur" , "rtDW.ctbynjdwij"
, "rtDW.anfxf0zt2u" , "rtDW.afo0nwhxua" , "rtDW.jdtstycpmg" ,
"rtDW.g2ry4vjsj1" , "rtDW.iehvrkddj2" , "rtDW.nbavx35izv" , "rtDW.cl1vsftpzn"
, "rtDW.lhojsnn24m" , "rtDW.d42pvxfz0g" , "rtDW.kovzbujdnb" ,
"rtDW.dttn4xmcnk" , "rtDW.n1ap5w5rdi" , "rtDW.ndb122ek3u" , "rtDW.hoesofthyy"
, "rtDW.ifur0qjdev" , "rtDW.h2z1m5wxiy" , "rtDW.dviol1u0jv" ,
"rtDW.df5ibuzfvl" , "rtDW.ikv4gqtanm" , "rtDW.hru10ym4o1" , "rtDW.erp5nno2ec"
, "rtDW.ima1cclrzn" , "rtDW.hm24hbgcg1" , "rtDW.ob20xueupt" ,
"rtDW.emh5kwkq0f" , "rtDW.f3zvxiekpj" , "rtDW.dspkd5mdvs" , "rtDW.gmymeboquk"
, "rtDW.bs1nmm0jpl" , "rtDW.bx5vsdt4mt" , "rtDW.ciaqlqmyyx" ,
"rtDW.e1kih03oaj" , "rtDW.m5gzgpvijm" , "rtDW.o3kxgyy1fj" , "rtDW.nkf0blmwkl"
, "rtDW.h5lg5oz5ks" , "rtDW.hggmceleiv" , "rtDW.pdhtdmqeof" ,
"rtDW.i3xwoxj5zy" , "rtDW.lth0p1kskk" , "rtDW.ko0pv0nfnn" , "rtDW.kr1btzpdxw"
, "rtDW.axidhoghf0" , "rtDW.pqgou55kzx" , "rtDW.fuh3bn4ezo" ,
"rtDW.kzefheif0g" , "rtDW.aa2p00mqis" , "rtDW.pasm0mbp1y" , "rtDW.jqvl3ulori"
, "rtDW.jez5q1v2di" , "rtDW.lr1nlrmqch" , "rtDW.a44d5qyg12" ,
"rtDW.bwkcfpuwid" , "rtDW.cno1ak0c3c" , "rtDW.nxk0ojgi44" , "rtDW.bubytbfjvq"
, "rtDW.glikpzp24u" , "rtDW.hskq4vr1qs" , "rtDW.hljbnnt3zw" ,
"rtDW.d2cg15qgjf" , "rtDW.ir1mqsar5f" , "rtDW.kebzxgfy5a" , "rtDW.pmncprwmz4"
, "rtDW.g05suawwrk" , "rtDW.ore24n4522" , "rtDW.mz1lyyodga" ,
"rtDW.i22hackosr" , "rtDW.hrf0r3epza" , "rtDW.l4gldy0ied" , "rtDW.jcgd4tqv41"
, "rtDW.oyxqmd0f4v" , "rtDW.cdd1gh0rmi" , "rtDW.ayjsmpf3pd" ,
"rtDW.etncgat1qk" , "rtDW.j0pfyx5sl0" , "rtDW.otdqomronl" , "rtDW.nz3xkbxksp"
, "rtDW.cmxd2uv3ip" , "rtDW.hbomutgs5x" , "rtDW.kkklfomjr5" ,
"rtDW.dmmot30jq4" , "rtDW.dzr2rntvvo" , "rtDW.aw0bxhrzal" , "rtDW.estezyunas"
, "rtDW.olzifhaukx" , "rtDW.miwm3apiea" , "rtDW.otborblus0" ,
"rtDW.jcievkrvvv" , "rtDW.ovlbtlz2z5" , "rtDW.mx1dy0gdum" , "rtDW.iygynuhhiw"
, "rtDW.oamcwpfckc" , "rtDW.az4aq4f2to" , "rtDW.hv1tfq2dkg" ,
"rtDW.ckuddxo2v5" , "rtDW.hoqlzb3yrr" , "rtDW.d2yav1jvrg" , "rtDW.pdli3lyef1"
, "rtDW.bqjtw0doyx" , "rtDW.cc421u2f3f" , "rtDW.pdjafikrtl" ,
"rtDW.pojlxrwx0d" , "rtDW.m4fnnxykzj" , "rtDW.k40ux0ctpf" , "rtDW.kvknfbkwvk"
, "rtDW.by04uer2xp" , "rtDW.n1vlvivlrx" , "rtDW.ib3g0mc4j4" ,
"rtDW.c3coe5r3z1" , "rtDW.gopfnpfdpo" , "rtDW.fhefxq1ozn" , "rtDW.bfidcyeanb"
, "rtDW.fi31qowovj" , "rtDW.pbpmgsmorm" , "rtDW.axle03m4av" ,
"rtDW.evcuev5sfd" , "rtDW.cblzsrog5u" , "rtDW.nqfbacpvcp" , "rtDW.fdktvwm3kd"
, "rtDW.bjkklesnma" , "rtDW.nsaa1gti0b" , "rtDW.ghx0ts2zzs" ,
"rtDW.lafrvsvgf0" , "rtDW.og3lno4rre" , "rtDW.ld5g5vrgmj" , "rtDW.niztd2zg4p"
, "rtDW.faadh0wdog" , "rtDW.jgx0xkzgjo" , "rtDW.gpf5tclqta" ,
"rtDW.mvfamndgj4" , "rtDW.kcaj1yegtz" , "rtDW.guhdmzy0n4" , "rtDW.bi1fzovgs2"
, "rtDW.llxyyz4q5x" , "rtDW.bjzrd2jgh1" , "rtDW.npqdzcpz4k" ,
"rtDW.k44l31otpd" , "rtDW.ocwqpyvhqo" , "rtDW.bb0v2ld5vf" , "rtDW.htr1ntw0w0"
, "rtDW.f1sl003e30" , "rtDW.lbwbhxgeac" , "rtDW.lgjrfdubva" ,
"rtDW.il1i11vhya" , "rtDW.fmvtpht2wc" , "rtDW.jlwpaqqpol" , "rtDW.o2nyvbjxnw"
, "rtDW.mofgw1cji2" , "rtDW.hbtp4braxp" , "rtDW.ifa1aifv0v" ,
"rtDW.azvnw5pvht" , "rtDW.avqcisj0g1" , "rtDW.hyopdoshjp" , "rtDW.fqvcumyba1"
, "rtDW.njfpshnpni" , "rtDW.k0efqstpz0" , "rtDW.jitieevvno" ,
"rtDW.ip0d0t1043" , "rtDW.i1c4xekdhn" , "rtDW.bfyezaoly2" , "rtDW.idcpojjs11"
, "rtDW.fe3ipxqiw5" , "rtDW.hw1g0wvqpq" , "rtDW.iw5qsles1z" ,
"rtDW.gomqyfi1fi" , "rtDW.dczrefoerg" , "rtDW.py4iuvrbea" , "rtDW.a43rt5p5qk"
, "rtDW.e5cexk5tsa" , "rtDW.d2ne5d41vh" , "rtDW.gdbbfmmgdg" ,
"rtDW.jd2ppumcjt" , "rtDW.cx41wglw3j.bineo4prgi" ,
"rtDW.cx41wglw3j.bvutux0ucw" , "rtDW.jjob4ur221.bineo4prgi" ,
"rtDW.jjob4ur221.bvutux0ucw" , "rtDW.jogryxdnkz.bineo4prgi" ,
"rtDW.jogryxdnkz.bvutux0ucw" , "rtDW.n4cqr1dkmr.bineo4prgi" ,
"rtDW.n4cqr1dkmr.bvutux0ucw" , "rtDW.a13lr3lsi3.bineo4prgi" ,
"rtDW.a13lr3lsi3.bvutux0ucw" , "rtDW.jjajpmoyel.bineo4prgi" ,
"rtDW.jjajpmoyel.bvutux0ucw" , "rtDW.ndmeqad3sm.bineo4prgi" ,
"rtDW.ndmeqad3sm.bvutux0ucw" , "rtDW.o0tbmhvpds.bineo4prgi" ,
"rtDW.o0tbmhvpds.bvutux0ucw" , "rtDW.f5mkygzljka.bineo4prgi" ,
"rtDW.f5mkygzljka.bvutux0ucw" , "rtDW.biyhxca30f.ftf50xwldj" ,
"rtDW.biyhxca30f.ic4jzsnsgd" , "rtDW.biyhxca30f.j5itaoriq1" ,
"rtDW.biyhxca30f.bjona3wx3v" , "rtDW.biyhxca30f.bldvjsjmit" ,
"rtDW.biyhxca30f.opg33homib" , "rtDW.biyhxca30f.n4jsnmm3dp" ,
"rtDW.biyhxca30f.bnbpcxxvih" , "rtDW.biyhxca30f.e4ertwjipw" ,
"rtDW.msqwmshj2n.ltyokv5jui" , "rtDW.msqwmshj2n.dmqhv1kuog" ,
"rtDW.msqwmshj2n.grzcmycdpb" , "rtDW.msqwmshj2n.hlqhpqgl5d" ,
"rtDW.msqwmshj2n.dqmv313jji" , "rtDW.msqwmshj2n.jaldgiolnb" ,
"rtDW.mzoe5aiivc.ftf50xwldj" , "rtDW.mzoe5aiivc.ic4jzsnsgd" ,
"rtDW.mzoe5aiivc.j5itaoriq1" , "rtDW.mzoe5aiivc.bjona3wx3v" ,
"rtDW.mzoe5aiivc.bldvjsjmit" , "rtDW.mzoe5aiivc.opg33homib" ,
"rtDW.mzoe5aiivc.n4jsnmm3dp" , "rtDW.mzoe5aiivc.bnbpcxxvih" ,
"rtDW.mzoe5aiivc.e4ertwjipw" , "rtDW.cstc0v1lpw.ltyokv5jui" ,
"rtDW.cstc0v1lpw.dmqhv1kuog" , "rtDW.cstc0v1lpw.grzcmycdpb" ,
"rtDW.cstc0v1lpw.hlqhpqgl5d" , "rtDW.cstc0v1lpw.dqmv313jji" ,
"rtDW.cstc0v1lpw.jaldgiolnb" , "rtDW.azshdeeeiw3.ftf50xwldj" ,
"rtDW.azshdeeeiw3.ic4jzsnsgd" , "rtDW.azshdeeeiw3.j5itaoriq1" ,
"rtDW.azshdeeeiw3.bjona3wx3v" , "rtDW.azshdeeeiw3.bldvjsjmit" ,
"rtDW.azshdeeeiw3.opg33homib" , "rtDW.azshdeeeiw3.n4jsnmm3dp" ,
"rtDW.azshdeeeiw3.bnbpcxxvih" , "rtDW.azshdeeeiw3.e4ertwjipw" ,
"rtDW.cqjwvwhkzvh.ltyokv5jui" , "rtDW.cqjwvwhkzvh.dmqhv1kuog" ,
"rtDW.cqjwvwhkzvh.grzcmycdpb" , "rtDW.cqjwvwhkzvh.hlqhpqgl5d" ,
"rtDW.cqjwvwhkzvh.dqmv313jji" , "rtDW.cqjwvwhkzvh.jaldgiolnb" , } ; mxArray *
rtdwData = mxCreateStructMatrix ( 1 , 1 , 384 , rtdwDataFieldNames ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 0 , ( const void * ) &
( rtDW . ituktxufmb ) , sizeof ( rtDW . ituktxufmb ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 1 , ( const void * ) &
( rtDW . epsbkv53pu ) , sizeof ( rtDW . epsbkv53pu ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 2 , ( const void * ) &
( rtDW . cmh2vel5ym ) , sizeof ( rtDW . cmh2vel5ym ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 3 , ( const void * ) &
( rtDW . miazophk3q ) , sizeof ( rtDW . miazophk3q ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 4 , ( const void * ) &
( rtDW . cnrqogla5d ) , sizeof ( rtDW . cnrqogla5d ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 5 , ( const void * ) &
( rtDW . aanjcgvfa0 ) , sizeof ( rtDW . aanjcgvfa0 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 6 , ( const void * ) &
( rtDW . aoxcwu3qll ) , sizeof ( rtDW . aoxcwu3qll ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 7 , ( const void * ) &
( rtDW . gnh32qpzkl ) , sizeof ( rtDW . gnh32qpzkl ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 8 , ( const void * ) &
( rtDW . ihfcziqcgk ) , sizeof ( rtDW . ihfcziqcgk ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 9 , ( const void * ) &
( rtDW . eahq4k0qba ) , sizeof ( rtDW . eahq4k0qba ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 10 , ( const void * ) &
( rtDW . oo31woulsl ) , sizeof ( rtDW . oo31woulsl ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 11 , ( const void * ) &
( rtDW . blhgrykwvp ) , sizeof ( rtDW . blhgrykwvp ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 12 , ( const void * ) &
( rtDW . osqohvejno ) , sizeof ( rtDW . osqohvejno ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 13 , ( const void * ) &
( rtDW . cvcfermial ) , sizeof ( rtDW . cvcfermial ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 14 , ( const void * ) &
( rtDW . ocn3tuy1mq ) , sizeof ( rtDW . ocn3tuy1mq ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 15 , ( const void * ) &
( rtDW . lzrfskvb50 ) , sizeof ( rtDW . lzrfskvb50 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 16 , ( const void * ) &
( rtDW . kxzyyq15r0 ) , sizeof ( rtDW . kxzyyq15r0 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 17 , ( const void * ) &
( rtDW . jfrl3cqm1n ) , sizeof ( rtDW . jfrl3cqm1n ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 18 , ( const void * ) &
( rtDW . ayahx5voca ) , sizeof ( rtDW . ayahx5voca ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 19 , ( const void * ) &
( rtDW . l2zkdqsp2y ) , sizeof ( rtDW . l2zkdqsp2y ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 20 , ( const void * ) &
( rtDW . lxk5izw00o ) , sizeof ( rtDW . lxk5izw00o ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 21 , ( const void * ) &
( rtDW . cqp1dau03w ) , sizeof ( rtDW . cqp1dau03w ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 22 , ( const void * ) &
( rtDW . gfiovjo3e2 ) , sizeof ( rtDW . gfiovjo3e2 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 23 , ( const void * ) &
( rtDW . p2iwsajmfp ) , sizeof ( rtDW . p2iwsajmfp ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 24 , ( const void * ) &
( rtDW . b4auxd1lsk ) , sizeof ( rtDW . b4auxd1lsk ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 25 , ( const void * ) &
( rtDW . al5aajfx21 ) , sizeof ( rtDW . al5aajfx21 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 26 , ( const void * ) &
( rtDW . gt3chc0tga ) , sizeof ( rtDW . gt3chc0tga ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 27 , ( const void * ) &
( rtDW . erukb0glgz ) , sizeof ( rtDW . erukb0glgz ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 28 , ( const void * ) &
( rtDW . pdjkbbbzjq ) , sizeof ( rtDW . pdjkbbbzjq ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 29 , ( const void * ) &
( rtDW . pml0yl52te ) , sizeof ( rtDW . pml0yl52te ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 30 , ( const void * ) &
( rtDW . eswvf4pz4v ) , sizeof ( rtDW . eswvf4pz4v ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 31 , ( const void * ) &
( rtDW . phidvr4lhk ) , sizeof ( rtDW . phidvr4lhk ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 32 , ( const void * ) &
( rtDW . atdfcebxbc ) , sizeof ( rtDW . atdfcebxbc ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 33 , ( const void * ) &
( rtDW . o3sgmp4aev ) , sizeof ( rtDW . o3sgmp4aev ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 34 , ( const void * ) &
( rtDW . nld3uzo5io ) , sizeof ( rtDW . nld3uzo5io ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 35 , ( const void * ) &
( rtDW . fi4wuwmktb ) , sizeof ( rtDW . fi4wuwmktb ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 36 , ( const void * ) &
( rtDW . gm4ivysliu ) , sizeof ( rtDW . gm4ivysliu ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 37 , ( const void * ) &
( rtDW . pyurk4he1k ) , sizeof ( rtDW . pyurk4he1k ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 38 , ( const void * ) &
( rtDW . ocff1ayzzn ) , sizeof ( rtDW . ocff1ayzzn ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 39 , ( const void * ) &
( rtDW . l0rzviqodi ) , sizeof ( rtDW . l0rzviqodi ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 40 , ( const void * ) &
( rtDW . o0qik01ouq ) , sizeof ( rtDW . o0qik01ouq ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 41 , ( const void * ) &
( rtDW . jci52usrwf ) , sizeof ( rtDW . jci52usrwf ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 42 , ( const void * ) &
( rtDW . n0ifswwd21 ) , sizeof ( rtDW . n0ifswwd21 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 43 , ( const void * ) &
( rtDW . enqlcsixk2 ) , sizeof ( rtDW . enqlcsixk2 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 44 , ( const void * ) &
( rtDW . bq4gap0f1m ) , sizeof ( rtDW . bq4gap0f1m ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 45 , ( const void * ) &
( rtDW . lfuv5ipyfs ) , sizeof ( rtDW . lfuv5ipyfs ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 46 , ( const void * ) &
( rtDW . hjbvl0tg45 ) , sizeof ( rtDW . hjbvl0tg45 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 47 , ( const void * ) &
( rtDW . nyxm5sdvcd ) , sizeof ( rtDW . nyxm5sdvcd ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 48 , ( const void * ) &
( rtDW . f0lbp4tqqn ) , sizeof ( rtDW . f0lbp4tqqn ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 49 , ( const void * ) &
( rtDW . fva2rmvmh4 ) , sizeof ( rtDW . fva2rmvmh4 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 50 , ( const void * ) &
( rtDW . hdlc0qsc4w ) , sizeof ( rtDW . hdlc0qsc4w ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 51 , ( const void * ) &
( rtDW . fl4tijqsrl ) , sizeof ( rtDW . fl4tijqsrl ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 52 , ( const void * ) &
( rtDW . mxawq0evig ) , sizeof ( rtDW . mxawq0evig ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 53 , ( const void * ) &
( rtDW . e1vdezejb0 ) , sizeof ( rtDW . e1vdezejb0 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 54 , ( const void * ) &
( rtDW . nrq4usubsl ) , sizeof ( rtDW . nrq4usubsl ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 55 , ( const void * ) &
( rtDW . omuzgpsf1f ) , sizeof ( rtDW . omuzgpsf1f ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 56 , ( const void * ) &
( rtDW . hys0om0qbu ) , sizeof ( rtDW . hys0om0qbu ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 57 , ( const void * ) &
( rtDW . nr5d4vqt4t ) , sizeof ( rtDW . nr5d4vqt4t ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 58 , ( const void * ) &
( rtDW . cnk414y00k ) , sizeof ( rtDW . cnk414y00k ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 59 , ( const void * ) &
( rtDW . fnpjhtoie0 ) , sizeof ( rtDW . fnpjhtoie0 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 60 , ( const void * ) &
( rtDW . frvvvscadt ) , sizeof ( rtDW . frvvvscadt ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 61 , ( const void * ) &
( rtDW . pfwwityzhm ) , sizeof ( rtDW . pfwwityzhm ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 62 , ( const void * ) &
( rtDW . awvvdj3gzy ) , sizeof ( rtDW . awvvdj3gzy ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 63 , ( const void * ) &
( rtDW . esrssadyy0 ) , sizeof ( rtDW . esrssadyy0 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 64 , ( const void * ) &
( rtDW . loh1yczrtr ) , sizeof ( rtDW . loh1yczrtr ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 65 , ( const void * ) &
( rtDW . cayw42bvqq ) , sizeof ( rtDW . cayw42bvqq ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 66 , ( const void * ) &
( rtDW . fmhxej54hb ) , sizeof ( rtDW . fmhxej54hb ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 67 , ( const void * ) &
( rtDW . fzberuaezs ) , sizeof ( rtDW . fzberuaezs ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 68 , ( const void * ) &
( rtDW . oiurtflkiv ) , sizeof ( rtDW . oiurtflkiv ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 69 , ( const void * ) &
( rtDW . cedwdfuxlq ) , sizeof ( rtDW . cedwdfuxlq ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 70 , ( const void * ) &
( rtDW . ny5tmca5u1 ) , sizeof ( rtDW . ny5tmca5u1 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 71 , ( const void * ) &
( rtDW . k3sz0zxcz4 ) , sizeof ( rtDW . k3sz0zxcz4 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 72 , ( const void * ) &
( rtDW . hafwy3njkc ) , sizeof ( rtDW . hafwy3njkc ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 73 , ( const void * ) &
( rtDW . gqa5jm0r2v ) , sizeof ( rtDW . gqa5jm0r2v ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 74 , ( const void * ) &
( rtDW . inffcupvx2 ) , sizeof ( rtDW . inffcupvx2 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 75 , ( const void * ) &
( rtDW . p21lrpi51b ) , sizeof ( rtDW . p21lrpi51b ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 76 , ( const void * ) &
( rtDW . mpvdclcsce ) , sizeof ( rtDW . mpvdclcsce ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 77 , ( const void * ) &
( rtDW . hma0f53x5s ) , sizeof ( rtDW . hma0f53x5s ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 78 , ( const void * ) &
( rtDW . fbadxescvd ) , sizeof ( rtDW . fbadxescvd ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 79 , ( const void * ) &
( rtDW . neqcp2rk0x ) , sizeof ( rtDW . neqcp2rk0x ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 80 , ( const void * ) &
( rtDW . injrnpzipy ) , sizeof ( rtDW . injrnpzipy ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 81 , ( const void * ) &
( rtDW . cgg3v13mlz ) , sizeof ( rtDW . cgg3v13mlz ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 82 , ( const void * ) &
( rtDW . ffjft2t0pj ) , sizeof ( rtDW . ffjft2t0pj ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 83 , ( const void * ) &
( rtDW . jayew5vh20 ) , sizeof ( rtDW . jayew5vh20 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 84 , ( const void * ) &
( rtDW . gtl5stszrm ) , sizeof ( rtDW . gtl5stszrm ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 85 , ( const void * ) &
( rtDW . pacgla51lq ) , sizeof ( rtDW . pacgla51lq ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 86 , ( const void * ) &
( rtDW . jntfw1jmxj ) , sizeof ( rtDW . jntfw1jmxj ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 87 , ( const void * ) &
( rtDW . ml1vr0zmzd ) , sizeof ( rtDW . ml1vr0zmzd ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 88 , ( const void * ) &
( rtDW . ietukijfm5 ) , sizeof ( rtDW . ietukijfm5 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 89 , ( const void * ) &
( rtDW . hcvygsausk ) , sizeof ( rtDW . hcvygsausk ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 90 , ( const void * ) &
( rtDW . osj02yjrnn ) , sizeof ( rtDW . osj02yjrnn ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 91 , ( const void * ) &
( rtDW . o3dbqj4xyk ) , sizeof ( rtDW . o3dbqj4xyk ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 92 , ( const void * ) &
( rtDW . ghxlzewxqv ) , sizeof ( rtDW . ghxlzewxqv ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 93 , ( const void * ) &
( rtDW . jw4znmasof ) , sizeof ( rtDW . jw4znmasof ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 94 , ( const void * ) &
( rtDW . jsu3fijte2 ) , sizeof ( rtDW . jsu3fijte2 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 95 , ( const void * ) &
( rtDW . my5afrzgkd ) , sizeof ( rtDW . my5afrzgkd ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 96 , ( const void * ) &
( rtDW . edo3dr0fru ) , sizeof ( rtDW . edo3dr0fru ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 97 , ( const void * ) &
( rtDW . hyaxdywynl ) , sizeof ( rtDW . hyaxdywynl ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 98 , ( const void * ) &
( rtDW . on2kbwtd1i ) , sizeof ( rtDW . on2kbwtd1i ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 99 , ( const void * ) &
( rtDW . lfzkcubuyh ) , sizeof ( rtDW . lfzkcubuyh ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 100 , ( const void * )
& ( rtDW . bt2kw45n5u ) , sizeof ( rtDW . bt2kw45n5u ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 101 , ( const void * )
& ( rtDW . eqzj0rxvun ) , sizeof ( rtDW . eqzj0rxvun ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 102 , ( const void * )
& ( rtDW . ilnpea2zjg ) , sizeof ( rtDW . ilnpea2zjg ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 103 , ( const void * )
& ( rtDW . ddhgjj4slr ) , sizeof ( rtDW . ddhgjj4slr ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 104 , ( const void * )
& ( rtDW . cguk3rlz2c ) , sizeof ( rtDW . cguk3rlz2c ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 105 , ( const void * )
& ( rtDW . myfhgr2zam ) , sizeof ( rtDW . myfhgr2zam ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 106 , ( const void * )
& ( rtDW . jsu3fijte22 ) , sizeof ( rtDW . jsu3fijte22 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 107 , ( const void * )
& ( rtDW . my5afrzgkdf ) , sizeof ( rtDW . my5afrzgkdf ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 108 , ( const void * )
& ( rtDW . edo3dr0fru5 ) , sizeof ( rtDW . edo3dr0fru5 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 109 , ( const void * )
& ( rtDW . hyaxdywynlc ) , sizeof ( rtDW . hyaxdywynlc ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 110 , ( const void * )
& ( rtDW . anqq4l0npb ) , sizeof ( rtDW . anqq4l0npb ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 111 , ( const void * )
& ( rtDW . o13fmizguv ) , sizeof ( rtDW . o13fmizguv ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 112 , ( const void * )
& ( rtDW . hdglqralt5 ) , sizeof ( rtDW . hdglqralt5 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 113 , ( const void * )
& ( rtDW . ptnxk4g0lc ) , sizeof ( rtDW . ptnxk4g0lc ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 114 , ( const void * )
& ( rtDW . pjnb2ek2e3 ) , sizeof ( rtDW . pjnb2ek2e3 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 115 , ( const void * )
& ( rtDW . m0rv3vqddv ) , sizeof ( rtDW . m0rv3vqddv ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 116 , ( const void * )
& ( rtDW . o10ebbt22e ) , sizeof ( rtDW . o10ebbt22e ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 117 , ( const void * )
& ( rtDW . mam5vcqfvx ) , sizeof ( rtDW . mam5vcqfvx ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 118 , ( const void * )
& ( rtDW . jsu3fijte22m ) , sizeof ( rtDW . jsu3fijte22m ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 119 , ( const void * )
& ( rtDW . my5afrzgkdfq ) , sizeof ( rtDW . my5afrzgkdfq ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 120 , ( const void * )
& ( rtDW . edo3dr0fru5x ) , sizeof ( rtDW . edo3dr0fru5x ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 121 , ( const void * )
& ( rtDW . hyaxdywynlcl ) , sizeof ( rtDW . hyaxdywynlcl ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 122 , ( const void * )
& ( rtDW . dq0pmdxppu ) , sizeof ( rtDW . dq0pmdxppu ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 123 , ( const void * )
& ( rtDW . jpqfmeeeto ) , sizeof ( rtDW . jpqfmeeeto ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 124 , ( const void * )
& ( rtDW . p25vgyovxo ) , sizeof ( rtDW . p25vgyovxo ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 125 , ( const void * )
& ( rtDW . fgxsmumrmw ) , sizeof ( rtDW . fgxsmumrmw ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 126 , ( const void * )
& ( rtDW . p3km4baqfe ) , sizeof ( rtDW . p3km4baqfe ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 127 , ( const void * )
& ( rtDW . agchj4uiph ) , sizeof ( rtDW . agchj4uiph ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 128 , ( const void * )
& ( rtDW . fd5nlfaj2u ) , sizeof ( rtDW . fd5nlfaj2u ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 129 , ( const void * )
& ( rtDW . gvxq4lgohv ) , sizeof ( rtDW . gvxq4lgohv ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 130 , ( const void * )
& ( rtDW . ixrsi3erhf ) , sizeof ( rtDW . ixrsi3erhf ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 131 , ( const void * )
& ( rtDW . jis1uepreo ) , sizeof ( rtDW . jis1uepreo ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 132 , ( const void * )
& ( rtDW . fwkxey5epo ) , sizeof ( rtDW . fwkxey5epo ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 133 , ( const void * )
& ( rtDW . pnsuou2020 ) , sizeof ( rtDW . pnsuou2020 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 134 , ( const void * )
& ( rtDW . opg1thx2qw ) , sizeof ( rtDW . opg1thx2qw ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 135 , ( const void * )
& ( rtDW . amalc3ffil ) , sizeof ( rtDW . amalc3ffil ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 136 , ( const void * )
& ( rtDW . mwenvz0tar ) , sizeof ( rtDW . mwenvz0tar ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 137 , ( const void * )
& ( rtDW . de3otshxus ) , sizeof ( rtDW . de3otshxus ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 138 , ( const void * )
& ( rtDW . i2ctd1awel ) , sizeof ( rtDW . i2ctd1awel ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 139 , ( const void * )
& ( rtDW . ccf5juo5ya ) , sizeof ( rtDW . ccf5juo5ya ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 140 , ( const void * )
& ( rtDW . i4lkkodfyj ) , sizeof ( rtDW . i4lkkodfyj ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 141 , ( const void * )
& ( rtDW . mdvclm3wpb ) , sizeof ( rtDW . mdvclm3wpb ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 142 , ( const void * )
& ( rtDW . gai5nv42oe ) , sizeof ( rtDW . gai5nv42oe ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 143 , ( const void * )
& ( rtDW . imfxseqvvv ) , sizeof ( rtDW . imfxseqvvv ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 144 , ( const void * )
& ( rtDW . cxatkad2jz ) , sizeof ( rtDW . cxatkad2jz ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 145 , ( const void * )
& ( rtDW . ikxzuowx1v ) , sizeof ( rtDW . ikxzuowx1v ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 146 , ( const void * )
& ( rtDW . bg2vv1po0e ) , sizeof ( rtDW . bg2vv1po0e ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 147 , ( const void * )
& ( rtDW . f4tcd4udur ) , sizeof ( rtDW . f4tcd4udur ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 148 , ( const void * )
& ( rtDW . ctbynjdwij ) , sizeof ( rtDW . ctbynjdwij ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 149 , ( const void * )
& ( rtDW . anfxf0zt2u ) , sizeof ( rtDW . anfxf0zt2u ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 150 , ( const void * )
& ( rtDW . afo0nwhxua ) , sizeof ( rtDW . afo0nwhxua ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 151 , ( const void * )
& ( rtDW . jdtstycpmg ) , sizeof ( rtDW . jdtstycpmg ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 152 , ( const void * )
& ( rtDW . g2ry4vjsj1 ) , sizeof ( rtDW . g2ry4vjsj1 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 153 , ( const void * )
& ( rtDW . iehvrkddj2 ) , sizeof ( rtDW . iehvrkddj2 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 154 , ( const void * )
& ( rtDW . nbavx35izv ) , sizeof ( rtDW . nbavx35izv ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 155 , ( const void * )
& ( rtDW . cl1vsftpzn ) , sizeof ( rtDW . cl1vsftpzn ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 156 , ( const void * )
& ( rtDW . lhojsnn24m ) , sizeof ( rtDW . lhojsnn24m ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 157 , ( const void * )
& ( rtDW . d42pvxfz0g ) , sizeof ( rtDW . d42pvxfz0g ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 158 , ( const void * )
& ( rtDW . kovzbujdnb ) , sizeof ( rtDW . kovzbujdnb ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 159 , ( const void * )
& ( rtDW . dttn4xmcnk ) , sizeof ( rtDW . dttn4xmcnk ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 160 , ( const void * )
& ( rtDW . n1ap5w5rdi ) , sizeof ( rtDW . n1ap5w5rdi ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 161 , ( const void * )
& ( rtDW . ndb122ek3u ) , sizeof ( rtDW . ndb122ek3u ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 162 , ( const void * )
& ( rtDW . hoesofthyy ) , sizeof ( rtDW . hoesofthyy ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 163 , ( const void * )
& ( rtDW . ifur0qjdev ) , sizeof ( rtDW . ifur0qjdev ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 164 , ( const void * )
& ( rtDW . h2z1m5wxiy ) , sizeof ( rtDW . h2z1m5wxiy ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 165 , ( const void * )
& ( rtDW . dviol1u0jv ) , sizeof ( rtDW . dviol1u0jv ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 166 , ( const void * )
& ( rtDW . df5ibuzfvl ) , sizeof ( rtDW . df5ibuzfvl ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 167 , ( const void * )
& ( rtDW . ikv4gqtanm ) , sizeof ( rtDW . ikv4gqtanm ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 168 , ( const void * )
& ( rtDW . hru10ym4o1 ) , sizeof ( rtDW . hru10ym4o1 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 169 , ( const void * )
& ( rtDW . erp5nno2ec ) , sizeof ( rtDW . erp5nno2ec ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 170 , ( const void * )
& ( rtDW . ima1cclrzn ) , sizeof ( rtDW . ima1cclrzn ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 171 , ( const void * )
& ( rtDW . hm24hbgcg1 ) , sizeof ( rtDW . hm24hbgcg1 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 172 , ( const void * )
& ( rtDW . ob20xueupt ) , sizeof ( rtDW . ob20xueupt ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 173 , ( const void * )
& ( rtDW . emh5kwkq0f ) , sizeof ( rtDW . emh5kwkq0f ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 174 , ( const void * )
& ( rtDW . f3zvxiekpj ) , sizeof ( rtDW . f3zvxiekpj ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 175 , ( const void * )
& ( rtDW . dspkd5mdvs ) , sizeof ( rtDW . dspkd5mdvs ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 176 , ( const void * )
& ( rtDW . gmymeboquk ) , sizeof ( rtDW . gmymeboquk ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 177 , ( const void * )
& ( rtDW . bs1nmm0jpl ) , sizeof ( rtDW . bs1nmm0jpl ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 178 , ( const void * )
& ( rtDW . bx5vsdt4mt ) , sizeof ( rtDW . bx5vsdt4mt ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 179 , ( const void * )
& ( rtDW . ciaqlqmyyx ) , sizeof ( rtDW . ciaqlqmyyx ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 180 , ( const void * )
& ( rtDW . e1kih03oaj ) , sizeof ( rtDW . e1kih03oaj ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 181 , ( const void * )
& ( rtDW . m5gzgpvijm ) , sizeof ( rtDW . m5gzgpvijm ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 182 , ( const void * )
& ( rtDW . o3kxgyy1fj ) , sizeof ( rtDW . o3kxgyy1fj ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 183 , ( const void * )
& ( rtDW . nkf0blmwkl ) , sizeof ( rtDW . nkf0blmwkl ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 184 , ( const void * )
& ( rtDW . h5lg5oz5ks ) , sizeof ( rtDW . h5lg5oz5ks ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 185 , ( const void * )
& ( rtDW . hggmceleiv ) , sizeof ( rtDW . hggmceleiv ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 186 , ( const void * )
& ( rtDW . pdhtdmqeof ) , sizeof ( rtDW . pdhtdmqeof ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 187 , ( const void * )
& ( rtDW . i3xwoxj5zy ) , sizeof ( rtDW . i3xwoxj5zy ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 188 , ( const void * )
& ( rtDW . lth0p1kskk ) , sizeof ( rtDW . lth0p1kskk ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 189 , ( const void * )
& ( rtDW . ko0pv0nfnn ) , sizeof ( rtDW . ko0pv0nfnn ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 190 , ( const void * )
& ( rtDW . kr1btzpdxw ) , sizeof ( rtDW . kr1btzpdxw ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 191 , ( const void * )
& ( rtDW . axidhoghf0 ) , sizeof ( rtDW . axidhoghf0 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 192 , ( const void * )
& ( rtDW . pqgou55kzx ) , sizeof ( rtDW . pqgou55kzx ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 193 , ( const void * )
& ( rtDW . fuh3bn4ezo ) , sizeof ( rtDW . fuh3bn4ezo ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 194 , ( const void * )
& ( rtDW . kzefheif0g ) , sizeof ( rtDW . kzefheif0g ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 195 , ( const void * )
& ( rtDW . aa2p00mqis ) , sizeof ( rtDW . aa2p00mqis ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 196 , ( const void * )
& ( rtDW . pasm0mbp1y ) , sizeof ( rtDW . pasm0mbp1y ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 197 , ( const void * )
& ( rtDW . jqvl3ulori ) , sizeof ( rtDW . jqvl3ulori ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 198 , ( const void * )
& ( rtDW . jez5q1v2di ) , sizeof ( rtDW . jez5q1v2di ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 199 , ( const void * )
& ( rtDW . lr1nlrmqch ) , sizeof ( rtDW . lr1nlrmqch ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 200 , ( const void * )
& ( rtDW . a44d5qyg12 ) , sizeof ( rtDW . a44d5qyg12 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 201 , ( const void * )
& ( rtDW . bwkcfpuwid ) , sizeof ( rtDW . bwkcfpuwid ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 202 , ( const void * )
& ( rtDW . cno1ak0c3c ) , sizeof ( rtDW . cno1ak0c3c ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 203 , ( const void * )
& ( rtDW . nxk0ojgi44 ) , sizeof ( rtDW . nxk0ojgi44 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 204 , ( const void * )
& ( rtDW . bubytbfjvq ) , sizeof ( rtDW . bubytbfjvq ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 205 , ( const void * )
& ( rtDW . glikpzp24u ) , sizeof ( rtDW . glikpzp24u ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 206 , ( const void * )
& ( rtDW . hskq4vr1qs ) , sizeof ( rtDW . hskq4vr1qs ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 207 , ( const void * )
& ( rtDW . hljbnnt3zw ) , sizeof ( rtDW . hljbnnt3zw ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 208 , ( const void * )
& ( rtDW . d2cg15qgjf ) , sizeof ( rtDW . d2cg15qgjf ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 209 , ( const void * )
& ( rtDW . ir1mqsar5f ) , sizeof ( rtDW . ir1mqsar5f ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 210 , ( const void * )
& ( rtDW . kebzxgfy5a ) , sizeof ( rtDW . kebzxgfy5a ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 211 , ( const void * )
& ( rtDW . pmncprwmz4 ) , sizeof ( rtDW . pmncprwmz4 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 212 , ( const void * )
& ( rtDW . g05suawwrk ) , sizeof ( rtDW . g05suawwrk ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 213 , ( const void * )
& ( rtDW . ore24n4522 ) , sizeof ( rtDW . ore24n4522 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 214 , ( const void * )
& ( rtDW . mz1lyyodga ) , sizeof ( rtDW . mz1lyyodga ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 215 , ( const void * )
& ( rtDW . i22hackosr ) , sizeof ( rtDW . i22hackosr ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 216 , ( const void * )
& ( rtDW . hrf0r3epza ) , sizeof ( rtDW . hrf0r3epza ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 217 , ( const void * )
& ( rtDW . l4gldy0ied ) , sizeof ( rtDW . l4gldy0ied ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 218 , ( const void * )
& ( rtDW . jcgd4tqv41 ) , sizeof ( rtDW . jcgd4tqv41 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 219 , ( const void * )
& ( rtDW . oyxqmd0f4v ) , sizeof ( rtDW . oyxqmd0f4v ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 220 , ( const void * )
& ( rtDW . cdd1gh0rmi ) , sizeof ( rtDW . cdd1gh0rmi ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 221 , ( const void * )
& ( rtDW . ayjsmpf3pd ) , sizeof ( rtDW . ayjsmpf3pd ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 222 , ( const void * )
& ( rtDW . etncgat1qk ) , sizeof ( rtDW . etncgat1qk ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 223 , ( const void * )
& ( rtDW . j0pfyx5sl0 ) , sizeof ( rtDW . j0pfyx5sl0 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 224 , ( const void * )
& ( rtDW . otdqomronl ) , sizeof ( rtDW . otdqomronl ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 225 , ( const void * )
& ( rtDW . nz3xkbxksp ) , sizeof ( rtDW . nz3xkbxksp ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 226 , ( const void * )
& ( rtDW . cmxd2uv3ip ) , sizeof ( rtDW . cmxd2uv3ip ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 227 , ( const void * )
& ( rtDW . hbomutgs5x ) , sizeof ( rtDW . hbomutgs5x ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 228 , ( const void * )
& ( rtDW . kkklfomjr5 ) , sizeof ( rtDW . kkklfomjr5 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 229 , ( const void * )
& ( rtDW . dmmot30jq4 ) , sizeof ( rtDW . dmmot30jq4 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 230 , ( const void * )
& ( rtDW . dzr2rntvvo ) , sizeof ( rtDW . dzr2rntvvo ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 231 , ( const void * )
& ( rtDW . aw0bxhrzal ) , sizeof ( rtDW . aw0bxhrzal ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 232 , ( const void * )
& ( rtDW . estezyunas ) , sizeof ( rtDW . estezyunas ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 233 , ( const void * )
& ( rtDW . olzifhaukx ) , sizeof ( rtDW . olzifhaukx ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 234 , ( const void * )
& ( rtDW . miwm3apiea ) , sizeof ( rtDW . miwm3apiea ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 235 , ( const void * )
& ( rtDW . otborblus0 ) , sizeof ( rtDW . otborblus0 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 236 , ( const void * )
& ( rtDW . jcievkrvvv ) , sizeof ( rtDW . jcievkrvvv ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 237 , ( const void * )
& ( rtDW . ovlbtlz2z5 ) , sizeof ( rtDW . ovlbtlz2z5 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 238 , ( const void * )
& ( rtDW . mx1dy0gdum ) , sizeof ( rtDW . mx1dy0gdum ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 239 , ( const void * )
& ( rtDW . iygynuhhiw ) , sizeof ( rtDW . iygynuhhiw ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 240 , ( const void * )
& ( rtDW . oamcwpfckc ) , sizeof ( rtDW . oamcwpfckc ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 241 , ( const void * )
& ( rtDW . az4aq4f2to ) , sizeof ( rtDW . az4aq4f2to ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 242 , ( const void * )
& ( rtDW . hv1tfq2dkg ) , sizeof ( rtDW . hv1tfq2dkg ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 243 , ( const void * )
& ( rtDW . ckuddxo2v5 ) , sizeof ( rtDW . ckuddxo2v5 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 244 , ( const void * )
& ( rtDW . hoqlzb3yrr ) , sizeof ( rtDW . hoqlzb3yrr ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 245 , ( const void * )
& ( rtDW . d2yav1jvrg ) , sizeof ( rtDW . d2yav1jvrg ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 246 , ( const void * )
& ( rtDW . pdli3lyef1 ) , sizeof ( rtDW . pdli3lyef1 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 247 , ( const void * )
& ( rtDW . bqjtw0doyx ) , sizeof ( rtDW . bqjtw0doyx ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 248 , ( const void * )
& ( rtDW . cc421u2f3f ) , sizeof ( rtDW . cc421u2f3f ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 249 , ( const void * )
& ( rtDW . pdjafikrtl ) , sizeof ( rtDW . pdjafikrtl ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 250 , ( const void * )
& ( rtDW . pojlxrwx0d ) , sizeof ( rtDW . pojlxrwx0d ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 251 , ( const void * )
& ( rtDW . m4fnnxykzj ) , sizeof ( rtDW . m4fnnxykzj ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 252 , ( const void * )
& ( rtDW . k40ux0ctpf ) , sizeof ( rtDW . k40ux0ctpf ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 253 , ( const void * )
& ( rtDW . kvknfbkwvk ) , sizeof ( rtDW . kvknfbkwvk ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 254 , ( const void * )
& ( rtDW . by04uer2xp ) , sizeof ( rtDW . by04uer2xp ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 255 , ( const void * )
& ( rtDW . n1vlvivlrx ) , sizeof ( rtDW . n1vlvivlrx ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 256 , ( const void * )
& ( rtDW . ib3g0mc4j4 ) , sizeof ( rtDW . ib3g0mc4j4 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 257 , ( const void * )
& ( rtDW . c3coe5r3z1 ) , sizeof ( rtDW . c3coe5r3z1 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 258 , ( const void * )
& ( rtDW . gopfnpfdpo ) , sizeof ( rtDW . gopfnpfdpo ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 259 , ( const void * )
& ( rtDW . fhefxq1ozn ) , sizeof ( rtDW . fhefxq1ozn ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 260 , ( const void * )
& ( rtDW . bfidcyeanb ) , sizeof ( rtDW . bfidcyeanb ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 261 , ( const void * )
& ( rtDW . fi31qowovj ) , sizeof ( rtDW . fi31qowovj ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 262 , ( const void * )
& ( rtDW . pbpmgsmorm ) , sizeof ( rtDW . pbpmgsmorm ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 263 , ( const void * )
& ( rtDW . axle03m4av ) , sizeof ( rtDW . axle03m4av ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 264 , ( const void * )
& ( rtDW . evcuev5sfd ) , sizeof ( rtDW . evcuev5sfd ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 265 , ( const void * )
& ( rtDW . cblzsrog5u ) , sizeof ( rtDW . cblzsrog5u ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 266 , ( const void * )
& ( rtDW . nqfbacpvcp ) , sizeof ( rtDW . nqfbacpvcp ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 267 , ( const void * )
& ( rtDW . fdktvwm3kd ) , sizeof ( rtDW . fdktvwm3kd ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 268 , ( const void * )
& ( rtDW . bjkklesnma ) , sizeof ( rtDW . bjkklesnma ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 269 , ( const void * )
& ( rtDW . nsaa1gti0b ) , sizeof ( rtDW . nsaa1gti0b ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 270 , ( const void * )
& ( rtDW . ghx0ts2zzs ) , sizeof ( rtDW . ghx0ts2zzs ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 271 , ( const void * )
& ( rtDW . lafrvsvgf0 ) , sizeof ( rtDW . lafrvsvgf0 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 272 , ( const void * )
& ( rtDW . og3lno4rre ) , sizeof ( rtDW . og3lno4rre ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 273 , ( const void * )
& ( rtDW . ld5g5vrgmj ) , sizeof ( rtDW . ld5g5vrgmj ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 274 , ( const void * )
& ( rtDW . niztd2zg4p ) , sizeof ( rtDW . niztd2zg4p ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 275 , ( const void * )
& ( rtDW . faadh0wdog ) , sizeof ( rtDW . faadh0wdog ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 276 , ( const void * )
& ( rtDW . jgx0xkzgjo ) , sizeof ( rtDW . jgx0xkzgjo ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 277 , ( const void * )
& ( rtDW . gpf5tclqta ) , sizeof ( rtDW . gpf5tclqta ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 278 , ( const void * )
& ( rtDW . mvfamndgj4 ) , sizeof ( rtDW . mvfamndgj4 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 279 , ( const void * )
& ( rtDW . kcaj1yegtz ) , sizeof ( rtDW . kcaj1yegtz ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 280 , ( const void * )
& ( rtDW . guhdmzy0n4 ) , sizeof ( rtDW . guhdmzy0n4 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 281 , ( const void * )
& ( rtDW . bi1fzovgs2 ) , sizeof ( rtDW . bi1fzovgs2 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 282 , ( const void * )
& ( rtDW . llxyyz4q5x ) , sizeof ( rtDW . llxyyz4q5x ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 283 , ( const void * )
& ( rtDW . bjzrd2jgh1 ) , sizeof ( rtDW . bjzrd2jgh1 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 284 , ( const void * )
& ( rtDW . npqdzcpz4k ) , sizeof ( rtDW . npqdzcpz4k ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 285 , ( const void * )
& ( rtDW . k44l31otpd ) , sizeof ( rtDW . k44l31otpd ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 286 , ( const void * )
& ( rtDW . ocwqpyvhqo ) , sizeof ( rtDW . ocwqpyvhqo ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 287 , ( const void * )
& ( rtDW . bb0v2ld5vf ) , sizeof ( rtDW . bb0v2ld5vf ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 288 , ( const void * )
& ( rtDW . htr1ntw0w0 ) , sizeof ( rtDW . htr1ntw0w0 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 289 , ( const void * )
& ( rtDW . f1sl003e30 ) , sizeof ( rtDW . f1sl003e30 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 290 , ( const void * )
& ( rtDW . lbwbhxgeac ) , sizeof ( rtDW . lbwbhxgeac ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 291 , ( const void * )
& ( rtDW . lgjrfdubva ) , sizeof ( rtDW . lgjrfdubva ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 292 , ( const void * )
& ( rtDW . il1i11vhya ) , sizeof ( rtDW . il1i11vhya ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 293 , ( const void * )
& ( rtDW . fmvtpht2wc ) , sizeof ( rtDW . fmvtpht2wc ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 294 , ( const void * )
& ( rtDW . jlwpaqqpol ) , sizeof ( rtDW . jlwpaqqpol ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 295 , ( const void * )
& ( rtDW . o2nyvbjxnw ) , sizeof ( rtDW . o2nyvbjxnw ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 296 , ( const void * )
& ( rtDW . mofgw1cji2 ) , sizeof ( rtDW . mofgw1cji2 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 297 , ( const void * )
& ( rtDW . hbtp4braxp ) , sizeof ( rtDW . hbtp4braxp ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 298 , ( const void * )
& ( rtDW . ifa1aifv0v ) , sizeof ( rtDW . ifa1aifv0v ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 299 , ( const void * )
& ( rtDW . azvnw5pvht ) , sizeof ( rtDW . azvnw5pvht ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 300 , ( const void * )
& ( rtDW . avqcisj0g1 ) , sizeof ( rtDW . avqcisj0g1 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 301 , ( const void * )
& ( rtDW . hyopdoshjp ) , sizeof ( rtDW . hyopdoshjp ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 302 , ( const void * )
& ( rtDW . fqvcumyba1 ) , sizeof ( rtDW . fqvcumyba1 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 303 , ( const void * )
& ( rtDW . njfpshnpni ) , sizeof ( rtDW . njfpshnpni ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 304 , ( const void * )
& ( rtDW . k0efqstpz0 ) , sizeof ( rtDW . k0efqstpz0 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 305 , ( const void * )
& ( rtDW . jitieevvno ) , sizeof ( rtDW . jitieevvno ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 306 , ( const void * )
& ( rtDW . ip0d0t1043 ) , sizeof ( rtDW . ip0d0t1043 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 307 , ( const void * )
& ( rtDW . i1c4xekdhn ) , sizeof ( rtDW . i1c4xekdhn ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 308 , ( const void * )
& ( rtDW . bfyezaoly2 ) , sizeof ( rtDW . bfyezaoly2 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 309 , ( const void * )
& ( rtDW . idcpojjs11 ) , sizeof ( rtDW . idcpojjs11 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 310 , ( const void * )
& ( rtDW . fe3ipxqiw5 ) , sizeof ( rtDW . fe3ipxqiw5 ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 311 , ( const void * )
& ( rtDW . hw1g0wvqpq ) , sizeof ( rtDW . hw1g0wvqpq ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 312 , ( const void * )
& ( rtDW . iw5qsles1z ) , sizeof ( rtDW . iw5qsles1z ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 313 , ( const void * )
& ( rtDW . gomqyfi1fi ) , sizeof ( rtDW . gomqyfi1fi ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 314 , ( const void * )
& ( rtDW . dczrefoerg ) , sizeof ( rtDW . dczrefoerg ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 315 , ( const void * )
& ( rtDW . py4iuvrbea ) , sizeof ( rtDW . py4iuvrbea ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 316 , ( const void * )
& ( rtDW . a43rt5p5qk ) , sizeof ( rtDW . a43rt5p5qk ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 317 , ( const void * )
& ( rtDW . e5cexk5tsa ) , sizeof ( rtDW . e5cexk5tsa ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 318 , ( const void * )
& ( rtDW . d2ne5d41vh ) , sizeof ( rtDW . d2ne5d41vh ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 319 , ( const void * )
& ( rtDW . gdbbfmmgdg ) , sizeof ( rtDW . gdbbfmmgdg ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 320 , ( const void * )
& ( rtDW . jd2ppumcjt ) , sizeof ( rtDW . jd2ppumcjt ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 321 , ( const void * )
& ( rtDW . cx41wglw3j . bineo4prgi ) , sizeof ( rtDW . cx41wglw3j .
bineo4prgi ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 322 ,
( const void * ) & ( rtDW . cx41wglw3j . bvutux0ucw ) , sizeof ( rtDW .
cx41wglw3j . bvutux0ucw ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData
, 0 , 323 , ( const void * ) & ( rtDW . jjob4ur221 . bineo4prgi ) , sizeof (
rtDW . jjob4ur221 . bineo4prgi ) ) ; mr_uz_drive_model_cacheDataAsMxArray (
rtdwData , 0 , 324 , ( const void * ) & ( rtDW . jjob4ur221 . bvutux0ucw ) ,
sizeof ( rtDW . jjob4ur221 . bvutux0ucw ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 325 , ( const void * )
& ( rtDW . jogryxdnkz . bineo4prgi ) , sizeof ( rtDW . jogryxdnkz .
bineo4prgi ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 326 ,
( const void * ) & ( rtDW . jogryxdnkz . bvutux0ucw ) , sizeof ( rtDW .
jogryxdnkz . bvutux0ucw ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData
, 0 , 327 , ( const void * ) & ( rtDW . n4cqr1dkmr . bineo4prgi ) , sizeof (
rtDW . n4cqr1dkmr . bineo4prgi ) ) ; mr_uz_drive_model_cacheDataAsMxArray (
rtdwData , 0 , 328 , ( const void * ) & ( rtDW . n4cqr1dkmr . bvutux0ucw ) ,
sizeof ( rtDW . n4cqr1dkmr . bvutux0ucw ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 329 , ( const void * )
& ( rtDW . a13lr3lsi3 . bineo4prgi ) , sizeof ( rtDW . a13lr3lsi3 .
bineo4prgi ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 330 ,
( const void * ) & ( rtDW . a13lr3lsi3 . bvutux0ucw ) , sizeof ( rtDW .
a13lr3lsi3 . bvutux0ucw ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData
, 0 , 331 , ( const void * ) & ( rtDW . jjajpmoyel . bineo4prgi ) , sizeof (
rtDW . jjajpmoyel . bineo4prgi ) ) ; mr_uz_drive_model_cacheDataAsMxArray (
rtdwData , 0 , 332 , ( const void * ) & ( rtDW . jjajpmoyel . bvutux0ucw ) ,
sizeof ( rtDW . jjajpmoyel . bvutux0ucw ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 333 , ( const void * )
& ( rtDW . ndmeqad3sm . bineo4prgi ) , sizeof ( rtDW . ndmeqad3sm .
bineo4prgi ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 334 ,
( const void * ) & ( rtDW . ndmeqad3sm . bvutux0ucw ) , sizeof ( rtDW .
ndmeqad3sm . bvutux0ucw ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData
, 0 , 335 , ( const void * ) & ( rtDW . o0tbmhvpds . bineo4prgi ) , sizeof (
rtDW . o0tbmhvpds . bineo4prgi ) ) ; mr_uz_drive_model_cacheDataAsMxArray (
rtdwData , 0 , 336 , ( const void * ) & ( rtDW . o0tbmhvpds . bvutux0ucw ) ,
sizeof ( rtDW . o0tbmhvpds . bvutux0ucw ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 337 , ( const void * )
& ( rtDW . f5mkygzljka . bineo4prgi ) , sizeof ( rtDW . f5mkygzljka .
bineo4prgi ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 338 ,
( const void * ) & ( rtDW . f5mkygzljka . bvutux0ucw ) , sizeof ( rtDW .
f5mkygzljka . bvutux0ucw ) ) ; mr_uz_drive_model_cacheDataAsMxArray (
rtdwData , 0 , 339 , ( const void * ) & ( rtDW . biyhxca30f . ftf50xwldj ) ,
sizeof ( rtDW . biyhxca30f . ftf50xwldj ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 340 , ( const void * )
& ( rtDW . biyhxca30f . ic4jzsnsgd ) , sizeof ( rtDW . biyhxca30f .
ic4jzsnsgd ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 341 ,
( const void * ) & ( rtDW . biyhxca30f . j5itaoriq1 ) , sizeof ( rtDW .
biyhxca30f . j5itaoriq1 ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData
, 0 , 342 , ( const void * ) & ( rtDW . biyhxca30f . bjona3wx3v ) , sizeof (
rtDW . biyhxca30f . bjona3wx3v ) ) ; mr_uz_drive_model_cacheDataAsMxArray (
rtdwData , 0 , 343 , ( const void * ) & ( rtDW . biyhxca30f . bldvjsjmit ) ,
sizeof ( rtDW . biyhxca30f . bldvjsjmit ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 344 , ( const void * )
& ( rtDW . biyhxca30f . opg33homib ) , sizeof ( rtDW . biyhxca30f .
opg33homib ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 345 ,
( const void * ) & ( rtDW . biyhxca30f . n4jsnmm3dp ) , sizeof ( rtDW .
biyhxca30f . n4jsnmm3dp ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData
, 0 , 346 , ( const void * ) & ( rtDW . biyhxca30f . bnbpcxxvih ) , sizeof (
rtDW . biyhxca30f . bnbpcxxvih ) ) ; mr_uz_drive_model_cacheDataAsMxArray (
rtdwData , 0 , 347 , ( const void * ) & ( rtDW . biyhxca30f . e4ertwjipw ) ,
sizeof ( rtDW . biyhxca30f . e4ertwjipw ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 348 , ( const void * )
& ( rtDW . msqwmshj2n . ltyokv5jui ) , sizeof ( rtDW . msqwmshj2n .
ltyokv5jui ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 349 ,
( const void * ) & ( rtDW . msqwmshj2n . dmqhv1kuog ) , sizeof ( rtDW .
msqwmshj2n . dmqhv1kuog ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData
, 0 , 350 , ( const void * ) & ( rtDW . msqwmshj2n . grzcmycdpb ) , sizeof (
rtDW . msqwmshj2n . grzcmycdpb ) ) ; mr_uz_drive_model_cacheDataAsMxArray (
rtdwData , 0 , 351 , ( const void * ) & ( rtDW . msqwmshj2n . hlqhpqgl5d ) ,
sizeof ( rtDW . msqwmshj2n . hlqhpqgl5d ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 352 , ( const void * )
& ( rtDW . msqwmshj2n . dqmv313jji ) , sizeof ( rtDW . msqwmshj2n .
dqmv313jji ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 353 ,
( const void * ) & ( rtDW . msqwmshj2n . jaldgiolnb ) , sizeof ( rtDW .
msqwmshj2n . jaldgiolnb ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData
, 0 , 354 , ( const void * ) & ( rtDW . mzoe5aiivc . ftf50xwldj ) , sizeof (
rtDW . mzoe5aiivc . ftf50xwldj ) ) ; mr_uz_drive_model_cacheDataAsMxArray (
rtdwData , 0 , 355 , ( const void * ) & ( rtDW . mzoe5aiivc . ic4jzsnsgd ) ,
sizeof ( rtDW . mzoe5aiivc . ic4jzsnsgd ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 356 , ( const void * )
& ( rtDW . mzoe5aiivc . j5itaoriq1 ) , sizeof ( rtDW . mzoe5aiivc .
j5itaoriq1 ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 357 ,
( const void * ) & ( rtDW . mzoe5aiivc . bjona3wx3v ) , sizeof ( rtDW .
mzoe5aiivc . bjona3wx3v ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData
, 0 , 358 , ( const void * ) & ( rtDW . mzoe5aiivc . bldvjsjmit ) , sizeof (
rtDW . mzoe5aiivc . bldvjsjmit ) ) ; mr_uz_drive_model_cacheDataAsMxArray (
rtdwData , 0 , 359 , ( const void * ) & ( rtDW . mzoe5aiivc . opg33homib ) ,
sizeof ( rtDW . mzoe5aiivc . opg33homib ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 360 , ( const void * )
& ( rtDW . mzoe5aiivc . n4jsnmm3dp ) , sizeof ( rtDW . mzoe5aiivc .
n4jsnmm3dp ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 361 ,
( const void * ) & ( rtDW . mzoe5aiivc . bnbpcxxvih ) , sizeof ( rtDW .
mzoe5aiivc . bnbpcxxvih ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData
, 0 , 362 , ( const void * ) & ( rtDW . mzoe5aiivc . e4ertwjipw ) , sizeof (
rtDW . mzoe5aiivc . e4ertwjipw ) ) ; mr_uz_drive_model_cacheDataAsMxArray (
rtdwData , 0 , 363 , ( const void * ) & ( rtDW . cstc0v1lpw . ltyokv5jui ) ,
sizeof ( rtDW . cstc0v1lpw . ltyokv5jui ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 364 , ( const void * )
& ( rtDW . cstc0v1lpw . dmqhv1kuog ) , sizeof ( rtDW . cstc0v1lpw .
dmqhv1kuog ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 365 ,
( const void * ) & ( rtDW . cstc0v1lpw . grzcmycdpb ) , sizeof ( rtDW .
cstc0v1lpw . grzcmycdpb ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData
, 0 , 366 , ( const void * ) & ( rtDW . cstc0v1lpw . hlqhpqgl5d ) , sizeof (
rtDW . cstc0v1lpw . hlqhpqgl5d ) ) ; mr_uz_drive_model_cacheDataAsMxArray (
rtdwData , 0 , 367 , ( const void * ) & ( rtDW . cstc0v1lpw . dqmv313jji ) ,
sizeof ( rtDW . cstc0v1lpw . dqmv313jji ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 368 , ( const void * )
& ( rtDW . cstc0v1lpw . jaldgiolnb ) , sizeof ( rtDW . cstc0v1lpw .
jaldgiolnb ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 369 ,
( const void * ) & ( rtDW . azshdeeeiw3 . ftf50xwldj ) , sizeof ( rtDW .
azshdeeeiw3 . ftf50xwldj ) ) ; mr_uz_drive_model_cacheDataAsMxArray (
rtdwData , 0 , 370 , ( const void * ) & ( rtDW . azshdeeeiw3 . ic4jzsnsgd ) ,
sizeof ( rtDW . azshdeeeiw3 . ic4jzsnsgd ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 371 , ( const void * )
& ( rtDW . azshdeeeiw3 . j5itaoriq1 ) , sizeof ( rtDW . azshdeeeiw3 .
j5itaoriq1 ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 372 ,
( const void * ) & ( rtDW . azshdeeeiw3 . bjona3wx3v ) , sizeof ( rtDW .
azshdeeeiw3 . bjona3wx3v ) ) ; mr_uz_drive_model_cacheDataAsMxArray (
rtdwData , 0 , 373 , ( const void * ) & ( rtDW . azshdeeeiw3 . bldvjsjmit ) ,
sizeof ( rtDW . azshdeeeiw3 . bldvjsjmit ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 374 , ( const void * )
& ( rtDW . azshdeeeiw3 . opg33homib ) , sizeof ( rtDW . azshdeeeiw3 .
opg33homib ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 375 ,
( const void * ) & ( rtDW . azshdeeeiw3 . n4jsnmm3dp ) , sizeof ( rtDW .
azshdeeeiw3 . n4jsnmm3dp ) ) ; mr_uz_drive_model_cacheDataAsMxArray (
rtdwData , 0 , 376 , ( const void * ) & ( rtDW . azshdeeeiw3 . bnbpcxxvih ) ,
sizeof ( rtDW . azshdeeeiw3 . bnbpcxxvih ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 377 , ( const void * )
& ( rtDW . azshdeeeiw3 . e4ertwjipw ) , sizeof ( rtDW . azshdeeeiw3 .
e4ertwjipw ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 378 ,
( const void * ) & ( rtDW . cqjwvwhkzvh . ltyokv5jui ) , sizeof ( rtDW .
cqjwvwhkzvh . ltyokv5jui ) ) ; mr_uz_drive_model_cacheDataAsMxArray (
rtdwData , 0 , 379 , ( const void * ) & ( rtDW . cqjwvwhkzvh . dmqhv1kuog ) ,
sizeof ( rtDW . cqjwvwhkzvh . dmqhv1kuog ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 380 , ( const void * )
& ( rtDW . cqjwvwhkzvh . grzcmycdpb ) , sizeof ( rtDW . cqjwvwhkzvh .
grzcmycdpb ) ) ; mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 381 ,
( const void * ) & ( rtDW . cqjwvwhkzvh . hlqhpqgl5d ) , sizeof ( rtDW .
cqjwvwhkzvh . hlqhpqgl5d ) ) ; mr_uz_drive_model_cacheDataAsMxArray (
rtdwData , 0 , 382 , ( const void * ) & ( rtDW . cqjwvwhkzvh . dqmv313jji ) ,
sizeof ( rtDW . cqjwvwhkzvh . dqmv313jji ) ) ;
mr_uz_drive_model_cacheDataAsMxArray ( rtdwData , 0 , 383 , ( const void * )
& ( rtDW . cqjwvwhkzvh . jaldgiolnb ) , sizeof ( rtDW . cqjwvwhkzvh .
jaldgiolnb ) ) ; mxSetFieldByNumber ( ssDW , 0 , 1 , rtdwData ) ; }
mr_uz_drive_model_cacheDataAsMxArray ( ssDW , 0 , 2 , ( const void * ) & (
rtPrevZCX ) , sizeof ( rtPrevZCX ) ) ; return ssDW ; } void
mr_uz_drive_model_SetDWork ( const mxArray * ssDW ) { ( void ) ssDW ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtB ) , ssDW , 0 ,
0 , sizeof ( rtB ) ) ; { const mxArray * rtdwData = mxGetFieldByNumber ( ssDW
, 0 , 1 ) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW .
ituktxufmb ) , rtdwData , 0 , 0 , sizeof ( rtDW . ituktxufmb ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . epsbkv53pu )
, rtdwData , 0 , 1 , sizeof ( rtDW . epsbkv53pu ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cmh2vel5ym )
, rtdwData , 0 , 2 , sizeof ( rtDW . cmh2vel5ym ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . miazophk3q )
, rtdwData , 0 , 3 , sizeof ( rtDW . miazophk3q ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cnrqogla5d )
, rtdwData , 0 , 4 , sizeof ( rtDW . cnrqogla5d ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . aanjcgvfa0 )
, rtdwData , 0 , 5 , sizeof ( rtDW . aanjcgvfa0 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . aoxcwu3qll )
, rtdwData , 0 , 6 , sizeof ( rtDW . aoxcwu3qll ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . gnh32qpzkl )
, rtdwData , 0 , 7 , sizeof ( rtDW . gnh32qpzkl ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ihfcziqcgk )
, rtdwData , 0 , 8 , sizeof ( rtDW . ihfcziqcgk ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . eahq4k0qba )
, rtdwData , 0 , 9 , sizeof ( rtDW . eahq4k0qba ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . oo31woulsl )
, rtdwData , 0 , 10 , sizeof ( rtDW . oo31woulsl ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . blhgrykwvp )
, rtdwData , 0 , 11 , sizeof ( rtDW . blhgrykwvp ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . osqohvejno )
, rtdwData , 0 , 12 , sizeof ( rtDW . osqohvejno ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cvcfermial )
, rtdwData , 0 , 13 , sizeof ( rtDW . cvcfermial ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ocn3tuy1mq )
, rtdwData , 0 , 14 , sizeof ( rtDW . ocn3tuy1mq ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . lzrfskvb50 )
, rtdwData , 0 , 15 , sizeof ( rtDW . lzrfskvb50 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . kxzyyq15r0 )
, rtdwData , 0 , 16 , sizeof ( rtDW . kxzyyq15r0 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jfrl3cqm1n )
, rtdwData , 0 , 17 , sizeof ( rtDW . jfrl3cqm1n ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ayahx5voca )
, rtdwData , 0 , 18 , sizeof ( rtDW . ayahx5voca ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . l2zkdqsp2y )
, rtdwData , 0 , 19 , sizeof ( rtDW . l2zkdqsp2y ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . lxk5izw00o )
, rtdwData , 0 , 20 , sizeof ( rtDW . lxk5izw00o ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cqp1dau03w )
, rtdwData , 0 , 21 , sizeof ( rtDW . cqp1dau03w ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . gfiovjo3e2 )
, rtdwData , 0 , 22 , sizeof ( rtDW . gfiovjo3e2 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . p2iwsajmfp )
, rtdwData , 0 , 23 , sizeof ( rtDW . p2iwsajmfp ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . b4auxd1lsk )
, rtdwData , 0 , 24 , sizeof ( rtDW . b4auxd1lsk ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . al5aajfx21 )
, rtdwData , 0 , 25 , sizeof ( rtDW . al5aajfx21 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . gt3chc0tga )
, rtdwData , 0 , 26 , sizeof ( rtDW . gt3chc0tga ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . erukb0glgz )
, rtdwData , 0 , 27 , sizeof ( rtDW . erukb0glgz ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . pdjkbbbzjq )
, rtdwData , 0 , 28 , sizeof ( rtDW . pdjkbbbzjq ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . pml0yl52te )
, rtdwData , 0 , 29 , sizeof ( rtDW . pml0yl52te ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . eswvf4pz4v )
, rtdwData , 0 , 30 , sizeof ( rtDW . eswvf4pz4v ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . phidvr4lhk )
, rtdwData , 0 , 31 , sizeof ( rtDW . phidvr4lhk ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . atdfcebxbc )
, rtdwData , 0 , 32 , sizeof ( rtDW . atdfcebxbc ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . o3sgmp4aev )
, rtdwData , 0 , 33 , sizeof ( rtDW . o3sgmp4aev ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . nld3uzo5io )
, rtdwData , 0 , 34 , sizeof ( rtDW . nld3uzo5io ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . fi4wuwmktb )
, rtdwData , 0 , 35 , sizeof ( rtDW . fi4wuwmktb ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . gm4ivysliu )
, rtdwData , 0 , 36 , sizeof ( rtDW . gm4ivysliu ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . pyurk4he1k )
, rtdwData , 0 , 37 , sizeof ( rtDW . pyurk4he1k ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ocff1ayzzn )
, rtdwData , 0 , 38 , sizeof ( rtDW . ocff1ayzzn ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . l0rzviqodi )
, rtdwData , 0 , 39 , sizeof ( rtDW . l0rzviqodi ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . o0qik01ouq )
, rtdwData , 0 , 40 , sizeof ( rtDW . o0qik01ouq ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jci52usrwf )
, rtdwData , 0 , 41 , sizeof ( rtDW . jci52usrwf ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . n0ifswwd21 )
, rtdwData , 0 , 42 , sizeof ( rtDW . n0ifswwd21 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . enqlcsixk2 )
, rtdwData , 0 , 43 , sizeof ( rtDW . enqlcsixk2 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . bq4gap0f1m )
, rtdwData , 0 , 44 , sizeof ( rtDW . bq4gap0f1m ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . lfuv5ipyfs )
, rtdwData , 0 , 45 , sizeof ( rtDW . lfuv5ipyfs ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hjbvl0tg45 )
, rtdwData , 0 , 46 , sizeof ( rtDW . hjbvl0tg45 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . nyxm5sdvcd )
, rtdwData , 0 , 47 , sizeof ( rtDW . nyxm5sdvcd ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . f0lbp4tqqn )
, rtdwData , 0 , 48 , sizeof ( rtDW . f0lbp4tqqn ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . fva2rmvmh4 )
, rtdwData , 0 , 49 , sizeof ( rtDW . fva2rmvmh4 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hdlc0qsc4w )
, rtdwData , 0 , 50 , sizeof ( rtDW . hdlc0qsc4w ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . fl4tijqsrl )
, rtdwData , 0 , 51 , sizeof ( rtDW . fl4tijqsrl ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . mxawq0evig )
, rtdwData , 0 , 52 , sizeof ( rtDW . mxawq0evig ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . e1vdezejb0 )
, rtdwData , 0 , 53 , sizeof ( rtDW . e1vdezejb0 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . nrq4usubsl )
, rtdwData , 0 , 54 , sizeof ( rtDW . nrq4usubsl ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . omuzgpsf1f )
, rtdwData , 0 , 55 , sizeof ( rtDW . omuzgpsf1f ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hys0om0qbu )
, rtdwData , 0 , 56 , sizeof ( rtDW . hys0om0qbu ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . nr5d4vqt4t )
, rtdwData , 0 , 57 , sizeof ( rtDW . nr5d4vqt4t ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cnk414y00k )
, rtdwData , 0 , 58 , sizeof ( rtDW . cnk414y00k ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . fnpjhtoie0 )
, rtdwData , 0 , 59 , sizeof ( rtDW . fnpjhtoie0 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . frvvvscadt )
, rtdwData , 0 , 60 , sizeof ( rtDW . frvvvscadt ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . pfwwityzhm )
, rtdwData , 0 , 61 , sizeof ( rtDW . pfwwityzhm ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . awvvdj3gzy )
, rtdwData , 0 , 62 , sizeof ( rtDW . awvvdj3gzy ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . esrssadyy0 )
, rtdwData , 0 , 63 , sizeof ( rtDW . esrssadyy0 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . loh1yczrtr )
, rtdwData , 0 , 64 , sizeof ( rtDW . loh1yczrtr ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cayw42bvqq )
, rtdwData , 0 , 65 , sizeof ( rtDW . cayw42bvqq ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . fmhxej54hb )
, rtdwData , 0 , 66 , sizeof ( rtDW . fmhxej54hb ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . fzberuaezs )
, rtdwData , 0 , 67 , sizeof ( rtDW . fzberuaezs ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . oiurtflkiv )
, rtdwData , 0 , 68 , sizeof ( rtDW . oiurtflkiv ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cedwdfuxlq )
, rtdwData , 0 , 69 , sizeof ( rtDW . cedwdfuxlq ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ny5tmca5u1 )
, rtdwData , 0 , 70 , sizeof ( rtDW . ny5tmca5u1 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . k3sz0zxcz4 )
, rtdwData , 0 , 71 , sizeof ( rtDW . k3sz0zxcz4 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hafwy3njkc )
, rtdwData , 0 , 72 , sizeof ( rtDW . hafwy3njkc ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . gqa5jm0r2v )
, rtdwData , 0 , 73 , sizeof ( rtDW . gqa5jm0r2v ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . inffcupvx2 )
, rtdwData , 0 , 74 , sizeof ( rtDW . inffcupvx2 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . p21lrpi51b )
, rtdwData , 0 , 75 , sizeof ( rtDW . p21lrpi51b ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . mpvdclcsce )
, rtdwData , 0 , 76 , sizeof ( rtDW . mpvdclcsce ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hma0f53x5s )
, rtdwData , 0 , 77 , sizeof ( rtDW . hma0f53x5s ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . fbadxescvd )
, rtdwData , 0 , 78 , sizeof ( rtDW . fbadxescvd ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . neqcp2rk0x )
, rtdwData , 0 , 79 , sizeof ( rtDW . neqcp2rk0x ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . injrnpzipy )
, rtdwData , 0 , 80 , sizeof ( rtDW . injrnpzipy ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cgg3v13mlz )
, rtdwData , 0 , 81 , sizeof ( rtDW . cgg3v13mlz ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ffjft2t0pj )
, rtdwData , 0 , 82 , sizeof ( rtDW . ffjft2t0pj ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jayew5vh20 )
, rtdwData , 0 , 83 , sizeof ( rtDW . jayew5vh20 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . gtl5stszrm )
, rtdwData , 0 , 84 , sizeof ( rtDW . gtl5stszrm ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . pacgla51lq )
, rtdwData , 0 , 85 , sizeof ( rtDW . pacgla51lq ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jntfw1jmxj )
, rtdwData , 0 , 86 , sizeof ( rtDW . jntfw1jmxj ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ml1vr0zmzd )
, rtdwData , 0 , 87 , sizeof ( rtDW . ml1vr0zmzd ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ietukijfm5 )
, rtdwData , 0 , 88 , sizeof ( rtDW . ietukijfm5 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hcvygsausk )
, rtdwData , 0 , 89 , sizeof ( rtDW . hcvygsausk ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . osj02yjrnn )
, rtdwData , 0 , 90 , sizeof ( rtDW . osj02yjrnn ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . o3dbqj4xyk )
, rtdwData , 0 , 91 , sizeof ( rtDW . o3dbqj4xyk ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ghxlzewxqv )
, rtdwData , 0 , 92 , sizeof ( rtDW . ghxlzewxqv ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jw4znmasof )
, rtdwData , 0 , 93 , sizeof ( rtDW . jw4znmasof ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jsu3fijte2 )
, rtdwData , 0 , 94 , sizeof ( rtDW . jsu3fijte2 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . my5afrzgkd )
, rtdwData , 0 , 95 , sizeof ( rtDW . my5afrzgkd ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . edo3dr0fru )
, rtdwData , 0 , 96 , sizeof ( rtDW . edo3dr0fru ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hyaxdywynl )
, rtdwData , 0 , 97 , sizeof ( rtDW . hyaxdywynl ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . on2kbwtd1i )
, rtdwData , 0 , 98 , sizeof ( rtDW . on2kbwtd1i ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . lfzkcubuyh )
, rtdwData , 0 , 99 , sizeof ( rtDW . lfzkcubuyh ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . bt2kw45n5u )
, rtdwData , 0 , 100 , sizeof ( rtDW . bt2kw45n5u ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . eqzj0rxvun )
, rtdwData , 0 , 101 , sizeof ( rtDW . eqzj0rxvun ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ilnpea2zjg )
, rtdwData , 0 , 102 , sizeof ( rtDW . ilnpea2zjg ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ddhgjj4slr )
, rtdwData , 0 , 103 , sizeof ( rtDW . ddhgjj4slr ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cguk3rlz2c )
, rtdwData , 0 , 104 , sizeof ( rtDW . cguk3rlz2c ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . myfhgr2zam )
, rtdwData , 0 , 105 , sizeof ( rtDW . myfhgr2zam ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jsu3fijte22
) , rtdwData , 0 , 106 , sizeof ( rtDW . jsu3fijte22 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . my5afrzgkdf
) , rtdwData , 0 , 107 , sizeof ( rtDW . my5afrzgkdf ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . edo3dr0fru5
) , rtdwData , 0 , 108 , sizeof ( rtDW . edo3dr0fru5 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hyaxdywynlc
) , rtdwData , 0 , 109 , sizeof ( rtDW . hyaxdywynlc ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . anqq4l0npb )
, rtdwData , 0 , 110 , sizeof ( rtDW . anqq4l0npb ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . o13fmizguv )
, rtdwData , 0 , 111 , sizeof ( rtDW . o13fmizguv ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hdglqralt5 )
, rtdwData , 0 , 112 , sizeof ( rtDW . hdglqralt5 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ptnxk4g0lc )
, rtdwData , 0 , 113 , sizeof ( rtDW . ptnxk4g0lc ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . pjnb2ek2e3 )
, rtdwData , 0 , 114 , sizeof ( rtDW . pjnb2ek2e3 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . m0rv3vqddv )
, rtdwData , 0 , 115 , sizeof ( rtDW . m0rv3vqddv ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . o10ebbt22e )
, rtdwData , 0 , 116 , sizeof ( rtDW . o10ebbt22e ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . mam5vcqfvx )
, rtdwData , 0 , 117 , sizeof ( rtDW . mam5vcqfvx ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jsu3fijte22m
) , rtdwData , 0 , 118 , sizeof ( rtDW . jsu3fijte22m ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . my5afrzgkdfq
) , rtdwData , 0 , 119 , sizeof ( rtDW . my5afrzgkdfq ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . edo3dr0fru5x
) , rtdwData , 0 , 120 , sizeof ( rtDW . edo3dr0fru5x ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hyaxdywynlcl
) , rtdwData , 0 , 121 , sizeof ( rtDW . hyaxdywynlcl ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . dq0pmdxppu )
, rtdwData , 0 , 122 , sizeof ( rtDW . dq0pmdxppu ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jpqfmeeeto )
, rtdwData , 0 , 123 , sizeof ( rtDW . jpqfmeeeto ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . p25vgyovxo )
, rtdwData , 0 , 124 , sizeof ( rtDW . p25vgyovxo ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . fgxsmumrmw )
, rtdwData , 0 , 125 , sizeof ( rtDW . fgxsmumrmw ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . p3km4baqfe )
, rtdwData , 0 , 126 , sizeof ( rtDW . p3km4baqfe ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . agchj4uiph )
, rtdwData , 0 , 127 , sizeof ( rtDW . agchj4uiph ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . fd5nlfaj2u )
, rtdwData , 0 , 128 , sizeof ( rtDW . fd5nlfaj2u ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . gvxq4lgohv )
, rtdwData , 0 , 129 , sizeof ( rtDW . gvxq4lgohv ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ixrsi3erhf )
, rtdwData , 0 , 130 , sizeof ( rtDW . ixrsi3erhf ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jis1uepreo )
, rtdwData , 0 , 131 , sizeof ( rtDW . jis1uepreo ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . fwkxey5epo )
, rtdwData , 0 , 132 , sizeof ( rtDW . fwkxey5epo ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . pnsuou2020 )
, rtdwData , 0 , 133 , sizeof ( rtDW . pnsuou2020 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . opg1thx2qw )
, rtdwData , 0 , 134 , sizeof ( rtDW . opg1thx2qw ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . amalc3ffil )
, rtdwData , 0 , 135 , sizeof ( rtDW . amalc3ffil ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . mwenvz0tar )
, rtdwData , 0 , 136 , sizeof ( rtDW . mwenvz0tar ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . de3otshxus )
, rtdwData , 0 , 137 , sizeof ( rtDW . de3otshxus ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . i2ctd1awel )
, rtdwData , 0 , 138 , sizeof ( rtDW . i2ctd1awel ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ccf5juo5ya )
, rtdwData , 0 , 139 , sizeof ( rtDW . ccf5juo5ya ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . i4lkkodfyj )
, rtdwData , 0 , 140 , sizeof ( rtDW . i4lkkodfyj ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . mdvclm3wpb )
, rtdwData , 0 , 141 , sizeof ( rtDW . mdvclm3wpb ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . gai5nv42oe )
, rtdwData , 0 , 142 , sizeof ( rtDW . gai5nv42oe ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . imfxseqvvv )
, rtdwData , 0 , 143 , sizeof ( rtDW . imfxseqvvv ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cxatkad2jz )
, rtdwData , 0 , 144 , sizeof ( rtDW . cxatkad2jz ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ikxzuowx1v )
, rtdwData , 0 , 145 , sizeof ( rtDW . ikxzuowx1v ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . bg2vv1po0e )
, rtdwData , 0 , 146 , sizeof ( rtDW . bg2vv1po0e ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . f4tcd4udur )
, rtdwData , 0 , 147 , sizeof ( rtDW . f4tcd4udur ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ctbynjdwij )
, rtdwData , 0 , 148 , sizeof ( rtDW . ctbynjdwij ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . anfxf0zt2u )
, rtdwData , 0 , 149 , sizeof ( rtDW . anfxf0zt2u ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . afo0nwhxua )
, rtdwData , 0 , 150 , sizeof ( rtDW . afo0nwhxua ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jdtstycpmg )
, rtdwData , 0 , 151 , sizeof ( rtDW . jdtstycpmg ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . g2ry4vjsj1 )
, rtdwData , 0 , 152 , sizeof ( rtDW . g2ry4vjsj1 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . iehvrkddj2 )
, rtdwData , 0 , 153 , sizeof ( rtDW . iehvrkddj2 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . nbavx35izv )
, rtdwData , 0 , 154 , sizeof ( rtDW . nbavx35izv ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cl1vsftpzn )
, rtdwData , 0 , 155 , sizeof ( rtDW . cl1vsftpzn ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . lhojsnn24m )
, rtdwData , 0 , 156 , sizeof ( rtDW . lhojsnn24m ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . d42pvxfz0g )
, rtdwData , 0 , 157 , sizeof ( rtDW . d42pvxfz0g ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . kovzbujdnb )
, rtdwData , 0 , 158 , sizeof ( rtDW . kovzbujdnb ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . dttn4xmcnk )
, rtdwData , 0 , 159 , sizeof ( rtDW . dttn4xmcnk ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . n1ap5w5rdi )
, rtdwData , 0 , 160 , sizeof ( rtDW . n1ap5w5rdi ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ndb122ek3u )
, rtdwData , 0 , 161 , sizeof ( rtDW . ndb122ek3u ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hoesofthyy )
, rtdwData , 0 , 162 , sizeof ( rtDW . hoesofthyy ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ifur0qjdev )
, rtdwData , 0 , 163 , sizeof ( rtDW . ifur0qjdev ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . h2z1m5wxiy )
, rtdwData , 0 , 164 , sizeof ( rtDW . h2z1m5wxiy ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . dviol1u0jv )
, rtdwData , 0 , 165 , sizeof ( rtDW . dviol1u0jv ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . df5ibuzfvl )
, rtdwData , 0 , 166 , sizeof ( rtDW . df5ibuzfvl ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ikv4gqtanm )
, rtdwData , 0 , 167 , sizeof ( rtDW . ikv4gqtanm ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hru10ym4o1 )
, rtdwData , 0 , 168 , sizeof ( rtDW . hru10ym4o1 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . erp5nno2ec )
, rtdwData , 0 , 169 , sizeof ( rtDW . erp5nno2ec ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ima1cclrzn )
, rtdwData , 0 , 170 , sizeof ( rtDW . ima1cclrzn ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hm24hbgcg1 )
, rtdwData , 0 , 171 , sizeof ( rtDW . hm24hbgcg1 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ob20xueupt )
, rtdwData , 0 , 172 , sizeof ( rtDW . ob20xueupt ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . emh5kwkq0f )
, rtdwData , 0 , 173 , sizeof ( rtDW . emh5kwkq0f ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . f3zvxiekpj )
, rtdwData , 0 , 174 , sizeof ( rtDW . f3zvxiekpj ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . dspkd5mdvs )
, rtdwData , 0 , 175 , sizeof ( rtDW . dspkd5mdvs ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . gmymeboquk )
, rtdwData , 0 , 176 , sizeof ( rtDW . gmymeboquk ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . bs1nmm0jpl )
, rtdwData , 0 , 177 , sizeof ( rtDW . bs1nmm0jpl ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . bx5vsdt4mt )
, rtdwData , 0 , 178 , sizeof ( rtDW . bx5vsdt4mt ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ciaqlqmyyx )
, rtdwData , 0 , 179 , sizeof ( rtDW . ciaqlqmyyx ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . e1kih03oaj )
, rtdwData , 0 , 180 , sizeof ( rtDW . e1kih03oaj ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . m5gzgpvijm )
, rtdwData , 0 , 181 , sizeof ( rtDW . m5gzgpvijm ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . o3kxgyy1fj )
, rtdwData , 0 , 182 , sizeof ( rtDW . o3kxgyy1fj ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . nkf0blmwkl )
, rtdwData , 0 , 183 , sizeof ( rtDW . nkf0blmwkl ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . h5lg5oz5ks )
, rtdwData , 0 , 184 , sizeof ( rtDW . h5lg5oz5ks ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hggmceleiv )
, rtdwData , 0 , 185 , sizeof ( rtDW . hggmceleiv ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . pdhtdmqeof )
, rtdwData , 0 , 186 , sizeof ( rtDW . pdhtdmqeof ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . i3xwoxj5zy )
, rtdwData , 0 , 187 , sizeof ( rtDW . i3xwoxj5zy ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . lth0p1kskk )
, rtdwData , 0 , 188 , sizeof ( rtDW . lth0p1kskk ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ko0pv0nfnn )
, rtdwData , 0 , 189 , sizeof ( rtDW . ko0pv0nfnn ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . kr1btzpdxw )
, rtdwData , 0 , 190 , sizeof ( rtDW . kr1btzpdxw ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . axidhoghf0 )
, rtdwData , 0 , 191 , sizeof ( rtDW . axidhoghf0 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . pqgou55kzx )
, rtdwData , 0 , 192 , sizeof ( rtDW . pqgou55kzx ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . fuh3bn4ezo )
, rtdwData , 0 , 193 , sizeof ( rtDW . fuh3bn4ezo ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . kzefheif0g )
, rtdwData , 0 , 194 , sizeof ( rtDW . kzefheif0g ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . aa2p00mqis )
, rtdwData , 0 , 195 , sizeof ( rtDW . aa2p00mqis ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . pasm0mbp1y )
, rtdwData , 0 , 196 , sizeof ( rtDW . pasm0mbp1y ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jqvl3ulori )
, rtdwData , 0 , 197 , sizeof ( rtDW . jqvl3ulori ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jez5q1v2di )
, rtdwData , 0 , 198 , sizeof ( rtDW . jez5q1v2di ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . lr1nlrmqch )
, rtdwData , 0 , 199 , sizeof ( rtDW . lr1nlrmqch ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . a44d5qyg12 )
, rtdwData , 0 , 200 , sizeof ( rtDW . a44d5qyg12 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . bwkcfpuwid )
, rtdwData , 0 , 201 , sizeof ( rtDW . bwkcfpuwid ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cno1ak0c3c )
, rtdwData , 0 , 202 , sizeof ( rtDW . cno1ak0c3c ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . nxk0ojgi44 )
, rtdwData , 0 , 203 , sizeof ( rtDW . nxk0ojgi44 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . bubytbfjvq )
, rtdwData , 0 , 204 , sizeof ( rtDW . bubytbfjvq ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . glikpzp24u )
, rtdwData , 0 , 205 , sizeof ( rtDW . glikpzp24u ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hskq4vr1qs )
, rtdwData , 0 , 206 , sizeof ( rtDW . hskq4vr1qs ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hljbnnt3zw )
, rtdwData , 0 , 207 , sizeof ( rtDW . hljbnnt3zw ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . d2cg15qgjf )
, rtdwData , 0 , 208 , sizeof ( rtDW . d2cg15qgjf ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ir1mqsar5f )
, rtdwData , 0 , 209 , sizeof ( rtDW . ir1mqsar5f ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . kebzxgfy5a )
, rtdwData , 0 , 210 , sizeof ( rtDW . kebzxgfy5a ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . pmncprwmz4 )
, rtdwData , 0 , 211 , sizeof ( rtDW . pmncprwmz4 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . g05suawwrk )
, rtdwData , 0 , 212 , sizeof ( rtDW . g05suawwrk ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ore24n4522 )
, rtdwData , 0 , 213 , sizeof ( rtDW . ore24n4522 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . mz1lyyodga )
, rtdwData , 0 , 214 , sizeof ( rtDW . mz1lyyodga ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . i22hackosr )
, rtdwData , 0 , 215 , sizeof ( rtDW . i22hackosr ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hrf0r3epza )
, rtdwData , 0 , 216 , sizeof ( rtDW . hrf0r3epza ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . l4gldy0ied )
, rtdwData , 0 , 217 , sizeof ( rtDW . l4gldy0ied ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jcgd4tqv41 )
, rtdwData , 0 , 218 , sizeof ( rtDW . jcgd4tqv41 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . oyxqmd0f4v )
, rtdwData , 0 , 219 , sizeof ( rtDW . oyxqmd0f4v ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cdd1gh0rmi )
, rtdwData , 0 , 220 , sizeof ( rtDW . cdd1gh0rmi ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ayjsmpf3pd )
, rtdwData , 0 , 221 , sizeof ( rtDW . ayjsmpf3pd ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . etncgat1qk )
, rtdwData , 0 , 222 , sizeof ( rtDW . etncgat1qk ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . j0pfyx5sl0 )
, rtdwData , 0 , 223 , sizeof ( rtDW . j0pfyx5sl0 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . otdqomronl )
, rtdwData , 0 , 224 , sizeof ( rtDW . otdqomronl ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . nz3xkbxksp )
, rtdwData , 0 , 225 , sizeof ( rtDW . nz3xkbxksp ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cmxd2uv3ip )
, rtdwData , 0 , 226 , sizeof ( rtDW . cmxd2uv3ip ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hbomutgs5x )
, rtdwData , 0 , 227 , sizeof ( rtDW . hbomutgs5x ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . kkklfomjr5 )
, rtdwData , 0 , 228 , sizeof ( rtDW . kkklfomjr5 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . dmmot30jq4 )
, rtdwData , 0 , 229 , sizeof ( rtDW . dmmot30jq4 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . dzr2rntvvo )
, rtdwData , 0 , 230 , sizeof ( rtDW . dzr2rntvvo ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . aw0bxhrzal )
, rtdwData , 0 , 231 , sizeof ( rtDW . aw0bxhrzal ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . estezyunas )
, rtdwData , 0 , 232 , sizeof ( rtDW . estezyunas ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . olzifhaukx )
, rtdwData , 0 , 233 , sizeof ( rtDW . olzifhaukx ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . miwm3apiea )
, rtdwData , 0 , 234 , sizeof ( rtDW . miwm3apiea ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . otborblus0 )
, rtdwData , 0 , 235 , sizeof ( rtDW . otborblus0 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jcievkrvvv )
, rtdwData , 0 , 236 , sizeof ( rtDW . jcievkrvvv ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ovlbtlz2z5 )
, rtdwData , 0 , 237 , sizeof ( rtDW . ovlbtlz2z5 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . mx1dy0gdum )
, rtdwData , 0 , 238 , sizeof ( rtDW . mx1dy0gdum ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . iygynuhhiw )
, rtdwData , 0 , 239 , sizeof ( rtDW . iygynuhhiw ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . oamcwpfckc )
, rtdwData , 0 , 240 , sizeof ( rtDW . oamcwpfckc ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . az4aq4f2to )
, rtdwData , 0 , 241 , sizeof ( rtDW . az4aq4f2to ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hv1tfq2dkg )
, rtdwData , 0 , 242 , sizeof ( rtDW . hv1tfq2dkg ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ckuddxo2v5 )
, rtdwData , 0 , 243 , sizeof ( rtDW . ckuddxo2v5 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hoqlzb3yrr )
, rtdwData , 0 , 244 , sizeof ( rtDW . hoqlzb3yrr ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . d2yav1jvrg )
, rtdwData , 0 , 245 , sizeof ( rtDW . d2yav1jvrg ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . pdli3lyef1 )
, rtdwData , 0 , 246 , sizeof ( rtDW . pdli3lyef1 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . bqjtw0doyx )
, rtdwData , 0 , 247 , sizeof ( rtDW . bqjtw0doyx ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cc421u2f3f )
, rtdwData , 0 , 248 , sizeof ( rtDW . cc421u2f3f ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . pdjafikrtl )
, rtdwData , 0 , 249 , sizeof ( rtDW . pdjafikrtl ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . pojlxrwx0d )
, rtdwData , 0 , 250 , sizeof ( rtDW . pojlxrwx0d ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . m4fnnxykzj )
, rtdwData , 0 , 251 , sizeof ( rtDW . m4fnnxykzj ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . k40ux0ctpf )
, rtdwData , 0 , 252 , sizeof ( rtDW . k40ux0ctpf ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . kvknfbkwvk )
, rtdwData , 0 , 253 , sizeof ( rtDW . kvknfbkwvk ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . by04uer2xp )
, rtdwData , 0 , 254 , sizeof ( rtDW . by04uer2xp ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . n1vlvivlrx )
, rtdwData , 0 , 255 , sizeof ( rtDW . n1vlvivlrx ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ib3g0mc4j4 )
, rtdwData , 0 , 256 , sizeof ( rtDW . ib3g0mc4j4 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . c3coe5r3z1 )
, rtdwData , 0 , 257 , sizeof ( rtDW . c3coe5r3z1 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . gopfnpfdpo )
, rtdwData , 0 , 258 , sizeof ( rtDW . gopfnpfdpo ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . fhefxq1ozn )
, rtdwData , 0 , 259 , sizeof ( rtDW . fhefxq1ozn ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . bfidcyeanb )
, rtdwData , 0 , 260 , sizeof ( rtDW . bfidcyeanb ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . fi31qowovj )
, rtdwData , 0 , 261 , sizeof ( rtDW . fi31qowovj ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . pbpmgsmorm )
, rtdwData , 0 , 262 , sizeof ( rtDW . pbpmgsmorm ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . axle03m4av )
, rtdwData , 0 , 263 , sizeof ( rtDW . axle03m4av ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . evcuev5sfd )
, rtdwData , 0 , 264 , sizeof ( rtDW . evcuev5sfd ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cblzsrog5u )
, rtdwData , 0 , 265 , sizeof ( rtDW . cblzsrog5u ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . nqfbacpvcp )
, rtdwData , 0 , 266 , sizeof ( rtDW . nqfbacpvcp ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . fdktvwm3kd )
, rtdwData , 0 , 267 , sizeof ( rtDW . fdktvwm3kd ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . bjkklesnma )
, rtdwData , 0 , 268 , sizeof ( rtDW . bjkklesnma ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . nsaa1gti0b )
, rtdwData , 0 , 269 , sizeof ( rtDW . nsaa1gti0b ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ghx0ts2zzs )
, rtdwData , 0 , 270 , sizeof ( rtDW . ghx0ts2zzs ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . lafrvsvgf0 )
, rtdwData , 0 , 271 , sizeof ( rtDW . lafrvsvgf0 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . og3lno4rre )
, rtdwData , 0 , 272 , sizeof ( rtDW . og3lno4rre ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ld5g5vrgmj )
, rtdwData , 0 , 273 , sizeof ( rtDW . ld5g5vrgmj ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . niztd2zg4p )
, rtdwData , 0 , 274 , sizeof ( rtDW . niztd2zg4p ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . faadh0wdog )
, rtdwData , 0 , 275 , sizeof ( rtDW . faadh0wdog ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jgx0xkzgjo )
, rtdwData , 0 , 276 , sizeof ( rtDW . jgx0xkzgjo ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . gpf5tclqta )
, rtdwData , 0 , 277 , sizeof ( rtDW . gpf5tclqta ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . mvfamndgj4 )
, rtdwData , 0 , 278 , sizeof ( rtDW . mvfamndgj4 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . kcaj1yegtz )
, rtdwData , 0 , 279 , sizeof ( rtDW . kcaj1yegtz ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . guhdmzy0n4 )
, rtdwData , 0 , 280 , sizeof ( rtDW . guhdmzy0n4 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . bi1fzovgs2 )
, rtdwData , 0 , 281 , sizeof ( rtDW . bi1fzovgs2 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . llxyyz4q5x )
, rtdwData , 0 , 282 , sizeof ( rtDW . llxyyz4q5x ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . bjzrd2jgh1 )
, rtdwData , 0 , 283 , sizeof ( rtDW . bjzrd2jgh1 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . npqdzcpz4k )
, rtdwData , 0 , 284 , sizeof ( rtDW . npqdzcpz4k ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . k44l31otpd )
, rtdwData , 0 , 285 , sizeof ( rtDW . k44l31otpd ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ocwqpyvhqo )
, rtdwData , 0 , 286 , sizeof ( rtDW . ocwqpyvhqo ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . bb0v2ld5vf )
, rtdwData , 0 , 287 , sizeof ( rtDW . bb0v2ld5vf ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . htr1ntw0w0 )
, rtdwData , 0 , 288 , sizeof ( rtDW . htr1ntw0w0 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . f1sl003e30 )
, rtdwData , 0 , 289 , sizeof ( rtDW . f1sl003e30 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . lbwbhxgeac )
, rtdwData , 0 , 290 , sizeof ( rtDW . lbwbhxgeac ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . lgjrfdubva )
, rtdwData , 0 , 291 , sizeof ( rtDW . lgjrfdubva ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . il1i11vhya )
, rtdwData , 0 , 292 , sizeof ( rtDW . il1i11vhya ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . fmvtpht2wc )
, rtdwData , 0 , 293 , sizeof ( rtDW . fmvtpht2wc ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jlwpaqqpol )
, rtdwData , 0 , 294 , sizeof ( rtDW . jlwpaqqpol ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . o2nyvbjxnw )
, rtdwData , 0 , 295 , sizeof ( rtDW . o2nyvbjxnw ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . mofgw1cji2 )
, rtdwData , 0 , 296 , sizeof ( rtDW . mofgw1cji2 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hbtp4braxp )
, rtdwData , 0 , 297 , sizeof ( rtDW . hbtp4braxp ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ifa1aifv0v )
, rtdwData , 0 , 298 , sizeof ( rtDW . ifa1aifv0v ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . azvnw5pvht )
, rtdwData , 0 , 299 , sizeof ( rtDW . azvnw5pvht ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . avqcisj0g1 )
, rtdwData , 0 , 300 , sizeof ( rtDW . avqcisj0g1 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hyopdoshjp )
, rtdwData , 0 , 301 , sizeof ( rtDW . hyopdoshjp ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . fqvcumyba1 )
, rtdwData , 0 , 302 , sizeof ( rtDW . fqvcumyba1 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . njfpshnpni )
, rtdwData , 0 , 303 , sizeof ( rtDW . njfpshnpni ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . k0efqstpz0 )
, rtdwData , 0 , 304 , sizeof ( rtDW . k0efqstpz0 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jitieevvno )
, rtdwData , 0 , 305 , sizeof ( rtDW . jitieevvno ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . ip0d0t1043 )
, rtdwData , 0 , 306 , sizeof ( rtDW . ip0d0t1043 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . i1c4xekdhn )
, rtdwData , 0 , 307 , sizeof ( rtDW . i1c4xekdhn ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . bfyezaoly2 )
, rtdwData , 0 , 308 , sizeof ( rtDW . bfyezaoly2 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . idcpojjs11 )
, rtdwData , 0 , 309 , sizeof ( rtDW . idcpojjs11 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . fe3ipxqiw5 )
, rtdwData , 0 , 310 , sizeof ( rtDW . fe3ipxqiw5 ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . hw1g0wvqpq )
, rtdwData , 0 , 311 , sizeof ( rtDW . hw1g0wvqpq ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . iw5qsles1z )
, rtdwData , 0 , 312 , sizeof ( rtDW . iw5qsles1z ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . gomqyfi1fi )
, rtdwData , 0 , 313 , sizeof ( rtDW . gomqyfi1fi ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . dczrefoerg )
, rtdwData , 0 , 314 , sizeof ( rtDW . dczrefoerg ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . py4iuvrbea )
, rtdwData , 0 , 315 , sizeof ( rtDW . py4iuvrbea ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . a43rt5p5qk )
, rtdwData , 0 , 316 , sizeof ( rtDW . a43rt5p5qk ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . e5cexk5tsa )
, rtdwData , 0 , 317 , sizeof ( rtDW . e5cexk5tsa ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . d2ne5d41vh )
, rtdwData , 0 , 318 , sizeof ( rtDW . d2ne5d41vh ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . gdbbfmmgdg )
, rtdwData , 0 , 319 , sizeof ( rtDW . gdbbfmmgdg ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jd2ppumcjt )
, rtdwData , 0 , 320 , sizeof ( rtDW . jd2ppumcjt ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cx41wglw3j .
bineo4prgi ) , rtdwData , 0 , 321 , sizeof ( rtDW . cx41wglw3j . bineo4prgi )
) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW .
cx41wglw3j . bvutux0ucw ) , rtdwData , 0 , 322 , sizeof ( rtDW . cx41wglw3j .
bvutux0ucw ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & (
rtDW . jjob4ur221 . bineo4prgi ) , rtdwData , 0 , 323 , sizeof ( rtDW .
jjob4ur221 . bineo4prgi ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( (
void * ) & ( rtDW . jjob4ur221 . bvutux0ucw ) , rtdwData , 0 , 324 , sizeof (
rtDW . jjob4ur221 . bvutux0ucw ) ) ; mr_uz_drive_model_restoreDataFromMxArray
( ( void * ) & ( rtDW . jogryxdnkz . bineo4prgi ) , rtdwData , 0 , 325 ,
sizeof ( rtDW . jogryxdnkz . bineo4prgi ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jogryxdnkz .
bvutux0ucw ) , rtdwData , 0 , 326 , sizeof ( rtDW . jogryxdnkz . bvutux0ucw )
) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW .
n4cqr1dkmr . bineo4prgi ) , rtdwData , 0 , 327 , sizeof ( rtDW . n4cqr1dkmr .
bineo4prgi ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & (
rtDW . n4cqr1dkmr . bvutux0ucw ) , rtdwData , 0 , 328 , sizeof ( rtDW .
n4cqr1dkmr . bvutux0ucw ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( (
void * ) & ( rtDW . a13lr3lsi3 . bineo4prgi ) , rtdwData , 0 , 329 , sizeof (
rtDW . a13lr3lsi3 . bineo4prgi ) ) ; mr_uz_drive_model_restoreDataFromMxArray
( ( void * ) & ( rtDW . a13lr3lsi3 . bvutux0ucw ) , rtdwData , 0 , 330 ,
sizeof ( rtDW . a13lr3lsi3 . bvutux0ucw ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . jjajpmoyel .
bineo4prgi ) , rtdwData , 0 , 331 , sizeof ( rtDW . jjajpmoyel . bineo4prgi )
) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW .
jjajpmoyel . bvutux0ucw ) , rtdwData , 0 , 332 , sizeof ( rtDW . jjajpmoyel .
bvutux0ucw ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & (
rtDW . ndmeqad3sm . bineo4prgi ) , rtdwData , 0 , 333 , sizeof ( rtDW .
ndmeqad3sm . bineo4prgi ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( (
void * ) & ( rtDW . ndmeqad3sm . bvutux0ucw ) , rtdwData , 0 , 334 , sizeof (
rtDW . ndmeqad3sm . bvutux0ucw ) ) ; mr_uz_drive_model_restoreDataFromMxArray
( ( void * ) & ( rtDW . o0tbmhvpds . bineo4prgi ) , rtdwData , 0 , 335 ,
sizeof ( rtDW . o0tbmhvpds . bineo4prgi ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . o0tbmhvpds .
bvutux0ucw ) , rtdwData , 0 , 336 , sizeof ( rtDW . o0tbmhvpds . bvutux0ucw )
) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW .
f5mkygzljka . bineo4prgi ) , rtdwData , 0 , 337 , sizeof ( rtDW . f5mkygzljka
. bineo4prgi ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & (
rtDW . f5mkygzljka . bvutux0ucw ) , rtdwData , 0 , 338 , sizeof ( rtDW .
f5mkygzljka . bvutux0ucw ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( (
void * ) & ( rtDW . biyhxca30f . ftf50xwldj ) , rtdwData , 0 , 339 , sizeof (
rtDW . biyhxca30f . ftf50xwldj ) ) ; mr_uz_drive_model_restoreDataFromMxArray
( ( void * ) & ( rtDW . biyhxca30f . ic4jzsnsgd ) , rtdwData , 0 , 340 ,
sizeof ( rtDW . biyhxca30f . ic4jzsnsgd ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . biyhxca30f .
j5itaoriq1 ) , rtdwData , 0 , 341 , sizeof ( rtDW . biyhxca30f . j5itaoriq1 )
) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW .
biyhxca30f . bjona3wx3v ) , rtdwData , 0 , 342 , sizeof ( rtDW . biyhxca30f .
bjona3wx3v ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & (
rtDW . biyhxca30f . bldvjsjmit ) , rtdwData , 0 , 343 , sizeof ( rtDW .
biyhxca30f . bldvjsjmit ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( (
void * ) & ( rtDW . biyhxca30f . opg33homib ) , rtdwData , 0 , 344 , sizeof (
rtDW . biyhxca30f . opg33homib ) ) ; mr_uz_drive_model_restoreDataFromMxArray
( ( void * ) & ( rtDW . biyhxca30f . n4jsnmm3dp ) , rtdwData , 0 , 345 ,
sizeof ( rtDW . biyhxca30f . n4jsnmm3dp ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . biyhxca30f .
bnbpcxxvih ) , rtdwData , 0 , 346 , sizeof ( rtDW . biyhxca30f . bnbpcxxvih )
) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW .
biyhxca30f . e4ertwjipw ) , rtdwData , 0 , 347 , sizeof ( rtDW . biyhxca30f .
e4ertwjipw ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & (
rtDW . msqwmshj2n . ltyokv5jui ) , rtdwData , 0 , 348 , sizeof ( rtDW .
msqwmshj2n . ltyokv5jui ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( (
void * ) & ( rtDW . msqwmshj2n . dmqhv1kuog ) , rtdwData , 0 , 349 , sizeof (
rtDW . msqwmshj2n . dmqhv1kuog ) ) ; mr_uz_drive_model_restoreDataFromMxArray
( ( void * ) & ( rtDW . msqwmshj2n . grzcmycdpb ) , rtdwData , 0 , 350 ,
sizeof ( rtDW . msqwmshj2n . grzcmycdpb ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . msqwmshj2n .
hlqhpqgl5d ) , rtdwData , 0 , 351 , sizeof ( rtDW . msqwmshj2n . hlqhpqgl5d )
) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW .
msqwmshj2n . dqmv313jji ) , rtdwData , 0 , 352 , sizeof ( rtDW . msqwmshj2n .
dqmv313jji ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & (
rtDW . msqwmshj2n . jaldgiolnb ) , rtdwData , 0 , 353 , sizeof ( rtDW .
msqwmshj2n . jaldgiolnb ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( (
void * ) & ( rtDW . mzoe5aiivc . ftf50xwldj ) , rtdwData , 0 , 354 , sizeof (
rtDW . mzoe5aiivc . ftf50xwldj ) ) ; mr_uz_drive_model_restoreDataFromMxArray
( ( void * ) & ( rtDW . mzoe5aiivc . ic4jzsnsgd ) , rtdwData , 0 , 355 ,
sizeof ( rtDW . mzoe5aiivc . ic4jzsnsgd ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . mzoe5aiivc .
j5itaoriq1 ) , rtdwData , 0 , 356 , sizeof ( rtDW . mzoe5aiivc . j5itaoriq1 )
) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW .
mzoe5aiivc . bjona3wx3v ) , rtdwData , 0 , 357 , sizeof ( rtDW . mzoe5aiivc .
bjona3wx3v ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & (
rtDW . mzoe5aiivc . bldvjsjmit ) , rtdwData , 0 , 358 , sizeof ( rtDW .
mzoe5aiivc . bldvjsjmit ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( (
void * ) & ( rtDW . mzoe5aiivc . opg33homib ) , rtdwData , 0 , 359 , sizeof (
rtDW . mzoe5aiivc . opg33homib ) ) ; mr_uz_drive_model_restoreDataFromMxArray
( ( void * ) & ( rtDW . mzoe5aiivc . n4jsnmm3dp ) , rtdwData , 0 , 360 ,
sizeof ( rtDW . mzoe5aiivc . n4jsnmm3dp ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . mzoe5aiivc .
bnbpcxxvih ) , rtdwData , 0 , 361 , sizeof ( rtDW . mzoe5aiivc . bnbpcxxvih )
) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW .
mzoe5aiivc . e4ertwjipw ) , rtdwData , 0 , 362 , sizeof ( rtDW . mzoe5aiivc .
e4ertwjipw ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & (
rtDW . cstc0v1lpw . ltyokv5jui ) , rtdwData , 0 , 363 , sizeof ( rtDW .
cstc0v1lpw . ltyokv5jui ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( (
void * ) & ( rtDW . cstc0v1lpw . dmqhv1kuog ) , rtdwData , 0 , 364 , sizeof (
rtDW . cstc0v1lpw . dmqhv1kuog ) ) ; mr_uz_drive_model_restoreDataFromMxArray
( ( void * ) & ( rtDW . cstc0v1lpw . grzcmycdpb ) , rtdwData , 0 , 365 ,
sizeof ( rtDW . cstc0v1lpw . grzcmycdpb ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cstc0v1lpw .
hlqhpqgl5d ) , rtdwData , 0 , 366 , sizeof ( rtDW . cstc0v1lpw . hlqhpqgl5d )
) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW .
cstc0v1lpw . dqmv313jji ) , rtdwData , 0 , 367 , sizeof ( rtDW . cstc0v1lpw .
dqmv313jji ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & (
rtDW . cstc0v1lpw . jaldgiolnb ) , rtdwData , 0 , 368 , sizeof ( rtDW .
cstc0v1lpw . jaldgiolnb ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( (
void * ) & ( rtDW . azshdeeeiw3 . ftf50xwldj ) , rtdwData , 0 , 369 , sizeof
( rtDW . azshdeeeiw3 . ftf50xwldj ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . azshdeeeiw3
. ic4jzsnsgd ) , rtdwData , 0 , 370 , sizeof ( rtDW . azshdeeeiw3 .
ic4jzsnsgd ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & (
rtDW . azshdeeeiw3 . j5itaoriq1 ) , rtdwData , 0 , 371 , sizeof ( rtDW .
azshdeeeiw3 . j5itaoriq1 ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( (
void * ) & ( rtDW . azshdeeeiw3 . bjona3wx3v ) , rtdwData , 0 , 372 , sizeof
( rtDW . azshdeeeiw3 . bjona3wx3v ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . azshdeeeiw3
. bldvjsjmit ) , rtdwData , 0 , 373 , sizeof ( rtDW . azshdeeeiw3 .
bldvjsjmit ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & (
rtDW . azshdeeeiw3 . opg33homib ) , rtdwData , 0 , 374 , sizeof ( rtDW .
azshdeeeiw3 . opg33homib ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( (
void * ) & ( rtDW . azshdeeeiw3 . n4jsnmm3dp ) , rtdwData , 0 , 375 , sizeof
( rtDW . azshdeeeiw3 . n4jsnmm3dp ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . azshdeeeiw3
. bnbpcxxvih ) , rtdwData , 0 , 376 , sizeof ( rtDW . azshdeeeiw3 .
bnbpcxxvih ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & (
rtDW . azshdeeeiw3 . e4ertwjipw ) , rtdwData , 0 , 377 , sizeof ( rtDW .
azshdeeeiw3 . e4ertwjipw ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( (
void * ) & ( rtDW . cqjwvwhkzvh . ltyokv5jui ) , rtdwData , 0 , 378 , sizeof
( rtDW . cqjwvwhkzvh . ltyokv5jui ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cqjwvwhkzvh
. dmqhv1kuog ) , rtdwData , 0 , 379 , sizeof ( rtDW . cqjwvwhkzvh .
dmqhv1kuog ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & (
rtDW . cqjwvwhkzvh . grzcmycdpb ) , rtdwData , 0 , 380 , sizeof ( rtDW .
cqjwvwhkzvh . grzcmycdpb ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( (
void * ) & ( rtDW . cqjwvwhkzvh . hlqhpqgl5d ) , rtdwData , 0 , 381 , sizeof
( rtDW . cqjwvwhkzvh . hlqhpqgl5d ) ) ;
mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & ( rtDW . cqjwvwhkzvh
. dqmv313jji ) , rtdwData , 0 , 382 , sizeof ( rtDW . cqjwvwhkzvh .
dqmv313jji ) ) ; mr_uz_drive_model_restoreDataFromMxArray ( ( void * ) & (
rtDW . cqjwvwhkzvh . jaldgiolnb ) , rtdwData , 0 , 383 , sizeof ( rtDW .
cqjwvwhkzvh . jaldgiolnb ) ) ; } mr_uz_drive_model_restoreDataFromMxArray ( (
void * ) & ( rtPrevZCX ) , ssDW , 0 , 2 , sizeof ( rtPrevZCX ) ) ; } mxArray
* mr_uz_drive_model_GetSimStateDisallowedBlocks ( ) { mxArray * data =
mxCreateCellMatrix ( 10 , 3 ) ; mwIndex subs [ 2 ] , offset ; { static const
char * blockType [ 10 ] = { "Scope" , "Scope" , "Scope" , "Scope" , "Scope" ,
"Scope" , "Scope" , "Scope" , "Scope" , "Scope" , } ; static const char *
blockPath [ 10 ] = { "uz_drive_model/Scope" , "uz_drive_model/Scope1" ,
"uz_drive_model/Scope2" , "uz_drive_model/Scope3" ,
"uz_drive_model/uz_inverter_3ph2/Gate Signals" ,
"uz_drive_model/uz_inverter_3ph2/Iab" ,
"uz_drive_model/uz_inverter_3ph2/Uab-Ubc" ,
"uz_drive_model/uz_inverter_3ph1/Gate Signals" ,
"uz_drive_model/uz_inverter_3ph1/Iab" ,
"uz_drive_model/uz_inverter_3ph1/Uab-Ubc" , } ; static const int reason [ 10
] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , } ; for ( subs [ 0 ] = 0 ; subs
[ 0 ] < 10 ; ++ ( subs [ 0 ] ) ) { subs [ 1 ] = 0 ; offset =
mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data , offset ,
mxCreateString ( blockType [ subs [ 0 ] ] ) ) ; subs [ 1 ] = 1 ; offset =
mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data , offset ,
mxCreateString ( blockPath [ subs [ 0 ] ] ) ) ; subs [ 1 ] = 2 ; offset =
mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data , offset ,
mxCreateDoubleScalar ( ( double ) reason [ subs [ 0 ] ] ) ) ; } } return data
; } void MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS , 2 ) ;
ssSetNumPeriodicContStates ( rtS , 0 ) ; ssSetNumY ( rtS , 0 ) ; ssSetNumU (
rtS , 0 ) ; ssSetDirectFeedThrough ( rtS , 0 ) ; ssSetNumSampleTimes ( rtS ,
6 ) ; ssSetNumBlocks ( rtS , 1347 ) ; ssSetNumBlockIO ( rtS , 486 ) ;
ssSetNumBlockParams ( rtS , 4572 ) ; } void MdlInitializeSampleTimes ( void )
{ ssSetSampleTime ( rtS , 0 , 0.0 ) ; ssSetSampleTime ( rtS , 1 , 2.0E-9 ) ;
ssSetSampleTime ( rtS , 2 , 1.0E-7 ) ; ssSetSampleTime ( rtS , 3 , 5.0E-7 ) ;
ssSetSampleTime ( rtS , 4 , 1.0E-6 ) ; ssSetSampleTime ( rtS , 5 , 0.00025 )
; ssSetOffsetTime ( rtS , 0 , 0.0 ) ; ssSetOffsetTime ( rtS , 1 , 0.0 ) ;
ssSetOffsetTime ( rtS , 2 , 0.0 ) ; ssSetOffsetTime ( rtS , 3 , 0.0 ) ;
ssSetOffsetTime ( rtS , 4 , 0.0 ) ; ssSetOffsetTime ( rtS , 5 , 0.0 ) ; }
void raccel_set_checksum ( ) { ssSetChecksumVal ( rtS , 0 , 1450536526U ) ;
ssSetChecksumVal ( rtS , 1 , 3180783492U ) ; ssSetChecksumVal ( rtS , 2 ,
2573665585U ) ; ssSetChecksumVal ( rtS , 3 , 2888385381U ) ; }
#if defined(_MSC_VER)
#pragma optimize( "", off )
#endif
SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) {
static struct _ssMdlInfo mdlInfo ; ( void ) memset ( ( char * ) rtS , 0 ,
sizeof ( SimStruct ) ) ; ( void ) memset ( ( char * ) & mdlInfo , 0 , sizeof
( struct _ssMdlInfo ) ) ; ssSetMdlInfoPtr ( rtS , & mdlInfo ) ;
ssSetExecutionInfo ( rtS , executionInfo ) ; { static time_T mdlPeriod [
NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T
mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ;
static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T
mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits
[ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [
NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) {
mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ;
mdlTsMap [ i ] = i ; mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS ,
& mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , &
mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ;
ssSetTNextWasAdjustedPtr ( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ;
ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] ) ;
ssSetTimeOfNextSampleHitPtr ( rtS , & mdlTimeOfNextSampleHit [ 0 ] ) ; }
ssSetSolverMode ( rtS , SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS ,
( ( void * ) & rtB ) ) ; ( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof
( B ) ) ; { int32_T i ; for ( i = 0 ; i < 9 ; i ++ ) { rtB . cx41wglw3j .
jvi14dsw1h [ i ] = ( 0LL ) ; } for ( i = 0 ; i < 9 ; i ++ ) { rtB .
jjob4ur221 . jvi14dsw1h [ i ] = ( 0LL ) ; } for ( i = 0 ; i < 9 ; i ++ ) {
rtB . jogryxdnkz . jvi14dsw1h [ i ] = ( 0LL ) ; } for ( i = 0 ; i < 9 ; i ++
) { rtB . n4cqr1dkmr . jvi14dsw1h [ i ] = ( 0LL ) ; } for ( i = 0 ; i < 9 ; i
++ ) { rtB . a13lr3lsi3 . jvi14dsw1h [ i ] = ( 0LL ) ; } for ( i = 0 ; i < 9
; i ++ ) { rtB . jjajpmoyel . jvi14dsw1h [ i ] = ( 0LL ) ; } for ( i = 0 ; i
< 9 ; i ++ ) { rtB . ndmeqad3sm . jvi14dsw1h [ i ] = ( 0LL ) ; } for ( i = 0
; i < 9 ; i ++ ) { rtB . o0tbmhvpds . jvi14dsw1h [ i ] = ( 0LL ) ; } for ( i
= 0 ; i < 9 ; i ++ ) { rtB . f5mkygzljka . jvi14dsw1h [ i ] = ( 0LL ) ; } rtB
. cx41wglw3j . kehk5h5kaa = ( 0LL ) ; rtB . jjob4ur221 . kehk5h5kaa = ( 0LL )
; rtB . jogryxdnkz . kehk5h5kaa = ( 0LL ) ; rtB . n4cqr1dkmr . kehk5h5kaa = (
0LL ) ; rtB . a13lr3lsi3 . kehk5h5kaa = ( 0LL ) ; rtB . jjajpmoyel .
kehk5h5kaa = ( 0LL ) ; rtB . ndmeqad3sm . kehk5h5kaa = ( 0LL ) ; rtB .
o0tbmhvpds . kehk5h5kaa = ( 0LL ) ; rtB . f5mkygzljka . kehk5h5kaa = ( 0LL )
; } } { real_T * x = ( real_T * ) & rtX ; ssSetContStates ( rtS , x ) ; (
void ) memset ( ( void * ) x , 0 , sizeof ( X ) ) ; } { void * dwork = ( void
* ) & rtDW ; ssSetRootDWork ( rtS , dwork ) ; ( void ) memset ( dwork , 0 ,
sizeof ( DW ) ) ; } { static DataTypeTransInfo dtInfo ; ( void ) memset ( (
char_T * ) & dtInfo , 0 , sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS ,
& dtInfo ) ; dtInfo . numDataTypes = 37 ; dtInfo . dataTypeSizes = &
rtDataTypeSizes [ 0 ] ; dtInfo . dataTypeNames = & rtDataTypeNames [ 0 ] ;
dtInfo . BTransTable = & rtBTransTable ; dtInfo . PTransTable = &
rtPTransTable ; dtInfo . dataTypeInfoTable = rtDataTypeInfoTable ; }
uz_drive_model_InitializeDataMapInfo ( ) ; ssSetIsRapidAcceleratorActive (
rtS , true ) ; ssSetRootSS ( rtS , rtS ) ; ssSetVersion ( rtS ,
SIMSTRUCT_VERSION_LEVEL2 ) ; ssSetModelName ( rtS , "uz_drive_model" ) ;
ssSetPath ( rtS , "uz_drive_model" ) ; ssSetTStart ( rtS , 0.0 ) ;
ssSetTFinal ( rtS , 0.8 ) ; ssSetStepSize ( rtS , 2.0E-9 ) ;
ssSetFixedStepSize ( rtS , 2.0E-9 ) ; { static RTWLogInfo rt_DataLoggingInfo
; rt_DataLoggingInfo . loggingInterval = ( NULL ) ; ssSetRTWLogInfo ( rtS , &
rt_DataLoggingInfo ) ; } { { static int_T rt_LoggedStateWidths [ ] = { 1 , 1
, 3 , 3 , 3 , 3 , 3 , 3 , 1 , 3 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 3 , 3 , 1 , 3 ,
3 , 3 , 3 , 3 , 3 , 3 , 6 , 6 , 3 , 3 , 3 , 1 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6
, 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 3 , 6 , 6 , 6 , 3 , 6 , 6 , 6 , 6 , 6 ,
6 , 6 , 6 , 6 , 6 , 6 , 1 , 3 , 1 , 6 , 6 , 6 , 6 , 54 , 6 , 6 , 6 , 6 , 6 ,
6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 1 , 3 , 6 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3
, 3 , 3 , 3 , 3 , 6 , 1 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 9 , 6 , 15 , 6
, 9 , 6 , 36 , 6 , 27 , 27 , 6 , 3 , 6 , 36 , 39 , 18 , 6 , 6 , 6 , 6 , 6 , 6
, 6 , 6 , 6 , 6 , 8 , 8 , 18 , 18 , 18 , 8 , 18 , 57 , 60 , 60 , 8 , 1 , 1 ,
1 , 1 , 8 , 8 , 18 , 18 , 18 , 12 , 12 , 40 , 12 , 12 , 40 , 12 , 12 , 40 , 2
, 6 , 2 , 6 , 6 , 6 , 3 , 3 , 3 , 3 , 3 , 3 , 1 , 54 , 1 , 3 , 3 , 3 , 1 , 1
, 1 , 1 , 1 , 3 , 1 , 18 , 60 , 8 , 1 , 5 , 5 , 1 , 5 , 5 , 1 , 5 , 5 , 1 , 1
, 1 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 1 , 1 , 1 , 1 , 1 , 1 } ; static
int_T rt_LoggedStateNumDimensions [ ] = { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1
, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1
, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1
, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1
, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1
, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1
} ; static int_T rt_LoggedStateDimensions [ ] = { 1 , 1 , 3 , 3 , 3 , 3 , 3 ,
3 , 1 , 3 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 3 , 3 , 1 , 3 , 3 , 3 , 3 , 3 , 3 , 3
, 6 , 6 , 3 , 3 , 3 , 1 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 ,
6 , 6 , 6 , 6 , 3 , 6 , 6 , 6 , 3 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6
, 1 , 3 , 1 , 6 , 6 , 6 , 6 , 54 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6
, 6 , 6 , 6 , 1 , 3 , 6 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 6 ,
1 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 9 , 6 , 15 , 6 , 9 , 6 , 36 , 6 , 27
, 27 , 6 , 3 , 6 , 36 , 39 , 18 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 8 ,
8 , 18 , 18 , 18 , 8 , 18 , 57 , 60 , 60 , 8 , 1 , 1 , 1 , 1 , 8 , 8 , 18 ,
18 , 18 , 12 , 12 , 40 , 12 , 12 , 40 , 12 , 12 , 40 , 2 , 6 , 2 , 6 , 6 , 6
, 3 , 3 , 3 , 3 , 3 , 3 , 1 , 54 , 1 , 3 , 3 , 3 , 1 , 1 , 1 , 1 , 1 , 3 , 1
, 18 , 60 , 8 , 1 , 5 , 5 , 1 , 5 , 5 , 1 , 5 , 5 , 1 , 1 , 1 , 8 , 8 , 8 , 8
, 8 , 8 , 8 , 8 , 8 , 1 , 1 , 1 , 1 , 1 , 1 } ; static boolean_T
rt_LoggedStateIsVarDims [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ;
static BuiltInDTypeId rt_LoggedStateDataTypeIds [ ] = { SS_DOUBLE , SS_DOUBLE
, SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_UINT16 , SS_UINT8 , SS_UINT8 , SS_UINT8 , SS_BOOLEAN , SS_BOOLEAN ,
SS_BOOLEAN , SS_BOOLEAN , SS_BOOLEAN , SS_BOOLEAN , SS_BOOLEAN , SS_BOOLEAN ,
SS_BOOLEAN , SS_BOOLEAN , SS_BOOLEAN , SS_BOOLEAN , SS_BOOLEAN , SS_BOOLEAN ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE } ;
static int_T rt_LoggedStateComplexSignals [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 } ; static RTWPreprocessingFcnPtr rt_LoggingStatePreprocessingFcnPtrs
[ ] = { ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) } ; static const char_T * rt_LoggedStateLabels [ ] = { "CSTATE" ,
"CSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" } ; static
const char_T * rt_LoggedStateBlockNames [ ] = {
 "uz_drive_model/Subsystem8/Subsystem2/PID Controller2/Integrator/Continuous/Integrator"
,
 "uz_drive_model/Subsystem8/Subsystem3/PID Controller2/Integrator/Continuous/Integrator"
, "uz_drive_model/Unit Delay" , "uz_drive_model/Unit Delay1" ,
"uz_drive_model/Unit Delay3" ,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion3/Data Type Conversion3_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion11/Data Type Conversion11_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion12/Data Type Conversion12_pd1"
, "uz_drive_model/uz_pmsm_model_9ph/crp_out_delay1" ,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion14/Data Type Conversion14_pd1"
, "uz_drive_model/uz_pmsm_model_9ph/crp_out_delay5" ,
"uz_drive_model/uz_pmsm_model_9ph/crp_out_delay6" ,
"uz_drive_model/uz_pmsm_model_9ph/crp_out_delay7" ,
"uz_drive_model/uz_pmsm_model_9ph/crp_out_delay8" ,
"uz_drive_model/uz_pmsm_model_9ph/crp_out_delay9" ,
"uz_drive_model/uz_pmsm_model_9ph/crp_out_delay10" ,
"uz_drive_model/uz_pmsm_model_9ph/crp_out_delay11" ,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion21/Data Type Conversion21_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion22/Data Type Conversion22_pd1"
, "uz_drive_model/uz_pmsm_model_9ph/crp_out_delay3" ,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion24/Data Type Conversion24_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion25/Data Type Conversion25_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion26/Data Type Conversion26_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion27/Data Type Conversion27_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion28/Data Type Conversion28_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion29/Data Type Conversion29_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion30/Data Type Conversion30_pd1"
, "uz_drive_model/uz_pmsm_model_9ph/Product6/Product6_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Product5/Product5_pd1" ,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion33/Data Type Conversion33_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion331/Data Type Conversion331_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion5/Data Type Conversion5_pd1"
, "uz_drive_model/uz_pmsm_model_9ph/crp_out_delay2" ,
"uz_drive_model/uz_pmsm_model_9ph/Sum1_stage3/Sum1_stage3_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Gain/Gain_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Gain1/Gain1_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Sum_stage3/Sum_stage3_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Gain2/Gain2_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Gain3/Gain3_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Gain4/Gain4_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Gain5/Gain5_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Gain6/Gain6_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Gain7/Gain7_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Gain8/Gain8_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Gain9/Gain9_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Product10/Product10_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Product/Product_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Product1/Product1_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch18" ,
"uz_drive_model/uz_pmsm_model_9ph/Sum2/Sum2_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch16" ,
"uz_drive_model/uz_pmsm_model_9ph/Product7/Product7_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Product8/Product8_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Sum1_stage2/Sum1_stage2_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch17" ,
"uz_drive_model/uz_pmsm_model_9ph/Sum3/Sum3_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Sum31/Sum31_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Sum310/Sum310_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Sum32/Sum32_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Sum34/Sum34_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Sum35/Sum35_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Sum36/Sum36_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Sum37/Sum37_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Sum38/Sum38_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Sum39/Sum39_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Sum_stage2/Sum_stage2_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Theta_el/delayMatch1" ,
 "uz_drive_model/uz_pmsm_model_9ph/Theta_el/Data Type Conversion2/Data Type Conversion2_pd1"
, "uz_drive_model/uz_pmsm_model_9ph/Theta_el/crp_out_delay" ,
"uz_drive_model/uz_pmsm_model_9ph/Theta_el/Gain/Gain_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Theta_el/Sum3/Sum3_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Transformation/Add/Add_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Transformation/Add1/Add1_pd1" ,
 "uz_drive_model/uz_pmsm_model_9ph/Transformation/Data Type Conversion39/Data Type Conversion39_pd1"
, "uz_drive_model/uz_pmsm_model_9ph/Divide/Divide_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Add/Add_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Divide2/Divide2_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Add1/Add1_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Divide4/Divide4_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Add2/Add2_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Divide6/Divide6_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Add3/Add3_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Divide8/Divide8_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Add4/Add4_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Divide10/Divide10_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Add5/Add5_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Divide12/Divide12_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Add6/Add6_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Theta_el/delayMatch2" ,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion13/Data Type Conversion13_pd1"
, "uz_drive_model/uz_pmsm_model_9ph/Product11/Product11_pd1" ,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion141/Data Type Conversion141_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion15/Data Type Conversion15_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion16/Data Type Conversion16_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion17/Data Type Conversion17_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion18/Data Type Conversion18_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion19/Data Type Conversion19_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion20/Data Type Conversion20_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion23/Data Type Conversion23_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion31/Data Type Conversion31_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion32/Data Type Conversion32_pd1"
,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion8/Data Type Conversion8_pd1"
, "uz_drive_model/uz_pmsm_model_9ph/delayMatch15" ,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion37/Data Type Conversion37_pd1"
, "uz_drive_model/uz_pmsm_model_9ph/crp_out_delay4" ,
"uz_drive_model/uz_pmsm_model_9ph/Divide1/Divide1_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Divide11/Divide11_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Divide13/Divide13_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Divide3/Divide3_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Divide5/Divide5_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Divide7/Divide7_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Divide9/Divide9_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Sum33/Sum33_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Factor/Factor_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Mux_out1" ,
"uz_drive_model/uz_pmsm_model_9ph/Sum1/Sum1_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch20" ,
"uz_drive_model/uz_pmsm_model_9ph/Product2/Product2_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch19" ,
"uz_drive_model/uz_pmsm_model_9ph/Product3/Product3_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch22" ,
"uz_drive_model/uz_pmsm_model_9ph/Product9/Product9_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Sin_to_sincos/Sin_to_sincos_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Sin_to_sincos/Sin_to_sincos_pd2" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch21" ,
 "uz_drive_model/uz_pmsm_model_9ph/Theta_el/Data Type Conversion1/Data Type Conversion1_pd1"
, "uz_drive_model/uz_pmsm_model_9ph/Theta_el/Divide/Divide_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch23" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch26" ,
"uz_drive_model/uz_pmsm_model_9ph/Theta_el/delayMatch" ,
"uz_drive_model/uz_pmsm_model_9ph/Transformation/Divide/Divide_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Transformation/Divide1/Divide1_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Transformation/Divide3/Divide3_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Transformation/Divide2/Divide2_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Transformation1/Divide/Divide_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Transformation1/Divide1/Divide1_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Transformation1/Add/Add_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Transformation1/Divide2/Divide2_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Transformation1/Divide3/Divide3_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/Transformation1/Add1/Add1_pd1" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch1" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch10" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch12" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch13" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch2" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch24" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch25" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch28" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch29" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch3" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch30" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch31" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch33" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch34" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch5" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch6" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch7" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch8" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch9" ,
"uz_drive_model/uz_inverter_3ph2/HDL Subsystem/HDL Algorithm/State Delay" ,
 "uz_drive_model/uz_inverter_3ph2/HDL Subsystem/HDL Algorithm/Mode Iteration Manager/Delay3"
, "uz_drive_model/uz_inverter_3ph2/HDL Subsystem/HDL Algorithm/Delay1" ,
"uz_drive_model/uz_inverter_3ph1/HDL Subsystem/HDL Algorithm/State Delay" ,
 "uz_drive_model/uz_inverter_3ph1/HDL Subsystem/HDL Algorithm/Mode Iteration Manager/Delay3"
, "uz_drive_model/uz_inverter_3ph1/HDL Subsystem/HDL Algorithm/Delay1" ,
"uz_drive_model/uz_inverter_3ph/HDL Subsystem/HDL Algorithm/State Delay" ,
 "uz_drive_model/uz_inverter_3ph/HDL Subsystem/HDL Algorithm/Mode Iteration Manager/Delay3"
, "uz_drive_model/uz_inverter_3ph/HDL Subsystem/HDL Algorithm/Delay1" ,
"uz_drive_model/Delay" ,
 "uz_drive_model/uz_pmsm_model_9ph/Data Type Conversion1/Data Type Conversion1_pd1"
, "uz_drive_model/uz_pmsm_model_9ph/Delay1" ,
"uz_drive_model/uz_pmsm_model_9ph/Delay" ,
"uz_drive_model/uz_pmsm_model_9ph/Delay2" ,
"uz_drive_model/uz_pmsm_model_9ph/Delay3" ,
"uz_drive_model/uz_pmsm_model_9ph/Delay4" ,
"uz_drive_model/uz_pmsm_model_9ph/crp_out_delay12" ,
"uz_drive_model/uz_pmsm_model_9ph/Delay5" ,
"uz_drive_model/uz_pmsm_model_9ph/crp_out_delay13" ,
"uz_drive_model/uz_pmsm_model_9ph/Delay6" ,
"uz_drive_model/uz_pmsm_model_9ph/crp_out_delay14" ,
"uz_drive_model/uz_pmsm_model_9ph/crp_out_delay" ,
 "uz_drive_model/uz_pmsm_model_9ph/Transformation1/Data Type Conversion28/Data Type Conversion28_pd1"
, "uz_drive_model/uz_pmsm_model_9ph/delay" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch35" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch36" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch37" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch38" ,
"uz_drive_model/uz_pmsm_model_9ph/ctr_499/Output" ,
 "uz_drive_model/uz_inverter_3ph2/HDL Subsystem/HDL Algorithm/Mode Iteration Manager/Counter Limited/Output"
,
 "uz_drive_model/uz_inverter_3ph1/HDL Subsystem/HDL Algorithm/Mode Iteration Manager/Counter Limited/Output"
,
 "uz_drive_model/uz_inverter_3ph/HDL Subsystem/HDL Algorithm/Mode Iteration Manager/Counter Limited/Output"
, "uz_drive_model/uz_pmsm_model_9ph/delayMatch14" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch32" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch11" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch27" ,
"uz_drive_model/uz_pmsm_model_9ph/delayMatch4" ,
 "uz_drive_model/uz_inverter_3ph2/HDL Subsystem/HDL Algorithm/Mode Iteration Manager/Delay"
,
 "uz_drive_model/uz_inverter_3ph2/HDL Subsystem/HDL Algorithm/Mode Iteration Manager/Delay2"
,
 "uz_drive_model/uz_inverter_3ph2/HDL Subsystem/HDL Algorithm/Mode Iteration Manager/Delay1"
,
 "uz_drive_model/uz_inverter_3ph1/HDL Subsystem/HDL Algorithm/Mode Iteration Manager/Delay"
,
 "uz_drive_model/uz_inverter_3ph1/HDL Subsystem/HDL Algorithm/Mode Iteration Manager/Delay2"
,
 "uz_drive_model/uz_inverter_3ph1/HDL Subsystem/HDL Algorithm/Mode Iteration Manager/Delay1"
,
 "uz_drive_model/uz_inverter_3ph/HDL Subsystem/HDL Algorithm/Mode Iteration Manager/Delay"
,
 "uz_drive_model/uz_inverter_3ph/HDL Subsystem/HDL Algorithm/Mode Iteration Manager/Delay2"
,
 "uz_drive_model/uz_inverter_3ph/HDL Subsystem/HDL Algorithm/Mode Iteration Manager/Delay1"
, "uz_drive_model/uz_inverter_3ph2/HDL Subsystem/HDL Algorithm/Delay" ,
"uz_drive_model/uz_inverter_3ph1/HDL Subsystem/HDL Algorithm/Delay" ,
"uz_drive_model/uz_inverter_3ph/HDL Subsystem/HDL Algorithm/Delay" ,
 "uz_drive_model/uz_pmsm_model_9ph/Transformation1/Transformation1_MAC8/PipelineRegister"
,
 "uz_drive_model/uz_pmsm_model_9ph/Transformation1/Transformation1_MAC7/PipelineRegister"
,
 "uz_drive_model/uz_pmsm_model_9ph/Transformation1/Transformation1_MAC6/PipelineRegister"
,
 "uz_drive_model/uz_pmsm_model_9ph/Transformation1/Transformation1_MAC5/PipelineRegister"
,
 "uz_drive_model/uz_pmsm_model_9ph/Transformation1/Transformation1_MAC4/PipelineRegister"
,
 "uz_drive_model/uz_pmsm_model_9ph/Transformation1/Transformation1_MAC3/PipelineRegister"
,
 "uz_drive_model/uz_pmsm_model_9ph/Transformation1/Transformation1_MAC2/PipelineRegister"
,
 "uz_drive_model/uz_pmsm_model_9ph/Transformation1/Transformation1_MAC1/PipelineRegister"
,
 "uz_drive_model/uz_pmsm_model_9ph/Transformation1/Transformation1_MAC/PipelineRegister"
,
 "uz_drive_model/Subsystem2/SVPWM Generator\n(2-Level)/Model/SV Modulator\nPattern #2/Triangle\nGenerator/Model/Unit Delay"
,
 "uz_drive_model/Subsystem2/SVPWM Generator\n(2-Level)/Model/SV Modulator\nPattern #1/Generate \npulse pattern/Determine interval of the\nPWM period based on\nTa Tb and To/Sawtooth\nGenerator/Model/Unit Delay"
,
 "uz_drive_model/Subsystem1/SVPWM Generator\n(2-Level)/Model/SV Modulator\nPattern #2/Triangle\nGenerator/Model/Unit Delay"
,
 "uz_drive_model/Subsystem1/SVPWM Generator\n(2-Level)/Model/SV Modulator\nPattern #1/Generate \npulse pattern/Determine interval of the\nPWM period based on\nTa Tb and To/Sawtooth\nGenerator/Model/Unit Delay"
,
 "uz_drive_model/Subsystem/SVPWM Generator\n(2-Level)/Model/SV Modulator\nPattern #2/Triangle\nGenerator/Model/Unit Delay"
,
 "uz_drive_model/Subsystem/SVPWM Generator\n(2-Level)/Model/SV Modulator\nPattern #1/Generate \npulse pattern/Determine interval of the\nPWM period based on\nTa Tb and To/Sawtooth\nGenerator/Model/Unit Delay"
} ; static const char_T * rt_LoggedStateNames [ ] = { "" , "" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" } ; static boolean_T
rt_LoggedStateCrossMdlRef [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ;
static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert [ ] = { { 0 , SS_DOUBLE
, SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 ,
0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 1 ,
SS_DOUBLE , SS_INT32 , 64 , 1 , 1 , 1.0 , - 12 , 0.0 } , { 1 , SS_DOUBLE ,
SS_INT32 , 64 , 1 , 1 , 1.0 , - 12 , 0.0 } , { 1 , SS_DOUBLE , SS_INT32 , 64
, 1 , 1 , 1.0 , - 12 , 0.0 } , { 1 , SS_DOUBLE , SS_INT32 , 64 , 1 , 1 , 1.0
, - 12 , 0.0 } , { 1 , SS_DOUBLE , SS_INT32 , 64 , 1 , 1 , 1.0 , - 12 , 0.0 }
, { 1 , SS_DOUBLE , SS_INT32 , 64 , 1 , 1 , 1.0 , - 12 , 0.0 } , { 1 ,
SS_DOUBLE , SS_INT32 , 64 , 1 , 1 , 1.0 , - 12 , 0.0 } , { 1 , SS_DOUBLE ,
SS_INT32 , 64 , 1 , 1 , 1.0 , - 12 , 0.0 } , { 1 , SS_DOUBLE , SS_INT32 , 64
, 1 , 1 , 1.0 , - 12 , 0.0 } , { 1 , SS_DOUBLE , SS_INT32 , 64 , 1 , 1 , 1.0
, - 12 , 0.0 } , { 1 , SS_DOUBLE , SS_INT32 , 64 , 1 , 1 , 1.0 , - 12 , 0.0 }
, { 1 , SS_DOUBLE , SS_INT32 , 64 , 1 , 1 , 1.0 , - 12 , 0.0 } , { 1 ,
SS_DOUBLE , SS_INT32 , 64 , 1 , 1 , 1.0 , - 12 , 0.0 } , { 1 , SS_DOUBLE ,
SS_INT32 , 64 , 1 , 1 , 1.0 , - 12 , 0.0 } , { 1 , SS_DOUBLE , SS_INT32 , 64
, 1 , 1 , 1.0 , - 12 , 0.0 } , { 1 , SS_DOUBLE , SS_INT32 , 64 , 1 , 1 , 1.0
, - 12 , 0.0 } , { 1 , SS_DOUBLE , SS_INT32 , 64 , 1 , 1 , 1.0 , - 12 , 0.0 }
, { 1 , SS_DOUBLE , SS_INT32 , 64 , 1 , 1 , 1.0 , - 12 , 0.0 } , { 1 ,
SS_DOUBLE , SS_INT32 , 64 , 1 , 1 , 1.0 , - 12 , 0.0 } , { 0 , SS_UINT16 ,
SS_UINT16 , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_UINT8 , SS_UINT8 , 0 , 0 ,
0 , 1.0 , 0 , 0.0 } , { 0 , SS_UINT8 , SS_UINT8 , 0 , 0 , 0 , 1.0 , 0 , 0.0 }
, { 0 , SS_UINT8 , SS_UINT8 , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_BOOLEAN
, SS_BOOLEAN , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_BOOLEAN , SS_BOOLEAN ,
0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_BOOLEAN , SS_BOOLEAN , 0 , 0 , 0 , 1.0
, 0 , 0.0 } , { 0 , SS_BOOLEAN , SS_BOOLEAN , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , {
0 , SS_BOOLEAN , SS_BOOLEAN , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_BOOLEAN
, SS_BOOLEAN , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_BOOLEAN , SS_BOOLEAN ,
0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_BOOLEAN , SS_BOOLEAN , 0 , 0 , 0 , 1.0
, 0 , 0.0 } , { 0 , SS_BOOLEAN , SS_BOOLEAN , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , {
0 , SS_BOOLEAN , SS_BOOLEAN , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_BOOLEAN
, SS_BOOLEAN , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_BOOLEAN , SS_BOOLEAN ,
0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_BOOLEAN , SS_BOOLEAN , 0 , 0 , 0 , 1.0
, 0 , 0.0 } , { 0 , SS_BOOLEAN , SS_BOOLEAN , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , {
1 , SS_DOUBLE , SS_UINT8 , 64 , 1 , 0 , 1.0 , 0 , 0.0 } , { 1 , SS_DOUBLE ,
SS_UINT8 , 64 , 1 , 0 , 1.0 , 0 , 0.0 } , { 1 , SS_DOUBLE , SS_UINT8 , 64 , 1
, 0 , 1.0 , 0 , 0.0 } , { 1 , SS_DOUBLE , SS_INT64 , 64 , 1 , 1 , 1.0 , - 28
, 0.0 } , { 1 , SS_DOUBLE , SS_INT64 , 64 , 1 , 1 , 1.0 , - 28 , 0.0 } , { 1
, SS_DOUBLE , SS_INT64 , 64 , 1 , 1 , 1.0 , - 28 , 0.0 } , { 1 , SS_DOUBLE ,
SS_INT64 , 64 , 1 , 1 , 1.0 , - 28 , 0.0 } , { 1 , SS_DOUBLE , SS_INT64 , 64
, 1 , 1 , 1.0 , - 28 , 0.0 } , { 1 , SS_DOUBLE , SS_INT64 , 64 , 1 , 1 , 1.0
, - 28 , 0.0 } , { 1 , SS_DOUBLE , SS_INT64 , 64 , 1 , 1 , 1.0 , - 28 , 0.0 }
, { 1 , SS_DOUBLE , SS_INT64 , 64 , 1 , 1 , 1.0 , - 28 , 0.0 } , { 1 ,
SS_DOUBLE , SS_INT64 , 64 , 1 , 1 , 1.0 , - 28 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } } ; static int_T
rt_LoggedStateIdxList [ ] = { 0 , 1 , 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 ,
10 , 11 , 12 , 13 , 14 , 15 , 16 , 17 , 18 , 19 , 20 , 21 , 22 , 23 , 24 , 25
, 26 , 27 , 28 , 29 , 30 , 31 , 32 , 33 , 34 , 35 , 36 , 37 , 38 , 39 , 40 ,
41 , 42 , 43 , 44 , 45 , 46 , 47 , 48 , 49 , 50 , 51 , 52 , 53 , 54 , 55 , 56
, 57 , 58 , 59 , 60 , 61 , 62 , 63 , 64 , 65 , 66 , 67 , 68 , 162 , 163 , 164
, 165 , 166 , 167 , 168 , 169 , 170 , 171 , 172 , 173 , 174 , 175 , 176 , 177
, 178 , 179 , 180 , 181 , 182 , 183 , 184 , 185 , 186 , 187 , 188 , 189 , 190
, 191 , 192 , 193 , 194 , 195 , 196 , 197 , 198 , 199 , 200 , 201 , 202 , 203
, 204 , 205 , 206 , 207 , 208 , 209 , 210 , 211 , 212 , 213 , 214 , 215 , 216
, 217 , 218 , 219 , 220 , 221 , 222 , 223 , 224 , 225 , 226 , 227 , 228 , 229
, 230 , 231 , 232 , 233 , 234 , 235 , 236 , 237 , 238 , 239 , 240 , 241 , 242
, 243 , 244 , 245 , 246 , 247 , 248 , 249 , 250 , 251 , 252 , 253 , 254 , 255
, 256 , 257 , 258 , 259 , 260 , 261 , 262 , 263 , 264 , 265 , 266 , 267 , 268
, 269 , 270 , 271 , 272 , 273 , 274 , 275 , 276 , 277 , 278 , 313 , 314 , 315
, 316 , 317 , 318 , 319 , 320 , 321 , 322 , 323 , 324 , 325 , 326 , 327 , 328
, 329 , 330 , 331 , 332 , 333 , 353 , 355 , 357 , 359 , 361 , 363 , 365 , 367
, 369 , 371 , 380 , 386 , 395 , 401 , 410 } ; static RTWLogSignalInfo
rt_LoggedStateSignalInfo = { 224 , rt_LoggedStateWidths ,
rt_LoggedStateNumDimensions , rt_LoggedStateDimensions ,
rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) , rt_LoggedStateDataTypeIds ,
rt_LoggedStateComplexSignals , ( NULL ) , rt_LoggingStatePreprocessingFcnPtrs
, { rt_LoggedStateLabels } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedStateBlockNames } , { rt_LoggedStateNames } ,
rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert , rt_LoggedStateIdxList
} ; static void * rt_LoggedStateSignalPtrs [ 224 ] ; rtliSetLogXSignalPtrs (
ssGetRTWLogInfo ( rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) & rtX . ptze3ue0cm ;
rt_LoggedStateSignalPtrs [ 1 ] = ( void * ) & rtX . flellzbl1y ;
rt_LoggedStateSignalPtrs [ 2 ] = ( void * ) rtDW . ituktxufmb ;
rt_LoggedStateSignalPtrs [ 3 ] = ( void * ) rtDW . epsbkv53pu ;
rt_LoggedStateSignalPtrs [ 4 ] = ( void * ) rtDW . cmh2vel5ym ;
rt_LoggedStateSignalPtrs [ 5 ] = ( void * ) rtDW . miazophk3q ;
rt_LoggedStateSignalPtrs [ 6 ] = ( void * ) rtDW . cnrqogla5d ;
rt_LoggedStateSignalPtrs [ 7 ] = ( void * ) rtDW . aanjcgvfa0 ;
rt_LoggedStateSignalPtrs [ 8 ] = ( void * ) & rtDW . aoxcwu3qll ;
rt_LoggedStateSignalPtrs [ 9 ] = ( void * ) rtDW . gnh32qpzkl ;
rt_LoggedStateSignalPtrs [ 10 ] = ( void * ) & rtDW . ihfcziqcgk ;
rt_LoggedStateSignalPtrs [ 11 ] = ( void * ) & rtDW . eahq4k0qba ;
rt_LoggedStateSignalPtrs [ 12 ] = ( void * ) & rtDW . oo31woulsl ;
rt_LoggedStateSignalPtrs [ 13 ] = ( void * ) & rtDW . blhgrykwvp ;
rt_LoggedStateSignalPtrs [ 14 ] = ( void * ) & rtDW . osqohvejno ;
rt_LoggedStateSignalPtrs [ 15 ] = ( void * ) & rtDW . cvcfermial ;
rt_LoggedStateSignalPtrs [ 16 ] = ( void * ) & rtDW . ocn3tuy1mq ;
rt_LoggedStateSignalPtrs [ 17 ] = ( void * ) rtDW . lzrfskvb50 ;
rt_LoggedStateSignalPtrs [ 18 ] = ( void * ) rtDW . kxzyyq15r0 ;
rt_LoggedStateSignalPtrs [ 19 ] = ( void * ) & rtDW . jfrl3cqm1n ;
rt_LoggedStateSignalPtrs [ 20 ] = ( void * ) rtDW . ayahx5voca ;
rt_LoggedStateSignalPtrs [ 21 ] = ( void * ) rtDW . l2zkdqsp2y ;
rt_LoggedStateSignalPtrs [ 22 ] = ( void * ) rtDW . lxk5izw00o ;
rt_LoggedStateSignalPtrs [ 23 ] = ( void * ) rtDW . cqp1dau03w ;
rt_LoggedStateSignalPtrs [ 24 ] = ( void * ) rtDW . gfiovjo3e2 ;
rt_LoggedStateSignalPtrs [ 25 ] = ( void * ) rtDW . p2iwsajmfp ;
rt_LoggedStateSignalPtrs [ 26 ] = ( void * ) rtDW . b4auxd1lsk ;
rt_LoggedStateSignalPtrs [ 27 ] = ( void * ) rtDW . al5aajfx21 ;
rt_LoggedStateSignalPtrs [ 28 ] = ( void * ) rtDW . gt3chc0tga ;
rt_LoggedStateSignalPtrs [ 29 ] = ( void * ) rtDW . erukb0glgz ;
rt_LoggedStateSignalPtrs [ 30 ] = ( void * ) rtDW . pdjkbbbzjq ;
rt_LoggedStateSignalPtrs [ 31 ] = ( void * ) rtDW . pml0yl52te ;
rt_LoggedStateSignalPtrs [ 32 ] = ( void * ) & rtDW . eswvf4pz4v ;
rt_LoggedStateSignalPtrs [ 33 ] = ( void * ) rtDW . phidvr4lhk ;
rt_LoggedStateSignalPtrs [ 34 ] = ( void * ) rtDW . atdfcebxbc ;
rt_LoggedStateSignalPtrs [ 35 ] = ( void * ) rtDW . o3sgmp4aev ;
rt_LoggedStateSignalPtrs [ 36 ] = ( void * ) rtDW . nld3uzo5io ;
rt_LoggedStateSignalPtrs [ 37 ] = ( void * ) rtDW . fi4wuwmktb ;
rt_LoggedStateSignalPtrs [ 38 ] = ( void * ) rtDW . gm4ivysliu ;
rt_LoggedStateSignalPtrs [ 39 ] = ( void * ) rtDW . pyurk4he1k ;
rt_LoggedStateSignalPtrs [ 40 ] = ( void * ) rtDW . ocff1ayzzn ;
rt_LoggedStateSignalPtrs [ 41 ] = ( void * ) rtDW . l0rzviqodi ;
rt_LoggedStateSignalPtrs [ 42 ] = ( void * ) rtDW . o0qik01ouq ;
rt_LoggedStateSignalPtrs [ 43 ] = ( void * ) rtDW . jci52usrwf ;
rt_LoggedStateSignalPtrs [ 44 ] = ( void * ) rtDW . n0ifswwd21 ;
rt_LoggedStateSignalPtrs [ 45 ] = ( void * ) rtDW . enqlcsixk2 ;
rt_LoggedStateSignalPtrs [ 46 ] = ( void * ) rtDW . bq4gap0f1m ;
rt_LoggedStateSignalPtrs [ 47 ] = ( void * ) rtDW . lfuv5ipyfs ;
rt_LoggedStateSignalPtrs [ 48 ] = ( void * ) rtDW . hjbvl0tg45 ;
rt_LoggedStateSignalPtrs [ 49 ] = ( void * ) rtDW . nyxm5sdvcd ;
rt_LoggedStateSignalPtrs [ 50 ] = ( void * ) rtDW . f0lbp4tqqn ;
rt_LoggedStateSignalPtrs [ 51 ] = ( void * ) rtDW . fva2rmvmh4 ;
rt_LoggedStateSignalPtrs [ 52 ] = ( void * ) rtDW . hdlc0qsc4w ;
rt_LoggedStateSignalPtrs [ 53 ] = ( void * ) rtDW . fl4tijqsrl ;
rt_LoggedStateSignalPtrs [ 54 ] = ( void * ) rtDW . mxawq0evig ;
rt_LoggedStateSignalPtrs [ 55 ] = ( void * ) rtDW . e1vdezejb0 ;
rt_LoggedStateSignalPtrs [ 56 ] = ( void * ) rtDW . nrq4usubsl ;
rt_LoggedStateSignalPtrs [ 57 ] = ( void * ) rtDW . omuzgpsf1f ;
rt_LoggedStateSignalPtrs [ 58 ] = ( void * ) rtDW . hys0om0qbu ;
rt_LoggedStateSignalPtrs [ 59 ] = ( void * ) rtDW . nr5d4vqt4t ;
rt_LoggedStateSignalPtrs [ 60 ] = ( void * ) rtDW . cnk414y00k ;
rt_LoggedStateSignalPtrs [ 61 ] = ( void * ) rtDW . fnpjhtoie0 ;
rt_LoggedStateSignalPtrs [ 62 ] = ( void * ) rtDW . frvvvscadt ;
rt_LoggedStateSignalPtrs [ 63 ] = ( void * ) rtDW . pfwwityzhm ;
rt_LoggedStateSignalPtrs [ 64 ] = ( void * ) rtDW . awvvdj3gzy ;
rt_LoggedStateSignalPtrs [ 65 ] = ( void * ) rtDW . esrssadyy0 ;
rt_LoggedStateSignalPtrs [ 66 ] = ( void * ) & rtDW . loh1yczrtr ;
rt_LoggedStateSignalPtrs [ 67 ] = ( void * ) rtDW . cayw42bvqq ;
rt_LoggedStateSignalPtrs [ 68 ] = ( void * ) & rtDW . fmhxej54hb ;
rt_LoggedStateSignalPtrs [ 69 ] = ( void * ) rtDW . fzberuaezs ;
rt_LoggedStateSignalPtrs [ 70 ] = ( void * ) rtDW . oiurtflkiv ;
rt_LoggedStateSignalPtrs [ 71 ] = ( void * ) rtDW . ixrsi3erhf ;
rt_LoggedStateSignalPtrs [ 72 ] = ( void * ) rtDW . jis1uepreo ;
rt_LoggedStateSignalPtrs [ 73 ] = ( void * ) rtDW . fwkxey5epo ;
rt_LoggedStateSignalPtrs [ 74 ] = ( void * ) rtDW . pnsuou2020 ;
rt_LoggedStateSignalPtrs [ 75 ] = ( void * ) rtDW . opg1thx2qw ;
rt_LoggedStateSignalPtrs [ 76 ] = ( void * ) rtDW . amalc3ffil ;
rt_LoggedStateSignalPtrs [ 77 ] = ( void * ) rtDW . mwenvz0tar ;
rt_LoggedStateSignalPtrs [ 78 ] = ( void * ) rtDW . de3otshxus ;
rt_LoggedStateSignalPtrs [ 79 ] = ( void * ) rtDW . i2ctd1awel ;
rt_LoggedStateSignalPtrs [ 80 ] = ( void * ) rtDW . ccf5juo5ya ;
rt_LoggedStateSignalPtrs [ 81 ] = ( void * ) rtDW . i4lkkodfyj ;
rt_LoggedStateSignalPtrs [ 82 ] = ( void * ) rtDW . mdvclm3wpb ;
rt_LoggedStateSignalPtrs [ 83 ] = ( void * ) rtDW . gai5nv42oe ;
rt_LoggedStateSignalPtrs [ 84 ] = ( void * ) rtDW . imfxseqvvv ;
rt_LoggedStateSignalPtrs [ 85 ] = ( void * ) rtDW . cxatkad2jz ;
rt_LoggedStateSignalPtrs [ 86 ] = ( void * ) rtDW . ikxzuowx1v ;
rt_LoggedStateSignalPtrs [ 87 ] = ( void * ) rtDW . bg2vv1po0e ;
rt_LoggedStateSignalPtrs [ 88 ] = ( void * ) & rtDW . f4tcd4udur ;
rt_LoggedStateSignalPtrs [ 89 ] = ( void * ) rtDW . ctbynjdwij ;
rt_LoggedStateSignalPtrs [ 90 ] = ( void * ) rtDW . anfxf0zt2u ;
rt_LoggedStateSignalPtrs [ 91 ] = ( void * ) rtDW . afo0nwhxua ;
rt_LoggedStateSignalPtrs [ 92 ] = ( void * ) rtDW . jdtstycpmg ;
rt_LoggedStateSignalPtrs [ 93 ] = ( void * ) rtDW . g2ry4vjsj1 ;
rt_LoggedStateSignalPtrs [ 94 ] = ( void * ) rtDW . iehvrkddj2 ;
rt_LoggedStateSignalPtrs [ 95 ] = ( void * ) rtDW . nbavx35izv ;
rt_LoggedStateSignalPtrs [ 96 ] = ( void * ) rtDW . cl1vsftpzn ;
rt_LoggedStateSignalPtrs [ 97 ] = ( void * ) rtDW . lhojsnn24m ;
rt_LoggedStateSignalPtrs [ 98 ] = ( void * ) rtDW . d42pvxfz0g ;
rt_LoggedStateSignalPtrs [ 99 ] = ( void * ) rtDW . kovzbujdnb ;
rt_LoggedStateSignalPtrs [ 100 ] = ( void * ) rtDW . dttn4xmcnk ;
rt_LoggedStateSignalPtrs [ 101 ] = ( void * ) rtDW . n1ap5w5rdi ;
rt_LoggedStateSignalPtrs [ 102 ] = ( void * ) rtDW . ndb122ek3u ;
rt_LoggedStateSignalPtrs [ 103 ] = ( void * ) rtDW . hoesofthyy ;
rt_LoggedStateSignalPtrs [ 104 ] = ( void * ) & rtDW . ifur0qjdev ;
rt_LoggedStateSignalPtrs [ 105 ] = ( void * ) rtDW . h2z1m5wxiy ;
rt_LoggedStateSignalPtrs [ 106 ] = ( void * ) rtDW . dviol1u0jv ;
rt_LoggedStateSignalPtrs [ 107 ] = ( void * ) rtDW . df5ibuzfvl ;
rt_LoggedStateSignalPtrs [ 108 ] = ( void * ) rtDW . ikv4gqtanm ;
rt_LoggedStateSignalPtrs [ 109 ] = ( void * ) rtDW . hru10ym4o1 ;
rt_LoggedStateSignalPtrs [ 110 ] = ( void * ) rtDW . erp5nno2ec ;
rt_LoggedStateSignalPtrs [ 111 ] = ( void * ) rtDW . ima1cclrzn ;
rt_LoggedStateSignalPtrs [ 112 ] = ( void * ) rtDW . hm24hbgcg1 ;
rt_LoggedStateSignalPtrs [ 113 ] = ( void * ) rtDW . ob20xueupt ;
rt_LoggedStateSignalPtrs [ 114 ] = ( void * ) rtDW . emh5kwkq0f ;
rt_LoggedStateSignalPtrs [ 115 ] = ( void * ) rtDW . f3zvxiekpj ;
rt_LoggedStateSignalPtrs [ 116 ] = ( void * ) rtDW . dspkd5mdvs ;
rt_LoggedStateSignalPtrs [ 117 ] = ( void * ) rtDW . gmymeboquk ;
rt_LoggedStateSignalPtrs [ 118 ] = ( void * ) rtDW . bs1nmm0jpl ;
rt_LoggedStateSignalPtrs [ 119 ] = ( void * ) rtDW . bx5vsdt4mt ;
rt_LoggedStateSignalPtrs [ 120 ] = ( void * ) rtDW . ciaqlqmyyx ;
rt_LoggedStateSignalPtrs [ 121 ] = ( void * ) rtDW . e1kih03oaj ;
rt_LoggedStateSignalPtrs [ 122 ] = ( void * ) rtDW . m5gzgpvijm ;
rt_LoggedStateSignalPtrs [ 123 ] = ( void * ) rtDW . o3kxgyy1fj ;
rt_LoggedStateSignalPtrs [ 124 ] = ( void * ) rtDW . nkf0blmwkl ;
rt_LoggedStateSignalPtrs [ 125 ] = ( void * ) rtDW . h5lg5oz5ks ;
rt_LoggedStateSignalPtrs [ 126 ] = ( void * ) rtDW . hggmceleiv ;
rt_LoggedStateSignalPtrs [ 127 ] = ( void * ) rtDW . pdhtdmqeof ;
rt_LoggedStateSignalPtrs [ 128 ] = ( void * ) rtDW . i3xwoxj5zy ;
rt_LoggedStateSignalPtrs [ 129 ] = ( void * ) rtDW . lth0p1kskk ;
rt_LoggedStateSignalPtrs [ 130 ] = ( void * ) rtDW . ko0pv0nfnn ;
rt_LoggedStateSignalPtrs [ 131 ] = ( void * ) rtDW . kr1btzpdxw ;
rt_LoggedStateSignalPtrs [ 132 ] = ( void * ) rtDW . axidhoghf0 ;
rt_LoggedStateSignalPtrs [ 133 ] = ( void * ) rtDW . pqgou55kzx ;
rt_LoggedStateSignalPtrs [ 134 ] = ( void * ) rtDW . fuh3bn4ezo ;
rt_LoggedStateSignalPtrs [ 135 ] = ( void * ) rtDW . kzefheif0g ;
rt_LoggedStateSignalPtrs [ 136 ] = ( void * ) rtDW . aa2p00mqis ;
rt_LoggedStateSignalPtrs [ 137 ] = ( void * ) rtDW . pasm0mbp1y ;
rt_LoggedStateSignalPtrs [ 138 ] = ( void * ) rtDW . jqvl3ulori ;
rt_LoggedStateSignalPtrs [ 139 ] = ( void * ) rtDW . jez5q1v2di ;
rt_LoggedStateSignalPtrs [ 140 ] = ( void * ) rtDW . lr1nlrmqch ;
rt_LoggedStateSignalPtrs [ 141 ] = ( void * ) rtDW . a44d5qyg12 ;
rt_LoggedStateSignalPtrs [ 142 ] = ( void * ) rtDW . bwkcfpuwid ;
rt_LoggedStateSignalPtrs [ 143 ] = ( void * ) rtDW . cno1ak0c3c ;
rt_LoggedStateSignalPtrs [ 144 ] = ( void * ) rtDW . nxk0ojgi44 ;
rt_LoggedStateSignalPtrs [ 145 ] = ( void * ) rtDW . bubytbfjvq ;
rt_LoggedStateSignalPtrs [ 146 ] = ( void * ) rtDW . glikpzp24u ;
rt_LoggedStateSignalPtrs [ 147 ] = ( void * ) rtDW . hskq4vr1qs ;
rt_LoggedStateSignalPtrs [ 148 ] = ( void * ) rtDW . hljbnnt3zw ;
rt_LoggedStateSignalPtrs [ 149 ] = ( void * ) rtDW . d2cg15qgjf ;
rt_LoggedStateSignalPtrs [ 150 ] = ( void * ) rtDW . ir1mqsar5f ;
rt_LoggedStateSignalPtrs [ 151 ] = ( void * ) & rtDW . kebzxgfy5a ;
rt_LoggedStateSignalPtrs [ 152 ] = ( void * ) & rtDW . pmncprwmz4 ;
rt_LoggedStateSignalPtrs [ 153 ] = ( void * ) & rtDW . g05suawwrk ;
rt_LoggedStateSignalPtrs [ 154 ] = ( void * ) & rtDW . ore24n4522 ;
rt_LoggedStateSignalPtrs [ 155 ] = ( void * ) rtDW . mz1lyyodga ;
rt_LoggedStateSignalPtrs [ 156 ] = ( void * ) rtDW . i22hackosr ;
rt_LoggedStateSignalPtrs [ 157 ] = ( void * ) rtDW . hrf0r3epza ;
rt_LoggedStateSignalPtrs [ 158 ] = ( void * ) rtDW . l4gldy0ied ;
rt_LoggedStateSignalPtrs [ 159 ] = ( void * ) rtDW . jcgd4tqv41 ;
rt_LoggedStateSignalPtrs [ 160 ] = ( void * ) rtDW . oyxqmd0f4v ;
rt_LoggedStateSignalPtrs [ 161 ] = ( void * ) rtDW . cdd1gh0rmi ;
rt_LoggedStateSignalPtrs [ 162 ] = ( void * ) rtDW . ayjsmpf3pd ;
rt_LoggedStateSignalPtrs [ 163 ] = ( void * ) rtDW . etncgat1qk ;
rt_LoggedStateSignalPtrs [ 164 ] = ( void * ) rtDW . j0pfyx5sl0 ;
rt_LoggedStateSignalPtrs [ 165 ] = ( void * ) rtDW . otdqomronl ;
rt_LoggedStateSignalPtrs [ 166 ] = ( void * ) rtDW . nz3xkbxksp ;
rt_LoggedStateSignalPtrs [ 167 ] = ( void * ) rtDW . cmxd2uv3ip ;
rt_LoggedStateSignalPtrs [ 168 ] = ( void * ) rtDW . hbomutgs5x ;
rt_LoggedStateSignalPtrs [ 169 ] = ( void * ) rtDW . kkklfomjr5 ;
rt_LoggedStateSignalPtrs [ 170 ] = ( void * ) rtDW . dmmot30jq4 ;
rt_LoggedStateSignalPtrs [ 171 ] = ( void * ) rtDW . dzr2rntvvo ;
rt_LoggedStateSignalPtrs [ 172 ] = ( void * ) rtDW . aw0bxhrzal ;
rt_LoggedStateSignalPtrs [ 173 ] = ( void * ) rtDW . estezyunas ;
rt_LoggedStateSignalPtrs [ 174 ] = ( void * ) rtDW . olzifhaukx ;
rt_LoggedStateSignalPtrs [ 175 ] = ( void * ) rtDW . miwm3apiea ;
rt_LoggedStateSignalPtrs [ 176 ] = ( void * ) rtDW . otborblus0 ;
rt_LoggedStateSignalPtrs [ 177 ] = ( void * ) rtDW . jcievkrvvv ;
rt_LoggedStateSignalPtrs [ 178 ] = ( void * ) rtDW . ovlbtlz2z5 ;
rt_LoggedStateSignalPtrs [ 179 ] = ( void * ) rtDW . mx1dy0gdum ;
rt_LoggedStateSignalPtrs [ 180 ] = ( void * ) rtDW . iygynuhhiw ;
rt_LoggedStateSignalPtrs [ 181 ] = ( void * ) & rtDW . oamcwpfckc ;
rt_LoggedStateSignalPtrs [ 182 ] = ( void * ) rtDW . az4aq4f2to ;
rt_LoggedStateSignalPtrs [ 183 ] = ( void * ) & rtDW . hv1tfq2dkg ;
rt_LoggedStateSignalPtrs [ 184 ] = ( void * ) rtDW . ckuddxo2v5 ;
rt_LoggedStateSignalPtrs [ 185 ] = ( void * ) rtDW . hoqlzb3yrr ;
rt_LoggedStateSignalPtrs [ 186 ] = ( void * ) rtDW . d2yav1jvrg ;
rt_LoggedStateSignalPtrs [ 187 ] = ( void * ) & rtDW . pdli3lyef1 ;
rt_LoggedStateSignalPtrs [ 188 ] = ( void * ) & rtDW . bi1fzovgs2 ;
rt_LoggedStateSignalPtrs [ 189 ] = ( void * ) & rtDW . llxyyz4q5x ;
rt_LoggedStateSignalPtrs [ 190 ] = ( void * ) & rtDW . bjzrd2jgh1 ;
rt_LoggedStateSignalPtrs [ 191 ] = ( void * ) & rtDW . npqdzcpz4k ;
rt_LoggedStateSignalPtrs [ 192 ] = ( void * ) rtDW . k44l31otpd ;
rt_LoggedStateSignalPtrs [ 193 ] = ( void * ) & rtDW . ocwqpyvhqo ;
rt_LoggedStateSignalPtrs [ 194 ] = ( void * ) rtDW . bb0v2ld5vf ;
rt_LoggedStateSignalPtrs [ 195 ] = ( void * ) rtDW . htr1ntw0w0 ;
rt_LoggedStateSignalPtrs [ 196 ] = ( void * ) rtDW . f1sl003e30 ;
rt_LoggedStateSignalPtrs [ 197 ] = ( void * ) & rtDW . lbwbhxgeac ;
rt_LoggedStateSignalPtrs [ 198 ] = ( void * ) rtDW . lgjrfdubva ;
rt_LoggedStateSignalPtrs [ 199 ] = ( void * ) rtDW . il1i11vhya ;
rt_LoggedStateSignalPtrs [ 200 ] = ( void * ) & rtDW . fmvtpht2wc ;
rt_LoggedStateSignalPtrs [ 201 ] = ( void * ) rtDW . jlwpaqqpol ;
rt_LoggedStateSignalPtrs [ 202 ] = ( void * ) rtDW . o2nyvbjxnw ;
rt_LoggedStateSignalPtrs [ 203 ] = ( void * ) & rtDW . mofgw1cji2 ;
rt_LoggedStateSignalPtrs [ 204 ] = ( void * ) rtDW . hbtp4braxp ;
rt_LoggedStateSignalPtrs [ 205 ] = ( void * ) rtDW . ifa1aifv0v ;
rt_LoggedStateSignalPtrs [ 206 ] = ( void * ) & rtDW . azvnw5pvht ;
rt_LoggedStateSignalPtrs [ 207 ] = ( void * ) & rtDW . avqcisj0g1 ;
rt_LoggedStateSignalPtrs [ 208 ] = ( void * ) & rtDW . hyopdoshjp ;
rt_LoggedStateSignalPtrs [ 209 ] = ( void * ) rtDW . cx41wglw3j . bineo4prgi
; rt_LoggedStateSignalPtrs [ 210 ] = ( void * ) rtDW . jjob4ur221 .
bineo4prgi ; rt_LoggedStateSignalPtrs [ 211 ] = ( void * ) rtDW . jogryxdnkz
. bineo4prgi ; rt_LoggedStateSignalPtrs [ 212 ] = ( void * ) rtDW .
n4cqr1dkmr . bineo4prgi ; rt_LoggedStateSignalPtrs [ 213 ] = ( void * ) rtDW
. a13lr3lsi3 . bineo4prgi ; rt_LoggedStateSignalPtrs [ 214 ] = ( void * )
rtDW . jjajpmoyel . bineo4prgi ; rt_LoggedStateSignalPtrs [ 215 ] = ( void *
) rtDW . ndmeqad3sm . bineo4prgi ; rt_LoggedStateSignalPtrs [ 216 ] = ( void
* ) rtDW . o0tbmhvpds . bineo4prgi ; rt_LoggedStateSignalPtrs [ 217 ] = (
void * ) rtDW . f5mkygzljka . bineo4prgi ; rt_LoggedStateSignalPtrs [ 218 ] =
( void * ) & rtDW . biyhxca30f . ftf50xwldj ; rt_LoggedStateSignalPtrs [ 219
] = ( void * ) & rtDW . msqwmshj2n . ltyokv5jui ; rt_LoggedStateSignalPtrs [
220 ] = ( void * ) & rtDW . mzoe5aiivc . ftf50xwldj ;
rt_LoggedStateSignalPtrs [ 221 ] = ( void * ) & rtDW . cstc0v1lpw .
ltyokv5jui ; rt_LoggedStateSignalPtrs [ 222 ] = ( void * ) & rtDW .
azshdeeeiw3 . ftf50xwldj ; rt_LoggedStateSignalPtrs [ 223 ] = ( void * ) &
rtDW . cqjwvwhkzvh . ltyokv5jui ; } rtliSetLogT ( ssGetRTWLogInfo ( rtS ) ,
"tout" ) ; rtliSetLogX ( ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogXFinal (
ssGetRTWLogInfo ( rtS ) , "xFinal" ) ; rtliSetLogVarNameModifier (
ssGetRTWLogInfo ( rtS ) , "none" ) ; rtliSetLogFormat ( ssGetRTWLogInfo ( rtS
) , 4 ) ; rtliSetLogMaxRows ( ssGetRTWLogInfo ( rtS ) , 1000 ) ;
rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS ) , 1 ) ; rtliSetLogY (
ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogYSignalInfo ( ssGetRTWLogInfo (
rtS ) , ( NULL ) ) ; rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL
) ) ; } { static struct _ssStatesInfo2 statesInfo2 ; ssSetStatesInfo2 ( rtS ,
& statesInfo2 ) ; } { static ssPeriodicStatesInfo periodicStatesInfo ;
ssSetPeriodicStatesInfo ( rtS , & periodicStatesInfo ) ; } { static
ssJacobianPerturbationBounds jacobianPerturbationBounds ;
ssSetJacobianPerturbationBounds ( rtS , & jacobianPerturbationBounds ) ; } {
static ssSolverInfo slvrInfo ; static boolean_T contStatesDisabled [ 2 ] ;
ssSetSolverInfo ( rtS , & slvrInfo ) ; ssSetSolverName ( rtS , "ode3" ) ;
ssSetVariableStepSolver ( rtS , 0 ) ; ssSetSolverConsistencyChecking ( rtS ,
0 ) ; ssSetSolverAdaptiveZcDetection ( rtS , 0 ) ;
ssSetSolverRobustResetMethod ( rtS , 0 ) ; ssSetSolverStateProjection ( rtS ,
0 ) ; ssSetSolverMassMatrixType ( rtS , ( ssMatrixType ) 0 ) ;
ssSetSolverMassMatrixNzMax ( rtS , 0 ) ; ssSetModelOutputs ( rtS , MdlOutputs
) ; ssSetModelLogData ( rtS , rt_UpdateTXYLogVars ) ;
ssSetModelLogDataIfInInterval ( rtS , rt_UpdateTXXFYLogVars ) ;
ssSetModelUpdate ( rtS , MdlUpdate ) ; ssSetModelDerivatives ( rtS ,
MdlDerivatives ) ; ssSetTNextTid ( rtS , INT_MIN ) ; ssSetTNext ( rtS ,
rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ; ssSetNumNonsampledZCs ( rtS ,
0 ) ; ssSetContStateDisabled ( rtS , contStatesDisabled ) ; } { ZCSigState *
zc = ( ZCSigState * ) & rtPrevZCX ; ssSetPrevZCSigState ( rtS , zc ) ; } {
rtPrevZCX . msqwmshj2n . cowinqfkuy = UNINITIALIZED_ZCSIG ; rtPrevZCX .
cstc0v1lpw . cowinqfkuy = UNINITIALIZED_ZCSIG ; rtPrevZCX . cqjwvwhkzvh .
cowinqfkuy = UNINITIALIZED_ZCSIG ; } ssSetChecksumVal ( rtS , 0 , 1450536526U
) ; ssSetChecksumVal ( rtS , 1 , 3180783492U ) ; ssSetChecksumVal ( rtS , 2 ,
2573665585U ) ; ssSetChecksumVal ( rtS , 3 , 2888385381U ) ; { static const
sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo
rt_ExtModeInfo ; static const sysRanDType * systemRan [ 60 ] ;
gblRTWExtModeInfo = & rt_ExtModeInfo ; ssSetRTWExtModeInfo ( rtS , &
rt_ExtModeInfo ) ; rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo ,
systemRan ) ; systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = (
sysRanDType * ) & rtDW . cqjwvwhkzvh . dqmv313jji ; systemRan [ 2 ] = (
sysRanDType * ) & rtDW . azshdeeeiw3 . bnbpcxxvih ; systemRan [ 3 ] = (
sysRanDType * ) & rtDW . cstc0v1lpw . dqmv313jji ; systemRan [ 4 ] = (
sysRanDType * ) & rtDW . mzoe5aiivc . bnbpcxxvih ; systemRan [ 5 ] = (
sysRanDType * ) & rtDW . msqwmshj2n . dqmv313jji ; systemRan [ 6 ] = (
sysRanDType * ) & rtDW . biyhxca30f . bnbpcxxvih ; systemRan [ 7 ] = (
sysRanDType * ) & rtDW . i1c4xekdhn ; systemRan [ 8 ] = ( sysRanDType * ) &
rtDW . ip0d0t1043 ; systemRan [ 9 ] = ( sysRanDType * ) & rtDW . jitieevvno ;
systemRan [ 10 ] = ( sysRanDType * ) & rtDW . k0efqstpz0 ; systemRan [ 11 ] =
& rtAlwaysEnabled ; systemRan [ 12 ] = & rtAlwaysEnabled ; systemRan [ 13 ] =
& rtAlwaysEnabled ; systemRan [ 14 ] = & rtAlwaysEnabled ; systemRan [ 15 ] =
& rtAlwaysEnabled ; systemRan [ 16 ] = & rtAlwaysEnabled ; systemRan [ 17 ] =
& rtAlwaysEnabled ; systemRan [ 18 ] = & rtAlwaysEnabled ; systemRan [ 19 ] =
& rtAlwaysEnabled ; systemRan [ 20 ] = & rtAlwaysEnabled ; systemRan [ 21 ] =
& rtAlwaysEnabled ; systemRan [ 22 ] = & rtAlwaysEnabled ; systemRan [ 23 ] =
& rtAlwaysEnabled ; systemRan [ 24 ] = & rtAlwaysEnabled ; systemRan [ 25 ] =
& rtAlwaysEnabled ; systemRan [ 26 ] = & rtAlwaysEnabled ; systemRan [ 27 ] =
& rtAlwaysEnabled ; systemRan [ 28 ] = & rtAlwaysEnabled ; systemRan [ 29 ] =
& rtAlwaysEnabled ; systemRan [ 30 ] = & rtAlwaysEnabled ; systemRan [ 31 ] =
& rtAlwaysEnabled ; systemRan [ 32 ] = & rtAlwaysEnabled ; systemRan [ 33 ] =
& rtAlwaysEnabled ; systemRan [ 34 ] = & rtAlwaysEnabled ; systemRan [ 35 ] =
& rtAlwaysEnabled ; systemRan [ 36 ] = & rtAlwaysEnabled ; systemRan [ 37 ] =
& rtAlwaysEnabled ; systemRan [ 38 ] = & rtAlwaysEnabled ; systemRan [ 39 ] =
& rtAlwaysEnabled ; systemRan [ 40 ] = & rtAlwaysEnabled ; systemRan [ 41 ] =
( sysRanDType * ) & rtDW . f5mkygzljka . bvutux0ucw ; systemRan [ 42 ] = (
sysRanDType * ) & rtDW . f5mkygzljka . bvutux0ucw ; systemRan [ 43 ] = (
sysRanDType * ) & rtDW . o0tbmhvpds . bvutux0ucw ; systemRan [ 44 ] = (
sysRanDType * ) & rtDW . o0tbmhvpds . bvutux0ucw ; systemRan [ 45 ] = (
sysRanDType * ) & rtDW . ndmeqad3sm . bvutux0ucw ; systemRan [ 46 ] = (
sysRanDType * ) & rtDW . ndmeqad3sm . bvutux0ucw ; systemRan [ 47 ] = (
sysRanDType * ) & rtDW . jjajpmoyel . bvutux0ucw ; systemRan [ 48 ] = (
sysRanDType * ) & rtDW . jjajpmoyel . bvutux0ucw ; systemRan [ 49 ] = (
sysRanDType * ) & rtDW . a13lr3lsi3 . bvutux0ucw ; systemRan [ 50 ] = (
sysRanDType * ) & rtDW . a13lr3lsi3 . bvutux0ucw ; systemRan [ 51 ] = (
sysRanDType * ) & rtDW . n4cqr1dkmr . bvutux0ucw ; systemRan [ 52 ] = (
sysRanDType * ) & rtDW . n4cqr1dkmr . bvutux0ucw ; systemRan [ 53 ] = (
sysRanDType * ) & rtDW . jogryxdnkz . bvutux0ucw ; systemRan [ 54 ] = (
sysRanDType * ) & rtDW . jogryxdnkz . bvutux0ucw ; systemRan [ 55 ] = (
sysRanDType * ) & rtDW . jjob4ur221 . bvutux0ucw ; systemRan [ 56 ] = (
sysRanDType * ) & rtDW . jjob4ur221 . bvutux0ucw ; systemRan [ 57 ] = (
sysRanDType * ) & rtDW . cx41wglw3j . bvutux0ucw ; systemRan [ 58 ] = (
sysRanDType * ) & rtDW . cx41wglw3j . bvutux0ucw ; systemRan [ 59 ] = &
rtAlwaysEnabled ; rteiSetModelMappingInfoPtr ( ssGetRTWExtModeInfo ( rtS ) ,
& ssGetModelMappingInfo ( rtS ) ) ; rteiSetChecksumsPtr ( ssGetRTWExtModeInfo
( rtS ) , ssGetChecksums ( rtS ) ) ; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS
) , ssGetTPtr ( rtS ) ) ; } slsaDisallowedBlocksForSimTargetOP ( rtS ,
mr_uz_drive_model_GetSimStateDisallowedBlocks ) ;
slsaGetWorkFcnForSimTargetOP ( rtS , mr_uz_drive_model_GetDWork ) ;
slsaSetWorkFcnForSimTargetOP ( rtS , mr_uz_drive_model_SetDWork ) ;
rt_RapidReadMatFileAndUpdateParams ( rtS ) ; if ( ssGetErrorStatus ( rtS ) )
{ return rtS ; } return rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
const int_T gblParameterTuningTid = 6 ; void MdlOutputsParameterSampleTime (
int_T tid ) { MdlOutputsTID6 ( tid ) ; }
