function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.var["rtInf"] = {file: "C:\\Users\\ELSYS\\ultrazohm\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	size: 8};
	 this.metricsArray.var["rtInfF"] = {file: "C:\\Users\\ELSYS\\ultrazohm\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	size: 4};
	 this.metricsArray.var["rtMinusInf"] = {file: "C:\\Users\\ELSYS\\ultrazohm\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	size: 8};
	 this.metricsArray.var["rtMinusInfF"] = {file: "C:\\Users\\ELSYS\\ultrazohm\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	size: 4};
	 this.metricsArray.var["rtNaN"] = {file: "C:\\Users\\ELSYS\\ultrazohm\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	size: 8};
	 this.metricsArray.var["rtNaNF"] = {file: "C:\\Users\\ELSYS\\ultrazohm\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	size: 4};
	 this.metricsArray.var["rtP"] = {file: "C:\\Users\\ELSYS\\ultrazohm\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\Flussschaetzer_ert_rtw\\Flussschaetzer_data.c",
	size: 16};
	 this.metricsArray.fcn["Flussschaetzer_initialize"] = {file: "C:\\Users\\ELSYS\\ultrazohm\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\Flussschaetzer_ert_rtw\\Flussschaetzer.c",
	stack: 8,
	stackTotal: 8};
	 this.metricsArray.fcn["Flussschaetzer_step"] = {file: "C:\\Users\\ELSYS\\ultrazohm\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\Flussschaetzer_ert_rtw\\Flussschaetzer.c",
	stack: 68,
	stackTotal: 97};
	 this.metricsArray.fcn["atan2f"] = {file: "C:\\Program Files\\MATLAB\\R2024b\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["atanf"] = {file: "C:\\Program Files\\MATLAB\\R2024b\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["fabsf"] = {file: "C:\\Program Files\\MATLAB\\R2024b\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["floorf"] = {file: "C:\\Program Files\\MATLAB\\R2024b\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["fmodf"] = {file: "C:\\Program Files\\MATLAB\\R2024b\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["rtGetNaN"] = {file: "C:\\Users\\ELSYS\\ultrazohm\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\slprj\\ert\\_sharedutils\\rtGetNaN.c",
	stack: 8,
	stackTotal: 8};
	 this.metricsArray.fcn["rtGetNaNF"] = {file: "C:\\Users\\ELSYS\\ultrazohm\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\slprj\\ert\\_sharedutils\\rtGetNaN.c",
	stack: 4,
	stackTotal: 4};
	 this.metricsArray.fcn["rtIsInf"] = {file: "C:\\Users\\ELSYS\\ultrazohm\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	stack: 9,
	stackTotal: 9};
	 this.metricsArray.fcn["rtIsInfF"] = {file: "C:\\Users\\ELSYS\\ultrazohm\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	stack: 5,
	stackTotal: 5};
	 this.metricsArray.fcn["rtIsNaN"] = {file: "C:\\Users\\ELSYS\\ultrazohm\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	stack: 9,
	stackTotal: 9};
	 this.metricsArray.fcn["rtIsNaNF"] = {file: "C:\\Users\\ELSYS\\ultrazohm\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	stack: 5,
	stackTotal: 5};
	 this.metricsArray.fcn["rt_atan2f_snf"] = {file: "C:\\Users\\ELSYS\\ultrazohm\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\slprj\\ert\\_sharedutils\\rt_atan2f_snf.c",
	stack: 24,
	stackTotal: 29};
	 this.metricsArray.fcn["rt_modf_snf"] = {file: "C:\\Users\\ELSYS\\ultrazohm\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\slprj\\ert\\_sharedutils\\rt_modf_snf.c",
	stack: 21,
	stackTotal: 26};
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
	 this.codeMetricsSummary = '<a href="javascript:void(0)" onclick="return postParentWindowMessage({message:\'gotoReportPage\', pageName:\'Flussschaetzer_metrics\'});">Global Memory: 52(bytes) Maximum Stack: 68(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
