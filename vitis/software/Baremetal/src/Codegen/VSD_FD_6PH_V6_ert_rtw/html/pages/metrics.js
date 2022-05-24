function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.fcn["VSD_FD_6PH_V6_initialize"] = {file: "C:\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\VSD_FD_6PH_V6_ert_rtw\\VSD_FD_6PH_V6.c",
	stack: 12,
	stackTotal: 12};
	 this.metricsArray.fcn["VSD_FD_6PH_V6_step"] = {file: "C:\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\Codegen\\VSD_FD_6PH_V6_ert_rtw\\VSD_FD_6PH_V6.c",
	stack: 32,
	stackTotal: 32};
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
	 this.codeMetricsSummary = '<a href="javascript:void(0)" onclick="return postParentWindowMessage({message:\'gotoReportPage\', pageName:\'VSD_FD_6PH_V6_metrics\'});">Global Memory: 0(bytes) Maximum Stack: 32(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
