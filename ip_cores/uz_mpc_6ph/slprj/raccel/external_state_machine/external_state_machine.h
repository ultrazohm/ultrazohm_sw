#ifndef RTW_HEADER_external_state_machine_h_
#define RTW_HEADER_external_state_machine_h_
#include <stddef.h>
#include <emmintrin.h>
#include <string.h>
#include "rtw_modelmap_simtarget.h"
#ifndef external_state_machine_COMMON_INCLUDES_
#define external_state_machine_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "sigstream_rtw.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging_simtarget.h"
#include "dt_info.h"
#include "ext_work.h"
#include "nesl_rtw.h"
#include "external_state_machine_605b847d_1_gateway.h"
#endif
#include "external_state_machine_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rt_defines.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#define MODEL_NAME external_state_machine
#define NSAMPLE_TIMES (6) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (368) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (0)   
#elif NCSTATES != 0
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T fcozgxup2r ; real_T dqp13zkjbj ; real_T lmkwkw2lhs [
12 ] ; real_T kgu2nomxi3 ; real_T coilnsyskm ; real_T kkvwllx1gm [ 4 ] ;
real_T hs3rg4x4ij [ 12 ] ; real_T lvlyzea3mc [ 4 ] ; real_T pjjqylgrq1 [ 4 ]
; real_T dcri1qgabh [ 4 ] ; real_T iui5f4c211 [ 4 ] ; real_T ofh24d2eaz [ 4 ]
; real_T moi15iwh0h [ 4 ] ; real_T obyantfxn4 [ 4 ] ; real_T p25clet1cn [ 4 ]
; real_T hchz4qh53z [ 4 ] ; real_T pmg1smq0gc [ 4 ] ; real_T dp1kyta3vn [ 4 ]
; real_T jugjyagxhv [ 4 ] ; real_T jykmlqtkrp [ 4 ] ; real_T dqinqamfi1 [ 39
] ; real_T dp4jpvrmv3 ; real_T lp2l32tgao ; real_T bghjerrr0e ; real_T
c1dsvyiwhm [ 12 ] ; real_T ihxw3fzoje ; real_T p3mop3zcfx [ 6 ] ; real_T
fydkgnnnmt ; real_T hrkx0npxpj ; real_T mnewdly4rk [ 12 ] ; real_T ikiwxh3pr0
; uint32_T clw5wzlj5g ; uint32_T ifqle4ujtr ; uint32_T ggywohjzma ; uint32_T
k3rwb1nqzz ; uint32_T e1seijo30z ; uint32_T kgid2mdewr ; uint32_T p4xxqflaz5
; uint32_T m2w3iz3aee ; uint32_T b04dlpqzmt ; uint32_T iqah1i2pca ; uint32_T
cvltirj1q3 ; uint32_T cpaefdqklz ; uint32_T he2mr2rcnd ; uint32_T jfmanze4hz
; uint32_T kxdt20352r ; uint32_T aqyozdfrvn ; uint32_T aazbfhr2ut ; uint32_T
ff5hmeglkf ; uint32_T dz3wnztbfs ; uint32_T ae4vubc5b1 ; uint32_T hc43hyjorn
; uint32_T pycin0ogk2 ; uint32_T k5oalu5yu0 ; uint32_T f4vkxxvqv1 ; uint32_T
ovneqytvb3 ; uint32_T fsht3xlhlm ; uint32_T lyfo12bhlu ; uint32_T lqon1cuusl
; uint32_T lckc244i1e ; uint32_T jijwjr1aep ; uint32_T cposlljum2 ; uint32_T
lxudeufh1d ; uint32_T akztohrenr ; uint32_T cgb3qjmnm1 ; uint32_T m3fqdyqaq0
; uint32_T dcv0qoidsm ; uint32_T plsxbe2rwl ; uint32_T brxbx3aefy ; uint32_T
jrwqq01e0j ; uint32_T kvgqqefxxk ; uint32_T jfag3ljpz2 ; uint32_T m4sshnlbnd
; uint32_T f5vvqvlmdf ; uint32_T cxwqwlgqc4 ; uint32_T e2cucg45wx ; uint32_T
avpwddkess ; uint32_T hwynjfgmpa ; uint32_T j53pgmxfiw ; uint32_T h0sxejbfrf
; uint32_T lffhrtss2z ; uint32_T aef0nmtmyw ; uint32_T bwt2ta3y4t ; uint32_T
ijz2qzhhuv ; uint32_T ebml2kyo2g ; uint32_T nt0shde4ft ; uint32_T hec3bzzryy
; uint32_T ca0aodvq2z ; uint32_T fmsyx2mkyl ; uint32_T gwflnfyd3y ; uint32_T
l0ihtrjlj1 ; uint32_T aioy1sakev ; uint32_T gg3t0vmeel ; uint32_T gdwi5f1bbu
; uint32_T pql34arxv5 ; uint32_T ntdmohlrsu ; uint32_T aiyagoteaz ; int32_T
ci4qtrfbmi ; int32_T askifyoshw ; int32_T cg2pnptrpr ; int32_T aajgiijj3s ;
int32_T n2vhiuxqrd ; int32_T i2hx5d4jqp ; int32_T n1grg5qbak ; int32_T
ptih1c04wn ; int32_T bcnxdxqltu ; int32_T bb5t3ibe0p ; int32_T mxlokkcfhc ;
int32_T dyj5bgbcuc ; int32_T nwjbxd5r0c ; int32_T iiaud3znpo ; int32_T
nysw21g0bp ; int32_T bpxzqnm4l3 ; int32_T brzsggcuou ; int32_T awb2jvsx2b ;
int32_T fuouordfgu ; int32_T djnlln1rt3 ; int32_T i2mvlkkrve ; int32_T
h5u0rntcrt ; int32_T gdeqi52c3t ; int32_T jdjvvy4qkx ; int32_T nt5gslipee ;
int32_T fj24gr35mh ; int32_T drn44sdqme ; int32_T mucr14b03d ; int32_T
g1xkscgfyp ; int32_T dzpm51udig ; int32_T gu53noaj33 ; int32_T b3a00fi0lk ;
int32_T iv3zvpc4hj ; int32_T kpt5p5oivq ; int32_T ltkwgay4se ; int32_T
ezwccynacw ; int32_T bptsg3neq1 ; int32_T nwlyfnjpph ; int32_T by5z1sdg50 ;
int32_T pvifqhny22 ; int32_T atmzkwoefg ; int32_T a1mkbd21bt ; int32_T
mb1dausxob ; int32_T pdklgdrtks ; int32_T m02jkz3erl ; int32_T b2wveawkxh ;
int32_T lbnydus2mk ; int32_T eozaupyiiy ; int32_T dxma5mr1lx ; int32_T
ladqh1l1ay ; int32_T cym20fugcb ; int32_T nthdrri3s0 ; int32_T a2351vndi4 ;
int32_T kvgxa5awww ; int32_T crbyngd1fp ; int32_T otw0xeijil ; int32_T
erx2bhl3a2 ; int32_T fs5cilycmk ; int32_T jmpbc3xkzj ; int32_T aox4zs4akc ;
int32_T nrwwbchbrw ; int32_T gssmxnvfua ; int32_T ji4elq5u20 ; int32_T
cf2gbuvld4 ; int32_T fgyfte5o4r ; int32_T kokmmzmj5h ; int32_T am4ducelp3 ;
int32_T lhxfwcched ; int32_T dddfdi4ui2 ; int32_T eggdor1wld ; int32_T
iczjnwpnj2 ; int32_T n44tlwb0da ; int32_T nxoknrq2e3 ; int32_T if42drdoar ;
int32_T bnkb2z4ycm ; int32_T oxqakuykpz ; int32_T c4z2wnbs4r ; int32_T
ldbpssyze0 ; int32_T bwcpigp5ap ; int32_T pkt0kcmmwy ; int32_T i1cv5s0qez ;
int32_T b3k1jc2spd ; int32_T oc1bhsd51n ; int32_T mbfvpiofjh ; int32_T
obrkszk0cv ; int32_T dy41bixjgm ; int32_T d3q00brn3g ; int32_T csksiawycx ;
int32_T catclpkjvb ; int32_T df5a40typz ; int32_T biilum20bi ; int32_T
es1xmwhqgi ; int32_T kzgxqag1v5 ; int32_T n5nlogcsom ; int32_T agynjzlh54 ;
int32_T nmkdcrt0qx ; int32_T ih5jd5n4ln ; int32_T jqgatvc5ch ; int32_T
dds5fk25sg ; int32_T dastx34d4p ; int32_T cvmrh4mo4a ; int32_T nursxirg3t ;
int32_T pr325ipqz2 ; int32_T a45zgfroe3 ; int32_T imof4oqoms ; int32_T
b5jzoasf2i ; int32_T j1jikgvsbe ; int32_T ctvejegmmg ; int32_T loi2dpkdmq ;
int32_T icibs2siak ; int32_T iga5ruvk1d ; int32_T kwcdebbbzm ; int32_T
d2ue2amye1 ; int32_T ogw0jlrsav ; int32_T fgekdgytcl ; int32_T js1jw0gwoh ;
int32_T ow0lbcm3nw ; int32_T g4tjr4rodb ; int32_T ecbinphpys ; int32_T
ark4jw0ol1 ; int32_T j0zjiyvk0f ; int32_T ktdz5w4hac ; int32_T oomqbqsxdx ;
int32_T b51fi2l4e5 ; int32_T eymox4nbbw ; int32_T ogo4agvx4m ; int32_T
dmllkyn2lu ; int32_T dsob5gptyg ; int32_T ikf05abn4x ; int32_T nqmjim4gch ;
int32_T k2w1rqjksr ; int32_T f3x3ayd3vh ; int32_T a1csjnflft ; int32_T
lcnsuqiqav ; int32_T gw4aeghx5n ; int32_T kjitpnmckx ; int32_T cfzlg02rpx ;
int32_T jfynefzxod ; int32_T klau3bhcok ; int32_T iw2bemw1sc ; int32_T
ecqkpipjds ; int32_T ai05mevrg4 ; int32_T mm5qjw1ml3 ; int32_T dugaktvjly ;
int32_T gcovqfjvjy ; int32_T chqj5hplsb ; int32_T eqsz3uj5cb ; int32_T
mrc40d2oaq ; int32_T erfdu1ogpt ; int32_T dxhgfbvkpv ; int32_T ae3nlgfi0l ;
int32_T g4sstpqgr1 ; int32_T cqnfwarygo ; int32_T ilhom1roft ; int32_T
ank1auk353 ; int32_T o1nheal4dl ; int32_T ldtzknqryt ; int32_T l40jsbi33q ;
int32_T gkbeex3aov ; int32_T egxt2dwnsf ; int32_T as3hkfei2t ; int32_T
pxism14cfu ; int32_T otjtab4rn1 ; int32_T g1idrksute ; int32_T lb2a0b0xi1 ;
int32_T djtjkyc3yb ; int32_T nbwy3kxczg ; int32_T mtqsyo3cre ; int32_T
dkdzjfwmsv ; int32_T enzloc2m4v ; int32_T fbvmghhwrb ; int32_T a2yzlhimua ;
int32_T gmmx5idrtv ; int32_T mjaavthri3 ; int32_T lgs4fxnwq4 ; int32_T
mtzx4xvlax ; int32_T pslktcu2l4 ; int32_T cshwcojbkl ; int32_T bz5z1h3w5l ;
int32_T avqujsxhbp ; int32_T emojjx24as ; int32_T iaykrjeium ; int32_T
jitz2wpx1e ; int32_T hlquagpjg5 ; int32_T ezujvliyy2 ; int32_T jralpmdrls ;
int32_T iykbyydmon ; int32_T nporvgpwl5 ; int32_T bd2h1p1dwd ; int32_T
blfvxdt1an ; int32_T m2gcavesop ; int32_T nkpmpn3xav ; int32_T ohixx01idi ;
int32_T hp4mdxny0h ; int32_T l2ps0onw3e ; int32_T kvkl30wy5k ; int32_T
b42v5ih2op ; int32_T lcy00sgc1j ; int32_T lrabwpf3mg ; int32_T cjk0kj5ilh ;
int32_T d1yvyet12z ; int32_T fbuev32gxu ; int32_T kvqdejhsfd ; uint16_T
abmmtw4kju [ 6 ] ; uint16_T mhzb0kyqbm ; uint16_T mh05k33kvh [ 6 ] ; uint8_T
du0yxgyaqq ; uint8_T dybu4alcby ; uint8_T ie4ievmzf2 ; uint8_T cqzet413xp ;
boolean_T dnri1ykhvw ; boolean_T b3b4mzzxo5 ; boolean_T kpjhx4ulbx ;
boolean_T l1y4ubxzp4 ; boolean_T hgpvoewzdj ; boolean_T hzvrhcluwq ;
boolean_T jwzsfkd1v0 ; boolean_T nazisikh4e ; boolean_T jgei5mlpwd ;
boolean_T nmc2xljzas ; boolean_T eqmn14zfna ; boolean_T d4ao3nqx04 ;
boolean_T lnykytlnzs ; boolean_T dzkyf1yhey ; boolean_T mljf2qmgrn ;
boolean_T nu0uuuhmkq [ 12 ] ; boolean_T moankq0vrm ; boolean_T olsapwr1z4 ;
boolean_T p2yxu3rxuj ; boolean_T ojitybxqj0 ; boolean_T bt2grerp03 ;
boolean_T lo0tdpg4mu ; boolean_T od0dkd0ufc ; boolean_T ltwz301alb ;
boolean_T dhfjsgln1r ; boolean_T lncdbextut ; boolean_T pbs13vjlcq ;
boolean_T icer2di2hv ; boolean_T aod5ud5rjm ; boolean_T a4e5d4dld3 ;
boolean_T c1qtgfuqip ; boolean_T eg2janikev ; boolean_T mzofnr1feg ;
boolean_T cwpwdtuvmh ; boolean_T k2mr5pqns3 ; boolean_T o52zy5et4p ;
boolean_T oidxdtv5az ; boolean_T c2nvlokfal ; boolean_T aifqhbnefh ;
boolean_T plgbvxdc4e ; boolean_T gzgid3ewbc ; boolean_T nsawlq2dr0 ;
boolean_T jr4adxnn11 ; boolean_T nfdfoxbx1p ; boolean_T piyxjz1ppc ;
boolean_T enr0e4zgln ; boolean_T gkgzqppshb ; boolean_T bfl4myxuyy ;
boolean_T ah2bxq3tfk ; boolean_T cilyi3ulpf ; boolean_T cwxbyautnv ;
boolean_T ju33m4cdrm [ 6 ] ; boolean_T jmghpd1ccq [ 6 ] ; boolean_T
mtim2c0h5d ; boolean_T n5zujmxxlk ; boolean_T gtwmnrkwjh [ 6 ] ; boolean_T
j0okylvykn [ 6 ] ; boolean_T a0h3ocewhn [ 6 ] ; boolean_T figchqmbtq [ 768 ]
; } B ; typedef struct { real_T eqflivmrhn ; real_T cswz51ldzr [ 552 ] ;
real_T nyvul1g5hq [ 46 ] ; real_T hsqs4zwebm [ 2 ] ; real_T dpcwky0ftp [ 2 ]
; real_T gs1swkfg54 [ 2 ] ; real_T gdl4ajdoji [ 2 ] ; real_T bolh2wuudn [ 2 ]
; real_T d5xwueu1t1 [ 2 ] ; real_T prcf24nsej [ 2 ] ; real_T aqpiz15lug [ 2 ]
; real_T jlewq0umhw [ 2 ] ; real_T iidy2fb2s0 [ 2 ] ; real_T avgpwos2k1 [ 2 ]
; real_T ctwao3eeah [ 2 ] ; real_T hzhlqw3x0a [ 2 ] ; real_T b22w2zl35z [ 2 ]
; real_T pw3p2quktx [ 27 ] ; real_T nivuhwp25t ; real_T aslubgdt3m ; real_T
bo2doil4yr [ 12 ] ; real_T f5ozdvquu0 ; real_T dhn4ocr3hx [ 6 ] ; real_T
l2xam1sqj3 ; struct { void * LoggedData [ 5 ] ; } n5dtdvqf3z ; struct { void
* LoggedData [ 4 ] ; } b2tn0x2gwc ; struct { void * LoggedData [ 2 ] ; }
nrufvbsky3 ; struct { void * LoggedData [ 3 ] ; } ho1dzeztqh ; struct { void
* LoggedData [ 2 ] ; } oc2jgxsp0c ; struct { void * LoggedData [ 2 ] ; }
l4j4bsboyz ; struct { void * LoggedData [ 2 ] ; } cheft0msva ; struct { void
* LoggedData [ 4 ] ; } efbj2pbwsp ; struct { void * LoggedData [ 4 ] ; }
hsznnmxatb ; struct { void * LoggedData ; } hf1lm5pfin ; struct { void *
LoggedData [ 2 ] ; } ca2ri1oftl ; struct { void * LoggedData [ 2 ] ; }
bhpirgeiwj ; struct { void * LoggedData [ 6 ] ; } letioycjii ; struct { void
* LoggedData ; } gcsdtms0hp ; void * eqk1drlg11 ; void * icwn2ozeda ; void *
ezqt0kagwy ; void * kym5efhlub ; void * foiypp1yj3 ; void * projzzi4r1 ; void
* fylvpzqjub ; void * i2fd1id5ne ; void * iuq4usvw3k ; void * bjpje3o3le ;
struct { void * LoggedData ; } alctduyfki ; void * osezho2aqf ; void *
agm4mit3ol ; void * m1urw5zcgj ; void * miqlkfyp4d ; void * dtl2ynudxx ;
struct { void * LoggedData [ 2 ] ; } ochbi50c4s ; struct { void * LoggedData
[ 2 ] ; } b0pufuivqz ; struct { void * LoggedData [ 3 ] ; } klwogl0nlt ;
struct { void * LoggedData [ 2 ] ; } kat0satdzm ; struct { void * LoggedData
[ 10 ] ; } dotpzch5iu ; struct { void * LoggedData [ 2 ] ; } lh2hervkbm ;
struct { void * LoggedData [ 4 ] ; } ixd50rs0xr ; struct { void * LoggedData
[ 5 ] ; } c1mp1whnby ; struct { void * LoggedData [ 4 ] ; } kycdgbrtxt ;
struct { void * LoggedData [ 4 ] ; } bxan4zguxa ; struct { void * LoggedData
[ 3 ] ; } gqvvjo2r3l ; uint32_T ph0vcv3xx3 ; uint32_T a44brdngje ; uint32_T
eflvhzawfx ; uint32_T fgw43ruw4a ; uint32_T fmuqbfwzh5 ; uint32_T eqrgko1gta
[ 2 ] ; uint32_T a0w5rld3qp ; uint32_T i5oosdelei [ 2 ] ; uint32_T czrfyxldkr
; uint32_T ap4al0flqc [ 2 ] ; uint32_T araqcjki03 ; uint32_T grzztx5z3t [ 2 ]
; uint32_T pu31a1u0ym ; uint32_T ccybwu5xhu [ 2 ] ; uint32_T ioouqwat4b ;
uint32_T hnzys0m5ax [ 4 ] ; uint32_T iqjotnra5s ; uint32_T gfqr4qerea ;
uint32_T ogfcozp3ha [ 2 ] ; uint32_T hn51ztd0c5 ; int32_T kqngwowbti ;
int32_T p0vrjbkra4 ; int32_T oo1tz3vklj ; int32_T lrc0tzzhzo ; int32_T
oyszp2gent ; int32_T d4hzqyikcn [ 2 ] ; int32_T fury44sqqm [ 2 ] ; int32_T
laoco1bcxw ; int32_T mrvzqk5v41 ; int32_T g20ustkt4z [ 5 ] ; int32_T
avvyilapoa [ 5 ] ; int32_T foc2ckjj1g [ 2 ] ; int32_T i532k0jjr1 [ 2 ] ;
int32_T m2fkorms3o [ 2 ] ; int32_T blm3g2brtf [ 2 ] ; int32_T bec2rxqq1j [ 2
] ; int32_T myxtgd1g4e [ 2 ] ; int32_T fffm4mkes3 [ 2 ] ; int32_T eyxsco2dff
[ 2 ] ; int32_T fdwah0oe4l [ 2 ] ; int32_T n4fnhtn2lt [ 2 ] ; int32_T
nh3n1i2252 [ 2 ] ; int32_T mbcv4ealjf [ 2 ] ; int32_T cp1lcufpzz [ 3 ] ;
int32_T b4sxh342jo [ 3 ] ; int32_T eqgjomcuym [ 3 ] ; int32_T hlwvvh0lau [ 3
] ; int32_T ohek5ifq4c ; int32_T ogg51iu3le ; int32_T oafnb5m1xu ; int32_T
ez0ndysdkt ; int32_T lshvgervmz [ 2 ] ; int32_T i5zfdbldzp ; int32_T
fuldp5a1f0 [ 2 ] ; int32_T oqsiocuy5n ; int32_T grpty3jhof ; int32_T
m5ldqtyv4e ; int32_T ifm3gom5zm ; int32_T j24zau2mqs ; int32_T f1ldti12wr ;
int32_T npzaonjadm ; int32_T fguecqgzna ; int32_T eddlb1pg2o ; int32_T
msynz5xkym ; int32_T edhmyuvegf ; int32_T povgsg11rd [ 2 ] ; int32_T
meheisfdqg [ 2 ] ; int32_T jyvtobstrz [ 2 ] ; int32_T huakhkgrgb ; int32_T
nqh2idndlu ; int32_T ofddmqvvnr ; int32_T pbxsharq1k ; int32_T b2jfj0g343 [ 2
] ; int32_T ju4z32kclz [ 2 ] ; int32_T dkxpfvhueg [ 2 ] ; int32_T cal15zgc2j
; int32_T aomaqw23kj [ 2 ] ; int32_T a2umzxezhz ; int32_T iufwzza132 ;
int32_T ihsl4yaihz [ 2 ] ; int32_T b2ur50zxxt ; int32_T i30aas21r4 ; int32_T
e4el4xxp3v ; int32_T l2gznv0r5s ; int32_T j2eam25xdq [ 2 ] ; int32_T
ntpky5zyq2 ; int32_T mrah5z4bxd ; int32_T avcjqv3yvo [ 2 ] ; int32_T
k0k5mnrrmr ; int32_T pt4w0x5oly ; int32_T g13tb3xzkh [ 2 ] ; int32_T
lp0as1a4yv ; int32_T h5ovytsf0t [ 2 ] ; int32_T aajipqonk2 ; int32_T
fpjfr1amhz [ 2 ] ; int32_T et5rsn2hy4 ; int32_T baflhjzlry [ 2 ] ; int32_T
beuwjzk2js ; int32_T d4gqmfgseo [ 2 ] ; int32_T hpvgz11ce1 ; int32_T
pkencd32qb [ 2 ] ; int32_T hckdjv2pdj ; int32_T fpbrhfgaer ; int32_T
bfi3hpsbd3 ; int32_T jrqvfa31pb [ 2 ] ; int32_T i03hufrr2p ; int32_T
bljjpdwl2j [ 2 ] ; int32_T jpgks1qgaw ; int32_T emnw2fitbc [ 2 ] ; int32_T
bwcaqrcfm3 ; int32_T mp5kfnnivd ; int32_T fk2i3lc0pr [ 2 ] ; int32_T
lhdj1valxq ; int32_T nytzvsshod [ 2 ] ; int32_T j0vdk0pzxt [ 2 ] ; int32_T
n45w2fovey ; int32_T j2gmx5224s [ 2 ] ; int32_T mg1v5d23v2 [ 2 ] ; int32_T
d3vqmksatz ; int32_T hjxclaa2yg [ 2 ] ; int32_T dfgotgwmje ; int32_T
f13s4kjsla [ 2 ] ; int32_T ob1ut3pxkt ; int32_T hzcybqqwu3 [ 2 ] ; int32_T
nqkgfgueru ; int32_T oegqj0rjkt [ 2 ] ; int32_T kj5znpbtcb ; int32_T
eb1uxhsqqm [ 2 ] ; int32_T i3i5h1aecw ; int32_T l3v4rktkci ; int32_T
okfw4tek12 ; int32_T avvg4m2ph3 [ 2 ] ; int32_T nsnjitjkig [ 2 ] ; int32_T
norrylpua0 [ 2 ] ; int32_T mkophtbsmp [ 2 ] ; int32_T nukgcs3zfx [ 2 ] ;
int32_T kelnhnufbd [ 2 ] ; int32_T dykmoyjonj [ 2 ] ; int32_T hazsc5s2go [ 2
] ; int32_T e3htrycz4b [ 2 ] ; int32_T ezhs2uvh1a ; int32_T h54bictfkj [ 2 ]
; int32_T fzkdhwq4mp ; int32_T mgrzfyi4oa ; int32_T k3ojbdyfkr ; int32_T
atk5pjg2l0 [ 2 ] ; int32_T cdghbdch3h ; int32_T be40hraahf ; int32_T
ejtabalbsl [ 2 ] ; int32_T dd5rdstz0v ; int32_T olvm4q5w1t ; int32_T
kuwvwijrj4 [ 2 ] ; int32_T enqv0axoe1 ; int32_T bsnn5xduey [ 2 ] ; int32_T
kexsmlxyyr [ 2 ] ; int32_T m050u1pkdn [ 2 ] ; int32_T plthkype15 [ 2 ] ;
int32_T lz4jycs0ko ; int32_T agmh5vg5m1 [ 2 ] ; int32_T bqxukhy3el [ 2 ] ;
int32_T olsyxbpls2 [ 2 ] ; int32_T jzsp4ie14h [ 2 ] ; int32_T aa0cqyuvlk [ 2
] ; int32_T n1opq0gvrx ; int32_T g3wgvzncg5 [ 2 ] ; int32_T hqc2ch10k1 ;
int32_T hpqux2phoy [ 2 ] ; int32_T keuj0e4mnl [ 2 ] ; int32_T k3ww5ne5bh ;
int32_T nhfcgtr3ia [ 2 ] ; int32_T as5htnrszu ; int32_T esimoh5jib [ 2 ] ;
int32_T essr5tj3oh [ 2 ] ; int32_T kgwx5qqs42 [ 2 ] ; int32_T canq2xe42o [ 2
] ; int32_T j1vmwiaxnu ; int32_T jx5ls1devh [ 2 ] ; int32_T pzgorkrxhu [ 2 ]
; int32_T ot4swxwqqs [ 2 ] ; int32_T ljulcz111w [ 2 ] ; int32_T nz5ib2ld32 [
2 ] ; int32_T av3a3zcuqj ; int32_T bjqrqmjcjg ; int32_T igcuwgdzd0 ; int32_T
ibxiiyvusn ; int32_T ls2jh3ij1z ; int32_T a2ca2hmpvn [ 2 ] ; int32_T
ix302zziyv [ 2 ] ; int32_T lp0af3stow [ 2 ] ; int32_T mdve0ynzxq [ 2 ] ;
int32_T a250lrvuji [ 2 ] ; int32_T kbi5ewto5r ; int32_T gofs2r35wz [ 2 ] ;
int32_T hnuz1mcnnb ; int32_T ioqvkj4wg5 [ 2 ] ; int32_T jd5otstyr0 ; int32_T
fgj1o5d3wf ; int32_T in0s3j2vbz ; int32_T jbwkqy4lww ; int32_T jr0cm41ns0 ;
int32_T b03ynxq3ci ; int32_T n3yddfnxom ; int32_T hfzal52yqa ; int32_T
bi43xmkbts ; int32_T ngmcidhgrx ; int32_T psmxr0dgvq ; int32_T hic3dy2pg3 ;
int32_T b33plhp5lq ; int32_T emzlcvjqrl ; int32_T b1aaqxmyc5 ; int32_T
ofzaerhr2g ; int32_T k5asw4x2m2 ; int32_T l5pw4zv2f2 ; int32_T cxu2flwqcb ;
uint32_T fbbmy1wbzs ; uint32_T gwrzo0cikl ; uint32_T otbtrf0cu5 ; uint32_T
ly4nq3dl50 ; uint32_T jt2e5dazfs ; uint32_T jqijwj1oky ; uint32_T ofzbjgtz44
; uint32_T jdnm2bpvlc ; uint32_T ox45q3oubn ; uint32_T de1tbsv3lb ; uint32_T
adhvispgo1 ; uint32_T azoan4k1wt ; uint32_T ih0oggj4uc ; uint32_T hztxudeghr
; uint32_T ps1v0o2vkk ; uint32_T er5ddaavly ; uint32_T lknvjor25u ; uint32_T
dv25rhomhd ; uint32_T cmcwr1dobx ; uint32_T nzi13vd4vf ; uint32_T ggcmxpxglp
; uint32_T pmuq1kzurl ; uint32_T h5eygcntpd ; uint32_T gnoyihfwwh ; uint32_T
ewq2jrulsd ; uint32_T kjkwbk0ioe ; uint32_T efr1khdxuf ; uint32_T a4j2q5hqkj
; uint32_T ljmnyp04gz ; uint32_T asvgitun3r ; uint32_T mxitjavfsi ; uint32_T
d0uvuuier1 ; uint32_T cz1xft2bzo ; uint32_T mhrksxb124 ; uint32_T etv2yffban
; uint32_T gsvee1flrc ; uint32_T lohsnxfx2m ; uint32_T ckdjj2ibul ; uint32_T
ab5vzstxle ; int32_T n5zmidyqtv ; int32_T j2xdrhiiyh ; int32_T afqvi4strk ;
int32_T ksgq41r5hd ; int32_T ayhm13jmhk ; int32_T eosyl11ck4 ; int32_T
g5r3plrxzo ; int32_T irgo31r4av ; int32_T obyfghtxdm ; int32_T hwy03ly2qu ;
int32_T eguqvfj45q ; int32_T pmsq4lyxsi ; int32_T c00lh5aati ; uint32_T
pzvmy2vtfc ; uint32_T gv2xz0dvbb ; int32_T krkcguglpr ; int32_T cqtxhvgugx ;
int32_T bsefub12sr ; int32_T hvjzsyvuds ; int32_T bfwwp0fpz5 ; int32_T
gthgbyegoi ; int32_T exlltcu5du ; int32_T eaxrc2oait ; uint32_T db5evvqnl4 ;
int_T aysrl0xgu4 [ 12 ] ; int_T fw3ogbmils ; int_T fr0mgm4ze4 ; uint16_T
ndgvh0rhxn [ 6 ] ; uint16_T cjhn1omf4g ; uint8_T proj4kw2yk ; uint8_T
emlli4rslf ; uint8_T iqtpn4wozh ; boolean_T msqdvb1oe3 [ 12 ] ; boolean_T
pypegkulyo ; boolean_T avj0hig2vi ; boolean_T o2tzopi4yw ; boolean_T
ge3yyfojcr ; boolean_T gvzljplnc3 ; boolean_T gh0enpmvuu ; boolean_T
g3dl0sflej ; boolean_T gz3gsvlted ; boolean_T ifnrxma1iz ; boolean_T
f4jilaq3hc ; boolean_T bwxelwcrfw [ 10 ] ; boolean_T hu0b41lcp1 [ 3 ] ;
boolean_T a1sgqobma2 ; boolean_T gmrae4velq ; boolean_T dfinexqblw ;
boolean_T kxfqpvg5vg ; boolean_T o4b52nmt5t ; boolean_T ajsaohnywt [ 2 ] ;
boolean_T ckvljaf0xe [ 2 ] ; boolean_T dcnfa1hret ; boolean_T nepprh5zjw ;
boolean_T kg01bocea3 ; boolean_T msfoqh5wd4 ; boolean_T aygucjpsfl [ 3 ] ;
boolean_T oiagkzfr4s [ 2 ] ; boolean_T ny41ndogg5 ; boolean_T fefiyesn2c [ 2
] ; boolean_T iut0zctrfu ; boolean_T jorktkth3b [ 2 ] ; boolean_T c4nfafxwn2
[ 2 ] ; boolean_T hslrcq10qm ; boolean_T bzc0votazj [ 2 ] ; boolean_T
j1kvhxhzek ; boolean_T pveht2cmfg [ 2 ] ; boolean_T gtctdgq4yk [ 2 ] ;
boolean_T p5cd5aqqxz ; boolean_T ko3u3tbi04 [ 2 ] ; boolean_T apl3xte3ud ;
boolean_T gzokbkqazo [ 2 ] ; boolean_T fkxyzdoqtm [ 2 ] ; boolean_T
izkkpn4koi [ 6 ] ; boolean_T lqfppykebt ; boolean_T pn554mryvj ; boolean_T
oz2gkeuuat ; boolean_T drm0gtane3 [ 6 ] ; boolean_T jwfcigl1ou [ 12 ] ;
boolean_T mxexirnsfa ; boolean_T kmvjqbtlvc ; boolean_T hamxxmcqkv ;
boolean_T oth1jsetnv ; } DW ; typedef struct { rtwCAPI_ModelMappingInfo mmi ;
} DataMapInfo ; struct P_ { real_T IB ; real_T Ld_over_LB ; real_T Lq_over_LB
; real_T Rs_over_ZB ; real_T Ts_times_ZB_over_Ld ; real_T Ts_times_ZB_over_Lq
; real_T Ts_times_ZB_over_Lx ; real_T Ts_times_ZB_over_Ly ; real_T VB ;
real_T id_ref ; real_T iq_ref ; real_T ix_ref ; real_T iy_ref ; real_T
lambda_d ; real_T lambda_q ; real_T lambda_u ; real_T lambda_x ; real_T
lambda_y ; real_T n_rpm ; real_T omegaB ; real_T omega_m ; real_T p ; real_T
psi_pm_over_psiB ; real_T v_dc ; real_T HDLCounter_CountStep ; real_T
HDLCounter_CountStep_jkdercy3f0 ; int64_T CompareToConstant_const ; uint64_T
CompareToConstant_const_lsb3od3rov ; int16_T
CompareToConstant_const_p3naxlyak2 ; uint16_T
CompareToConstant_const_frsa0cp1w5 ; boolean_T DetectRisePositive_vinit ;
boolean_T DetectRisePositive_vinit_fo4xnhoygk ; boolean_T
DetectRisePositive1_vinit ; boolean_T DetectRisePositive_vinit_f1y4obgego ;
boolean_T DetectRisePositive1_vinit_ivletkhlft ; boolean_T
DetectRisePositive1_vinit_bpoqq0kqip ; boolean_T
DetectRisePositive_vinit_dm4ai0zmth ; boolean_T
DetectRisePositive_vinit_kkghatpupi ; boolean_T
DetectRisePositive_vinit_al1piibe1i ; boolean_T DetectRisePositive2_vinit ;
boolean_T DetectRisePositive_vinit_ib22cc4q3r ; boolean_T
DetectRisePositive1_vinit_gbiji02hsl ; boolean_T DetectRisePositive3_vinit ;
boolean_T DetectRisePositive4_vinit ; real_T Constant30_Value ; real_T
reset_old2_InitialCondition ; real_T Gain19_Gain ; real_T
Delay1_InitialCondition ; real_T Delay2_InitialCondition ; real_T
Constant43_Value ; real_T Constant44_Value ; real_T PulseGenerator2_Amp ;
real_T PulseGenerator2_Period ; real_T PulseGenerator2_Duty ; real_T
PulseGenerator2_PhaseDelay ; real_T Gain2_Gain ; real_T Switch_Threshold ;
real_T RateTransition38_InitialCondition ; real_T
RateTransition_InitialCondition ; real_T RateTransition5_InitialCondition ;
real_T Constant30_Value_prnuyl4z0d ; real_T Gain1_Gain ; real_T
Constant1_Value ; real_T Constant11_Value ; real_T Constant12_Value ; real_T
Constant13_Value ; real_T Constant2_Value ; real_T Constant25_Value ; real_T
Constant45_Value ; real_T Constant46_Value ; real_T Constant47_Value ; real_T
Constant48_Value ; real_T Constant49_Value ; real_T Constant50_Value ; real_T
Constant36_Value ; real_T Constant37_Value ; real_T Constant38_Value ; real_T
Constant39_Value ; real_T Constant40_Value ; real_T Constant41_Value ;
int64_T Switch_wrap_Threshold ; uint64_T Mod_value_Value ; uint64_T
Switch_wrap_Threshold_er4cjhkfze ; uint64_T Mod_value_Value_grlkw0lqhe ;
int32_T Delay14_InitialCondition ; int32_T Delay15_InitialCondition ; int32_T
Delay16_InitialCondition ; int32_T Delay17_InitialCondition ; int32_T
Delay18_InitialCondition ; int32_T Delay19_InitialCondition ; int32_T
Delay20_InitialCondition ; int32_T Delay21_InitialCondition ; int32_T
Delay6_InitialCondition ; int32_T Delay7_InitialCondition ; int32_T
Delay8_InitialCondition ; int32_T Delay9_InitialCondition ; int32_T
Delay22_InitialCondition ; int32_T Delay24_InitialCondition ; int32_T
Delay23_InitialCondition ; int32_T Delay25_InitialCondition ; int32_T
Delay_InitialCondition ; int32_T Delay1_InitialCondition_ly22xqd5qq ; int32_T
Delay4_InitialCondition ; int32_T Delay5_InitialCondition ; int32_T
Delay14_InitialCondition_aykb0m4uaj ; int32_T
Delay15_InitialCondition_lijhdzhcao ; int32_T
Delay16_InitialCondition_ea4j2itlpr ; int32_T
Delay17_InitialCondition_eshmddcula ; int32_T
Delay18_InitialCondition_mvcbk0lpqx ; int32_T
Delay19_InitialCondition_ltjalipc0r ; int32_T
Delay20_InitialCondition_ieha2k4so3 ; int32_T
Delay21_InitialCondition_dnukglu4wl ; int32_T
Delay22_InitialCondition_fiqqx4xn4m ; int32_T
Delay23_InitialCondition_mivupfqcav ; int32_T
Delay24_InitialCondition_hptjdovnd3 ; int32_T
Delay25_InitialCondition_jp1hnwtuv1 ; int32_T Delay3_InitialCondition ;
int32_T Delay4_InitialCondition_j0mtraynb2 ; int32_T
Delay20_InitialCondition_mbo0wh3jll ; int32_T
Delay21_InitialCondition_ptwc2dagcm ; int32_T
Delay15_InitialCondition_mfiibw15yv ; int32_T Delay11_InitialCondition ;
int32_T Delay12_InitialCondition ; int32_T Delay2_InitialCondition_fsrhxdibbo
; int32_T Delay6_InitialCondition_j5vpi3mg4q ; int32_T
sfix18_En15maxvalue_Value ; int32_T Delay10_InitialCondition ; int32_T
Delay1_InitialCondition_dat0r241xb ; int32_T Delay27_InitialCondition ;
int32_T Delay28_InitialCondition ; int32_T
Delay20_InitialCondition_aectgnkorn ; int32_T
Delay21_InitialCondition_mklmlykc1g ; int32_T
Delay22_InitialCondition_pybkr3xzaa ; int32_T Delay29_InitialCondition ;
int32_T Delay30_InitialCondition ; int32_T
Delay24_InitialCondition_gf5unztfp3 ; int32_T Delay31_InitialCondition ;
int32_T Delay32_InitialCondition ; int32_T Delay42_InitialCondition ; int32_T
Delay33_InitialCondition ; int32_T Delay34_InitialCondition ; int32_T
Delay12_InitialCondition_dhy1cxosgt ; int32_T Delay13_InitialCondition ;
int32_T Delay25_InitialCondition_ld1wgcfanj ; int32_T
Delay26_InitialCondition ; int32_T Delay35_InitialCondition ; int32_T
Delay36_InitialCondition ; int32_T Delay37_InitialCondition ; int32_T
Delay38_InitialCondition ; int32_T Delay39_InitialCondition ; int32_T
Delay40_InitialCondition ; int32_T Delay45_InitialCondition ; int32_T
Delay47_InitialCondition ; int32_T Delay10_InitialCondition_l0q4djyeoi ;
int32_T Delay1_InitialCondition_igcycvhe02 ; int32_T
Delay27_InitialCondition_m4iln3awwi ; int32_T
Delay28_InitialCondition_cb32osnq0d ; int32_T
Delay20_InitialCondition_o35q2txese ; int32_T
Delay21_InitialCondition_glizedcvzk ; int32_T
Delay22_InitialCondition_oo0fxo4ts3 ; int32_T
Delay29_InitialCondition_mm0khohit1 ; int32_T
Delay30_InitialCondition_ggwlqp3ayv ; int32_T
Delay24_InitialCondition_mohdww4zbp ; int32_T
Delay31_InitialCondition_ekfi3stwf2 ; int32_T
Delay32_InitialCondition_cs5kutlccj ; int32_T
Delay42_InitialCondition_gru3zset4s ; int32_T
Delay33_InitialCondition_ppr11dhhgn ; int32_T
Delay34_InitialCondition_dpua2hw2gm ; int32_T
Delay12_InitialCondition_ouc2nmxdsk ; int32_T
Delay13_InitialCondition_kimcfr4gze ; int32_T
Delay25_InitialCondition_gsczwe1i1u ; int32_T
Delay26_InitialCondition_mgka52oerp ; int32_T
Delay35_InitialCondition_dysk2sqtpr ; int32_T
Delay36_InitialCondition_nmclzfgmgt ; int32_T
Delay37_InitialCondition_pvv3oz1agd ; int32_T
Delay38_InitialCondition_hyqujaeun2 ; int32_T
Delay39_InitialCondition_mceniyldyc ; int32_T
Delay40_InitialCondition_ehtobfeh4e ; int32_T
Delay45_InitialCondition_ncb3hew20x ; int32_T
Delay47_InitialCondition_pbr1n1noet ; int32_T Delay56_InitialCondition ;
int32_T Delay9_InitialCondition_prno1bxsxa ; int32_T
Delay_InitialCondition_dnv0ifrubu ; int32_T
Delay1_InitialCondition_c52q2mr0yt ; int32_T
Delay10_InitialCondition_g0wldcu40f ; int32_T
Delay11_InitialCondition_o15pinrfzn ; int32_T
Delay12_InitialCondition_ck3j1elvfp ; int32_T
Delay2_InitialCondition_euoswkcs5n ; int32_T
Delay3_InitialCondition_pi0tmw14b4 ; int32_T
Delay4_InitialCondition_jeioq1ufui ; int32_T
Delay5_InitialCondition_emgr2bsszy ; int32_T
Delay7_InitialCondition_gh5vhp5qht ; int32_T
Delay8_InitialCondition_pmfdfw522x ; int32_T
Delay9_InitialCondition_cyyr0jpkpb ; int32_T
RateTransition35_InitialCondition ; int32_T RateTransition32_InitialCondition
; int32_T RateTransition33_InitialCondition ; int32_T
RateTransition34_InitialCondition ; int32_T RateTransition36_InitialCondition
; int32_T RateTransition37_InitialCondition ; int32_T
RateTransition23_InitialCondition ; int32_T RateTransition43_InitialCondition
; int32_T Delay10_InitialCondition_izlyzkvwk0 ; int32_T
Delay11_InitialCondition_gmmvu1fbcm ; int32_T
Delay2_InitialCondition_p3vzpccrzz ; int32_T
Delay3_InitialCondition_cdk4mpryb2 ; int32_T
Delay17_InitialCondition_kt3xokvvuu ; int32_T
Delay16_InitialCondition_b4fkcf5yn4 ; int32_T
Delay14_InitialCondition_bylgo2mpoi ; int32_T
Delay18_InitialCondition_eqkpnac3um ; int32_T
Delay19_InitialCondition_fkv3s3dp5d ; int32_T Gain_Gain ; int32_T
Delay46_InitialCondition ; int32_T Delay48_InitialCondition ; int32_T
Delay46_InitialCondition_c3h254v0m5 ; int32_T
Delay48_InitialCondition_p4le5tsnjt ; int32_T
Delay10_InitialCondition_iotuu4egg5 ; int32_T
Delay7_InitialCondition_pn01ygnqgy ; int32_T
Delay8_InitialCondition_owtbs5ubep ; int32_T
Delay9_InitialCondition_o4ddfnrtdp ; int32_T
Delay5_InitialCondition_earayqbybk ; int32_T
Delay6_InitialCondition_kamhzwpi4u ; int32_T
Delay2_InitialCondition_lcgjnepw1h ; int32_T
Delay3_InitialCondition_pugikzolzj ; int32_T
Delay7_InitialCondition_cmnkpdmjvh ; int32_T
Delay8_InitialCondition_a21yi54nej ; int32_T
Delay9_InitialCondition_i5y5manjyq ; int32_T
Delay10_InitialCondition_fncm3u0aqk ; int32_T
Delay36_InitialCondition_pw5b5tbf3k ; int32_T
Delay39_InitialCondition_pla21bbxiw ; int32_T
Delay40_InitialCondition_muusj1w2jz ; int32_T Delay41_InitialCondition ;
int32_T Delay2_InitialCondition_mnfmscojm5 ; int32_T
Delay3_InitialCondition_h5j03igjqv ; int32_T Delay59_InitialCondition ;
int32_T Delay57_InitialCondition ; int32_T
Delay14_InitialCondition_bati1r4y0o ; int32_T
Delay18_InitialCondition_jntt4dfp5k ; int32_T
Delay19_InitialCondition_mrc5koktnp ; int32_T
Delay4_InitialCondition_chzqhro0zz ; int32_T
Delay5_InitialCondition_o3nqpbca5j ; int32_T
Delay23_InitialCondition_nqh0wedxsh ; int32_T
Delay41_InitialCondition_ky0pjf1mvz ; int32_T
Delay15_InitialCondition_noxola40gw ; int32_T
Delay16_InitialCondition_il3shhgxsb ; int32_T
Delay17_InitialCondition_p4m3kzesyj ; int32_T Delay51_InitialCondition ;
int32_T Delay52_InitialCondition ; int32_T Delay53_InitialCondition ; int32_T
Delay54_InitialCondition ; int32_T Delay58_InitialCondition ; int32_T
Delay60_InitialCondition ; int32_T Delay62_InitialCondition ; int32_T
Delay63_InitialCondition ; int32_T Delay64_InitialCondition ; int32_T
Delay65_InitialCondition ; int32_T Delay70_InitialCondition ; int32_T
Delay71_InitialCondition ; int32_T Delay72_InitialCondition ; int32_T
Delay73_InitialCondition ; int32_T Delay2_InitialCondition_h1aqdsgg2a ;
int32_T Delay3_InitialCondition_ezgpfjbzr1 ; int32_T
Delay59_InitialCondition_bxg5ajl2cg ; int32_T
Delay57_InitialCondition_d0pinoubfq ; int32_T
Delay18_InitialCondition_pngf4p1bou ; int32_T
Delay19_InitialCondition_indohfis2p ; int32_T
Delay4_InitialCondition_mshy1btqrq ; int32_T
Delay5_InitialCondition_lbpw0wn4yz ; int32_T
Delay23_InitialCondition_puaz0elee4 ; int32_T
Delay6_InitialCondition_i4uwjjxy40 ; int32_T
Delay7_InitialCondition_duzxicgcbl ; int32_T
Delay41_InitialCondition_e2e5nal5lm ; int32_T
Delay8_InitialCondition_dwwg2yfgol ; int32_T
Delay9_InitialCondition_nrucrycygo ; int32_T
Delay14_InitialCondition_jf44sqesxi ; int32_T
Delay15_InitialCondition_lb41cd340o ; int32_T
Delay16_InitialCondition_kxh1ifbnkm ; int32_T
Delay17_InitialCondition_lnkr0kpdkt ; int32_T
Delay58_InitialCondition_fqi0cwobbv ; int32_T
Delay60_InitialCondition_pxiemqggyu ; int32_T
Delay62_InitialCondition_p1wk5q0cdt ; int32_T
Delay63_InitialCondition_beo3flwsuv ; int32_T
Delay64_InitialCondition_ka3tfhhj1f ; int32_T
Delay65_InitialCondition_bmbct3hq2d ; int32_T
Delay70_InitialCondition_p0mpocu54t ; int32_T
Delay71_InitialCondition_cf3uyr12b4 ; int32_T
Delay72_InitialCondition_fhvujjzjmp ; int32_T
Delay73_InitialCondition_obxslsutcn ; int32_T
Delay17_InitialCondition_nxouw4fmzy ; int32_T
Delay18_InitialCondition_bxgh5q1rnv ; int32_T
Delay19_InitialCondition_dskcubxram ; int32_T
Delay20_InitialCondition_a3mgvgzkkd ; int32_T
Delay4_InitialCondition_fb1eurtbw1 ; int32_T
Delay5_InitialCondition_nuntj3gqhg ; int32_T
Delay6_InitialCondition_ajvsfi0dp2 ; int32_T
Delay7_InitialCondition_coynyzjcg4 ; int32_T
Delay46_InitialCondition_hp1tgavvdq ; int32_T
Delay47_InitialCondition_ij0jcy2nr2 ; int32_T
Delay48_InitialCondition_f1f5dsuuw2 ; int32_T Delay49_InitialCondition ;
uint32_T LookUpTable_tableData [ 256 ] ; uint32_T
LookUpTable_tableData_l4xsx4sjok [ 256 ] ; uint32_T
Delay11_InitialCondition_aefe120qnx ; uint32_T
Delay12_InitialCondition_iyuzeo4mp3 ; uint32_T
Delay51_InitialCondition_myx3xoza4z ; uint32_T
Delay25_InitialCondition_f02epsp2gx ; uint32_T
Delay26_InitialCondition_io0pemxg3l ; uint32_T
Delay27_InitialCondition_eimdrnj4fl ; uint32_T
Delay28_InitialCondition_px5icuhcg5 ; uint32_T
Delay29_InitialCondition_glmi4lltd2 ; uint32_T
Delay30_InitialCondition_ofnmyt0tby ; uint32_T
Delay31_InitialCondition_pmkvgjaz2l ; uint32_T
Delay32_InitialCondition_f5wtxt21ad ; uint32_T
Delay33_InitialCondition_oi2vbhmnab ; uint32_T
Delay34_InitialCondition_bhvxb4sani ; uint32_T
Delay64_InitialCondition_miacangvo0 ; uint32_T
Delay65_InitialCondition_kjdhdv3njw ; uint32_T Delay66_InitialCondition ;
uint32_T Delay67_InitialCondition ; uint32_T Delay68_InitialCondition ;
uint32_T Point25_Value ; uint32_T Point75_Value ; uint32_T Point50_Value ;
uint32_T Point50_Value_bq4x5ihc1z ; uint32_T Point25_Value_ae3byy1qfp ;
uint32_T delay_InitialCondition ; uint32_T
Delay53_InitialCondition_ejnujgvjuc ; uint32_T
Delay54_InitialCondition_gsztafuagp ; uint32_T Delay55_InitialCondition ;
uint32_T Delay56_InitialCondition_bt1dah4zxx ; uint32_T
Delay42_InitialCondition_moexjyifg4 ; uint32_T Delay43_InitialCondition ;
uint32_T Delay44_InitialCondition ; uint32_T
Delay45_InitialCondition_aaata0dpq2 ; uint32_T
Delay52_InitialCondition_hccf1x1wju ; uint32_T
Delay59_InitialCondition_aefql4ojpq ; uint32_T
Delay60_InitialCondition_mlmhnwovs5 ; uint32_T Delay61_InitialCondition ;
uint32_T Delay62_InitialCondition_guxfhxoq5j ; uint32_T
Delay69_InitialCondition ; uint32_T Delay70_InitialCondition_fvi5gvi3z2 ;
uint32_T Delay71_InitialCondition_dp0cjzqycn ; uint32_T
Delay72_InitialCondition_exjymra1sd ; uint32_T
Delay57_InitialCondition_l0nrhq2swb ; uint32_T
Delay35_InitialCondition_g0vgtma3kl ; uint32_T Delay94_InitialCondition ;
uint32_T Delay50_InitialCondition ; uint32_T
Delay73_InitialCondition_cbbkdwlw5h ; uint32_T
Delay23_InitialCondition_op2l2kezcw ; uint32_T
Delay24_InitialCondition_p14sgx14xm ; uint32_T
Delay4_InitialCondition_bnp5uh2nbr ; uint32_T
Delay43_InitialCondition_h2okxsmbyb ; uint32_T
Delay44_InitialCondition_hnfu4d5knp ; uint32_T
Delay43_InitialCondition_fk3jz0t30i ; uint32_T
Delay44_InitialCondition_otecsnu01f ; uint32_T
Delay12_InitialCondition_gmkk1why2d ; uint32_T
Delay8_InitialCondition_h4ihxe4npk ; uint32_T
Delay15_InitialCondition_nk02qrs4ya ; uint32_T
Delay16_InitialCondition_mr40dl0mot ; uint32_T
Delay13_InitialCondition_m0jqhjefa3 ; uint32_T
Delay14_InitialCondition_iptsnmiqcc ; uint32_T Switch_Threshold_lbu3enyq0g ;
uint32_T Count_reg_InitialCondition ; uint32_T Constant1_Value_ehsaxh0cmq ;
uint32_T Switch1_Threshold ; uint32_T Delay7_InitialCondition_dqlbrwosli ;
uint32_T Delay8_InitialCondition_hbbfrekxgi ; uint32_T
Delay5_InitialCondition_iro1ml0o4b ; uint32_T
Delay6_InitialCondition_c31jqcw5pd ; uint32_T Constant1_Value_ialq4qchdp ;
uint32_T Switch1_Threshold_cmgitpnmj4 ; uint32_T Constant1_Value_az5chewn2m ;
uint32_T Switch1_Threshold_bszl3a5ngz ; uint32_T Constant_Value ; uint32_T
Step_value_Value ; uint32_T Constant_Value_lwusvgbjut ; uint32_T
const_load_val_Value ; uint32_T From_value_Value ; uint32_T Init_value_Value
; uint32_T Constant1_Value_ej4utqpdhu ; uint32_T Switch1_Threshold_bsiyvpmeeg
; int16_T Switch_wrap_Threshold_izyhb3bebo ; uint16_T Saturation_UpperSat ;
uint16_T Saturation_LowerSat ; uint16_T LookUpTable_bpFirstPoint01Data ;
uint16_T LookUpTable_bpSpace01Data ; uint16_T Saturation_UpperSat_h5014v3u1p
; uint16_T Saturation_LowerSat_otvbogra21 ; uint16_T
LookUpTable_bpFirstPoint01Data_bm0k1ty0wi ; uint16_T
LookUpTable_bpSpace01Data_jpds1epk12 ; uint16_T Mod_value_Value_l21scu10m2 ;
uint16_T Switch_wrap_Threshold_nhu5pffepr ; uint16_T
Mod_value_Value_pbng05kqkk ; uint16_T Delay58_InitialCondition_luxfkrhdi3 ;
uint16_T Delay63_InitialCondition_e4x3dh2sou ; boolean_T
Constant_Value_jjvoona122 ; boolean_T Delay37_InitialCondition_o4l3n4g21g ;
boolean_T Delay_InitialCondition_ayrfgyd5vh ; boolean_T
Delay1_InitialCondition_acststv1xc ; boolean_T
Delay38_InitialCondition_fjlfddcmxf ; boolean_T Constant_Value_nwkotzyoei ;
boolean_T Constant_Value_fxz04fjufv ; boolean_T
Delay_InitialCondition_eem2mixovl ; boolean_T
Delay50_InitialCondition_mfmxuzil5a ; boolean_T
Delay11_InitialCondition_ehofyfh5ho ; boolean_T
Delay49_InitialCondition_mzyf012msw ; boolean_T Constant_Value_p2ftaoinvh ;
boolean_T Constant_Value_hdyf3gawar ; boolean_T
Delay_InitialCondition_mguhinw1z3 ; boolean_T
Delay50_InitialCondition_f4xnk4oved ; boolean_T
Delay11_InitialCondition_dpsigb2nh3 ; boolean_T Constant_Value_dmcqaaps25 ;
boolean_T Constant_Value_pm1sdpisrb ; boolean_T
Delay21_InitialCondition_apznhxher1 ; boolean_T
Delay_InitialCondition_f5wa0qe2ex ; boolean_T
Delay1_InitialCondition_kwcvbd3x3q ; boolean_T Constant_Value_orbhgrq4vm ;
boolean_T Delay3_InitialCondition_ezcydfdbof ; boolean_T
Delay13_InitialCondition_etk5iarzoa ; boolean_T
Delay26_InitialCondition_pllnymf2r1 ; boolean_T pow2switch_Value ; boolean_T
pow2switch_Value_pcaa04qou3 ; boolean_T RAMDelayBalance_InitialCondition ;
boolean_T Constant_Value_aifiy50g10 ; boolean_T
Delay13_InitialCondition_chiigtws5y ; boolean_T
Delay6_InitialCondition_ombiorxymx ; boolean_T Constant_Value_fe2tuwwksa ;
boolean_T Constant_Value_kquk2qjynt ; boolean_T Constant_Value_lspkkwit3o ;
boolean_T Constant_Value_pjgiu3aaeo ; boolean_T Constant_Value_aeu2zpibv2 ;
boolean_T SS_Old_InitialCondition ; boolean_T
Delay21_InitialCondition_pzx2rrfnsh ; boolean_T
Delay_InitialCondition_arimfvovwm ; boolean_T UnitDelay_InitialCondition ;
boolean_T Delay3_InitialCondition_kt0ior3g52 ; boolean_T
Delay4_InitialCondition_ehuroqp43u ; boolean_T
UnitDelay_InitialCondition_lapzeesnb2 ; boolean_T
UnitDelay_InitialCondition_h2pwusbzsi ; boolean_T
Delay_InitialCondition_mgy5b5rjgy ; boolean_T const_dir_Value ; boolean_T
Free_running_or_modulo_Value ; boolean_T const_load_Value ; boolean_T
const_rst_Value ; boolean_T RateTransition10_InitialCondition ; boolean_T
Delay9_InitialCondition_ff0n2wb02d ; boolean_T
Delay1_InitialCondition_dpy3sexlsr ; boolean_T
Delay2_InitialCondition_mqwne0yfzv ; boolean_T const_dir_Value_i0caynohtg ;
boolean_T Free_running_or_modulo_Value_la3s00hfhs ; boolean_T
const_load_Value_anfy5khxl2 ; boolean_T UnitDelay_InitialCondition_mm1y0ejde0
; uint8_T Saturation_UpperSat_nhlfqmn4x4 ; uint8_T
Saturation_LowerSat_cyyxxqbhoa ; uint8_T
RAMDelayBalance_InitialCondition_bi3be0mmud ; uint8_T
Delay4_InitialCondition_fmraqiik34 ; uint8_T Constant1_Value_oayr5juvkv ;
uint8_T Constant6_Value ; uint8_T Constant5_Value ; uint8_T Constant3_Value ;
uint8_T Constant4_Value ; uint8_T Step_value_Value_bryryaclem ; uint8_T
Count_reg_InitialCondition_asueyru4ot ; uint8_T Constant_Value_krezwpdugr ;
uint8_T const_load_val_Value_b0tcqrjnzj ; uint8_T From_value_Value_mqtm0fsuxq
; uint8_T Init_value_Value_dhwjsos3in ; uint8_T
Delay4_InitialCondition_ftztsa1ilo ; uint8_T Constant6_Value_gdnteqbjb4 ;
uint8_T Constant5_Value_fqzhn0hxkr ; uint8_T Constant3_Value_ivo13icu2r ; } ;
extern const char * RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern DW
rtDW ; extern P rtP ; extern mxArray * mr_external_state_machine_GetDWork ( )
; extern void mr_external_state_machine_SetDWork ( const mxArray * ssDW ) ;
extern mxArray * mr_external_state_machine_GetSimStateDisallowedBlocks ( ) ;
extern const rtwCAPI_ModelMappingStaticInfo *
external_state_machine_GetCAPIStaticMap ( void ) ; extern SimStruct * const
rtS ; extern const int_T gblNumToFiles ; extern const int_T gblNumFrFiles ;
extern const int_T gblNumFrWksBlocks ; extern rtInportTUtable *
gblInportTUtables ; extern const char * gblInportFileName ; extern const
int_T gblNumRootInportBlks ; extern const int_T gblNumModelInputs ; extern
const int_T gblInportDataTypeIdx [ ] ; extern const int_T gblInportDims [ ] ;
extern const int_T gblInportComplex [ ] ; extern const int_T
gblInportInterpoFlag [ ] ; extern const int_T gblInportContinuous [ ] ;
extern const int_T gblParameterTuningTid ; extern DataMapInfo *
rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr ;
void MdlOutputs ( int_T tid ) ; void MdlOutputsParameterSampleTime ( int_T
tid ) ; void MdlUpdate ( int_T tid ) ; void MdlTerminate ( void ) ; void
MdlInitializeSizes ( void ) ; void MdlInitializeSampleTimes ( void ) ;
SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) ;
#endif
