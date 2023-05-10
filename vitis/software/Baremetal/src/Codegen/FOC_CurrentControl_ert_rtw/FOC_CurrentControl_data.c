/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_CurrentControl_data.c
 *
 * Code generated for Simulink model 'FOC_CurrentControl'.
 *
 * Model version                  : 7.2
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Wed May 10 08:14:37 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "FOC_CurrentControl.h"

/* Block parameters (default storage) */
P rtP = {
  /* Mask Parameter: CompareToConstant_const
   * Referenced by: '<S7>/Constant'
   */
  3.0,

  /* Mask Parameter: CompareToConstant_const_e
   * Referenced by: '<S50>/Constant'
   */
  1.0,

  /* Mask Parameter: AntiWindupGT_d_const
   * Referenced by: '<S33>/Constant'
   */
  0.0,

  /* Mask Parameter: AntiWindupGT_q_const
   * Referenced by: '<S34>/Constant'
   */
  0.0,

  /* Mask Parameter: CompareToConstant_const_j
   * Referenced by: '<S47>/Constant'
   */
  1.0,

  /* Mask Parameter: SRFlipFlop_initial_condition
   * Referenced by: '<S58>/Memory'
   */
  false,

  /* Mask Parameter: SRFlipFlop1_initial_condition
   * Referenced by: '<S59>/Memory'
   */
  false,

  /* Mask Parameter: SRFlipFlop_initial_condition_d
   * Referenced by: '<S53>/Memory'
   */
  false,

  /* Mask Parameter: If_Start_over_initial_condition
   * Referenced by: '<S39>/Memory'
   */
  false,

  /* Mask Parameter: If_Start_over1_initial_conditio
   * Referenced by: '<S40>/Memory'
   */
  false,

  /* Mask Parameter: DetectRisePositive_vinit
   * Referenced by: '<S57>/Delay Input1'
   */
  false,

  /* Mask Parameter: DetectRisePositive_vinit_c
   * Referenced by: '<S52>/Delay Input1'
   */
  false,

  /* Expression: [0 0 0]
   * Referenced by: '<S3>/AKS_LS'
   */
  { 0.0, 0.0, 0.0 },

  /* Expression: [1 1 1]
   * Referenced by: '<S3>/AKS_HS'
   */
  { 1.0, 1.0, 1.0 },

  /* Expression: [0.5 0.5 0.5]
   * Referenced by: '<S3>/AKS_LSHS'
   */
  { 0.5, 0.5, 0.5 },

  /* Expression: 0
   * Referenced by: '<S16>/Constant2'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S16>/Constant3'
   */
  6.2831853071795862,

  /* Expression: -2*pi
   * Referenced by: '<S16>/Constant1'
   */
  -6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S16>/Constant'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S17>/Constant'
   */
  6.2831853071795862,

  /* Expression: -2*pi
   * Referenced by: '<S19>/Bias'
   */
  -6.2831853071795862,

  /* Expression: 1
   * Referenced by: '<S4>/Constant1'
   */
  1.0,

  /* Expression: -1
   * Referenced by: '<S4>/Constant2'
   */
  -1.0,

  /* Expression: -2*pi
   * Referenced by: '<S26>/Constant5'
   */
  -6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S26>/Constant6'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S26>/Constant2'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S26>/Constant4'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S24>/Constant'
   */
  6.2831853071795862,

  /* Expression: 2*pi
   * Referenced by: '<S24>/Constant1'
   */
  6.2831853071795862,

  /* Expression: 2*pi
   * Referenced by: '<S25>/Constant'
   */
  6.2831853071795862,

  /* Expression: 2*pi
   * Referenced by: '<S25>/Constant1'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S32>/IntegStopSwitch3'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S36>/Gain'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S36>/Gain1'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S36>/Discrete FIR Filter 20th order1'
   */
  0.0,

  /* Expression: 1/20*[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]
   * Referenced by: '<S36>/Discrete FIR Filter 20th order1'
   */
  { 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05,
    0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05 },

  /* Expression: 1
   * Referenced by: '<S36>/Gain3'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S36>/Discrete FIR Filter 20th order'
   */
  0.0,

  /* Expression: 1/20*[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]
   * Referenced by: '<S36>/Discrete FIR Filter 20th order'
   */
  { 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05,
    0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05 },

  /* Expression: 1
   * Referenced by: '<S36>/Gain2'
   */
  1.0,

  /* Expression: 0.5
   * Referenced by: '<S37>/Constant1'
   */
  0.5,

  /* Expression: 0
   * Referenced by: '<S41>/Constant1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S48>/Constant1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S49>/Constant1'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S45>/Gain1'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S45>/Constant1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S46>/Constant1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S42>/Constant'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S14>/limit T3'
   */
  0.0,

  /* Expression: V_R_n.z
   * Referenced by: '<S14>/V_R_Scheduling'
   */
  { 0.06, 0.03, 0.01, 0.005, 0.002 },

  /* Expression: V_R_n.x1
   * Referenced by: '<S14>/V_R_Scheduling'
   */
  { 30000.0, 50000.0, 75000.0, 100000.0, 120000.0 },

  /* Expression: 0
   * Referenced by: '<S14>/Constant7'
   */
  0.0,

  /* Expression: 15e3
   * Referenced by: '<S14>/Switch'
   */
  15000.0,

  /* Expression: EMotor.par.k_T.z
   * Referenced by: '<S14>/calc_TorqueRef'
   */
  0.045675499832195113,

  /* Expression: 1/sqrt(2)
   * Referenced by: '<S14>/Gain3'
   */
  0.70710678118654746,

  /* Expression: EMotor.FEM_data.Id_Mn.z
   * Referenced by: '<S14>/Id_Mn_LUT'
   */
  { -0.032190124786170858, -0.060404953539763981, -0.078635057358864544,
    -0.096622558429319966, -0.114902783239511, -0.13438849800321059,
    -0.15648836529379839, -0.18317033360322379, -0.21702563513209219,
    -0.26133154922488888, -0.31933373201966753, -0.39549628969231759,
    -0.49521666811130388, -0.62447389653132335, -0.78915433133940982,
    -0.98976332623982743, -1.2272442508217061, -1.4979128779587461,
    -1.798299514010725, -2.144095379149479, -0.335328584376955,
    -0.40704439825105, -0.42771128570138661, -0.4470026909764257,
    -0.46643819552433169, -0.48712570785178222, -0.51053353253768885,
    -0.538651574912485, -0.57408514380626618, -0.62007788386109985,
    -0.67900511820508225, -0.75543599785687421, -0.85505431532163723,
    -0.98375671865894965, -1.1466414756374379, -1.343237852517279,
    -1.57481166128198, -1.8381949846339141, -2.1316217096594761,
    -2.4725931714301672, -0.71280087225539557, -0.7877097976859897,
    -0.81104656654698548, -0.8318283082331871, -0.85257879764538791,
    -0.87461856399408089, -0.89947948970640645, -0.92918789015980663,
    -0.96636164256083357, -1.0141094545650531, -1.074012231408348,
    -1.1506500559489681, -1.250042617814217, -1.37795019771812,
    -1.5385938239492321, -1.730843641221373, -1.956006992508067,
    -2.2116799121900161, -2.4980694484143151, -2.834003330249883,
    -1.12962589711839, -1.201597781073481, -1.2277054565919809,
    -1.2500902703662711, -1.2722593837446941, -1.2957533841676749,
    -1.322185954082699, -1.35362237794408, -1.3926786575880969,
    -1.442209006054026, -1.5031404738338221, -1.5799696243757251,
    -1.6790061981537909, -1.805859657700386, -1.963840591909821,
    -2.151418412184718, -2.3697954236414409, -2.61749797497971,
    -2.89689866634002, -3.227622424700384, -1.580141124087858, -1.64794555004887,
    -1.6768438187032, -1.7009457614014289, -1.724644689810567,
    -1.749708288234777, -1.7778437079823419, -1.8111524870402289,
    -1.852219382662359, -1.903536580938388, -1.96553481086879,
    -2.042549181150545, -2.1411122995971912, -2.2666141102379571,
    -2.4215495957601552, -2.604154577645811, -2.8154660171667878,
    -3.0550974591535032, -3.3276201365966971, -3.6530141333407409,
    -2.0626908016266738, -2.1259982137669522, -2.1576117440724989,
    -2.1835415346311282, -2.2088904796808331, -2.2356501891734739,
    -2.2656244337029512, -2.3009454435757, -2.3441215517614271,
    -2.3972133637985018, -2.4603043360327361, -2.537521665846072,
    -2.6354795072238129, -2.759330352117773, -2.9108681726631889,
    -3.0882376790549881, -3.2923349148724319, -3.52393692540404,
    -3.7897528054706129, -4.1097175755379087, -2.5761930934519151,
    -2.6350061251938151, -2.669163004195767, -2.697016022689255,
    -2.7241378359371708, -2.7527233145723242, -2.784665599679216,
    -2.822123293198767, -2.8674713940569321, -2.922307055920514,
    -2.9865017596634549, -3.0639392391406228, -3.161173203324855,
    -3.283089065220083, -3.4309282572259039, -3.60285677288178,
    -3.7997083793179018, -4.0234774323790869, -4.2827999048403376,
    -4.5972587481496214, -3.11970571652335, -3.1742181649443131,
    -3.210664242444849, -3.2405104766598649, -3.2695194146721178,
    -3.3000497849265, -3.3340799428877248, -3.3737693065600789,
    -3.42130642858442, -3.4778414914318132, -3.5431315461801649,
    -3.620806188558189, -3.717207612901213, -3.836943473610456,
    -3.980847993822024, -4.1472150156261636, -4.336919062167544,
    -4.5531637070850319, -4.8062507325584756, -5.1151350380775957,
    -3.6923418999691142, -3.7428759265558269, -3.781299424325911,
    -3.81317597218218, -3.844162702467397, -3.8767399840721781,
    -3.9129471960270492, -3.954919793936035, -4.0046160821244747,
    -4.0627916783321556, -4.129155378537936, -4.2070753814341568,
    -4.3025655069021314, -4.4199220560253529, -4.5597406643871823,
    -4.7205121626180544, -4.9032984150221344, -5.1124515200245106,
    -7.3110580334039961, -18.70191398168928, -4.2932463027437384,
    -4.340211667693862, -4.3802738156382031, -4.4141746597856377,
    -4.447203456117629, -4.4818922551389511, -4.5203258317343193,
    -4.5645792637448626, -4.6163641984730024, -4.6760939401869646,
    -4.7434920828896843, -4.821655177952433, -4.9161756613166094,
    -5.0310362605388148, -5.1667081453992356, -5.321976179213487,
    -13.22316018374989, -24.728044463674959, -42.389915556078087,
    -42.389915556078087, -4.9215869452701337, -4.9654487161688152,
    -5.0068129008774687, -5.0426884449041811, -5.0777742277952136,
    -5.1145985748623879, -5.155252738084382, -5.2017244311713373,
    -5.2554755821099342, -5.31665523363048, -5.3850359327639143,
    -5.4634351156429, -5.5569665228702192, -6.3185160832917946,
    -14.25152375260353, -24.464000732455961, -39.510290212004442,
    -58.878096106969643, -58.878096106969643, -58.878096106969643,
    -5.5765566698943667, -5.6178043437794356, -5.660160314299933,
    -5.6979121919394444, -5.7350232178893554, -5.7739455058921152,
    -5.8167477559726963, -5.865310347325388, -5.920856209600899,
    -5.983359008787863, -6.0526492070357829, -6.1312755979633966,
    -12.70138804749519, -21.056109704487671, -32.406309085030387,
    -52.648780983011477, -52.648780983011477, -52.648780983011477,
    -52.648780983011477, -52.648780983011477, -6.2573590584253553,
    -6.2964910688209574, -6.3395707776665384, -6.379063498266647,
    -6.4181016725981772, -6.4590194268636134, -6.5038241118701512,
    -6.554276444209691, -6.6113996902445926, -6.67506797665565,
    -10.234186753592629, -16.820325658900021, -25.220570531150621,
    -37.183825724016742, -60.1700268348775, -60.1700268348775, -60.1700268348775,
    -60.1700268348775, -60.1700268348775, -60.1700268348775, -6.9632096349766419,
    -7.0007216991311534, -7.044311558240504, -7.0853638623714437,
    -7.1261756702028407, -7.1689057318092058, -7.2154873372581809,
    -7.2675599585470314, -7.88755472439142, -12.93705918932943,
    -19.208034002066459, -27.34734676370142, -39.007736864750932,
    -60.7569729168207, -60.7569729168207, -60.7569729168207, -60.7569729168207,
    -60.7569729168207, -60.7569729168207, -60.7569729168207, -7.693333580279659,
    -7.7297068404673608, -7.7736413242619626, -7.81604404343267,
    -7.8584099425937719, -7.9026965415560291, -7.9507467079412644,
    -9.9562158494037973, -14.584152998678171, -20.3784577719331,
    -27.922158737907061, -38.636946802250037, -59.853901316845167,
    -59.853901316845167, -59.853901316845167, -59.853901316845167,
    -59.853901316845167, -59.853901316845167, -59.853901316845167,
    -59.853901316845167, -8.4469468352008157, -8.4826526455459721,
    -8.52682096087836, -8.5703365667391118, -8.6139742662720824,
    -8.6594851483848849, -11.4138709598094, -15.53452872169262,
    -20.730672506690919, -27.481088043381209, -36.9057794542617,
    -54.060947387934071, -54.060947387934071, -54.060947387934071,
    -54.060947387934071, -54.060947387934071, -54.060947387934071,
    -54.060947387934071, -54.060947387934071, -54.060947387934071,
    -9.2232562937451235, -9.2587523518605153, -9.3030878085891366,
    -9.3474627349197625, -9.7440927605718528, -12.52085848052328,
    -16.089992395563481, -20.641059332652159, -26.524180050944778,
    -34.529881267505658, -47.374737873288019, -47.374737873288019,
    -47.374737873288019, -47.374737873288019, -47.374737873288019,
    -47.374737873288019, -47.374737873288019, -47.374737873288019,
    -47.374737873288019, -47.374737873288019, -10.02144577234524,
    -10.0571815120562, -10.10166490737879, -11.24084825675711,
    -13.482230868517361, -16.465078370299761, -20.345367345299241,
    -25.366106293496451, -32.111125026289578, -42.017288161196483,
    -61.523318732212488, -61.523318732212488, -61.523318732212488,
    -61.523318732212488, -61.523318732212488, -61.523318732212488,
    -61.523318732212488, -61.523318732212488, -61.523318732212488,
    -61.523318732212488, -11.28144328240055, -11.73093981783215,
    -12.778300968402981, -14.460511153707341, -16.8470734002335,
    -20.04352781932063, -24.26025964434676, -29.861172143172169,
    -37.669164987662427, -51.20652673126655, -51.20652673126655,
    -51.20652673126655, -51.20652673126655, -51.20652673126655,
    -51.20652673126655, -51.20652673126655, -51.20652673126655,
    -51.20652673126655, -51.20652673126655, -51.20652673126655,
    -14.020266190868419, -14.48728991608888, -15.58661980035845,
    -17.362848701848161, -19.89555300085242, -23.331463307561911,
    -27.912255343165079, -34.169390631636048, -43.569351092236971,
    -43.569351092236971, -43.569351092236971, -43.569351092236971,
    -43.569351092236971, -43.569351092236971, -43.569351092236971,
    -43.569351092236971, -43.569351092236971, -43.569351092236971,
    -43.569351092236971, -43.569351092236971 },

  /* Expression: EMotor.FEM_data.Id_Mn.x2
   * Referenced by: '<S14>/Id_Mn_LUT'
   */
  { 0.0, 0.1789473684210526, 0.35789473684210532, 0.5368421052631579,
    0.71578947368421053, 0.89473684210526316, 1.073684210526316,
    1.2526315789473681, 1.4315789473684211, 1.610526315789474,
    1.7894736842105261, 1.9684210526315791, 2.147368421052632,
    2.3263157894736839, 2.5052631578947371, 2.6842105263157889,
    2.8631578947368421, 3.0421052631578949, 3.2210526315789481, 3.4 },

  /* Expression: EMotor.FEM_data.Id_Mn.x1
   * Referenced by: '<S14>/Id_Mn_LUT'
   */
  { 1000.0, 8842.105263157895, 16684.21052631579, 24526.315789473691,
    32368.42105263158, 40210.526315789473, 48052.631578947367,
    55894.736842105267, 63736.84210526316, 71578.947368421053,
    79421.052631578947, 87263.15789473684, 95105.263157894748, 102947.3684210526,
    110789.4736842105, 118631.5789473684, 126473.68421052631, 134315.78947368421,
    142157.89473684211, 150000.0 },

  /* Expression: 0
   * Referenced by: '<S14>/Constant13'
   */
  0.0,

  /* Expression: 15e3
   * Referenced by: '<S14>/Switch2'
   */
  15000.0,

  /* Expression: 0
   * Referenced by: '<S14>/IdRefZero1'
   */
  0.0,

  /* Expression: [0 0]
   * Referenced by: '<S14>/IdqRefZero'
   */
  { 0.0, 0.0 },

  /* Expression: EMotor.par.k_T.z
   * Referenced by: '<S14>/RMS Torque constant'
   */
  0.045675499832195113,

  /* Expression: sqrt(2)
   * Referenced by: '<S14>/Gain2'
   */
  1.4142135623730951,

  /* Expression: 0
   * Referenced by: '<S14>/limit T1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S61>/Switch2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S14>/Unit Delay'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S14>/Switch1'
   */
  0.0,

  /* Expression: 0.0001
   * Referenced by: '<S14>/Constant3'
   */
  0.0001,

  /* Expression: 1
   * Referenced by: '<S14>/dummy_gain5'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S14>/dummy_gain1'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S14>/dummy_gain3'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S14>/dummy_gain2'
   */
  1.0,

  /* Expression: [0;0;0]
   * Referenced by: '<S2>/Null'
   */
  { 0.0, 0.0, 0.0 },

  /* Expression: 0
   * Referenced by: '<S32>/Zero'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S2>/Constant'
   */
  1.0,

  /* Expression: 2*pi
   * Referenced by: '<S66>/Gain1'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S66>/Constant1'
   */
  0.0,

  /* Computed Parameter: DutyCycles_OUT_Y0
   * Referenced by: '<S2>/DutyCycles_OUT'
   */
  0.0,

  /* Computed Parameter: ModInd_Y0
   * Referenced by: '<S2>/ModInd'
   */
  0.0,

  /* Computed Parameter: Idq_Y0
   * Referenced by: '<S2>/Idq'
   */
  0.0,

  /* Computed Parameter: w_el_Y0
   * Referenced by: '<S2>/w_el'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S8>/Constant'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S54>/Constant'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S60>/Constant'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S2>/Switch1'
   */
  0.0,

  /* Expression: [1-0.995]
   * Referenced by: '<S15>/Discrete Transfer Fcn'
   */
  0.0050000000000000044,

  /* Expression: [1 -0.995]
   * Referenced by: '<S15>/Discrete Transfer Fcn'
   */
  { 1.0, -0.995 },

  /* Expression: 0
   * Referenced by: '<S15>/Discrete Transfer Fcn'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S15>/f_2_w_el'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S66>/Unit Delay'
   */
  0.0,

  /* Expression: [1 -0.5 -0.5;0 sqrt(3)/2 -sqrt(3)/2]*2/3
   * Referenced by: '<S30>/TrafoMatrix uvw->alphabeta'
   */
  { 0.66666666666666663, 0.0, -0.33333333333333331, 0.57735026918962573,
    -0.33333333333333331, -0.57735026918962573 },

  /* Expression: 1
   * Referenced by: '<S46>/Constant2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S46>/Unit Delay'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S49>/Constant2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S49>/Unit Delay'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S5>/ResolverOffsetLimitation'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S5>/ResolverOffsetLimitation'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S17>/Switch_Phi'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S18>/Unit Delay'
   */
  0.0,

  /* Expression: [1 -1]
   * Referenced by: '<S19>/Discrete Transfer Fcn'
   */
  { 1.0, -1.0 },

  /* Expression: [1 0]
   * Referenced by: '<S19>/Discrete Transfer Fcn'
   */
  { 1.0, 0.0 },

  /* Expression: 0
   * Referenced by: '<S19>/Discrete Transfer Fcn'
   */
  0.0,

  /* Expression: 3/2*pi
   * Referenced by: '<S19>/Constant'
   */
  4.71238898038469,

  /* Expression: 1/2*pi
   * Referenced by: '<S19>/Constant1'
   */
  1.5707963267948966,

  /* Expression: pi
   * Referenced by: '<S19>/Constant2'
   */
  3.1415926535897931,

  /* Expression: [1 -1]
   * Referenced by: '<S19>/Discrete Transfer Fcn1'
   */
  { 1.0, -1.0 },

  /* Expression: [1 0]
   * Referenced by: '<S19>/Discrete Transfer Fcn1'
   */
  { 1.0, 0.0 },

  /* Expression: 0
   * Referenced by: '<S19>/Discrete Transfer Fcn1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S4>/Switch2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S4>/Switch'
   */
  0.0,

  /* Expression: pi/2
   * Referenced by: '<S4>/Constant'
   */
  1.5707963267948966,

  /* Expression: 2*pi
   * Referenced by: '<S16>/Switch2'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S16>/Switch1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S26>/Unit Delay'
   */
  0.0,

  /* Expression: -pi
   * Referenced by: '<S26>/Constant3'
   */
  -3.1415926535897931,

  /* Expression: pi
   * Referenced by: '<S26>/Constant1'
   */
  3.1415926535897931,

  /* Expression: 0
   * Referenced by: '<S23>/Unit Delay3'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S24>/Switch1'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S24>/Switch2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S45>/Unit Delay'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S48>/Constant2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S48>/Unit Delay'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S32>/IntegDelay1'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S25>/Switch1'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S25>/Switch2'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S38>/Gain1'
   */
  1.0,

  /* Expression: -0.5
   * Referenced by: '<S38>/Gain3'
   */
  -0.5,

  /* Expression: sqrt(3)/2
   * Referenced by: '<S38>/Gain4'
   */
  0.8660254037844386,

  /* Expression: 1
   * Referenced by: '<S38>/Gain2'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S38>/Gain5'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S9>/avoid_div_by_0'
   */
  1.0,

  /* Expression: 2
   * Referenced by: '<S9>/U_DC_half'
   */
  2.0,

  /* Expression: 0
   * Referenced by: '<S9>/Switch'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S35>/Saturation'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S35>/Saturation'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S3>/AKS_Switch'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S20>/Unit Delay1'
   */
  0.0,

  /* Expression: 0.5
   * Referenced by: '<S20>/Switch4'
   */
  0.5,

  /* Expression: 0
   * Referenced by: '<S20>/Unit Delay'
   */
  0.0,

  /* Expression: 0.5
   * Referenced by: '<S20>/Switch3'
   */
  0.5,

  /* Expression: [0,0]
   * Referenced by: '<S32>/Zero1'
   */
  { 0.0, 0.0 },

  /* Expression: 1
   * Referenced by: '<S9>/Gain1'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S35>/Gain1'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S35>/Gain2'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S35>/Gain3'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S5>/dummy_gain2'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S32>/dummy'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S32>/dummy1'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S6>/PsiReduceGain3'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S6>/PsiReduceGain4'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S41>/Constant2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S41>/Unit Delay'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S41>/Switch'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S30>/Discrete FIR Filter 20th order1'
   */
  0.0,

  /* Expression: 1/20*[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]
   * Referenced by: '<S30>/Discrete FIR Filter 20th order1'
   */
  { 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05,
    0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05 },

  /* Expression: 1
   * Referenced by: '<S30>/Gain6'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S30>/Gain1'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S30>/Discrete FIR Filter 20th order'
   */
  0.0,

  /* Expression: 1/20*[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]
   * Referenced by: '<S30>/Discrete FIR Filter 20th order'
   */
  { 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05,
    0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05 },

  /* Expression: 1
   * Referenced by: '<S30>/Gain5'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S30>/Gain'
   */
  1.0,

  /* Expression: 2*pi
   * Referenced by: '<S45>/Switch'
   */
  6.2831853071795862,

  /* Expression: 1
   * Referenced by: '<S5>/dummy_gain4'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S5>/dummy_gain1'
   */
  1.0,

  /* Expression: 2
   * Referenced by: '<S23>/Gain'
   */
  2.0,

  /* Expression: 0
   * Referenced by: '<S28>/Unit Delay1'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S5>/dummy_gain5'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S18>/Constant'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S4>/Gain2'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S4>/Gain3'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S4>/Gain4'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S5>/dummy_gain'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S46>/Switch'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S66>/Switch'
   */
  6.2831853071795862,

  /* Expression: 1
   * Referenced by: '<S30>/Gain2'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S30>/Gain3'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S30>/Gain4'
   */
  1.0,

  /* Computed Parameter: Constant5_Value_m
   * Referenced by: '<S35>/Constant5'
   */
  2.0F,

  /* Computed Parameter: Constant4_Value_i
   * Referenced by: '<S35>/Constant4'
   */
  1.0F,

  /* Computed Parameter: Gain1_Gain_m
   * Referenced by: '<S11>/Gain1'
   */
  1.0F,

  /* Computed Parameter: Gain2_Gain_a
   * Referenced by: '<S12>/Gain2'
   */
  1.0F,

  /* Computed Parameter: Gain1_Gain_mo
   * Referenced by: '<S12>/Gain1'
   */
  1.0F,

  /* Computed Parameter: Id_Mn_LUT_maxIndex
   * Referenced by: '<S14>/Id_Mn_LUT'
   */
  { 19U, 19U },

  /* Computed Parameter: Constant2_Value_o
   * Referenced by: '<S11>/Constant2'
   */
  true,

  /* Computed Parameter: Constant1_Value_g
   * Referenced by: '<S11>/Constant1'
   */
  true,

  /* Computed Parameter: Constant3_Value_f
   * Referenced by: '<S12>/Constant3'
   */
  true,

  /* Computed Parameter: Constant1_Value_jr
   * Referenced by: '<S12>/Constant1'
   */
  true,

  /* Computed Parameter: Constant2_Value_j
   * Referenced by: '<S12>/Constant2'
   */
  true,

  /* Computed Parameter: Constant4_Value_c
   * Referenced by: '<S12>/Constant4'
   */
  true,

  /* Computed Parameter: Logic_table
   * Referenced by: '<S58>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_c
   * Referenced by: '<S59>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_k
   * Referenced by: '<S53>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: UnitDelay_InitialCondition_hp
   * Referenced by: '<S44>/Unit Delay'
   */
  true,

  /* Computed Parameter: Logic_table_kz
   * Referenced by: '<S39>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_l
   * Referenced by: '<S40>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: dummy_gain5_Gain_m
   * Referenced by: '<S10>/dummy_gain5'
   */
  128U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
