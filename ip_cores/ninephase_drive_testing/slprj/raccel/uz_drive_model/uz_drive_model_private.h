#ifndef RTW_HEADER_uz_drive_model_private_h_
#define RTW_HEADER_uz_drive_model_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "zero_crossing_types.h"
#include "uz_drive_model.h"
#if !defined(rt_VALIDATE_MEMORY)
#define rt_VALIDATE_MEMORY(S, ptr)     if(!(ptr)) {\
    ssSetErrorStatus(rtS, RT_MEMORY_ALLOCATION_ERROR);\
    }
#endif
#if !defined(rt_FREE)
#if !defined(_WIN32)
#define rt_FREE(ptr)     if((ptr) != (NULL)) {\
    free((ptr));\
    (ptr) = (NULL);\
    }
#else
#define rt_FREE(ptr)     if((ptr) != (NULL)) {\
    free((void *)(ptr));\
    (ptr) = (NULL);\
    }
#endif
#endif
#ifndef UCHAR_MAX
#include <limits.h>
#endif
#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
extern real_T look1_pbinlxpw ( real_T u0 , const real_T bp0 [ ] , const
real_T table [ ] , uint32_T prevIndex [ ] , uint32_T maxIndex ) ; extern void
fdvdj1poit ( cz235gejcz * localB , gqx2bugedg * localDW , bnof3krbot * localP
) ; extern void fndh4y3t0v ( SimStruct * rtS_p , gqx2bugedg * localDW ) ;
extern void pqmhjlfkxs ( gqx2bugedg * localDW ) ; extern void px4gj3w5ct (
SimStruct * rtS_i , cz235gejcz * localB , gqx2bugedg * localDW ) ; extern
void cqjwvwhkzv ( SimStruct * rtS_i , boolean_T dy3dvniwgq , real_T
djs0afef4t , real_T hnq1e5wf11 , real_T rtp_Fc , cz235gejcz * localB ,
gqx2bugedg * localDW , bnof3krbot * localP , nrs5bzunb3 * localZCE ) ; extern
void cqjwvwhkzvTID6 ( SimStruct * rtS_m , gqx2bugedg * localDW ) ; extern
void jya45nfjbt ( cog2itxiqj * localB , dqnc2mdlgm * localDW , nygobnlzkj *
localP ) ; extern void psbttp2yxj ( SimStruct * rtS_p , dqnc2mdlgm * localDW
) ; extern void k0i1quatwd ( dqnc2mdlgm * localDW ) ; extern void l1bndan4eb
( SimStruct * rtS_c , cog2itxiqj * localB , dqnc2mdlgm * localDW ) ; extern
void azshdeeeiw ( SimStruct * rtS_f , boolean_T c3yka0vm44 , real_T
flq35icr02 , real_T g4md3o4lvx , cog2itxiqj * localB , dqnc2mdlgm * localDW ,
nygobnlzkj * localP ) ; extern void azshdeeeiwTID6 ( SimStruct * rtS_m ,
dqnc2mdlgm * localDW ) ; extern void gy5wd21nmz ( const real32_T dcl5qalq3t [
12 ] , const real32_T md2lseqy24 [ 8 ] , kavyiqnma5 * localB ) ; extern void
p4z2y3oxrm ( const boolean_T oy0pxpnzml [ 12 ] , uint8_T enwomtisuj , const
boolean_T mprhu3voft [ 12 ] , uint8_T rtp_Index , c43be0leba * localB ) ;
extern void amrcdbjbbq ( ch3csirfgx * localB , f5d5p32bfp * localDW ,
nytscbbkkv * localP ) ; extern void ipssuqc5xa ( boolean_T pbf43v0ydb , const
int32_T go3yyxmtm4 [ 9 ] , const int32_T mk3rn1uuk1 [ 9 ] , ch3csirfgx *
localB , f5d5p32bfp * localDW ) ; extern void f5mkygzljk ( boolean_T
pbf43v0ydb , ch3csirfgx * localB , f5d5p32bfp * localDW , nytscbbkkv * localP
) ; extern void nn0sefi01r ( SimStruct * rtS_g , gqx2bugedg * localDW ) ;
#if defined(MULTITASKING)
#error Model (uz_drive_model) was built in \SingleTasking solver mode, however the MULTITASKING define is \present. If you have multitasking (e.g. -DMT or -DMULTITASKING) \defined on the Code Generation page of Simulation parameter dialog, please \remove it and on the Solver page, select solver mode \MultiTasking. If the Simulation parameter dialog is configured \correctly, please verify that your template makefile is \configured correctly.
#endif
#endif
