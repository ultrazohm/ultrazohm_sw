function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <S17>/omega_m_left */
	this.urlHashMap["uz_mpc_3ph:2858"] = "msg=&block=uz_mpc_3ph:2858";
	/* <S17>/omega_m_right */
	this.urlHashMap["uz_mpc_3ph:2859"] = "msg=&block=uz_mpc_3ph:2859";
	/* <S17>/theta_el_left */
	this.urlHashMap["uz_mpc_3ph:2860"] = "msg=&block=uz_mpc_3ph:2860";
	/* <S17>/theta_el_right */
	this.urlHashMap["uz_mpc_3ph:2861"] = "msg=&block=uz_mpc_3ph:2861";
	/* <S17>/right_or_left_AXI */
	this.urlHashMap["uz_mpc_3ph:2876"] = "msg=&block=uz_mpc_3ph:2876";
	/* <S17>/adc_valid_trigger */
	this.urlHashMap["uz_mpc_3ph:2877"] = "msg=&block=uz_mpc_3ph:2877";
	/* <S17>/Delay */
	this.urlHashMap["uz_mpc_3ph:2878"] = "uz_sel_resolver_src_uz_sel_resolver.vhd:130,131,132,133,134,135,136,137,138,139,140,142";
	/* <S17>/Delay1 */
	this.urlHashMap["uz_mpc_3ph:2879"] = "uz_sel_resolver_src_uz_sel_resolver.vhd:114,115,116,117,118,119,120,121,122,123,124,126";
	/* <S17>/Delay2 */
	this.urlHashMap["uz_mpc_3ph:2890"] = "uz_sel_resolver_src_uz_sel_resolver.vhd:148,149,150,151,152,153,154,155,156,157,158,160";
	/* <S17>/Delay21 */
	this.urlHashMap["uz_mpc_3ph:2892"] = "uz_sel_resolver_src_uz_sel_resolver.vhd:94,95,96,97,98,99,100,101,102,103,104,106";
	/* <S17>/Delay28 */
	this.urlHashMap["uz_mpc_3ph:2899"] = "uz_sel_resolver_src_uz_sel_resolver.vhd:220,221,222,223,224,225,226,227,228,229,230,232";
	/* <S17>/Delay29 */
	this.urlHashMap["uz_mpc_3ph:2900"] = "uz_sel_resolver_src_uz_sel_resolver.vhd:220,221,222,223,224,225,226,227,228,229,230,232";
	/* <S17>/Delay3 */
	this.urlHashMap["uz_mpc_3ph:2901"] = "uz_sel_resolver_src_uz_sel_resolver.vhd:186,187,188,189,190,191,192,193,194,195,196,198";
	/* <S17>/Delay4 */
	this.urlHashMap["uz_mpc_3ph:2902"] = "uz_sel_resolver_src_uz_sel_resolver.vhd:170,171,172,173,174,175,176,177,178,179,180,182";
	/* <S17>/Delay5 */
	this.urlHashMap["uz_mpc_3ph:2903"] = "uz_sel_resolver_src_uz_sel_resolver.vhd:204,205,206,207,208,209,210,211,212,213,214,216";
	/* <S17>/Switch */
	this.urlHashMap["uz_mpc_3ph:2908"] = "uz_sel_resolver_src_uz_sel_resolver.vhd:145,146";
	/* <S17>/Switch1 */
	this.urlHashMap["uz_mpc_3ph:2909"] = "uz_sel_resolver_src_uz_sel_resolver.vhd:201,202";
	/* <S17>/omega_m */
	this.urlHashMap["uz_mpc_3ph:2917"] = "msg=&block=uz_mpc_3ph:2917";
	/* <S17>/theta_el */
	this.urlHashMap["uz_mpc_3ph:2918"] = "msg=&block=uz_mpc_3ph:2918";
	/* <S17>/selector_ip_done */
	this.urlHashMap["uz_mpc_3ph:2926"] = "msg=&block=uz_mpc_3ph:2926";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "uz_mpc_3ph"};
	this.sidHashMap["uz_mpc_3ph"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S17>/omega_m_left"] = {sid: "uz_mpc_3ph:2858"};
	this.sidHashMap["uz_mpc_3ph:2858"] = {rtwname: "<S17>/omega_m_left"};
	this.rtwnameHashMap["<S17>/omega_m_right"] = {sid: "uz_mpc_3ph:2859"};
	this.sidHashMap["uz_mpc_3ph:2859"] = {rtwname: "<S17>/omega_m_right"};
	this.rtwnameHashMap["<S17>/theta_el_left"] = {sid: "uz_mpc_3ph:2860"};
	this.sidHashMap["uz_mpc_3ph:2860"] = {rtwname: "<S17>/theta_el_left"};
	this.rtwnameHashMap["<S17>/theta_el_right"] = {sid: "uz_mpc_3ph:2861"};
	this.sidHashMap["uz_mpc_3ph:2861"] = {rtwname: "<S17>/theta_el_right"};
	this.rtwnameHashMap["<S17>/right_or_left_AXI"] = {sid: "uz_mpc_3ph:2876"};
	this.sidHashMap["uz_mpc_3ph:2876"] = {rtwname: "<S17>/right_or_left_AXI"};
	this.rtwnameHashMap["<S17>/adc_valid_trigger"] = {sid: "uz_mpc_3ph:2877"};
	this.sidHashMap["uz_mpc_3ph:2877"] = {rtwname: "<S17>/adc_valid_trigger"};
	this.rtwnameHashMap["<S17>/Delay"] = {sid: "uz_mpc_3ph:2878"};
	this.sidHashMap["uz_mpc_3ph:2878"] = {rtwname: "<S17>/Delay"};
	this.rtwnameHashMap["<S17>/Delay1"] = {sid: "uz_mpc_3ph:2879"};
	this.sidHashMap["uz_mpc_3ph:2879"] = {rtwname: "<S17>/Delay1"};
	this.rtwnameHashMap["<S17>/Delay2"] = {sid: "uz_mpc_3ph:2890"};
	this.sidHashMap["uz_mpc_3ph:2890"] = {rtwname: "<S17>/Delay2"};
	this.rtwnameHashMap["<S17>/Delay21"] = {sid: "uz_mpc_3ph:2892"};
	this.sidHashMap["uz_mpc_3ph:2892"] = {rtwname: "<S17>/Delay21"};
	this.rtwnameHashMap["<S17>/Delay28"] = {sid: "uz_mpc_3ph:2899"};
	this.sidHashMap["uz_mpc_3ph:2899"] = {rtwname: "<S17>/Delay28"};
	this.rtwnameHashMap["<S17>/Delay29"] = {sid: "uz_mpc_3ph:2900"};
	this.sidHashMap["uz_mpc_3ph:2900"] = {rtwname: "<S17>/Delay29"};
	this.rtwnameHashMap["<S17>/Delay3"] = {sid: "uz_mpc_3ph:2901"};
	this.sidHashMap["uz_mpc_3ph:2901"] = {rtwname: "<S17>/Delay3"};
	this.rtwnameHashMap["<S17>/Delay4"] = {sid: "uz_mpc_3ph:2902"};
	this.sidHashMap["uz_mpc_3ph:2902"] = {rtwname: "<S17>/Delay4"};
	this.rtwnameHashMap["<S17>/Delay5"] = {sid: "uz_mpc_3ph:2903"};
	this.sidHashMap["uz_mpc_3ph:2903"] = {rtwname: "<S17>/Delay5"};
	this.rtwnameHashMap["<S17>/Switch"] = {sid: "uz_mpc_3ph:2908"};
	this.sidHashMap["uz_mpc_3ph:2908"] = {rtwname: "<S17>/Switch"};
	this.rtwnameHashMap["<S17>/Switch1"] = {sid: "uz_mpc_3ph:2909"};
	this.sidHashMap["uz_mpc_3ph:2909"] = {rtwname: "<S17>/Switch1"};
	this.rtwnameHashMap["<S17>/omega_m"] = {sid: "uz_mpc_3ph:2917"};
	this.sidHashMap["uz_mpc_3ph:2917"] = {rtwname: "<S17>/omega_m"};
	this.rtwnameHashMap["<S17>/theta_el"] = {sid: "uz_mpc_3ph:2918"};
	this.sidHashMap["uz_mpc_3ph:2918"] = {rtwname: "<S17>/theta_el"};
	this.rtwnameHashMap["<S17>/selector_ip_done"] = {sid: "uz_mpc_3ph:2926"};
	this.sidHashMap["uz_mpc_3ph:2926"] = {rtwname: "<S17>/selector_ip_done"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
