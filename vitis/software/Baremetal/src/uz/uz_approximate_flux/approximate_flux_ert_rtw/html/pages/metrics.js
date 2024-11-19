function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.fcn["approximate_flux_initialize"] = {file: "C:\\Users\\Philipp\\uz_temp\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\uz\\uz_approximate_flux\\approximate_flux_ert_rtw\\approximate_flux.c",
	stack: 12,
	stackTotal: 12};
	 this.metricsArray.fcn["approximate_flux_step"] = {file: "C:\\Users\\Philipp\\uz_temp\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\uz\\uz_approximate_flux\\approximate_flux_ert_rtw\\approximate_flux.c",
	stack: 32,
	stackTotal: 32};
	 this.metricsArray.fcn["coshf"] = {file: "C:\\Program Files\\MATLAB\\R2023b\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["logf"] = {file: "C:\\Program Files\\MATLAB\\R2023b\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["memset"] = {file: "C:\\Program Files\\MATLAB\\R2023b\\polyspace\\verifier\\cxx\\include\\include-libc\\string.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["tanhf"] = {file: "C:\\Program Files\\MATLAB\\R2023b\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
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
	 this.codeMetricsSummary = '<a href="javascript:void(0)" onclick="return postParentWindowMessage({message:\'gotoReportPage\', pageName:\'approximate_flux_metrics\'});">Global Memory: 0(bytes) Maximum Stack: 32(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
