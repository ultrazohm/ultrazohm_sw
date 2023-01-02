function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <S1>/Delay */
	this.urlHashMap["uz_typeconv_multi:45"] = "uz_typeconv_multi_src_uz_typeconv_multi.vhd:134,135,136,137,138,139,140,141,142,143";
	/* <S1>/Delay1 */
	this.urlHashMap["uz_typeconv_multi:46"] = "uz_typeconv_multi_src_uz_typeconv_multi.vhd:122,123,124,125,126,127,128,129,130,131";
	/* <S1>/Delay2 */
	this.urlHashMap["uz_typeconv_multi:47"] = "uz_typeconv_multi_src_uz_typeconv_multi.vhd:104,105,106,107,108,109,110,111,112,113";
	/* <S1>/Delay3 */
	this.urlHashMap["uz_typeconv_multi:48"] = "uz_typeconv_multi_src_uz_typeconv_multi.vhd:189,190,191,192,193,194,195,196,197,198";
	/* <S1>/Delay4 */
	this.urlHashMap["uz_typeconv_multi:49"] = "uz_typeconv_multi_src_uz_typeconv_multi.vhd:203,204,205,206,207,208,209,210,211,212";
	/* <S1>/Delay5 */
	this.urlHashMap["uz_typeconv_multi:52"] = "uz_typeconv_multi_src_uz_typeconv_multi.vhd:156,157,158,159,160,161,162,163,164,165";
	/* <S1>/Delay6 */
	this.urlHashMap["uz_typeconv_multi:53"] = "uz_typeconv_multi_src_uz_typeconv_multi.vhd:168,169,170,171,172,173,174,175,176,177";
	/* <S1>/Detect Rise
Positive */
	this.urlHashMap["uz_typeconv_multi:43"] = "uz_typeconv_multi_src_uz_typeconv_multi.vhd:94,95,96,97,98,99,100";
	/* <S1>/Product */
	this.urlHashMap["uz_typeconv_multi:55"] = "uz_typeconv_multi_src_uz_typeconv_multi.vhd:184,185,186,187";
	/* <S1>/Switch */
	this.urlHashMap["uz_typeconv_multi:44"] = "uz_typeconv_multi_src_uz_typeconv_multi.vhd:147,148";
	/* <S1>/Switch1 */
	this.urlHashMap["uz_typeconv_multi:54"] = "uz_typeconv_multi_src_uz_typeconv_multi.vhd:181,182";
	/* <S2>/Delay Input1 */
	this.urlHashMap["uz_typeconv_multi:43:2"] = "uz_typeconv_multi_src_Detect_Rise_Positive.vhd:49,50,51,52,53,54,55,56,57,58";
	/* <S2>/FixPt
Relational
Operator */
	this.urlHashMap["uz_typeconv_multi:43:3"] = "uz_typeconv_multi_src_Detect_Rise_Positive.vhd:62,63";
	/* <S2>/Positive */
	this.urlHashMap["uz_typeconv_multi:43:4"] = "uz_typeconv_multi_src_Detect_Rise_Positive.vhd:45,46";
	/* <S3>/Compare */
	this.urlHashMap["uz_typeconv_multi:43:4:2"] = "msg=rtwMsg_notTraceable&block=uz_typeconv_multi:43:4:2";
	/* <S3>/Constant */
	this.urlHashMap["uz_typeconv_multi:43:4:3"] = "msg=rtwMsg_notTraceable&block=uz_typeconv_multi:43:4:3";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "uz_typeconv_multi"};
	this.sidHashMap["uz_typeconv_multi"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>/omega_m_sfix24En11"] = {sid: "uz_typeconv_multi:8"};
	this.sidHashMap["uz_typeconv_multi:8"] = {rtwname: "<S1>/omega_m_sfix24En11"};
	this.rtwnameHashMap["<S1>/omega_B_inv_AXI_ufix18En18"] = {sid: "uz_typeconv_multi:51"};
	this.sidHashMap["uz_typeconv_multi:51"] = {rtwname: "<S1>/omega_B_inv_AXI_ufix18En18"};
	this.rtwnameHashMap["<S1>/trigger"] = {sid: "uz_typeconv_multi:41"};
	this.sidHashMap["uz_typeconv_multi:41"] = {rtwname: "<S1>/trigger"};
	this.rtwnameHashMap["<S1>/Delay"] = {sid: "uz_typeconv_multi:45"};
	this.sidHashMap["uz_typeconv_multi:45"] = {rtwname: "<S1>/Delay"};
	this.rtwnameHashMap["<S1>/Delay1"] = {sid: "uz_typeconv_multi:46"};
	this.sidHashMap["uz_typeconv_multi:46"] = {rtwname: "<S1>/Delay1"};
	this.rtwnameHashMap["<S1>/Delay2"] = {sid: "uz_typeconv_multi:47"};
	this.sidHashMap["uz_typeconv_multi:47"] = {rtwname: "<S1>/Delay2"};
	this.rtwnameHashMap["<S1>/Delay3"] = {sid: "uz_typeconv_multi:48"};
	this.sidHashMap["uz_typeconv_multi:48"] = {rtwname: "<S1>/Delay3"};
	this.rtwnameHashMap["<S1>/Delay4"] = {sid: "uz_typeconv_multi:49"};
	this.sidHashMap["uz_typeconv_multi:49"] = {rtwname: "<S1>/Delay4"};
	this.rtwnameHashMap["<S1>/Delay5"] = {sid: "uz_typeconv_multi:52"};
	this.sidHashMap["uz_typeconv_multi:52"] = {rtwname: "<S1>/Delay5"};
	this.rtwnameHashMap["<S1>/Delay6"] = {sid: "uz_typeconv_multi:53"};
	this.sidHashMap["uz_typeconv_multi:53"] = {rtwname: "<S1>/Delay6"};
	this.rtwnameHashMap["<S1>/Detect Rise Positive"] = {sid: "uz_typeconv_multi:43"};
	this.sidHashMap["uz_typeconv_multi:43"] = {rtwname: "<S1>/Detect Rise Positive"};
	this.rtwnameHashMap["<S1>/Product"] = {sid: "uz_typeconv_multi:55"};
	this.sidHashMap["uz_typeconv_multi:55"] = {rtwname: "<S1>/Product"};
	this.rtwnameHashMap["<S1>/Switch"] = {sid: "uz_typeconv_multi:44"};
	this.sidHashMap["uz_typeconv_multi:44"] = {rtwname: "<S1>/Switch"};
	this.rtwnameHashMap["<S1>/Switch1"] = {sid: "uz_typeconv_multi:54"};
	this.sidHashMap["uz_typeconv_multi:54"] = {rtwname: "<S1>/Switch1"};
	this.rtwnameHashMap["<S1>/sfix18En15"] = {sid: "uz_typeconv_multi:10"};
	this.sidHashMap["uz_typeconv_multi:10"] = {rtwname: "<S1>/sfix18En15"};
	this.rtwnameHashMap["<S1>/done"] = {sid: "uz_typeconv_multi:42"};
	this.sidHashMap["uz_typeconv_multi:42"] = {rtwname: "<S1>/done"};
	this.rtwnameHashMap["<S2>/U"] = {sid: "uz_typeconv_multi:43:1"};
	this.sidHashMap["uz_typeconv_multi:43:1"] = {rtwname: "<S2>/U"};
	this.rtwnameHashMap["<S2>/Delay Input1"] = {sid: "uz_typeconv_multi:43:2"};
	this.sidHashMap["uz_typeconv_multi:43:2"] = {rtwname: "<S2>/Delay Input1"};
	this.rtwnameHashMap["<S2>/FixPt Relational Operator"] = {sid: "uz_typeconv_multi:43:3"};
	this.sidHashMap["uz_typeconv_multi:43:3"] = {rtwname: "<S2>/FixPt Relational Operator"};
	this.rtwnameHashMap["<S2>/Positive"] = {sid: "uz_typeconv_multi:43:4"};
	this.sidHashMap["uz_typeconv_multi:43:4"] = {rtwname: "<S2>/Positive"};
	this.rtwnameHashMap["<S2>/Y"] = {sid: "uz_typeconv_multi:43:5"};
	this.sidHashMap["uz_typeconv_multi:43:5"] = {rtwname: "<S2>/Y"};
	this.rtwnameHashMap["<S3>/u"] = {sid: "uz_typeconv_multi:43:4:1"};
	this.sidHashMap["uz_typeconv_multi:43:4:1"] = {rtwname: "<S3>/u"};
	this.rtwnameHashMap["<S3>/Compare"] = {sid: "uz_typeconv_multi:43:4:2"};
	this.sidHashMap["uz_typeconv_multi:43:4:2"] = {rtwname: "<S3>/Compare"};
	this.rtwnameHashMap["<S3>/Constant"] = {sid: "uz_typeconv_multi:43:4:3"};
	this.sidHashMap["uz_typeconv_multi:43:4:3"] = {rtwname: "<S3>/Constant"};
	this.rtwnameHashMap["<S3>/y"] = {sid: "uz_typeconv_multi:43:4:5"};
	this.sidHashMap["uz_typeconv_multi:43:4:5"] = {rtwname: "<S3>/y"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
