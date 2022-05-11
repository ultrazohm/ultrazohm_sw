#ifndef RTW_HEADER_uz_drive_model_h_
#define RTW_HEADER_uz_drive_model_h_
#include <stddef.h>
#include <string.h>
#include "rtw_modelmap_simtarget.h"
#ifndef uz_drive_model_COMMON_INCLUDES_
#define uz_drive_model_COMMON_INCLUDES_
#include <stdlib.h>
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "rtwtypes.h"
#include "zero_crossing_types.h"
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
#endif
#include "uz_drive_model_types.h"
#include "multiword_types.h"
#include "rt_zcfcn.h"
#include "mwmathutil.h"
#include "rt_defines.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#define MODEL_NAME uz_drive_model
#define NSAMPLE_TIMES (7) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (486) 
#define NUM_ZC_EVENTS (3) 
#ifndef NCSTATES
#define NCSTATES (2)   
#elif NCSTATES != 2
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
typedef struct { real_T mua04mpyc1 ; real_T ffroit3bl4 ; real_T hqezd5t15w [
3 ] ; real_T d1n40oandv [ 3 ] ; boolean_T a4vwthkenj ; } cz235gejcz ; typedef
struct { real_T ltyokv5jui ; uint32_T dmqhv1kuog ; uint32_T grzcmycdpb ;
int_T hlqhpqgl5d ; int8_T dqmv313jji ; boolean_T jaldgiolnb ; } gqx2bugedg ;
typedef struct { ZCSigState cowinqfkuy ; } nrs5bzunb3 ; typedef struct {
real_T getzpyfpzt ; real_T gexcbgcs0i ; real_T da1hylhljz ; real_T hhdeynni3k
; real_T hx1dswidvn ; real_T ann0jcq1uk ; real_T l5rfzkfj5k ; } cog2itxiqj ;
typedef struct { real_T ftf50xwldj ; uint32_T ic4jzsnsgd ; uint32_T
j5itaoriq1 ; uint32_T bjona3wx3v ; uint32_T bldvjsjmit ; uint32_T opg33homib
; uint32_T n4jsnmm3dp ; int8_T bnbpcxxvih ; boolean_T e4ertwjipw ; }
dqnc2mdlgm ; typedef struct { boolean_T gwunl2xrbh [ 12 ] ; } kavyiqnma5 ;
typedef struct { uint8_T f3ngbvxvpa ; } c43be0leba ; typedef struct { int64_T
kehk5h5kaa ; int64_T jvi14dsw1h [ 9 ] ; int32_T gts4dkakcf [ 9 ] ; int32_T
pejblvhpwh [ 9 ] ; } ch3csirfgx ; typedef struct { int64_T bineo4prgi [ 8 ] ;
int8_T bvutux0ucw ; } f5d5p32bfp ; typedef struct { real_T cqr5wxn5sb ;
real_T d2xswmz51j ; real_T ejyqailfrk ; real_T mrvvmxjbsp ; real_T ghi2pz21ut
; real_T k0tjdml5mw ; real_T ei1bavxqil ; real_T agqqnkjpc4 [ 9 ] ; real_T
flx3sokx1j [ 6 ] ; real_T i2luwb2xg3 ; real_T iztliysr2c [ 3 ] ; real_T
dcyymdlgr3 [ 3 ] ; real_T gjirmvlhql [ 3 ] ; real_T forvj4qm2y ; real_T
k2ndgrxbvv ; real_T gqp4loxl10 ; real_T cqqwj4hgbc ; real_T jmtjax2f4t ;
real_T bohcvczirh ; real_T i3srfw2hbe ; real_T nwpl41ljbn ; real_T g4t0xlro5r
; real_T lxu2tizwog ; real_T imc322aww5 ; real_T amb4v03txh ; real_T
nahffw1fqn ; real_T pgp2ddnfdk ; real_T lup5lr2jvb ; real_T jnpfxzq53a ;
real_T jqoi3hd2f5 ; real_T olgy0iynok ; real_T eztey41xwv ; real_T lkk5omnvvt
; real_T fevhynkzve ; real_T k2u5abxvdm ; real_T fmww04dhk3 ; real_T
lsypufcvtj ; real_T crebamanmt ; real_T ac1d3qgxbp ; real_T dxuigsm1g2 ;
real_T dzx3p1gp32 ; real_T g1mrrh2azp ; real_T bft2jjoec5 ; real_T cmhi33mwre
; real_T jml1bsjxtz ; real_T mkhgcxbdbc ; real_T mmaiq4q51j ; real_T
ejp2ouo0yj ; real_T dxm0qgspl5 ; real_T j4ghcw5gtk ; real_T n3tpootby4 ;
real_T nyfnpu0nol ; real_T b4ty1phbhk ; real_T p0dldf2akj ; real_T ncbythljam
; real_T ab2h2zhgij ; real_T gztw3fbv31 ; real_T hwcg2de5ln ; real_T
cw25rqhbhe ; real_T bohbdh5pos ; real_T mg4hzao3ac ; real_T k3devdomyi ;
real_T l2ecs4m1wq ; real_T lphdmpzics ; real_T bg5sagtx2f ; real_T o42245qd4a
; real_T lofmmfuim4 ; real_T cajcokate4 ; real_T mxgu50ynet ; real_T
m4ynyxpbu2 ; real_T ik02utyxan ; real_T lie0qvypkt ; real_T ghwcctc4hl ;
real_T pzyy3abz13 ; real_T jjunnmldtx ; real_T ewkvxp0tx3 ; real_T pxpefqknkg
; real_T pmnldr5rgz ; real_T jorthzrtqn ; real_T kkydc41wz4 ; real_T
pls0pucbim ; real_T c4jaly0gxz ; real_T kmjcmuq4sa ; real_T j4shds0cgp ;
real_T crlo0ykadd ; real_T a3nmhcj3ac ; real_T ekqsqfqm5z ; real_T nvrrli0mdp
; real_T k2epoclkhf ; real_T o3isut3xe2 ; real_T frhtoi20is ; real_T
pdwhfw3xoj ; real_T h2h3aoif55 ; real_T atculhoes1 ; real_T ba4ycbfbms ;
real_T d5bxbfmv3h ; real_T jmg21szmcd ; real_T nvio0y23qb ; real_T o5rpzk02ux
; real_T o44jebcpbs ; real_T fhua05yaow ; real_T ekqxh0o2yy ; real_T
pro0t00oqz [ 6 ] ; real_T cf5pwifjmr [ 6 ] ; real_T kwpowwsiez [ 3 ] ; real_T
jpqnsdsvax ; real_T a4skgo2zdk ; real_T a3hcsd5djm ; real_T aqrztu4oci ;
real_T ftks2e35i3 ; real_T klaa1rzh3f ; real_T kvtifit3ew ; real_T ilatryxyc3
[ 6 ] ; real_T a3lvlw3afz ; real_T pro0t00oqzl [ 6 ] ; real_T dkskqk5nay [ 6
] ; real_T kdtkapks5q [ 3 ] ; real_T mj20pqbu5g ; real_T a4skgo2zdk4 ; real_T
oed0sm4hyv ; real_T aqrztu4ocia ; real_T aspz402pif ; real_T klaa1rzh3fa ;
real_T f1keoylfm3 ; real_T lvxw1arzhe [ 6 ] ; real_T a1el3w34yn ; real_T
pro0t00oqzlp [ 6 ] ; real_T atklik5qqa [ 6 ] ; real_T nimpzzl3rt [ 3 ] ;
real_T oi0f1dpmvz ; real_T a4skgo2zdk4r ; real_T o1jq12suxm ; real_T
aqrztu4ociaz ; real_T ile2cuirmz ; real_T klaa1rzh3fay ; real_T aotbj02q5j ;
real_T arkmcvldut [ 6 ] ; real_T fsoxlkgk5l ; real_T js3yk5ooqs ; real_T
b2ae2knt0i ; real_T pnc3vys3n0 ; real_T mxbllj53re ; real_T pmyyd40jng ;
real_T muhro1pthm ; real_T hfsnjuqzrn ; real_T kt0x35emh1 ; real32_T
ozrwjzfnca ; real32_T hv5ezjmgeo ; real32_T fqxsmb4jyk ; real32_T nftvdrrocl
; real32_T pqtimdb5j0 ; real32_T bmvpiaropc ; real32_T msybf1i1ih ; real32_T
ctfswtdkgy ; real32_T famzz0eg5w ; real32_T lt1czm1uxp ; real32_T o4hoccuzjr
; real32_T bnaxt4mwdx ; real32_T du0uth4oge ; real32_T iuri1z2qfy ; real32_T
cgssfsafy3 ; real32_T bfmnddev3o ; real32_T fwt504l0fp ; real32_T dmg5kd4tx3
; real32_T ezj0gynpe2 ; real32_T c5qcb5u3xz ; real32_T n01lcmfhax ; real32_T
ill1vghh4b ; real32_T g5udhujwag ; real32_T op5yeerppz ; real32_T kh313ui5yr
; real32_T hvql1wzp1l ; real32_T ibyskbyf12 ; real32_T fxv4zcsfc1 ; real32_T
bvmuyedlcu ; real32_T klks1betwn ; real32_T apfmql0sei ; real32_T axfg3xmtsw
; real32_T haranx30a5 [ 4 ] ; real32_T ardjnl10dt ; real32_T jf1dkqak4i ;
real32_T lvqyun4ml4 ; real32_T mr5jvkeea4 ; real32_T glnkapw4oj ; real32_T
fclle0plbx ; real32_T nlrhqopjdv ; real32_T bqib1cp1cj ; real32_T oj1n41111k
; real32_T gxiz1fefsk ; real32_T ozq3nsiak4 ; real32_T fxar2syvnw ; real32_T
igl4agsvph ; real32_T kkpufmifuj ; real32_T lx40xm1u3s ; real32_T fyoaaccrru
; real32_T a00j4is05h ; real32_T a1lifabcqz ; real32_T oq4k1jl1j1 ; real32_T
lzb32orqgb ; real32_T fme5wp01hh ; real32_T ialnb1yw5e ; real32_T cqo5mybcym
; real32_T fwwwwnm0xy ; real32_T iskolztlai ; real32_T odetrknlzz ; real32_T
murauiwsvw ; real32_T lugsvs2nsp ; real32_T gydjzs1bdb ; real32_T im5yymuath
; real32_T bs3jd3qjqw ; real32_T iiqlz25ibz ; real32_T m3i5omzuvm ; real32_T
opdam4elco ; real32_T bpvldt4nml ; real32_T b5q02ypjjz ; real32_T bzop13ab3h
; real32_T ohmrbovmfa ; real32_T jc2xb5555z ; real32_T ku3t5edtlg ; real32_T
eqti4hemyn ; real32_T n4gmeaqzp4 ; real32_T gti1gti2ss ; real32_T f00exjvhy5
; real32_T ijrdbn05so ; real32_T mk1wynbhp2 ; real32_T gjoeyfmk32 ; real32_T
e4wgz1h5dw ; real32_T cssbez0qdp ; real32_T krcsx2cqzw ; real32_T krzkvwtyr5
; real32_T lkfyl1qpfg ; real32_T drcj52wpue ; real32_T mfqi5bmnfc [ 9 ] ;
real32_T n01cwk51y2 ; real32_T p3g0p13atl ; real32_T jgteqxearg [ 9 ] ;
real32_T fonmaxluk5 ; real32_T ly2e1zoduv ; real32_T hz5f5wlyee ; real32_T
mel3kf0new ; real32_T htuhckhws0 ; real32_T e5k1nos5fp ; real32_T ggxspydiyp
; real32_T ntn5swsdwf ; real32_T bgjebmhgfv ; real32_T j4uzb05eqs ; real32_T
loraops0qq ; real32_T cxh2bze2aw ; real32_T m4jtd010un ; real32_T klvorwbawb
; real32_T oafknyqwix ; real32_T iuqrgdsyyu ; real32_T kffkzglrlg ; real32_T
fmeg1ss5bt ; real32_T oirs5ucrzg ; real32_T g5f1cmb3g1 ; real32_T lme3ejskfc
; real32_T en2i3j4iug ; real32_T dwjldlpqwz ; real32_T avfxnnnygf ; real32_T
bqjbue4zrx ; real32_T axkfxspns0 ; real32_T ntfnjg0jqj [ 9 ] ; real32_T
jiuomirfvx [ 12 ] ; real32_T gxf5v3fekk ; real32_T ljvsb0m4tf ; real32_T
hcl2mherxb ; real32_T jqrr1set1f ; real32_T klznlbui1b ; real32_T lk3th3p1al
; real32_T kqqvdbnzy3 ; real32_T i5uxa5wsug ; real32_T amtihtn1an [ 8 ] ;
real32_T b5hsoldwxb [ 12 ] ; real32_T brenn0ae3u [ 12 ] ; real32_T ifeyoqsf33
; real32_T kcblg0vlib ; real32_T otf010jouj ; real32_T i5wwklu4fv ; real32_T
i5kvikzb3h ; real32_T evlbtuq3cx ; real32_T in3lhsbtco ; real32_T fsedjavxts
; real32_T asxknbd3q5 [ 8 ] ; real32_T fld2qyvslw [ 12 ] ; real32_T
jryifpteuq [ 12 ] ; real32_T emtc4xb3jh ; real32_T a0cgfepyxf ; real32_T
dakqt0dgf2 ; real32_T ctjk3zl0rw ; real32_T jqmsjhg33r ; real32_T j10c3it1oh
; real32_T nxi2wmkwov ; real32_T ib5sxshjan ; real32_T eprprovalw [ 8 ] ;
real32_T dl4p452e1n [ 12 ] ; int32_T kqxgd32mvf ; int32_T p1wjqkompn [ 3 ] ;
int32_T bc4jkovamz [ 3 ] ; int32_T ct50xdrbpe [ 3 ] ; int32_T ljbz13eall ;
int32_T bi5qzktbi4 ; int32_T faduibn1mq [ 9 ] ; int32_T ld0qtnhxv2 ; int32_T
ghazr1rloj [ 3 ] ; int32_T kxltf1cq42 [ 3 ] ; int32_T coti0iqh4j [ 3 ] ;
int32_T njb5q03jbz [ 3 ] ; int32_T piz1xhutnj [ 3 ] ; int32_T grirtgo1wo [ 3
] ; int32_T p30scmuimh [ 3 ] ; int32_T edxyvtrnw3 [ 3 ] ; int32_T ckmlti53ey
[ 3 ] ; int32_T i11z0ig3jm ; int32_T ke0zqpublh [ 9 ] ; int32_T enz5ww01sg [
9 ] ; int32_T jakdxomnmi ; int32_T nd2ifd1axi [ 3 ] ; int32_T llye522vj1 ;
int32_T iaytspuvc2 [ 3 ] ; int32_T i0e4upsk2d [ 9 ] ; int32_T io0z1g0pje [ 9
] ; int32_T gihxrchecp [ 9 ] ; int32_T hemavelcim [ 9 ] ; int32_T h1tpfgxf3b
[ 9 ] ; int32_T jszybsysr2 [ 9 ] ; int32_T ioigeufkrg [ 9 ] ; int32_T
ngwwugiho4 [ 9 ] ; int32_T nd1jlmty5o [ 9 ] ; uint16_T fvfmloctub ; uint8_T
mciby2bhmc ; uint8_T oksi514ex4 ; uint8_T d5mmalu5vx ; uint8_T n3swfpwaok ;
uint8_T kycn2fuam4 ; uint8_T e2ntsret2e ; uint8_T aw0y5alaor ; int8_T
jfzsdgbq5e ; int8_T hbkhdg0qsb ; int8_T myemztkk1m ; int8_T j3et02wxql ;
boolean_T dolerm5nyh ; boolean_T bjkenl5zqo ; boolean_T inbt3za1lf ;
boolean_T fmskolgwcb ; boolean_T bttgnayvtn ; boolean_T a4s3xvlbex ;
boolean_T fbqqxnvweh ; boolean_T a1ijhl4wri ; boolean_T fjcgdlcjwe ;
boolean_T nh3gjjgpvk ; boolean_T od5ai22z2l ; boolean_T ksgsqnb2ei ;
boolean_T oru1rzybc2 ; boolean_T mt1ygms2s1 ; boolean_T aondhpk131 ;
boolean_T idhzvwwmxp ; boolean_T j20cbeet2a ; boolean_T fjlr1apiaj ;
boolean_T epstor1a22 ; boolean_T cwnrh0a0wn ; boolean_T h3tkzgo55v ;
boolean_T jeqz1ilrpj ; boolean_T ghxuospbjl ; boolean_T hxnqngtyf1 ;
boolean_T a1jnu0tnvv ; boolean_T jt0dbfa543 ; boolean_T mp2miztasv ;
boolean_T grg2qcew0n ; boolean_T mdhyl1ygwf ; boolean_T p50ijigx25 ;
boolean_T ayauqzczgu ; boolean_T fsyrkzjyrx ; boolean_T j1vdqdq20c ;
boolean_T jvvqwef1jr ; boolean_T c25uz5tds5 ; boolean_T brsz4ajf4x ;
boolean_T f0w0cum5km ; ch3csirfgx cx41wglw3j ; ch3csirfgx jjob4ur221 ;
ch3csirfgx jogryxdnkz ; ch3csirfgx n4cqr1dkmr ; ch3csirfgx a13lr3lsi3 ;
ch3csirfgx jjajpmoyel ; ch3csirfgx ndmeqad3sm ; ch3csirfgx o0tbmhvpds ;
ch3csirfgx f5mkygzljka ; c43be0leba m432cmsuep ; c43be0leba mdkybjqwpy ;
c43be0leba gpry1jhtuq ; c43be0leba dh2sbcx1k5 ; c43be0leba boikvzokby ;
c43be0leba l1oh3i210b ; c43be0leba fzihwa5jz0 ; c43be0leba o0k0yxtimm ;
kavyiqnma5 nzetkmjqj1 ; c43be0leba ndadpcsjlu ; c43be0leba bvam4ywori ;
c43be0leba fpkdn4t3sg ; c43be0leba itzps5ovbe ; c43be0leba nnjygkohqv ;
c43be0leba ijklzzyo04 ; c43be0leba kfdyhargi1 ; c43be0leba bbywkhmyky ;
kavyiqnma5 mwi1r4mwtx ; c43be0leba hfxpwwyhz1 ; c43be0leba epl0ubbsvb ;
c43be0leba imuz2bmqa4 ; c43be0leba a4jyvx22i5 ; c43be0leba kmk13inloe ;
c43be0leba liod1hodre ; c43be0leba f52ctbgs3v ; c43be0leba p4z2y3oxrmd ;
kavyiqnma5 obefemx0qd ; cog2itxiqj biyhxca30f ; cz235gejcz msqwmshj2n ;
cog2itxiqj mzoe5aiivc ; cz235gejcz cstc0v1lpw ; cog2itxiqj azshdeeeiw3 ;
cz235gejcz cqjwvwhkzvh ; } B ; typedef struct { real_T ituktxufmb [ 3 ] ;
real_T epsbkv53pu [ 3 ] ; real_T cmh2vel5ym [ 3 ] ; real_T miazophk3q [ 3 ] ;
real_T cnrqogla5d [ 3 ] ; real_T aanjcgvfa0 [ 3 ] ; real_T aoxcwu3qll ;
real_T gnh32qpzkl [ 3 ] ; real_T ihfcziqcgk ; real_T eahq4k0qba ; real_T
oo31woulsl ; real_T blhgrykwvp ; real_T osqohvejno ; real_T cvcfermial ;
real_T ocn3tuy1mq ; real_T lzrfskvb50 [ 3 ] ; real_T kxzyyq15r0 [ 3 ] ;
real_T jfrl3cqm1n ; real_T ayahx5voca [ 3 ] ; real_T l2zkdqsp2y [ 3 ] ;
real_T lxk5izw00o [ 3 ] ; real_T cqp1dau03w [ 3 ] ; real_T gfiovjo3e2 [ 3 ] ;
real_T p2iwsajmfp [ 3 ] ; real_T b4auxd1lsk [ 3 ] ; real_T al5aajfx21 [ 6 ] ;
real_T gt3chc0tga [ 6 ] ; real_T erukb0glgz [ 3 ] ; real_T pdjkbbbzjq [ 3 ] ;
real_T pml0yl52te [ 3 ] ; real_T eswvf4pz4v ; real_T phidvr4lhk [ 6 ] ;
real_T atdfcebxbc [ 6 ] ; real_T o3sgmp4aev [ 6 ] ; real_T nld3uzo5io [ 6 ] ;
real_T fi4wuwmktb [ 6 ] ; real_T gm4ivysliu [ 6 ] ; real_T pyurk4he1k [ 6 ] ;
real_T ocff1ayzzn [ 6 ] ; real_T l0rzviqodi [ 6 ] ; real_T o0qik01ouq [ 6 ] ;
real_T jci52usrwf [ 6 ] ; real_T n0ifswwd21 [ 6 ] ; real_T enqlcsixk2 [ 6 ] ;
real_T bq4gap0f1m [ 6 ] ; real_T lfuv5ipyfs [ 6 ] ; real_T hjbvl0tg45 [ 6 ] ;
real_T nyxm5sdvcd [ 6 ] ; real_T f0lbp4tqqn [ 3 ] ; real_T fva2rmvmh4 [ 6 ] ;
real_T hdlc0qsc4w [ 6 ] ; real_T fl4tijqsrl [ 6 ] ; real_T mxawq0evig [ 3 ] ;
real_T e1vdezejb0 [ 6 ] ; real_T nrq4usubsl [ 6 ] ; real_T omuzgpsf1f [ 6 ] ;
real_T hys0om0qbu [ 6 ] ; real_T nr5d4vqt4t [ 6 ] ; real_T cnk414y00k [ 6 ] ;
real_T fnpjhtoie0 [ 6 ] ; real_T frvvvscadt [ 6 ] ; real_T pfwwityzhm [ 6 ] ;
real_T awvvdj3gzy [ 6 ] ; real_T esrssadyy0 [ 6 ] ; real_T loh1yczrtr ;
real_T cayw42bvqq [ 3 ] ; real_T fmhxej54hb ; real_T fzberuaezs [ 6 ] ;
real_T oiurtflkiv [ 6 ] ; real_T cedwdfuxlq ; real_T ny5tmca5u1 ; real_T
k3sz0zxcz4 ; real_T hafwy3njkc ; real_T gqa5jm0r2v ; real_T inffcupvx2 ;
real_T p21lrpi51b ; real_T mpvdclcsce ; real_T hma0f53x5s ; real_T fbadxescvd
[ 3 ] ; real_T neqcp2rk0x [ 3 ] ; real_T injrnpzipy [ 3 ] ; real_T cgg3v13mlz
; real_T ffjft2t0pj ; real_T jayew5vh20 ; real_T gtl5stszrm ; real_T
pacgla51lq ; real_T jntfw1jmxj ; real_T ml1vr0zmzd ; real_T ietukijfm5 ;
real_T hcvygsausk ; real_T osj02yjrnn ; real_T o3dbqj4xyk ; real_T ghxlzewxqv
; real_T jw4znmasof ; real_T jsu3fijte2 [ 6 ] ; real_T my5afrzgkd ; real_T
edo3dr0fru ; real_T hyaxdywynl ; real_T on2kbwtd1i ; real_T lfzkcubuyh ;
real_T bt2kw45n5u ; real_T eqzj0rxvun ; real_T ilnpea2zjg ; real_T ddhgjj4slr
; real_T cguk3rlz2c ; real_T myfhgr2zam ; real_T jsu3fijte22 [ 6 ] ; real_T
my5afrzgkdf ; real_T edo3dr0fru5 ; real_T hyaxdywynlc ; real_T anqq4l0npb ;
real_T o13fmizguv ; real_T hdglqralt5 ; real_T ptnxk4g0lc ; real_T pjnb2ek2e3
; real_T m0rv3vqddv ; real_T o10ebbt22e ; real_T mam5vcqfvx ; real_T
jsu3fijte22m [ 6 ] ; real_T my5afrzgkdfq ; real_T edo3dr0fru5x ; real_T
hyaxdywynlcl ; real_T dq0pmdxppu ; real_T jpqfmeeeto ; real_T p25vgyovxo ;
real_T fgxsmumrmw ; real_T p3km4baqfe ; real_T agchj4uiph ; real_T fd5nlfaj2u
; real_T gvxq4lgohv ; struct { void * LoggedData ; } pyihjj0xon ; struct {
void * LoggedData ; } b5wekqpxdr ; struct { void * LoggedData ; } geukoyeszb
; struct { void * LoggedData ; } jmyzu33dul ; struct { void * AQHandles ; }
ityuo0nupl ; struct { void * AQHandles ; } lrdg4xmzak ; struct { void *
AQHandles ; } fkpb3hpobh ; struct { void * AQHandles ; } euzuyivlcf ; struct
{ void * AQHandles ; } hzgoj3w1ci ; struct { void * AQHandles ; } k2wlyn1paf
; struct { void * AQHandles ; } f4ugnmm3af ; struct { void * AQHandles ; }
lnwwdousnr ; struct { void * AQHandles ; } b3y2ruf2y2 ; struct { void *
AQHandles ; } f0zxs3dlyt ; struct { void * AQHandles ; } hdsszfpsby ; struct
{ void * AQHandles ; } exqvxbdaup ; struct { void * AQHandles ; } ettcurcs0e
; struct { void * AQHandles ; } c0e12yj12u ; struct { void * AQHandles ; }
gwqsbwh5jo ; struct { void * AQHandles ; } p3pqosjddk ; struct { void *
LoggedData ; } eaim053dlw ; struct { void * LoggedData ; } oqeo0oboto ;
struct { void * AQHandles ; } e0liuhgqup ; struct { void * LoggedData [ 3 ] ;
} p5myxvrjkv ; struct { void * LoggedData ; } g01sgb0hso ; struct { void *
LoggedData ; } hfxib2vcth ; struct { void * AQHandles ; } e0liuhgqupr ;
struct { void * LoggedData [ 3 ] ; } irsuteiubs ; struct { void * LoggedData
; } pfjuv4s532 ; struct { void * LoggedData ; } homn0ilrw2 ; struct { void *
AQHandles ; } e0liuhgquprw ; struct { void * LoggedData [ 3 ] ; } jdw5ozj2hv
; real32_T ixrsi3erhf [ 6 ] ; real32_T jis1uepreo [ 6 ] ; real32_T fwkxey5epo
[ 54 ] ; real32_T pnsuou2020 [ 6 ] ; real32_T opg1thx2qw [ 6 ] ; real32_T
amalc3ffil [ 6 ] ; real32_T mwenvz0tar [ 6 ] ; real32_T de3otshxus [ 6 ] ;
real32_T i2ctd1awel [ 6 ] ; real32_T ccf5juo5ya [ 6 ] ; real32_T i4lkkodfyj [
6 ] ; real32_T mdvclm3wpb [ 6 ] ; real32_T gai5nv42oe [ 6 ] ; real32_T
imfxseqvvv [ 6 ] ; real32_T cxatkad2jz [ 6 ] ; real32_T ikxzuowx1v [ 6 ] ;
real32_T bg2vv1po0e [ 6 ] ; real32_T f4tcd4udur ; real32_T ctbynjdwij [ 3 ] ;
real32_T anfxf0zt2u [ 6 ] ; real32_T afo0nwhxua [ 3 ] ; real32_T jdtstycpmg [
3 ] ; real32_T g2ry4vjsj1 [ 3 ] ; real32_T iehvrkddj2 [ 3 ] ; real32_T
nbavx35izv [ 3 ] ; real32_T cl1vsftpzn [ 3 ] ; real32_T lhojsnn24m [ 3 ] ;
real32_T d42pvxfz0g [ 3 ] ; real32_T kovzbujdnb [ 3 ] ; real32_T dttn4xmcnk [
3 ] ; real32_T n1ap5w5rdi [ 3 ] ; real32_T ndb122ek3u [ 3 ] ; real32_T
hoesofthyy [ 6 ] ; real32_T ifur0qjdev ; real32_T h2z1m5wxiy [ 6 ] ; real32_T
dviol1u0jv [ 6 ] ; real32_T df5ibuzfvl [ 6 ] ; real32_T ikv4gqtanm [ 6 ] ;
real32_T hru10ym4o1 [ 6 ] ; real32_T erp5nno2ec [ 6 ] ; real32_T ima1cclrzn [
6 ] ; real32_T hm24hbgcg1 [ 6 ] ; real32_T ob20xueupt [ 6 ] ; real32_T
emh5kwkq0f [ 9 ] ; real32_T f3zvxiekpj [ 6 ] ; real32_T dspkd5mdvs [ 15 ] ;
real32_T gmymeboquk [ 6 ] ; real32_T bs1nmm0jpl [ 9 ] ; real32_T bx5vsdt4mt [
6 ] ; real32_T ciaqlqmyyx [ 36 ] ; real32_T e1kih03oaj [ 6 ] ; real32_T
m5gzgpvijm [ 27 ] ; real32_T o3kxgyy1fj [ 27 ] ; real32_T nkf0blmwkl [ 6 ] ;
real32_T h5lg5oz5ks [ 3 ] ; real32_T hggmceleiv [ 6 ] ; real32_T pdhtdmqeof [
36 ] ; real32_T i3xwoxj5zy [ 39 ] ; real32_T lth0p1kskk [ 18 ] ; real32_T
ko0pv0nfnn [ 6 ] ; real32_T kr1btzpdxw [ 6 ] ; real32_T axidhoghf0 [ 6 ] ;
real32_T pqgou55kzx [ 6 ] ; real32_T fuh3bn4ezo [ 6 ] ; real32_T kzefheif0g [
6 ] ; real32_T aa2p00mqis [ 6 ] ; real32_T pasm0mbp1y [ 6 ] ; real32_T
jqvl3ulori [ 6 ] ; real32_T jez5q1v2di [ 6 ] ; real32_T lr1nlrmqch [ 8 ] ;
real32_T a44d5qyg12 [ 8 ] ; real32_T bwkcfpuwid [ 18 ] ; real32_T cno1ak0c3c
[ 18 ] ; real32_T nxk0ojgi44 [ 18 ] ; real32_T bubytbfjvq [ 8 ] ; real32_T
glikpzp24u [ 18 ] ; real32_T hskq4vr1qs [ 57 ] ; real32_T hljbnnt3zw [ 60 ] ;
real32_T d2cg15qgjf [ 60 ] ; real32_T ir1mqsar5f [ 8 ] ; real32_T kebzxgfy5a
; real32_T pmncprwmz4 ; real32_T g05suawwrk ; real32_T ore24n4522 ; real32_T
mz1lyyodga [ 8 ] ; real32_T i22hackosr [ 8 ] ; real32_T hrf0r3epza [ 18 ] ;
real32_T l4gldy0ied [ 18 ] ; real32_T jcgd4tqv41 [ 18 ] ; real32_T oyxqmd0f4v
[ 12 ] ; real32_T cdd1gh0rmi [ 12 ] ; real32_T ayjsmpf3pd [ 40 ] ; real32_T
etncgat1qk [ 12 ] ; real32_T j0pfyx5sl0 [ 12 ] ; real32_T otdqomronl [ 40 ] ;
real32_T nz3xkbxksp [ 12 ] ; real32_T cmxd2uv3ip [ 12 ] ; real32_T hbomutgs5x
[ 40 ] ; int32_T kkklfomjr5 [ 2 ] ; int32_T dmmot30jq4 [ 6 ] ; int32_T
dzr2rntvvo [ 2 ] ; int32_T aw0bxhrzal [ 6 ] ; int32_T estezyunas [ 6 ] ;
int32_T olzifhaukx [ 6 ] ; int32_T miwm3apiea [ 3 ] ; int32_T otborblus0 [ 3
] ; int32_T jcievkrvvv [ 3 ] ; int32_T ovlbtlz2z5 [ 3 ] ; int32_T mx1dy0gdum
[ 3 ] ; int32_T iygynuhhiw [ 3 ] ; int32_T oamcwpfckc ; int32_T az4aq4f2to [
54 ] ; int32_T hv1tfq2dkg ; int32_T ckuddxo2v5 [ 3 ] ; int32_T hoqlzb3yrr [ 3
] ; int32_T d2yav1jvrg [ 3 ] ; int32_T pdli3lyef1 ; real32_T bqjtw0doyx ;
real32_T cc421u2f3f ; real32_T pdjafikrtl ; real32_T pojlxrwx0d ; real32_T
m4fnnxykzj ; real32_T k40ux0ctpf ; real32_T kvknfbkwvk ; real32_T by04uer2xp
; real32_T n1vlvivlrx ; real32_T ib3g0mc4j4 ; real32_T c3coe5r3z1 ; real32_T
gopfnpfdpo ; real32_T fhefxq1ozn ; real32_T bfidcyeanb ; real32_T fi31qowovj
; real32_T pbpmgsmorm ; real32_T axle03m4av [ 5 ] ; real32_T evcuev5sfd [ 9 ]
; real32_T cblzsrog5u ; real32_T nqfbacpvcp ; real32_T fdktvwm3kd ; real32_T
bjkklesnma ; real32_T nsaa1gti0b ; real32_T ghx0ts2zzs ; real32_T lafrvsvgf0
; real32_T og3lno4rre ; real32_T ld5g5vrgmj ; int32_T niztd2zg4p [ 3 ] ;
int32_T faadh0wdog [ 3 ] ; int32_T jgx0xkzgjo [ 3 ] ; int32_T gpf5tclqta [ 3
] ; int32_T mvfamndgj4 [ 3 ] ; int32_T kcaj1yegtz [ 3 ] ; int32_T guhdmzy0n4
; uint16_T bi1fzovgs2 ; uint8_T llxyyz4q5x ; uint8_T bjzrd2jgh1 ; uint8_T
npqdzcpz4k ; boolean_T k44l31otpd [ 3 ] ; boolean_T ocwqpyvhqo ; boolean_T
bb0v2ld5vf [ 18 ] ; boolean_T htr1ntw0w0 [ 60 ] ; boolean_T f1sl003e30 [ 8 ]
; boolean_T lbwbhxgeac ; boolean_T lgjrfdubva [ 5 ] ; boolean_T il1i11vhya [
5 ] ; boolean_T fmvtpht2wc ; boolean_T jlwpaqqpol [ 5 ] ; boolean_T
o2nyvbjxnw [ 5 ] ; boolean_T mofgw1cji2 ; boolean_T hbtp4braxp [ 5 ] ;
boolean_T ifa1aifv0v [ 5 ] ; uint8_T azvnw5pvht ; uint8_T avqcisj0g1 ;
uint8_T hyopdoshjp ; int8_T fqvcumyba1 ; int8_T njfpshnpni ; int8_T
k0efqstpz0 ; int8_T jitieevvno ; int8_T ip0d0t1043 ; int8_T i1c4xekdhn ;
boolean_T bfyezaoly2 ; boolean_T idcpojjs11 ; boolean_T fe3ipxqiw5 ;
boolean_T hw1g0wvqpq ; boolean_T iw5qsles1z ; boolean_T gomqyfi1fi ;
boolean_T dczrefoerg ; boolean_T py4iuvrbea ; boolean_T a43rt5p5qk ;
boolean_T e5cexk5tsa ; boolean_T d2ne5d41vh ; boolean_T gdbbfmmgdg ;
boolean_T jd2ppumcjt ; f5d5p32bfp cx41wglw3j ; f5d5p32bfp jjob4ur221 ;
f5d5p32bfp jogryxdnkz ; f5d5p32bfp n4cqr1dkmr ; f5d5p32bfp a13lr3lsi3 ;
f5d5p32bfp jjajpmoyel ; f5d5p32bfp ndmeqad3sm ; f5d5p32bfp o0tbmhvpds ;
f5d5p32bfp f5mkygzljka ; dqnc2mdlgm biyhxca30f ; gqx2bugedg msqwmshj2n ;
dqnc2mdlgm mzoe5aiivc ; gqx2bugedg cstc0v1lpw ; dqnc2mdlgm azshdeeeiw3 ;
gqx2bugedg cqjwvwhkzvh ; } DW ; typedef struct { real_T ptze3ue0cm ; real_T
flellzbl1y ; } X ; typedef struct { real_T ptze3ue0cm ; real_T flellzbl1y ; }
XDot ; typedef struct { boolean_T ptze3ue0cm ; boolean_T flellzbl1y ; } XDis
; typedef struct { nrs5bzunb3 msqwmshj2n ; nrs5bzunb3 cstc0v1lpw ; nrs5bzunb3
cqjwvwhkzvh ; } PrevZCX ; typedef struct { rtwCAPI_ModelMappingInfo mmi ; }
DataMapInfo ; struct bnof3krbot_ { real_T Pulses_Y0 ; real_T
uDLookupTable_tableData [ 6 ] ; real_T uDLookupTable_bp01Data [ 6 ] ; real_T
Switch1_Threshold ; real_T Constant4_Value ; real_T Constant2_Value ; real_T
uib2_Gain ; real_T u4_Gain ; real_T u2_Gain ; real_T u2_Gain_ci0stxvb1g ;
real_T u2_Gain_bktdt40nlr ; real_T HitCrossing_Offset ; real_T
UnitDelay_InitialCondition ; real_T Saturation_UpperSat ; real_T
Saturation_LowerSat ; real_T DirectLookUpTablenD_table [ 126 ] ; real_T
Constant_Value ; real_T Constant1_Value ; real_T Constant2_Value_g14jlw05vl ;
real_T Constant8_Value ; real_T Constant1_Value_kmpgskj54q ; real_T
Constant2_Value_h0opffki0s ; real_T Constant3_Value ; real_T Constant7_Value
; uint8_T DirectLookUpTablenD_DiagnosticForOutOfRangeInput ; } ; struct
nygobnlzkj_ { real_T Pulses_Y0 ; real_T
LookUpTableDeterminethesectorofUbasedonalpharad_tableData [ 6 ] ; real_T
LookUpTableDeterminethesectorofUbasedonalpharad_bp01Data [ 6 ] ; real_T
uDLookupTable_tableData [ 6 ] ; real_T uDLookupTable_bp01Data [ 6 ] ; real_T
uDLookupTable1_tableData [ 6 ] ; real_T uDLookupTable1_bp01Data [ 6 ] ;
real_T uDLookupTable2_tableData [ 6 ] ; real_T uDLookupTable2_bp01Data [ 6 ]
; real_T uDLookupTable3_tableData [ 6 ] ; real_T uDLookupTable3_bp01Data [ 6
] ; real_T gain_Gain ; real_T Constant3_Value ; real_T Constant4_Value ;
real_T uib1_Gain ; real_T uDLookupTable_tableData_jf0tl0zi2n [ 3 ] ; real_T
uDLookupTable_bp01Data_dlxdluyycg [ 3 ] ; real_T Constant2_Value ; real_T
Saturation_UpperSat ; real_T Saturation_LowerSat ; real_T
UnitDelay_InitialCondition ; real_T Constant1_Value ; real_T
Constant2_Value_kj0t41nl1x ; } ; struct nytscbbkkv_ { int64_T out0_Y0 ;
int64_T PipelineRegister_InitialCondition ; int64_T Constant_Value ; } ;
struct P_ { real_T L_d ; real_T L_o1 ; real_T L_o2 ; real_T L_q ; real_T L_x1
; real_T L_x2 ; real_T L_y1 ; real_T L_y2 ; real_T L_zero ; real_T R_1 ;
real_T c [ 81 ] ; real_T f_pwm ; real_T friction_coefficient ; real_T inertia
; real_T k_i_d ; real_T k_i_q ; real_T k_p_d ; real_T k_p_q ; real_T lim_pi ;
real_T polepair ; real_T psi_pm ; real_T static_friction_torque ; real_T
AlphaBetaZerotodq0_Alignment ; real_T dq0toAlphaBetaZero_Alignment ; real_T
PIDController2_InitialConditionForIntegrator ; real_T
PIDController2_InitialConditionForIntegrator_fepqme2wel ; real_T
SVPWMGenerator2Level_InputType ; real_T
SVPWMGenerator2Level_InputType_p5gp2uzlhc ; real_T
SVPWMGenerator2Level_InputType_eeovqphbmi ; real_T
SVPWMGenerator2Level_SwitchingPattern ; real_T
SVPWMGenerator2Level_SwitchingPattern_kmqtzirjjx ; real_T
SVPWMGenerator2Level_SwitchingPattern_b5rdju1jqc ; real_T
CompareToConstant_const ; real_T CompareToConstant1_const ; real_T
CompareToConstant_const_i2rz2duvtn ; real_T
CompareToConstant1_const_icp5urwmrl ; real32_T MultiplyState_constMatrix [ 36
] ; real32_T MultiplyInput_constMatrix [ 768 ] ; real32_T
MultiplyState_constMatrix_eohiapchpm [ 36 ] ; real32_T
MultiplyInput_constMatrix_ny0mxowoiz [ 768 ] ; real32_T
MultiplyState_constMatrix_d53rujt10a [ 36 ] ; real32_T
MultiplyInput_constMatrix_dt0y2fteom [ 768 ] ; uint16_T
enb_counter_ge_51_const ; uint16_T enb_counter_le_59_const ; uint16_T
ctr_499_uplimit ; uint8_T Subsystem8_Index ; uint8_T Subsystem7_Index ;
uint8_T Subsystem6_Index ; uint8_T Subsystem5_Index ; uint8_T
Subsystem4_Index ; uint8_T Subsystem3_Index ; uint8_T Subsystem2_Index ;
uint8_T Subsystem1_Index ; uint8_T Subsystem8_Index_fzlqi5zbx5 ; uint8_T
Subsystem7_Index_hzi3xwpiyv ; uint8_T Subsystem6_Index_g31i2fthbw ; uint8_T
Subsystem5_Index_glcvjbpr4j ; uint8_T Subsystem4_Index_gjtpscjc3t ; uint8_T
Subsystem3_Index_jyh2hyuoat ; uint8_T Subsystem2_Index_o2hydk3gbe ; uint8_T
Subsystem1_Index_gamunef4go ; uint8_T Subsystem8_Index_g1r4pfdd11 ; uint8_T
Subsystem7_Index_n4h55mccm4 ; uint8_T Subsystem6_Index_kjr4ynilvy ; uint8_T
Subsystem5_Index_kc5dwsgpkh ; uint8_T Subsystem4_Index_k4wyew5d14 ; uint8_T
Subsystem3_Index_cao32uglvg ; uint8_T Subsystem2_Index_cwbdy5b3nk ; uint8_T
Subsystem1_Index_onoalnmieu ; uint8_T CompareToConstant_const_cnyrwuombr ;
uint8_T CompareToConstant_const_fvoxtyn5vv ; uint8_T
CompareToConstant_const_kipk51db13 ; uint8_T CounterLimited_uplimit ; uint8_T
CounterLimited_uplimit_fvgmipctvh ; uint8_T CounterLimited_uplimit_np4zdwmb1e
; real_T dq_Y0 [ 2 ] ; real_T dq_Y0_o3qdmlalvk [ 2 ] ; real_T alpha_beta_Y0 [
2 ] ; real_T alpha_beta_Y0_ops5pd5nfl [ 2 ] ; real_T G_InitialCondition ;
real_T RateTransition2_InitialCondition ; real_T
RateTransition1_InitialCondition ; real_T G_InitialCondition_jxkxj0lwzg ;
real_T RateTransition2_InitialCondition_koo3fszowf ; real_T
RateTransition1_InitialCondition_fmb14y3cnw ; real_T
G_InitialCondition_jxkxj0lwzg4 ; real_T
RateTransition2_InitialCondition_aqmfututeg ; real_T
RateTransition1_InitialCondition_pdphulocq1 ; real_T
DataTypeConversion3_pd1_InitialCondition ; real_T
DataTypeConversion11_pd1_InitialCondition ; real_T
DataTypeConversion12_pd1_InitialCondition ; real_T Initial_Val2_Value ;
real_T crp_out_delay1_InitialCondition ; real_T
DataTypeConversion14_pd1_InitialCondition ; real_T Initial_Val3_Value ;
real_T crp_out_delay5_InitialCondition ; real_T Initial_Val4_Value ; real_T
crp_out_delay6_InitialCondition ; real_T Initial_Val5_Value ; real_T
crp_out_delay7_InitialCondition ; real_T Initial_Val6_Value ; real_T
crp_out_delay8_InitialCondition ; real_T Initial_Val7_Value ; real_T
crp_out_delay9_InitialCondition ; real_T Initial_Val8_Value ; real_T
crp_out_delay10_InitialCondition ; real_T Initial_Val9_Value ; real_T
crp_out_delay11_InitialCondition ; real_T
DataTypeConversion21_pd1_InitialCondition ; real_T
DataTypeConversion22_pd1_InitialCondition ; real_T Initial_Val_Value ; real_T
crp_out_delay3_InitialCondition ; real_T
DataTypeConversion24_pd1_InitialCondition ; real_T
DataTypeConversion25_pd1_InitialCondition ; real_T
DataTypeConversion26_pd1_InitialCondition ; real_T
DataTypeConversion27_pd1_InitialCondition ; real_T
DataTypeConversion28_pd1_InitialCondition ; real_T
DataTypeConversion29_pd1_InitialCondition ; real_T
DataTypeConversion30_pd1_InitialCondition ; real_T
Product6_pd1_InitialCondition ; real_T Product5_pd1_InitialCondition ; real_T
DataTypeConversion33_pd1_InitialCondition ; real_T
DataTypeConversion331_pd1_InitialCondition ; real_T
DataTypeConversion5_pd1_InitialCondition ; real_T Initial_Val1_Value ; real_T
crp_out_delay2_InitialCondition ; real_T Gain_const_Value ; real_T
Sum1_stage3_pd1_InitialCondition ; real_T Gain_pd1_InitialCondition ; real_T
Gain_const1_Value ; real_T Gain1_pd1_InitialCondition ; real_T
Gain_const2_Value ; real_T Sum_stage3_pd1_InitialCondition ; real_T
Gain2_pd1_InitialCondition ; real_T Gain_const3_Value ; real_T
Gain3_pd1_InitialCondition ; real_T Gain_const4_Value ; real_T
Gain4_pd1_InitialCondition ; real_T Gain_const5_Value ; real_T
Gain5_pd1_InitialCondition ; real_T Gain_const6_Value ; real_T
Gain6_pd1_InitialCondition ; real_T Gain_const7_Value ; real_T
Gain7_pd1_InitialCondition ; real_T Gain_const8_Value ; real_T
Gain8_pd1_InitialCondition ; real_T Gain_const9_Value ; real_T
Gain9_pd1_InitialCondition ; real_T Product10_pd1_InitialCondition ; real_T
Product_pd1_InitialCondition ; real_T Product1_pd1_InitialCondition ; real_T
delayMatch18_InitialCondition ; real_T Sum2_pd1_InitialCondition ; real_T
delayMatch16_InitialCondition ; real_T Product7_pd1_InitialCondition ; real_T
Product8_pd1_InitialCondition ; real_T Sum1_stage2_pd1_InitialCondition ;
real_T delayMatch17_InitialCondition ; real_T Sum3_pd1_InitialCondition ;
real_T Sum31_pd1_InitialCondition ; real_T Sum310_pd1_InitialCondition ;
real_T Sum32_pd1_InitialCondition ; real_T Sum34_pd1_InitialCondition ;
real_T Sum35_pd1_InitialCondition ; real_T Sum36_pd1_InitialCondition ;
real_T Sum37_pd1_InitialCondition ; real_T Sum38_pd1_InitialCondition ;
real_T Sum39_pd1_InitialCondition ; real_T Sum_stage2_pd1_InitialCondition ;
real_T Initial_Val_Value_pik4yifivl ; real_T delayMatch1_InitialCondition ;
real_T DataTypeConversion2_pd1_InitialCondition ; real_T
crp_out_delay_InitialCondition ; real_T Gain_const_Value_kf5wnphskk ; real_T
Gain_pd1_InitialCondition_cts3ldlqmt ; real_T
Sum3_pd1_InitialCondition_peozyuudyd ; real_T Constant1_Value ; real_T
Constant1_Value_ldif3tdbbp ; real_T Step1_Time ; real_T Step1_Y0 ; real_T
Step1_YFinal ; real_T TmpRTBAtSumInport1_InitialCondition ; real_T
TmpRTBAtSumInport1_InitialCondition_i0245o1ytv ; real_T
TmpRTBAtSubsystem1Inport2_InitialCondition ; real_T
TmpRTBAtSubsystempi2delayInport2_InitialCondition ; real_T Gain3_Gain [ 9 ] ;
real_T Gain1_Gain ; real_T um1_UpperSat ; real_T um1_LowerSat ; real_T
Constant_Value ; real_T Constant_Value_nf3bb0tq45 ; real_T
Constant_Value_mwigsjn0on ; real_T Gain3_Gain_gkm2xguh4p [ 9 ] ; real_T
Gain1_Gain_nutmkm45g1 ; real_T um1_UpperSat_lvqel1uo0o ; real_T
um1_LowerSat_necuzvpcee ; real_T Gain3_Gain_bttof010vd [ 9 ] ; real_T
Gain1_Gain_bejkcmwgji ; real_T um1_UpperSat_l35ktjv2oo ; real_T
um1_LowerSat_d3qp0zvp4b ; real_T UnitDelay_InitialCondition ; real_T
UnitDelay1_InitialCondition ; real_T UnitDelay3_InitialCondition ; real_T
ZeroGain_Gain ; real_T TmpRTBAtSwitchInport3_InitialCondition ; real_T
ZeroGain_Gain_b4r1gxoc4f ; real_T
TmpRTBAtSwitchInport3_InitialCondition_i4lr0xcxgv ; real_T Constant3_Value ;
real_T Constant_Value_a3tiqve2ba ; real_T Constant1_Value_pc5hbderw4 ; real_T
Constant2_Value ; real_T Constant3_Value_asrfyaoivf ; real_T
Constant_Value_ep3zz2rhlg ; real_T Constant1_Value_gihsyq2jvw ; real_T
Constant2_Value_ouhzm4n00j ; real_T DegRad_Gain ; real_T Freq2_Value ; real_T
Constant_Value_hrxltwm4pv ; real_T Constant1_Value_are0ior3pl ; real_T
Constant2_Value_ayggr1hr00 ; real_T Constant3_Value_fsonf21ozn ; real_T
Constant_Value_n5xgxhep3k ; real_T Constant1_Value_fc5w4veyse ; real_T
Constant2_Value_jrika1x30d ; real_T DegRad_Gain_hsvtiaadnd ; real_T
Freq2_Value_hfy2fcbazp ; real_T Constant_Value_hnyucebqyk ; real_T
Constant1_Value_eembvftqvk ; real_T Constant2_Value_nvluxn40nk ; real_T
Constant3_Value_mwaqmz2fbl ; real_T Constant_Value_dl3vzsgqc3 ; real_T
Constant1_Value_id2q2llyug ; real_T Constant2_Value_aq5b3qckdj ; real_T
DegRad_Gain_lpbikznakf ; real_T Freq2_Value_nqc1qew4zf ; real_T setp_iq_Value
; real_T Constant_Value_k0oeb5ytii ; real_T Constant2_Value_c1xcu1ly3c ;
real_T Constant_Value_ak1tppnn4h ; real_T Constant_Value_pzbpxmwupt ; real_T
Constant1_Value_grwerjwqox [ 81 ] ; real_T Constant3_Value_lglm3qv24g ;
real_T omega_mech1_Value ; real_T ud_Value ; real_T uq_Value ; int64_T
_bias_Value ; int64_T _bias1_Value ; int64_T _bias2_Value ; int64_T
_bias3_Value ; int64_T _bias4_Value ; int64_T _bias5_Value ; int64_T
_bias6_Value ; int64_T _bias7_Value ; int64_T _bias8_Value ; int32_T
Constant1_Value_mfqrhuom3x [ 81 ] ; int32_T Constant1_Value_jytosolkko [ 81 ]
; int32_T DataTypeConversion1_pd1_InitialCondition ; int32_T
Delay1_InitialCondition ; int32_T Delay_InitialCondition ; int32_T
Delay2_InitialCondition ; int32_T Delay3_InitialCondition ; int32_T
Delay4_InitialCondition ; int32_T crp_out_delay12_InitialCondition ; int32_T
Delay5_InitialCondition ; int32_T crp_out_delay13_InitialCondition ; int32_T
Delay6_InitialCondition ; int32_T crp_out_delay14_InitialCondition ; int32_T
crp_out_delay_InitialCondition_j0kceq3s5o ; int32_T
DataTypeConversion28_pd1_InitialCondition_enouvozbat ; int32_T
delay_InitialCondition ; int32_T delayMatch35_InitialCondition ; int32_T
delayMatch36_InitialCondition ; int32_T delayMatch37_InitialCondition ;
int32_T delayMatch38_InitialCondition ; int32_T
Delay_InitialCondition_doutal3110 ; real32_T StateDelay_InitialCondition [ 12
] ; real32_T Delay3_InitialCondition_pz0l4fynfp ; real32_T X0_Value [ 12 ] ;
real32_T Delay1_InitialCondition_gatgxvvxab ; real32_T Bias_Value [ 96 ] ;
real32_T StateDelay_InitialCondition_mi2yczlxa3 [ 12 ] ; real32_T
Delay3_InitialCondition_g5eqpjibmj ; real32_T X0_Value_osgqfzom1r [ 12 ] ;
real32_T Delay1_InitialCondition_opon0r3npu ; real32_T Bias_Value_aaxy53sl5x
[ 96 ] ; real32_T StateDelay_InitialCondition_guggx4cua1 [ 12 ] ; real32_T
Delay3_InitialCondition_ixg4h4ehk2 ; real32_T X0_Value_dgtnjkgayi [ 12 ] ;
real32_T Delay1_InitialCondition_fmarmststv ; real32_T Bias_Value_egvhuyhyzm
[ 96 ] ; real32_T Constant_Value_hlt3aiqgcy ; real32_T
Add_pd1_InitialCondition ; real32_T Add1_pd1_InitialCondition ; real32_T
DataTypeConversion39_pd1_InitialCondition ; real32_T
Divide_pd1_InitialCondition ; real32_T Add_pd1_InitialCondition_n1tl5wbe5f ;
real32_T Divide2_pd1_InitialCondition ; real32_T
Add1_pd1_InitialCondition_jad155jnqy ; real32_T Divide4_pd1_InitialCondition
; real32_T Add2_pd1_InitialCondition ; real32_T Divide6_pd1_InitialCondition
; real32_T Add3_pd1_InitialCondition ; real32_T Divide8_pd1_InitialCondition
; real32_T Add4_pd1_InitialCondition ; real32_T Divide10_pd1_InitialCondition
; real32_T Add5_pd1_InitialCondition ; real32_T Divide12_pd1_InitialCondition
; real32_T Add6_pd1_InitialCondition ; real32_T delayMatch2_InitialCondition
; real32_T DataTypeConversion13_pd1_InitialCondition ; real32_T
Product11_pd1_InitialCondition ; real32_T
DataTypeConversion141_pd1_InitialCondition ; real32_T
DataTypeConversion15_pd1_InitialCondition ; real32_T
DataTypeConversion16_pd1_InitialCondition ; real32_T
DataTypeConversion17_pd1_InitialCondition ; real32_T
DataTypeConversion18_pd1_InitialCondition ; real32_T
DataTypeConversion19_pd1_InitialCondition ; real32_T
DataTypeConversion20_pd1_InitialCondition ; real32_T
DataTypeConversion23_pd1_InitialCondition ; real32_T
DataTypeConversion31_pd1_InitialCondition ; real32_T
DataTypeConversion32_pd1_InitialCondition ; real32_T
DataTypeConversion8_pd1_InitialCondition ; real32_T
delayMatch15_InitialCondition ; real32_T
DataTypeConversion37_pd1_InitialCondition ; real32_T
crp_out_delay4_InitialCondition ; real32_T Divide1_pd1_InitialCondition ;
real32_T Divide11_pd1_InitialCondition ; real32_T
Divide13_pd1_InitialCondition ; real32_T Divide3_pd1_InitialCondition ;
real32_T Divide5_pd1_InitialCondition ; real32_T Divide7_pd1_InitialCondition
; real32_T Divide9_pd1_InitialCondition ; real32_T Factor_const_Value ;
real32_T Sum33_pd1_InitialCondition ; real32_T Factor_pd1_InitialCondition ;
real32_T Mux_out1_InitialCondition ; real32_T Sum1_pd1_InitialCondition ;
real32_T delayMatch20_InitialCondition ; real32_T
Product2_pd1_InitialCondition ; real32_T delayMatch19_InitialCondition ;
real32_T Product3_pd1_InitialCondition ; real32_T
delayMatch22_InitialCondition ; real32_T Product9_pd1_InitialCondition ;
real32_T Sin_to_sincos_pd1_InitialCondition ; real32_T
Sin_to_sincos_pd2_InitialCondition ; real32_T delayMatch21_InitialCondition ;
real32_T DataTypeConversion1_pd1_InitialCondition_mvexewp4sm ; real32_T
Divide_pd1_InitialCondition_iqg20l45y4 ; real32_T
delayMatch23_InitialCondition ; real32_T delayMatch26_InitialCondition ;
real32_T delayMatch_InitialCondition ; real32_T
Divide_pd1_InitialCondition_on1tgmlnc5 ; real32_T
Divide1_pd1_InitialCondition_nynh3rh5wh ; real32_T
Divide3_pd1_InitialCondition_mlowt02ilw ; real32_T
Divide2_pd1_InitialCondition_kdu4cy0gyz ; real32_T
Divide_pd1_InitialCondition_pjuin1ba3m ; real32_T
Divide1_pd1_InitialCondition_jtfnqzsn4k ; real32_T
Add_pd1_InitialCondition_asnecikhmg ; real32_T
Divide2_pd1_InitialCondition_kxizquldvw ; real32_T
Divide3_pd1_InitialCondition_bk22v0hz40 ; real32_T
Add1_pd1_InitialCondition_foyb4xrhux ; real32_T
delayMatch_InitialCondition_gw555m4rpr ; real32_T
delayMatch1_InitialCondition_pf2zcfdqdf ; real32_T
delayMatch10_InitialCondition ; real32_T delayMatch12_InitialCondition ;
real32_T delayMatch13_InitialCondition ; real32_T
delayMatch2_InitialCondition_gxmnquuszr ; real32_T
delayMatch24_InitialCondition ; real32_T delayMatch25_InitialCondition ;
real32_T delayMatch28_InitialCondition ; real32_T
delayMatch29_InitialCondition ; real32_T delayMatch3_InitialCondition ;
real32_T delayMatch30_InitialCondition ; real32_T
delayMatch31_InitialCondition ; real32_T delayMatch33_InitialCondition ;
real32_T delayMatch34_InitialCondition ; real32_T
delayMatch5_InitialCondition ; real32_T delayMatch6_InitialCondition ;
real32_T delayMatch7_InitialCondition ; real32_T delayMatch8_InitialCondition
; real32_T delayMatch9_InitialCondition ; uint16_T Output_InitialCondition ;
uint16_T FixPtConstant_Value ; uint16_T Constant_Value_nxgby3d43k ; boolean_T
Delay_InitialCondition_h2511jeak5 ; boolean_T
Delay2_InitialCondition_bawdou0zon ; boolean_T
Delay1_InitialCondition_phnxqmqpfv ; boolean_T Constant_Value_pcb3rcescv ;
boolean_T ModeVector8_Value [ 12 ] ; boolean_T ModeVector7_Value [ 12 ] ;
boolean_T ModeVector6_Value [ 12 ] ; boolean_T ModeVector5_Value [ 12 ] ;
boolean_T ModeVector4_Value [ 12 ] ; boolean_T ModeVector3_Value [ 12 ] ;
boolean_T ModeVector2_Value [ 12 ] ; boolean_T ModeVector1_Value [ 12 ] ;
boolean_T ValidOut1_Value ; boolean_T Delay_InitialCondition_hsyswncslp ;
boolean_T Delay2_InitialCondition_l1s0ro1fve ; boolean_T
Delay1_InitialCondition_lhskk4uacg ; boolean_T Constant_Value_a2izqb3iov ;
boolean_T ModeVector8_Value_pe5qwse0zo [ 12 ] ; boolean_T
ModeVector7_Value_exy1mfuwew [ 12 ] ; boolean_T ModeVector6_Value_be5qaduvq0
[ 12 ] ; boolean_T ModeVector5_Value_mcfamzdv4h [ 12 ] ; boolean_T
ModeVector4_Value_bvzbygmfek [ 12 ] ; boolean_T ModeVector3_Value_dpbdjp1pks
[ 12 ] ; boolean_T ModeVector2_Value_pbdosmlzxp [ 12 ] ; boolean_T
ModeVector1_Value_lzg1v22s1n [ 12 ] ; boolean_T ValidOut1_Value_fddponpq1g ;
boolean_T Delay_InitialCondition_lwyrt2xv4d ; boolean_T
Delay2_InitialCondition_fjvh01tibv ; boolean_T
Delay1_InitialCondition_jfqjorsshb ; boolean_T Constant_Value_n1bvru41ik ;
boolean_T ModeVector8_Value_ndjrz30mn4 [ 12 ] ; boolean_T
ModeVector7_Value_kfcbsv4wr0 [ 12 ] ; boolean_T ModeVector6_Value_jxzmvcin1w
[ 12 ] ; boolean_T ModeVector5_Value_pdt0z4g5rr [ 12 ] ; boolean_T
ModeVector4_Value_cebv2o0h2i [ 12 ] ; boolean_T ModeVector3_Value_ct3wsuvwjv
[ 12 ] ; boolean_T ModeVector2_Value_ksothw4zp0 [ 12 ] ; boolean_T
ModeVector1_Value_jwc0rjoavh [ 12 ] ; boolean_T ValidOut1_Value_lbhou0b3dw ;
boolean_T delayMatch14_InitialCondition ; boolean_T
delayMatch32_InitialCondition ; boolean_T delayMatch11_InitialCondition ;
boolean_T delayMatch27_InitialCondition ; boolean_T
delayMatch4_InitialCondition ; boolean_T
TmpRTBAtuz_inverter_3phInport2_InitialCondition ; boolean_T
Memory_InitialCondition ; boolean_T Memory_InitialCondition_h50fp4oqpu ;
boolean_T TmpRTBAtuz_inverter_3ph1Inport2_InitialCondition ; boolean_T
TmpRTBAtuz_inverter_3ph2Inport2_InitialCondition ; boolean_T Constant9_Value
; boolean_T Constant9_Value_gdn1knb3nq ; boolean_T Constant9_Value_fgokpme3bd
; boolean_T simulate_mechanical_Value ; boolean_T simulate_mechanical1_Value
; boolean_T simulate_mechanical2_Value ; boolean_T Constant1_Value_mkyn4cvwnf
; int8_T Constant_Value_isqfwdnanj ; int8_T Constant_Value_fbzm1lgfms ;
int8_T TmpRTBAtEqual1Inport2_InitialCondition ; int8_T
TmpRTBAtEqual1Inport2_InitialCondition_elqjaja3n4 ; uint8_T
Delay_InitialCondition_locz5doan2 ; uint8_T Index_Value ; uint8_T
Delay_InitialCondition_gboil2iboz ; uint8_T Index_Value_fzocaavlvm ; uint8_T
Delay_InitialCondition_hk250tgmls ; uint8_T Index_Value_co5ixudaqi ; uint8_T
Constant_Value_ebjb3omr24 ; uint8_T DefaultIndex_Value ; uint8_T
Constant_Value_h33j5qc3ne ; uint8_T DefaultIndex_Value_dlqxo25nwp ; uint8_T
Constant_Value_a2fgb02dpi ; uint8_T DefaultIndex_Value_a00bbokt5z ; uint8_T
Output_InitialCondition_k1eifxwcol ; uint8_T FixPtConstant_Value_opnmhasca3 ;
uint8_T Constant_Value_lcohz4siwn ; uint8_T
Output_InitialCondition_p4phx04cq3 ; uint8_T FixPtConstant_Value_ixzugyupnp ;
uint8_T Constant_Value_fm1213sgjm ; uint8_T
Output_InitialCondition_fsvrv3myjb ; uint8_T FixPtConstant_Value_mariintfbp ;
uint8_T Constant_Value_eorisuadz3 ; nytscbbkkv cx41wglw3j ; nytscbbkkv
jjob4ur221 ; nytscbbkkv jogryxdnkz ; nytscbbkkv n4cqr1dkmr ; nytscbbkkv
a13lr3lsi3 ; nytscbbkkv jjajpmoyel ; nytscbbkkv ndmeqad3sm ; nytscbbkkv
o0tbmhvpds ; nytscbbkkv f5mkygzljka ; nygobnlzkj biyhxca30f ; bnof3krbot
msqwmshj2n ; nygobnlzkj mzoe5aiivc ; bnof3krbot cstc0v1lpw ; nygobnlzkj
azshdeeeiw3 ; bnof3krbot cqjwvwhkzvh ; } ; extern const char *
RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern X rtX ; extern DW rtDW ;
extern PrevZCX rtPrevZCX ; extern P rtP ; extern mxArray *
mr_uz_drive_model_GetDWork ( ) ; extern void mr_uz_drive_model_SetDWork (
const mxArray * ssDW ) ; extern mxArray *
mr_uz_drive_model_GetSimStateDisallowedBlocks ( ) ; extern const
rtwCAPI_ModelMappingStaticInfo * uz_drive_model_GetCAPIStaticMap ( void ) ;
extern SimStruct * const rtS ; extern const int_T gblNumToFiles ; extern
const int_T gblNumFrFiles ; extern const int_T gblNumFrWksBlocks ; extern
rtInportTUtable * gblInportTUtables ; extern const char * gblInportFileName ;
extern const int_T gblNumRootInportBlks ; extern const int_T
gblNumModelInputs ; extern const int_T gblInportDataTypeIdx [ ] ; extern
const int_T gblInportDims [ ] ; extern const int_T gblInportComplex [ ] ;
extern const int_T gblInportInterpoFlag [ ] ; extern const int_T
gblInportContinuous [ ] ; extern const int_T gblParameterTuningTid ; extern
DataMapInfo * rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo *
rt_modelMapInfoPtr ; void MdlOutputs ( int_T tid ) ; void
MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T tid ) ;
void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void
MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model (
ssExecutionInfo * executionInfo ) ;
#endif
