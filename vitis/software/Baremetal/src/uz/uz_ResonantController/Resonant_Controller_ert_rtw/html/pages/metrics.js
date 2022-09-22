function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.fcn["Resonant_Controller_initialize"] = {file: "C:\\uz_sw\\vitis\\software\\Baremetal\\src\\Codegen\\Resonant_Controller_ert_rtw\\Resonant_Controller.c",
	stack: 12,
	stackTotal: 12};
	 this.metricsArray.fcn["Resonant_Controller_step"] = {file: "C:\\uz_sw\\vitis\\software\\Baremetal\\src\\Codegen\\Resonant_Controller_ert_rtw\\Resonant_Controller.c",
	stack: 36,
	stackTotal: 36};
	 this.metricsArray.fcn["byteswap-16.h:__bswap_16"] = {file: "C:\\Program Files\\MATLAB\\R2022a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\byteswap-16.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["byteswap.h:__bswap_32"] = {file: "C:\\Program Files\\MATLAB\\R2022a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\byteswap.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["byteswap.h:__bswap_64"] = {file: "C:\\Program Files\\MATLAB\\R2022a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\byteswap.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["cos"] = {file: "C:\\Program Files\\MATLAB\\R2022a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["memset"] = {file: "C:\\Program Files\\MATLAB\\R2022a\\polyspace\\verifier\\cxx\\include\\include-libc\\string.h",
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
	 this.codeMetricsSummary = '<a href="javascript:void(0)" onclick="return postParentWindowMessage({message:\'gotoReportPage\', pageName:\'Resonant_Controller_metrics\'});">Global Memory: 0(bytes) Maximum Stack: 36(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
