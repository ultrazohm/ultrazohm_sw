function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.fcn["CC_Kp_id_adjustment_initialize"] = {file: "C:\\Users\\Philipp\\uz_temp\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\uz\\uz_CC_Kp_id_adjustment\\CC_Kp_id_adjustment_ert_rtw\\CC_Kp_id_adjustment.c",
	stack: 12,
	stackTotal: 12};
	 this.metricsArray.fcn["CC_Kp_id_adjustment_step"] = {file: "C:\\Users\\Philipp\\uz_temp\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\uz\\uz_CC_Kp_id_adjustment\\CC_Kp_id_adjustment_ert_rtw\\CC_Kp_id_adjustment.c",
	stack: 16,
	stackTotal: 16};
	 this.metricsArray.fcn["memset"] = {file: "C:\\Program Files\\MATLAB\\R2023b\\polyspace\\verifier\\cxx\\include\\include-libc\\string.h",
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
	 this.codeMetricsSummary = '<a href="javascript:void(0)" onclick="return postParentWindowMessage({message:\'gotoReportPage\', pageName:\'CC_Kp_id_adjustment_metrics\'});">Global Memory: 0(bytes) Maximum Stack: 16(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
