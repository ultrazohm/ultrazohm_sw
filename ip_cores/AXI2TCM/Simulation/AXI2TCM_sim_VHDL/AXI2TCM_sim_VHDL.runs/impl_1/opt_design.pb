
O
Command: %s
53*	vivadotcl2

opt_design2default:defaultZ4-113h px� 
�
@Attempting to get a license for feature '%s' and/or device '%s'
308*common2"
Implementation2default:default2
xczu9eg2default:defaultZ17-347h px� 
�
0Got license for feature '%s' and/or device '%s'
310*common2"
Implementation2default:default2
xczu9eg2default:defaultZ17-349h px� 
n
,Running DRC as a precondition to command %s
22*	vivadotcl2

opt_design2default:defaultZ4-22h px� 
R

Starting %s Task
103*constraints2
DRC2default:defaultZ18-103h px� 
P
Running DRC with %s threads
24*drc2
22default:defaultZ23-27h px� 
U
DRC finished with %s
272*project2
0 Errors2default:defaultZ1-461h px� 
d
BPlease refer to the DRC report (report_drc) for more information.
274*projectZ1-462h px� 
�

%s
*constraints2p
\Time (s): cpu = 00:00:01 ; elapsed = 00:00:01 . Memory (MB): peak = 1203.789 ; gain = 26.2152default:defaulth px� 
E
%Done setting XDC timing constraints.
35*timingZ38-35h px� 
a

Starting %s Task
103*constraints2&
Logic Optimization2default:defaultZ18-103h px� 
i

Phase %s%s
101*constraints2
1 2default:default2
Retarget2default:defaultZ18-101h px� 
u
)Pushed %s inverter(s) to %s load pin(s).
98*opt2
12default:default2
82default:defaultZ31-138h px� 
K
Retargeted %s cell(s).
49*opt2
02default:defaultZ31-49h px� 
;
&Phase 1 Retarget | Checksum: 0ad1c842
*commonh px� 
�

%s
*constraints2s
_Time (s): cpu = 00:00:01 ; elapsed = 00:00:00.078 . Memory (MB): peak = 1752.480 ; gain = 0.0002default:defaulth px� 
�
.Phase %s created %s cells and removed %s cells267*opt2
Retarget2default:default2
202default:default2
242default:defaultZ31-389h px� 
u

Phase %s%s
101*constraints2
2 2default:default2(
Constant propagation2default:defaultZ18-101h px� 
w
)Pushed %s inverter(s) to %s load pin(s).
98*opt2
192default:default2
192default:defaultZ31-138h px� 
G
2Phase 2 Constant propagation | Checksum: 3bd2387a
*commonh px� 
�

%s
*constraints2s
_Time (s): cpu = 00:00:01 ; elapsed = 00:00:00.211 . Memory (MB): peak = 1752.480 ; gain = 0.0002default:defaulth px� 
�
.Phase %s created %s cells and removed %s cells267*opt2(
Constant propagation2default:default2
1002default:default2
3612default:defaultZ31-389h px� 
f

Phase %s%s
101*constraints2
3 2default:default2
Sweep2default:defaultZ18-101h px� 
8
#Phase 3 Sweep | Checksum: 8de9b3e7
*commonh px� 
�

%s
*constraints2s
_Time (s): cpu = 00:00:01 ; elapsed = 00:00:00.388 . Memory (MB): peak = 1752.480 ; gain = 0.0002default:defaulth px� 
�
.Phase %s created %s cells and removed %s cells267*opt2
Sweep2default:default2
02default:default2
4142default:defaultZ31-389h px� 
r

Phase %s%s
101*constraints2
4 2default:default2%
BUFG optimization2default:defaultZ18-101h px� 
D
/Phase 4 BUFG optimization | Checksum: 8de9b3e7
*commonh px� 
�

%s
*constraints2s
_Time (s): cpu = 00:00:01 ; elapsed = 00:00:00.390 . Memory (MB): peak = 1752.480 ; gain = 0.0002default:defaulth px� 
�
.Phase %s created %s cells and removed %s cells267*opt2%
BUFG optimization2default:default2
02default:default2
02default:defaultZ31-389h px� 
|

Phase %s%s
101*constraints2
5 2default:default2/
Shift Register Optimization2default:defaultZ18-101h px� 
N
9Phase 5 Shift Register Optimization | Checksum: 8de9b3e7
*commonh px� 
�

%s
*constraints2s
_Time (s): cpu = 00:00:01 ; elapsed = 00:00:00.392 . Memory (MB): peak = 1752.480 ; gain = 0.0002default:defaulth px� 
�
.Phase %s created %s cells and removed %s cells267*opt2/
Shift Register Optimization2default:default2
02default:default2
02default:defaultZ31-389h px� 
a

Starting %s Task
103*constraints2&
Connectivity Check2default:defaultZ18-103h px� 
�

%s
*constraints2s
_Time (s): cpu = 00:00:00 ; elapsed = 00:00:00.001 . Memory (MB): peak = 1752.480 ; gain = 0.0002default:defaulth px� 
I
4Ending Logic Optimization Task | Checksum: 8de9b3e7
*commonh px� 
�

%s
*constraints2s
_Time (s): cpu = 00:00:01 ; elapsed = 00:00:00.393 . Memory (MB): peak = 1752.480 ; gain = 0.0002default:defaulth px� 
a

Starting %s Task
103*constraints2&
Power Optimization2default:defaultZ18-103h px� 
s
7Will skip clock gating for clocks with period < %s ns.
114*pwropt2
2.002default:defaultZ34-132h px� 
I
4Ending Power Optimization Task | Checksum: afa025ec
*commonh px� 
�

%s
*constraints2s
_Time (s): cpu = 00:00:00 ; elapsed = 00:00:00.007 . Memory (MB): peak = 1752.480 ; gain = 0.0002default:defaulth px� 
Z
Releasing license: %s
83*common2"
Implementation2default:defaultZ17-83h px� 
�
G%s Infos, %s Warnings, %s Critical Warnings and %s Errors encountered.
28*	vivadotcl2
272default:default2
02default:default2
02default:default2
02default:defaultZ4-41h px� 
\
%s completed successfully
29*	vivadotcl2

opt_design2default:defaultZ4-42h px� 
�
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2 
opt_design: 2default:default2
00:00:102default:default2
00:00:102default:default2
1752.4802default:default2
574.9412default:defaultZ17-268h px� 
�
 The %s '%s' has been generated.
621*common2

checkpoint2default:default2p
\C:/XilinxEyke/MPSOC/007_AXI_TCM/AXI2TCM_sim/AXI2TCM_sim.runs/impl_1/design_1_wrapper_opt.dcp2default:defaultZ17-1381h px� 
�
%s4*runtcl2�
�Executing : report_drc -file design_1_wrapper_drc_opted.rpt -pb design_1_wrapper_drc_opted.pb -rpx design_1_wrapper_drc_opted.rpx
2default:defaulth px� 
�
Command: %s
53*	vivadotcl2�
ureport_drc -file design_1_wrapper_drc_opted.rpt -pb design_1_wrapper_drc_opted.pb -rpx design_1_wrapper_drc_opted.rpx2default:defaultZ4-113h px� 
>
IP Catalog is up to date.1232*coregenZ19-1839h px� 
P
Running DRC with %s threads
24*drc2
22default:defaultZ23-27h px� 
�
#The results of DRC are in file %s.
168*coretcl2�
bC:/XilinxEyke/MPSOC/007_AXI_TCM/AXI2TCM_sim/AXI2TCM_sim.runs/impl_1/design_1_wrapper_drc_opted.rptbC:/XilinxEyke/MPSOC/007_AXI_TCM/AXI2TCM_sim/AXI2TCM_sim.runs/impl_1/design_1_wrapper_drc_opted.rpt2default:default8Z2-168h px� 
\
%s completed successfully
29*	vivadotcl2

report_drc2default:defaultZ4-42h px� 


End Record