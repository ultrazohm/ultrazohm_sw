// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
// Date        : Thu Mar 11 12:58:08 2021
// Host        : ws-wendt running 64-bit Ubuntu 20.04.2 LTS
// Command     : write_verilog -force -mode funcsim
//               /home/thilo/ultrazohm/ultrazohm_sw/ip_cores/ADC_LVDS_LTC2311_3.0/hdl/ip/xbip_multadd_0/xbip_multadd_0_sim_netlist.v
// Design      : xbip_multadd_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu9eg-ffvc900-1-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "xbip_multadd_0,xbip_multadd_v3_0_15,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* x_core_info = "xbip_multadd_v3_0_15,Vivado 2020.1" *) 
(* NotValidForBitStream *)
module xbip_multadd_0
   (CLK,
    CE,
    SCLR,
    A,
    B,
    C,
    SUBTRACT,
    P,
    PCOUT);
  (* x_interface_info = "xilinx.com:signal:clock:1.0 clk_intf CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME clk_intf, ASSOCIATED_BUSIF pcout_intf:p_intf:subtract_intf:pcin_intf:c_intf:b_intf:a_intf, ASSOCIATED_RESET SCLR, ASSOCIATED_CLKEN CE, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, INSERT_VIP 0" *) input CLK;
  (* x_interface_info = "xilinx.com:signal:clockenable:1.0 ce_intf CE" *) (* x_interface_parameter = "XIL_INTERFACENAME ce_intf, POLARITY ACTIVE_HIGH" *) input CE;
  (* x_interface_info = "xilinx.com:signal:reset:1.0 sclr_intf RST" *) (* x_interface_parameter = "XIL_INTERFACENAME sclr_intf, POLARITY ACTIVE_HIGH, INSERT_VIP 0" *) input SCLR;
  (* x_interface_info = "xilinx.com:signal:data:1.0 a_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME a_intf, LAYERED_METADATA undef" *) input [15:0]A;
  (* x_interface_info = "xilinx.com:signal:data:1.0 b_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME b_intf, LAYERED_METADATA undef" *) input [15:0]B;
  (* x_interface_info = "xilinx.com:signal:data:1.0 c_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME c_intf, LAYERED_METADATA undef" *) input [31:0]C;
  (* x_interface_info = "xilinx.com:signal:data:1.0 subtract_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME subtract_intf, LAYERED_METADATA undef" *) input SUBTRACT;
  (* x_interface_info = "xilinx.com:signal:data:1.0 p_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME p_intf, LAYERED_METADATA undef" *) output [47:0]P;
  (* x_interface_info = "xilinx.com:signal:data:1.0 pcout_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME pcout_intf, LAYERED_METADATA undef" *) output [47:0]PCOUT;

  wire [15:0]A;
  wire [15:0]B;
  wire [31:0]C;
  wire CE;
  wire CLK;
  wire [47:0]P;
  wire [47:0]PCOUT;
  wire SCLR;
  wire SUBTRACT;

  (* C_AB_LATENCY = "-1" *) 
  (* C_A_TYPE = "1" *) 
  (* C_A_WIDTH = "16" *) 
  (* C_B_TYPE = "0" *) 
  (* C_B_WIDTH = "16" *) 
  (* C_CE_OVERRIDES_SCLR = "0" *) 
  (* C_C_LATENCY = "-1" *) 
  (* C_C_TYPE = "0" *) 
  (* C_C_WIDTH = "32" *) 
  (* C_OUT_HIGH = "47" *) 
  (* C_OUT_LOW = "0" *) 
  (* C_TEST_CORE = "0" *) 
  (* C_USE_PCIN = "0" *) 
  (* C_VERBOSITY = "0" *) 
  (* C_XDEVICEFAMILY = "zynquplus" *) 
  (* KEEP_HIERARCHY = "soft" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  xbip_multadd_0_xbip_multadd_v3_0_15 U0
       (.A(A),
        .B(B),
        .C(C),
        .CE(CE),
        .CLK(CLK),
        .P(P),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(PCOUT),
        .SCLR(SCLR),
        .SUBTRACT(SUBTRACT));
endmodule

(* C_AB_LATENCY = "-1" *) (* C_A_TYPE = "1" *) (* C_A_WIDTH = "16" *) 
(* C_B_TYPE = "0" *) (* C_B_WIDTH = "16" *) (* C_CE_OVERRIDES_SCLR = "0" *) 
(* C_C_LATENCY = "-1" *) (* C_C_TYPE = "0" *) (* C_C_WIDTH = "32" *) 
(* C_OUT_HIGH = "47" *) (* C_OUT_LOW = "0" *) (* C_TEST_CORE = "0" *) 
(* C_USE_PCIN = "0" *) (* C_VERBOSITY = "0" *) (* C_XDEVICEFAMILY = "zynquplus" *) 
(* ORIG_REF_NAME = "xbip_multadd_v3_0_15" *) (* downgradeipidentifiedwarnings = "yes" *) 
module xbip_multadd_0_xbip_multadd_v3_0_15
   (CLK,
    CE,
    SCLR,
    A,
    B,
    C,
    PCIN,
    SUBTRACT,
    P,
    PCOUT);
  input CLK;
  input CE;
  input SCLR;
  input [15:0]A;
  input [15:0]B;
  input [31:0]C;
  input [47:0]PCIN;
  input SUBTRACT;
  output [47:0]P;
  output [47:0]PCOUT;

  wire [15:0]A;
  wire [15:0]B;
  wire [31:0]C;
  wire CE;
  wire CLK;
  wire [47:0]P;
  wire [47:0]PCOUT;
  wire SCLR;
  wire SUBTRACT;

  (* C_AB_LATENCY = "-1" *) 
  (* C_A_TYPE = "1" *) 
  (* C_A_WIDTH = "16" *) 
  (* C_B_TYPE = "0" *) 
  (* C_B_WIDTH = "16" *) 
  (* C_CE_OVERRIDES_SCLR = "0" *) 
  (* C_C_LATENCY = "-1" *) 
  (* C_C_TYPE = "0" *) 
  (* C_C_WIDTH = "32" *) 
  (* C_OUT_HIGH = "47" *) 
  (* C_OUT_LOW = "0" *) 
  (* C_TEST_CORE = "0" *) 
  (* C_USE_PCIN = "0" *) 
  (* C_VERBOSITY = "0" *) 
  (* C_XDEVICEFAMILY = "zynquplus" *) 
  (* KEEP_HIERARCHY = "soft" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  xbip_multadd_0_xbip_multadd_v3_0_15_viv i_synth
       (.A(A),
        .B(B),
        .C(C),
        .CE(CE),
        .CLK(CLK),
        .P(P),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(PCOUT),
        .SCLR(SCLR),
        .SUBTRACT(SUBTRACT));
endmodule
`pragma protect begin_protected
`pragma protect version = 1
`pragma protect encrypt_agent = "XILINX"
`pragma protect encrypt_agent_info = "Xilinx Encryption Tool 2020.1"
`pragma protect key_keyowner="Cadence Design Systems.", key_keyname="cds_rsa_key", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=64)
`pragma protect key_block
oPPBmdjVxxQgYqTPHO0IY5hg5KMAb7EBJLCGgBUYq08ZIfUX8ndg1Eiqv2dFWIRo3mt/OQsTLY1S
ZPHug+wO0Q==

`pragma protect key_keyowner="Synopsys", key_keyname="SNPS-VCS-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
O2N1mQ5zhVgmtFXaAPAwvL2k+ycbd56UvLowFGIBaAOuFgVryTcW6hBGXBBEB58r47F2cJUl+V8q
5v9YWBAXGFm9aknUEJ9zcXZ4EK1EA/Xir5blfta+j8IxsqdLQpqab63J0gxmbaWuaxJpIStQqP1Z
UWOQgzSjIOuaLpp76p8=

`pragma protect key_keyowner="Aldec", key_keyname="ALDEC15_001", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
jB0psSt7+yYPqTjcOfKqfOAZTSTbCNlMvEm4VRZHWBSrXg/D5x+6oQxJ1MwXCyNvW46g+Yfm+XHf
9jJJhsIkBuaYAfEngj9iV2PbYubWLfBOSPjs3QRn8FqFW1MpRAGv4oKgvT2aMG+xhmcZtQ82QBuC
GUVBztfbA0dd7AcqiPG5peJOZ5iMr1U10duOTfrQ8HUSuwInNflbZtqZNLGpTVHBlZhhO0jxCdDY
QOqm37/9z+sZElWCbTfdarzEPwccjoUl8e6y6aAcGCdRcmgusSci0/D431QlyEBCAAxGK3JvZUsF
Kf8WzBvr2W19eun24XFvpfhgC89d/VhubWD9ww==

`pragma protect key_keyowner="ATRENTA", key_keyname="ATR-SG-2015-RSA-3", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
qwh+XXGxTUHeH6kldJdH/ZfvLKe0buzXRPKSUak+BQq54vBafi6lJqg1V89dBIPQ64RZRn3a3rfP
vwblASDB7ynllBzhkNR/JYkNLwtiLB1fx9ZrxFbLouaDHdLgonLMMk9paLYLIwjESipPNB1Tjj97
wLv5OFCvFygRFJWC7V8ql0Xn0fWEEL2H85xNLtC/Vx6zvcY06Tc4pOhBA14Yg1IX2ci7GBFaEBR9
UKM82IYIAVjwz3iJvEH/Fh7OLv7rRifYGVUfW1LuJ0OnkfzWNrYM4FMvVaECIsP8jLWraVLHygHM
Rjs4eFfc0edJpZvFaoZaDmoDBJOzj/8spqqnJg==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VELOCE-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
iQ4VmTylxQ1J2QyAZBzI4TSDIFkbArdLXWKz2YLqq6D2esS5w7IJDG77FiV7khPlE8o4RqFia3zt
GYntd1KVZWz9whLaXoFmIXMQ+C0HInJ6Ow9f2OkRx3Jo/y9KfvLGQhCytDaLe/G7KLItsx1emkO9
r230p0iDzCX0NcTRap0=

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VERIF-SIM-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
Jo1LukfQIZ4+tL1i3tj2SLJ5Cqfg6q6cJeJzw7zeVbbkSXANWzMqU362P0kfRQC3BGVOWZqYRmzt
ifxxiGgZz+mOCMKE5GSqji7V9P2o3LYOSdO34vFQNTcS0angvb90zmZCmUeHtmgAYHyjsHhKE6uE
4TMqy4wjwc1P2phyK3+Dn5zywq61/02+3eHpeYL3aRAD7qFg2AbcLUznHcGd9BSMiEZE6z0ZyB6f
2RgDLBp2oPqo7vJC/maqM0R5/7GCoiGIoBFq60cKtD7kAUeeyuRGPZuR4o/5/dIRswF0ovMHb1gY
PhuJJQbP+26afzCpMTaZtHwB9wiic+zyKlA+KQ==

`pragma protect key_keyowner="Real Intent", key_keyname="RI-RSA-KEY-1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
NxUc//wt4b27/ZO3BT+IO7PjgX2k0SdQl3fxsCqQfrEJyp5zqNZTLNox5mxgtWiAtYlLryJstwEv
V5khBk4tQA9ybob6ETgBp3es9fmkcoJ0kFo7kAbiGupx94zUU06hNpW3yh+nT7HnEEUivdALUanI
N8oiclpWdq67XI1baxM1nc2hvgfbF7oD6uo8/S2RP+r7wYuH+LGIsDpEinNSefF8q4pxiTuQ1JWI
Hnkq0gP49gNBxQAE8HAUL3HdFqmLyvqM1+h2YveplFRw/YWVj9rRoWjogoypIsR28DBIgG0kZSv2
0LaFz1+uxGCUqeUHl2O8MiM4bnFB0Eu53WUeCg==

`pragma protect key_keyowner="Xilinx", key_keyname="xilinxt_2019_11", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
T247l9ZTWcyAfNCDFW6sINHv9gSjVxvdQgjd3+yL66BsCz+N8y+fBh8/bJq+a3LvMUEZislY+RAz
m6IsvWzXAJZ+nJR1T33Ze1V/0A/hg4SjgiCI4FxB1scShneaAdiEp/17LmoN5LFdjo/OfpqG8CsG
Jx/8KePeXWJxRYZETm/DfttXqTX5n5SA7cKpB8ytqTiP5CLO4ahI71k24YFbUK4U0GhVB7QJ57IL
xhTg5fdqqfZRp53EQ/9ytrea0iwurfDDiE5v7YzXY4yCUo3P4qS4rEkFC/MallqMX+z4E4lCgL1w
GBcooqZKVw0PNLyHcjrxBhjse0+BHOEByIQOHg==

`pragma protect key_keyowner="Metrics Technologies Inc.", key_keyname="DSim", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
qoIFn8X5jnle3ONbIM699hZ2OBgRp5157ijj0xig7Li8V5roRXokRqYy/Ov5omTosQi8NWzwI2sL
+nGmt4ethMuzhVJgMKoik+tUMO1dc5UgT4Jm2JYXNyWXZS5r8OaNijEUK+OZpLKB5cedP8Tk3BuL
u1adICr8cQk4ndopmzmyDg/Ro9PekMV8QlkHXD3ouu4eQPraoUz2q38AznNUCMq3IHdgL/4Ba9mm
IKEE8k58KfSus/tB60qoN920bxYvqe2EpSheFs69Pq8PA/4NTDcvffptGVpuIyO9Wz/QYDbRoMMn
Q1mAFHt9t6szp1TyfqEzH7a9ok7IjQbSCXnMRg==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-PREC-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
jvYGGGCIBOB7aaAcywXW7JBhIAKyqTT8E4z9bE+20XEiJrfZEwr8wgX19e1reodL5eArIKMmHjqq
pGhrk8kSWmNexLmGyYnPrQ0afuzsfcOyyTQxLgrXZjsqYtX4JZlIv4nJDPudVkyXye4uMZT5pfLB
lcFrlgB8zLfef+BvP3d8FVxSuxpJWimrEIbU6Y4rgdDl2H9NAbANbrX/jTF1K6krvws3KCkIOn5P
lfVo1kYQygmNFsNhwP/E/goc7R670wYo2oUrQdlrxcbqtMh5JbEsZd3dTJXsuq843uTVKozGFwew
iLSo02DHv76n8opdPee6CziFmcO3wXqOahd9vg==

`pragma protect key_keyowner="Synplicity", key_keyname="SYNP15_1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
NcZ0n6ynEgXs1P/Yejy3/w9hp+o3NA4u6byDGSOTx/HV2gweAu5VGpcXEgfNB0RTxLLhf1AXhzl6
C8aVHeDQnP/ytx8pdxeUM/VZEKoxoTkV54WiATHxW7e0BuJc3DZwOKcWel+RE/qxlph/VjZtNd6K
/JTfgGEP45OwX/kGSLw6Nk4wg+nHrOBtRxYNFY69oDrBBqVtScWztDsRQf0qx3eKHPAWuTqhlmlZ
II7SeWrvy5UhPPEfK44sSmKhMTmwhCT6ACMspje8Ayt4aOxbLUL9sE+azSKxb+8Fx8ZXq8JUkPHZ
i5gv8d2/0+vFYtg1Eh+8EpcQ15umVbPoBQr9Qg==

`pragma protect data_method = "AES128-CBC"
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 10112)
`pragma protect data_block
NzihhIbBBHrTjBSgIG0NDebPJn6DGJWHOygS/kSlhcVo5fy2yO77r6PddvMSdFnHqkHl+rPsgz4r
5rM5YM3aMWkz3kx0JBVIwe2TbIMc/3Xv8M40QIp+31io5bpyzcS/OqMgo34Cv2Wxr1NpfAylBX52
Trhr7Vhh5+9tt2jQwJeqiciiBNszOqZZ4O+NwvwCdfXOi3a2u5KJ0T3PBNmhe9dA9N15NY/gNixx
ez+KWeVWVFirAMB2uUAS3Ru0kBizOGz8DeeZQhi+BAPh1/W0R234RTvM62T2ItIqE9gqB1O0O3aW
2dJHvp3sxCcNcmY+2cRwXGeBpdBpBiVe7/UAeTb9a0Ysv/vKF49gmNgEK71r+rJ6GrKYCiPXHblj
apJKba27eCFUZcPB1LCxqeQa8kGAiBdZ9Au0zSPBv3IS4rWOB9qAJM2r4YSbHWHNG86wvelezGzq
0oTF2IOMlNrEUDcGrOfTzGE1ghkoWH5MJ3QalMot7k5eLe50DPLNG6REpBpMRCFmvgp/xoBhxsrT
s5i25sB2f+uY0+THVwbUVjWcx8ONN3+48YNgyhe010hLBmVJr+BDjC6tRYByJyPlAlc0FQSlQ+8t
AIxMbO37yAQLPvMvCIkHBgL1TWK3FctEix4kGGQLhiwS/XrgkfSHSwD98OLlwNNYfj7b6B3Mf6+w
eId37CpXL7Fv+k9GDhpuxaOCNtH7FPZ95OldiGfOM/O2Dmf0jbR/BrjqWH5x6S+99qs5b/2NDbLe
K40vw96sjL1vjWpBglJHmfsCv2CiBwbMS6p1l3FvxN702mbBvftby1XtQZ6eFfk4Uq9hADWAAap1
QyuUC4oHWFfczqXh/dVHma+WjkuHHEujAJrj0+nuHmEchrSLESMrgNYf7i0VwEOp0QJ8+78Suy69
6eYYSqqjKvi4UUwQbiQS/VCN7JT/b4BxudgSnVbx3oTw8r7cVJpsChUL6QJB61jvyDtVK90N+8KG
Y67uG02rbETn+XnapA7W4qSJKuah0F+beOPSRBqVI7Xw4RilBYalpiz2P8OuTM0F+Bv+dEOgZ0I1
1O+/lCf3oT8ZlAUTM6ozcn3w0qx1v5pc/i4/4HTz4KHz1I90TlGCOddRrjCEoTHF3915kBVa9GH1
wScOHeXIuEPNMuIZpkBPzZAXDbJt8wtuIm6ubQBHxDHfKROke/MbNT6xJIYL3Rg/oh1Lj/ziWtAc
RPsMY+ubX0CN4WplZFlZKyV+ojLa4w9ZGZLZJT3z9AAoJfTcobG4cpFYFdwDZ2M0qpxepSw/kZUE
sHOJgJx5etrt4+UTJFGj27ry4AydXpHwkYfYLRsbUailIVaQE4AZoSMsTXC5pdpTkx2DpcHd7oZ3
6/L45e7PS1jnhSUgJeylVzWFK6wYvvD/qVImcbucb3t5lR0Mk6pD6yWEKyjLNmfhYu0X5yPm1O/L
rd+/+lgXM2HtTimQxDaSlh9dgd6kmA8aiof2nkK3OawVNQRQppPkCUnY9n71dG4f3zujENB6mQuD
i1eLYYesh6CqlqNrmogwKjgZoTSNLvE7DT7ezP4oQS1vQ+VAAdgOhzAYEMYut3T7EKRm/3iBBIc8
UkgacOVzchglDQ8IkSpLF5hM4nTu7I6zvPeigJOOR7uNcU3rVL/HxAfvKfrL7x86SGHujwjhYZPW
fMrM/P1Bzn7+WC4SW2e3Hrqfe0QialWr9V8OXJRedkpRfbt/tVT/QQOSoW3tlxXUSkAta/L2fIs8
QgPNE/0P4hrvRMkTfHYBV+fl+1Zi+O/YUTJpb6cOENXI5gIHzuCwhKGSISr6oGWl10VEttdw+X5f
qHzgC5M9OWurkDCJtDekuagRLA2GxE3VqZ12kx6p1q4161FSsVSIgLKKTCwMixDtLWKzR/pmWDlg
NUoAilQeL3ezLGC+AHOTo58xkD5UmycNXqfK687gi4EmvHBv6Sy9nPx2fP+BPfM100ageMDPfKVl
/rEpdoxr7xaaRNnV0f7CX1amRAk4Xq45jiGunldz5fmc3su9N9rNq+2amgNb8UtaLRls1pX+GHf/
IytcctR17vJLJhCsBqEIpxPY72irXJu8ar6VyK/NQGMHLLwx64SUUZ6bRxicqD8XynMO1GiVh0hy
ncA70bWdCeZaC1Vm61HGIY2fLTjK1tL+tPXaw8IFYamWzJxpCtzPi0bWgqrQhniIwbCXeN6mSRpV
nj5xHxSHxfNH3M6RQQvPEBIiciwiwOUKvJw3gCiu+EfnGHWWULbRvJ6lIMEi5R+Ke/JSjeODguGr
8w1MBChI5Izyo9G9zjQ62jn2E8kOW9gIIIOaY0MXpVHsXQn8yibPVF3w3mG+zQ26VCyY2EJ6OJJV
Tf6Qg4P3Ec+OuSnzqDngxjhz9xvl1PEjDz+Q3sDujCgFcKhtIzbOf5xPyZyB8HHPXU4JdhURiZxJ
zb8FqwQCjJRn7KlhbBmbMFdYgfnZLtGd5qwGlJIb5RNrkBczQxXvbPCA8nnhiWOpiCKOorGMWovu
fw6l2+xTySm2w/WaroQ8q5L82FG9g8lN3704TOKGhquTY+wBwpkwcbeoOT6zGFhY6nhISx8j+fXA
jhX9YSSRFkjRyimwv8eScmmftWR7Yzh+iZMXlc+khdRDGq72ijV9vIb79ot7k6mgSJuLSrVnjxr+
PwnfT8XnEZ/NtW5FhtDsWMug+t7AHGB0CtIbdKigO9vWMaYh4AZZC0/7u7Qa4Ocx3ohq9W8y3GfE
KFEO82LjyIRM5QPLM+ywSKYA3LI0vW+PNK4GOI5GtGz7OiGh7ekIwRcQmEfLGx2/+udSc6Plbeow
r0MIVli51O9qVqLMHr4PxONzjWOEbuTuaQ4CJSd8y8+QFVQfmheq0krO1bMc0IHYUbt08XQp7vtq
8mjnFv3278NsGCJ/k3lTIC1CRiefyel1lPhIZNz0zZsvIhK7zQT/IK0S/sHl64G6nel4Mjx0aeZ4
oPQCpnapq6BMT+7cay3U2UU0bhweSchY8fPpWDh3OosteOykTRAtPauCJxriffMm2JC1bkOEVeZi
Kq0wBxakFqzj0a4c/x/OpacnqaLo7OCdgulvR00VYpwEwwU6fzcCgSsOSM/Ya7dqRo51FvOcdIY5
urGjV4tFG4+0wqtSF+9f3R29tmTgyEhvrPc/UjK+Y61gXC83iU76bnEkxoP7IHG+sA76w4gpT81o
mdp+4DFbHNev2Kn967C1b3GZjhZGU8QjXrO8fUuKCTTCalyUiyFCcBUjClpX/xM8Xq+UZLQ1drMD
QlHCCLB/o1sF2FFiFbShyzUwS8+Il3GsPnpi9tUqsT9neYkdFYcSq5TR/YyxpZ4b6mADS3sOCDA4
x4RKmcjjouQheKmDyOTcrOfcct8O5FM6rXxa7YJ4L4Z8NR10PTFroje7ZmtdWQ8jLC8Jv6VlWzb4
tPGi1Gs5SmsjZrUi3bu0tnlwmLivFPYu/wykg1HB8jqEScMoFnkOno2h+fQXfNek1SJlPROwO9Pp
S1Koz1wPPv+Yy/Ad6xfHkZt2kSreLv/frsz07QVzujjTeObrHyB86LgF5zE4xkx8kWNn/YaFiaS9
NpXQHksXVqWiEefUk6Vfr9gMwWwigvfJaq9czUwuOPCwjhIjkzZGH4viKUTF3V28+hj7plgc37Za
68S1VIgTkQQnM+tv2YNOR48rtLx4xiFYZJgPwnVRhY+lpbHRi3hnFfztQiCSF/DoNJfkmyn0zEGA
6z7Wsnr0P1zZPhnd689rsnF9ntr6z/enzvnawbw+ggBzdFTF4dWyvnLDexRl/CrQkme5hqthvxVr
smec7CZkpyqrX8EQ/zP0Wp58+Pgbka/CjQVlbPsRXa8D8JjzTfKbilJhXhvvowOApfc7VnzZttHj
IL6gklJRk81zxxNHgK+y2QNrbJhL6+lOkw551uUik8klJ8WEapxen7L6oiwGRIP64nIl8wGTDmQI
lBICrH3J6zAVb745cUt+lqXM9SQJnxXu3kP0zK7Ng8Xa2D6czQuE7mCuYJHhrk0RbTsJHrldFWQK
+m8QH9Jou05+NFnD5VBYiUnM1Ru+PsX9jeoezHUpZSq2p2I7Hxsm4scdma9Rv8Lm3ka/WHziSOvz
0WHZSC/XqnWWqKwmJBHt+oAulFlWs1iTB/23N8raNN9JycynLfWCRAsuWNeuol8nLAL4aM6VzOK9
lW4DPziSTMg7XmZZTWKq5dcYuGsTAdN0iY9lDuPeXNC9niIkr3Cy+0QoE/nxErrfE+rU+CFuFKZB
qDq6ydDB5cuK1Ss2WvperMAur+C0SSaw1zhovZqJ2HI93anHibpErW4TuyixJHVpEiB8Tcx9C4zz
jVbaSm8mCQSD8inuYneGILcTFMC0dWfl8rnW7Vw6dkL6gPBOHZTDebPX0vOxzutfYJFNRnd/Oqng
4CfiEbqTOMG7m9ioASqbsYFnhp/HFvpdO2bYR0ZeeAktPbWqTh+dkx9Bib0VkEoesH5NbSUh845Z
VwAv4RpyUwqIZabRKBeBIcZKVxFVIc+BihYnbFLPWBltbGYOhtZsIABW3CwvZkbEa0X4Nyqa66vi
qaVQkLyRUGko3anLeLJcBzmcdW46p2EsvVuQJtThdNjcsAs5s7NAXsTsPg2C1pRYhEYKlAa6LNnP
cjTGRPSm3Wi4RScjEoSB9lBQDQJJv949bISg3XbqxbdwzW+4aa76bVt8ZHQPmmcmxsRew+pKtXTe
ogxm4vBM6PCcj0w4+yA1lg0leKmN7RfAoinix4+RYyP8TqlKYCm/H6yVsMf+7muTq7gxtmX9quK8
D/UGk0LDn7fhZV3Izn/TcSB3NQvgtnNKyxy7GlsqhwHyh6cRxCX1foP4I899y99eBMVor0xLM8BT
Se1VyolYEePmwSXA84eMgMzAmup56SSQ14SHZkwk1vJ09b2KdO0kZm3whhxXSjsrODJlmEyYvZ0V
6aKXEBw1f/+ExYOoT6L8Jzg91x41+m3MwvcGHp4dg88CRI17GqrviZNGBLh+Xuq++0qxHaaW8nyn
erKH8dyt20OiSUT86H64gzU/O1bcRzpNfRi1NlYVv/EHYJNIQUFXqxD2J0D5msTv1Oa3SW86WXtr
QnwZoQDlbDTcta0snzslWM48pzUVhpskYgXbNK6gS5nVkPVXpM7n81aUwZx5ItvnjI0Ql04m9Kir
v8K1qVlPeeZq1nNj5/kaiAgWqpn1bTPsbFTb+m5TPuySIyMTEPjnAG7hfsrbAKmFtBOv7JNO0vL0
x8IQ55m3E77+oZvN+cCTsZZqH6WCGYnndz1RhG2WqwuYNVKxOZGdSRa1GOuyiJu2SJ3+dku+ocsF
SQPPBgLEEHBpk7YWFMlY8Ws0x0SdSvkL6E9qjnEVu+hyI6t2IGbAWumSXgU3H2cwqpAr5qrNCiwt
jUph0SaQ60sgf+U0QksK1Pal4W0VFLexJNWFCDscclRsAP03kaVYqmd7wZvLToCvbLZIbx5I9EfL
7MUo976dr4adX527BF8sJW2t2yteVgfhAKxlN0YDUf7l7w+M3ulVq+CGxK9BJe3MeRVYwZmENLdh
UdVFTkEkOffpQ6Aji5y2SFsIy6+tTPUm5/Ivwjr7wcN29F54uzdZoHqwFPydV453pXbT3k/uHbO6
8MOZCd89lr6lFICwAnFzCt+nXArp3YaTL9v7iaWSbiGxkjwOXhFnA71eGOqgcKGx8nmYnlQnejde
xTqj8jG3DQXzLWng9neKnPt/07kVeZqJkvutYIXoSC8miMLRxkcVJO0/RnJ94dhxCMTRaTDvAGSK
fbB+cg3N0Wc5uvTpQBcSjdppvx0VAM1d7UonAG04/PdxQBq4WbTe61XdHqPe/r6MNl+aDnuiYm2A
UBHVR7hDQg/PV2ZBEj0n1/IX1s+Lvbr+gMwzV8Io5hwhVVtm35sJXBrmKW7AM4Z14s7AogSPTXZy
AEEAVyOKttuf33Zv/60AoNcvri3fqEm4QbFYBlRWd85CnOqPpZc6MNtyAqdFTXajZFNRIls3U4Hz
Weo1FsYYIMbZvXAyEHD/OUssRs/3Pv1QxNs8L0q2DJw8ogNgJYjaJFXurjbCBpfXkwvG4Enop1ss
lrfiVEXZhk4OwVJnuoD4BT1QfEsjahyhz68CsTVNQiQmj+CUhY2OO5gSIFfi9JaBr7HLT5s7eAvF
VZ4dKVeU47dEM5gE1Osxcyl6MVjowzYZIicfeOXXj0zIA+un2SL1p0iVsHd/hiNV6HXwfBCdkvY1
Ns+2lnmCNSxMBfCD8Q2BcAUK6JrHN6EbWdmzqSlI/VxpjDrxnGywmIk1ldqD1pkypxnlKbAcRdGR
svyKO/v3BKY3uqjeQz+C7IwPgrKfo5mxw38pGFVQW0wssjAlC21VPk4HVpp0eTYBdD8JYSwwFFiD
S9MJ4jLYfQSV0DK8KXXLXT/YsbuDfTpbp5yD1JtzR4itnYresw3O2WcR7aTgQNzMN0x/U6uOSqv6
/UElOBX3t8tnx8mGvu0a/Imp/CRNwjfb+dQe672AkGR/3lPUJfByGyn1CSTBdbmZ4wVGutgYgWct
bjlKCtHYyaTom6eeIJUW5IWbVUU66aFijC14Cu3mxrHt0YWHwLQLvyY4Oiv33099C7/1eHOB24Nc
1nao02HzhtvtZzYfMZoA3/USKQUT47+cBaqtXd4goHxZlZOIzhaL31d1m062rVnS0ciRMPBWWc5b
RCdhILw4t+/VMyS0hf/+zaQb1ecdRr4ftwPxaU+LuEVc2xi7+Ceb41knBjcI5R75E8NKf100utca
vs/+jryv9FSUB306vUd3RU13DolilkXBsSrzwRcXtc7SvAuH3L2l8HPwAnWcJbrmFxSrEb6rrpb6
W797QrmMfagMExFz7GEMerI2tGgrULWMze/q+2aGKLRrkLXfRK53Nwp3cfAQgyLHuY9606h+3Xx0
/x2tInhNFMe9Be129ieY/QKO5RtvKTBPw0nzV3CV4qihy89M0H0Vp2COJso62FQpiAG81QGB7dj0
BXT8+iEhMm3VK6fBpiFu1xCP+3lMHXInRu5dONghF9AkyURun0RBkDjFFN82RtVG8s9vnzTTWoGY
iuu5yLdUicsuqb8Ak8YkpMqP2WT5Dn8wQxw83YE2RnDhdV96gpq3oJyiNoqNuqvbwaJf7a44sQhS
MuyeW6lQq/97dcckYEUOodLktk35Qm1NM+CAhXeOHcPQ8m4lKQdN3gNmAwKWlD1hypKK5JwKoqgm
4yzNBgoyTaB3uey01M6BzYaSKwqvypOWt+0RJV3g1RHA6D1jdSN3FE2z90YmFT3J69AVgi7awfze
ujixuMySqidTv/fG/4zoPiD5O8LPwawP9LEdNV1ewEUTy3SAKbJ0fXf32bLXwpN4f7t9jENjNCNA
XRuRETJCD7Lh6gR55Hjmn0n+04TMZk/Axwq8PcmbzZxL25BjMp5m8XvhS139tlBiko/t2VDiyRqz
w1xoIv3IOzKQ3GGnL5rCu71oFQDfz4xAfTGLpSXdAmdK1+G4PXPKJBPFc33mB2BXCG2NHoJqQOpD
ZL30wlGDVfUPKZquDr11Ad3ZcsLezjsbZmgN+wlp1iq/C34BG+B+Vml2FStXGF+gv/fhg1P01Nvk
FKFr95Q/r4xSHEV1AQAFvxSjmbVbncvD0rVgXJjjJCq295W0SooxMMDzVgmqp947PNRtBBMvEMld
ow+9MdQuNtyA1RBKfunyo3Zp4s4TCA0kTXQsRmg/7jByXei/lJF11c8YFQjZi2FQosX79STe+qqY
DegAgWe4TudYEl9qq6KE9GxjBvCCwi/WpbRO3g2LwCNdTEL+/nOFRZCR2ye9wXdmtu2NDLzXge1E
KijW0+zNzug7zu3oqLiEoilxZRM1NaNSDJ0nKHFd03apqRSDFohY0Zyom5wRBFWjZe6H4eJ4cm+G
f90ufIA0VhvrPHA/c4JVFy1rdFJ84yCJOxrFaBK83B88IxJXzsayn5XfiqvJJFCUItsqR3OUf+4J
6abM1bI3prfVPfDu6bdNugW4/8eADE0/L9M9nUFmKpQxEq9TvE5aLRw/J/wg0TGPGcO0G9U6S8Fa
09RBDMNDmqd5lbnW3UoxMK09PeVYgBfNygrFs2Oa4K/tL72ejyMnWYcaqsHcHdSh8aDYhCeOFn7d
O8Plao0sg7Gn161FZdffNyf45p2Qt90h78Aj3MXAUVOsKOWE6XcuHlwD93Y0jbFcj9m7xcJulmrE
szIJ/t6MeFkTyOdRnXYZ7HFQin+BXFKUP9xOFGIO6iIPofsg1tJjn/8P++d3NjIIpBewgtecZOzI
4eZM5FoJdgAUznlWKTpPYwN4c6t0+pwOiGu7kqdSwhn9sZ6L4Gyc/2ZB6VGkPwEyOBQ5bPQP221E
L7KAivNFvkS9hghlC20fuAE8R8BC2/b/YEUu7NGrKOlvwkTiNR/l0h184l8KmS5xYJFQEuIV+/3J
MbhhewwN/9biSngKaLMpoPsYrV2Twl/+SAYuEhGAhodjaZJ72vuN7t8XoAo+mmnNhLOkcxxC4BTg
FwMQBdBbR3VXu5Wfc47sUYj8cH2N+Ali+s0tFD1qVD1b54wxKRwmRrScuK3k4UAh7pwbYbXbFkd0
/JS3XS90zgpmQIGH1ZfjaMQuotpUiT8lQv8B04UNqEdO0iRR6erAtLkSSj9G5YocIsRIXOo7+SQ2
wA3znKEKNbmkreb4lRLB313xz5nL4SO9sYWsouQUmZXu9VWA4aW1WUbaz62ZCrHUh+Kn90gg6h9I
TR9Xq05+EoO+Qr1hx//Mnte/+OJaEVfiH5YwHkIST2FTl2wK9fVtkARjqAjKylVrdmsdHziQ4Xvf
0lgb+glTnSzAeE44DE5f2CcX/YTL+dpPbEnorPdW2bslOX4qr2BkQvRxN1tIoiRRV09aTGtztda8
wAHOS1ck9gt8cIdUGTgM45F9C8KldKwEOO5zDdhZs73vhrtUDgX66GWv6ORc1XnvIEVNnhFC5PrO
GHIWXrQiHsPJyRaakGRPendDxfaBoZkGmuy4LaeEScX/isGPFUBB/NZ83cmwbp/Tp8q3mc25tdy8
gMpbR51tysB5j3+x7LYHc+sjX1EtzzcCqrQt3f2WnHtj3a8J0Qm+k3l9CfmEYycTVO6I/jWRAMO5
6VnwLxP3xZJelP/F0AyUGtpMo1qML3gJ/iJhQIq4D/fH4bAQFJPN+d09oyfl6ne06bL3D/8+3l8f
U5LR4vKVO5Y3FVMEXWcESJEFkcxm7PpN0qAQma0amvQSt2jn1k1CCfjrAsUJfxXO6BdlZQ1fsfoS
9vWlQ2jLsc+AqNqa6kJML1sJVFq8Wkf+4hMQdGMnvQQjtAH1AGTy9bE5Nx6368+sGiUWErrnCD+k
zBcOrSvNnDDk1yg0d4/tqwMS0DH3XgAQBpVG0XPXNRTq7TevP1UFZP1Zwyle4+3C0gSHGjmQR2w+
OC9CPkBJeYpf3s1aYcn524xRHNRLikQTgNhUSq7gsldfKRF32mMV/JmotPQ0x6Op0E+R44UX13LJ
ABXklEU+e9O3ea3IYpuytzgkC0MDa380U8j4vqGwJOvbkDltQkL8uEISvSzio0cDis/LsdGJ+gDj
ktyHU9jqnWDYtfLxoxoXRpBfYSj4sXcbyFbkBuKBHVDUOo/NESmHI/pt7/SLIOdqSfGxdbJ9Uepg
UAgpH3ymvfXDnCEjpBq6iNEcHbopv6p9qeKxa2ZNEYR4Y3DXTKehe730yfiSkzW7RtFavAfrkWqB
L4oNbk//K2ceKL7tu/FC/G3yZhm2WynS/r3qa6h5QlWtMojPXlUBCImYrZOehxYJ732rOcSUQDC3
IZAygmQciyKTOLsvPhlUrd0SXxjX0UhW0wtOLpXVvty/OtVOeJHj1LQElx8mNx9Owc2luLO/u0yb
xST17PjL2bolfCE1zTVYSv4DO93XW23ktGFO3u1Go4CKOEhW4Xa2piBMbSnBvh8+7+UufI/zSGQF
NpH7FUs3TKfUcyIsZrrOuGqeNwCTzjiZIVK+8ewgHFBrRMigB/7NNk/jvh6iXzNIJmI47uGvEHOG
fNdT5hRHHn82Rvq4ixKc7STLcHll+X6SNBnqRDN4jQjVqJWZhKaTdAfOL6MkWVuHvXq7UvFsSuGb
Vmy4DBIPFVjjPhKxeYQM6gMN9GCQ9/qyJkk00peKSeUnntvH/3qwDhSpAKbttkiS3i/ZiiLGwbe0
FECaSINeP2jsbHfnS6bHj6XMM5CnrYzNFOWpqeLA5It4ZqhvxLM848uV65A882Q+ZcSdv4l/NikS
Y0yQdpYQHGB/Yo2XudoVAIWepIglPNsNNKgpKXm4AGJ98bnjA2Zt70/P8ZJ0vI7JC031SahXmN/3
Z7C40m3vwut8rhAWW8Yvhn1EeZlp8Ef7U0MC9xVEuA6o64S/cRzckEImyCyGg+gHG2YG/UyAin71
gC/tk34PrAgiwWLOVW2a1ocMKVY49LStjFFDHyF+RKhxtWObiIkfxKbKIiGQWlKivDL3T83/LkvG
dJUwLt41W7TIREKStjxeYrjk/3wGVmiQdpLyuH+3jvsY2fofEn0NH67avRIvelS4dHSCg5uTrG+X
GWt8mrDdSuI0n5c7E0BHmFhA9d7t2BX0EBrN2mAtVV4MHA5oImLjEGnLVDWQLUzyypTlzVc5kbb6
kbCv4fwDSIOu6G2JeoVqtToxMBBQ0NGyujoQg/uCL8iXKc6sHj+4iuhgIqkvQ5ZO6fzVEybTa/Xd
QiBBjIBV+PhbVqEbUCmEBwqSHDTMyFCKO/wU7VniEgljZFAtDCD4njtmZ/ZoHW2h9ehddWwH7Fwg
4+LXnMbzlnXxwo/ycn9zKvUELQ4yVN/D7Oli3NLtXzjv61AV1aevKK1pAfRBErFshc5L/tTPkowa
yg1Yb9iN5zsAzuBjVJSOIfmvR4zYF5CcDHB5FLOIfpqflb8WwkTPCvQ9dslVb2Zh8Mt2IrHIWSCG
8CG+LjJqwJp6PIZje4Mm7Pc8wD6VN7OZnLOBOB4S/PukDhVQ/ClNsogJZlWfnNW5Dbc1bcgUWkF6
RDch6ZElVGUeZhphc5Yi1707JmBosHoCUoV/GLwuNsBTKPFy40IHjcR9pDAFILs/9CMCTDyzQa59
72YClLX/Bh2TmX8h7OMLJwijgSYG/99N1uVHMFLe+T2FtOUhEnt19fg5XbraWEhVOdIETg18FQOk
43OmvEeBUn3Qm7gYq/pNcKMrcdxwRgchrIdzI0mBJ3BGcXJ+321UJ22V7yadgxazevdTuuqtjRq0
z8nuCjTCbGb/agG383J7GsIJujK/JOFScdmc7TuvhS+Gu2KmzZ4f/N9eFwCby35MnkPXcCC5Qk0J
9IovYm/AxnfjcUE8hvjRWiwk0f35E6sZhCdPbKb9qt1uInoWudgRYytPEJmPvYgvrPmV4IgoLG9m
6VBVnaQ+6vbBqPoD7oLr5zm9Esj6Y8WOAwKAMZDNNi9HRzvrtHwXUCiRp0OF58/izg5X2+cxTFTw
8meB2ZaIQSrI6CNSqRFPSvXm4+mQzmiVd4IfhLsvuxyZvHW2Zgs5xg2C7D45Ma4uuKk5mE5XBowH
1kPumnTNkDI5CloN0AdRfu6RFh9qNBE72Y9M4cCSXcyWE4Dj6wKJ3TmeEIR3Een1p4Fuyr7CqioQ
riOg7lgWmA/z60i+J5G4GEom9LHmnX3j4GZbkzCUtlZioJYF+z1b2mY+lLrYvVA7dEj4oAuB3YgI
rj4Ecld3TDTPtROEzi0US4CeJhBwO3GBLDyiGKKSHeikjvK5MWOZ00zHJo0cNQZiUyC9fley/083
Xemq+l2MubaX46dzyFXjyCDWLJsKyJvrTgF3ZfRuEPFFt1oH+KQj/FCGMIpYi8gnfqrhKGwEfAkB
/++VtHwCd2wjWqOALxbLCdOJhC7qRNGgJy8teuHB1O9mTyVcvHzJzTLajs0q6SgCnZeRmOFgjL7T
/G/ntrcAA8k2oSHns7YHlHLxGcRXVH5PW1nSGej+Nx+do4onh7IwcBR/9SbPn/f/n6ldG4T+yx3v
JSFiRwEx0T5p//7k5JD9kHwcpb7R9CYcQIi9z98SjeRQWOOU8PtvbRkLu+HRWMbQAy6OcRO9iyQW
VngOri6Tm78FAeNLfeZgk0iditZ2y88jGkDTrHHmhDUJ8G8gcyS6jjHrrSKBjnNmLeIg9UnPOM8i
AV0NReQx6V6gbDWDc+ydjVy04JwI+l5WiFmbqemTN9WsN6JELRxAWKB0iYlhhDoVMIcXSmn6BKcH
OkPyYxOrhpvb4vhryJsTXl5M54LIwkgPYD37F6QszAxuSlvjffUyISQD4EGx3JBdEqsqaAxukgGP
EvAbJI1YQ3rDb+54GtgnhM6S3fzaWgLmCtWcdA2L68ZTOqrk2tSjDf6BZQO3MwziZ9PCDkJMIUix
3nuROb4uYx9E0godESB+6C34NAnZGInIQukGYvLuhWzHVOXmKPnUMRTlFlyNTfrpoccTNg3I7O8c
Zs9frOxo7bpIupwv9XnVWxdVZepsCRhXCdk4osl/TWL6G7uIYsRKSXGT38RWH4G7kGC+6iHZvDFQ
GH5rIgCikVCEuiM5lwG1775nBw3iJz5Di3yJSnf2YYFxUYpSamCClb7PhQN58WFs3aCFXgFpHL/B
PlCBjKMIJX5Ggi4ybMBsDm/ElugabGS+V5NLUaQi9Ie7byFxz3W+1cOuIm0Hleu61YkSh5Ztm9dP
l8TfD+b2nHrNUDjNWoiHx0au5YjqaTkJkX9HWiEDaCOnvdj+dxudhviWaCOv2nnLDcou9cA72Tta
fl7Leb679XfOsmBC3CMXDMEHTbikM0YQ9oe1B6dvdSIIhn8pV+8DZmaVS+EO6ogUCOwqhjNtbq0o
/mowMx5753mCvfQ+umRyh91cieyYpwtoMA8D1Fn0QGRiJf9BFHw8jXsuVWHQK3jFlTbmiA1whtfC
lLhA9/lZmsA/F47UGJoZsqkT+8fuV4BN5aOL8Lw6JKNABTIgrL7jzIP9RwI+ZN2ByQg3mNkhU0QA
Syb/cqMaX4F23cQnC/Nn+qQeWGvSWP99reCYUNDLVXxzATKRAfAB+Am9BTVoYf1i9qhbJOxeDgyE
IkNUaYhktquQKyIESGVD+qpOXw/pTNfFuzGdolQjEUzR5lvLk7kKShzz8HMoI2V3jry5AeHxESGE
Z9n+4lQ5cWXgmEI78pizD1+5+EeEl/gW7iTSEcSCPj7KnPY5g+8CenLNlCfJvRe0WNc6XL+W2Hs5
8GaLm7HZTnuyfXQGWr4sBLYICwWStCepGk6hU6TssSm30lE3WT/+J92TEevSR24Gt+tFcrujBYyX
EfVVkT91s8Hmz1BcRqAb9jTCiG3Ccd/LRezH/j3OkUkvqZIZoslHrqbnwmW5wGLNzItLfYnzWke4
4/ogxv7b/teq6qAE3o2b2iK8h/bmDMzbDJLUStEWn0hTqPUL1Vn2FsdJdB+3DSgjrCwoyOnHTp00
3fEK1MDPcJfiyzW58lE8MGlcYHowxf0=
`pragma protect end_protected
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;
    parameter GRES_WIDTH = 10000;
    parameter GRES_START = 10000;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    wire GRESTORE;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;
    reg GRESTORE_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;
    assign (strong1, weak0) GRESTORE = GRESTORE_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

    initial begin 
	GRESTORE_int = 1'b0;
	#(GRES_START);
	GRESTORE_int = 1'b1;
	#(GRES_WIDTH);
	GRESTORE_int = 1'b0;
    end

endmodule
`endif
