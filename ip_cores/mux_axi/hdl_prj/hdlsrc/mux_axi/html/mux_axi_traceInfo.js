function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <S4>/Bit Slice */
	this.urlHashMap["mux_axi:43"] = "msg=&block=mux_axi:43";
	/* <S4>/Bit Slice1 */
	this.urlHashMap["mux_axi:48"] = "msg=&block=mux_axi:48";
	/* <S4>/Bit Slice2 */
	this.urlHashMap["mux_axi:49"] = "msg=&block=mux_axi:49";
	/* <S4>/Bit Slice3 */
	this.urlHashMap["mux_axi:50"] = "msg=&block=mux_axi:50";
	/* <S4>/Bit Slice4 */
	this.urlHashMap["mux_axi:51"] = "msg=&block=mux_axi:51";
	/* <S4>/Bit Slice5 */
	this.urlHashMap["mux_axi:52"] = "msg=&block=mux_axi:52";
	/* <S4>/Bit Slice6 */
	this.urlHashMap["mux_axi:53"] = "msg=&block=mux_axi:53";
	/* <S4>/Bit Slice7 */
	this.urlHashMap["mux_axi:54"] = "msg=&block=mux_axi:54";
	/* <S4>/Constant */
	this.urlHashMap["mux_axi:42"] = "msg=&block=mux_axi:42";
	/* <S4>/Data Type Conversion3 */
	this.urlHashMap["mux_axi:58"] = "msg=&block=mux_axi:58";
	/* <S4>/Multiport
Switch */
	this.urlHashMap["mux_axi:41"] = "msg=&block=mux_axi:41";
	/* <S21>/bit_slice */
	this.urlHashMap["mux_axi:43:472"] = "msg=rtwMsg_notTraceable&block=mux_axi:43:472";
	/* <S22>/bit_slice */
	this.urlHashMap["mux_axi:48:472"] = "msg=rtwMsg_notTraceable&block=mux_axi:48:472";
	/* <S23>/bit_slice */
	this.urlHashMap["mux_axi:49:472"] = "msg=rtwMsg_notTraceable&block=mux_axi:49:472";
	/* <S24>/bit_slice */
	this.urlHashMap["mux_axi:50:472"] = "msg=rtwMsg_notTraceable&block=mux_axi:50:472";
	/* <S25>/bit_slice */
	this.urlHashMap["mux_axi:51:472"] = "msg=rtwMsg_notTraceable&block=mux_axi:51:472";
	/* <S26>/bit_slice */
	this.urlHashMap["mux_axi:52:472"] = "msg=rtwMsg_notTraceable&block=mux_axi:52:472";
	/* <S27>/bit_slice */
	this.urlHashMap["mux_axi:53:472"] = "msg=rtwMsg_notTraceable&block=mux_axi:53:472";
	/* <S28>/bit_slice */
	this.urlHashMap["mux_axi:54:472"] = "msg=rtwMsg_notTraceable&block=mux_axi:54:472";
	/* <S29>:1 */
	this.urlHashMap["mux_axi:43:472:1"] = "msg=rtwMsg_optimizedSfObject&block=mux_axi:43:472:1";
	/* <S30>:1 */
	this.urlHashMap["mux_axi:48:472:1"] = "msg=rtwMsg_optimizedSfObject&block=mux_axi:48:472:1";
	/* <S31>:1 */
	this.urlHashMap["mux_axi:49:472:1"] = "msg=rtwMsg_optimizedSfObject&block=mux_axi:49:472:1";
	/* <S32>:1 */
	this.urlHashMap["mux_axi:50:472:1"] = "msg=rtwMsg_optimizedSfObject&block=mux_axi:50:472:1";
	/* <S33>:1 */
	this.urlHashMap["mux_axi:51:472:1"] = "msg=rtwMsg_optimizedSfObject&block=mux_axi:51:472:1";
	/* <S34>:1 */
	this.urlHashMap["mux_axi:52:472:1"] = "msg=rtwMsg_optimizedSfObject&block=mux_axi:52:472:1";
	/* <S35>:1 */
	this.urlHashMap["mux_axi:53:472:1"] = "msg=rtwMsg_optimizedSfObject&block=mux_axi:53:472:1";
	/* <S36>:1 */
	this.urlHashMap["mux_axi:54:472:1"] = "msg=rtwMsg_optimizedSfObject&block=mux_axi:54:472:1";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "mux_axi"};
	this.sidHashMap["mux_axi"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S4>/select_AXI"] = {sid: "mux_axi:8"};
	this.sidHashMap["mux_axi:8"] = {rtwname: "<S4>/select_AXI"};
	this.rtwnameHashMap["<S4>/interrupts_in"] = {sid: "mux_axi:9"};
	this.sidHashMap["mux_axi:9"] = {rtwname: "<S4>/interrupts_in"};
	this.rtwnameHashMap["<S4>/Bit Slice"] = {sid: "mux_axi:43"};
	this.sidHashMap["mux_axi:43"] = {rtwname: "<S4>/Bit Slice"};
	this.rtwnameHashMap["<S4>/Bit Slice1"] = {sid: "mux_axi:48"};
	this.sidHashMap["mux_axi:48"] = {rtwname: "<S4>/Bit Slice1"};
	this.rtwnameHashMap["<S4>/Bit Slice2"] = {sid: "mux_axi:49"};
	this.sidHashMap["mux_axi:49"] = {rtwname: "<S4>/Bit Slice2"};
	this.rtwnameHashMap["<S4>/Bit Slice3"] = {sid: "mux_axi:50"};
	this.sidHashMap["mux_axi:50"] = {rtwname: "<S4>/Bit Slice3"};
	this.rtwnameHashMap["<S4>/Bit Slice4"] = {sid: "mux_axi:51"};
	this.sidHashMap["mux_axi:51"] = {rtwname: "<S4>/Bit Slice4"};
	this.rtwnameHashMap["<S4>/Bit Slice5"] = {sid: "mux_axi:52"};
	this.sidHashMap["mux_axi:52"] = {rtwname: "<S4>/Bit Slice5"};
	this.rtwnameHashMap["<S4>/Bit Slice6"] = {sid: "mux_axi:53"};
	this.sidHashMap["mux_axi:53"] = {rtwname: "<S4>/Bit Slice6"};
	this.rtwnameHashMap["<S4>/Bit Slice7"] = {sid: "mux_axi:54"};
	this.sidHashMap["mux_axi:54"] = {rtwname: "<S4>/Bit Slice7"};
	this.rtwnameHashMap["<S4>/Constant"] = {sid: "mux_axi:42"};
	this.sidHashMap["mux_axi:42"] = {rtwname: "<S4>/Constant"};
	this.rtwnameHashMap["<S4>/Data Type Conversion3"] = {sid: "mux_axi:58"};
	this.sidHashMap["mux_axi:58"] = {rtwname: "<S4>/Data Type Conversion3"};
	this.rtwnameHashMap["<S4>/Multiport Switch"] = {sid: "mux_axi:41"};
	this.sidHashMap["mux_axi:41"] = {rtwname: "<S4>/Multiport Switch"};
	this.rtwnameHashMap["<S4>/interrupt_out"] = {sid: "mux_axi:10"};
	this.sidHashMap["mux_axi:10"] = {rtwname: "<S4>/interrupt_out"};
	this.rtwnameHashMap["<S4>/select_out"] = {sid: "mux_axi:57"};
	this.sidHashMap["mux_axi:57"] = {rtwname: "<S4>/select_out"};
	this.rtwnameHashMap["<S21>/u"] = {sid: "mux_axi:43:471"};
	this.sidHashMap["mux_axi:43:471"] = {rtwname: "<S21>/u"};
	this.rtwnameHashMap["<S21>/bit_slice"] = {sid: "mux_axi:43:472"};
	this.sidHashMap["mux_axi:43:472"] = {rtwname: "<S21>/bit_slice"};
	this.rtwnameHashMap["<S21>/y"] = {sid: "mux_axi:43:473"};
	this.sidHashMap["mux_axi:43:473"] = {rtwname: "<S21>/y"};
	this.rtwnameHashMap["<S22>/u"] = {sid: "mux_axi:48:471"};
	this.sidHashMap["mux_axi:48:471"] = {rtwname: "<S22>/u"};
	this.rtwnameHashMap["<S22>/bit_slice"] = {sid: "mux_axi:48:472"};
	this.sidHashMap["mux_axi:48:472"] = {rtwname: "<S22>/bit_slice"};
	this.rtwnameHashMap["<S22>/y"] = {sid: "mux_axi:48:473"};
	this.sidHashMap["mux_axi:48:473"] = {rtwname: "<S22>/y"};
	this.rtwnameHashMap["<S23>/u"] = {sid: "mux_axi:49:471"};
	this.sidHashMap["mux_axi:49:471"] = {rtwname: "<S23>/u"};
	this.rtwnameHashMap["<S23>/bit_slice"] = {sid: "mux_axi:49:472"};
	this.sidHashMap["mux_axi:49:472"] = {rtwname: "<S23>/bit_slice"};
	this.rtwnameHashMap["<S23>/y"] = {sid: "mux_axi:49:473"};
	this.sidHashMap["mux_axi:49:473"] = {rtwname: "<S23>/y"};
	this.rtwnameHashMap["<S24>/u"] = {sid: "mux_axi:50:471"};
	this.sidHashMap["mux_axi:50:471"] = {rtwname: "<S24>/u"};
	this.rtwnameHashMap["<S24>/bit_slice"] = {sid: "mux_axi:50:472"};
	this.sidHashMap["mux_axi:50:472"] = {rtwname: "<S24>/bit_slice"};
	this.rtwnameHashMap["<S24>/y"] = {sid: "mux_axi:50:473"};
	this.sidHashMap["mux_axi:50:473"] = {rtwname: "<S24>/y"};
	this.rtwnameHashMap["<S25>/u"] = {sid: "mux_axi:51:471"};
	this.sidHashMap["mux_axi:51:471"] = {rtwname: "<S25>/u"};
	this.rtwnameHashMap["<S25>/bit_slice"] = {sid: "mux_axi:51:472"};
	this.sidHashMap["mux_axi:51:472"] = {rtwname: "<S25>/bit_slice"};
	this.rtwnameHashMap["<S25>/y"] = {sid: "mux_axi:51:473"};
	this.sidHashMap["mux_axi:51:473"] = {rtwname: "<S25>/y"};
	this.rtwnameHashMap["<S26>/u"] = {sid: "mux_axi:52:471"};
	this.sidHashMap["mux_axi:52:471"] = {rtwname: "<S26>/u"};
	this.rtwnameHashMap["<S26>/bit_slice"] = {sid: "mux_axi:52:472"};
	this.sidHashMap["mux_axi:52:472"] = {rtwname: "<S26>/bit_slice"};
	this.rtwnameHashMap["<S26>/y"] = {sid: "mux_axi:52:473"};
	this.sidHashMap["mux_axi:52:473"] = {rtwname: "<S26>/y"};
	this.rtwnameHashMap["<S27>/u"] = {sid: "mux_axi:53:471"};
	this.sidHashMap["mux_axi:53:471"] = {rtwname: "<S27>/u"};
	this.rtwnameHashMap["<S27>/bit_slice"] = {sid: "mux_axi:53:472"};
	this.sidHashMap["mux_axi:53:472"] = {rtwname: "<S27>/bit_slice"};
	this.rtwnameHashMap["<S27>/y"] = {sid: "mux_axi:53:473"};
	this.sidHashMap["mux_axi:53:473"] = {rtwname: "<S27>/y"};
	this.rtwnameHashMap["<S28>/u"] = {sid: "mux_axi:54:471"};
	this.sidHashMap["mux_axi:54:471"] = {rtwname: "<S28>/u"};
	this.rtwnameHashMap["<S28>/bit_slice"] = {sid: "mux_axi:54:472"};
	this.sidHashMap["mux_axi:54:472"] = {rtwname: "<S28>/bit_slice"};
	this.rtwnameHashMap["<S28>/y"] = {sid: "mux_axi:54:473"};
	this.sidHashMap["mux_axi:54:473"] = {rtwname: "<S28>/y"};
	this.rtwnameHashMap["<S29>:1"] = {sid: "mux_axi:43:472:1"};
	this.sidHashMap["mux_axi:43:472:1"] = {rtwname: "<S29>:1"};
	this.rtwnameHashMap["<S30>:1"] = {sid: "mux_axi:48:472:1"};
	this.sidHashMap["mux_axi:48:472:1"] = {rtwname: "<S30>:1"};
	this.rtwnameHashMap["<S31>:1"] = {sid: "mux_axi:49:472:1"};
	this.sidHashMap["mux_axi:49:472:1"] = {rtwname: "<S31>:1"};
	this.rtwnameHashMap["<S32>:1"] = {sid: "mux_axi:50:472:1"};
	this.sidHashMap["mux_axi:50:472:1"] = {rtwname: "<S32>:1"};
	this.rtwnameHashMap["<S33>:1"] = {sid: "mux_axi:51:472:1"};
	this.sidHashMap["mux_axi:51:472:1"] = {rtwname: "<S33>:1"};
	this.rtwnameHashMap["<S34>:1"] = {sid: "mux_axi:52:472:1"};
	this.sidHashMap["mux_axi:52:472:1"] = {rtwname: "<S34>:1"};
	this.rtwnameHashMap["<S35>:1"] = {sid: "mux_axi:53:472:1"};
	this.sidHashMap["mux_axi:53:472:1"] = {rtwname: "<S35>:1"};
	this.rtwnameHashMap["<S36>:1"] = {sid: "mux_axi:54:472:1"};
	this.sidHashMap["mux_axi:54:472:1"] = {rtwname: "<S36>:1"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
