function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.var["rtInf"] = {file: "C:\\Users\\valen\\Documents\\repos\\UZ\\ultrazohm_sw_pr\\docs\\source\\mpsoc\\software_framework\\ParameterID\\simulink_model\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	size: 8};
	 this.metricsArray.var["rtInfF"] = {file: "C:\\Users\\valen\\Documents\\repos\\UZ\\ultrazohm_sw_pr\\docs\\source\\mpsoc\\software_framework\\ParameterID\\simulink_model\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	size: 4};
	 this.metricsArray.var["rtMinusInf"] = {file: "C:\\Users\\valen\\Documents\\repos\\UZ\\ultrazohm_sw_pr\\docs\\source\\mpsoc\\software_framework\\ParameterID\\simulink_model\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	size: 8};
	 this.metricsArray.var["rtMinusInfF"] = {file: "C:\\Users\\valen\\Documents\\repos\\UZ\\ultrazohm_sw_pr\\docs\\source\\mpsoc\\software_framework\\ParameterID\\simulink_model\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	size: 4};
	 this.metricsArray.var["rtNaN"] = {file: "C:\\Users\\valen\\Documents\\repos\\UZ\\ultrazohm_sw_pr\\docs\\source\\mpsoc\\software_framework\\ParameterID\\simulink_model\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	size: 8};
	 this.metricsArray.var["rtNaNF"] = {file: "C:\\Users\\valen\\Documents\\repos\\UZ\\ultrazohm_sw_pr\\docs\\source\\mpsoc\\software_framework\\ParameterID\\simulink_model\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	size: 4};
	 this.metricsArray.fcn["eye_6olvtp5i"] = {file: "C:\\Users\\valen\\Documents\\repos\\UZ\\ultrazohm_sw_pr\\docs\\source\\mpsoc\\software_framework\\ParameterID\\simulink_model\\slprj\\ert\\_sharedutils\\eye_6olvtp5i.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["rtGetInf"] = {file: "C:\\Users\\valen\\Documents\\repos\\UZ\\ultrazohm_sw_pr\\docs\\source\\mpsoc\\software_framework\\ParameterID\\simulink_model\\slprj\\ert\\_sharedutils\\rtGetInf.c",
	stack: 20,
	stackTotal: 20};
	 this.metricsArray.fcn["rtGetInfF"] = {file: "C:\\Users\\valen\\Documents\\repos\\UZ\\ultrazohm_sw_pr\\docs\\source\\mpsoc\\software_framework\\ParameterID\\simulink_model\\slprj\\ert\\_sharedutils\\rtGetInf.c",
	stack: 4,
	stackTotal: 4};
	 this.metricsArray.fcn["rtGetMinusInf"] = {file: "C:\\Users\\valen\\Documents\\repos\\UZ\\ultrazohm_sw_pr\\docs\\source\\mpsoc\\software_framework\\ParameterID\\simulink_model\\slprj\\ert\\_sharedutils\\rtGetInf.c",
	stack: 20,
	stackTotal: 20};
	 this.metricsArray.fcn["rtGetMinusInfF"] = {file: "C:\\Users\\valen\\Documents\\repos\\UZ\\ultrazohm_sw_pr\\docs\\source\\mpsoc\\software_framework\\ParameterID\\simulink_model\\slprj\\ert\\_sharedutils\\rtGetInf.c",
	stack: 4,
	stackTotal: 4};
	 this.metricsArray.fcn["rtGetNaN"] = {file: "C:\\Users\\valen\\Documents\\repos\\UZ\\ultrazohm_sw_pr\\docs\\source\\mpsoc\\software_framework\\ParameterID\\simulink_model\\slprj\\ert\\_sharedutils\\rtGetNaN.c",
	stack: 20,
	stackTotal: 20};
	 this.metricsArray.fcn["rtGetNaNF"] = {file: "C:\\Users\\valen\\Documents\\repos\\UZ\\ultrazohm_sw_pr\\docs\\source\\mpsoc\\software_framework\\ParameterID\\simulink_model\\slprj\\ert\\_sharedutils\\rtGetNaN.c",
	stack: 4,
	stackTotal: 4};
	 this.metricsArray.fcn["rtIsInf"] = {file: "C:\\Users\\valen\\Documents\\repos\\UZ\\ultrazohm_sw_pr\\docs\\source\\mpsoc\\software_framework\\ParameterID\\simulink_model\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["rtIsInfF"] = {file: "C:\\Users\\valen\\Documents\\repos\\UZ\\ultrazohm_sw_pr\\docs\\source\\mpsoc\\software_framework\\ParameterID\\simulink_model\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["rtIsNaN"] = {file: "C:\\Users\\valen\\Documents\\repos\\UZ\\ultrazohm_sw_pr\\docs\\source\\mpsoc\\software_framework\\ParameterID\\simulink_model\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	stack: 13,
	stackTotal: 13};
	 this.metricsArray.fcn["rtIsNaNF"] = {file: "C:\\Users\\valen\\Documents\\repos\\UZ\\ultrazohm_sw_pr\\docs\\source\\mpsoc\\software_framework\\ParameterID\\simulink_model\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	stack: 4,
	stackTotal: 4};
	 this.metricsArray.fcn["rt_InitInfAndNaN"] = {file: "C:\\Users\\valen\\Documents\\repos\\UZ\\ultrazohm_sw_pr\\docs\\source\\mpsoc\\software_framework\\ParameterID\\simulink_model\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	stack: 0,
	stackTotal: 0};
	 this.getMetrics = function(token) { 
		 var data;
		 data = this.metricsArray.var[token];
		 if (!data) {
			 data = this.metricsArray.fcn[token];
			 if (data) data.type = "fcn";
		 } else { 
			 data.type = "var";
		 }
	 return data; }; 
	 this.codeMetricsSummary = '<a href="javascript:void(0)" onclick="return postParentWindowMessage({message:\'gotoReportPage\', pageName:\'TwoMassID_metrics\'});">Global Memory: 36(bytes) Maximum Stack: 20(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
