function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <S4>/ss_in_0 */
	this.urlHashMap["uz_mpc_3ph:1081"] = "msg=&block=uz_mpc_3ph:1081";
	/* <S4>/ss_in_1 */
	this.urlHashMap["uz_mpc_3ph:1082"] = "msg=&block=uz_mpc_3ph:1082";
	/* <S4>/ss_in_2 */
	this.urlHashMap["uz_mpc_3ph:1083"] = "msg=&block=uz_mpc_3ph:1083";
	/* <S4>/ss_in_3 */
	this.urlHashMap["uz_mpc_3ph:1084"] = "msg=&block=uz_mpc_3ph:1084";
	/* <S4>/ss_in_4 */
	this.urlHashMap["uz_mpc_3ph:1085"] = "msg=&block=uz_mpc_3ph:1085";
	/* <S4>/ss_in_5 */
	this.urlHashMap["uz_mpc_3ph:1086"] = "msg=&block=uz_mpc_3ph:1086";
	/* <S4>/bResetAXI */
	this.urlHashMap["uz_mpc_3ph:1093"] = "msg=&block=uz_mpc_3ph:1093";
	/* <S4>/Count_f_sw */
	this.urlHashMap["uz_mpc_3ph:1094"] = "count_f_sw_src_counter_f_sw_3ph.vhd:106,107,108,109,110,111,112";
	/* <S4>/Detec_edge */
	this.urlHashMap["uz_mpc_3ph:1095"] = "count_f_sw_src_counter_f_sw_3ph.vhd:153,154,155";
	/* <S4>/Gain */
	this.urlHashMap["uz_mpc_3ph:1096"] = "msg=&block=uz_mpc_3ph:1096";
	/* <S4>/Mux */
	this.urlHashMap["uz_mpc_3ph:1097"] = "count_f_sw_src_counter_f_sw_3ph.vhd:116,117,118,119,120,121";
	/* <S4>/SS_Old */
	this.urlHashMap["uz_mpc_3ph:1100"] = "count_f_sw_src_counter_f_sw_3ph.vhd:123,124,125,126,127,128,129,130,131,132";
	/* <S4>/Saturation */
	this.urlHashMap["uz_mpc_3ph:1101"] = "count_f_sw_src_counter_f_sw_3ph.vhd:162";
	/* <S4>/Scope */
	this.urlHashMap["uz_mpc_3ph:1102"] = "msg=&block=uz_mpc_3ph:1102";
	/* <S4>/delay */
	this.urlHashMap["uz_mpc_3ph:1103"] = "count_f_sw_src_counter_f_sw_3ph.vhd:166,167,168,169,170,171,172,173,174,175";
	/* <S4>/reset_old2 */
	this.urlHashMap["uz_mpc_3ph:1104"] = "count_f_sw_src_counter_f_sw_3ph.vhd:141,142,143,144,145,146,147,148,149,150";
	/* <S4>/reset_old_switch1 */
	this.urlHashMap["uz_mpc_3ph:1105"] = "count_f_sw_src_counter_f_sw_3ph.vhd:138,139";
	/* <S4>/switchNumb_AXI */
	this.urlHashMap["uz_mpc_3ph:1106"] = "msg=&block=uz_mpc_3ph:1106";
	/* <S4>/switchNumb */
	this.urlHashMap["uz_mpc_3ph:1107"] = "msg=&block=uz_mpc_3ph:1107";
	/* <S26>:1 */
	this.urlHashMap["uz_mpc_3ph:1094:1"] = "count_f_sw_src_Count_f_sw.vhd:51";
	/* <S26>:1:14 */
	this.urlHashMap["uz_mpc_3ph:1094:1:14"] = "msg=&block=uz_mpc_3ph:1094:1:14";
	/* <S26>:1:15 */
	this.urlHashMap["uz_mpc_3ph:1094:1:15"] = "count_f_sw_src_Count_f_sw.vhd:61";
	/* <S26>:1:25 */
	this.urlHashMap["uz_mpc_3ph:1094:1:25"] = "count_f_sw_src_Count_f_sw.vhd:71,72,73,75,76,77,81,82";
	/* <S26>:1:26 */
	this.urlHashMap["uz_mpc_3ph:1094:1:26"] = "msg=&block=uz_mpc_3ph:1094:1:26";
	/* <S26>:1:27 */
	this.urlHashMap["uz_mpc_3ph:1094:1:27"] = "count_f_sw_src_Count_f_sw.vhd:79";
	/* <S26>:1:31 */
	this.urlHashMap["uz_mpc_3ph:1094:1:31"] = "count_f_sw_src_Count_f_sw.vhd:84";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "uz_mpc_3ph"};
	this.sidHashMap["uz_mpc_3ph"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S4>/ss_in_0"] = {sid: "uz_mpc_3ph:1081"};
	this.sidHashMap["uz_mpc_3ph:1081"] = {rtwname: "<S4>/ss_in_0"};
	this.rtwnameHashMap["<S4>/ss_in_1"] = {sid: "uz_mpc_3ph:1082"};
	this.sidHashMap["uz_mpc_3ph:1082"] = {rtwname: "<S4>/ss_in_1"};
	this.rtwnameHashMap["<S4>/ss_in_2"] = {sid: "uz_mpc_3ph:1083"};
	this.sidHashMap["uz_mpc_3ph:1083"] = {rtwname: "<S4>/ss_in_2"};
	this.rtwnameHashMap["<S4>/ss_in_3"] = {sid: "uz_mpc_3ph:1084"};
	this.sidHashMap["uz_mpc_3ph:1084"] = {rtwname: "<S4>/ss_in_3"};
	this.rtwnameHashMap["<S4>/ss_in_4"] = {sid: "uz_mpc_3ph:1085"};
	this.sidHashMap["uz_mpc_3ph:1085"] = {rtwname: "<S4>/ss_in_4"};
	this.rtwnameHashMap["<S4>/ss_in_5"] = {sid: "uz_mpc_3ph:1086"};
	this.sidHashMap["uz_mpc_3ph:1086"] = {rtwname: "<S4>/ss_in_5"};
	this.rtwnameHashMap["<S4>/bResetAXI"] = {sid: "uz_mpc_3ph:1093"};
	this.sidHashMap["uz_mpc_3ph:1093"] = {rtwname: "<S4>/bResetAXI"};
	this.rtwnameHashMap["<S4>/Count_f_sw"] = {sid: "uz_mpc_3ph:1094"};
	this.sidHashMap["uz_mpc_3ph:1094"] = {rtwname: "<S4>/Count_f_sw"};
	this.rtwnameHashMap["<S4>/Detec_edge"] = {sid: "uz_mpc_3ph:1095"};
	this.sidHashMap["uz_mpc_3ph:1095"] = {rtwname: "<S4>/Detec_edge"};
	this.rtwnameHashMap["<S4>/Gain"] = {sid: "uz_mpc_3ph:1096"};
	this.sidHashMap["uz_mpc_3ph:1096"] = {rtwname: "<S4>/Gain"};
	this.rtwnameHashMap["<S4>/Mux"] = {sid: "uz_mpc_3ph:1097"};
	this.sidHashMap["uz_mpc_3ph:1097"] = {rtwname: "<S4>/Mux"};
	this.rtwnameHashMap["<S4>/SS_Old"] = {sid: "uz_mpc_3ph:1100"};
	this.sidHashMap["uz_mpc_3ph:1100"] = {rtwname: "<S4>/SS_Old"};
	this.rtwnameHashMap["<S4>/Saturation"] = {sid: "uz_mpc_3ph:1101"};
	this.sidHashMap["uz_mpc_3ph:1101"] = {rtwname: "<S4>/Saturation"};
	this.rtwnameHashMap["<S4>/Scope"] = {sid: "uz_mpc_3ph:1102"};
	this.sidHashMap["uz_mpc_3ph:1102"] = {rtwname: "<S4>/Scope"};
	this.rtwnameHashMap["<S4>/delay"] = {sid: "uz_mpc_3ph:1103"};
	this.sidHashMap["uz_mpc_3ph:1103"] = {rtwname: "<S4>/delay"};
	this.rtwnameHashMap["<S4>/reset_old2"] = {sid: "uz_mpc_3ph:1104"};
	this.sidHashMap["uz_mpc_3ph:1104"] = {rtwname: "<S4>/reset_old2"};
	this.rtwnameHashMap["<S4>/reset_old_switch1"] = {sid: "uz_mpc_3ph:1105"};
	this.sidHashMap["uz_mpc_3ph:1105"] = {rtwname: "<S4>/reset_old_switch1"};
	this.rtwnameHashMap["<S4>/switchNumb_AXI"] = {sid: "uz_mpc_3ph:1106"};
	this.sidHashMap["uz_mpc_3ph:1106"] = {rtwname: "<S4>/switchNumb_AXI"};
	this.rtwnameHashMap["<S4>/switchNumb"] = {sid: "uz_mpc_3ph:1107"};
	this.sidHashMap["uz_mpc_3ph:1107"] = {rtwname: "<S4>/switchNumb"};
	this.rtwnameHashMap["<S26>:1"] = {sid: "uz_mpc_3ph:1094:1"};
	this.sidHashMap["uz_mpc_3ph:1094:1"] = {rtwname: "<S26>:1"};
	this.rtwnameHashMap["<S26>:1:14"] = {sid: "uz_mpc_3ph:1094:1:14"};
	this.sidHashMap["uz_mpc_3ph:1094:1:14"] = {rtwname: "<S26>:1:14"};
	this.rtwnameHashMap["<S26>:1:15"] = {sid: "uz_mpc_3ph:1094:1:15"};
	this.sidHashMap["uz_mpc_3ph:1094:1:15"] = {rtwname: "<S26>:1:15"};
	this.rtwnameHashMap["<S26>:1:25"] = {sid: "uz_mpc_3ph:1094:1:25"};
	this.sidHashMap["uz_mpc_3ph:1094:1:25"] = {rtwname: "<S26>:1:25"};
	this.rtwnameHashMap["<S26>:1:26"] = {sid: "uz_mpc_3ph:1094:1:26"};
	this.sidHashMap["uz_mpc_3ph:1094:1:26"] = {rtwname: "<S26>:1:26"};
	this.rtwnameHashMap["<S26>:1:27"] = {sid: "uz_mpc_3ph:1094:1:27"};
	this.sidHashMap["uz_mpc_3ph:1094:1:27"] = {rtwname: "<S26>:1:27"};
	this.rtwnameHashMap["<S26>:1:31"] = {sid: "uz_mpc_3ph:1094:1:31"};
	this.sidHashMap["uz_mpc_3ph:1094:1:31"] = {rtwname: "<S26>:1:31"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
