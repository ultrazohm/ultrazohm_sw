#include "ne_ds.h"
#include "external_state_machine_605b847d_1_ds_zc.h"
#include "external_state_machine_605b847d_1_ds_tdxy_p.h"
#include "external_state_machine_605b847d_1_ds_dxy_p.h"
#include "external_state_machine_605b847d_1_ds_y.h"
#include "external_state_machine_605b847d_1_ds_m_p.h"
#include "external_state_machine_605b847d_1_ds_log.h"
#include "external_state_machine_605b847d_1_ds_obs_all.h"
#include "external_state_machine_605b847d_1_ds_imax.h"
#include "external_state_machine_605b847d_1_ds_obs_act.h"
#include "external_state_machine_605b847d_1_ds_imin.h"
#include "external_state_machine_605b847d_1_ds_tdxf_p.h"
#include "external_state_machine_605b847d_1_ds_a_p.h"
#include "external_state_machine_605b847d_1_ds_obs_il.h"
#include "external_state_machine_605b847d_1_ds_a.h"
#include "external_state_machine_605b847d_1_ds_tduf_p.h"
#include "external_state_machine_605b847d_1_ds_dxf_p.h"
#include "external_state_machine_605b847d_1_ds_dxf.h"
#include "external_state_machine_605b847d_1_ds_mode.h"
#include "external_state_machine_605b847d_1_ds_f.h"
#include "external_state_machine_605b847d_1_ds.h"
#include "ssc_ml_fun.h"
#include "external_state_machine_605b847d_1_ds_external_struct.h"
#include "external_state_machine_605b847d_1_ds_sys_struct.h"
#include "external_state_machine_605b847d_1_ds_externals.h"
static int32_T ds_m ( const NeDynamicSystem * ds , const NeDynamicSystemInput
* in , NeDsMethodOutput * out ) ; static int32_T ds_vmm ( const
NeDynamicSystem * ds , const NeDynamicSystemInput * in , NeDsMethodOutput *
out ) ; static int32_T ds_dxm_p ( const NeDynamicSystem * ds , const
NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T ds_dxm
( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_ddm_p ( const NeDynamicSystem *
ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_ddm ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in
, NeDsMethodOutput * out ) ; static int32_T ds_dum_p ( const NeDynamicSystem
* ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_dum ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in
, NeDsMethodOutput * out ) ; static int32_T ds_dtm_p ( const NeDynamicSystem
* ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_dtm ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in
, NeDsMethodOutput * out ) ; static int32_T ds_dpm_p ( const NeDynamicSystem
* ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_dpm ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in
, NeDsMethodOutput * out ) ; static int32_T ds_b_p ( const NeDynamicSystem *
ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_b ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_c_p ( const NeDynamicSystem * ds
, const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_c ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_vmf ( const NeDynamicSystem * ds
, const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_vpf ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_vsf ( const NeDynamicSystem * ds
, const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_slf ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_slf0 ( const NeDynamicSystem *
ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_duf_p ( const NeDynamicSystem * ds , const NeDynamicSystemInput *
in , NeDsMethodOutput * out ) ; static int32_T ds_duf ( const NeDynamicSystem
* ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_dtf_p ( const NeDynamicSystem * ds , const NeDynamicSystemInput *
in , NeDsMethodOutput * out ) ; static int32_T ds_dtf ( const NeDynamicSystem
* ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_ddf_p ( const NeDynamicSystem * ds , const NeDynamicSystemInput *
in , NeDsMethodOutput * out ) ; static int32_T ds_ddf ( const NeDynamicSystem
* ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_dpdxf_p ( const NeDynamicSystem * ds , const NeDynamicSystemInput
* in , NeDsMethodOutput * out ) ; static int32_T ds_dpdxf ( const
NeDynamicSystem * ds , const NeDynamicSystemInput * in , NeDsMethodOutput *
out ) ; static int32_T ds_dwf_p ( const NeDynamicSystem * ds , const
NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T ds_dwf
( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_dnf_p ( const NeDynamicSystem *
ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_dnf ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in
, NeDsMethodOutput * out ) ; static int32_T ds_dnf_v_x ( const
NeDynamicSystem * ds , const NeDynamicSystemInput * in , NeDsMethodOutput *
out ) ; static int32_T ds_cer ( const NeDynamicSystem * ds , const
NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_dxcer ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_dxcer_p ( const NeDynamicSystem
* ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_ic ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in
, NeDsMethodOutput * out ) ; static int32_T ds_icr ( const NeDynamicSystem *
ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_icr_im ( const NeDynamicSystem * ds , const NeDynamicSystemInput *
in , NeDsMethodOutput * out ) ; static int32_T ds_icr_id ( const
NeDynamicSystem * ds , const NeDynamicSystemInput * in , NeDsMethodOutput *
out ) ; static int32_T ds_icr_il ( const NeDynamicSystem * ds , const
NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_dxicr ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_dxicr_p ( const NeDynamicSystem
* ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_ddicr ( const NeDynamicSystem * ds , const NeDynamicSystemInput *
in , NeDsMethodOutput * out ) ; static int32_T ds_ddicr_p ( const
NeDynamicSystem * ds , const NeDynamicSystemInput * in , NeDsMethodOutput *
out ) ; static int32_T ds_tduicr_p ( const NeDynamicSystem * ds , const
NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_icrm_p ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_icrm ( const NeDynamicSystem *
ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_dxicrm_p ( const NeDynamicSystem * ds , const NeDynamicSystemInput
* in , NeDsMethodOutput * out ) ; static int32_T ds_dxicrm ( const
NeDynamicSystem * ds , const NeDynamicSystemInput * in , NeDsMethodOutput *
out ) ; static int32_T ds_ddicrm_p ( const NeDynamicSystem * ds , const
NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_ddicrm ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_mduy_p ( const NeDynamicSystem *
ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_mdxy_p ( const NeDynamicSystem * ds , const NeDynamicSystemInput *
in , NeDsMethodOutput * out ) ; static int32_T ds_tduy_p ( const
NeDynamicSystem * ds , const NeDynamicSystemInput * in , NeDsMethodOutput *
out ) ; static int32_T ds_dxy ( const NeDynamicSystem * ds , const
NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_duy_p ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_duy ( const NeDynamicSystem * ds
, const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_dty_p ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_dty ( const NeDynamicSystem * ds
, const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_cache_r ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_cache_i ( const NeDynamicSystem
* ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_update_r ( const NeDynamicSystem * ds , const NeDynamicSystemInput
* in , NeDsMethodOutput * out ) ; static int32_T ds_update_i ( const
NeDynamicSystem * ds , const NeDynamicSystemInput * in , NeDsMethodOutput *
out ) ; static int32_T ds_update2_r ( const NeDynamicSystem * ds , const
NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_update2_i ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_lock_r ( const NeDynamicSystem *
ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_lock_i ( const NeDynamicSystem * ds , const NeDynamicSystemInput *
in , NeDsMethodOutput * out ) ; static int32_T ds_lock2_r ( const
NeDynamicSystem * ds , const NeDynamicSystemInput * in , NeDsMethodOutput *
out ) ; static int32_T ds_lock2_i ( const NeDynamicSystem * ds , const
NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T ds_sfo
( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_sfp ( const NeDynamicSystem * ds
, const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_init_r ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_init_i ( const NeDynamicSystem *
ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_assert ( const NeDynamicSystem * ds , const NeDynamicSystemInput *
in , NeDsMethodOutput * out ) ; static int32_T ds_passert ( const
NeDynamicSystem * ds , const NeDynamicSystemInput * in , NeDsMethodOutput *
out ) ; static int32_T ds_iassert ( const NeDynamicSystem * ds , const
NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_del_t ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_del_v ( const NeDynamicSystem *
ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_del_v0 ( const NeDynamicSystem * ds , const NeDynamicSystemInput *
in , NeDsMethodOutput * out ) ; static int32_T ds_del_tmax ( const
NeDynamicSystem * ds , const NeDynamicSystemInput * in , NeDsMethodOutput *
out ) ; static int32_T ds_dxdelt_p ( const NeDynamicSystem * ds , const
NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_dxdelt ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_dudelt_p ( const NeDynamicSystem
* ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_dudelt ( const NeDynamicSystem * ds , const NeDynamicSystemInput *
in , NeDsMethodOutput * out ) ; static int32_T ds_dtdelt_p ( const
NeDynamicSystem * ds , const NeDynamicSystemInput * in , NeDsMethodOutput *
out ) ; static int32_T ds_dtdelt ( const NeDynamicSystem * ds , const
NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_obs_exp ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_dp_l ( const NeDynamicSystem *
ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_dp_i ( const NeDynamicSystem * ds , const NeDynamicSystemInput *
in , NeDsMethodOutput * out ) ; static int32_T ds_dp_j ( const
NeDynamicSystem * ds , const NeDynamicSystemInput * in , NeDsMethodOutput *
out ) ; static int32_T ds_dp_r ( const NeDynamicSystem * ds , const
NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T ds_qx (
const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_qu ( const NeDynamicSystem * ds
, const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_qt ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_q1 ( const NeDynamicSystem * ds
, const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_qx_p ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_qu_p ( const NeDynamicSystem *
ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_qt_p ( const NeDynamicSystem * ds , const NeDynamicSystemInput *
in , NeDsMethodOutput * out ) ; static int32_T ds_q1_p ( const
NeDynamicSystem * ds , const NeDynamicSystemInput * in , NeDsMethodOutput *
out ) ; static int32_T ds_var_tol ( const NeDynamicSystem * ds , const
NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_eq_tol ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_lv ( const NeDynamicSystem * ds
, const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static int32_T
ds_slv ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
NeDsMethodOutput * out ) ; static int32_T ds_nldv ( const NeDynamicSystem *
ds , const NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
int32_T ds_sclv ( const NeDynamicSystem * ds , const NeDynamicSystemInput *
in , NeDsMethodOutput * out ) ; static int32_T ds_dimin ( const
NeDynamicSystem * ds , const NeDynamicSystemInput * in , NeDsMethodOutput *
out ) ; static int32_T ds_dimax ( const NeDynamicSystem * ds , const
NeDynamicSystemInput * in , NeDsMethodOutput * out ) ; static
NeDsMethodOutput * ds_output_m_p ( const NeDynamicSystem * ds , PmAllocator *
allocator ) ; static NeDsMethodOutput * ds_output_m ( const NeDynamicSystem *
ds , PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_vmm (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_dxm_p ( const NeDynamicSystem * ds , PmAllocator
* allocator ) ; static NeDsMethodOutput * ds_output_dxm ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_ddm_p ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_ddm ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_dum_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_dum ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_dtm_p ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_dtm ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_dpm_p ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_dpm ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_a_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_a ( const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_b_p ( const NeDynamicSystem * ds , PmAllocator *
allocator ) ; static NeDsMethodOutput * ds_output_b ( const NeDynamicSystem *
ds , PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_c_p (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_c ( const NeDynamicSystem * ds , PmAllocator *
allocator ) ; static NeDsMethodOutput * ds_output_f ( const NeDynamicSystem *
ds , PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_vmf (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_vpf ( const NeDynamicSystem * ds , PmAllocator *
allocator ) ; static NeDsMethodOutput * ds_output_vsf ( const NeDynamicSystem
* ds , PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_slf (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_slf0 ( const NeDynamicSystem * ds , PmAllocator
* allocator ) ; static NeDsMethodOutput * ds_output_dxf_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_dxf ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_duf_p ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_duf ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_dtf_p ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_dtf ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_ddf_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_ddf ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_dpdxf_p ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_dpdxf ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_dwf_p ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_dwf ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_tduf_p (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_tdxf_p ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_dnf_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_dnf ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_dnf_v_x ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_cer ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_dxcer ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_dxcer_p ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_ic ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_icr ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_icr_im ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_icr_id (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_icr_il ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_dxicr ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_dxicr_p ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_ddicr ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_ddicr_p (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_tduicr_p ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_icrm_p (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_icrm ( const NeDynamicSystem * ds , PmAllocator
* allocator ) ; static NeDsMethodOutput * ds_output_dxicrm_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_dxicrm ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_ddicrm_p ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_ddicrm (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_mduy_p ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_mdxy_p (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_tduy_p ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_tdxy_p (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_y ( const NeDynamicSystem * ds , PmAllocator *
allocator ) ; static NeDsMethodOutput * ds_output_dxy_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_dxy ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_duy_p ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_duy ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_dty_p ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_dty ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_mode ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_zc ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_cache_r ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_cache_i (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_update_r ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_update_i (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_update2_r ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_update2_i (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_lock_r ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_lock_i (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_lock2_r ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_lock2_i (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_sfo ( const NeDynamicSystem * ds , PmAllocator *
allocator ) ; static NeDsMethodOutput * ds_output_sfp ( const NeDynamicSystem
* ds , PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_init_r
( const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_init_i ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_log ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_assert ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_passert ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_iassert (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_del_t ( const NeDynamicSystem * ds , PmAllocator
* allocator ) ; static NeDsMethodOutput * ds_output_del_v ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_del_v0 ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_del_tmax ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_dxdelt_p (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_dxdelt ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_dudelt_p (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_dudelt ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_dtdelt_p (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_dtdelt ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_obs_exp (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_obs_act ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_obs_all (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_obs_il ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_dp_l ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_dp_i ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_dp_j ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_dp_r ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_qx ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_qu ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_qt ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_q1 ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_qx_p ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_qu_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_qt_p ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_q1_p ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_var_tol (
const NeDynamicSystem * ds , PmAllocator * allocator ) ; static
NeDsMethodOutput * ds_output_eq_tol ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_lv ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_slv ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_nldv ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_sclv ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_imin ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static NeDsMethodOutput * ds_output_imax ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) ; static NeDsMethodOutput * ds_output_dimin ( const
NeDynamicSystem * ds , PmAllocator * allocator ) ; static NeDsMethodOutput *
ds_output_dimax ( const NeDynamicSystem * ds , PmAllocator * allocator ) ;
static void release_reference ( NeDynamicSystem * ds ) ; static void
get_reference ( NeDynamicSystem * ds ) ; static NeDynamicSystem * diagnostics
( NeDynamicSystem * ds , boolean_T ) ; static void expand ( const
NeDynamicSystem * ds , const NeDynamicSystemInput * in , PmRealVector * out ,
boolean_T kp ) ; static void rtpmap ( const NeDynamicSystem * ds , const
PmIntVector * inl , const PmIntVector * ini , const PmIntVector * inj , const
PmRealVector * inr , PmIntVector * outl , PmIntVector * outi , PmIntVector *
outj , PmRealVector * outr ) ; static NeEquationData s_equation_data [ 27 ] =
{ { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/DC_link/Capacitor" , 1U , 0U , TRUE , 1.0
, "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/Ideal Rotational Motion Sensor1" , 2U , 1U
, TRUE , 1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/Inertia1" , 2U , 3U , TRUE , 1.0 , "1" , }
, { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/Simscape Component" , 2U , 5U , TRUE , 1.0
, "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 7U , FALSE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 8U , FALSE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 9U , TRUE , 1.0
, "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 10U , TRUE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/DC_link/Capacitor" , 1U , 11U , TRUE , 1.0
, "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/Ideal Angular Velocity Source1" , 1U , 12U
, TRUE , 1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 13U , TRUE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 14U , TRUE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 15U , FALSE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 16U , FALSE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 17U , FALSE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET" , 3U , 18U , TRUE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET1" , 3U , 21U , TRUE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET10" , 3U , 24U , TRUE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET11" , 3U , 27U , TRUE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET2" , 3U , 30U , TRUE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET3" , 3U , 33U , TRUE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET4" , 3U , 36U , TRUE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET5" , 3U , 39U , TRUE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET6" , 3U , 42U , TRUE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET7" , 3U , 45U , TRUE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET8" , 3U , 48U , TRUE ,
1.0 , "1" , } , { "" , 0U , 8 , NE_EQUATION_DOMAIN_TIME ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET9" , 3U , 51U , TRUE ,
1.0 , "1" , } } ; static NeCERData * s_cer_data = NULL ; static NeICRData *
s_icr_data = NULL ; static NeVariableData s_variable_data [ 27 ] = { {
"Subsystem1.DC_link.Capacitor.vc" , 0U , 0 ,
"external_state_machine/Subsystem1/DC_link/Capacitor" , 1.0 , "1" , 0.0 ,
TRUE , FALSE , 1U , 1U , NE_INIT_MODE_MANDATORY , "Capacitor voltage" , } , {
"Subsystem1.Inertia1.w" , 0U , 0 ,
"external_state_machine/Subsystem1/Inertia1" , 1.0 , "1" , 0.0 , TRUE , FALSE
, 1U , 1U , NE_INIT_MODE_MANDATORY , "Rotational velocity" , } , {
"Subsystem1.Ideal_Rotational_Motion_Sensor1.phi" , 0U , 0 ,
"external_state_machine/Subsystem1/Ideal Rotational Motion Sensor1" , 1.0 ,
"1" , 0.0 , TRUE , FALSE , 1U , 1U , NE_INIT_MODE_MANDATORY , "Angle" , } , {
"Subsystem1.Simscape_Component.i_d" , 0U , 0 ,
"external_state_machine/Subsystem1/Simscape Component" , 1.0 , "1" , 0.0 ,
TRUE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "Strom in d-Achse" , } , {
"Subsystem1.Simscape_Component.i_q" , 0U , 0 ,
"external_state_machine/Subsystem1/Simscape Component" , 1.0 , "1" , 0.0 ,
TRUE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "Strom in q-Achse" , } , {
"Subsystem1.Simscape_Component.i_x" , 0U , 0 ,
"external_state_machine/Subsystem1/Simscape Component" , 1.0 , "1" , 0.0 ,
TRUE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "Strom der x-Komponente" , } , {
"Subsystem1.Simscape_Component.i_y" , 0U , 0 ,
"external_state_machine/Subsystem1/Simscape Component" , 1.0 , "1" , 0.0 ,
TRUE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "Strom der y-Komponente" , } , {
"Subsystem1.Simscape_Component.theta_m" , 0U , 0 ,
"external_state_machine/Subsystem1/Simscape Component" , 1.0 , "1" , 0.0 ,
TRUE , FALSE , 1U , 1U , NE_INIT_MODE_NONE ,
"Startposition des mech. Rotorwinkels bez\303\274glich a-Achse" , } , {
"Subsystem1.DC_link.Capacitor.i" , 0U , 0 ,
"external_state_machine/Subsystem1/DC_link/Capacitor" , 1.0 , "1" , 0.0 ,
FALSE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "Current" , } , {
"Subsystem1.Inertia1.t" , 0U , 0 ,
"external_state_machine/Subsystem1/Inertia1" , 1.0 , "1" , 0.0 , FALSE ,
FALSE , 1U , 1U , NE_INIT_MODE_NONE , "Torque" , } , {
"Subsystem1.Simscape_Component.m_m" , 0U , 0 ,
"external_state_machine/Subsystem1/Simscape Component" , 1.0 , "1" , 0.0 ,
FALSE , FALSE , 1U , 1U , NE_INIT_MODE_NONE ,
"inneres elektrisches Drehmoment" , } , {
"Subsystem1.Simscape_Component.a1.v" , 0U , 1 ,
"external_state_machine/Subsystem1/Simscape Component" , 1.0 , "1" , 0.0 ,
FALSE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "Voltage" , } , {
"Subsystem1.Simscape_Component.b1.v" , 0U , 1 ,
"external_state_machine/Subsystem1/Simscape Component" , 1.0 , "1" , 0.0 ,
FALSE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "Voltage" , } , {
"Subsystem1.Simscape_Component.c1.v" , 0U , 1 ,
"external_state_machine/Subsystem1/Simscape Component" , 1.0 , "1" , 0.0 ,
FALSE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "Voltage" , } , {
"Subsystem1.Simscape_Component.a2.v" , 0U , 1 ,
"external_state_machine/Subsystem1/Simscape Component" , 1.0 , "1" , 0.0 ,
FALSE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "Voltage" , } , {
"Subsystem1.Simscape_Component.b2.v" , 0U , 1 ,
"external_state_machine/Subsystem1/Simscape Component" , 1.0 , "1" , 0.0 ,
FALSE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "Voltage" , } , {
"Subsystem1.Simscape_Component.c2.v" , 0U , 1 ,
"external_state_machine/Subsystem1/Simscape Component" , 1.0 , "1" , 0.0 ,
FALSE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET1.mosfet_equation.i" , 0U , 0 ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET1" , 1.0 , "1" , 0.0 ,
FALSE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "i" , } , {
"Subsystem1.x6ph_Inverter.MOSFET11.mosfet_equation.i" , 0U , 0 ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET11" , 1.0 , "1" , 0.0 ,
FALSE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "i" , } , {
"Subsystem1.x6ph_Inverter.MOSFET3.mosfet_equation.i" , 0U , 0 ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET3" , 1.0 , "1" , 0.0 ,
FALSE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "i" , } , {
"Subsystem1.x6ph_Inverter.MOSFET5.mosfet_equation.i" , 0U , 0 ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET5" , 1.0 , "1" , 0.0 ,
FALSE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "i" , } , {
"Subsystem1.x6ph_Inverter.MOSFET7.mosfet_equation.i" , 0U , 0 ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET7" , 1.0 , "1" , 0.0 ,
FALSE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "i" , } , {
"Subsystem1.x6ph_Inverter.MOSFET9.mosfet_equation.i" , 0U , 0 ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET9" , 1.0 , "1" , 0.0 ,
FALSE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "i" , } , {
"Subsystem1.Simscape_Component.i_b1" , 0U , 0 ,
"external_state_machine/Subsystem1/Simscape Component" , 1.0 , "1" , 0.0 ,
FALSE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "Strom Strang b1" , } , {
"Subsystem1.Simscape_Component.i_c1" , 0U , 0 ,
"external_state_machine/Subsystem1/Simscape Component" , 1.0 , "1" , 0.0 ,
FALSE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "Strom Strang c1" , } , {
"Subsystem1.Simscape_Component.i_a2" , 0U , 0 ,
"external_state_machine/Subsystem1/Simscape Component" , 1.0 , "1" , 0.0 ,
FALSE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "Strom Strang a2" , } , {
"Subsystem1.Simscape_Component.i_b2" , 0U , 0 ,
"external_state_machine/Subsystem1/Simscape Component" , 1.0 , "1" , 0.0 ,
FALSE , FALSE , 1U , 1U , NE_INIT_MODE_NONE , "Strom Strang b2" , } } ;
static NeVariableData * s_discrete_data = NULL ; static NeObservableData
s_observable_data [ 279 ] = { { "Subsystem1.DC_link.Capacitor.i" ,
"external_state_machine/Subsystem1/DC_link/Capacitor" , 1U , 1U , "A" , 1.0 ,
"A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Current" , } , {
"Subsystem1.DC_link.Capacitor.n.v" ,
"external_state_machine/Subsystem1/DC_link/Capacitor" , 1U , 1U , "V" , 1.0 ,
"V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.DC_link.Capacitor.p.v" ,
"external_state_machine/Subsystem1/DC_link/Capacitor" , 1U , 1U , "V" , 1.0 ,
"V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.DC_link.Capacitor.v" ,
"external_state_machine/Subsystem1/DC_link/Capacitor" , 1U , 1U , "V" , 1.0 ,
"V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.DC_link.Capacitor.vc" ,
"external_state_machine/Subsystem1/DC_link/Capacitor" , 1U , 1U , "V" , 1.0 ,
"V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_MANDATORY , FALSE , TRUE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Capacitor voltage" , } , {
"Subsystem1.DC_link.Capacitor.power_dissipated" ,
"external_state_machine/Subsystem1/DC_link/Capacitor" , 1U , 1U , "kW" ,
1.0e-6 , "kW" , NE_NOMINAL_SOURCE_NONE , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , FALSE , "power_dissipated" , } , {
"Subsystem1.DC_link.U_dc_link_in0.v" ,
"external_state_machine/Subsystem1/DC_link" , 1U , 1U , "V" , 1.0 , "V" ,
NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage" , } , {
"Subsystem1.DC_link.U_dc_link_in1.v" ,
"external_state_machine/Subsystem1/DC_link" , 1U , 1U , "V" , 1.0 , "V" ,
NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage" , } , {
"Subsystem1.DC_link.Voltage_Sensor.V" ,
"external_state_machine/Subsystem1/DC_link/Voltage Sensor" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "V" , } , {
"Subsystem1.DC_link.Voltage_Sensor.n.v" ,
"external_state_machine/Subsystem1/DC_link/Voltage Sensor" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.DC_link.Voltage_Sensor.p.v" ,
"external_state_machine/Subsystem1/DC_link/Voltage Sensor" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.DC_link.Voltage_Sensor_V" ,
"external_state_machine/Subsystem1/DC_link" , 1U , 1U , "V" , 1.0 , "V" ,
NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage_Sensor_V" , } , {
"Subsystem1.Electrical_Reference1.V.v" ,
"external_state_machine/Subsystem1/Electrical Reference1" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.Ideal_Angular_Velocity_Source1.C.w" ,
"external_state_machine/Subsystem1/Ideal Angular Velocity Source1" , 1U , 1U
, "rad/s" , 1.0 , "1/s" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE ,
TRUE , FALSE , NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Rotational velocity" ,
} , { "Subsystem1.Ideal_Angular_Velocity_Source1.R.w" ,
"external_state_machine/Subsystem1/Ideal Angular Velocity Source1" , 1U , 1U
, "rad/s" , 1.0 , "1/s" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE ,
FALSE , FALSE , NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Rotational velocity" ,
} , { "Subsystem1.Ideal_Angular_Velocity_Source1.S" ,
"external_state_machine/Subsystem1/Ideal Angular Velocity Source1" , 1U , 1U
, "rad/s" , 1.0 , "1/s" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE ,
FALSE , FALSE , NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "S" , } , {
"Subsystem1.Ideal_Angular_Velocity_Source1.t" ,
"external_state_machine/Subsystem1/Ideal Angular Velocity Source1" , 1U , 1U
, "N*m" , 1.0 , "N*m" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE ,
FALSE , NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Torque" , } , {
"Subsystem1.Ideal_Angular_Velocity_Source1.w" ,
"external_state_machine/Subsystem1/Ideal Angular Velocity Source1" , 1U , 1U
, "rad/s" , 1.0 , "1/s" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE ,
FALSE , FALSE , NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Angular velocity" , }
, { "Subsystem1.Ideal_Rotational_Motion_Sensor1.A" ,
"external_state_machine/Subsystem1/Ideal Rotational Motion Sensor1" , 1U , 1U
, "rad" , 1.0 , "1" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE ,
FALSE , NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "A" , } , {
"Subsystem1.Ideal_Rotational_Motion_Sensor1.C.w" ,
"external_state_machine/Subsystem1/Ideal Rotational Motion Sensor1" , 1U , 1U
, "rad/s" , 1.0 , "1/s" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE ,
TRUE , FALSE , NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Rotational velocity" ,
} , { "Subsystem1.Ideal_Rotational_Motion_Sensor1.R.w" ,
"external_state_machine/Subsystem1/Ideal Rotational Motion Sensor1" , 1U , 1U
, "rad/s" , 1.0 , "1/s" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE ,
FALSE , FALSE , NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Rotational velocity" ,
} , { "Subsystem1.Ideal_Rotational_Motion_Sensor1.W" ,
"external_state_machine/Subsystem1/Ideal Rotational Motion Sensor1" , 1U , 1U
, "rad/s" , 1.0 , "1/s" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE ,
FALSE , FALSE , NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "W" , } , {
"Subsystem1.Ideal_Rotational_Motion_Sensor1.phi" ,
"external_state_machine/Subsystem1/Ideal Rotational Motion Sensor1" , 1U , 1U
, "deg" , 1.0 , "1" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_MANDATORY ,
FALSE , TRUE , NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Angle" , } , {
"Subsystem1.Ideal_Rotational_Motion_Sensor1_A" ,
"external_state_machine/Subsystem1" , 1U , 1U , "rad" , 1.0 , "1" ,
NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Ideal_Rotational_Motion_Sensor1_A" ,
} , { "Subsystem1.Ideal_Rotational_Motion_Sensor1_W" ,
"external_state_machine/Subsystem1" , 1U , 1U , "rad/s" , 1.0 , "1/s" ,
NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Ideal_Rotational_Motion_Sensor1_W" ,
} , { "Subsystem1.Inertia1.I.w" ,
"external_state_machine/Subsystem1/Inertia1" , 1U , 1U , "rad/s" , 1.0 ,
"1/s" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Rotational velocity" , } , {
"Subsystem1.Inertia1.J.w" , "external_state_machine/Subsystem1/Inertia1" , 1U
, 1U , "rad/s" , 1.0 , "1/s" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE
, FALSE , FALSE , NE_FREQTIME_TYPE_TIME , FALSE , TRUE ,
"Rotational velocity" , } , { "Subsystem1.Inertia1.t" ,
"external_state_machine/Subsystem1/Inertia1" , 1U , 1U , "N*m" , 1.0 , "N*m"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Torque" , } , {
"Subsystem1.Inertia1.w" , "external_state_machine/Subsystem1/Inertia1" , 1U ,
1U , "rad/s" , 1.0 , "1/s" , NE_NOMINAL_SOURCE_DERIVED ,
NE_INIT_MODE_MANDATORY , FALSE , TRUE , NE_FREQTIME_TYPE_TIME , TRUE , TRUE ,
"Rotational velocity" , } , {
"Subsystem1.Mechanical_Rotational_Reference1.W.w" ,
"external_state_machine/Subsystem1/Mechanical Rotational Reference1" , 1U ,
1U , "rad/s" , 1.0 , "1/s" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE ,
TRUE , FALSE , NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Rotational velocity" ,
} , { "Subsystem1.Open_Circuit.V.v" ,
"external_state_machine/Subsystem1/Open Circuit" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.Open_Circuit.v" ,
"external_state_machine/Subsystem1/Open Circuit" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.Open_Circuit1.V.v" ,
"external_state_machine/Subsystem1/Open Circuit1" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.Open_Circuit1.v" ,
"external_state_machine/Subsystem1/Open Circuit1" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.Power_Source.Controlled_Voltage_Source.i" ,
"external_state_machine/Subsystem1/Power_Source/Controlled Voltage Source" ,
1U , 1U , "A" , 1.0 , "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE ,
FALSE , FALSE , NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "i" , } , {
"Subsystem1.Power_Source.Controlled_Voltage_Source.n.v" ,
"external_state_machine/Subsystem1/Power_Source/Controlled Voltage Source" ,
1U , 1U , "V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE ,
TRUE , FALSE , NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.Power_Source.Controlled_Voltage_Source.p.v" ,
"external_state_machine/Subsystem1/Power_Source/Controlled Voltage Source" ,
1U , 1U , "V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE ,
FALSE , FALSE , NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.Power_Source.Controlled_Voltage_Source.v" ,
"external_state_machine/Subsystem1/Power_Source/Controlled Voltage Source" ,
1U , 1U , "V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE ,
FALSE , FALSE , NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "v" , } , {
"Subsystem1.Power_Source.Controlled_Voltage_Source.vT" ,
"external_state_machine/Subsystem1/Power_Source/Controlled Voltage Source" ,
1U , 1U , "V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE ,
FALSE , FALSE , NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "vT" , } , {
"Subsystem1.Power_Source.ref_voltage" ,
"external_state_machine/Subsystem1/Power_Source" , 1U , 1U , "1" , 1.0 , "1"
, NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "ref_voltage" , } , {
"Subsystem1.Power_Source.x0.v" ,
"external_state_machine/Subsystem1/Power_Source" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage" , } , {
"Subsystem1.Power_Source.x1.v" ,
"external_state_machine/Subsystem1/Power_Source" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage" , } , {
"Subsystem1.Power_Source_ref_voltage" , "external_state_machine/Subsystem1" ,
1U , 1U , "1" , 1.0 , "1" , NE_NOMINAL_SOURCE_FIXED , NE_INIT_MODE_NONE ,
FALSE , FALSE , NE_FREQTIME_TYPE_TIME , FALSE , TRUE ,
"Power_Source_ref_voltage" , } , { "Subsystem1.Simscape_Component.C.w" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "rad/s" ,
1.0 , "1/s" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Rotational velocity" , } , {
"Subsystem1.Simscape_Component.R.w" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "rad/s" ,
1.0 , "1/s" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Rotational velocity" , } , {
"Subsystem1.Simscape_Component.a1.v" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.Simscape_Component.a2.v" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.Simscape_Component.b1.v" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.Simscape_Component.b2.v" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.Simscape_Component.c1.v" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.Simscape_Component.c2.v" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.Simscape_Component.i_a1" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Strom Strang a1" , } , {
"Subsystem1.Simscape_Component.i_a2" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Strom Strang a2" , } , {
"Subsystem1.Simscape_Component.i_alpha" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Strom in Alpha-Komponente" , } , {
"Subsystem1.Simscape_Component.i_b1" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Strom Strang b1" , } , {
"Subsystem1.Simscape_Component.i_b2" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Strom Strang b2" , } , {
"Subsystem1.Simscape_Component.i_beta" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Strom in Beta-Komponente" , } , {
"Subsystem1.Simscape_Component.i_c1" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Strom Strang c1" , } , {
"Subsystem1.Simscape_Component.i_c2" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Strom Strang c2" , } , {
"Subsystem1.Simscape_Component.i_d" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , TRUE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Strom in d-Achse" , } , {
"Subsystem1.Simscape_Component.i_q" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , TRUE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Strom in q-Achse" , } , {
"Subsystem1.Simscape_Component.i_x" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , TRUE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Strom der x-Komponente" , } , {
"Subsystem1.Simscape_Component.i_y" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , TRUE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Strom der y-Komponente" , } , {
"Subsystem1.Simscape_Component.m_m" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "N*m" ,
1.0 , "N*m" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "inneres elektrisches Drehmoment" , } ,
{ "Subsystem1.Simscape_Component.n1.v" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.Simscape_Component.n2.v" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.Simscape_Component.theta_m" ,
"external_state_machine/Subsystem1/Simscape Component" , 1U , 1U , "rad" ,
1.0 , "1" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , TRUE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE ,
"Startposition des mech. Rotorwinkels bez\303\274glich a-Achse" , } , {
"Subsystem1.Simulink_PS_Converter11_output" ,
"external_state_machine/Subsystem1" , 1U , 1U , "1" , 1.0 , "1" ,
NE_NOMINAL_SOURCE_FIXED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Simulink_PS_Converter11_output" , } ,
{ "Subsystem1.Simulink_PS_Converter12_output" ,
"external_state_machine/Subsystem1" , 1U , 1U , "1" , 1.0 , "1" ,
NE_NOMINAL_SOURCE_FIXED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Simulink_PS_Converter12_output" , } ,
{ "Subsystem1.Simulink_PS_Converter17_output" ,
"external_state_machine/Subsystem1" , 1U , 1U , "1" , 1.0 , "1" ,
NE_NOMINAL_SOURCE_FIXED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Simulink_PS_Converter17_output" , } ,
{ "Subsystem1.Simulink_PS_Converter18_output" ,
"external_state_machine/Subsystem1" , 1U , 1U , "1" , 1.0 , "1" ,
NE_NOMINAL_SOURCE_FIXED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Simulink_PS_Converter18_output" , } ,
{ "Subsystem1.Simulink_PS_Converter19_output" ,
"external_state_machine/Subsystem1" , 1U , 1U , "1" , 1.0 , "1" ,
NE_NOMINAL_SOURCE_FIXED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Simulink_PS_Converter19_output" , } ,
{ "Subsystem1.Simulink_PS_Converter20_output" ,
"external_state_machine/Subsystem1" , 1U , 1U , "1" , 1.0 , "1" ,
NE_NOMINAL_SOURCE_FIXED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Simulink_PS_Converter20_output" , } ,
{ "Subsystem1.Simulink_PS_Converter2_output" ,
"external_state_machine/Subsystem1" , 1U , 1U , "1" , 1.0 , "1" ,
NE_NOMINAL_SOURCE_FIXED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Simulink_PS_Converter2_output" , } ,
{ "Subsystem1.Simulink_PS_Converter3_output" ,
"external_state_machine/Subsystem1" , 1U , 1U , "1" , 1.0 , "1" ,
NE_NOMINAL_SOURCE_FIXED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Simulink_PS_Converter3_output" , } ,
{ "Subsystem1.Simulink_PS_Converter4_output" ,
"external_state_machine/Subsystem1" , 1U , 1U , "1" , 1.0 , "1" ,
NE_NOMINAL_SOURCE_FIXED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Simulink_PS_Converter4_output" , } ,
{ "Subsystem1.Simulink_PS_Converter5_output" ,
"external_state_machine/Subsystem1" , 1U , 1U , "1" , 1.0 , "1" ,
NE_NOMINAL_SOURCE_FIXED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Simulink_PS_Converter5_output" , } ,
{ "Subsystem1.Simulink_PS_Converter6_output" ,
"external_state_machine/Subsystem1" , 1U , 1U , "1" , 1.0 , "1" ,
NE_NOMINAL_SOURCE_FIXED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Simulink_PS_Converter6_output" , } ,
{ "Subsystem1.Simulink_PS_Converter7_output" ,
"external_state_machine/Subsystem1" , 1U , 1U , "1" , 1.0 , "1" ,
NE_NOMINAL_SOURCE_FIXED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Simulink_PS_Converter7_output" , } ,
{ "Subsystem1.Simulink_PS_Converter8_output" ,
"external_state_machine/Subsystem1" , 1U , 1U , "1" , 1.0 , "1" ,
NE_NOMINAL_SOURCE_FIXED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Simulink_PS_Converter8_output" , } ,
{ "Subsystem1.x6ph_Inverter.HB1B" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "1" , 1.0 , "1"
, NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "HB1B" , } , {
"Subsystem1.x6ph_Inverter.HB1T" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "1" , 1.0 , "1"
, NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "HB1T" , } , {
"Subsystem1.x6ph_Inverter.HB2B" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "1" , 1.0 , "1"
, NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "HB2B" , } , {
"Subsystem1.x6ph_Inverter.HB2T" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "1" , 1.0 , "1"
, NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "HB2T" , } , {
"Subsystem1.x6ph_Inverter.HB3B" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "1" , 1.0 , "1"
, NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "HB3B" , } , {
"Subsystem1.x6ph_Inverter.HB3T" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "1" , 1.0 , "1"
, NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "HB3T" , } , {
"Subsystem1.x6ph_Inverter.HB4B" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "1" , 1.0 , "1"
, NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "HB4B" , } , {
"Subsystem1.x6ph_Inverter.HB4T" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "1" , 1.0 , "1"
, NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "HB4T" , } , {
"Subsystem1.x6ph_Inverter.HB5B" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "1" , 1.0 , "1"
, NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "HB5B" , } , {
"Subsystem1.x6ph_Inverter.HB5T" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "1" , 1.0 , "1"
, NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "HB5T" , } , {
"Subsystem1.x6ph_Inverter.HB6B" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "1" , 1.0 , "1"
, NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "HB6B" , } , {
"Subsystem1.x6ph_Inverter.HB6T" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "1" , 1.0 , "1"
, NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "HB6T" , } , {
"Subsystem1.x6ph_Inverter.MOSFET.D.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "G" , } , {
"Subsystem1.x6ph_Inverter.MOSFET.S.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET.mosfet_equation.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "PS" , } , {
"Subsystem1.x6ph_Inverter.MOSFET.mosfet_equation.i" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "i" , } , {
"Subsystem1.x6ph_Inverter.MOSFET.mosfet_equation.isOn" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET" , 1U , 1U , "1" , 1.0
, "1" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "isOn" , } , {
"Subsystem1.x6ph_Inverter.MOSFET.mosfet_equation.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET.mosfet_equation.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET.mosfet_equation.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "v" , } , {
"Subsystem1.x6ph_Inverter.MOSFET.mosfet_equation.power_dissipated" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET" , 1U , 1U , "W" , 1.0
, "kW" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Power dissipated" , } , {
"Subsystem1.x6ph_Inverter.MOSFET1.D.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET1" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET1.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET1" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "G" , } , {
"Subsystem1.x6ph_Inverter.MOSFET1.S.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET1" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET1.mosfet_equation.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET1" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "PS" , } , {
"Subsystem1.x6ph_Inverter.MOSFET1.mosfet_equation.i" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET1" , 1U , 1U , "A" ,
1.0 , "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "i" , } , {
"Subsystem1.x6ph_Inverter.MOSFET1.mosfet_equation.isOn" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET1" , 1U , 1U , "1" ,
1.0 , "1" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "isOn" , } , {
"Subsystem1.x6ph_Inverter.MOSFET1.mosfet_equation.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET1" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET1.mosfet_equation.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET1" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET1.mosfet_equation.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET1" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "v" , } , {
"Subsystem1.x6ph_Inverter.MOSFET1.mosfet_equation.power_dissipated" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET1" , 1U , 1U , "W" ,
1.0 , "kW" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Power dissipated" , } , {
"Subsystem1.x6ph_Inverter.MOSFET10.D.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET10" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET10.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET10" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "G" , } , {
"Subsystem1.x6ph_Inverter.MOSFET10.S.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET10" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET10.mosfet_equation.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET10" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "PS" , } , {
"Subsystem1.x6ph_Inverter.MOSFET10.mosfet_equation.i" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET10" , 1U , 1U , "A" ,
1.0 , "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "i" , } , {
"Subsystem1.x6ph_Inverter.MOSFET10.mosfet_equation.isOn" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET10" , 1U , 1U , "1" ,
1.0 , "1" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "isOn" , } , {
"Subsystem1.x6ph_Inverter.MOSFET10.mosfet_equation.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET10" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET10.mosfet_equation.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET10" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET10.mosfet_equation.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET10" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "v" , } , {
"Subsystem1.x6ph_Inverter.MOSFET10.mosfet_equation.power_dissipated" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET10" , 1U , 1U , "W" ,
1.0 , "kW" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Power dissipated" , } , {
"Subsystem1.x6ph_Inverter.MOSFET11.D.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET11" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET11.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET11" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "G" , } , {
"Subsystem1.x6ph_Inverter.MOSFET11.S.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET11" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET11.mosfet_equation.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET11" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "PS" , } , {
"Subsystem1.x6ph_Inverter.MOSFET11.mosfet_equation.i" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET11" , 1U , 1U , "A" ,
1.0 , "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "i" , } , {
"Subsystem1.x6ph_Inverter.MOSFET11.mosfet_equation.isOn" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET11" , 1U , 1U , "1" ,
1.0 , "1" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "isOn" , } , {
"Subsystem1.x6ph_Inverter.MOSFET11.mosfet_equation.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET11" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET11.mosfet_equation.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET11" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET11.mosfet_equation.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET11" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "v" , } , {
"Subsystem1.x6ph_Inverter.MOSFET11.mosfet_equation.power_dissipated" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET11" , 1U , 1U , "W" ,
1.0 , "kW" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Power dissipated" , } , {
"Subsystem1.x6ph_Inverter.MOSFET2.D.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET2" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET2.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET2" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "G" , } , {
"Subsystem1.x6ph_Inverter.MOSFET2.S.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET2" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET2.mosfet_equation.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET2" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "PS" , } , {
"Subsystem1.x6ph_Inverter.MOSFET2.mosfet_equation.i" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET2" , 1U , 1U , "A" ,
1.0 , "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "i" , } , {
"Subsystem1.x6ph_Inverter.MOSFET2.mosfet_equation.isOn" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET2" , 1U , 1U , "1" ,
1.0 , "1" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "isOn" , } , {
"Subsystem1.x6ph_Inverter.MOSFET2.mosfet_equation.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET2" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET2.mosfet_equation.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET2" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET2.mosfet_equation.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET2" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "v" , } , {
"Subsystem1.x6ph_Inverter.MOSFET2.mosfet_equation.power_dissipated" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET2" , 1U , 1U , "W" ,
1.0 , "kW" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Power dissipated" , } , {
"Subsystem1.x6ph_Inverter.MOSFET3.D.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET3" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET3.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET3" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "G" , } , {
"Subsystem1.x6ph_Inverter.MOSFET3.S.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET3" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET3.mosfet_equation.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET3" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "PS" , } , {
"Subsystem1.x6ph_Inverter.MOSFET3.mosfet_equation.i" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET3" , 1U , 1U , "A" ,
1.0 , "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "i" , } , {
"Subsystem1.x6ph_Inverter.MOSFET3.mosfet_equation.isOn" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET3" , 1U , 1U , "1" ,
1.0 , "1" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "isOn" , } , {
"Subsystem1.x6ph_Inverter.MOSFET3.mosfet_equation.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET3" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET3.mosfet_equation.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET3" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET3.mosfet_equation.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET3" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "v" , } , {
"Subsystem1.x6ph_Inverter.MOSFET3.mosfet_equation.power_dissipated" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET3" , 1U , 1U , "W" ,
1.0 , "kW" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Power dissipated" , } , {
"Subsystem1.x6ph_Inverter.MOSFET4.D.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET4" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET4.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET4" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "G" , } , {
"Subsystem1.x6ph_Inverter.MOSFET4.S.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET4" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET4.mosfet_equation.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET4" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "PS" , } , {
"Subsystem1.x6ph_Inverter.MOSFET4.mosfet_equation.i" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET4" , 1U , 1U , "A" ,
1.0 , "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "i" , } , {
"Subsystem1.x6ph_Inverter.MOSFET4.mosfet_equation.isOn" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET4" , 1U , 1U , "1" ,
1.0 , "1" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "isOn" , } , {
"Subsystem1.x6ph_Inverter.MOSFET4.mosfet_equation.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET4" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET4.mosfet_equation.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET4" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET4.mosfet_equation.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET4" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "v" , } , {
"Subsystem1.x6ph_Inverter.MOSFET4.mosfet_equation.power_dissipated" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET4" , 1U , 1U , "W" ,
1.0 , "kW" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Power dissipated" , } , {
"Subsystem1.x6ph_Inverter.MOSFET5.D.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET5" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET5.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET5" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "G" , } , {
"Subsystem1.x6ph_Inverter.MOSFET5.S.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET5" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET5.mosfet_equation.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET5" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "PS" , } , {
"Subsystem1.x6ph_Inverter.MOSFET5.mosfet_equation.i" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET5" , 1U , 1U , "A" ,
1.0 , "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "i" , } , {
"Subsystem1.x6ph_Inverter.MOSFET5.mosfet_equation.isOn" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET5" , 1U , 1U , "1" ,
1.0 , "1" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "isOn" , } , {
"Subsystem1.x6ph_Inverter.MOSFET5.mosfet_equation.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET5" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET5.mosfet_equation.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET5" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET5.mosfet_equation.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET5" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "v" , } , {
"Subsystem1.x6ph_Inverter.MOSFET5.mosfet_equation.power_dissipated" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET5" , 1U , 1U , "W" ,
1.0 , "kW" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Power dissipated" , } , {
"Subsystem1.x6ph_Inverter.MOSFET6.D.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET6" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET6.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET6" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "G" , } , {
"Subsystem1.x6ph_Inverter.MOSFET6.S.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET6" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET6.mosfet_equation.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET6" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "PS" , } , {
"Subsystem1.x6ph_Inverter.MOSFET6.mosfet_equation.i" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET6" , 1U , 1U , "A" ,
1.0 , "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "i" , } , {
"Subsystem1.x6ph_Inverter.MOSFET6.mosfet_equation.isOn" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET6" , 1U , 1U , "1" ,
1.0 , "1" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "isOn" , } , {
"Subsystem1.x6ph_Inverter.MOSFET6.mosfet_equation.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET6" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET6.mosfet_equation.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET6" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET6.mosfet_equation.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET6" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "v" , } , {
"Subsystem1.x6ph_Inverter.MOSFET6.mosfet_equation.power_dissipated" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET6" , 1U , 1U , "W" ,
1.0 , "kW" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Power dissipated" , } , {
"Subsystem1.x6ph_Inverter.MOSFET7.D.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET7" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET7.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET7" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "G" , } , {
"Subsystem1.x6ph_Inverter.MOSFET7.S.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET7" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET7.mosfet_equation.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET7" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "PS" , } , {
"Subsystem1.x6ph_Inverter.MOSFET7.mosfet_equation.i" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET7" , 1U , 1U , "A" ,
1.0 , "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "i" , } , {
"Subsystem1.x6ph_Inverter.MOSFET7.mosfet_equation.isOn" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET7" , 1U , 1U , "1" ,
1.0 , "1" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "isOn" , } , {
"Subsystem1.x6ph_Inverter.MOSFET7.mosfet_equation.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET7" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET7.mosfet_equation.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET7" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET7.mosfet_equation.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET7" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "v" , } , {
"Subsystem1.x6ph_Inverter.MOSFET7.mosfet_equation.power_dissipated" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET7" , 1U , 1U , "W" ,
1.0 , "kW" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Power dissipated" , } , {
"Subsystem1.x6ph_Inverter.MOSFET8.D.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET8" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET8.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET8" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "G" , } , {
"Subsystem1.x6ph_Inverter.MOSFET8.S.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET8" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET8.mosfet_equation.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET8" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "PS" , } , {
"Subsystem1.x6ph_Inverter.MOSFET8.mosfet_equation.i" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET8" , 1U , 1U , "A" ,
1.0 , "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "i" , } , {
"Subsystem1.x6ph_Inverter.MOSFET8.mosfet_equation.isOn" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET8" , 1U , 1U , "1" ,
1.0 , "1" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "isOn" , } , {
"Subsystem1.x6ph_Inverter.MOSFET8.mosfet_equation.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET8" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET8.mosfet_equation.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET8" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET8.mosfet_equation.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET8" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "v" , } , {
"Subsystem1.x6ph_Inverter.MOSFET8.mosfet_equation.power_dissipated" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET8" , 1U , 1U , "W" ,
1.0 , "kW" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Power dissipated" , } , {
"Subsystem1.x6ph_Inverter.MOSFET9.D.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET9" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET9.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET9" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "G" , } , {
"Subsystem1.x6ph_Inverter.MOSFET9.S.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET9" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET9.mosfet_equation.G" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET9" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "PS" , } , {
"Subsystem1.x6ph_Inverter.MOSFET9.mosfet_equation.i" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET9" , 1U , 1U , "A" ,
1.0 , "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "i" , } , {
"Subsystem1.x6ph_Inverter.MOSFET9.mosfet_equation.isOn" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET9" , 1U , 1U , "1" ,
1.0 , "1" , NE_NOMINAL_SOURCE_DERIVED , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "isOn" , } , {
"Subsystem1.x6ph_Inverter.MOSFET9.mosfet_equation.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET9" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET9.mosfet_equation.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET9" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.MOSFET9.mosfet_equation.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET9" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "v" , } , {
"Subsystem1.x6ph_Inverter.MOSFET9.mosfet_equation.power_dissipated" ,
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET9" , 1U , 1U , "W" ,
1.0 , "kW" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Power dissipated" , } , {
"Subsystem1.x6ph_Inverter.U_dc_0.v" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.U_dc_1.v" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor.V" ,
"external_state_machine/Subsystem1/6ph_Inverter/Voltage Sensor" , 1U , 1U ,
"V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE
, NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "V" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/Voltage Sensor" , 1U , 1U ,
"V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE
, NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/Voltage Sensor" , 1U , 1U ,
"V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE
, NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor1.V" ,
"external_state_machine/Subsystem1/6ph_Inverter/Voltage Sensor1" , 1U , 1U ,
"V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE
, NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "V" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor1.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/Voltage Sensor1" , 1U , 1U ,
"V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE
, NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor1.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/Voltage Sensor1" , 1U , 1U ,
"V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE
, NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor1_V" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage_Sensor1_V" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor2.V" ,
"external_state_machine/Subsystem1/6ph_Inverter/Voltage Sensor2" , 1U , 1U ,
"V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE
, NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "V" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor2.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/Voltage Sensor2" , 1U , 1U ,
"V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE
, NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor2.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/Voltage Sensor2" , 1U , 1U ,
"V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE
, NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor2_V" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage_Sensor2_V" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor3.V" ,
"external_state_machine/Subsystem1/6ph_Inverter/Voltage Sensor3" , 1U , 1U ,
"V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE
, NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "V" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor3.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/Voltage Sensor3" , 1U , 1U ,
"V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE
, NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor3.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/Voltage Sensor3" , 1U , 1U ,
"V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE
, NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor3_V" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage_Sensor3_V" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor4.V" ,
"external_state_machine/Subsystem1/6ph_Inverter/Voltage Sensor4" , 1U , 1U ,
"V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE
, NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "V" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor4.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/Voltage Sensor4" , 1U , 1U ,
"V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE
, NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor4.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/Voltage Sensor4" , 1U , 1U ,
"V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE
, NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor4_V" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage_Sensor4_V" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor5.V" ,
"external_state_machine/Subsystem1/6ph_Inverter/Voltage Sensor5" , 1U , 1U ,
"V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE
, NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "V" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor5.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/Voltage Sensor5" , 1U , 1U ,
"V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE
, NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor5.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/Voltage Sensor5" , 1U , 1U ,
"V" , 1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE
, NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor5_V" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage_Sensor5_V" , } , {
"Subsystem1.x6ph_Inverter.Voltage_Sensor_V" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage_Sensor_V" , } , {
"Subsystem1.x6ph_Inverter.i_1_ph.I" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_1_ph" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "I" , } , {
"Subsystem1.x6ph_Inverter.i_1_ph.i1" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_1_ph" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Current" , } , {
"Subsystem1.x6ph_Inverter.i_1_ph.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_1_ph" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.i_1_ph.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_1_ph" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.i_1_ph_I" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "A" , 1.0 , "A"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "i_1_ph_I" , } , {
"Subsystem1.x6ph_Inverter.i_2_ph.I" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_2_ph" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "I" , } , {
"Subsystem1.x6ph_Inverter.i_2_ph.i1" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_2_ph" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Current" , } , {
"Subsystem1.x6ph_Inverter.i_2_ph.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_2_ph" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.i_2_ph.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_2_ph" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.i_2_ph_I" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "A" , 1.0 , "A"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "i_2_ph_I" , } , {
"Subsystem1.x6ph_Inverter.i_3_ph.I" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_3_ph" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "I" , } , {
"Subsystem1.x6ph_Inverter.i_3_ph.i1" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_3_ph" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Current" , } , {
"Subsystem1.x6ph_Inverter.i_3_ph.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_3_ph" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.i_3_ph.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_3_ph" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.i_3_ph_I" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "A" , 1.0 , "A"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "i_3_ph_I" , } , {
"Subsystem1.x6ph_Inverter.i_4_ph.I" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_4_ph" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "I" , } , {
"Subsystem1.x6ph_Inverter.i_4_ph.i1" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_4_ph" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Current" , } , {
"Subsystem1.x6ph_Inverter.i_4_ph.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_4_ph" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.i_4_ph.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_4_ph" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.i_4_ph_I" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "A" , 1.0 , "A"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "i_4_ph_I" , } , {
"Subsystem1.x6ph_Inverter.i_5_ph.I" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_5_ph" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "I" , } , {
"Subsystem1.x6ph_Inverter.i_5_ph.i1" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_5_ph" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Current" , } , {
"Subsystem1.x6ph_Inverter.i_5_ph.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_5_ph" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.i_5_ph.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_5_ph" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.i_5_ph_I" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "A" , 1.0 , "A"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "i_5_ph_I" , } , {
"Subsystem1.x6ph_Inverter.i_6_ph.I" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_6_ph" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "I" , } , {
"Subsystem1.x6ph_Inverter.i_6_ph.i1" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_6_ph" , 1U , 1U , "A" , 1.0
, "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Current" , } , {
"Subsystem1.x6ph_Inverter.i_6_ph.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_6_ph" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.i_6_ph.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_6_ph" , 1U , 1U , "V" , 1.0
, "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.i_6_ph_I" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "A" , 1.0 , "A"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "i_6_ph_I" , } , {
"Subsystem1.x6ph_Inverter.i_dc_ph.I" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_dc_ph" , 1U , 1U , "A" ,
1.0 , "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "I" , } , {
"Subsystem1.x6ph_Inverter.i_dc_ph.i1" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_dc_ph" , 1U , 1U , "A" ,
1.0 , "A" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Current" , } , {
"Subsystem1.x6ph_Inverter.i_dc_ph.n.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_dc_ph" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.i_dc_ph.p.v" ,
"external_state_machine/Subsystem1/6ph_Inverter/i_dc_ph" , 1U , 1U , "V" ,
1.0 , "V" , NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , TRUE , FALSE ,
NE_FREQTIME_TYPE_TIME , TRUE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.i_dc_ph_I" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "A" , 1.0 , "A"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "i_dc_ph_I" , } , {
"Subsystem1.x6ph_Inverter.u_1_ph.v" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.u_2_ph.v" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.u_3_ph.v" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.u_4_ph.v" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.u_5_ph.v" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage" , } , {
"Subsystem1.x6ph_Inverter.u_6_ph.v" ,
"external_state_machine/Subsystem1/6ph_Inverter" , 1U , 1U , "V" , 1.0 , "V"
, NE_NOMINAL_SOURCE_MODEL , NE_INIT_MODE_NONE , FALSE , FALSE ,
NE_FREQTIME_TYPE_TIME , FALSE , TRUE , "Voltage" , } } ; static NeModeData *
s_major_mode_data = NULL ; static NeZCData s_zc_data [ 12 ] = { {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET" , 1U , 0U ,
"Subsystem1.x6ph_Inverter.MOSFET.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, NE_ZC_TYPE_FALSE , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET1" , 1U , 1U ,
"Subsystem1.x6ph_Inverter.MOSFET1.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, NE_ZC_TYPE_FALSE , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET10" , 1U , 2U ,
"Subsystem1.x6ph_Inverter.MOSFET10.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, NE_ZC_TYPE_FALSE , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET11" , 1U , 3U ,
"Subsystem1.x6ph_Inverter.MOSFET11.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, NE_ZC_TYPE_FALSE , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET2" , 1U , 4U ,
"Subsystem1.x6ph_Inverter.MOSFET2.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, NE_ZC_TYPE_FALSE , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET3" , 1U , 5U ,
"Subsystem1.x6ph_Inverter.MOSFET3.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, NE_ZC_TYPE_FALSE , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET4" , 1U , 6U ,
"Subsystem1.x6ph_Inverter.MOSFET4.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, NE_ZC_TYPE_FALSE , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET5" , 1U , 7U ,
"Subsystem1.x6ph_Inverter.MOSFET5.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, NE_ZC_TYPE_FALSE , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET6" , 1U , 8U ,
"Subsystem1.x6ph_Inverter.MOSFET6.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, NE_ZC_TYPE_FALSE , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET7" , 1U , 9U ,
"Subsystem1.x6ph_Inverter.MOSFET7.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, NE_ZC_TYPE_FALSE , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET8" , 1U , 10U ,
"Subsystem1.x6ph_Inverter.MOSFET8.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, NE_ZC_TYPE_FALSE , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET9" , 1U , 11U ,
"Subsystem1.x6ph_Inverter.MOSFET9.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, NE_ZC_TYPE_FALSE , } } ; static NeRange s_range [ 12 ] = { {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } } ; static NeAssertData
s_assert_data [ 16 ] = { {
"external_state_machine/Subsystem1/DC_link/Capacitor" , 1U , 0U ,
"Subsystem1.DC_link.Capacitor.power_dissipated" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/simscape/library/m/+foundation/+electrical/+elements/capacitor.ssc"
, FALSE ,
"In power, the exponent must be positive when the base is equal to zero." ,
"physmod:common:mf:expr:analyze:RequireExponentPositive" , } , {
"external_state_machine/Subsystem1/DC_link/Capacitor" , 1U , 1U ,
"Subsystem1.DC_link.Capacitor.power_dissipated" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/simscape/library/m/+foundation/+electrical/+elements/capacitor.ssc"
, FALSE ,
"In power, the base must be nonnegative when the exponent is not an integer."
, "physmod:common:mf:expr:analyze:RequireBaseNonnegative" , } , {
"external_state_machine/Subsystem1/DC_link/Capacitor" , 1U , 2U ,
"Subsystem1.DC_link.Capacitor.power_dissipated" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/simscape/library/m/+foundation/+electrical/+elements/capacitor.ssc"
, FALSE ,
"In power, the exponent must be positive when the base is equal to zero." ,
"physmod:common:mf:expr:analyze:RequireExponentPositive" , } , {
"external_state_machine/Subsystem1/DC_link/Capacitor" , 1U , 3U ,
"Subsystem1.DC_link.Capacitor.power_dissipated" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/simscape/library/m/+foundation/+electrical/+elements/capacitor.ssc"
, FALSE ,
"In power, the base must be nonnegative when the exponent is not an integer."
, "physmod:common:mf:expr:analyze:RequireBaseNonnegative" , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET" , 1U , 4U ,
"Subsystem1.x6ph_Inverter.MOSFET.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, FALSE , "In divide, the denominator must be nonzero." ,
"physmod:common:mf:expr:analyze:RequireDenominatorNonzero" , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET1" , 1U , 5U ,
"Subsystem1.x6ph_Inverter.MOSFET1.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, FALSE , "In divide, the denominator must be nonzero." ,
"physmod:common:mf:expr:analyze:RequireDenominatorNonzero" , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET10" , 1U , 6U ,
"Subsystem1.x6ph_Inverter.MOSFET10.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, FALSE , "In divide, the denominator must be nonzero." ,
"physmod:common:mf:expr:analyze:RequireDenominatorNonzero" , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET11" , 1U , 7U ,
"Subsystem1.x6ph_Inverter.MOSFET11.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, FALSE , "In divide, the denominator must be nonzero." ,
"physmod:common:mf:expr:analyze:RequireDenominatorNonzero" , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET2" , 1U , 8U ,
"Subsystem1.x6ph_Inverter.MOSFET2.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, FALSE , "In divide, the denominator must be nonzero." ,
"physmod:common:mf:expr:analyze:RequireDenominatorNonzero" , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET3" , 1U , 9U ,
"Subsystem1.x6ph_Inverter.MOSFET3.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, FALSE , "In divide, the denominator must be nonzero." ,
"physmod:common:mf:expr:analyze:RequireDenominatorNonzero" , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET4" , 1U , 10U ,
"Subsystem1.x6ph_Inverter.MOSFET4.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, FALSE , "In divide, the denominator must be nonzero." ,
"physmod:common:mf:expr:analyze:RequireDenominatorNonzero" , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET5" , 1U , 11U ,
"Subsystem1.x6ph_Inverter.MOSFET5.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, FALSE , "In divide, the denominator must be nonzero." ,
"physmod:common:mf:expr:analyze:RequireDenominatorNonzero" , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET6" , 1U , 12U ,
"Subsystem1.x6ph_Inverter.MOSFET6.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, FALSE , "In divide, the denominator must be nonzero." ,
"physmod:common:mf:expr:analyze:RequireDenominatorNonzero" , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET7" , 1U , 13U ,
"Subsystem1.x6ph_Inverter.MOSFET7.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, FALSE , "In divide, the denominator must be nonzero." ,
"physmod:common:mf:expr:analyze:RequireDenominatorNonzero" , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET8" , 1U , 14U ,
"Subsystem1.x6ph_Inverter.MOSFET8.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, FALSE , "In divide, the denominator must be nonzero." ,
"physmod:common:mf:expr:analyze:RequireDenominatorNonzero" , } , {
"external_state_machine/Subsystem1/6ph_Inverter/MOSFET9" , 1U , 15U ,
"Subsystem1.x6ph_Inverter.MOSFET9.mosfet_equation" ,
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, FALSE , "In divide, the denominator must be nonzero." ,
"physmod:common:mf:expr:analyze:RequireDenominatorNonzero" , } } ; static
NeRange s_assert_range [ 16 ] = { {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/simscape/library/m/+foundation/+electrical/+elements/capacitor.ssc"
, 26U , 29U , 26U , 30U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/simscape/library/m/+foundation/+electrical/+elements/capacitor.ssc"
, 26U , 27U , 26U , 28U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/simscape/library/m/+foundation/+electrical/+elements/capacitor.ssc"
, 26U , 36U , 26U , 37U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/simscape/library/m/+foundation/+electrical/+elements/capacitor.ssc"
, 26U , 33U , 26U , 35U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } } ; static NeAssertData *
s_param_assert_data = NULL ; static NeRange * s_param_assert_range = NULL ;
static NeAssertData * s_initial_assert_data = NULL ; static NeRange *
s_initial_assert_range = NULL ; static NeRange s_equation_range [ 54 ] = { {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/simscape/library/m/+foundation/+electrical/+elements/capacitor.ssc"
, 36U , 5U , 36U , 25U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/simscape/library/m/+foundation/+mechanical/+sensors/angular_velocity.ssc"
, 46U , 5U , 46U , 12U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/simscape/library/m/+foundation/+mechanical/+sensors/angular_velocity.ssc"
, 46U , 9U , 46U , 17U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/simscape/library/m/+foundation/+mechanical/+rotational/inertia.ssc"
, 44U , 5U , 44U , 21U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/simscape/library/m/+foundation/+mechanical/+rotational/inertia.ssc"
, 44U , 20U , 44U , 25U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/GIT/UltraZohm/software/ultrazohm_sw_PullRequests2/ip_cores/uz_mpc_6ph/SixPhase_PMSM.ssc"
, 95U , 13U , 95U , 31U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/GIT/UltraZohm/software/ultrazohm_sw_PullRequests2/ip_cores/uz_mpc_6ph/SixPhase_PMSM.ssc"
, 95U , 24U , 95U , 35U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/GIT/UltraZohm/software/ultrazohm_sw_PullRequests2/ip_cores/uz_mpc_6ph/SixPhase_PMSM.ssc"
, 98U , 13U , 98U , 73U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/GIT/UltraZohm/software/ultrazohm_sw_PullRequests2/ip_cores/uz_mpc_6ph/SixPhase_PMSM.ssc"
, 99U , 13U , 99U , 96U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/GIT/UltraZohm/software/ultrazohm_sw_PullRequests2/ip_cores/uz_mpc_6ph/SixPhase_PMSM.ssc"
, 100U , 13U , 100U , 47U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/GIT/UltraZohm/software/ultrazohm_sw_PullRequests2/ip_cores/uz_mpc_6ph/SixPhase_PMSM.ssc"
, 101U , 13U , 101U , 47U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/simscape/library/m/+foundation/+electrical/+elements/capacitor.ssc"
, 35U , 5U , 35U , 18U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/simscape/library/m/+foundation/+mechanical/+sources/angular_velocity.ssc"
, 36U , 5U , 36U , 19U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/GIT/UltraZohm/software/ultrazohm_sw_PullRequests2/ip_cores/uz_mpc_6ph/SixPhase_PMSM.ssc"
, 108U , 13U , 108U , 110U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/GIT/UltraZohm/software/ultrazohm_sw_PullRequests2/ip_cores/uz_mpc_6ph/SixPhase_PMSM.ssc"
, 109U , 13U , 109U , 110U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/GIT/UltraZohm/software/ultrazohm_sw_PullRequests2/ip_cores/uz_mpc_6ph/SixPhase_PMSM.ssc"
, 114U , 13U , 114U , 73U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/GIT/UltraZohm/software/ultrazohm_sw_PullRequests2/ip_cores/uz_mpc_6ph/SixPhase_PMSM.ssc"
, 115U , 13U , 115U , 73U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/GIT/UltraZohm/software/ultrazohm_sw_PullRequests2/ip_cores/uz_mpc_6ph/SixPhase_PMSM.ssc"
, 118U , 13U , 118U , 63U , NE_RANGE_TYPE_NORMAL , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } , {
 "C:/Program Files/MATLAB/R2021a/toolbox/physmod/elec/library/m/+ee/+semiconductors/+mosfet_ideal/mosfet_equation.sscp"
, 1U , 1U , 1U , 1U , NE_RANGE_TYPE_PROTECTED , } } ; static NeRange *
s_cer_range = NULL ; static NeRange * s_icr_range = NULL ; static
NeParameterData * s_logical_parameter_data = NULL ; static NeParameterData *
s_integer_parameter_data = NULL ; static NeParameterData *
s_index_parameter_data = NULL ; static NeParameterData *
s_real_parameter_data = NULL ; static NeDsMethodOutput * ds_output_m_p (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mM_P . mNumCol = 27 ;
out -> mM_P . mNumRow = 27 ; out -> mM_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 28 ) ; out -> mM_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 8 ) ;
return out ; } static NeDsMethodOutput * ds_output_m ( const NeDynamicSystem
* ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out
= ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mM . mN = 8 ; out -> mM . mX = ( real_T * )
allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 8 ) ; return out ;
} static NeDsMethodOutput * ds_output_vmm ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = (
NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mVMM . mN = 8 ; out -> mVMM . mX = (
boolean_T * ) allocator -> mCallocFcn ( allocator , sizeof ( boolean_T ) , 8
) ; return out ; } static NeDsMethodOutput * ds_output_dxm_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDXM_P . mNumCol = 27 ; out ->
mDXM_P . mNumRow = 8 ; out -> mDXM_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 28 ) ; out -> mDXM_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 ) ;
return out ; } static NeDsMethodOutput * ds_output_dxm ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDXM . mN = 0 ; out -> mDXM . mX
= ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 0 )
; return out ; } static NeDsMethodOutput * ds_output_ddm_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDDM_P . mNumCol = 0 ; out ->
mDDM_P . mNumRow = 8 ; out -> mDDM_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 1 ) ; out -> mDDM_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 ) ;
return out ; } static NeDsMethodOutput * ds_output_ddm ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDDM . mN = 0 ; out -> mDDM . mX
= ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 0 )
; return out ; } static NeDsMethodOutput * ds_output_dum_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDUM_P . mNumCol = 14 ; out ->
mDUM_P . mNumRow = 8 ; out -> mDUM_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 15 ) ; out -> mDUM_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 ) ;
return out ; } static NeDsMethodOutput * ds_output_dum ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDUM . mN = 0 ; out -> mDUM . mX
= ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 0 )
; return out ; } static NeDsMethodOutput * ds_output_dtm_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDTM_P . mNumCol = 1 ; out ->
mDTM_P . mNumRow = 8 ; out -> mDTM_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 2 ) ; out -> mDTM_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 ) ;
return out ; } static NeDsMethodOutput * ds_output_dtm ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDTM . mN = 0 ; out -> mDTM . mX
= ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 0 )
; return out ; } static NeDsMethodOutput * ds_output_dpm_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDPM_P . mNumCol = 0 ; out ->
mDPM_P . mNumRow = 8 ; out -> mDPM_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 1 ) ; out -> mDPM_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 ) ;
return out ; } static NeDsMethodOutput * ds_output_dpm ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDPM . mN = 0 ; out -> mDPM . mX
= ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 0 )
; return out ; } static NeDsMethodOutput * ds_output_a_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mA_P . mNumCol = 27 ; out ->
mA_P . mNumRow = 27 ; out -> mA_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 28 ) ; out -> mA_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 39 ) ;
return out ; } static NeDsMethodOutput * ds_output_a ( const NeDynamicSystem
* ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out
= ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mA . mN = 39 ; out -> mA . mX = ( real_T *
) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 39 ) ; return out
; } static NeDsMethodOutput * ds_output_b_p ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = (
NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mB_P . mNumCol = 14 ; out -> mB_P . mNumRow
= 27 ; out -> mB_P . mJc = ( int32_T * ) allocator -> mCallocFcn ( allocator
, sizeof ( int32_T ) , 15 ) ; out -> mB_P . mIr = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 2 ) ; return out ; } static
NeDsMethodOutput * ds_output_b ( const NeDynamicSystem * ds , PmAllocator *
allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = ( NeDsMethodOutput
* ) allocator -> mCallocFcn ( allocator , sizeof ( NeDsMethodOutput ) , 1 ) ;
out -> mB . mN = 2 ; out -> mB . mX = ( real_T * ) allocator -> mCallocFcn (
allocator , sizeof ( real_T ) , 2 ) ; return out ; } static NeDsMethodOutput
* ds_output_c_p ( const NeDynamicSystem * ds , PmAllocator * allocator ) {
NeDsMethodOutput * out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator
-> mCallocFcn ( allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mC_P .
mNumCol = 1 ; out -> mC_P . mNumRow = 27 ; out -> mC_P . mJc = ( int32_T * )
allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 2 ) ; out -> mC_P
. mIr = ( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T
) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_c ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mC . mN = 0 ; out -> mC . mX = (
real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 0 ) ;
return out ; } static NeDsMethodOutput * ds_output_f ( const NeDynamicSystem
* ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out
= ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mF . mN = 27 ; out -> mF . mX = ( real_T *
) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 27 ) ; return out
; } static NeDsMethodOutput * ds_output_vmf ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = (
NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mVMF . mN = 27 ; out -> mVMF . mX = (
boolean_T * ) allocator -> mCallocFcn ( allocator , sizeof ( boolean_T ) , 27
) ; return out ; } static NeDsMethodOutput * ds_output_vpf ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mVPF . mN = 27 ; out -> mVPF .
mX = ( boolean_T * ) allocator -> mCallocFcn ( allocator , sizeof ( boolean_T
) , 27 ) ; return out ; } static NeDsMethodOutput * ds_output_vsf ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mVSF . mN = 27 ; out -> mVSF .
mX = ( boolean_T * ) allocator -> mCallocFcn ( allocator , sizeof ( boolean_T
) , 27 ) ; return out ; } static NeDsMethodOutput * ds_output_slf ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mSLF . mN = 27 ; out -> mSLF .
mX = ( boolean_T * ) allocator -> mCallocFcn ( allocator , sizeof ( boolean_T
) , 27 ) ; return out ; } static NeDsMethodOutput * ds_output_slf0 ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mSLF0 . mN = 27 ; out -> mSLF0 .
mX = ( boolean_T * ) allocator -> mCallocFcn ( allocator , sizeof ( boolean_T
) , 27 ) ; return out ; } static NeDsMethodOutput * ds_output_dxf_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDXF_P . mNumCol = 27 ; out ->
mDXF_P . mNumRow = 27 ; out -> mDXF_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 28 ) ; out -> mDXF_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 62 ) ;
return out ; } static NeDsMethodOutput * ds_output_dxf ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDXF . mN = 62 ; out -> mDXF .
mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) ,
62 ) ; return out ; } static NeDsMethodOutput * ds_output_duf_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDUF_P . mNumCol = 14 ; out ->
mDUF_P . mNumRow = 27 ; out -> mDUF_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 15 ) ; out -> mDUF_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 6 ) ;
return out ; } static NeDsMethodOutput * ds_output_duf ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDUF . mN = 6 ; out -> mDUF . mX
= ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 6 )
; return out ; } static NeDsMethodOutput * ds_output_dtf_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDTF_P . mNumCol = 1 ; out ->
mDTF_P . mNumRow = 27 ; out -> mDTF_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 2 ) ; out -> mDTF_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 ) ;
return out ; } static NeDsMethodOutput * ds_output_dtf ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDTF . mN = 0 ; out -> mDTF . mX
= ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 0 )
; return out ; } static NeDsMethodOutput * ds_output_ddf_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDDF_P . mNumCol = 0 ; out ->
mDDF_P . mNumRow = 27 ; out -> mDDF_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 1 ) ; out -> mDDF_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 ) ;
return out ; } static NeDsMethodOutput * ds_output_ddf ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDDF . mN = 0 ; out -> mDDF . mX
= ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 0 )
; return out ; } static NeDsMethodOutput * ds_output_dpdxf_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDPDXF_P . mNumCol = 0 ; out ->
mDPDXF_P . mNumRow = 62 ; out -> mDPDXF_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 1 ) ; out -> mDPDXF_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 ) ;
return out ; } static NeDsMethodOutput * ds_output_dpdxf ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDPDXF . mN = 0 ; out -> mDPDXF
. mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) ,
0 ) ; return out ; } static NeDsMethodOutput * ds_output_dwf_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDWF_P . mNumCol = 0 ; out ->
mDWF_P . mNumRow = 27 ; out -> mDWF_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 1 ) ; out -> mDWF_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 ) ;
return out ; } static NeDsMethodOutput * ds_output_dwf ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDWF . mN = 0 ; out -> mDWF . mX
= ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 0 )
; return out ; } static NeDsMethodOutput * ds_output_tduf_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mTDUF_P . mNumCol = 14 ; out ->
mTDUF_P . mNumRow = 27 ; out -> mTDUF_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 15 ) ; out -> mTDUF_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 20 ) ;
return out ; } static NeDsMethodOutput * ds_output_tdxf_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mTDXF_P . mNumCol = 27 ; out ->
mTDXF_P . mNumRow = 27 ; out -> mTDXF_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 28 ) ; out -> mTDXF_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 99 ) ;
return out ; } static NeDsMethodOutput * ds_output_dnf_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDNF_P . mNumCol = 15 ; out ->
mDNF_P . mNumRow = 27 ; out -> mDNF_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 16 ) ; out -> mDNF_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 ) ;
return out ; } static NeDsMethodOutput * ds_output_dnf ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDNF . mN = 0 ; out -> mDNF . mX
= ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 0 )
; return out ; } static NeDsMethodOutput * ds_output_dnf_v_x ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDNF_V_X . mN = 27 ; out ->
mDNF_V_X . mX = ( boolean_T * ) allocator -> mCallocFcn ( allocator , sizeof
( boolean_T ) , 27 ) ; return out ; } static NeDsMethodOutput * ds_output_cer
( const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mCER . mN = 0 ; out ->
mCER . mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof (
real_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_dxcer (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDXCER . mN = 0 ; out
-> mDXCER . mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof (
real_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_dxcer_p (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDXCER_P . mNumCol =
27 ; out -> mDXCER_P . mNumRow = 0 ; out -> mDXCER_P . mJc = ( int32_T * )
allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 28 ) ; out ->
mDXCER_P . mIr = ( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof (
int32_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_ic (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mIC . mN = 27 ; out ->
mIC . mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T
) , 27 ) ; return out ; } static NeDsMethodOutput * ds_output_icr ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mICR . mN = 0 ; out -> mICR . mX
= ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 0 )
; return out ; } static NeDsMethodOutput * ds_output_icr_im ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mICR_IM . mN = 0 ; out ->
mICR_IM . mX = ( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof (
int32_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_icr_id (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mICR_ID . mN = 0 ; out
-> mICR_ID . mX = ( boolean_T * ) allocator -> mCallocFcn ( allocator ,
sizeof ( boolean_T ) , 0 ) ; return out ; } static NeDsMethodOutput *
ds_output_icr_il ( const NeDynamicSystem * ds , PmAllocator * allocator ) {
NeDsMethodOutput * out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator
-> mCallocFcn ( allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out ->
mICR_IL . mN = 0 ; out -> mICR_IL . mX = ( boolean_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( boolean_T ) , 0 ) ; return out ; } static
NeDsMethodOutput * ds_output_dxicr ( const NeDynamicSystem * ds , PmAllocator
* allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = (
NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mDXICR . mN = 0 ; out -> mDXICR . mX = (
real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 0 ) ;
return out ; } static NeDsMethodOutput * ds_output_dxicr_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDXICR_P . mNumCol = 27 ; out ->
mDXICR_P . mNumRow = 0 ; out -> mDXICR_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 28 ) ; out -> mDXICR_P . mIr =
( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 )
; return out ; } static NeDsMethodOutput * ds_output_ddicr ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDDICR . mN = 0 ; out -> mDDICR
. mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) ,
0 ) ; return out ; } static NeDsMethodOutput * ds_output_ddicr_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDDICR_P . mNumCol = 0 ; out ->
mDDICR_P . mNumRow = 0 ; out -> mDDICR_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 1 ) ; out -> mDDICR_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 ) ;
return out ; } static NeDsMethodOutput * ds_output_tduicr_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mTDUICR_P . mNumCol = 14 ; out
-> mTDUICR_P . mNumRow = 0 ; out -> mTDUICR_P . mJc = ( int32_T * ) allocator
-> mCallocFcn ( allocator , sizeof ( int32_T ) , 15 ) ; out -> mTDUICR_P .
mIr = ( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T )
, 0 ) ; return out ; } static NeDsMethodOutput * ds_output_icrm_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mICRM_P . mNumCol = 27 ; out ->
mICRM_P . mNumRow = 0 ; out -> mICRM_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 28 ) ; out -> mICRM_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 ) ;
return out ; } static NeDsMethodOutput * ds_output_icrm ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mICRM . mN = 0 ; out -> mICRM .
mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 0
) ; return out ; } static NeDsMethodOutput * ds_output_dxicrm_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDXICRM_P . mNumCol = 27 ; out
-> mDXICRM_P . mNumRow = 0 ; out -> mDXICRM_P . mJc = ( int32_T * ) allocator
-> mCallocFcn ( allocator , sizeof ( int32_T ) , 28 ) ; out -> mDXICRM_P .
mIr = ( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T )
, 0 ) ; return out ; } static NeDsMethodOutput * ds_output_dxicrm ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDXICRM . mN = 0 ; out ->
mDXICRM . mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof (
real_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_ddicrm_p
( const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDDICRM_P . mNumCol =
0 ; out -> mDDICRM_P . mNumRow = 0 ; out -> mDDICRM_P . mJc = ( int32_T * )
allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 1 ) ; out ->
mDDICRM_P . mIr = ( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof
( int32_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_ddicrm
( const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDDICRM . mN = 0 ; out
-> mDDICRM . mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof (
real_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_mduy_p (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mMDUY_P . mNumCol = 14
; out -> mMDUY_P . mNumRow = 16 ; out -> mMDUY_P . mJc = ( int32_T * )
allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 15 ) ; out ->
mMDUY_P . mIr = ( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof (
int32_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_mdxy_p (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mMDXY_P . mNumCol = 27
; out -> mMDXY_P . mNumRow = 16 ; out -> mMDXY_P . mJc = ( int32_T * )
allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 28 ) ; out ->
mMDXY_P . mIr = ( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof (
int32_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_tduy_p (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mTDUY_P . mNumCol = 14
; out -> mTDUY_P . mNumRow = 16 ; out -> mTDUY_P . mJc = ( int32_T * )
allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 15 ) ; out ->
mTDUY_P . mIr = ( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof (
int32_T ) , 1 ) ; return out ; } static NeDsMethodOutput * ds_output_tdxy_p (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mTDXY_P . mNumCol = 27
; out -> mTDXY_P . mNumRow = 16 ; out -> mTDXY_P . mJc = ( int32_T * )
allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 28 ) ; out ->
mTDXY_P . mIr = ( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof (
int32_T ) , 22 ) ; return out ; } static NeDsMethodOutput * ds_output_y (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mY . mN = 16 ; out ->
mY . mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T
) , 16 ) ; return out ; } static NeDsMethodOutput * ds_output_dxy_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDXY_P . mNumCol = 27 ; out ->
mDXY_P . mNumRow = 16 ; out -> mDXY_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 28 ) ; out -> mDXY_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 22 ) ;
return out ; } static NeDsMethodOutput * ds_output_dxy ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDXY . mN = 22 ; out -> mDXY .
mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) ,
22 ) ; return out ; } static NeDsMethodOutput * ds_output_duy_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDUY_P . mNumCol = 14 ; out ->
mDUY_P . mNumRow = 16 ; out -> mDUY_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 15 ) ; out -> mDUY_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 1 ) ;
return out ; } static NeDsMethodOutput * ds_output_duy ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDUY . mN = 1 ; out -> mDUY . mX
= ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 1 )
; return out ; } static NeDsMethodOutput * ds_output_dty_p ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDTY_P . mNumCol = 1 ; out ->
mDTY_P . mNumRow = 16 ; out -> mDTY_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 2 ) ; out -> mDTY_P . mIr = (
int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 ) ;
return out ; } static NeDsMethodOutput * ds_output_dty ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDTY . mN = 0 ; out -> mDTY . mX
= ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 0 )
; return out ; } static NeDsMethodOutput * ds_output_mode ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mMODE . mN = 12 ; out -> mMODE .
mX = ( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) ,
12 ) ; return out ; } static NeDsMethodOutput * ds_output_zc ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mZC . mN = 12 ; out -> mZC . mX
= ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 12 )
; return out ; } static NeDsMethodOutput * ds_output_cache_r ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mCACHE_R . mN = 0 ; out ->
mCACHE_R . mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof (
real_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_cache_i (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mCACHE_I . mN = 0 ;
out -> mCACHE_I . mX = ( int32_T * ) allocator -> mCallocFcn ( allocator ,
sizeof ( int32_T ) , 0 ) ; return out ; } static NeDsMethodOutput *
ds_output_update_r ( const NeDynamicSystem * ds , PmAllocator * allocator ) {
NeDsMethodOutput * out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator
-> mCallocFcn ( allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out ->
mUPDATE_R . mN = 0 ; out -> mUPDATE_R . mX = ( real_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( real_T ) , 0 ) ; return out ; } static
NeDsMethodOutput * ds_output_update_i ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = (
NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mUPDATE_I . mN = 0 ; out -> mUPDATE_I . mX
= ( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0
) ; return out ; } static NeDsMethodOutput * ds_output_update2_r ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mUPDATE2_R . mN = 0 ; out ->
mUPDATE2_R . mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof (
real_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_update2_i
( const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mUPDATE2_I . mN = 0 ;
out -> mUPDATE2_I . mX = ( int32_T * ) allocator -> mCallocFcn ( allocator ,
sizeof ( int32_T ) , 0 ) ; return out ; } static NeDsMethodOutput *
ds_output_lock_r ( const NeDynamicSystem * ds , PmAllocator * allocator ) {
NeDsMethodOutput * out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator
-> mCallocFcn ( allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out ->
mLOCK_R . mN = 0 ; out -> mLOCK_R . mX = ( boolean_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( boolean_T ) , 0 ) ; return out ; } static
NeDsMethodOutput * ds_output_lock_i ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = (
NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mLOCK_I . mN = 0 ; out -> mLOCK_I . mX = (
boolean_T * ) allocator -> mCallocFcn ( allocator , sizeof ( boolean_T ) , 0
) ; return out ; } static NeDsMethodOutput * ds_output_lock2_r ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mLOCK2_R . mN = 0 ; out ->
mLOCK2_R . mX = ( boolean_T * ) allocator -> mCallocFcn ( allocator , sizeof
( boolean_T ) , 0 ) ; return out ; } static NeDsMethodOutput *
ds_output_lock2_i ( const NeDynamicSystem * ds , PmAllocator * allocator ) {
NeDsMethodOutput * out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator
-> mCallocFcn ( allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out ->
mLOCK2_I . mN = 0 ; out -> mLOCK2_I . mX = ( boolean_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( boolean_T ) , 0 ) ; return out ; } static
NeDsMethodOutput * ds_output_sfo ( const NeDynamicSystem * ds , PmAllocator *
allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = ( NeDsMethodOutput
* ) allocator -> mCallocFcn ( allocator , sizeof ( NeDsMethodOutput ) , 1 ) ;
out -> mSFO . mN = 0 ; out -> mSFO . mX = ( real_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( real_T ) , 0 ) ; return out ; } static
NeDsMethodOutput * ds_output_sfp ( const NeDynamicSystem * ds , PmAllocator *
allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = ( NeDsMethodOutput
* ) allocator -> mCallocFcn ( allocator , sizeof ( NeDsMethodOutput ) , 1 ) ;
out -> mSFP . mN = 0 ; out -> mSFP . mX = ( real_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( real_T ) , 0 ) ; return out ; } static
NeDsMethodOutput * ds_output_init_r ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = (
NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mINIT_R . mN = 0 ; out -> mINIT_R . mX = (
real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 0 ) ;
return out ; } static NeDsMethodOutput * ds_output_init_i ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mINIT_I . mN = 0 ; out ->
mINIT_I . mX = ( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof (
int32_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_log (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mLOG . mN = 279 ; out
-> mLOG . mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof (
real_T ) , 279 ) ; return out ; } static NeDsMethodOutput * ds_output_assert
( const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mASSERT . mN = 16 ;
out -> mASSERT . mX = ( int32_T * ) allocator -> mCallocFcn ( allocator ,
sizeof ( int32_T ) , 16 ) ; return out ; } static NeDsMethodOutput *
ds_output_passert ( const NeDynamicSystem * ds , PmAllocator * allocator ) {
NeDsMethodOutput * out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator
-> mCallocFcn ( allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out ->
mPASSERT . mN = 0 ; out -> mPASSERT . mX = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 0 ) ; return out ; } static
NeDsMethodOutput * ds_output_iassert ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = (
NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mIASSERT . mN = 0 ; out -> mIASSERT . mX =
( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 )
; return out ; } static NeDsMethodOutput * ds_output_del_t ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDEL_T . mN = 0 ; out -> mDEL_T
. mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) ,
0 ) ; return out ; } static NeDsMethodOutput * ds_output_del_v ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDEL_V . mN = 0 ; out -> mDEL_V
. mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) ,
0 ) ; return out ; } static NeDsMethodOutput * ds_output_del_v0 ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDEL_V0 . mN = 0 ; out ->
mDEL_V0 . mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof (
real_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_del_tmax
( const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDEL_TMAX . mN = 0 ;
out -> mDEL_TMAX . mX = ( real_T * ) allocator -> mCallocFcn ( allocator ,
sizeof ( real_T ) , 0 ) ; return out ; } static NeDsMethodOutput *
ds_output_dxdelt_p ( const NeDynamicSystem * ds , PmAllocator * allocator ) {
NeDsMethodOutput * out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator
-> mCallocFcn ( allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out ->
mDXDELT_P . mNumCol = 27 ; out -> mDXDELT_P . mNumRow = 0 ; out -> mDXDELT_P
. mJc = ( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T
) , 28 ) ; out -> mDXDELT_P . mIr = ( int32_T * ) allocator -> mCallocFcn (
allocator , sizeof ( int32_T ) , 0 ) ; return out ; } static NeDsMethodOutput
* ds_output_dxdelt ( const NeDynamicSystem * ds , PmAllocator * allocator ) {
NeDsMethodOutput * out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator
-> mCallocFcn ( allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out ->
mDXDELT . mN = 0 ; out -> mDXDELT . mX = ( real_T * ) allocator -> mCallocFcn
( allocator , sizeof ( real_T ) , 0 ) ; return out ; } static
NeDsMethodOutput * ds_output_dudelt_p ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = (
NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mDUDELT_P . mNumCol = 14 ; out -> mDUDELT_P
. mNumRow = 0 ; out -> mDUDELT_P . mJc = ( int32_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( int32_T ) , 15 ) ; out -> mDUDELT_P . mIr =
( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 )
; return out ; } static NeDsMethodOutput * ds_output_dudelt ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDUDELT . mN = 0 ; out ->
mDUDELT . mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof (
real_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_dtdelt_p
( const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDTDELT_P . mNumCol =
1 ; out -> mDTDELT_P . mNumRow = 0 ; out -> mDTDELT_P . mJc = ( int32_T * )
allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 2 ) ; out ->
mDTDELT_P . mIr = ( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof
( int32_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_dtdelt
( const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDTDELT . mN = 0 ; out
-> mDTDELT . mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof (
real_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_obs_exp (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mOBS_EXP . mN = 278 ;
out -> mOBS_EXP . mX = ( real_T * ) allocator -> mCallocFcn ( allocator ,
sizeof ( real_T ) , 278 ) ; return out ; } static NeDsMethodOutput *
ds_output_obs_act ( const NeDynamicSystem * ds , PmAllocator * allocator ) {
NeDsMethodOutput * out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator
-> mCallocFcn ( allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out ->
mOBS_ACT . mN = 278 ; out -> mOBS_ACT . mX = ( real_T * ) allocator ->
mCallocFcn ( allocator , sizeof ( real_T ) , 278 ) ; return out ; } static
NeDsMethodOutput * ds_output_obs_all ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = (
NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mOBS_ALL . mN = 278 ; out -> mOBS_ALL . mX
= ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 278
) ; return out ; } static NeDsMethodOutput * ds_output_obs_il ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mOBS_IL . mN = 278 ; out ->
mOBS_IL . mX = ( boolean_T * ) allocator -> mCallocFcn ( allocator , sizeof (
boolean_T ) , 278 ) ; return out ; } static NeDsMethodOutput * ds_output_dp_l
( const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDP_L . mN = 0 ; out
-> mDP_L . mX = ( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof (
int32_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_dp_i (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDP_I . mN = 0 ; out
-> mDP_I . mX = ( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof (
int32_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_dp_j (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDP_J . mN = 0 ; out
-> mDP_J . mX = ( int32_T * ) allocator -> mCallocFcn ( allocator , sizeof (
int32_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_dp_r (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDP_R . mN = 0 ; out
-> mDP_R . mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof (
real_T ) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_qx (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mQX . mN = 0 ; out ->
mQX . mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T
) , 0 ) ; return out ; } static NeDsMethodOutput * ds_output_qu ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mQU . mN = 0 ; out -> mQU . mX =
( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 0 ) ;
return out ; } static NeDsMethodOutput * ds_output_qt ( const NeDynamicSystem
* ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out
= ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mQT . mN = 0 ; out -> mQT . mX = ( real_T *
) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 0 ) ; return out
; } static NeDsMethodOutput * ds_output_q1 ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = (
NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mQ1 . mN = 0 ; out -> mQ1 . mX = ( real_T *
) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 0 ) ; return out
; } static NeDsMethodOutput * ds_output_qx_p ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = (
NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mQX_P . mNumCol = 27 ; out -> mQX_P .
mNumRow = 27 ; out -> mQX_P . mJc = ( int32_T * ) allocator -> mCallocFcn (
allocator , sizeof ( int32_T ) , 28 ) ; out -> mQX_P . mIr = ( int32_T * )
allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 ) ; return out ;
} static NeDsMethodOutput * ds_output_qu_p ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = (
NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mQU_P . mNumCol = 14 ; out -> mQU_P .
mNumRow = 27 ; out -> mQU_P . mJc = ( int32_T * ) allocator -> mCallocFcn (
allocator , sizeof ( int32_T ) , 15 ) ; out -> mQU_P . mIr = ( int32_T * )
allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 ) ; return out ;
} static NeDsMethodOutput * ds_output_qt_p ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = (
NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mQT_P . mNumCol = 1 ; out -> mQT_P .
mNumRow = 27 ; out -> mQT_P . mJc = ( int32_T * ) allocator -> mCallocFcn (
allocator , sizeof ( int32_T ) , 2 ) ; out -> mQT_P . mIr = ( int32_T * )
allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 ) ; return out ;
} static NeDsMethodOutput * ds_output_q1_p ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = (
NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mQ1_P . mNumCol = 1 ; out -> mQ1_P .
mNumRow = 27 ; out -> mQ1_P . mJc = ( int32_T * ) allocator -> mCallocFcn (
allocator , sizeof ( int32_T ) , 2 ) ; out -> mQ1_P . mIr = ( int32_T * )
allocator -> mCallocFcn ( allocator , sizeof ( int32_T ) , 0 ) ; return out ;
} static NeDsMethodOutput * ds_output_var_tol ( const NeDynamicSystem * ds ,
PmAllocator * allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = (
NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mVAR_TOL . mN = 27 ; out -> mVAR_TOL . mX =
( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 27 ) ;
return out ; } static NeDsMethodOutput * ds_output_eq_tol ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mEQ_TOL . mN = 27 ; out ->
mEQ_TOL . mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof (
real_T ) , 27 ) ; return out ; } static NeDsMethodOutput * ds_output_lv (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mLV . mN = 27 ; out ->
mLV . mX = ( boolean_T * ) allocator -> mCallocFcn ( allocator , sizeof (
boolean_T ) , 27 ) ; return out ; } static NeDsMethodOutput * ds_output_slv (
const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mSLV . mN = 27 ; out
-> mSLV . mX = ( boolean_T * ) allocator -> mCallocFcn ( allocator , sizeof (
boolean_T ) , 27 ) ; return out ; } static NeDsMethodOutput * ds_output_nldv
( const NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput *
out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn (
allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mNLDV . mN = 27 ; out
-> mNLDV . mX = ( boolean_T * ) allocator -> mCallocFcn ( allocator , sizeof
( boolean_T ) , 27 ) ; return out ; } static NeDsMethodOutput *
ds_output_sclv ( const NeDynamicSystem * ds , PmAllocator * allocator ) {
NeDsMethodOutput * out ; ( void ) ds ; out = ( NeDsMethodOutput * ) allocator
-> mCallocFcn ( allocator , sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mSCLV
. mN = 27 ; out -> mSCLV . mX = ( boolean_T * ) allocator -> mCallocFcn (
allocator , sizeof ( boolean_T ) , 27 ) ; return out ; } static
NeDsMethodOutput * ds_output_imin ( const NeDynamicSystem * ds , PmAllocator
* allocator ) { NeDsMethodOutput * out ; ( void ) ds ; out = (
NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator , sizeof (
NeDsMethodOutput ) , 1 ) ; out -> mIMIN . mN = 27 ; out -> mIMIN . mX = (
real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) , 27 ) ;
return out ; } static NeDsMethodOutput * ds_output_imax ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mIMAX . mN = 27 ; out -> mIMAX .
mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) ,
27 ) ; return out ; } static NeDsMethodOutput * ds_output_dimin ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDIMIN . mN = 0 ; out -> mDIMIN
. mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) ,
0 ) ; return out ; } static NeDsMethodOutput * ds_output_dimax ( const
NeDynamicSystem * ds , PmAllocator * allocator ) { NeDsMethodOutput * out ; (
void ) ds ; out = ( NeDsMethodOutput * ) allocator -> mCallocFcn ( allocator
, sizeof ( NeDsMethodOutput ) , 1 ) ; out -> mDIMAX . mN = 0 ; out -> mDIMAX
. mX = ( real_T * ) allocator -> mCallocFcn ( allocator , sizeof ( real_T ) ,
0 ) ; return out ; } static void release_reference ( NeDynamicSystem * ds ) {
_NeDynamicSystem * _ds ; _ds = ( _NeDynamicSystem * ) ds ; if ( -- _ds ->
mRefCnt == 0 ) { _ds -> mAlloc . mFreeFcn ( & _ds -> mAlloc , _ds ) ; } }
static void get_reference ( NeDynamicSystem * ds ) { _NeDynamicSystem * _ds ;
_ds = ( _NeDynamicSystem * ) ds ; ++ _ds -> mRefCnt ; } static
NeDynamicSystem * diagnostics ( NeDynamicSystem * ds , boolean_T kp ) {
_NeDynamicSystem * _ds = ( _NeDynamicSystem * ) ds ; ( void ) kp ;
ne_ds_get_reference ( & _ds -> mBase ) ; return & _ds -> mBase ; } static
void expand ( const NeDynamicSystem * ds , const NeDynamicSystemInput * in ,
PmRealVector * out , boolean_T kp ) { ( void ) ds ; ( void ) kp ; memcpy (
out -> mX , in -> mX . mX , sizeof ( real_T ) * out -> mN ) ; } static void
rtpmap ( const NeDynamicSystem * ds , const PmIntVector * inl , const
PmIntVector * ini , const PmIntVector * inj , const PmRealVector * inr ,
PmIntVector * outl , PmIntVector * outi , PmIntVector * outj , PmRealVector *
outr ) { ( void ) ds ; memcpy ( outl -> mX , inl -> mX , sizeof ( int32_T ) *
inl -> mN ) ; memcpy ( outi -> mX , ini -> mX , sizeof ( int32_T ) * ini ->
mN ) ; memcpy ( outj -> mX , inj -> mX , sizeof ( int32_T ) * inj -> mN ) ;
memcpy ( outr -> mX , inr -> mX , sizeof ( real_T ) * inr -> mN ) ; }
NeDynamicSystem * external_state_machine_605b847d_1_dae_ds ( PmAllocator *
allocator ) { NeDynamicSystem * ds ; _NeDynamicSystem * _ds ; static
NeDsIoInfo input_info [ 14 ] ; static NeDsIoInfo output_info [ 16 ] ; _ds = (
_NeDynamicSystem * ) allocator -> mCallocFcn ( allocator , sizeof (
_NeDynamicSystem ) , 1 ) ; _ds -> mAlloc = * allocator ; _ds -> mRefCnt = 1 ;
ds = & _ds -> mBase ; ds -> mNumVariables = 27 ; ds ->
mNumDiscreteRealVariables = 0 ; ds -> mNumDifferentialVariables = 8 ; ds ->
mNumEquations = 27 ; ds -> mNumCEResiduals = 0 ; ds -> mNumICResiduals = 0 ;
ds -> mNumModes = 12 ; ds -> mNumMajorModes = 0 ; ds -> mNumRealCache = 0 ;
ds -> mNumIntCache = 0 ; ds -> mNumObservables = 279 ; ds ->
mNumObservableElements = 278 ; ds -> mNumZcs = 12 ; ds -> mNumAsserts = 16 ;
ds -> mNumAssertRanges = 16 ; ds -> mNumParamAsserts = 0 ; ds ->
mNumParamAssertRanges = 0 ; ds -> mNumInitialAsserts = 0 ; ds ->
mNumInitialAssertRanges = 0 ; ds -> mNumRanges = 12 ; ds ->
mNumEquationRanges = 54 ; ds -> mNumCERRanges = 0 ; ds -> mNumICRRanges = 0 ;
ds -> mNumFundamentalSamples = 0 ; ds -> mNumDelays = 0 ; ds ->
mNumLogicalParameters = 0 ; ds -> mNumIntegerParameters = 0 ; ds ->
mNumIndexParameters = 0 ; ds -> mNumRealParameters = 0 ; ds ->
mNumLogicalDerivedParameters = 0 ; ds -> mNumIntegerDerivedParameters = 0 ;
ds -> mNumIndexDerivedParameters = 0 ; ds -> mNumRealDerivedParameters = 0 ;
ds -> mIsOutputLinear = TRUE ; ds -> mIsOutputSwitchedLinear = TRUE ; ds ->
mNumIo [ NE_INPUT_IO_TYPE ] = 14 ; input_info [ 0 ] . mIdentifier =
"Subsystem1.Power_Source_ref_voltage" ; input_info [ 0 ] . mM = 1 ;
input_info [ 0 ] . mN = 1 ; input_info [ 0 ] . mName =
"Subsystem1.Power_Source_ref_voltage" ; input_info [ 0 ] . mUnit = "1" ;
input_info [ 1 ] . mIdentifier = "Subsystem1.Simulink_PS_Converter11_output"
; input_info [ 1 ] . mM = 1 ; input_info [ 1 ] . mN = 1 ; input_info [ 1 ] .
mName = "Subsystem1.Simulink_PS_Converter11_output" ; input_info [ 1 ] .
mUnit = "1" ; input_info [ 2 ] . mIdentifier =
"Subsystem1.Simulink_PS_Converter12_output" ; input_info [ 2 ] . mM = 1 ;
input_info [ 2 ] . mN = 1 ; input_info [ 2 ] . mName =
"Subsystem1.Simulink_PS_Converter12_output" ; input_info [ 2 ] . mUnit = "1"
; input_info [ 3 ] . mIdentifier =
"Subsystem1.Simulink_PS_Converter17_output" ; input_info [ 3 ] . mM = 1 ;
input_info [ 3 ] . mN = 1 ; input_info [ 3 ] . mName =
"Subsystem1.Simulink_PS_Converter17_output" ; input_info [ 3 ] . mUnit = "1"
; input_info [ 4 ] . mIdentifier =
"Subsystem1.Simulink_PS_Converter18_output" ; input_info [ 4 ] . mM = 1 ;
input_info [ 4 ] . mN = 1 ; input_info [ 4 ] . mName =
"Subsystem1.Simulink_PS_Converter18_output" ; input_info [ 4 ] . mUnit = "1"
; input_info [ 5 ] . mIdentifier =
"Subsystem1.Simulink_PS_Converter19_output" ; input_info [ 5 ] . mM = 1 ;
input_info [ 5 ] . mN = 1 ; input_info [ 5 ] . mName =
"Subsystem1.Simulink_PS_Converter19_output" ; input_info [ 5 ] . mUnit = "1"
; input_info [ 6 ] . mIdentifier =
"Subsystem1.Simulink_PS_Converter20_output" ; input_info [ 6 ] . mM = 1 ;
input_info [ 6 ] . mN = 1 ; input_info [ 6 ] . mName =
"Subsystem1.Simulink_PS_Converter20_output" ; input_info [ 6 ] . mUnit = "1"
; input_info [ 7 ] . mIdentifier = "Subsystem1.Simulink_PS_Converter2_output"
; input_info [ 7 ] . mM = 1 ; input_info [ 7 ] . mN = 1 ; input_info [ 7 ] .
mName = "Subsystem1.Simulink_PS_Converter2_output" ; input_info [ 7 ] . mUnit
= "1" ; input_info [ 8 ] . mIdentifier =
"Subsystem1.Simulink_PS_Converter3_output" ; input_info [ 8 ] . mM = 1 ;
input_info [ 8 ] . mN = 1 ; input_info [ 8 ] . mName =
"Subsystem1.Simulink_PS_Converter3_output" ; input_info [ 8 ] . mUnit = "1" ;
input_info [ 9 ] . mIdentifier = "Subsystem1.Simulink_PS_Converter4_output" ;
input_info [ 9 ] . mM = 1 ; input_info [ 9 ] . mN = 1 ; input_info [ 9 ] .
mName = "Subsystem1.Simulink_PS_Converter4_output" ; input_info [ 9 ] . mUnit
= "1" ; input_info [ 10 ] . mIdentifier =
"Subsystem1.Simulink_PS_Converter5_output" ; input_info [ 10 ] . mM = 1 ;
input_info [ 10 ] . mN = 1 ; input_info [ 10 ] . mName =
"Subsystem1.Simulink_PS_Converter5_output" ; input_info [ 10 ] . mUnit = "1"
; input_info [ 11 ] . mIdentifier =
"Subsystem1.Simulink_PS_Converter6_output" ; input_info [ 11 ] . mM = 1 ;
input_info [ 11 ] . mN = 1 ; input_info [ 11 ] . mName =
"Subsystem1.Simulink_PS_Converter6_output" ; input_info [ 11 ] . mUnit = "1"
; input_info [ 12 ] . mIdentifier =
"Subsystem1.Simulink_PS_Converter7_output" ; input_info [ 12 ] . mM = 1 ;
input_info [ 12 ] . mN = 1 ; input_info [ 12 ] . mName =
"Subsystem1.Simulink_PS_Converter7_output" ; input_info [ 12 ] . mUnit = "1"
; input_info [ 13 ] . mIdentifier =
"Subsystem1.Simulink_PS_Converter8_output" ; input_info [ 13 ] . mM = 1 ;
input_info [ 13 ] . mN = 1 ; input_info [ 13 ] . mName =
"Subsystem1.Simulink_PS_Converter8_output" ; input_info [ 13 ] . mUnit = "1"
; ds -> mIo [ NE_INPUT_IO_TYPE ] = input_info ; ds -> mNumIo [
NE_OUTPUT_IO_TYPE ] = 16 ; output_info [ 0 ] . mIdentifier =
"Subsystem1.DC_link.Voltage_Sensor_V" ; output_info [ 0 ] . mM = 1 ;
output_info [ 0 ] . mN = 1 ; output_info [ 0 ] . mName =
"Subsystem1.DC_link.Voltage_Sensor_V" ; output_info [ 0 ] . mUnit = "V" ;
output_info [ 1 ] . mIdentifier =
"Subsystem1.Ideal_Rotational_Motion_Sensor1_A" ; output_info [ 1 ] . mM = 1 ;
output_info [ 1 ] . mN = 1 ; output_info [ 1 ] . mName =
"Subsystem1.Ideal_Rotational_Motion_Sensor1_A" ; output_info [ 1 ] . mUnit =
"rad" ; output_info [ 2 ] . mIdentifier =
"Subsystem1.Ideal_Rotational_Motion_Sensor1_W" ; output_info [ 2 ] . mM = 1 ;
output_info [ 2 ] . mN = 1 ; output_info [ 2 ] . mName =
"Subsystem1.Ideal_Rotational_Motion_Sensor1_W" ; output_info [ 2 ] . mUnit =
"rad/s" ; output_info [ 3 ] . mIdentifier =
"Subsystem1.x6ph_Inverter.Voltage_Sensor1_V" ; output_info [ 3 ] . mM = 1 ;
output_info [ 3 ] . mN = 1 ; output_info [ 3 ] . mName =
"Subsystem1.x6ph_Inverter.Voltage_Sensor1_V" ; output_info [ 3 ] . mUnit =
"V" ; output_info [ 4 ] . mIdentifier =
"Subsystem1.x6ph_Inverter.Voltage_Sensor2_V" ; output_info [ 4 ] . mM = 1 ;
output_info [ 4 ] . mN = 1 ; output_info [ 4 ] . mName =
"Subsystem1.x6ph_Inverter.Voltage_Sensor2_V" ; output_info [ 4 ] . mUnit =
"V" ; output_info [ 5 ] . mIdentifier =
"Subsystem1.x6ph_Inverter.Voltage_Sensor3_V" ; output_info [ 5 ] . mM = 1 ;
output_info [ 5 ] . mN = 1 ; output_info [ 5 ] . mName =
"Subsystem1.x6ph_Inverter.Voltage_Sensor3_V" ; output_info [ 5 ] . mUnit =
"V" ; output_info [ 6 ] . mIdentifier =
"Subsystem1.x6ph_Inverter.Voltage_Sensor4_V" ; output_info [ 6 ] . mM = 1 ;
output_info [ 6 ] . mN = 1 ; output_info [ 6 ] . mName =
"Subsystem1.x6ph_Inverter.Voltage_Sensor4_V" ; output_info [ 6 ] . mUnit =
"V" ; output_info [ 7 ] . mIdentifier =
"Subsystem1.x6ph_Inverter.Voltage_Sensor5_V" ; output_info [ 7 ] . mM = 1 ;
output_info [ 7 ] . mN = 1 ; output_info [ 7 ] . mName =
"Subsystem1.x6ph_Inverter.Voltage_Sensor5_V" ; output_info [ 7 ] . mUnit =
"V" ; output_info [ 8 ] . mIdentifier =
"Subsystem1.x6ph_Inverter.Voltage_Sensor_V" ; output_info [ 8 ] . mM = 1 ;
output_info [ 8 ] . mN = 1 ; output_info [ 8 ] . mName =
"Subsystem1.x6ph_Inverter.Voltage_Sensor_V" ; output_info [ 8 ] . mUnit = "V"
; output_info [ 9 ] . mIdentifier = "Subsystem1.x6ph_Inverter.i_1_ph_I" ;
output_info [ 9 ] . mM = 1 ; output_info [ 9 ] . mN = 1 ; output_info [ 9 ] .
mName = "Subsystem1.x6ph_Inverter.i_1_ph_I" ; output_info [ 9 ] . mUnit = "A"
; output_info [ 10 ] . mIdentifier = "Subsystem1.x6ph_Inverter.i_2_ph_I" ;
output_info [ 10 ] . mM = 1 ; output_info [ 10 ] . mN = 1 ; output_info [ 10
] . mName = "Subsystem1.x6ph_Inverter.i_2_ph_I" ; output_info [ 10 ] . mUnit
= "A" ; output_info [ 11 ] . mIdentifier =
"Subsystem1.x6ph_Inverter.i_3_ph_I" ; output_info [ 11 ] . mM = 1 ;
output_info [ 11 ] . mN = 1 ; output_info [ 11 ] . mName =
"Subsystem1.x6ph_Inverter.i_3_ph_I" ; output_info [ 11 ] . mUnit = "A" ;
output_info [ 12 ] . mIdentifier = "Subsystem1.x6ph_Inverter.i_4_ph_I" ;
output_info [ 12 ] . mM = 1 ; output_info [ 12 ] . mN = 1 ; output_info [ 12
] . mName = "Subsystem1.x6ph_Inverter.i_4_ph_I" ; output_info [ 12 ] . mUnit
= "A" ; output_info [ 13 ] . mIdentifier =
"Subsystem1.x6ph_Inverter.i_5_ph_I" ; output_info [ 13 ] . mM = 1 ;
output_info [ 13 ] . mN = 1 ; output_info [ 13 ] . mName =
"Subsystem1.x6ph_Inverter.i_5_ph_I" ; output_info [ 13 ] . mUnit = "A" ;
output_info [ 14 ] . mIdentifier = "Subsystem1.x6ph_Inverter.i_6_ph_I" ;
output_info [ 14 ] . mM = 1 ; output_info [ 14 ] . mN = 1 ; output_info [ 14
] . mName = "Subsystem1.x6ph_Inverter.i_6_ph_I" ; output_info [ 14 ] . mUnit
= "A" ; output_info [ 15 ] . mIdentifier =
"Subsystem1.x6ph_Inverter.i_dc_ph_I" ; output_info [ 15 ] . mM = 1 ;
output_info [ 15 ] . mN = 1 ; output_info [ 15 ] . mName =
"Subsystem1.x6ph_Inverter.i_dc_ph_I" ; output_info [ 15 ] . mUnit = "A" ; ds
-> mIo [ NE_OUTPUT_IO_TYPE ] = output_info ; ds -> mReleaseReference =
release_reference ; ds -> mGetReference = get_reference ; ds ->
mDiagnosticsDsFcn = diagnostics ; ds -> mExpandFcn = expand ; ds ->
mRtpMapFcn = rtpmap ; ds -> mMethods [ NE_DS_METHOD_M_P ] =
external_state_machine_605b847d_1_ds_m_p ; ds -> mMakeOutput [
NE_DS_METHOD_M_P ] = ds_output_m_p ; ds -> mMethods [ NE_DS_METHOD_M ] = ds_m
; ds -> mMakeOutput [ NE_DS_METHOD_M ] = ds_output_m ; ds -> mMethods [
NE_DS_METHOD_VMM ] = ds_vmm ; ds -> mMakeOutput [ NE_DS_METHOD_VMM ] =
ds_output_vmm ; ds -> mMethods [ NE_DS_METHOD_DXM_P ] = ds_dxm_p ; ds ->
mMakeOutput [ NE_DS_METHOD_DXM_P ] = ds_output_dxm_p ; ds -> mMethods [
NE_DS_METHOD_DXM ] = ds_dxm ; ds -> mMakeOutput [ NE_DS_METHOD_DXM ] =
ds_output_dxm ; ds -> mMethods [ NE_DS_METHOD_DDM_P ] = ds_ddm_p ; ds ->
mMakeOutput [ NE_DS_METHOD_DDM_P ] = ds_output_ddm_p ; ds -> mMethods [
NE_DS_METHOD_DDM ] = ds_ddm ; ds -> mMakeOutput [ NE_DS_METHOD_DDM ] =
ds_output_ddm ; ds -> mMethods [ NE_DS_METHOD_DUM_P ] = ds_dum_p ; ds ->
mMakeOutput [ NE_DS_METHOD_DUM_P ] = ds_output_dum_p ; ds -> mMethods [
NE_DS_METHOD_DUM ] = ds_dum ; ds -> mMakeOutput [ NE_DS_METHOD_DUM ] =
ds_output_dum ; ds -> mMethods [ NE_DS_METHOD_DTM_P ] = ds_dtm_p ; ds ->
mMakeOutput [ NE_DS_METHOD_DTM_P ] = ds_output_dtm_p ; ds -> mMethods [
NE_DS_METHOD_DTM ] = ds_dtm ; ds -> mMakeOutput [ NE_DS_METHOD_DTM ] =
ds_output_dtm ; ds -> mMethods [ NE_DS_METHOD_DPM_P ] = ds_dpm_p ; ds ->
mMakeOutput [ NE_DS_METHOD_DPM_P ] = ds_output_dpm_p ; ds -> mMethods [
NE_DS_METHOD_DPM ] = ds_dpm ; ds -> mMakeOutput [ NE_DS_METHOD_DPM ] =
ds_output_dpm ; ds -> mMethods [ NE_DS_METHOD_A_P ] =
external_state_machine_605b847d_1_ds_a_p ; ds -> mMakeOutput [
NE_DS_METHOD_A_P ] = ds_output_a_p ; ds -> mMethods [ NE_DS_METHOD_A ] =
external_state_machine_605b847d_1_ds_a ; ds -> mMakeOutput [ NE_DS_METHOD_A ]
= ds_output_a ; ds -> mMethods [ NE_DS_METHOD_B_P ] = ds_b_p ; ds ->
mMakeOutput [ NE_DS_METHOD_B_P ] = ds_output_b_p ; ds -> mMethods [
NE_DS_METHOD_B ] = ds_b ; ds -> mMakeOutput [ NE_DS_METHOD_B ] = ds_output_b
; ds -> mMethods [ NE_DS_METHOD_C_P ] = ds_c_p ; ds -> mMakeOutput [
NE_DS_METHOD_C_P ] = ds_output_c_p ; ds -> mMethods [ NE_DS_METHOD_C ] = ds_c
; ds -> mMakeOutput [ NE_DS_METHOD_C ] = ds_output_c ; ds -> mMethods [
NE_DS_METHOD_F ] = external_state_machine_605b847d_1_ds_f ; ds -> mMakeOutput
[ NE_DS_METHOD_F ] = ds_output_f ; ds -> mMethods [ NE_DS_METHOD_VMF ] =
ds_vmf ; ds -> mMakeOutput [ NE_DS_METHOD_VMF ] = ds_output_vmf ; ds ->
mMethods [ NE_DS_METHOD_VPF ] = ds_vpf ; ds -> mMakeOutput [ NE_DS_METHOD_VPF
] = ds_output_vpf ; ds -> mMethods [ NE_DS_METHOD_VSF ] = ds_vsf ; ds ->
mMakeOutput [ NE_DS_METHOD_VSF ] = ds_output_vsf ; ds -> mMethods [
NE_DS_METHOD_SLF ] = ds_slf ; ds -> mMakeOutput [ NE_DS_METHOD_SLF ] =
ds_output_slf ; ds -> mMethods [ NE_DS_METHOD_SLF0 ] = ds_slf0 ; ds ->
mMakeOutput [ NE_DS_METHOD_SLF0 ] = ds_output_slf0 ; ds -> mMethods [
NE_DS_METHOD_DXF_P ] = external_state_machine_605b847d_1_ds_dxf_p ; ds ->
mMakeOutput [ NE_DS_METHOD_DXF_P ] = ds_output_dxf_p ; ds -> mMethods [
NE_DS_METHOD_DXF ] = external_state_machine_605b847d_1_ds_dxf ; ds ->
mMakeOutput [ NE_DS_METHOD_DXF ] = ds_output_dxf ; ds -> mMethods [
NE_DS_METHOD_DUF_P ] = ds_duf_p ; ds -> mMakeOutput [ NE_DS_METHOD_DUF_P ] =
ds_output_duf_p ; ds -> mMethods [ NE_DS_METHOD_DUF ] = ds_duf ; ds ->
mMakeOutput [ NE_DS_METHOD_DUF ] = ds_output_duf ; ds -> mMethods [
NE_DS_METHOD_DTF_P ] = ds_dtf_p ; ds -> mMakeOutput [ NE_DS_METHOD_DTF_P ] =
ds_output_dtf_p ; ds -> mMethods [ NE_DS_METHOD_DTF ] = ds_dtf ; ds ->
mMakeOutput [ NE_DS_METHOD_DTF ] = ds_output_dtf ; ds -> mMethods [
NE_DS_METHOD_DDF_P ] = ds_ddf_p ; ds -> mMakeOutput [ NE_DS_METHOD_DDF_P ] =
ds_output_ddf_p ; ds -> mMethods [ NE_DS_METHOD_DDF ] = ds_ddf ; ds ->
mMakeOutput [ NE_DS_METHOD_DDF ] = ds_output_ddf ; ds -> mMethods [
NE_DS_METHOD_DPDXF_P ] = ds_dpdxf_p ; ds -> mMakeOutput [
NE_DS_METHOD_DPDXF_P ] = ds_output_dpdxf_p ; ds -> mMethods [
NE_DS_METHOD_DPDXF ] = ds_dpdxf ; ds -> mMakeOutput [ NE_DS_METHOD_DPDXF ] =
ds_output_dpdxf ; ds -> mMethods [ NE_DS_METHOD_DWF_P ] = ds_dwf_p ; ds ->
mMakeOutput [ NE_DS_METHOD_DWF_P ] = ds_output_dwf_p ; ds -> mMethods [
NE_DS_METHOD_DWF ] = ds_dwf ; ds -> mMakeOutput [ NE_DS_METHOD_DWF ] =
ds_output_dwf ; ds -> mMethods [ NE_DS_METHOD_TDUF_P ] =
external_state_machine_605b847d_1_ds_tduf_p ; ds -> mMakeOutput [
NE_DS_METHOD_TDUF_P ] = ds_output_tduf_p ; ds -> mMethods [
NE_DS_METHOD_TDXF_P ] = external_state_machine_605b847d_1_ds_tdxf_p ; ds ->
mMakeOutput [ NE_DS_METHOD_TDXF_P ] = ds_output_tdxf_p ; ds -> mMethods [
NE_DS_METHOD_DNF_P ] = ds_dnf_p ; ds -> mMakeOutput [ NE_DS_METHOD_DNF_P ] =
ds_output_dnf_p ; ds -> mMethods [ NE_DS_METHOD_DNF ] = ds_dnf ; ds ->
mMakeOutput [ NE_DS_METHOD_DNF ] = ds_output_dnf ; ds -> mMethods [
NE_DS_METHOD_DNF_V_X ] = ds_dnf_v_x ; ds -> mMakeOutput [
NE_DS_METHOD_DNF_V_X ] = ds_output_dnf_v_x ; ds -> mMethods [
NE_DS_METHOD_CER ] = ds_cer ; ds -> mMakeOutput [ NE_DS_METHOD_CER ] =
ds_output_cer ; ds -> mMethods [ NE_DS_METHOD_DXCER ] = ds_dxcer ; ds ->
mMakeOutput [ NE_DS_METHOD_DXCER ] = ds_output_dxcer ; ds -> mMethods [
NE_DS_METHOD_DXCER_P ] = ds_dxcer_p ; ds -> mMakeOutput [
NE_DS_METHOD_DXCER_P ] = ds_output_dxcer_p ; ds -> mMethods [ NE_DS_METHOD_IC
] = ds_ic ; ds -> mMakeOutput [ NE_DS_METHOD_IC ] = ds_output_ic ; ds ->
mMethods [ NE_DS_METHOD_ICR ] = ds_icr ; ds -> mMakeOutput [ NE_DS_METHOD_ICR
] = ds_output_icr ; ds -> mMethods [ NE_DS_METHOD_ICR_IM ] = ds_icr_im ; ds
-> mMakeOutput [ NE_DS_METHOD_ICR_IM ] = ds_output_icr_im ; ds -> mMethods [
NE_DS_METHOD_ICR_ID ] = ds_icr_id ; ds -> mMakeOutput [ NE_DS_METHOD_ICR_ID ]
= ds_output_icr_id ; ds -> mMethods [ NE_DS_METHOD_ICR_IL ] = ds_icr_il ; ds
-> mMakeOutput [ NE_DS_METHOD_ICR_IL ] = ds_output_icr_il ; ds -> mMethods [
NE_DS_METHOD_DXICR ] = ds_dxicr ; ds -> mMakeOutput [ NE_DS_METHOD_DXICR ] =
ds_output_dxicr ; ds -> mMethods [ NE_DS_METHOD_DXICR_P ] = ds_dxicr_p ; ds
-> mMakeOutput [ NE_DS_METHOD_DXICR_P ] = ds_output_dxicr_p ; ds -> mMethods
[ NE_DS_METHOD_DDICR ] = ds_ddicr ; ds -> mMakeOutput [ NE_DS_METHOD_DDICR ]
= ds_output_ddicr ; ds -> mMethods [ NE_DS_METHOD_DDICR_P ] = ds_ddicr_p ; ds
-> mMakeOutput [ NE_DS_METHOD_DDICR_P ] = ds_output_ddicr_p ; ds -> mMethods
[ NE_DS_METHOD_TDUICR_P ] = ds_tduicr_p ; ds -> mMakeOutput [
NE_DS_METHOD_TDUICR_P ] = ds_output_tduicr_p ; ds -> mMethods [
NE_DS_METHOD_ICRM_P ] = ds_icrm_p ; ds -> mMakeOutput [ NE_DS_METHOD_ICRM_P ]
= ds_output_icrm_p ; ds -> mMethods [ NE_DS_METHOD_ICRM ] = ds_icrm ; ds ->
mMakeOutput [ NE_DS_METHOD_ICRM ] = ds_output_icrm ; ds -> mMethods [
NE_DS_METHOD_DXICRM_P ] = ds_dxicrm_p ; ds -> mMakeOutput [
NE_DS_METHOD_DXICRM_P ] = ds_output_dxicrm_p ; ds -> mMethods [
NE_DS_METHOD_DXICRM ] = ds_dxicrm ; ds -> mMakeOutput [ NE_DS_METHOD_DXICRM ]
= ds_output_dxicrm ; ds -> mMethods [ NE_DS_METHOD_DDICRM_P ] = ds_ddicrm_p ;
ds -> mMakeOutput [ NE_DS_METHOD_DDICRM_P ] = ds_output_ddicrm_p ; ds ->
mMethods [ NE_DS_METHOD_DDICRM ] = ds_ddicrm ; ds -> mMakeOutput [
NE_DS_METHOD_DDICRM ] = ds_output_ddicrm ; ds -> mMethods [
NE_DS_METHOD_MDUY_P ] = ds_mduy_p ; ds -> mMakeOutput [ NE_DS_METHOD_MDUY_P ]
= ds_output_mduy_p ; ds -> mMethods [ NE_DS_METHOD_MDXY_P ] = ds_mdxy_p ; ds
-> mMakeOutput [ NE_DS_METHOD_MDXY_P ] = ds_output_mdxy_p ; ds -> mMethods [
NE_DS_METHOD_TDUY_P ] = ds_tduy_p ; ds -> mMakeOutput [ NE_DS_METHOD_TDUY_P ]
= ds_output_tduy_p ; ds -> mMethods [ NE_DS_METHOD_TDXY_P ] =
external_state_machine_605b847d_1_ds_tdxy_p ; ds -> mMakeOutput [
NE_DS_METHOD_TDXY_P ] = ds_output_tdxy_p ; ds -> mMethods [ NE_DS_METHOD_Y ]
= external_state_machine_605b847d_1_ds_y ; ds -> mMakeOutput [ NE_DS_METHOD_Y
] = ds_output_y ; ds -> mMethods [ NE_DS_METHOD_DXY_P ] =
external_state_machine_605b847d_1_ds_dxy_p ; ds -> mMakeOutput [
NE_DS_METHOD_DXY_P ] = ds_output_dxy_p ; ds -> mMethods [ NE_DS_METHOD_DXY ]
= ds_dxy ; ds -> mMakeOutput [ NE_DS_METHOD_DXY ] = ds_output_dxy ; ds ->
mMethods [ NE_DS_METHOD_DUY_P ] = ds_duy_p ; ds -> mMakeOutput [
NE_DS_METHOD_DUY_P ] = ds_output_duy_p ; ds -> mMethods [ NE_DS_METHOD_DUY ]
= ds_duy ; ds -> mMakeOutput [ NE_DS_METHOD_DUY ] = ds_output_duy ; ds ->
mMethods [ NE_DS_METHOD_DTY_P ] = ds_dty_p ; ds -> mMakeOutput [
NE_DS_METHOD_DTY_P ] = ds_output_dty_p ; ds -> mMethods [ NE_DS_METHOD_DTY ]
= ds_dty ; ds -> mMakeOutput [ NE_DS_METHOD_DTY ] = ds_output_dty ; ds ->
mMethods [ NE_DS_METHOD_MODE ] = external_state_machine_605b847d_1_ds_mode ;
ds -> mMakeOutput [ NE_DS_METHOD_MODE ] = ds_output_mode ; ds -> mMethods [
NE_DS_METHOD_ZC ] = external_state_machine_605b847d_1_ds_zc ; ds ->
mMakeOutput [ NE_DS_METHOD_ZC ] = ds_output_zc ; ds -> mMethods [
NE_DS_METHOD_CACHE_R ] = ds_cache_r ; ds -> mMakeOutput [
NE_DS_METHOD_CACHE_R ] = ds_output_cache_r ; ds -> mMethods [
NE_DS_METHOD_CACHE_I ] = ds_cache_i ; ds -> mMakeOutput [
NE_DS_METHOD_CACHE_I ] = ds_output_cache_i ; ds -> mMethods [
NE_DS_METHOD_UPDATE_R ] = ds_update_r ; ds -> mMakeOutput [
NE_DS_METHOD_UPDATE_R ] = ds_output_update_r ; ds -> mMethods [
NE_DS_METHOD_UPDATE_I ] = ds_update_i ; ds -> mMakeOutput [
NE_DS_METHOD_UPDATE_I ] = ds_output_update_i ; ds -> mMethods [
NE_DS_METHOD_UPDATE2_R ] = ds_update2_r ; ds -> mMakeOutput [
NE_DS_METHOD_UPDATE2_R ] = ds_output_update2_r ; ds -> mMethods [
NE_DS_METHOD_UPDATE2_I ] = ds_update2_i ; ds -> mMakeOutput [
NE_DS_METHOD_UPDATE2_I ] = ds_output_update2_i ; ds -> mMethods [
NE_DS_METHOD_LOCK_R ] = ds_lock_r ; ds -> mMakeOutput [ NE_DS_METHOD_LOCK_R ]
= ds_output_lock_r ; ds -> mMethods [ NE_DS_METHOD_LOCK_I ] = ds_lock_i ; ds
-> mMakeOutput [ NE_DS_METHOD_LOCK_I ] = ds_output_lock_i ; ds -> mMethods [
NE_DS_METHOD_LOCK2_R ] = ds_lock2_r ; ds -> mMakeOutput [
NE_DS_METHOD_LOCK2_R ] = ds_output_lock2_r ; ds -> mMethods [
NE_DS_METHOD_LOCK2_I ] = ds_lock2_i ; ds -> mMakeOutput [
NE_DS_METHOD_LOCK2_I ] = ds_output_lock2_i ; ds -> mMethods [
NE_DS_METHOD_SFO ] = ds_sfo ; ds -> mMakeOutput [ NE_DS_METHOD_SFO ] =
ds_output_sfo ; ds -> mMethods [ NE_DS_METHOD_SFP ] = ds_sfp ; ds ->
mMakeOutput [ NE_DS_METHOD_SFP ] = ds_output_sfp ; ds -> mMethods [
NE_DS_METHOD_INIT_R ] = ds_init_r ; ds -> mMakeOutput [ NE_DS_METHOD_INIT_R ]
= ds_output_init_r ; ds -> mMethods [ NE_DS_METHOD_INIT_I ] = ds_init_i ; ds
-> mMakeOutput [ NE_DS_METHOD_INIT_I ] = ds_output_init_i ; ds -> mMethods [
NE_DS_METHOD_LOG ] = external_state_machine_605b847d_1_ds_log ; ds ->
mMakeOutput [ NE_DS_METHOD_LOG ] = ds_output_log ; ds -> mMethods [
NE_DS_METHOD_ASSERT ] = ds_assert ; ds -> mMakeOutput [ NE_DS_METHOD_ASSERT ]
= ds_output_assert ; ds -> mMethods [ NE_DS_METHOD_PASSERT ] = ds_passert ;
ds -> mMakeOutput [ NE_DS_METHOD_PASSERT ] = ds_output_passert ; ds ->
mMethods [ NE_DS_METHOD_IASSERT ] = ds_iassert ; ds -> mMakeOutput [
NE_DS_METHOD_IASSERT ] = ds_output_iassert ; ds -> mMethods [
NE_DS_METHOD_DEL_T ] = ds_del_t ; ds -> mMakeOutput [ NE_DS_METHOD_DEL_T ] =
ds_output_del_t ; ds -> mMethods [ NE_DS_METHOD_DEL_V ] = ds_del_v ; ds ->
mMakeOutput [ NE_DS_METHOD_DEL_V ] = ds_output_del_v ; ds -> mMethods [
NE_DS_METHOD_DEL_V0 ] = ds_del_v0 ; ds -> mMakeOutput [ NE_DS_METHOD_DEL_V0 ]
= ds_output_del_v0 ; ds -> mMethods [ NE_DS_METHOD_DEL_TMAX ] = ds_del_tmax ;
ds -> mMakeOutput [ NE_DS_METHOD_DEL_TMAX ] = ds_output_del_tmax ; ds ->
mMethods [ NE_DS_METHOD_DXDELT_P ] = ds_dxdelt_p ; ds -> mMakeOutput [
NE_DS_METHOD_DXDELT_P ] = ds_output_dxdelt_p ; ds -> mMethods [
NE_DS_METHOD_DXDELT ] = ds_dxdelt ; ds -> mMakeOutput [ NE_DS_METHOD_DXDELT ]
= ds_output_dxdelt ; ds -> mMethods [ NE_DS_METHOD_DUDELT_P ] = ds_dudelt_p ;
ds -> mMakeOutput [ NE_DS_METHOD_DUDELT_P ] = ds_output_dudelt_p ; ds ->
mMethods [ NE_DS_METHOD_DUDELT ] = ds_dudelt ; ds -> mMakeOutput [
NE_DS_METHOD_DUDELT ] = ds_output_dudelt ; ds -> mMethods [
NE_DS_METHOD_DTDELT_P ] = ds_dtdelt_p ; ds -> mMakeOutput [
NE_DS_METHOD_DTDELT_P ] = ds_output_dtdelt_p ; ds -> mMethods [
NE_DS_METHOD_DTDELT ] = ds_dtdelt ; ds -> mMakeOutput [ NE_DS_METHOD_DTDELT ]
= ds_output_dtdelt ; ds -> mMethods [ NE_DS_METHOD_OBS_EXP ] = ds_obs_exp ;
ds -> mMakeOutput [ NE_DS_METHOD_OBS_EXP ] = ds_output_obs_exp ; ds ->
mMethods [ NE_DS_METHOD_OBS_ACT ] =
external_state_machine_605b847d_1_ds_obs_act ; ds -> mMakeOutput [
NE_DS_METHOD_OBS_ACT ] = ds_output_obs_act ; ds -> mMethods [
NE_DS_METHOD_OBS_ALL ] = external_state_machine_605b847d_1_ds_obs_all ; ds ->
mMakeOutput [ NE_DS_METHOD_OBS_ALL ] = ds_output_obs_all ; ds -> mMethods [
NE_DS_METHOD_OBS_IL ] = external_state_machine_605b847d_1_ds_obs_il ; ds ->
mMakeOutput [ NE_DS_METHOD_OBS_IL ] = ds_output_obs_il ; ds -> mMethods [
NE_DS_METHOD_DP_L ] = ds_dp_l ; ds -> mMakeOutput [ NE_DS_METHOD_DP_L ] =
ds_output_dp_l ; ds -> mMethods [ NE_DS_METHOD_DP_I ] = ds_dp_i ; ds ->
mMakeOutput [ NE_DS_METHOD_DP_I ] = ds_output_dp_i ; ds -> mMethods [
NE_DS_METHOD_DP_J ] = ds_dp_j ; ds -> mMakeOutput [ NE_DS_METHOD_DP_J ] =
ds_output_dp_j ; ds -> mMethods [ NE_DS_METHOD_DP_R ] = ds_dp_r ; ds ->
mMakeOutput [ NE_DS_METHOD_DP_R ] = ds_output_dp_r ; ds -> mMethods [
NE_DS_METHOD_QX ] = ds_qx ; ds -> mMakeOutput [ NE_DS_METHOD_QX ] =
ds_output_qx ; ds -> mMethods [ NE_DS_METHOD_QU ] = ds_qu ; ds -> mMakeOutput
[ NE_DS_METHOD_QU ] = ds_output_qu ; ds -> mMethods [ NE_DS_METHOD_QT ] =
ds_qt ; ds -> mMakeOutput [ NE_DS_METHOD_QT ] = ds_output_qt ; ds -> mMethods
[ NE_DS_METHOD_Q1 ] = ds_q1 ; ds -> mMakeOutput [ NE_DS_METHOD_Q1 ] =
ds_output_q1 ; ds -> mMethods [ NE_DS_METHOD_QX_P ] = ds_qx_p ; ds ->
mMakeOutput [ NE_DS_METHOD_QX_P ] = ds_output_qx_p ; ds -> mMethods [
NE_DS_METHOD_QU_P ] = ds_qu_p ; ds -> mMakeOutput [ NE_DS_METHOD_QU_P ] =
ds_output_qu_p ; ds -> mMethods [ NE_DS_METHOD_QT_P ] = ds_qt_p ; ds ->
mMakeOutput [ NE_DS_METHOD_QT_P ] = ds_output_qt_p ; ds -> mMethods [
NE_DS_METHOD_Q1_P ] = ds_q1_p ; ds -> mMakeOutput [ NE_DS_METHOD_Q1_P ] =
ds_output_q1_p ; ds -> mMethods [ NE_DS_METHOD_VAR_TOL ] = ds_var_tol ; ds ->
mMakeOutput [ NE_DS_METHOD_VAR_TOL ] = ds_output_var_tol ; ds -> mMethods [
NE_DS_METHOD_EQ_TOL ] = ds_eq_tol ; ds -> mMakeOutput [ NE_DS_METHOD_EQ_TOL ]
= ds_output_eq_tol ; ds -> mMethods [ NE_DS_METHOD_LV ] = ds_lv ; ds ->
mMakeOutput [ NE_DS_METHOD_LV ] = ds_output_lv ; ds -> mMethods [
NE_DS_METHOD_SLV ] = ds_slv ; ds -> mMakeOutput [ NE_DS_METHOD_SLV ] =
ds_output_slv ; ds -> mMethods [ NE_DS_METHOD_NLDV ] = ds_nldv ; ds ->
mMakeOutput [ NE_DS_METHOD_NLDV ] = ds_output_nldv ; ds -> mMethods [
NE_DS_METHOD_SCLV ] = ds_sclv ; ds -> mMakeOutput [ NE_DS_METHOD_SCLV ] =
ds_output_sclv ; ds -> mMethods [ NE_DS_METHOD_IMIN ] =
external_state_machine_605b847d_1_ds_imin ; ds -> mMakeOutput [
NE_DS_METHOD_IMIN ] = ds_output_imin ; ds -> mMethods [ NE_DS_METHOD_IMAX ] =
external_state_machine_605b847d_1_ds_imax ; ds -> mMakeOutput [
NE_DS_METHOD_IMAX ] = ds_output_imax ; ds -> mMethods [ NE_DS_METHOD_DIMIN ]
= ds_dimin ; ds -> mMakeOutput [ NE_DS_METHOD_DIMIN ] = ds_output_dimin ; ds
-> mMethods [ NE_DS_METHOD_DIMAX ] = ds_dimax ; ds -> mMakeOutput [
NE_DS_METHOD_DIMAX ] = ds_output_dimax ; ds -> mEquationData =
s_equation_data ; ds -> mCERData = s_cer_data ; ds -> mICRData = s_icr_data ;
ds -> mVariableData = s_variable_data ; ds -> mDiscreteData = s_discrete_data
; ds -> mObservableData = s_observable_data ; ds -> mMajorModeData =
s_major_mode_data ; ds -> mZCData = s_zc_data ; ds -> mRanges = s_range ; ds
-> mAssertData = s_assert_data ; ds -> mAssertRanges = s_assert_range ; ds ->
mParamAssertData = s_param_assert_data ; ds -> mParamAssertRanges =
s_param_assert_range ; ds -> mInitialAssertData = s_initial_assert_data ; ds
-> mInitialAssertRanges = s_initial_assert_range ; ds -> mEquationRanges =
s_equation_range ; ds -> mCERRanges = s_cer_range ; ds -> mICRRanges =
s_icr_range ; ds -> mLogicalParameters = s_logical_parameter_data ; ds ->
mIntegerParameters = s_integer_parameter_data ; ds -> mIndexParameters =
s_index_parameter_data ; ds -> mRealParameters = s_real_parameter_data ;
return ( NeDynamicSystem * ) _ds ; } static int32_T ds_assert ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { PmIntVector out ; ( void ) t1 ; out = t2 -> mASSERT ; out . mX [ 0 ] =
1 ; out . mX [ 1 ] = 1 ; out . mX [ 2 ] = 1 ; out . mX [ 3 ] = 1 ; out . mX [
4 ] = 1 ; out . mX [ 5 ] = 1 ; out . mX [ 6 ] = 1 ; out . mX [ 7 ] = 1 ; out
. mX [ 8 ] = 1 ; out . mX [ 9 ] = 1 ; out . mX [ 10 ] = 1 ; out . mX [ 11 ] =
1 ; out . mX [ 12 ] = 1 ; out . mX [ 13 ] = 1 ; out . mX [ 14 ] = 1 ; out .
mX [ 15 ] = 1 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T
ds_passert ( const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0
; } static int32_T ds_iassert ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_cer ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T
ds_dxcer ( const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0
; } static int32_T ds_dxcer_p ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmSparsityPattern out ;
( void ) t1 ; out = t2 -> mDXCER_P ; out . mNumCol = 27ULL ; out . mNumRow =
0ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 0 ; out . mJc [ 2 ] = 0 ; out
. mJc [ 3 ] = 0 ; out . mJc [ 4 ] = 0 ; out . mJc [ 5 ] = 0 ; out . mJc [ 6 ]
= 0 ; out . mJc [ 7 ] = 0 ; out . mJc [ 8 ] = 0 ; out . mJc [ 9 ] = 0 ; out .
mJc [ 10 ] = 0 ; out . mJc [ 11 ] = 0 ; out . mJc [ 12 ] = 0 ; out . mJc [ 13
] = 0 ; out . mJc [ 14 ] = 0 ; out . mJc [ 15 ] = 0 ; out . mJc [ 16 ] = 0 ;
out . mJc [ 17 ] = 0 ; out . mJc [ 18 ] = 0 ; out . mJc [ 19 ] = 0 ; out .
mJc [ 20 ] = 0 ; out . mJc [ 21 ] = 0 ; out . mJc [ 22 ] = 0 ; out . mJc [ 23
] = 0 ; out . mJc [ 24 ] = 0 ; out . mJc [ 25 ] = 0 ; out . mJc [ 26 ] = 0 ;
out . mJc [ 27 ] = 0 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static
int32_T ds_del_v ( const NeDynamicSystem * sys , const NeDynamicSystemInput *
t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ;
return 0 ; } static int32_T ds_del_v0 ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_del_tmax ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T
ds_del_t ( const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0
; } static int32_T ds_dxdelt ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_dxdelt_p ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { PmSparsityPattern out ; ( void ) t1 ; out = t2 -> mDXDELT_P ; out .
mNumCol = 27ULL ; out . mNumRow = 0ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1
] = 0 ; out . mJc [ 2 ] = 0 ; out . mJc [ 3 ] = 0 ; out . mJc [ 4 ] = 0 ; out
. mJc [ 5 ] = 0 ; out . mJc [ 6 ] = 0 ; out . mJc [ 7 ] = 0 ; out . mJc [ 8 ]
= 0 ; out . mJc [ 9 ] = 0 ; out . mJc [ 10 ] = 0 ; out . mJc [ 11 ] = 0 ; out
. mJc [ 12 ] = 0 ; out . mJc [ 13 ] = 0 ; out . mJc [ 14 ] = 0 ; out . mJc [
15 ] = 0 ; out . mJc [ 16 ] = 0 ; out . mJc [ 17 ] = 0 ; out . mJc [ 18 ] = 0
; out . mJc [ 19 ] = 0 ; out . mJc [ 20 ] = 0 ; out . mJc [ 21 ] = 0 ; out .
mJc [ 22 ] = 0 ; out . mJc [ 23 ] = 0 ; out . mJc [ 24 ] = 0 ; out . mJc [ 25
] = 0 ; out . mJc [ 26 ] = 0 ; out . mJc [ 27 ] = 0 ; ( void ) sys ; ( void )
t2 ; return 0 ; } static int32_T ds_dudelt ( const NeDynamicSystem * sys ,
const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; (
void ) sys ; ( void ) t2 ; return 0 ; } static int32_T ds_dudelt_p ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { PmSparsityPattern out ; ( void ) t1 ; out = t2 -> mDUDELT_P ; out .
mNumCol = 14ULL ; out . mNumRow = 0ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1
] = 0 ; out . mJc [ 2 ] = 0 ; out . mJc [ 3 ] = 0 ; out . mJc [ 4 ] = 0 ; out
. mJc [ 5 ] = 0 ; out . mJc [ 6 ] = 0 ; out . mJc [ 7 ] = 0 ; out . mJc [ 8 ]
= 0 ; out . mJc [ 9 ] = 0 ; out . mJc [ 10 ] = 0 ; out . mJc [ 11 ] = 0 ; out
. mJc [ 12 ] = 0 ; out . mJc [ 13 ] = 0 ; out . mJc [ 14 ] = 0 ; ( void ) sys
; ( void ) t2 ; return 0 ; } static int32_T ds_dtdelt ( const NeDynamicSystem
* sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void )
t1 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T ds_dtdelt_p (
const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { PmSparsityPattern out ; ( void ) t1 ; out = t2 ->
mDTDELT_P ; out . mNumCol = 1ULL ; out . mNumRow = 0ULL ; out . mJc [ 0 ] = 0
; out . mJc [ 1 ] = 0 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static
int32_T ds_cache_r ( const NeDynamicSystem * sys , const NeDynamicSystemInput
* t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ;
return 0 ; } static int32_T ds_init_r ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_update_r ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T
ds_lock_r ( const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0
; } static int32_T ds_cache_i ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_init_i ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T
ds_update_i ( const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0
; } static int32_T ds_lock_i ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_update2_r ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T
ds_lock2_r ( const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0
; } static int32_T ds_update2_i ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_lock2_i ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T
ds_sfp ( const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0
; } static int32_T ds_sfo ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_duf ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { PmRealVector out ; ( void ) t1 ; out = t2 -> mDUF ; out . mX [ 0 ] =
1.0E-6 ; out . mX [ 1 ] = 1.0E-6 ; out . mX [ 2 ] = 1.0E-6 ; out . mX [ 3 ] =
1.0E-6 ; out . mX [ 4 ] = 1.0E-6 ; out . mX [ 5 ] = 1.0E-6 ; ( void ) sys ; (
void ) t2 ; return 0 ; } static int32_T ds_duf_p ( const NeDynamicSystem *
sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) {
PmSparsityPattern out ; ( void ) t1 ; out = t2 -> mDUF_P ; out . mNumCol =
14ULL ; out . mNumRow = 27ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 6 ;
out . mJc [ 2 ] = 6 ; out . mJc [ 3 ] = 6 ; out . mJc [ 4 ] = 6 ; out . mJc [
5 ] = 6 ; out . mJc [ 6 ] = 6 ; out . mJc [ 7 ] = 6 ; out . mJc [ 8 ] = 6 ;
out . mJc [ 9 ] = 6 ; out . mJc [ 10 ] = 6 ; out . mJc [ 11 ] = 6 ; out . mJc
[ 12 ] = 6 ; out . mJc [ 13 ] = 6 ; out . mJc [ 14 ] = 6 ; out . mIr [ 0 ] =
15 ; out . mIr [ 1 ] = 17 ; out . mIr [ 2 ] = 19 ; out . mIr [ 3 ] = 21 ; out
. mIr [ 4 ] = 23 ; out . mIr [ 5 ] = 25 ; ( void ) sys ; ( void ) t2 ; return
0 ; } static int32_T ds_dtf ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_dtf_p ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { PmSparsityPattern out ; ( void ) t1 ; out = t2 -> mDTF_P ; out .
mNumCol = 1ULL ; out . mNumRow = 27ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1
] = 0 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T ds_ddf (
const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0
; } static int32_T ds_ddf_p ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmSparsityPattern out ;
( void ) t1 ; out = t2 -> mDDF_P ; out . mNumCol = 0ULL ; out . mNumRow =
27ULL ; out . mJc [ 0 ] = 0 ; ( void ) sys ; ( void ) t2 ; return 0 ; }
static int32_T ds_b ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmRealVector out ; (
void ) t1 ; out = t2 -> mB ; out . mX [ 0 ] = 1.0 ; out . mX [ 1 ] = 1.0 ; (
void ) sys ; ( void ) t2 ; return 0 ; } static int32_T ds_b_p ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { PmSparsityPattern out ; ( void ) t1 ; out = t2 -> mB_P ; out . mNumCol
= 14ULL ; out . mNumRow = 27ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 1 ;
out . mJc [ 2 ] = 1 ; out . mJc [ 3 ] = 1 ; out . mJc [ 4 ] = 1 ; out . mJc [
5 ] = 1 ; out . mJc [ 6 ] = 1 ; out . mJc [ 7 ] = 1 ; out . mJc [ 8 ] = 1 ;
out . mJc [ 9 ] = 1 ; out . mJc [ 10 ] = 1 ; out . mJc [ 11 ] = 1 ; out . mJc
[ 12 ] = 1 ; out . mJc [ 13 ] = 1 ; out . mJc [ 14 ] = 2 ; out . mIr [ 0 ] =
8 ; out . mIr [ 1 ] = 9 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static
int32_T ds_c ( const NeDynamicSystem * sys , const NeDynamicSystemInput * t1
, NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return
0 ; } static int32_T ds_c_p ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmSparsityPattern out ;
( void ) t1 ; out = t2 -> mC_P ; out . mNumCol = 1ULL ; out . mNumRow = 27ULL
; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 0 ; ( void ) sys ; ( void ) t2 ;
return 0 ; } static int32_T ds_dwf ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_dwf_p ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { PmSparsityPattern out ; ( void ) t1 ; out = t2 -> mDWF_P ; out .
mNumCol = 0ULL ; out . mNumRow = 27ULL ; out . mJc [ 0 ] = 0 ; ( void ) sys ;
( void ) t2 ; return 0 ; } static int32_T ds_dpdxf ( const NeDynamicSystem *
sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1
; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T ds_dpdxf_p ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { PmSparsityPattern out ; ( void ) t1 ; out = t2 -> mDPDXF_P ; out .
mNumCol = 0ULL ; out . mNumRow = 62ULL ; out . mJc [ 0 ] = 0 ; ( void ) sys ;
( void ) t2 ; return 0 ; } static int32_T ds_vmf ( const NeDynamicSystem *
sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) {
PmBoolVector out ; ( void ) t1 ; out = t2 -> mVMF ; out . mX [ 0 ] = false ;
out . mX [ 1 ] = false ; out . mX [ 2 ] = false ; out . mX [ 3 ] = false ;
out . mX [ 4 ] = true ; out . mX [ 5 ] = true ; out . mX [ 6 ] = false ; out
. mX [ 7 ] = false ; out . mX [ 8 ] = false ; out . mX [ 9 ] = false ; out .
mX [ 10 ] = false ; out . mX [ 11 ] = false ; out . mX [ 12 ] = true ; out .
mX [ 13 ] = true ; out . mX [ 14 ] = true ; out . mX [ 15 ] = true ; out . mX
[ 16 ] = true ; out . mX [ 17 ] = true ; out . mX [ 18 ] = true ; out . mX [
19 ] = true ; out . mX [ 20 ] = true ; out . mX [ 21 ] = true ; out . mX [ 22
] = true ; out . mX [ 23 ] = true ; out . mX [ 24 ] = true ; out . mX [ 25 ]
= true ; out . mX [ 26 ] = true ; ( void ) sys ; ( void ) t2 ; return 0 ; }
static int32_T ds_slf ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmBoolVector out ; (
void ) t1 ; out = t2 -> mSLF ; out . mX [ 0 ] = false ; out . mX [ 1 ] =
false ; out . mX [ 2 ] = false ; out . mX [ 3 ] = false ; out . mX [ 4 ] =
false ; out . mX [ 5 ] = false ; out . mX [ 6 ] = false ; out . mX [ 7 ] =
false ; out . mX [ 8 ] = false ; out . mX [ 9 ] = false ; out . mX [ 10 ] =
false ; out . mX [ 11 ] = false ; out . mX [ 12 ] = false ; out . mX [ 13 ] =
false ; out . mX [ 14 ] = false ; out . mX [ 15 ] = false ; out . mX [ 16 ] =
false ; out . mX [ 17 ] = false ; out . mX [ 18 ] = false ; out . mX [ 19 ] =
false ; out . mX [ 20 ] = false ; out . mX [ 21 ] = false ; out . mX [ 22 ] =
false ; out . mX [ 23 ] = false ; out . mX [ 24 ] = false ; out . mX [ 25 ] =
false ; out . mX [ 26 ] = false ; ( void ) sys ; ( void ) t2 ; return 0 ; }
static int32_T ds_dnf ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_dnf_p ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { PmSparsityPattern out ; ( void ) t1 ; out = t2 -> mDNF_P ; out .
mNumCol = 15ULL ; out . mNumRow = 27ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1
] = 0 ; out . mJc [ 2 ] = 0 ; out . mJc [ 3 ] = 0 ; out . mJc [ 4 ] = 0 ; out
. mJc [ 5 ] = 0 ; out . mJc [ 6 ] = 0 ; out . mJc [ 7 ] = 0 ; out . mJc [ 8 ]
= 0 ; out . mJc [ 9 ] = 0 ; out . mJc [ 10 ] = 0 ; out . mJc [ 11 ] = 0 ; out
. mJc [ 12 ] = 0 ; out . mJc [ 13 ] = 0 ; out . mJc [ 14 ] = 0 ; out . mJc [
15 ] = 0 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T
ds_dnf_v_x ( const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { PmBoolVector out ; ( void ) t1 ; out = t2 ->
mDNF_V_X ; out . mX [ 0 ] = true ; out . mX [ 1 ] = true ; out . mX [ 2 ] =
true ; out . mX [ 3 ] = true ; out . mX [ 4 ] = true ; out . mX [ 5 ] = true
; out . mX [ 6 ] = true ; out . mX [ 7 ] = true ; out . mX [ 8 ] = false ;
out . mX [ 9 ] = false ; out . mX [ 10 ] = false ; out . mX [ 11 ] = false ;
out . mX [ 12 ] = true ; out . mX [ 13 ] = true ; out . mX [ 14 ] = true ;
out . mX [ 15 ] = true ; out . mX [ 16 ] = true ; out . mX [ 17 ] = true ;
out . mX [ 18 ] = true ; out . mX [ 19 ] = true ; out . mX [ 20 ] = true ;
out . mX [ 21 ] = true ; out . mX [ 22 ] = true ; out . mX [ 23 ] = true ;
out . mX [ 24 ] = true ; out . mX [ 25 ] = true ; out . mX [ 26 ] = true ; (
void ) sys ; ( void ) t2 ; return 0 ; } static int32_T ds_slf0 ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { PmBoolVector out ; ( void ) t1 ; out = t2 -> mSLF0 ; out . mX [ 0 ] =
false ; out . mX [ 1 ] = false ; out . mX [ 2 ] = false ; out . mX [ 3 ] =
false ; out . mX [ 4 ] = false ; out . mX [ 5 ] = false ; out . mX [ 6 ] =
false ; out . mX [ 7 ] = false ; out . mX [ 8 ] = false ; out . mX [ 9 ] =
false ; out . mX [ 10 ] = false ; out . mX [ 11 ] = false ; out . mX [ 12 ] =
false ; out . mX [ 13 ] = false ; out . mX [ 14 ] = false ; out . mX [ 15 ] =
false ; out . mX [ 16 ] = false ; out . mX [ 17 ] = false ; out . mX [ 18 ] =
false ; out . mX [ 19 ] = false ; out . mX [ 20 ] = false ; out . mX [ 21 ] =
false ; out . mX [ 22 ] = false ; out . mX [ 23 ] = false ; out . mX [ 24 ] =
false ; out . mX [ 25 ] = false ; out . mX [ 26 ] = false ; ( void ) sys ; (
void ) t2 ; return 0 ; } static int32_T ds_vpf ( const NeDynamicSystem * sys
, const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmBoolVector
out ; ( void ) t1 ; out = t2 -> mVPF ; out . mX [ 0 ] = false ; out . mX [ 1
] = false ; out . mX [ 2 ] = false ; out . mX [ 3 ] = false ; out . mX [ 4 ]
= false ; out . mX [ 5 ] = false ; out . mX [ 6 ] = false ; out . mX [ 7 ] =
false ; out . mX [ 8 ] = false ; out . mX [ 9 ] = false ; out . mX [ 10 ] =
false ; out . mX [ 11 ] = false ; out . mX [ 12 ] = false ; out . mX [ 13 ] =
false ; out . mX [ 14 ] = false ; out . mX [ 15 ] = false ; out . mX [ 16 ] =
false ; out . mX [ 17 ] = false ; out . mX [ 18 ] = false ; out . mX [ 19 ] =
false ; out . mX [ 20 ] = false ; out . mX [ 21 ] = false ; out . mX [ 22 ] =
false ; out . mX [ 23 ] = false ; out . mX [ 24 ] = false ; out . mX [ 25 ] =
false ; out . mX [ 26 ] = false ; ( void ) sys ; ( void ) t2 ; return 0 ; }
static int32_T ds_vsf ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmBoolVector out ; (
void ) t1 ; out = t2 -> mVSF ; out . mX [ 0 ] = false ; out . mX [ 1 ] =
false ; out . mX [ 2 ] = false ; out . mX [ 3 ] = false ; out . mX [ 4 ] =
false ; out . mX [ 5 ] = false ; out . mX [ 6 ] = false ; out . mX [ 7 ] =
false ; out . mX [ 8 ] = false ; out . mX [ 9 ] = false ; out . mX [ 10 ] =
false ; out . mX [ 11 ] = false ; out . mX [ 12 ] = false ; out . mX [ 13 ] =
false ; out . mX [ 14 ] = false ; out . mX [ 15 ] = false ; out . mX [ 16 ] =
false ; out . mX [ 17 ] = false ; out . mX [ 18 ] = false ; out . mX [ 19 ] =
false ; out . mX [ 20 ] = false ; out . mX [ 21 ] = false ; out . mX [ 22 ] =
false ; out . mX [ 23 ] = false ; out . mX [ 24 ] = false ; out . mX [ 25 ] =
false ; out . mX [ 26 ] = false ; ( void ) sys ; ( void ) t2 ; return 0 ; }
static int32_T ds_ic ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmRealVector out ; (
void ) t1 ; out = t2 -> mIC ; out . mX [ 0 ] = 0.0 ; out . mX [ 1 ] = 0.0 ;
out . mX [ 2 ] = 0.0 ; out . mX [ 3 ] = 0.0 ; out . mX [ 4 ] = 0.0 ; out . mX
[ 5 ] = 0.0 ; out . mX [ 6 ] = 0.0 ; out . mX [ 7 ] = 0.0 ; out . mX [ 8 ] =
0.0 ; out . mX [ 9 ] = 0.0 ; out . mX [ 10 ] = 0.0 ; out . mX [ 11 ] = 0.0 ;
out . mX [ 12 ] = 0.0 ; out . mX [ 13 ] = 0.0 ; out . mX [ 14 ] = 0.0 ; out .
mX [ 15 ] = 0.0 ; out . mX [ 16 ] = 0.0 ; out . mX [ 17 ] = 0.0 ; out . mX [
18 ] = 0.0 ; out . mX [ 19 ] = 0.0 ; out . mX [ 20 ] = 0.0 ; out . mX [ 21 ]
= 0.0 ; out . mX [ 22 ] = 0.0 ; out . mX [ 23 ] = 0.0 ; out . mX [ 24 ] = 0.0
; out . mX [ 25 ] = 0.0 ; out . mX [ 26 ] = 0.0 ; ( void ) sys ; ( void ) t2
; return 0 ; } static int32_T ds_icr ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_icr_im ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T
ds_icr_id ( const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0
; } static int32_T ds_icr_il ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_dxicr ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T
ds_dxicr_p ( const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { PmSparsityPattern out ; ( void ) t1 ; out = t2 ->
mDXICR_P ; out . mNumCol = 27ULL ; out . mNumRow = 0ULL ; out . mJc [ 0 ] = 0
; out . mJc [ 1 ] = 0 ; out . mJc [ 2 ] = 0 ; out . mJc [ 3 ] = 0 ; out . mJc
[ 4 ] = 0 ; out . mJc [ 5 ] = 0 ; out . mJc [ 6 ] = 0 ; out . mJc [ 7 ] = 0 ;
out . mJc [ 8 ] = 0 ; out . mJc [ 9 ] = 0 ; out . mJc [ 10 ] = 0 ; out . mJc
[ 11 ] = 0 ; out . mJc [ 12 ] = 0 ; out . mJc [ 13 ] = 0 ; out . mJc [ 14 ] =
0 ; out . mJc [ 15 ] = 0 ; out . mJc [ 16 ] = 0 ; out . mJc [ 17 ] = 0 ; out
. mJc [ 18 ] = 0 ; out . mJc [ 19 ] = 0 ; out . mJc [ 20 ] = 0 ; out . mJc [
21 ] = 0 ; out . mJc [ 22 ] = 0 ; out . mJc [ 23 ] = 0 ; out . mJc [ 24 ] = 0
; out . mJc [ 25 ] = 0 ; out . mJc [ 26 ] = 0 ; out . mJc [ 27 ] = 0 ; ( void
) sys ; ( void ) t2 ; return 0 ; } static int32_T ds_ddicr ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T
ds_ddicr_p ( const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { PmSparsityPattern out ; ( void ) t1 ; out = t2 ->
mDDICR_P ; out . mNumCol = 0ULL ; out . mNumRow = 0ULL ; out . mJc [ 0 ] = 0
; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T ds_tduicr_p (
const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { PmSparsityPattern out ; ( void ) t1 ; out = t2 ->
mTDUICR_P ; out . mNumCol = 14ULL ; out . mNumRow = 0ULL ; out . mJc [ 0 ] =
0 ; out . mJc [ 1 ] = 0 ; out . mJc [ 2 ] = 0 ; out . mJc [ 3 ] = 0 ; out .
mJc [ 4 ] = 0 ; out . mJc [ 5 ] = 0 ; out . mJc [ 6 ] = 0 ; out . mJc [ 7 ] =
0 ; out . mJc [ 8 ] = 0 ; out . mJc [ 9 ] = 0 ; out . mJc [ 10 ] = 0 ; out .
mJc [ 11 ] = 0 ; out . mJc [ 12 ] = 0 ; out . mJc [ 13 ] = 0 ; out . mJc [ 14
] = 0 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T ds_icrm (
const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0
; } static int32_T ds_icrm_p ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmSparsityPattern out ;
( void ) t1 ; out = t2 -> mICRM_P ; out . mNumCol = 27ULL ; out . mNumRow =
0ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 0 ; out . mJc [ 2 ] = 0 ; out
. mJc [ 3 ] = 0 ; out . mJc [ 4 ] = 0 ; out . mJc [ 5 ] = 0 ; out . mJc [ 6 ]
= 0 ; out . mJc [ 7 ] = 0 ; out . mJc [ 8 ] = 0 ; out . mJc [ 9 ] = 0 ; out .
mJc [ 10 ] = 0 ; out . mJc [ 11 ] = 0 ; out . mJc [ 12 ] = 0 ; out . mJc [ 13
] = 0 ; out . mJc [ 14 ] = 0 ; out . mJc [ 15 ] = 0 ; out . mJc [ 16 ] = 0 ;
out . mJc [ 17 ] = 0 ; out . mJc [ 18 ] = 0 ; out . mJc [ 19 ] = 0 ; out .
mJc [ 20 ] = 0 ; out . mJc [ 21 ] = 0 ; out . mJc [ 22 ] = 0 ; out . mJc [ 23
] = 0 ; out . mJc [ 24 ] = 0 ; out . mJc [ 25 ] = 0 ; out . mJc [ 26 ] = 0 ;
out . mJc [ 27 ] = 0 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static
int32_T ds_dxicrm ( const NeDynamicSystem * sys , const NeDynamicSystemInput
* t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ;
return 0 ; } static int32_T ds_dxicrm_p ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmSparsityPattern out ;
( void ) t1 ; out = t2 -> mDXICRM_P ; out . mNumCol = 27ULL ; out . mNumRow =
0ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 0 ; out . mJc [ 2 ] = 0 ; out
. mJc [ 3 ] = 0 ; out . mJc [ 4 ] = 0 ; out . mJc [ 5 ] = 0 ; out . mJc [ 6 ]
= 0 ; out . mJc [ 7 ] = 0 ; out . mJc [ 8 ] = 0 ; out . mJc [ 9 ] = 0 ; out .
mJc [ 10 ] = 0 ; out . mJc [ 11 ] = 0 ; out . mJc [ 12 ] = 0 ; out . mJc [ 13
] = 0 ; out . mJc [ 14 ] = 0 ; out . mJc [ 15 ] = 0 ; out . mJc [ 16 ] = 0 ;
out . mJc [ 17 ] = 0 ; out . mJc [ 18 ] = 0 ; out . mJc [ 19 ] = 0 ; out .
mJc [ 20 ] = 0 ; out . mJc [ 21 ] = 0 ; out . mJc [ 22 ] = 0 ; out . mJc [ 23
] = 0 ; out . mJc [ 24 ] = 0 ; out . mJc [ 25 ] = 0 ; out . mJc [ 26 ] = 0 ;
out . mJc [ 27 ] = 0 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static
int32_T ds_ddicrm ( const NeDynamicSystem * sys , const NeDynamicSystemInput
* t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ;
return 0 ; } static int32_T ds_ddicrm_p ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmSparsityPattern out ;
( void ) t1 ; out = t2 -> mDDICRM_P ; out . mNumCol = 0ULL ; out . mNumRow =
0ULL ; out . mJc [ 0 ] = 0 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static
int32_T ds_dimin ( const NeDynamicSystem * sys , const NeDynamicSystemInput *
t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ;
return 0 ; } static int32_T ds_dimax ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_m ( const NeDynamicSystem
* sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) {
PmRealVector out ; ( void ) t1 ; out = t2 -> mM ; out . mX [ 0 ] = - 8.0E-10
; out . mX [ 1 ] = - 0.0001 ; out . mX [ 2 ] = 1.0 ; out . mX [ 3 ] = - 0.06
; out . mX [ 4 ] = - 0.063578947368421054 ; out . mX [ 5 ] = -
0.89999999999999991 ; out . mX [ 6 ] = - 0.89999999999999991 ; out . mX [ 7 ]
= - 1.0 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T ds_dxm (
const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0
; } static int32_T ds_dxm_p ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmSparsityPattern out ;
( void ) t1 ; out = t2 -> mDXM_P ; out . mNumCol = 27ULL ; out . mNumRow =
8ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 0 ; out . mJc [ 2 ] = 0 ; out
. mJc [ 3 ] = 0 ; out . mJc [ 4 ] = 0 ; out . mJc [ 5 ] = 0 ; out . mJc [ 6 ]
= 0 ; out . mJc [ 7 ] = 0 ; out . mJc [ 8 ] = 0 ; out . mJc [ 9 ] = 0 ; out .
mJc [ 10 ] = 0 ; out . mJc [ 11 ] = 0 ; out . mJc [ 12 ] = 0 ; out . mJc [ 13
] = 0 ; out . mJc [ 14 ] = 0 ; out . mJc [ 15 ] = 0 ; out . mJc [ 16 ] = 0 ;
out . mJc [ 17 ] = 0 ; out . mJc [ 18 ] = 0 ; out . mJc [ 19 ] = 0 ; out .
mJc [ 20 ] = 0 ; out . mJc [ 21 ] = 0 ; out . mJc [ 22 ] = 0 ; out . mJc [ 23
] = 0 ; out . mJc [ 24 ] = 0 ; out . mJc [ 25 ] = 0 ; out . mJc [ 26 ] = 0 ;
out . mJc [ 27 ] = 0 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static
int32_T ds_ddm ( const NeDynamicSystem * sys , const NeDynamicSystemInput *
t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ;
return 0 ; } static int32_T ds_ddm_p ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmSparsityPattern out ;
( void ) t1 ; out = t2 -> mDDM_P ; out . mNumCol = 0ULL ; out . mNumRow =
8ULL ; out . mJc [ 0 ] = 0 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static
int32_T ds_dum ( const NeDynamicSystem * sys , const NeDynamicSystemInput *
t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ;
return 0 ; } static int32_T ds_dum_p ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmSparsityPattern out ;
( void ) t1 ; out = t2 -> mDUM_P ; out . mNumCol = 14ULL ; out . mNumRow =
8ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 0 ; out . mJc [ 2 ] = 0 ; out
. mJc [ 3 ] = 0 ; out . mJc [ 4 ] = 0 ; out . mJc [ 5 ] = 0 ; out . mJc [ 6 ]
= 0 ; out . mJc [ 7 ] = 0 ; out . mJc [ 8 ] = 0 ; out . mJc [ 9 ] = 0 ; out .
mJc [ 10 ] = 0 ; out . mJc [ 11 ] = 0 ; out . mJc [ 12 ] = 0 ; out . mJc [ 13
] = 0 ; out . mJc [ 14 ] = 0 ; ( void ) sys ; ( void ) t2 ; return 0 ; }
static int32_T ds_dtm ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_dtm_p ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { PmSparsityPattern out ; ( void ) t1 ; out = t2 -> mDTM_P ; out .
mNumCol = 1ULL ; out . mNumRow = 8ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ]
= 0 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T ds_dpm ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T
ds_dpm_p ( const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { PmSparsityPattern out ; ( void ) t1 ; out = t2 ->
mDPM_P ; out . mNumCol = 0ULL ; out . mNumRow = 8ULL ; out . mJc [ 0 ] = 0 ;
( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T ds_vmm ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { PmBoolVector out ; ( void ) t1 ; out = t2 -> mVMM ; out . mX [ 0 ] =
false ; out . mX [ 1 ] = false ; out . mX [ 2 ] = false ; out . mX [ 3 ] =
false ; out . mX [ 4 ] = false ; out . mX [ 5 ] = false ; out . mX [ 6 ] =
false ; out . mX [ 7 ] = false ; ( void ) sys ; ( void ) t2 ; return 0 ; }
static int32_T ds_obs_exp ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmRealVector out ;
real_T t0 [ 278 ] ; int32_T b ; ( void ) t1 ; out = t2 -> mOBS_EXP ; for ( b
= 0 ; b < 278 ; b ++ ) { t0 [ b ] = 0.0 ; } for ( b = 0 ; b < 278 ; b ++ ) {
out . mX [ b ] = t0 [ b ] ; } ( void ) sys ; ( void ) t2 ; return 0 ; }
static int32_T ds_dp_l ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_dp_i ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T
ds_dp_j ( const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0
; } static int32_T ds_dp_r ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_qx ( const NeDynamicSystem
* sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void )
t1 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T ds_qu ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T
ds_qt ( const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void ) sys ; ( void ) t2 ; return 0
; } static int32_T ds_q1 ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_qx_p ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { PmSparsityPattern out ; ( void ) t1 ; out = t2 -> mQX_P ; out .
mNumCol = 27ULL ; out . mNumRow = 27ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1
] = 0 ; out . mJc [ 2 ] = 0 ; out . mJc [ 3 ] = 0 ; out . mJc [ 4 ] = 0 ; out
. mJc [ 5 ] = 0 ; out . mJc [ 6 ] = 0 ; out . mJc [ 7 ] = 0 ; out . mJc [ 8 ]
= 0 ; out . mJc [ 9 ] = 0 ; out . mJc [ 10 ] = 0 ; out . mJc [ 11 ] = 0 ; out
. mJc [ 12 ] = 0 ; out . mJc [ 13 ] = 0 ; out . mJc [ 14 ] = 0 ; out . mJc [
15 ] = 0 ; out . mJc [ 16 ] = 0 ; out . mJc [ 17 ] = 0 ; out . mJc [ 18 ] = 0
; out . mJc [ 19 ] = 0 ; out . mJc [ 20 ] = 0 ; out . mJc [ 21 ] = 0 ; out .
mJc [ 22 ] = 0 ; out . mJc [ 23 ] = 0 ; out . mJc [ 24 ] = 0 ; out . mJc [ 25
] = 0 ; out . mJc [ 26 ] = 0 ; out . mJc [ 27 ] = 0 ; ( void ) sys ; ( void )
t2 ; return 0 ; } static int32_T ds_qu_p ( const NeDynamicSystem * sys ,
const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmSparsityPattern
out ; ( void ) t1 ; out = t2 -> mQU_P ; out . mNumCol = 14ULL ; out . mNumRow
= 27ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 0 ; out . mJc [ 2 ] = 0 ;
out . mJc [ 3 ] = 0 ; out . mJc [ 4 ] = 0 ; out . mJc [ 5 ] = 0 ; out . mJc [
6 ] = 0 ; out . mJc [ 7 ] = 0 ; out . mJc [ 8 ] = 0 ; out . mJc [ 9 ] = 0 ;
out . mJc [ 10 ] = 0 ; out . mJc [ 11 ] = 0 ; out . mJc [ 12 ] = 0 ; out .
mJc [ 13 ] = 0 ; out . mJc [ 14 ] = 0 ; ( void ) sys ; ( void ) t2 ; return 0
; } static int32_T ds_qt_p ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmSparsityPattern out ;
( void ) t1 ; out = t2 -> mQT_P ; out . mNumCol = 1ULL ; out . mNumRow =
27ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 0 ; ( void ) sys ; ( void )
t2 ; return 0 ; } static int32_T ds_q1_p ( const NeDynamicSystem * sys ,
const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmSparsityPattern
out ; ( void ) t1 ; out = t2 -> mQ1_P ; out . mNumCol = 1ULL ; out . mNumRow
= 27ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 0 ; ( void ) sys ; ( void )
t2 ; return 0 ; } static int32_T ds_var_tol ( const NeDynamicSystem * sys ,
const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmRealVector out
; ( void ) t1 ; out = t2 -> mVAR_TOL ; out . mX [ 0 ] = 1.0E-9 ; out . mX [ 1
] = 1.0E-9 ; out . mX [ 2 ] = 1.0E-9 ; out . mX [ 3 ] = 1.0E-9 ; out . mX [ 4
] = 1.0E-9 ; out . mX [ 5 ] = 1.0E-9 ; out . mX [ 6 ] = 1.0E-9 ; out . mX [ 7
] = 1.0E-9 ; out . mX [ 8 ] = 1.0E-9 ; out . mX [ 9 ] = 1.0E-9 ; out . mX [
10 ] = 1.0E-9 ; out . mX [ 11 ] = 1.0E-9 ; out . mX [ 12 ] = 1.0E-9 ; out .
mX [ 13 ] = 1.0E-9 ; out . mX [ 14 ] = 1.0E-9 ; out . mX [ 15 ] = 1.0E-9 ;
out . mX [ 16 ] = 1.0E-9 ; out . mX [ 17 ] = 1.0E-9 ; out . mX [ 18 ] =
1.0E-9 ; out . mX [ 19 ] = 1.0E-9 ; out . mX [ 20 ] = 1.0E-9 ; out . mX [ 21
] = 1.0E-9 ; out . mX [ 22 ] = 1.0E-9 ; out . mX [ 23 ] = 1.0E-9 ; out . mX [
24 ] = 1.0E-9 ; out . mX [ 25 ] = 1.0E-9 ; out . mX [ 26 ] = 1.0E-9 ; ( void
) sys ; ( void ) t2 ; return 0 ; } static int32_T ds_eq_tol ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { PmRealVector out ; ( void ) t1 ; out = t2 -> mEQ_TOL ; out . mX [ 0 ]
= 1.0E-9 ; out . mX [ 1 ] = 1.0E-9 ; out . mX [ 2 ] = 1.0E-9 ; out . mX [ 3 ]
= 1.0E-9 ; out . mX [ 4 ] = 1.0E-9 ; out . mX [ 5 ] = 1.0E-9 ; out . mX [ 6 ]
= 1.0E-9 ; out . mX [ 7 ] = 1.0E-9 ; out . mX [ 8 ] = 1.0E-9 ; out . mX [ 9 ]
= 1.0E-9 ; out . mX [ 10 ] = 1.0E-9 ; out . mX [ 11 ] = 1.0E-9 ; out . mX [
12 ] = 1.0E-9 ; out . mX [ 13 ] = 1.0E-9 ; out . mX [ 14 ] = 1.0E-9 ; out .
mX [ 15 ] = 1.0E-9 ; out . mX [ 16 ] = 1.0E-9 ; out . mX [ 17 ] = 1.0E-9 ;
out . mX [ 18 ] = 1.0E-9 ; out . mX [ 19 ] = 1.0E-9 ; out . mX [ 20 ] =
1.0E-9 ; out . mX [ 21 ] = 1.0E-9 ; out . mX [ 22 ] = 1.0E-9 ; out . mX [ 23
] = 1.0E-9 ; out . mX [ 24 ] = 1.0E-9 ; out . mX [ 25 ] = 1.0E-9 ; out . mX [
26 ] = 1.0E-9 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T
ds_lv ( const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { PmBoolVector out ; ( void ) t1 ; out = t2 -> mLV ;
out . mX [ 0 ] = false ; out . mX [ 1 ] = false ; out . mX [ 2 ] = false ;
out . mX [ 3 ] = false ; out . mX [ 4 ] = false ; out . mX [ 5 ] = false ;
out . mX [ 6 ] = false ; out . mX [ 7 ] = false ; out . mX [ 8 ] = true ; out
. mX [ 9 ] = true ; out . mX [ 10 ] = false ; out . mX [ 11 ] = false ; out .
mX [ 12 ] = false ; out . mX [ 13 ] = false ; out . mX [ 14 ] = false ; out .
mX [ 15 ] = false ; out . mX [ 16 ] = false ; out . mX [ 17 ] = false ; out .
mX [ 18 ] = false ; out . mX [ 19 ] = false ; out . mX [ 20 ] = false ; out .
mX [ 21 ] = false ; out . mX [ 22 ] = false ; out . mX [ 23 ] = false ; out .
mX [ 24 ] = false ; out . mX [ 25 ] = false ; out . mX [ 26 ] = false ; (
void ) sys ; ( void ) t2 ; return 0 ; } static int32_T ds_slv ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { PmBoolVector out ; ( void ) t1 ; out = t2 -> mSLV ; out . mX [ 0 ] =
false ; out . mX [ 1 ] = false ; out . mX [ 2 ] = false ; out . mX [ 3 ] =
false ; out . mX [ 4 ] = false ; out . mX [ 5 ] = false ; out . mX [ 6 ] =
false ; out . mX [ 7 ] = false ; out . mX [ 8 ] = true ; out . mX [ 9 ] =
true ; out . mX [ 10 ] = false ; out . mX [ 11 ] = false ; out . mX [ 12 ] =
false ; out . mX [ 13 ] = false ; out . mX [ 14 ] = false ; out . mX [ 15 ] =
false ; out . mX [ 16 ] = false ; out . mX [ 17 ] = false ; out . mX [ 18 ] =
false ; out . mX [ 19 ] = false ; out . mX [ 20 ] = false ; out . mX [ 21 ] =
false ; out . mX [ 22 ] = false ; out . mX [ 23 ] = false ; out . mX [ 24 ] =
false ; out . mX [ 25 ] = false ; out . mX [ 26 ] = false ; ( void ) sys ; (
void ) t2 ; return 0 ; } static int32_T ds_nldv ( const NeDynamicSystem * sys
, const NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmBoolVector
out ; ( void ) t1 ; out = t2 -> mNLDV ; out . mX [ 0 ] = false ; out . mX [ 1
] = false ; out . mX [ 2 ] = false ; out . mX [ 3 ] = false ; out . mX [ 4 ]
= false ; out . mX [ 5 ] = false ; out . mX [ 6 ] = false ; out . mX [ 7 ] =
true ; out . mX [ 8 ] = false ; out . mX [ 9 ] = false ; out . mX [ 10 ] =
false ; out . mX [ 11 ] = false ; out . mX [ 12 ] = false ; out . mX [ 13 ] =
false ; out . mX [ 14 ] = false ; out . mX [ 15 ] = false ; out . mX [ 16 ] =
false ; out . mX [ 17 ] = false ; out . mX [ 18 ] = false ; out . mX [ 19 ] =
false ; out . mX [ 20 ] = false ; out . mX [ 21 ] = false ; out . mX [ 22 ] =
false ; out . mX [ 23 ] = false ; out . mX [ 24 ] = false ; out . mX [ 25 ] =
false ; out . mX [ 26 ] = false ; ( void ) sys ; ( void ) t2 ; return 0 ; }
static int32_T ds_sclv ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmBoolVector out ; (
void ) t1 ; out = t2 -> mSCLV ; out . mX [ 0 ] = false ; out . mX [ 1 ] =
false ; out . mX [ 2 ] = false ; out . mX [ 3 ] = false ; out . mX [ 4 ] =
false ; out . mX [ 5 ] = false ; out . mX [ 6 ] = false ; out . mX [ 7 ] =
false ; out . mX [ 8 ] = false ; out . mX [ 9 ] = false ; out . mX [ 10 ] =
false ; out . mX [ 11 ] = false ; out . mX [ 12 ] = false ; out . mX [ 13 ] =
false ; out . mX [ 14 ] = false ; out . mX [ 15 ] = false ; out . mX [ 16 ] =
false ; out . mX [ 17 ] = false ; out . mX [ 18 ] = false ; out . mX [ 19 ] =
false ; out . mX [ 20 ] = false ; out . mX [ 21 ] = false ; out . mX [ 22 ] =
false ; out . mX [ 23 ] = false ; out . mX [ 24 ] = false ; out . mX [ 25 ] =
false ; out . mX [ 26 ] = false ; ( void ) sys ; ( void ) t2 ; return 0 ; }
static int32_T ds_dxy ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmRealVector out ; (
void ) t1 ; out = t2 -> mDXY ; out . mX [ 0 ] = 1.0 ; out . mX [ 1 ] = 1.0 ;
out . mX [ 2 ] = 1.0 ; out . mX [ 3 ] = 1.0 ; out . mX [ 4 ] = 1.0 ; out . mX
[ 5 ] = 1.0 ; out . mX [ 6 ] = 1.0 ; out . mX [ 7 ] = 1.0 ; out . mX [ 8 ] =
1.0 ; out . mX [ 9 ] = 1.0 ; out . mX [ 10 ] = 1.0 ; out . mX [ 11 ] = 1.0 ;
out . mX [ 12 ] = 1.0 ; out . mX [ 13 ] = 1.0 ; out . mX [ 14 ] = - 1.0 ; out
. mX [ 15 ] = 1.0 ; out . mX [ 16 ] = - 1.0 ; out . mX [ 17 ] = 1.0 ; out .
mX [ 18 ] = 1.0 ; out . mX [ 19 ] = - 1.0 ; out . mX [ 20 ] = 1.0 ; out . mX
[ 21 ] = - 1.0 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static int32_T
ds_duy ( const NeDynamicSystem * sys , const NeDynamicSystemInput * t1 ,
NeDsMethodOutput * t2 ) { PmRealVector out ; ( void ) t1 ; out = t2 -> mDUY ;
out . mX [ 0 ] = 1.0 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static
int32_T ds_duy_p ( const NeDynamicSystem * sys , const NeDynamicSystemInput *
t1 , NeDsMethodOutput * t2 ) { PmSparsityPattern out ; ( void ) t1 ; out = t2
-> mDUY_P ; out . mNumCol = 14ULL ; out . mNumRow = 16ULL ; out . mJc [ 0 ] =
0 ; out . mJc [ 1 ] = 1 ; out . mJc [ 2 ] = 1 ; out . mJc [ 3 ] = 1 ; out .
mJc [ 4 ] = 1 ; out . mJc [ 5 ] = 1 ; out . mJc [ 6 ] = 1 ; out . mJc [ 7 ] =
1 ; out . mJc [ 8 ] = 1 ; out . mJc [ 9 ] = 1 ; out . mJc [ 10 ] = 1 ; out .
mJc [ 11 ] = 1 ; out . mJc [ 12 ] = 1 ; out . mJc [ 13 ] = 1 ; out . mJc [ 14
] = 1 ; out . mIr [ 0 ] = 0 ; ( void ) sys ; ( void ) t2 ; return 0 ; }
static int32_T ds_mduy_p ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmSparsityPattern out ;
( void ) t1 ; out = t2 -> mMDUY_P ; out . mNumCol = 14ULL ; out . mNumRow =
16ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 0 ; out . mJc [ 2 ] = 0 ; out
. mJc [ 3 ] = 0 ; out . mJc [ 4 ] = 0 ; out . mJc [ 5 ] = 0 ; out . mJc [ 6 ]
= 0 ; out . mJc [ 7 ] = 0 ; out . mJc [ 8 ] = 0 ; out . mJc [ 9 ] = 0 ; out .
mJc [ 10 ] = 0 ; out . mJc [ 11 ] = 0 ; out . mJc [ 12 ] = 0 ; out . mJc [ 13
] = 0 ; out . mJc [ 14 ] = 0 ; ( void ) sys ; ( void ) t2 ; return 0 ; }
static int32_T ds_mdxy_p ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { PmSparsityPattern out ;
( void ) t1 ; out = t2 -> mMDXY_P ; out . mNumCol = 27ULL ; out . mNumRow =
16ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1 ] = 0 ; out . mJc [ 2 ] = 0 ; out
. mJc [ 3 ] = 0 ; out . mJc [ 4 ] = 0 ; out . mJc [ 5 ] = 0 ; out . mJc [ 6 ]
= 0 ; out . mJc [ 7 ] = 0 ; out . mJc [ 8 ] = 0 ; out . mJc [ 9 ] = 0 ; out .
mJc [ 10 ] = 0 ; out . mJc [ 11 ] = 0 ; out . mJc [ 12 ] = 0 ; out . mJc [ 13
] = 0 ; out . mJc [ 14 ] = 0 ; out . mJc [ 15 ] = 0 ; out . mJc [ 16 ] = 0 ;
out . mJc [ 17 ] = 0 ; out . mJc [ 18 ] = 0 ; out . mJc [ 19 ] = 0 ; out .
mJc [ 20 ] = 0 ; out . mJc [ 21 ] = 0 ; out . mJc [ 22 ] = 0 ; out . mJc [ 23
] = 0 ; out . mJc [ 24 ] = 0 ; out . mJc [ 25 ] = 0 ; out . mJc [ 26 ] = 0 ;
out . mJc [ 27 ] = 0 ; ( void ) sys ; ( void ) t2 ; return 0 ; } static
int32_T ds_tduy_p ( const NeDynamicSystem * sys , const NeDynamicSystemInput
* t1 , NeDsMethodOutput * t2 ) { PmSparsityPattern out ; ( void ) t1 ; out =
t2 -> mTDUY_P ; out . mNumCol = 14ULL ; out . mNumRow = 16ULL ; out . mJc [ 0
] = 0 ; out . mJc [ 1 ] = 1 ; out . mJc [ 2 ] = 1 ; out . mJc [ 3 ] = 1 ; out
. mJc [ 4 ] = 1 ; out . mJc [ 5 ] = 1 ; out . mJc [ 6 ] = 1 ; out . mJc [ 7 ]
= 1 ; out . mJc [ 8 ] = 1 ; out . mJc [ 9 ] = 1 ; out . mJc [ 10 ] = 1 ; out
. mJc [ 11 ] = 1 ; out . mJc [ 12 ] = 1 ; out . mJc [ 13 ] = 1 ; out . mJc [
14 ] = 1 ; out . mIr [ 0 ] = 0 ; ( void ) sys ; ( void ) t2 ; return 0 ; }
static int32_T ds_dty ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * t2 ) { ( void ) t1 ; ( void )
sys ; ( void ) t2 ; return 0 ; } static int32_T ds_dty_p ( const
NeDynamicSystem * sys , const NeDynamicSystemInput * t1 , NeDsMethodOutput *
t2 ) { PmSparsityPattern out ; ( void ) t1 ; out = t2 -> mDTY_P ; out .
mNumCol = 1ULL ; out . mNumRow = 16ULL ; out . mJc [ 0 ] = 0 ; out . mJc [ 1
] = 0 ; ( void ) sys ; ( void ) t2 ; return 0 ; }
