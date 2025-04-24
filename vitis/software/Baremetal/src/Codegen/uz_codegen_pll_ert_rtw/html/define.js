function CodeDefine() { 
this.def = new Array();
this.def["rt_modd"] = {file: "uz_codegen_pll_c.html",line:25,type:"fcn"};
this.def["uz_codegen_pll_step"] = {file: "uz_codegen_pll_c.html",line:56,type:"fcn"};
this.def["uz_codegen_pll_initialize"] = {file: "uz_codegen_pll_c.html",line:156,type:"fcn"};
this.def["RT_MODEL"] = {file: "uz_codegen_pll_h.html",line:63,type:"type"};
this.def["DW"] = {file: "uz_codegen_pll_h.html",line:70,type:"type"};
this.def["ExtU"] = {file: "uz_codegen_pll_h.html",line:79,type:"type"};
this.def["ExtY"] = {file: "uz_codegen_pll_h.html",line:85,type:"type"};
this.def["int8_T"] = {file: "rtwtypes_h.html",line:53,type:"type"};
this.def["uint8_T"] = {file: "rtwtypes_h.html",line:54,type:"type"};
this.def["int16_T"] = {file: "rtwtypes_h.html",line:55,type:"type"};
this.def["uint16_T"] = {file: "rtwtypes_h.html",line:56,type:"type"};
this.def["int32_T"] = {file: "rtwtypes_h.html",line:57,type:"type"};
this.def["uint32_T"] = {file: "rtwtypes_h.html",line:58,type:"type"};
this.def["int64_T"] = {file: "rtwtypes_h.html",line:59,type:"type"};
this.def["uint64_T"] = {file: "rtwtypes_h.html",line:60,type:"type"};
this.def["real32_T"] = {file: "rtwtypes_h.html",line:61,type:"type"};
this.def["real64_T"] = {file: "rtwtypes_h.html",line:62,type:"type"};
this.def["real_T"] = {file: "rtwtypes_h.html",line:68,type:"type"};
this.def["time_T"] = {file: "rtwtypes_h.html",line:69,type:"type"};
this.def["boolean_T"] = {file: "rtwtypes_h.html",line:70,type:"type"};
this.def["int_T"] = {file: "rtwtypes_h.html",line:71,type:"type"};
this.def["uint_T"] = {file: "rtwtypes_h.html",line:72,type:"type"};
this.def["ulong_T"] = {file: "rtwtypes_h.html",line:73,type:"type"};
this.def["ulonglong_T"] = {file: "rtwtypes_h.html",line:74,type:"type"};
this.def["char_T"] = {file: "rtwtypes_h.html",line:75,type:"type"};
this.def["uchar_T"] = {file: "rtwtypes_h.html",line:76,type:"type"};
this.def["byte_T"] = {file: "rtwtypes_h.html",line:77,type:"type"};
this.def["creal32_T"] = {file: "rtwtypes_h.html",line:87,type:"type"};
this.def["creal64_T"] = {file: "rtwtypes_h.html",line:92,type:"type"};
this.def["creal_T"] = {file: "rtwtypes_h.html",line:97,type:"type"};
this.def["cint8_T"] = {file: "rtwtypes_h.html",line:104,type:"type"};
this.def["cuint8_T"] = {file: "rtwtypes_h.html",line:111,type:"type"};
this.def["cint16_T"] = {file: "rtwtypes_h.html",line:118,type:"type"};
this.def["cuint16_T"] = {file: "rtwtypes_h.html",line:125,type:"type"};
this.def["cint32_T"] = {file: "rtwtypes_h.html",line:132,type:"type"};
this.def["cuint32_T"] = {file: "rtwtypes_h.html",line:139,type:"type"};
this.def["cint64_T"] = {file: "rtwtypes_h.html",line:146,type:"type"};
this.def["cuint64_T"] = {file: "rtwtypes_h.html",line:153,type:"type"};
this.def["pointer_T"] = {file: "rtwtypes_h.html",line:174,type:"type"};
}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
var relPathToBuildDir = "../ert_main.c";
var fileSep = "\\";
var isPC = true;
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["uz_codegen_pll_c.html"] = "../uz_codegen_pll.c";
	this.html2Root["uz_codegen_pll_c.html"] = "uz_codegen_pll_c.html";
	this.html2SrcPath["uz_codegen_pll_h.html"] = "../uz_codegen_pll.h";
	this.html2Root["uz_codegen_pll_h.html"] = "uz_codegen_pll_h.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "rtwtypes_h.html";
	this.html2SrcPath["rtmodel_h.html"] = "../rtmodel.h";
	this.html2Root["rtmodel_h.html"] = "rtmodel_h.html";
	this.getLink2Src = function (htmlFileName) {
		 if (this.html2SrcPath[htmlFileName])
			 return this.html2SrcPath[htmlFileName];
		 else
			 return null;
	}
	this.getLinkFromRoot = function (htmlFileName) {
		 if (this.html2Root[htmlFileName])
			 return this.html2Root[htmlFileName];
		 else
			 return null;
	}
}
Html2SrcLink.instance = new Html2SrcLink();
var fileList = [
"uz_codegen_pll_c.html","uz_codegen_pll_h.html","rtwtypes_h.html","rtmodel_h.html"];
