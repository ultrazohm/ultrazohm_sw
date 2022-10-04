function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <S1>/Data Type Conversion */
	this.urlHashMap["uz_typeconv_27En18_to27En15:30"] = "alpha27En18_to_27En15_src_27_En18_to_27_En15.vhd:141";
	/* <S1>/Delay */
	this.urlHashMap["uz_typeconv_27En18_to27En15:45"] = "alpha27En18_to_27En15_src_27_En18_to_27_En15.vhd:125,126,127,128,129,130,131,132,133,134";
	/* <S1>/Delay1 */
	this.urlHashMap["uz_typeconv_27En18_to27En15:46"] = "alpha27En18_to_27En15_src_27_En18_to_27_En15.vhd:113,114,115,116,117,118,119,120,121,122";
	/* <S1>/Delay2 */
	this.urlHashMap["uz_typeconv_27En18_to27En15:47"] = "alpha27En18_to_27En15_src_27_En18_to_27_En15.vhd:95,96,97,98,99,100,101,102,103,104";
	/* <S1>/Delay3 */
	this.urlHashMap["uz_typeconv_27En18_to27En15:48"] = "alpha27En18_to_27En15_src_27_En18_to_27_En15.vhd:143,144,145,146,147,148,149,150,151,152";
	/* <S1>/Delay4 */
	this.urlHashMap["uz_typeconv_27En18_to27En15:49"] = "alpha27En18_to_27En15_src_27_En18_to_27_En15.vhd:157,158,159,160,161,162,163,164,165,166";
	/* <S1>/Detect Rise
Positive */
	this.urlHashMap["uz_typeconv_27En18_to27En15:43"] = "alpha27En18_to_27En15_src_27_En18_to_27_En15.vhd:85,86,87,88,89,90,91";
	/* <S1>/Switch */
	this.urlHashMap["uz_typeconv_27En18_to27En15:44"] = "alpha27En18_to_27En15_src_27_En18_to_27_En15.vhd:138,139";
	/* <S2>/Delay Input1 */
	this.urlHashMap["uz_typeconv_27En18_to27En15:43:2"] = "alpha27En18_to_27En15_src_Detect_Rise_Positive.vhd:49,50,51,52,53,54,55,56,57,58";
	/* <S2>/FixPt
Relational
Operator */
	this.urlHashMap["uz_typeconv_27En18_to27En15:43:3"] = "alpha27En18_to_27En15_src_Detect_Rise_Positive.vhd:62,63";
	/* <S2>/Positive */
	this.urlHashMap["uz_typeconv_27En18_to27En15:43:4"] = "alpha27En18_to_27En15_src_Detect_Rise_Positive.vhd:45,46";
	/* <S3>/Compare */
	this.urlHashMap["uz_typeconv_27En18_to27En15:43:4:2"] = "msg=rtwMsg_notTraceable&block=uz_typeconv_27En18_to27En15:43:4:2";
	/* <S3>/Constant */
	this.urlHashMap["uz_typeconv_27En18_to27En15:43:4:3"] = "msg=rtwMsg_notTraceable&block=uz_typeconv_27En18_to27En15:43:4:3";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "uz_typeconv_27En18_to27En15"};
	this.sidHashMap["uz_typeconv_27En18_to27En15"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>/27En18"] = {sid: "uz_typeconv_27En18_to27En15:8"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:8"] = {rtwname: "<S1>/27En18"};
	this.rtwnameHashMap["<S1>/trigger"] = {sid: "uz_typeconv_27En18_to27En15:41"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:41"] = {rtwname: "<S1>/trigger"};
	this.rtwnameHashMap["<S1>/Data Type Conversion"] = {sid: "uz_typeconv_27En18_to27En15:30"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:30"] = {rtwname: "<S1>/Data Type Conversion"};
	this.rtwnameHashMap["<S1>/Delay"] = {sid: "uz_typeconv_27En18_to27En15:45"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:45"] = {rtwname: "<S1>/Delay"};
	this.rtwnameHashMap["<S1>/Delay1"] = {sid: "uz_typeconv_27En18_to27En15:46"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:46"] = {rtwname: "<S1>/Delay1"};
	this.rtwnameHashMap["<S1>/Delay2"] = {sid: "uz_typeconv_27En18_to27En15:47"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:47"] = {rtwname: "<S1>/Delay2"};
	this.rtwnameHashMap["<S1>/Delay3"] = {sid: "uz_typeconv_27En18_to27En15:48"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:48"] = {rtwname: "<S1>/Delay3"};
	this.rtwnameHashMap["<S1>/Delay4"] = {sid: "uz_typeconv_27En18_to27En15:49"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:49"] = {rtwname: "<S1>/Delay4"};
	this.rtwnameHashMap["<S1>/Detect Rise Positive"] = {sid: "uz_typeconv_27En18_to27En15:43"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:43"] = {rtwname: "<S1>/Detect Rise Positive"};
	this.rtwnameHashMap["<S1>/Switch"] = {sid: "uz_typeconv_27En18_to27En15:44"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:44"] = {rtwname: "<S1>/Switch"};
	this.rtwnameHashMap["<S1>/27En15"] = {sid: "uz_typeconv_27En18_to27En15:10"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:10"] = {rtwname: "<S1>/27En15"};
	this.rtwnameHashMap["<S1>/done"] = {sid: "uz_typeconv_27En18_to27En15:42"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:42"] = {rtwname: "<S1>/done"};
	this.rtwnameHashMap["<S2>/U"] = {sid: "uz_typeconv_27En18_to27En15:43:1"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:43:1"] = {rtwname: "<S2>/U"};
	this.rtwnameHashMap["<S2>/Delay Input1"] = {sid: "uz_typeconv_27En18_to27En15:43:2"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:43:2"] = {rtwname: "<S2>/Delay Input1"};
	this.rtwnameHashMap["<S2>/FixPt Relational Operator"] = {sid: "uz_typeconv_27En18_to27En15:43:3"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:43:3"] = {rtwname: "<S2>/FixPt Relational Operator"};
	this.rtwnameHashMap["<S2>/Positive"] = {sid: "uz_typeconv_27En18_to27En15:43:4"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:43:4"] = {rtwname: "<S2>/Positive"};
	this.rtwnameHashMap["<S2>/Y"] = {sid: "uz_typeconv_27En18_to27En15:43:5"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:43:5"] = {rtwname: "<S2>/Y"};
	this.rtwnameHashMap["<S3>/u"] = {sid: "uz_typeconv_27En18_to27En15:43:4:1"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:43:4:1"] = {rtwname: "<S3>/u"};
	this.rtwnameHashMap["<S3>/Compare"] = {sid: "uz_typeconv_27En18_to27En15:43:4:2"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:43:4:2"] = {rtwname: "<S3>/Compare"};
	this.rtwnameHashMap["<S3>/Constant"] = {sid: "uz_typeconv_27En18_to27En15:43:4:3"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:43:4:3"] = {rtwname: "<S3>/Constant"};
	this.rtwnameHashMap["<S3>/y"] = {sid: "uz_typeconv_27En18_to27En15:43:4:5"};
	this.sidHashMap["uz_typeconv_27En18_to27En15:43:4:5"] = {rtwname: "<S3>/y"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
