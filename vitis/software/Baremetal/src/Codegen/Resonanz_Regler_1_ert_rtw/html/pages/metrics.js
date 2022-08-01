function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.fcn["Resonanz_Regler_1_initialize"] = {file: "C:\\uz_sw\\vitis\\software\\Baremetal\\src\\Codegen\\Resonanz_Regler_1_ert_rtw\\Resonanz_Regler_1.c",
	stack: 12,
	stackTotal: 12};
	 this.metricsArray.fcn["Resonanz_Regler_1_step"] = {file: "C:\\uz_sw\\vitis\\software\\Baremetal\\src\\Codegen\\Resonanz_Regler_1_ert_rtw\\Resonanz_Regler_1.c",
	stack: 44,
	stackTotal: 44};
	 this.metricsArray.fcn["byteswap-16.h:__bswap_16"] = {file: "C:\\Program Files\\MATLAB\\R2021b\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\byteswap-16.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["byteswap.h:__bswap_32"] = {file: "C:\\Program Files\\MATLAB\\R2021b\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\byteswap.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["byteswap.h:__bswap_64"] = {file: "C:\\Program Files\\MATLAB\\R2021b\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\byteswap.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["cos"] = {file: "C:\\Program Files\\MATLAB\\R2021b\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["memset"] = {file: "C:\\Program Files\\MATLAB\\R2021b\\polyspace\\verifier\\cxx\\include\\include-libc\\string.h",
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
	 this.codeMetricsSummary = '<a href="javascript:void(0)" onclick="return postParentWindowMessage({message:\'gotoReportPage\', pageName:\'Resonanz_Regler_1_metrics\'});">Global Memory: 0(bytes) Maximum Stack: 44(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
