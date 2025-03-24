function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.fcn["Resonant_Controller_initialize"] = {file: "C:\\ultrazohm_sw\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\Resonant_Controller_ert_rtw\\Resonant_Controller.c",
	stack: 4,
	stackTotal: 4};
	 this.metricsArray.fcn["Resonant_Controller_step"] = {file: "C:\\ultrazohm_sw\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\Resonant_Controller_ert_rtw\\Resonant_Controller.c",
	stack: 28,
	stackTotal: 28};
	 this.metricsArray.fcn["cosf"] = {file: "C:\\Program Files\\MATLAB\\R2024a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
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
	 this.codeMetricsSummary = '<a href="javascript:void(0)" onclick="return postParentWindowMessage({message:\'gotoReportPage\', pageName:\'Resonant_Controller_metrics\'});">Global Memory: 0(bytes) Maximum Stack: 28(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
