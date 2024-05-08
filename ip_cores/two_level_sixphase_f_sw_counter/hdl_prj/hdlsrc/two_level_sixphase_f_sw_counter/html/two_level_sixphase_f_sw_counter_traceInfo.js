function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <S1>/Count_f_sw */
	this.urlHashMap["two_level_sixphase_f_sw_counter:43"] = "two_level_sixphase_f_sw_cnt_ip_src_two_level_sixphase_f_sw_counter.vhd:111,112,113,114,115,116,117";
	/* <S1>/Detec_edge */
	this.urlHashMap["two_level_sixphase_f_sw_counter:44"] = "two_level_sixphase_f_sw_cnt_ip_src_two_level_sixphase_f_sw_counter.vhd:162,163,164";
	/* <S1>/Mux */
	this.urlHashMap["two_level_sixphase_f_sw_counter:46"] = "two_level_sixphase_f_sw_cnt_ip_src_two_level_sixphase_f_sw_counter.vhd:121,122,123,124,125,126,127,128,129,130,131,132";
	/* <S1>/Mux1 */
	this.urlHashMap["two_level_sixphase_f_sw_counter:47"] = "two_level_sixphase_f_sw_cnt_ip_src_two_level_sixphase_f_sw_counter.vhd:121,122,123,124,125,126,127,128,129,130,131,132";
	/* <S1>/Mux2 */
	this.urlHashMap["two_level_sixphase_f_sw_counter:48"] = "two_level_sixphase_f_sw_cnt_ip_src_two_level_sixphase_f_sw_counter.vhd:121,122,123,124,125,126,127,128,129,130,131,132";
	/* <S1>/SS_Old */
	this.urlHashMap["two_level_sixphase_f_sw_counter:49"] = "two_level_sixphase_f_sw_cnt_ip_src_two_level_sixphase_f_sw_counter.vhd:134,135,136,137,138,139,140,141,142,143";
	/* <S1>/Saturation */
	this.urlHashMap["two_level_sixphase_f_sw_counter:50"] = "two_level_sixphase_f_sw_cnt_ip_src_two_level_sixphase_f_sw_counter.vhd:171";
	/* <S1>/Scope */
	this.urlHashMap["two_level_sixphase_f_sw_counter:51"] = "msg=rtwMsg_notTraceable&block=two_level_sixphase_f_sw_counter:51";
	/* <S1>/delay */
	this.urlHashMap["two_level_sixphase_f_sw_counter:52"] = "two_level_sixphase_f_sw_cnt_ip_src_two_level_sixphase_f_sw_counter.vhd:175,176,177,178,179,180,181,182,183,184";
	/* <S1>/reset_old2 */
	this.urlHashMap["two_level_sixphase_f_sw_counter:53"] = "two_level_sixphase_f_sw_cnt_ip_src_two_level_sixphase_f_sw_counter.vhd:150,151,152,153,154,155,156,157,158,159";
	/* <S1>/reset_old_switch1 */
	this.urlHashMap["two_level_sixphase_f_sw_counter:54"] = "two_level_sixphase_f_sw_cnt_ip_src_two_level_sixphase_f_sw_counter.vhd:147,148";
	/* <S2>:1 */
	this.urlHashMap["two_level_sixphase_f_sw_counter:43:1"] = "two_level_sixphase_f_sw_cnt_ip_src_Count_f_sw.vhd:51";
	/* <S2>:1:14 */
	this.urlHashMap["two_level_sixphase_f_sw_counter:43:1:14"] = "msg=rtwMsg_optimizedSfObject&block=two_level_sixphase_f_sw_counter:43:1:14";
	/* <S2>:1:15 */
	this.urlHashMap["two_level_sixphase_f_sw_counter:43:1:15"] = "two_level_sixphase_f_sw_cnt_ip_src_Count_f_sw.vhd:61";
	/* <S2>:1:25 */
	this.urlHashMap["two_level_sixphase_f_sw_counter:43:1:25"] = "two_level_sixphase_f_sw_cnt_ip_src_Count_f_sw.vhd:71,72,73,75,76,77,81,82";
	/* <S2>:1:26 */
	this.urlHashMap["two_level_sixphase_f_sw_counter:43:1:26"] = "msg=rtwMsg_optimizedSfObject&block=two_level_sixphase_f_sw_counter:43:1:26";
	/* <S2>:1:27 */
	this.urlHashMap["two_level_sixphase_f_sw_counter:43:1:27"] = "two_level_sixphase_f_sw_cnt_ip_src_Count_f_sw.vhd:79";
	/* <S2>:1:31 */
	this.urlHashMap["two_level_sixphase_f_sw_counter:43:1:31"] = "two_level_sixphase_f_sw_cnt_ip_src_Count_f_sw.vhd:84";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "two_level_sixphase_f_sw_counter"};
	this.sidHashMap["two_level_sixphase_f_sw_counter"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>/ss_in_0"] = {sid: "two_level_sixphase_f_sw_counter:30"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:30"] = {rtwname: "<S1>/ss_in_0"};
	this.rtwnameHashMap["<S1>/ss_in_1"] = {sid: "two_level_sixphase_f_sw_counter:31"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:31"] = {rtwname: "<S1>/ss_in_1"};
	this.rtwnameHashMap["<S1>/ss_in_2"] = {sid: "two_level_sixphase_f_sw_counter:32"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:32"] = {rtwname: "<S1>/ss_in_2"};
	this.rtwnameHashMap["<S1>/ss_in_3"] = {sid: "two_level_sixphase_f_sw_counter:33"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:33"] = {rtwname: "<S1>/ss_in_3"};
	this.rtwnameHashMap["<S1>/ss_in_4"] = {sid: "two_level_sixphase_f_sw_counter:34"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:34"] = {rtwname: "<S1>/ss_in_4"};
	this.rtwnameHashMap["<S1>/ss_in_5"] = {sid: "two_level_sixphase_f_sw_counter:35"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:35"] = {rtwname: "<S1>/ss_in_5"};
	this.rtwnameHashMap["<S1>/ss_in_6"] = {sid: "two_level_sixphase_f_sw_counter:36"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:36"] = {rtwname: "<S1>/ss_in_6"};
	this.rtwnameHashMap["<S1>/ss_in_7"] = {sid: "two_level_sixphase_f_sw_counter:37"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:37"] = {rtwname: "<S1>/ss_in_7"};
	this.rtwnameHashMap["<S1>/ss_in_8"] = {sid: "two_level_sixphase_f_sw_counter:38"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:38"] = {rtwname: "<S1>/ss_in_8"};
	this.rtwnameHashMap["<S1>/ss_in_9"] = {sid: "two_level_sixphase_f_sw_counter:39"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:39"] = {rtwname: "<S1>/ss_in_9"};
	this.rtwnameHashMap["<S1>/ss_in_10"] = {sid: "two_level_sixphase_f_sw_counter:40"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:40"] = {rtwname: "<S1>/ss_in_10"};
	this.rtwnameHashMap["<S1>/ss_in_11"] = {sid: "two_level_sixphase_f_sw_counter:41"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:41"] = {rtwname: "<S1>/ss_in_11"};
	this.rtwnameHashMap["<S1>/bResetAXI"] = {sid: "two_level_sixphase_f_sw_counter:42"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:42"] = {rtwname: "<S1>/bResetAXI"};
	this.rtwnameHashMap["<S1>/Count_f_sw"] = {sid: "two_level_sixphase_f_sw_counter:43"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:43"] = {rtwname: "<S1>/Count_f_sw"};
	this.rtwnameHashMap["<S1>/Detec_edge"] = {sid: "two_level_sixphase_f_sw_counter:44"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:44"] = {rtwname: "<S1>/Detec_edge"};
	this.rtwnameHashMap["<S1>/Gain"] = {sid: "two_level_sixphase_f_sw_counter:45"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:45"] = {rtwname: "<S1>/Gain"};
	this.rtwnameHashMap["<S1>/Mux"] = {sid: "two_level_sixphase_f_sw_counter:46"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:46"] = {rtwname: "<S1>/Mux"};
	this.rtwnameHashMap["<S1>/Mux1"] = {sid: "two_level_sixphase_f_sw_counter:47"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:47"] = {rtwname: "<S1>/Mux1"};
	this.rtwnameHashMap["<S1>/Mux2"] = {sid: "two_level_sixphase_f_sw_counter:48"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:48"] = {rtwname: "<S1>/Mux2"};
	this.rtwnameHashMap["<S1>/SS_Old"] = {sid: "two_level_sixphase_f_sw_counter:49"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:49"] = {rtwname: "<S1>/SS_Old"};
	this.rtwnameHashMap["<S1>/Saturation"] = {sid: "two_level_sixphase_f_sw_counter:50"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:50"] = {rtwname: "<S1>/Saturation"};
	this.rtwnameHashMap["<S1>/Scope"] = {sid: "two_level_sixphase_f_sw_counter:51"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:51"] = {rtwname: "<S1>/Scope"};
	this.rtwnameHashMap["<S1>/delay"] = {sid: "two_level_sixphase_f_sw_counter:52"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:52"] = {rtwname: "<S1>/delay"};
	this.rtwnameHashMap["<S1>/reset_old2"] = {sid: "two_level_sixphase_f_sw_counter:53"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:53"] = {rtwname: "<S1>/reset_old2"};
	this.rtwnameHashMap["<S1>/reset_old_switch1"] = {sid: "two_level_sixphase_f_sw_counter:54"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:54"] = {rtwname: "<S1>/reset_old_switch1"};
	this.rtwnameHashMap["<S1>/switchNumb_AXI"] = {sid: "two_level_sixphase_f_sw_counter:55"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:55"] = {rtwname: "<S1>/switchNumb_AXI"};
	this.rtwnameHashMap["<S1>/switchNumb"] = {sid: "two_level_sixphase_f_sw_counter:56"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:56"] = {rtwname: "<S1>/switchNumb"};
	this.rtwnameHashMap["<S2>:1"] = {sid: "two_level_sixphase_f_sw_counter:43:1"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:43:1"] = {rtwname: "<S2>:1"};
	this.rtwnameHashMap["<S2>:1:14"] = {sid: "two_level_sixphase_f_sw_counter:43:1:14"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:43:1:14"] = {rtwname: "<S2>:1:14"};
	this.rtwnameHashMap["<S2>:1:15"] = {sid: "two_level_sixphase_f_sw_counter:43:1:15"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:43:1:15"] = {rtwname: "<S2>:1:15"};
	this.rtwnameHashMap["<S2>:1:25"] = {sid: "two_level_sixphase_f_sw_counter:43:1:25"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:43:1:25"] = {rtwname: "<S2>:1:25"};
	this.rtwnameHashMap["<S2>:1:26"] = {sid: "two_level_sixphase_f_sw_counter:43:1:26"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:43:1:26"] = {rtwname: "<S2>:1:26"};
	this.rtwnameHashMap["<S2>:1:27"] = {sid: "two_level_sixphase_f_sw_counter:43:1:27"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:43:1:27"] = {rtwname: "<S2>:1:27"};
	this.rtwnameHashMap["<S2>:1:31"] = {sid: "two_level_sixphase_f_sw_counter:43:1:31"};
	this.sidHashMap["two_level_sixphase_f_sw_counter:43:1:31"] = {rtwname: "<S2>:1:31"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
