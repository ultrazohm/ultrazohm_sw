function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.fcn["cos"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["fabs"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["floor"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["fmod"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["memset"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\string.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["rt_modd"] = {file: "C:\\GIT\\UltraZohm\\software\\ultrazohm_sw_develop\\vitis\\software\\Baremetal\\src\\Codegen\\uz_codegen_pll_ert_rtw\\uz_codegen_pll.c",
	stack: 17,
	stackTotal: 17};
	 this.metricsArray.fcn["sin"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["uz_codegen_pll_initialize"] = {file: "C:\\GIT\\UltraZohm\\software\\ultrazohm_sw_develop\\vitis\\software\\Baremetal\\src\\Codegen\\uz_codegen_pll_ert_rtw\\uz_codegen_pll.c",
	stack: 12,
	stackTotal: 12};
	 this.metricsArray.fcn["uz_codegen_pll_step"] = {file: "C:\\GIT\\UltraZohm\\software\\ultrazohm_sw_develop\\vitis\\software\\Baremetal\\src\\Codegen\\uz_codegen_pll_ert_rtw\\uz_codegen_pll.c",
	stack: 28,
	stackTotal: 45};
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
	 this.codeMetricsSummary = '<a href="uz_codegen_pll_metrics.html">Global Memory: 0(bytes) Maximum Stack: 28(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
